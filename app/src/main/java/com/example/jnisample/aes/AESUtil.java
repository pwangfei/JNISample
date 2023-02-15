package com.example.jnisample.aes;


import java.io.UnsupportedEncodingException;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class AESUtil {
    private final String CIPHERMODEPADDING = "AES/CBC/PKCS5Padding";// AES/CBC/PKCS7Padding

    private SecretKeySpec skforAES = null;
    private static String ivParameter = "qo5GkZqbZRjNILvw";// 密钥默认偏移，可更改

    private byte[] iv = ivParameter.getBytes();
    private IvParameterSpec IV;
    String sKey = "yOLsWAkt5Pah1n7q";// key必须为16位，可更改为自己的key

    private static AESUtil instance = null;

    public static AESUtil getInstance() {
        if (instance == null) {
            synchronized (AESUtil.class) {
                if (instance == null) {
                    instance = new AESUtil();
                }
            }
        }
        return instance;
    }

    public AESUtil() {
        byte[] skAsByteArray;
        try {
            skAsByteArray = sKey.getBytes("ASCII");
            skforAES = new SecretKeySpec(skAsByteArray, "AES");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        IV = new IvParameterSpec(iv);
    }

    public String encrypt(byte[] plaintext) {
        byte[] ciphertext = encrypt(CIPHERMODEPADDING, skforAES, IV, plaintext);
        String base64_ciphertext = Base64Encoder.encode(ciphertext);
        return base64_ciphertext;
    }

    public String decrypt(String ciphertext_base64) {
        byte[] s = Base64Decoder.decodeToBytes(ciphertext_base64);
        String decrypted = new String(decrypt(CIPHERMODEPADDING, skforAES, IV, s));
        return decrypted;
    }

    private byte[] encrypt(String cmp, SecretKey sk, IvParameterSpec IV,
                           byte[] msg) {
        try {
            Cipher c = Cipher.getInstance(cmp);
            c.init(Cipher.ENCRYPT_MODE, sk, IV);
            return c.doFinal(msg);
        } catch (Exception nsae) {
        }
        return null;
    }

    public byte[] decrypt(String cmp, SecretKey sk, IvParameterSpec IV,
                           byte[] ciphertext) {
        try {
            Cipher c = Cipher.getInstance(cmp);
            c.init(Cipher.DECRYPT_MODE, sk, IV);
            return c.doFinal(ciphertext);
        } catch (Exception nsae) {
        }
        return null;
    }
}
