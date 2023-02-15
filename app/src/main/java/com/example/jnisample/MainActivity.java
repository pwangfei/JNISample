package com.example.jnisample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.jnisample.model.Person;

import java.util.ArrayList;

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

        ParamsJni paramsJni=new ParamsJni();
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