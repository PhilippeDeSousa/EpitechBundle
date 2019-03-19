package eu.epitech.area.retrofit

import eu.epitech.area.retrofit.POJO.*
import okhttp3.ResponseBody
import retrofit2.Call
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.Query
import utils.App

interface ApiService {
    @POST("/login")
    fun login(@Body loginPojo : LoginPojo): Call<TokenPojo>

    @POST("/signup")
    fun signup(@Body signUpPojo: SignUpPojo): Call<ResponseBody>

    @GET("/notifs")
    fun notifs(@Query("token") token: String): Call<ResponseBody>

    @POST("/subscribe")
    fun subscribe(@Body subscribePojo: SubscribePojo, @Query("token") token: String): Call<ResponseBody>

    @POST("/add")
    fun addWeather(@Body weatherAddPojo: WeatherAddPojo, @Query("token") token: String): Call<ResponseBody>

    @POST("/add")
    fun addTimer(@Body timerAddPojo: TimerAddPojo, @Query("token") token: String): Call<ResponseBody>

    @POST("/add")
    fun addTrends(@Body trendsAddPojo: TrendsAddPojo, @Query("token") token: String): Call<ResponseBody>

    companion object {
        fun getService() : ApiService {
            val retrofit = Retrofit.Builder()
                .addConverterFactory(GsonConverterFactory.create())
                .baseUrl(App.apiURL.toString())
                .build()
            return retrofit.create<ApiService>(ApiService::class.java)
        }
    }
}