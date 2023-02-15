#include <jni.h>
#include <string>
#include <android/log.h>
#define LOG_TAG "MyApp"

//可以使用的包名
const char *PACKAGE_NAME = "com.example.jnisample";
//APP的签名
const char *APP_SIGNATURE = "308202e4308201cc020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b30090603550406130255533020170d3230303232353130333132325a180f32303530303231373130333132325a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330820122300d06092a864886f70d01010105000382010f003082010a0282010100c83075ad7136193a4c68155552d0cee95db61d67f03abd97ab4eaa8037a2ffeb8e9dbea6ec0bbed2f6fec68a5001a4b6e882ecc25c03e20826d31a3db1bca05e8feec70f2d4028163ce1203e8452de01c216e8392f86176769ffd19be2296fe452fc27c080420002081fc7d7f441d5f60c2585e3f3567453a9797936858d98b5c80cb720984b79b7caf63f07d471547482e6c81a0f198264273f1d7bad216240b9bba61b6731802b1b58b43b915d032cd14048a5394ba1c6900eb4bcf5875885f2e639e36e1a0a416b3e7ef917c36095f8ad6dc04e302fd6473c88e6ea75b969c56892520fa8afd8b9820eacef10a54edb37c81e6e3d5f1612e4fea1f898362d0203010001300d06092a864886f70d0101050500038201010022ae9d136cf30f7c6ea27b7beb25028b7ea09777e7e5e7c209627aed18ddd4d632f98fa10b28e7d495e2e1c6636858eee028df1201b065fcd7caea1adbf15b6a238e91ec51f1389a0f0a0ab59349a9befdf7c015069a77868ea9b01f05ce160c41524ffc2396a71df32756d251d551d7dcd94c7dca5cdfbff4187b161adb262ddde76c6e1a54d7de1ebb589121ba1c5d6ff46a3bb6dcfca6fd1dacc41516f4ff53d7209061f221acd4a2e4deb61d90ca6ecbdc183f2f0602d5ec84152b60aa12a33b88553391e809a9699469f5e9379e8999f55acdf2d0d07b7d0e853d383a9c672dcf4cb7316bd473c06aaef1ecb296a3ca85d6aba86ac9a38fe0a5700a0548";
//是否可用
bool isVerify = 0;




extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnisample_ParamsJni_signatureVerify(JNIEnv *env, jobject thiz, jobject context) {
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
    jmid = env->GetMethodID(jclz, "toCharsString", "()Ljava/lang/String;");
    jobject signature_str = env->CallObjectMethod(signature0, jmid);
    //转换成char*
    const char *signature_char = env->GetStringUTFChars(static_cast<jstring>(signature_str), 0);
    //对比签名
    if (strcmp(signature_char, APP_SIGNATURE) != 0) {
        exit(0);
    }
    jint sum = 0;
    return sum;
}