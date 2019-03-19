/*
 * AudioManager.hpp
 *
 *  Created on: 1 oct. 2018
 *      Author: max
 */

#ifndef AudioManager_HPP_
#define AudioManager_HPP_

#include <portaudio.h>
#include <vector>

namespace Babel {

#define SAMPLE_RATE  		(48000)
#define FRAMES_PER_BUFFER 	(480)
#define NUM_SECONDS     	(5)
#define NUM_CHANNELS    	(2)
#define DITHER_FLAG     	(0)

	typedef struct {
		int frameIndex;
		int maxFrameIndex;
		float *recordedSamples;
	} PaData;

	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();

		void RecordAudio();
		void PlayAudio();
		//void WriteAudio(File file);

	private:
		PaStreamParameters _inputParams, _outputParams;
		PaStream *_stream;
		PaError _err = paNoError;
		PaData _data;

		std::vector<PaData> _dataList;
		int _currentIndex;

		int _frameIndex;
		int _maxFrameIndex;

		void cleanData(int index);
		static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *);
		static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
				const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *);

	};
}

#endif /* AudioManager_HPP_ */
