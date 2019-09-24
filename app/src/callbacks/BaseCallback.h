//
// Created by Administrator on 2019/9/18.
//

#ifndef TASKOK_BASECALLBACK_H
#define TASKOK_BASECALLBACK_H

#include <string>
#include <jni.h>
#include "../task/Task.h"
#include "../task/JNIThreadPool.h"
#include "AbstractCallback.h"

/****
class JNIEnv;
class JNIThreadPool;
****/

/***
 * 自定义回调基类
 * 每一个自定义回调类 对应了，上层的JAVA的RequestCallback
******/

enum CallBackStatus{
    CallBackStatus_SUCCESS=0,
    CallBackStatus_FAIL =1
};


class BaseCallback :public AbstractCallback {

protected:
    JNIThreadPool *pool;
    //全局对象
    jobject  resultRespd;
    CallBackStatus state;
protected:
    virtual std::string getResultType();
    virtual int onPreDo();
    virtual void onInPool(ThreadPool *threadPool);
    virtual int onDo();
    virtual int onPostDo();
    virtual int onRelease();
    void onExit();


    virtual void onSuccess()=0;
    virtual void onFail()=0;
    virtual jmethodID getSuccessMethodId();
    virtual jmethodID getFailMethodId();


private:
    void release();
public:
    void setState(CallBackStatus state);
    void adapterJavaReponseCallback(jobject javaCallback);
    virtual  void setReadyReponseCallbackParam(void * param);
    virtual ~BaseCallback();
};

typedef  BaseCallback* (*CallbackCreatorFn)();
class CallbackCreatorInfo{
public:
    int type;
    int opt;
    CallbackCreatorFn fn;

};
typedef  CallbackCreatorInfo (*CallbackCreatorInfoFn)();


#define  CLASS_CALLBACK_CREATOR\
        private :\
        static BaseCallback* callbackCreatorFn();\
        public:\
        static CallbackCreatorInfo getCallbackCreatorInfo();

#endif //TASKOK_BASECALLBACK_H
