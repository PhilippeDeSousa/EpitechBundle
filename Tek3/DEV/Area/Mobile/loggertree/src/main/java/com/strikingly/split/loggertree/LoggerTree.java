package com.strikingly.split.loggertree;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import timber.log.Timber;

public class LoggerTree extends Timber.DebugTree {
    public LoggerTree() {
        super();
    }

    protected void log(int priority, String tag, @NonNull String message, @Nullable Throwable t) {
        super.log(priority, tag, message, t);
    }

}