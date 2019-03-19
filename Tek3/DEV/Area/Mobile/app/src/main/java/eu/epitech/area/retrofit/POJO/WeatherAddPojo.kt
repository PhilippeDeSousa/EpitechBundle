package eu.epitech.area.retrofit.POJO

data class WeatherAddPojo(
    val service: String = "weather",
    val city: String?
)