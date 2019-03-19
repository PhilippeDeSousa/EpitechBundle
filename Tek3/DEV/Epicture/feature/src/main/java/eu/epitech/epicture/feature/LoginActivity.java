package eu.epitech.epicture.feature;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.annotation.TargetApi;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.support.annotation.NonNull;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.app.LoaderManager.LoaderCallbacks;

import android.content.CursorLoader;
import android.content.Loader;
import android.database.Cursor;
import android.net.Uri;
import android.os.AsyncTask;

import android.os.Build;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

import static android.provider.AlarmClock.EXTRA_MESSAGE;

/**
 * A login screen that offers login via imgur
 */
public class LoginActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
    }

    /**
     * Called when the user taps the Sign in with Imgur button
     */
    public void signInWithImgur(View view) {
        Toast.makeText(getApplicationContext(), "Oauth2 redirection here", Toast.LENGTH_SHORT);
        final String apiKey = "6456259a0903071";
        Uri authorizeURL = Uri.parse("https://api.imgur.com/oauth2/authorize"
                + "?client_id=" + apiKey
                + "&response_type");
        Intent intent = new Intent(Intent.ACTION_VIEW, authorizeURL);
        startActivity(intent);

        /// Defined in AndroidManifest.xml as an Intent Filter
        final String oauth2callbackURL = "app://epicture/imgur/oauth2callback";
        final String apiSecret = "26bd63ea9462ead778eb56daf7cca835042030a1";
    }
}

