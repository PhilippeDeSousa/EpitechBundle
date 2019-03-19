package eu.epitech.area.retrofit

import java.net.URL

class URLUtils {
    companion object {
        private const val port = 8080
        private const val protocol = "http"
        fun getURL(ip: String): URL {
            return URL("$protocol://$ip:$port/")
        }
        /// Change this with the IP of the API
        const val default_ip = "192.168.0.26"
        fun getDefaultURL(): URL {
            return getURL(default_ip)
        }
    }
}