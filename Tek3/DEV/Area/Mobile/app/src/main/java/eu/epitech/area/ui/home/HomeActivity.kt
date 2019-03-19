package eu.epitech.area.ui.home

import android.app.Activity
import android.app.Notification
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import androidx.core.net.toUri
import eu.epitech.area.R
import eu.epitech.area.retrofit.ApiService
import eu.epitech.area.retrofit.POJO.*
import kotlinx.android.synthetic.main.activity_home.*
import kotlinx.android.synthetic.main.service_timer.*
import kotlinx.android.synthetic.main.service_trends.*
import kotlinx.android.synthetic.main.service_weather.*
import okhttp3.ResponseBody
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import timber.log.Timber
import utils.App
import utils.Notifications
import utils.Notifications.Companion.CHANNEL_ID
import utils.Notifications.Companion.NOTIFICATION_ID
import utils.Notifications.Companion.notify
import utils.getDate
import java.text.SimpleDateFormat

class HomeActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_home)
    }

    fun notifs(@Suppress("UNUSED_PARAMETER") v: View) {
        val service = ApiService.getService()
        service.notifs(App.apiAccessToken).enqueue(object : Callback<ResponseBody> {
            override fun onFailure(call: Call<ResponseBody>?, t: Throwable?) {
                Timber.e(t)
                Notifications.notify(baseContext, "No new notifications")
            }

            override fun onResponse(call: Call<ResponseBody>?, response: Response<ResponseBody>?) {
                val body = response?.body()?.string()
                if (response?.code() == 200 && body != null) {
                    Notifications.notify(baseContext, body)
                } else {
                    onFailure(call, RuntimeException("Wrong response code: " + response?.code()))
                }
            }
        })
    }

    fun weather(@Suppress("UNUSED_PARAMETER") v: View) {
        val cityText = city.text.toString()
        val weatherAddPojo = WeatherAddPojo(city = cityText)
        val service = ApiService.getService()
        service.addWeather(weatherAddPojo, App.apiAccessToken).enqueue(addCallback)
    }

    fun timer(@Suppress("UNUSED_PARAMETER") v: View) {
        /// Get a date and convert it to the API format
        val date = date_picker.getDate()
        val format = SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
        val dateString = format.format(date)
        Timber.d("Add Timer: $dateString")

        val timerAddPojo = TimerAddPojo(date = dateString)
        val service = ApiService.getService()
        service.addTimer(timerAddPojo, App.apiAccessToken).enqueue(addCallback)
    }

    fun trends(@Suppress("UNUSED_PARAMETER") v: View) {
        val subjectText = subject.text.toString()
        val trendsAddPojo = TrendsAddPojo(subject = subjectText)
        val service = ApiService.getService()
        service.addTrends(trendsAddPojo, App.apiAccessToken).enqueue(addCallback)
    }

    private val addCallback = object : Callback<ResponseBody> {
        override fun onFailure(call: Call<ResponseBody>?, t: Throwable?) {
            Timber.e(t)
            toast("Retrofit Call Failed")
        }

        override fun onResponse(call: Call<ResponseBody>?, response: Response<ResponseBody>?) {
            if (response?.code() == 200) {
                toast("Added")
            } else {
                onFailure(call, RuntimeException("Wrong response code: " + response?.code()))
            }
        }
    }

    fun subscribeTimer(@Suppress("UNUSED_PARAMETER") v: View) {
        subscribeToService("timer")
    }

    fun subscribeWeather(@Suppress("UNUSED_PARAMETER") v: View) {
        subscribeToService("weather")
    }

    fun subscribeTrends(@Suppress("UNUSED_PARAMETER") v: View) {
        subscribeToService("trends")
    }

    private fun subscribeToService(serviceName: String) {
        val subscribePojo = SubscribePojo(service = serviceName)
        val service = ApiService.getService()
        service.subscribe(subscribePojo, App.apiAccessToken).enqueue(object : Callback<ResponseBody> {
            override fun onFailure(call: Call<ResponseBody>?, t: Throwable?) {
                Timber.e(t)
                toast("Retrofit Call Failed")
            }

            override fun onResponse(call: Call<ResponseBody>?, response: Response<ResponseBody>?) {
                if (response?.code() == 200) {
                    toast("Subscribed to service $serviceName")
                } else {
                    onFailure(call, RuntimeException("Wrong response code: " + response?.code()))
                }
            }
        })
    }

    private fun toast(str: String) {
        Timber.d(str)
        Toast.makeText(this, str, Toast.LENGTH_SHORT).show()
    }
}