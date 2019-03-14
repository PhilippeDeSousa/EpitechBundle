/*
 * OpusHandler.cpp
 *
 *  Created on: 5 oct. 2018
 *      Author: max
 */

#include <boost/asio.hpp>
#include <opus/opus_defines.h>
#include <OpusHandler.hpp>
#include <StreamHandler.hpp>
#include <cstdio>

namespace Babel {

	OpusHandler::OpusHandler() :
			_decodeSize(0), _encodeSize(0) {
		_encoder = opus_encoder_create(SoundDevice::sampleRate, SoundDevice::channelCount, OPUS_APPLICATION_VOIP, NULL);
		_decoder = opus_decoder_create(SoundDevice::sampleRate, SoundDevice::channelCount, NULL);

		this->_decodedData = new std::vector<float>(SoundDevice::channelCount * SoundDevice::sampleRate * SoundDevice::secTimeOfEachPacket);
		this->_encodedData = new std::vector<unsigned char>(SoundDevice::channelCount * SoundDevice::sampleRate * SoundDevice::secTimeOfEachPacket);
	}

	OpusHandler::~OpusHandler() {
	        opus_encoder_destroy(_encoder);
	        opus_decoder_destroy(_decoder);
	}

	std::vector<float> *OpusHandler::decode(std::vector<unsigned char> sound) {
		/*
		for (int i = 0; i < sound.size(); i++) {
			if (sound.at(i) != 0) {
				printf("BBBAAA%d\n", sound.at(i));
			}
		}*/

		//_decodedData->resize(sound.size());
		_decodeSize = opus_decode_float(_decoder, sound.data(), _encodeSize, _decodedData->data(), 480, 0); //* SoundDevice::channelCount;
		if (_decodeSize < 0) {
			throw("opus_decode_float : Couldn''t decode data.");
		}
		//printf("RET = %d\nSIZE = %lu\n", _decodeSize, _decodedData->size() );

		/*
		for (int i = 0; i < _decodedData->size(); i++) {
			if (_decodedData->at(i) != 0) {
				printf("DECODED = %f.\n", _decodedData->at(i));
			}
		}*/


		return _decodedData;
	}

	std::vector<unsigned char> *OpusHandler::encode(std::vector<float> sound) {

		printf("SIZE = %lu\n", sound.size());

		/*
		for (int i = 0; i < sound.size(); i++) {
			if (sound.at(i)) {
				printf("%f\n", sound.at(i));
			}
		}*/

		//_encodedData->resize(sound.size());
		_encodeSize = opus_encode_float(_encoder, sound.data(), 480, _encodedData->data(), sound.size());
		if (_encodeSize < 0) {
			throw("opus_encode_float : Couldn''t encode data.");
		}
		//printf("ret = %d\n", _encodeSize);
		/*

		for (int i = 0; i < _encodedData->size(); i++) {
			if (_encodedData->at(i) != 0) {
				printf("AAABBB = %d.\n", _encodedData->at(i));
			}
		}*/

		return _encodedData;
	}

} /* namespace Babel */







