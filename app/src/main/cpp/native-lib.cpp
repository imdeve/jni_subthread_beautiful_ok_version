#include <jni.h>
#include <string>
#include <androidSdkOut.h>
#include <TeamCallback.h>
#include "../../testexample2/testcpool.h"
#include "../../testexample2/testcpp_pool.h"
#include "WlAndroidLog.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_wenwp_tong_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_tong_JNIThread_jniStartCallBack(JNIEnv *env, jobject thiz) {
    // TODO: implement jniStartCallBack()


}


extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_tong_JNIThread_addCallback(JNIEnv *env, jobject thiz) {
    // TODO: implement addCallback()



}




extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_tong_JNIThread_testcpool(JNIEnv *env, jobject thiz) {
    // TODO: implement testcpool()
    test_c_taskpool();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_tong_JNIThread_testCppPool(JNIEnv *env, jobject thiz) {
    // TODO: implement testCppPool()
//    test_cpp();
test_cpp_task();

}

static JavaVM *jvm;
//在加载动态库时回去调用 JNI_Onload 方法，在这里可以得到 JavaVM 实例对象
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    jvm = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_tong_JNIThread_testInit(JNIEnv *env, jobject thiz) {
    // TODO: implement testInit
       //test_c_taskpool_init();
      // test_c_taskpool_init();
      ///  test_cpp_init();
     AndroidSdkCli::getInstance().initRequestWorkerNum(2);
     AndroidSdkCli::getInstance().initJNIEnv(jvm);
     AndroidSdkCli::getInstance().start();

}

static void client_job(job_t* job){
    TeamCallback* client = (TeamCallback*) job->user_data;
    if (client!= nullptr)
    {
        client->onSuccess();
        //释放
        free(client);
        free(job);
    }
}
static job_t* spoutTask(TeamCallback *task){
    job_t* job = (job_t*)malloc(sizeof(job_t));
    memset(job,0,sizeof(job_t));
    job->job_function = client_job;
    job->user_data = task;

    return job;
}

JavaVM *gJvm;
jobject greq;
jclass  gTeamCallbackClaz;
jmethodID gMethodSuccess;

extern "C"
JNIEXPORT void JNICALL
Java_com_wenwp_tong_JNIThread_pushJavaCallback(JNIEnv *env, jobject thiz, jobject req) {

   jclass  clz = env->GetObjectClass(req);
/*    jmethodID succeess =env->GetMethodID( clz,"success", "(Ljava/lang/String;)V");
    env->CallVoidMethod(req,succeess,env->NewStringUTF("hell world"));*/
    int res = env->GetJavaVM(&gJvm);
    if (res==0)
    {
        TeamCallback * task = new TeamCallback();

        greq=env->NewGlobalRef(req);
        task->adapterJavaReponseCallback(greq);
        task->setState(CallBackStatus_SUCCESS);
        task->jvm = gJvm;
        gTeamCallbackClaz = env->GetObjectClass(req);
        task->claz = gTeamCallbackClaz;

        gMethodSuccess=env->GetMethodID( task->claz,"success", "(Ljava/lang/String;)V");
        task->successMethod = gMethodSuccess;

       // task->failedMethod = env->GetMethodID( task->claz,"failed",  "(Ljava/lang/String;)V");

//        test_c_addjob(spoutTask(task));
        AndroidSdkCli::getInstance().sendRequestCallback(task);
    }
    


}