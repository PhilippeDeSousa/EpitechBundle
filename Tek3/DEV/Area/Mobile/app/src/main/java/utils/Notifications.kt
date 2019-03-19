package utils

import android.app.NotificationChannel
import android.app.NotificationManager
import android.content.Context
import android.os.Build
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import eu.epitech.area.R
import timber.log.Timber

class Notifications {
    companion object {
        const val CHANNEL_ID = "AREA"
        const val NOTIFICATION_ID = 1
        private const val CHANNEL_NAME = CHANNEL_ID
        private const val CHANNEL_DESCRIPTION = "This channel is used to get notifications from the API"

        fun createNotificationChannel(context: Context) {
            // Create the NotificationChannel, but only on API 26+ because
            // the NotificationChannel class is new and not in the support library
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                val importance = NotificationManager.IMPORTANCE_DEFAULT
                val channel = NotificationChannel(CHANNEL_ID, CHANNEL_NAME, importance).apply {
                    description = CHANNEL_DESCRIPTION
                }
                // Register the channel with the system
                val notificationManager: NotificationManager =
                    context.getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
                notificationManager.createNotificationChannel(channel)
            }
        }

        fun notify(context: Context, message: String) {
            Timber.d(message)
            /// Create a notification channel
            Notifications.createNotificationChannel(context)
            // Build a new notification, which informs the user that the system
            // handled their interaction with the previous notification.
            val builder = NotificationCompat.Builder(context, CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_notifications_black_24dp)
                .setContentTitle("AREA")
                .setContentText(message)
                /*
                .setStyle(
                    NotificationCompat.BigTextStyle()
                        .bigText(message)
                )
                */
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
            // Issue the new notification.
            NotificationManagerCompat.from(context).apply {
                this.notify(NOTIFICATION_ID, builder.build())
            }
        }
    }
}