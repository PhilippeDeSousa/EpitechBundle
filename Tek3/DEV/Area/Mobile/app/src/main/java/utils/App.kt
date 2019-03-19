package utils

import android.app.Application
//import com.squareup.leakcanary.LeakCanary
import com.strikingly.split.loggertree.LoggerTree
import eu.epitech.area.R
import eu.epitech.area.retrofit.URLUtils
import timber.log.Timber
import java.net.URL

class App : Application() {

    companion object {
        var apiURL: URL = URLUtils.getDefaultURL()
        var apiAccessToken: String = ""
    }

    override fun onCreate() {
        super.onCreate()
/*
        /// Leak Check in debug builds
        if (LeakCanary.isInAnalyzerProcess(this)) {
            // This process is dedicated to LeakCanary for heap analysis.
            // You should not init your app in this process.
            return
        }
        LeakCanary.install(this)
*/
        Timber.plant(LoggerTree())
    }


}