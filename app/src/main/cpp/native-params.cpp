#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnisample_ParamsJni_intMethod(JNIEnv *env, jobject thiz, jint n) {
    jint sum = 0;
    for(jint i =1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnisample_ParamsJni_stringMethod(JNIEnv *env, jobject thiz, jstring name) {
    const char *str = env->GetStringUTFChars(name, 0);

    char ch[20] = "hello, ";
    strcat(ch, str);

    env->ReleaseStringUTFChars(name, str);

    return env->NewStringUTF(ch);
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnisample_ParamsJni_intArrayMethod(JNIEnv *env, jobject thiz, jintArray arr_) {
    jint len = 0, sum = 0;
    jint *arr = env->GetIntArrayElements(arr_, 0);
    len = env->GetArrayLength(arr_);
    //由于一些版本不兼容，i不定义在for循环中
    jint i=0;
    for(; i < len; i++) {
        sum += arr[i];
    }
    env->ReleaseIntArrayElements(arr_, arr, 0);  //释放内存
    return sum;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jnisample_ParamsJni_personArrayListMethod(JNIEnv *env, jobject thiz,
                                                           jobject persons) {

    //通过参数获取 ArrayList 对象的 class
    jclass clazz = env->GetObjectClass(persons);
    if(clazz == NULL) {
        return env->NewStringUTF("not find class");
    }
    //获取 ArrayList 无参数的构造函数
    jmethodID constructorMid = env->GetMethodID(clazz, "<init>", "()V");
    if(constructorMid == NULL) {
        return env->NewStringUTF("not find constructor method");
    }
    //new一个 ArrayList 对象
    jobject arrayList = env->NewObject(clazz, constructorMid);
    //获取 ArrayList 的 add 方法的id
    jmethodID addMid = env->GetMethodID(clazz, "add", "(Ljava/lang/Object;)Z");

    //获取 Person 类的 class
    jclass personCls = env->FindClass("com/example/jnisample/model/Person");
    //获取 Person 的构造函数的 id
    jmethodID personMid = env->GetMethodID(personCls, "<init>", "(ILjava/lang/String;)V");

    jint i=0;
    for(; i < 3; i++) {
        jstring name = env->NewStringUTF("Native");
        jobject person = env->NewObject(personCls, personMid, 18 +i, name);
        //添加 person 到 ArrayList
        env->CallBooleanMethod(arrayList, addMid, person);
    }
    return arrayList;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_jnisample_ParamsJni_objectMethod(JNIEnv *env, jobject thiz, jobject person) {
    jclass clazz = env->GetObjectClass(person);  //注意是用 person，不是 jobj
//    jclass jclazz = env->FindClass("cn/cfanr/jnisample/model/Person;");  //或者通过反射获取
    if(clazz == NULL) {
        return env->NewStringUTF("cannot find class");
    }
    //获取方法 id
    jmethodID constructorMid = env->GetMethodID(clazz, "<init>", "(ILjava/lang/String;)V");
    if(constructorMid == NULL) {
        return env->NewStringUTF("not find constructor method");
    }
    jstring name = env->NewStringUTF("cfanr");

    return env->NewObject(clazz, constructorMid, 21, name);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnisample_DynamicRegisterJni_getStringFromCpp(JNIEnv *env, jobject thiz) {

}