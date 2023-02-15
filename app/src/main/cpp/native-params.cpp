#include <jni.h>
#include <string>
#include <android/log.h>
#define LOG_TAG "wpf123wpf"

//可以使用的包名
const char *PACKAGE_NAME = "com.example.jnisample";
//APP的签名
int APP_SIGNATURE = 244699197;
//是否可用
bool isVerify = 0;


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnisample_SignatureJni_signatureVerify(JNIEnv *env, jobject thiz, jobject context) {
    //1.校验包名
    jclass jclz = env->GetObjectClass(context);
    jmethodID jmid = env->GetMethodID(jclz, "getPackageName", "()Ljava/lang/String;");
    jstring jPackageName = static_cast<jstring>(env->CallObjectMethod(context, jmid));
    const char *cPackageName = env->GetStringUTFChars(jPackageName, 0);
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s", cPackageName);
    if (strcmp(cPackageName, PACKAGE_NAME) != 0) {//校验包名，如果包名不对直接退出
        exit(0);
    }

    jmid = env->GetMethodID(jclz, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject packManager = env->CallObjectMethod(context, jmid);
    //getPackageInfo
    jclz = env->GetObjectClass(packManager);
    jmid = env->GetMethodID(jclz, "getPackageInfo",
                            "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageInfo = env->CallObjectMethod(packManager, jmid, jPackageName, 0x00000040);
    //signatures
    jclz = env->GetObjectClass(packageInfo);
    jfieldID jfid = env->GetFieldID(jclz, "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signatures = static_cast<jobjectArray>(env->GetObjectField(packageInfo, jfid));
    //signatures[0]
    jobject signature0 = env->GetObjectArrayElement(signatures, 0);
    //toCharsString
    jclz = env->GetObjectClass(signature0);
    jmethodID methodID_hc = env->GetMethodID(jclz, "hashCode", "()I");
    int hash_code = env->CallIntMethod(signature0, methodID_hc);
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%u", hash_code);
    if (hash_code != APP_SIGNATURE) {
        exit(0);
    }
    jint sum = 0;
    return sum;
}



extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnisample_SignatureJni_signAES(JNIEnv *env, jobject thiz, jbyteArray plaintext) {
    // 获取Java类的引用
    jclass clazz = env->FindClass("com/example/jnisample/aes/AESUtil");

    // 获取单例对象的引用
    jmethodID getInstanceMethodId = env->GetStaticMethodID(clazz, "getInstance", "()Lcom/example/jnisample/aes/AESUtil;");
    jobject singleton = env->CallStaticObjectMethod(clazz, getInstanceMethodId);

    // 获取要调用的方法的ID
    jmethodID methodId = env->GetMethodID(clazz, "encrypt", "([B)Ljava/lang/String;");

    // 调用Java方法
     jstring str= static_cast<jstring>(env->CallObjectMethod(singleton, methodId, plaintext));

    return str;

}