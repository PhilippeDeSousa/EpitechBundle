package eu.epitech.area.retrofit

import eu.epitech.area.retrofit.POJO.Office365OAuth2Pojo
import retrofit2.Call
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.GET
import retrofit2.http.Path
import utils.App

interface Office365Service {
    @GET("/auth/office")
    fun auth(): Call<Office365OAuth2Pojo>

    companion object {
        fun getService(): Office365Service {
            val retrofit = Retrofit.Builder()
                .addConverterFactory(GsonConverterFactory.create())
                .baseUrl(App.apiURL.toString())
                .build()
            return retrofit.create<Office365Service>(Office365Service::class.java)
        }
    }
}