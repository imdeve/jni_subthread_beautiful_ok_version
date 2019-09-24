#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_freedom_MyJni_displayParms(JNIEnv *env, jobject instance, jstring showText_,
                                            jint i, jboolean bl) {
    const char *showText = env->GetStringUTFChars(showText_, 0);
    printf("showText:%s \n",showText);
    printf("i value:%d\n",(int)i);
    printf("boolean:%s" ,bl==JNI_TRUE?"true":"false");
    env->ReleaseStringUTFChars(showText_, showText);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_freedom_MyJni_add(JNIEnv *env, jobject instance, jint a, jint b) {
    int   res =(int) a+ (int)b;
    return (jint)res;
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_freedom_MyJni_setArray(JNIEnv *env, jobject instance, jbooleanArray blList_) {
    jboolean *blList = env->GetBooleanArrayElements(blList_, NULL);

    jsize  len = env->GetArrayLength(blList_);
    // change even array elements
    for(int i = 0; i < len; i += 2)
    {
        blList[i] = JNI_FALSE;  //JNI_FALSE是在jni.h中定义的
        printf("boolean = %s\n", (blList[i] == JNI_TRUE ? "true" : "false"));
    }

    env->ReleaseBooleanArrayElements(blList_, blList, 0);
}


extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_freedom_MyJni_getStringArray(JNIEnv *env, jobject instance) {
    const char * wordArr[]={"hello","world","haha","yes","no"};
    jsize  size = 5;
    jclass  strClaz= env->FindClass("java/lang/String");
    jobjectArray strs = env->NewObjectArray(size,strClaz,0);

    for (jsize i=0;i<size;i++)
    {
        env->SetObjectArrayElement(strs,i,env->NewStringUTF(wordArr[i]));
    }
    return strs;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_freedom_MyJni_getStruct(JNIEnv *env, jobject instance) {
    jclass  DiskInfoClaz = env->FindClass("com/example/freedom/DiskInfo");
    //jfieldID nameIdTag = env->GetFieldID(DiskInfoClaz,"name","java/lang/String");
    //jfieldID seriaIdTag= env->GetFieldID(DiskInfoClaz,"serial","I");

    std::string name="disk:F";
    jint serial = 100;
//    (Ljava/lang/String;I)V

/****
 * 构造函数不带参数
 *  jmethodID  diskInfoContructodMethod= env->GetMethodID(DiskInfoClaz,"<init>","()V");
    jobject  diskInfoInstance = env->NewObject(DiskInfoClaz,diskInfoContructodMethod);
 */

// 带参的构造函数调用
    jmethodID  diskInfoContructodMethod= env->GetMethodID(DiskInfoClaz,"<init>","(Ljava/lang/String;I)V");
    std::string msg = "我的磁盘名字是 D:";
    jstring diskName = env->NewStringUTF(msg.c_str());
    jobject  diskInfoInstance = env->NewObject(DiskInfoClaz,diskInfoContructodMethod,diskName,serial);// 带参的构造函数调用

    return diskInfoInstance;
}
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_freedom_MyJni_getStructArray(JNIEnv *env, jobject instance) {

    //申明一个object数组
    jobjectArray args = 0;
    //数组大小
    jsize        len = 5;

    //获取Java中的实例类
    jclass DiskInfoClaz = (env)->FindClass("com/example/freedom/DiskInfo");

    //新建object数组
    args = (env)->NewObjectArray(len, DiskInfoClaz, 0);
    /* 下面为获取到Java中对应的实例类中的变量*/


    //获取类中每一个变量的定义
    //名字
    // jfieldID nameIdTag = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
    // jfieldID seriaIdTag = (env)->GetFieldID(DiskInfoClaz, "serial", "I");
    //给每一个实例的变量付值
    std::string msg = "我的磁盘名字是 D:";
    jstring diskName = env->NewStringUTF(msg.c_str());

    jmethodID constrocMID = env->GetMethodID(DiskInfoClaz,"<init>","(Ljava/lang/String;I)V");

    //给每一个实例的变量付值，并且将实例作为一个object，添加到objcet数组中
    for(jint  i = 0; i < len; i++)
    {
        //获得得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V

//CALL 构造函数
        jobject diskInstance = env->NewObject(DiskInfoClaz,constrocMID,diskName,i);  //构造一个对象，调用该类的构造函数，并且传递参数

        //detail设置
        // (env)->SetObjectField(_obj,nameIdTag,(env)->NewStringUTF("my name is D:"));
        //  (env)->SetIntField(diskInstance, seriaIdTag, 10);
        //添加到objcet数组中
        (env)->SetObjectArrayElement(args, i, diskInstance);
    }
    //返回object数组
    return args;


}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_freedom_MyJni_getStructList(JNIEnv *env, jobject instance) {
    jclass DiskInfoClaz = (env)->FindClass("com/example/freedom/DiskInfo");
    jclass list_cls = env->FindClass("Ljava/util/ArrayList;");
    jmethodID constrocMID = env->GetMethodID(DiskInfoClaz,"<init>","()V");
    //  jfieldID str = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
    // jfieldID ival = (env)->GetFieldID(DiskInfoClaz, "serial", "I");
    jfieldID nameIdTag = (env)->GetFieldID(DiskInfoClaz, "name", "Ljava/lang/String;");
    //序列号
    jfieldID seriaIdTag = (env)->GetFieldID(DiskInfoClaz, "serial", "I");

    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","(Ljava/lang/String;I)V"); //获得得构造函数Id
    std::string pathName = "我的磁盘名字是 D:";
    jstring pathNameValue = env->NewStringUTF(pathName.c_str());
    jobject list_obj = env->NewObject(list_cls , list_costruct); //创建一个Arraylist集合对象
    // public boolean add(E e) 泛型 本身就是底层是object传递，上层的语言接入层的语法糖
    jmethodID list_add  = env->GetMethodID(list_cls,"add","(Ljava/lang/Object;)Z");

    jsize size =5;
    jint i=0;
    for (i=0;i<size;i++)
    {
        jobject diskInstance = env->NewObject(DiskInfoClaz,constrocMID,pathNameValue,i);  //构造一个对象，调用该类的构造函数，并且传递参数
        //  env->SetIntField(diskInstance,seriaIdTag,100);
        //  env->SetObjectField(diskInstance,nameIdTag,(env)->NewStringUTF("my name is F:"));
        // env->CallBooleanMethod(list_obj , list_add , diskInstance); //执行Arraylist类实

    }
    return list_obj;
}