//
// Created by Administrator on 2019/9/18.
//


#include <iostream>
#include <jni.h>
#include "BaseCallback.h"
#include  "../task/JNIThreadPool.h"


std::string BaseCallback::getResultType() {

   // this->env->GetObjectClass("");
    return "";
}

 void BaseCallback::adapterJavaReponseCallback(jobject javaCallback) {
    this->resultRespd =  javaCallback;

}


//每一个 callback都有自己的接收参数处理;可以重写
void BaseCallback::setReadyReponseCallbackParam(void *param) {
    this->callbackParam = param;
}


void BaseCallback::onInPool(ThreadPool *threadPool) {
     this->pool = (JNIThreadPool*)threadPool;
}

int BaseCallback::onPreDo() {
    Task::onPreDo();
    //转换数据
    return 0;
}

int BaseCallback::onDo() {
    Task::onDo();
    if (this->state==CallBackStatus_SUCCESS)
    {
        this->onSuccess();
    }else if (this->state==CallBackStatus_FAIL){
        this->onFail();
    }

    return 0;
}


void BaseCallback::release() {
    this->onRelease();
}

int BaseCallback::onRelease() {
  //  std::cout << "BaseCallback::~onRelease()  ..." << std::endl;
    return 0;
}

int BaseCallback::onPostDo() {
    Task::onPostDo();

    return 0;
}

void BaseCallback::onExit() {
    //释放自己资源
    this->release();
    //调用父类释放
     Task::onExit();
     //最终内存释放
 //    std::cout << "BaseCallback onExit..xxxxxxxxxxxxxxxxxxxxxxxxxxxxx.." << std::endl;
     delete this;
}


void BaseCallback::setState(CallBackStatus state) {
    this->state = state;
}

jmethodID BaseCallback::getSuccessMethodId() {

    return 0;
}

jmethodID BaseCallback::getFailMethodId() {

    return 0;
}


BaseCallback::~BaseCallback() {

    // std::cout << "BaseCallback::~BaseCallback() " << std::endl;
}
