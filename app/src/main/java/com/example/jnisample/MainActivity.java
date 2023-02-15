package com.example.jnisample;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.example.jnisample.aes.AESUtil;

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
        String str="opopopopjasjdakjsdljalsdjlia";
        String enstr=AESUtil.getInstance().encrypt(str.getBytes());
        Log.e("wpf123wpf", "加密的数据: "+enstr );
        String destr= AESUtil.getInstance().decrypt(enstr);
        Log.e("wpf123wpf", "解密的数据: "+destr );


        encryp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });











    }



}