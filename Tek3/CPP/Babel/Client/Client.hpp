/*
 * Client.hpp
 *
 *  Created on: 2 oct. 2018
 *      Author: max
 */

#ifndef CLIENT_CLIENT_HPP_
#define CLIENT_CLIENT_HPP_

#include <AudioManager.hpp>

namespace Babel {

	class Client {
	public:
		Client();
		virtual ~Client();

		void startRecording();

	private:
		AudioManager _audioManager;
		//NetworkManager _networkManager;
		//OpusManager _opusManager;
	};

} /* namespace Babel */

#endif /* CLIENT_CLIENT_HPP_ */
