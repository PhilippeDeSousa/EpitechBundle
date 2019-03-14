/*
 * StreamHandler.h
 *
 *  Created on: 2 oct. 2018
 *      Author: max
 */

#ifndef CLIENT_STREAMHANDLER_HPP_
#define CLIENT_STREAMHANDLER_HPP_

#include <portaudio.h>
#include <list>
#include <vector>

typedef float SAMPLE;

namespace Babel {

	namespace SoundDevice {
		const unsigned int channelCount = 1;
		const unsigned int sampleRate = 48000;
		const unsigned int framesPerBuffer = 512;
		const int PaSampleType = paFloat32;
		const float secTimeOfEachPacket = (0.011); //0.25
		const unsigned int maxDelay = 90;
	}

	enum AudioEventType {
		microOn, microOff, audioOn, audioOff, soundHigh, soundLow
	};

	class StreamHandler {
	public:
		StreamHandler();
		~StreamHandler();

		void processEvent(AudioEventType audioEventType);

		void ReadData(float data);
		float PlayData();
		int getIndexIn() const;
		int getIndexOut() const;
		bool getMicro() const;
		bool getAudio() const;
		void addDataInputToList();
		bool canPlayAudio();
		void endReadingAudio();

		void startAllStream();
		void stopAllStream();

		void event(AudioEventType event);

		std::vector<float> *getInputFromList();
		void addOutputToList(std::vector<float> *data);

	private:
		PaStream *_streamIn;
		PaStream *_streamOut;
		PaError _error;
		PaStreamParameters _outputParams;
		PaStreamParameters _inputParams;

		std::list<std::vector<float>*> _dataListInput;
		std::list<std::vector<float>*> _dataListOutput;
		std::vector<float> *_dataCurrentInput;
		std::vector<float> *_dataCurrentOutput;
		bool _dataOutputUsed;

		int _indexIn = 0;
		int _indexOut = 0;
		int _volume;

		bool _micro;
		bool _audio;

		void initStream();
	};

} /* namespace Babel */

#endif /* CLIENT_STREAMHANDLER_HPP_ */
