package com.example.jnisample;


import android.content.Context;

/**
 * Created by wpf 2023/2/15
 */

public class SignatureJni {


    /**
     * 包签名认证，只有授权的包才可以通过认证
     * @param context
     * @return
     */
    public native int signatureVerify(Context context);

    /**
     * 通过反射调用AES加密
     * @param context
     * @return
     */
    public native String signAES(Context context);


}
