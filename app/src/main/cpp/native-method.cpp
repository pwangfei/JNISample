#include <jni.h>
#include <string>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnisample_MethodJni_accessPublicMethod(JNIEnv *env, jobject thiz) {
    //1.获取对应 class 的实体类
    jclass jclazz = env->GetObjectClass(thiz);
    //2.获取方法的 id
    jmethodID mid = env->GetMethodID(jclazz, "setSex", "(Ljava/lang/String;)V");
    //3.字符数组转换为字符串
    char c[10] = "male";
    jstring jsex = env->NewStringUTF(c);
    //4.通过该 class 调用对应的 public 方法
    env->CallVoidMethod(thiz, mid, jsex); //调用 java private 方法也是类似， Java 的访问域修饰符对 C++无效
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnisample_MethodJni_accessStaticMethod(JNIEnv *env, jobject thiz) {
    //1.获取对应 class 实体类
    jclass jclazz = env->GetObjectClass(thiz);
    //2.通过 class 类找到对应的方法 id
    jmethodID mid = env->GetStaticMethodID(jclazz, "getHeight", "()I");  //注意静态方法是调用GetStaticMethodID, 不是GetMethodID
    //3.通过 class 调用对应的静态方法
    return env->CallStaticIntMethod(jclazz, mid);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnisample_MethodJni_accessSuperMethod(JNIEnv *env, jobject thiz) {
    //1.通过反射获取 class 实体类
    jclass jclazz = env->FindClass("com/example/jnisample/SuperJni");  //注意 FindClass 不要 L和;
    if (jclazz == NULL) {
        char c[10] = "error";
        return env->NewStringUTF(c);
    }
    //通过 class 找到对应的方法 id
    jmethodID mid = env->GetMethodID(jclazz, "hello", "(Ljava/lang/String;)Ljava/lang/String;");
    char ch[10] = "cfanr";
    jstring jstr = env->NewStringUTF(ch);
    return (jstring) env->CallNonvirtualObjectMethod(thiz, jclazz, mid, jstr);

}
