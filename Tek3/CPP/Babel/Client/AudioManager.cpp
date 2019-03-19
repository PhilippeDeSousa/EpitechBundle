/*
 * AudioManager.cpp
 *
 *  Created on: 1 oct. 2018
 *      Author: max
 */

#include <AudioManager.hpp>
#include <stdlib.h>
#include <iostream>
#include <opus.h>

namespace Babel {

	AudioManager::AudioManager() :
			_stream(), _frameIndex(0), _maxFrameIndex(NUM_SECONDS * SAMPLE_RATE), _currentIndex(0) {
		fflush(stdout);

		for (int i = 0; i < 9; i++) {
			PaData tmp;
			tmp.frameIndex = 0;
			tmp.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
			tmp.recordedSamples = (float*) malloc(tmp.maxFrameIndex * NUM_CHANNELS * sizeof(float));
			for (int i = 0; i < tmp.maxFrameIndex * NUM_CHANNELS; i++)
				tmp.recordedSamples[i] = 0;
			_dataList.push_back(tmp);
		}

		for (int i = 0; i < _dataList.size(); i++) {
			std::cout << "Initialisation dataList id : " << i << " Index : " << _dataList.at(i).frameIndex << std::endl;
		}

		_err = Pa_Initialize();
		if (_err != paNoError)
			throw("Pa_Initialize : Can''t initialize Port Audio.");

		_inputParams.device = Pa_GetDefaultInputDevice();
		if (_inputParams.device == paNoDevice) {
			throw("Pa_GetDefaultInputDevice : No device found.");
		}
		_inputParams.channelCount = 2;
		_inputParams.sampleFormat = paFloat32;
		_inputParams.suggestedLatency = Pa_GetDeviceInfo(_inputParams.device)->defaultLowInputLatency;
		_inputParams.hostApiSpecificStreamInfo = NULL;

		_outputParams.device = Pa_GetDefaultOutputDevice();
		if (_outputParams.device == paNoDevice) {
			throw("Pa_GetDefaultOutputDevice : No default output device.");
		}
		_outputParams.channelCount = 2;
		_outputParams.sampleFormat = paFloat32;
		_outputParams.suggestedLatency = Pa_GetDeviceInfo(_outputParams.device)->defaultLowOutputLatency;
		_outputParams.hostApiSpecificStreamInfo = NULL;

	}

	AudioManager::~AudioManager() {
		Pa_Terminate();
	}

	void AudioManager::cleanData(int index) {
		/*
		 if (index < _dataList.size()) {
		 for (int i = 0; i < _dataList.at(index).maxFrameIndex; i++)
		 _dataList.at(index).recordedSamples[i] = 0;
		 _dataList.at(index).frameIndex = 0;
		 } else {
		 throw("AudioManager::CleanData : Unvalid Index.");
		 }
		 */
	}

	void AudioManager::RecordAudio() {
		//_err = Pa_OpenStream(&_stream, &_inputParams, &_outputParams,
		//		SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);

		_err = Pa_OpenDefaultStream(&_stream, NUM_CHANNELS, NUM_CHANNELS, paInt16, SAMPLE_RATE,
		FRAMES_PER_BUFFER, nullptr, nullptr);
		if (_err != paNoError)
			throw("Pa_OpenStream.");

		_err = Pa_StartStream(_stream);
		if (_err != paNoError)
			throw("Pa_StartStream");
		printf("\n=== Now recording!! Please speak into the microphone. ===\n");
		fflush(stdout);

		int opusErr;
		// initialize opus
		OpusEncoder* enc = opus_encoder_create(
		SAMPLE_RATE, NUM_CHANNELS, OPUS_APPLICATION_AUDIO, &opusErr);
		if (opusErr != OPUS_OK) {
			std::cout << "opus_encoder_create failed: " << opusErr << "\n";
			//std::getline(std::cin, s);
			//return 1;
		}

		OpusDecoder* dec = opus_decoder_create(
		SAMPLE_RATE, NUM_CHANNELS, &opusErr);
		if (opusErr != OPUS_OK) {
			std::cout << "opus_decoder_create failed: " << opusErr << "\n";
			//std::getline(std::cin, s);
			//return 1;
		}

		opus_int32 enc_bytes;
		opus_int32 dec_bytes;

		std::vector<unsigned short> captured(FRAMES_PER_BUFFER * NUM_CHANNELS);
		std::vector<unsigned short> decoded(FRAMES_PER_BUFFER * NUM_CHANNELS);
		// * 2: byte count, 16 bit samples
		std::vector<unsigned char> encoded(FRAMES_PER_BUFFER * NUM_CHANNELS * 2);
		int framesProcessed = 0;
		while (framesProcessed < SAMPLE_RATE * NUM_SECONDS) {
			if ((_err = Pa_ReadStream(_stream, captured.data(), FRAMES_PER_BUFFER)) != paNoError) {
				//std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
				//std::getline(std::cin, s);
				std::cerr << "Error 1" << std::endl;
			}

			for (int i = 0; i < captured.size(); i++) {
				captured.at(i) *= 4;
			}
			/*
			if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const*>(captured.data()), 480, encoded.data(), encoded.size()))
					< 0) {
				std::cout << "opus_encode failed: " << enc_bytes << "\n";
				//std::getline(std::cin, s);
				//return 1;
			}

			if ((dec_bytes = opus_decode(dec, encoded.data(), enc_bytes, reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0) {
				std::cout << "opus_decode failed: " << dec_bytes << "\n";
				//std::getline(std::cin, s);
				//return 1;
			}*/

			if ((_err = Pa_WriteStream(_stream, decoded.data(), FRAMES_PER_BUFFER)) != paNoError) {
				std::cerr << "Error 2" << std::endl;
				std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(_err) << "\n";
				//std::getline(std::cin, s);
				//return 1;
			}

			framesProcessed += FRAMES_PER_BUFFER;
		}

		//while ((_err = Pa_IsStreamActive(_stream)) == 1) {
		//	Pa_Sleep(1000);
		//	fflush(stdout);
		//}
		//if (_err != paNoErr)

		for (int i = 0; i < captured.size(); i++) {
			std::cout << captured.at(i) << std::endl;
		}

		_err = Pa_CloseStream(_stream);
	}
}
