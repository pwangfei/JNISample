package com.example.jnisample;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        Button sign = findViewById(R.id.sign);
        Button encryp = findViewById(R.id.encryp);

        SignatureJni paramsJni=new SignatureJni();
        sign.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                paramsJni.signatureVerify(MainActivity.this);
            }
        });

        encryp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });











    }



}