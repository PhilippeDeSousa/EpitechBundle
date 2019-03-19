package eu.epitech.area.data

import android.os.AsyncTask
import eu.epitech.area.data.model.LoggedInUser
import eu.epitech.area.retrofit.ApiService
import eu.epitech.area.retrofit.POJO.LoginPojo
import eu.epitech.area.retrofit.POJO.SignUpPojo
import kotlinx.coroutines.*
import retrofit2.Call
import timber.log.Timber
import utils.App
import java.io.IOException
import kotlin.concurrent.thread

/**
 * Class that handles authentication w/ login credentials and retrieves user information.
 */
class LoginDataSource {

    fun login(username: String, password: String): Result<LoggedInUser> {
            if (signInOrRegister(username, password)) {
                return Result.Success(LoggedInUser(username))
            }
            return Result.Error(IOException("Error logging in"))
    }

    private fun signInOrRegister(username: String, password: String) : Boolean {
        if (signIn(username, password))
            return true
        else if (register(username, password, username) && signIn(username, password))
            return true
        return false
    }

    private fun signIn(username: String, password: String) : Boolean {
        Timber.d("Signing In")
        val loginPojo = LoginPojo(username, password)
        val service = ApiService.getService()

        return try {
            val call = runBlocking(Dispatchers.IO) {
                return@runBlocking service.login(loginPojo).execute()
            }
            Timber.d("Login executed with code: %s", call.code())
            val token = call.body()?.token
            Timber.d("Token: $token")
            if (token != null) {
                App.apiAccessToken = token
                true
            } else {
                false
            }
        } catch (e: Exception) {
            Timber.d(e, "Retrofit had a problem")
            false
        }
    }

    private fun register(username: String, password: String, email: String) : Boolean {
        Timber.d("Registering")
        val signUpPojo = SignUpPojo(username, password, email)
        val service = ApiService.getService()

        return try {
            val call = runBlocking(Dispatchers.IO) {
                return@runBlocking service.signup(signUpPojo).execute()
            }
            Timber.d("Signup executed with code: %s", call.code())
            call.code() == 200
        } catch (e: Exception) {
            Timber.d(e, "Retrofit had a problem")
            false
        }
    }


    fun logout() {
        // TODO: revoke authentication
    }
}

