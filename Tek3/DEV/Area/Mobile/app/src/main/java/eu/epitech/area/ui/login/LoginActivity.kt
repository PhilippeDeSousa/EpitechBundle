package eu.epitech.area.ui.login

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.view.inputmethod.EditorInfo
import android.widget.TextView
import android.widget.Toast
import androidx.annotation.StringRes
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProviders
import eu.epitech.area.ui.home.HomeActivity
import kotlinx.android.synthetic.main.activity_login.*
import utils.App
import utils.afterTextChanged
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.Retrofit
import eu.epitech.area.retrofit.Office365Service
import eu.epitech.area.retrofit.POJO.Office365OAuth2Pojo
import eu.epitech.area.retrofit.URLUtils
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import timber.log.Timber
import androidx.core.net.toUri


class LoginActivity : AppCompatActivity() {

    private lateinit var loginViewModel: LoginViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(eu.epitech.area.R.layout.activity_login)

        loginViewModel = ViewModelProviders.of(this, LoginViewModelFactory())
            .get(LoginViewModel::class.java)

        loginViewModel.loginFormState.observe(this@LoginActivity, Observer {
            val loginState = it ?: return@Observer

            // disable login button unless both username / password is valid
            login.isEnabled = loginState.isDataValid

            if (loginState.usernameError != null) {
                username.error = getString(loginState.usernameError)
            }
            if (loginState.passwordError != null) {
                password.error = getString(loginState.passwordError)
            }
        })

        loginViewModel.loginResult.observe(this@LoginActivity, Observer {
            val loginResult = it ?: return@Observer

            loading.visibility = View.GONE
            if (loginResult.error != null) {
                showLoginFailed(loginResult.error)
            } else if (loginResult.success != null) {
                updateUiWithUser(loginResult.success)
                val homeIntent = Intent(this, HomeActivity::class.java)
                startActivity(homeIntent)
            }
            //setResult(Activity.RESULT_OK)

            //Complete and destroy login activity once successful
            //finish()
        })

        username.afterTextChanged {
            loginViewModel.loginDataChanged(
                username.text.toString(),
                password.text.toString()
            )
        }

        password.apply {
            afterTextChanged {
                loginViewModel.loginDataChanged(
                    username.text.toString(),
                    password.text.toString()
                )
            }

            setOnEditorActionListener { _, actionId, _ ->
                when (actionId) {
                    EditorInfo.IME_ACTION_DONE ->
                        loginViewModel.login(
                            username.text.toString(),
                            password.text.toString()
                        )
                }
                false
            }

            login.setOnClickListener {
                loading.visibility = View.VISIBLE
                loginViewModel.login(username.text.toString(), password.text.toString())
            }
        }

        ip.setText(URLUtils.default_ip, TextView.BufferType.EDITABLE)
        ip.afterTextChanged {
            updateApiUrl(it)
        }
    }

    private fun updateUiWithUser(model: LoggedInUserView) {
        val welcome = getString(eu.epitech.area.R.string.welcome)
        val displayName = model.displayName
        // TODO : initiate successful logged in experience
        toast("$welcome $displayName")
    }

    private fun showLoginFailed(@StringRes errorString: Int) {
        Toast.makeText(applicationContext, errorString, Toast.LENGTH_SHORT).show()
    }

    /// We get the refresh token and access token here
    override fun onResume() {
        super.onResume()

        val uri = intent.data
        if (uri != null) {
            toast(uri.toString())
        }
    }

    private fun updateApiUrl(ip: String) = try {
        val url = URLUtils.getURL(ip)
        App.apiURL = url
    } catch (e: Exception) {
        Timber.e(e)
    }

    fun SignInOffice(@Suppress("UNUSED_PARAMETER") v: View) {
        Timber.d("Starting retrofit service on base URL: %s", App.apiURL)
        val service = Office365Service.getService()
        service.auth().enqueue(object : Callback<Office365OAuth2Pojo> {
            override fun onFailure(call: Call<Office365OAuth2Pojo>?, t: Throwable?) {
                Timber.e(t)
                toast("Retrofit Call Failed")
            }

            override fun onResponse(call: Call<Office365OAuth2Pojo>?, response: Response<Office365OAuth2Pojo>?) {
                if (response?.code() == 400) {
                    val signInUrl = response.body()?.signInUrl
                    Timber.d("Sign in URL: $signInUrl")
                    if (signInUrl != null) {
                        val browserIntent = Intent(Intent.ACTION_VIEW, signInUrl.toUri())
                        startActivity(browserIntent)
                    }
                } else {
                    onFailure(call, RuntimeException("Wrong response code: " + response?.code()))
                }
            }
        })
    }

    fun toast(str: String) {
        Timber.d(str)
        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
    }
}

