package eu.epitech.area.data

import android.view.View
import com.github.scribejava.apis.GoogleApi20
import com.github.scribejava.core.builder.ServiceBuilder
import timber.log.Timber
import java.util.*

class SignInButton {
    fun signInWithGoogle(view: View?) {
        /// TODO: Google button
        /// TODO: Connect button to onclick
        val clientId = "667080207891-ekeh722392869t5n3sm5n8ev0drlv6ar.apps.googleusercontent.com"
        //val clientSecret = "your client secret"
        val secretState = "secret" + Random().nextInt(999999)
        val service = ServiceBuilder(clientId)
        //        .apiSecret(clientSecret)
                .scope("profile") // replace with desired scope
                .callback("http://example.com/callback")
                .build(GoogleApi20.instance())

        //pass access_type=offline to get refresh token
        //https://developers.google.com/identity/protocols/OAuth2WebServer#preparing-to-start-the-oauth-20-flow
        val additionalParams = HashMap<String, String>()
        additionalParams.put("access_type", "offline")
        //force to reget refresh token (if usera are asked not the first time)
        additionalParams.put("prompt", "consent")
        val authorizationUrl = service.getAuthorizationUrl(secretState, additionalParams)
        Timber.d(authorizationUrl)
    }
}