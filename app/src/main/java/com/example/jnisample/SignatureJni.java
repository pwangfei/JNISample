package com.example.jnisample;


import android.content.Context;

/**
 * Created by wpf 2023/2/15
 */

public class SignatureJni {


    public native int signatureVerify(Context context);

    public native int md5(Context context);
}
