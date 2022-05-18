package com.example.jnisample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
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


        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        /**
         *  函數調用类的參數
         */
//        FieldJni fieldJni=new FieldJni();
//        Log.e("wpf123wpf", "调用前: " + fieldJni.num);
//        Log.e("wpf123wpf", "调用后 : " + fieldJni.addNum());

//        Log.e("wpf123wpf", "调用前：name = " + fieldJni.name);
//        fieldJni.accessStaticField();
//        Log.e("wpf123wpf", "调用后：" + fieldJni.name);

//        Log.e("wpf123wpf", "调用前：age = " + fieldJni.getAge());
//        fieldJni.accessPrivateField();
//        Log.e("wpf123wpf", "调用后：age = " + fieldJni.getAge());

        /**
         * JNI 访问 Java 的方法
         */
//        MethodJni methodJni = new MethodJni();
//        Log.e("wpf123wpf", "调用前：getSex() = " + methodJni.getSex());
//        methodJni.accessPublicMethod();
//        Log.e("wpf123wpf", "调用后：getSex() = " + methodJni.getSex());
//        Log.e("wpf123wpf", "调用静态方法：getHeight() = " + methodJni.accessStaticMethod());
//        Log.e("wpf123wpf", "调用父类方法：hello(name) = " + methodJni.accessSuperMethod());


        /**
         * 传递参数给 JNI 函数
         */
        Log.e("wpf123wpf", "-----------传递参数给 JNI 函数----------");
        ParamsJni paramsJni = new ParamsJni();

        Log.e("wpf123wpf", "intMethod: " + paramsJni.intMethod(4));
        Log.e("wpf123wpf", "stringMethod: " + paramsJni.stringMethod("cfanr"));
        Log.e("wpf123wpf", "intArrayMethod: " + paramsJni.intArrayMethod(new int[]{4, 9, 10, 16}) + "");
        Log.e("wpf123wpf", "objectMethod: " + paramsJni.objectMethod(new Person()).toString() + "");
        ArrayList<Person> personList = new ArrayList<>();
        Person person;
        for (int i = 0; i < 3; i++) {
            person = new Person();
            person.setName("cfanr");
            person.setAge(10 + i);
            personList.add(person);
        }
        Log.e("wpf123wpf", "调用前：java list = " + personList.toString());
        Log.e("wpf123wpf", "调用后：jni list  = " + paramsJni.personArrayListMethod(personList).toString());


        /**
         * JNI 函数字符串处理
         */
        Log.e("wpf123wpf", "-----------JNI 函数字符串处理----------");
        StringJni stringJni = new StringJni();
        Log.e("wpf123wpf", "handlerString: " + stringJni.handlerString("cfanr"));
        byte[] bytes = stringJni.handlerStrToByte("navyifanr");
        for (byte b : bytes) {
            Log.e("wpf123wpf", "handlerStrToByte: " + (char) b);
        }

        /**
         * 动态注册 JNI
         */
        Log.e("wpf123wpf", "-----------动态注册 JNI----------");
        String hello = new DynamicRegisterJni().getStringFromCpp();
        Log.e("wpf123wpf", hello);

    }


    public native String stringFromJNI();
}