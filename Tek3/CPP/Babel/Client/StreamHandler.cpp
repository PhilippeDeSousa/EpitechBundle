/*
 * StreamHandler.cpp
 *
 *  Created on: 2 oct. 2018
 *      Author: max
 */

#include <StreamHandler.hpp>
#include <unistd.h>
#include <cstdio>
#include <iostream>

namespace Babel {
	/**
	 ** CallBack Function to Record data 
	 ** Called with wen stream initialize Micro
	 */
	int recordCallback(const void *input, void *output, unsigned long, const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags, void *userData) {
		StreamHandler *handler = (StreamHandler*) userData;
		const SAMPLE *in = (const SAMPLE*) input;

		if ((SoundDevice::sampleRate * SoundDevice::secTimeOfEachPacket) - handler->getIndexIn() < SoundDevice::framesPerBuffer) {
			handler->addDataInputToList();
			return paContinue;
		}

		for (int i = 0; i < SoundDevice::framesPerBuffer; i++) {
			handler->ReadData(*in++);
		}
		return paContinue;
	}

	/**
	 ** Callback Function to Play data 
	 ** Called with wen stream initialize Audio
	 */
	int playCallback(const void *input, void *output, unsigned long, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
			void *userData) {
		StreamHandler *handler = (StreamHandler*) userData;
		SAMPLE *out = (SAMPLE*) output;

		if (handler->canPlayAudio() || handler->getAudio()) {
			if ((SoundDevice::sampleRate * SoundDevice::secTimeOfEachPacket) - handler->getIndexOut() < SoundDevice::framesPerBuffer) {
				handler->endReadingAudio();
				return paContinue;
			}
			for (int i = 0; i < SoundDevice::framesPerBuffer; i++) {
				*out++ = handler->PlayData();
			}
		} else {
			*out++ = (0.0f);
		}
		return paContinue;
	}

	/**
	 ** Constructor
	 */
	StreamHandler::StreamHandler() :
			_volume(4), _dataOutputUsed(false) {
		this->_dataCurrentInput = new std::vector<float>(SoundDevice::channelCount * SoundDevice::sampleRate * SoundDevice::secTimeOfEachPacket);
		this->_dataCurrentOutput = new std::vector<float>(SoundDevice::channelCount * SoundDevice::sampleRate * SoundDevice::secTimeOfEachPacket);
		for (int i = 0; i < _dataCurrentInput->size(); i++) {
			_dataCurrentInput->at(i) = 0;
			_dataCurrentOutput->at(i) = 0;
		}

		Pa_Initialize();
		initStream();

		event(Babel::AudioEventType::microOn);
		Pa_Sleep(2000);
		event(Babel::AudioEventType::audioOn);
	}

	StreamHandler::~StreamHandler() {
		stopAllStream();
		Pa_Terminate();
	}

	/**
	 ** Stream Input & Output Initilize
	 */
	void StreamHandler::initStream() {
		_outputParams.device = Pa_GetDefaultOutputDevice();
		if (_outputParams.device == paNoDevice) {
			throw("Pa_GetDefaultOutputDevice : No device found.");
		}
		_outputParams.channelCount = SoundDevice::channelCount;
		_outputParams.sampleFormat = SoundDevice::PaSampleType;
		_outputParams.suggestedLatency = Pa_GetDeviceInfo(_outputParams.device)->defaultHighInputLatency;
		_outputParams.hostApiSpecificStreamInfo = NULL;

		_inputParams.device = Pa_GetDefaultInputDevice();
		if (_inputParams.device == paNoDevice) {
			throw("Pa_GetDefaultInputDevice : No device found.");
		}
		_inputParams.channelCount = SoundDevice::channelCount;
		_inputParams.sampleFormat = SoundDevice::PaSampleType;
		_inputParams.suggestedLatency = Pa_GetDeviceInfo(_inputParams.device)->defaultHighInputLatency;
		_inputParams.hostApiSpecificStreamInfo = NULL;

		_error = Pa_OpenStream(&this->_streamIn, &this->_inputParams, NULL, SoundDevice::sampleRate, SoundDevice::framesPerBuffer, paClipOff, recordCallback, this);
		if (_error != paNoError) {
			throw("Pa_OpenStream.");
		}
		_error = Pa_OpenStream(&this->_streamOut, NULL, &this->_outputParams, SoundDevice::sampleRate, SoundDevice::framesPerBuffer, paClipOff, playCallback, this);
		if (_error != paNoError) {
			throw("Pa_OpenStream.");
		}
		std::cout << "[Info] Stream : Initialize successfully" << std::endl;
	}

	/**
	 ** Audio Event
	 ** Micro On / Micro Off / Audio On / Audio Off
	 */
	void StreamHandler::event(AudioEventType event) {
		switch (event) {
		case (AudioEventType::microOn):
			_error = Pa_OpenStream(&this->_streamIn, &this->_inputParams, NULL, SoundDevice::sampleRate, SoundDevice::framesPerBuffer, paClipOff, recordCallback,
					this);
			if (_error != paNoError) {
				throw("Pa_OpenStream : When trying to activate mirocrphone.");
			}
			_error = Pa_StartStream(_streamIn);
			if (_error != paNoError) {
				throw("Pa_StartStream : Input Stream.");
			}
			_micro = true;
			std::cout << "[Info] Microphone : On" << std::endl;
			break;

		case (AudioEventType::microOff):
			if (Pa_IsStreamActive(_streamIn)) {
				Pa_CloseStream(_streamIn);
				_micro = false;
				std::cout << "[Info] Microphone : Off" << std::endl;
			}
			break;

		case (AudioEventType::audioOn):
			_error = Pa_OpenStream(&this->_streamOut, NULL, &this->_outputParams, SoundDevice::sampleRate, SoundDevice::framesPerBuffer, paClipOff, playCallback,
					this);
			if (_error != paNoError) {
				throw("Pa_OpenStream : When trying to activate audio.");
			}
			_error = Pa_StartStream(_streamOut);
			if (_error != paNoError) {
				throw("Pa_StartStream : Output Stream.");
			}
			_audio = true;
			std::cout << "[Info] Audio : On" << std::endl;
			break;

		case (AudioEventType::audioOff):
			if (Pa_IsStreamActive(_streamOut)) {
				Pa_CloseStream(_streamOut);
				_audio = false;
				std::cout << "[Info] Audio : Off" << std::endl;
			}
			break;

		case (AudioEventType::soundHigh):
			if (_volume < 10) {
				_volume++;
			} else {
				std::cout << "[Info] Maximum Volume reach" << std::endl;
			}
			std::cout << "[Info] Volume : " << _volume << std::endl;
			break;

		case (AudioEventType::soundLow):
			if (_volume > 1) {
				_volume--;
			} else {
				std::cout << "[Info] Minimum Volume reach" << std::endl;
			}
			std::cout << "[Info] Volume : " << _volume << std::endl;
			break;
		}
	}

	/**
	 ** All Stream On 
	 */
	void StreamHandler::startAllStream() {
		event(Babel::AudioEventType::microOn);
		event(Babel::AudioEventType::audioOn);
	}

	/**
	 ** All Stream Off
	 */
	void StreamHandler::stopAllStream() {
		event(Babel::AudioEventType::microOff);
		event(Babel::AudioEventType::audioOff);
	}

	void StreamHandler::ReadData(float data) {
		if (_dataCurrentInput->size() > _indexIn * SoundDevice::channelCount) {
			_dataCurrentInput->at(_indexIn * SoundDevice::channelCount) = data * _volume;
			_indexIn++;
		} else {
			std::cerr << "ReadData : Index out of bound." << std::endl;
		}
	}

	/**
	 ** Add to data certain amount of readed data
	 */
	float StreamHandler::PlayData() {
		if (_dataCurrentOutput->size() > _indexOut * SoundDevice::channelCount) {
			float data = _dataCurrentOutput->at(_indexOut * SoundDevice::channelCount);
			_indexOut++;
			return (data);
		} else {
			std::cerr << "PlayData : Index out of bound." << std::endl;
		}
		return (0);
	}

	/**
	 ** Add all Current readed data to the list of all readed data
	 */
	void StreamHandler::addDataInputToList() {
		if (_dataListInput.size() >= SoundDevice::maxDelay)
			_dataListInput.clear();
		_dataListInput.push_back(_dataCurrentInput);
		_indexIn = 0;
	}

	int StreamHandler::getIndexIn() const {
		return _indexIn;
	}

	int StreamHandler::getIndexOut() const {
		return _indexOut;
	}

	bool StreamHandler::getMicro() const {
		return _micro;
	}

	bool StreamHandler::getAudio() const {
		return _audio;
	}

	void StreamHandler::endReadingAudio() {
		_dataOutputUsed = false;
	}

	/**
	 ** Check if audio can be played
	 */
	bool StreamHandler::canPlayAudio() {
		if (_dataOutputUsed) {
			return true;
		} else { // change with dataListOutput
			if (!_dataListOutput.empty()) {
				//printf("O = %lu I = %lu\n", _dataListOutput.size(), _dataListInput.size());
				_dataOutputUsed = true;
				_dataCurrentOutput = _dataListOutput.front();
				_dataListOutput.pop_front();
				_indexOut = 0;
				return false; // try with true : skip 1 tour de boucle dans la thread play
			} else {
				return false;
			}
		}
	}

	std::vector<float> *StreamHandler::getInputFromList() {
		if (!_dataListInput.empty()) {
			std::vector<float> *ret = _dataListInput.front();
			_dataListInput.pop_front();
			return ret;
		}
		return nullptr;
	}

	void StreamHandler::addOutputToList(std::vector<float> 	*data) {
		this->_dataListOutput.push_back(data);
	}
}

/* namespace Babel */

