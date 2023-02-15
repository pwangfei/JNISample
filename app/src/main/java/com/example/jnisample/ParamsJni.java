package com.example.jnisample;


import android.content.Context;

import com.example.jnisample.model.Person;

import java.util.ArrayList;

/**
 * Created by Pipi on 2017/8/2.
 */

public class ParamsJni {

    public native int intMethod(int n);



    public native int signatureVerify(Context context);

}
