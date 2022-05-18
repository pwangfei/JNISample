#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnisample_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnisample_FieldJni_addNum(JNIEnv *env, jobject thiz) {
    //获取实例对应的 class
    jclass jclass1 = env->GetObjectClass(thiz);
    //通过class获取相应的变量的 field id
    jfieldID fid = env->GetFieldID(jclass1, "num", "I");
    //通过 field id 获取对应的值
    jint num = env->GetIntField(thiz, fid);  //注意，不是用 jclazz, 使用 jobj, static 的话， 是使用 jclass 作为参数；
    num++;
    return num;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnisample_FieldJni_accessStaticField(JNIEnv *env, jobject thiz) {
    jclass jclazz = env->GetObjectClass(thiz);
    jfieldID fid = env->GetStaticFieldID(jclazz, "name", "Ljava/lang/String;");  //注意是用GetStaticFieldID，不是GetFieldID
    jstring name = (jstring) env->GetStaticObjectField(jclazz, fid);
    const char* str = env->GetStringUTFChars(name, JNI_FALSE);
    /*
     * 不要用 == 比较字符串
     * name == (jstring) "cfanr"
     * 或用 = 直接赋值
     * name = (jstring) "navy"
     * 警告：warning: result of comparison against a string literal is unspecified (use strncmp instead) [-Wstring-compare]
     */
    char ch[30] = "hello, ";
    strcat(ch, str);
    jstring new_str = env->NewStringUTF(ch);
    // 将jstring类型的变量，设置到java
    env->SetStaticObjectField(jclazz, fid, new_str);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnisample_FieldJni_accessPrivateField(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(clazz, "age", "I");
    jint age = env->GetIntField(thiz, fid);
    if (age > 18) {
        age = 18;
    } else {
        age--;
    }
    env->SetIntField(thiz, fid, age);
}