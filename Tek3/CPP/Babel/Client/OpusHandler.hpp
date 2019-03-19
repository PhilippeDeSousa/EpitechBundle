/*
 * OpusHandler.hpp
 *
 *  Created on: 5 oct. 2018
 *      Author: max
 */

#ifndef CLIENT_OPUSHANDLER_HPP_
#define CLIENT_OPUSHANDLER_HPP_

#include <vector>
#include <opus/opus.h>

namespace Babel {

	class OpusHandler {
	public:
		OpusHandler();
		virtual ~OpusHandler();

		std::vector<float> *decode(std::vector<unsigned char> data);
		std::vector<unsigned char> *encode(std::vector<float> data);

	private:
		OpusEncoder *_encoder;
		OpusDecoder *_decoder;

		std::vector<unsigned char> *_encodedData;
		std::vector<float> *_decodedData;

		int _decodeSize;
		int _encodeSize;
	};

} /* namespace Babel */

#endif /* CLIENT_OPUSHANDLER_HPP_ */
