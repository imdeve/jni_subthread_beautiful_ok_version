//
// Created by Administrator on 2019/9/20.
//

#include "androidSdkOut.h"
#include "../task/JNIThreadPool.h"
#include <jni.h>
#include <TeamCallback.h>

AndroidSdkCli::AndroidSdkCli() {

}

static CallbackCreatorInfoFn callbackCreatorInfoFns[]={
    TeamCallback::getCallbackCreatorInfo,
};

static void initCppCallbacksForJava(AndroidSdkCli * sdk){
    int size = sizeof(callbackCreatorInfoFns)/sizeof(CallbackCreatorInfoFn);
    int i=0;
    for (;i<size;++i){
        CallbackCreatorInfoFn infoFn = callbackCreatorInfoFns[i];
        if (infoFn!=0)
        {
            CallbackCreatorInfo info = infoFn();
            sdk->putCppCallbackCreator(info.type,info.opt,info.fn);
        }
    }
}


AndroidSdkCli& AndroidSdkCli::getInstance() {
    static AndroidSdkCli sdkcli;
    return sdkcli;
}

void AndroidSdkCli::initJNIEnv(JavaVM *javaVm) {
    this->jvm = javaVm;
 //   initCppCallbacksForJava(this);
}

void AndroidSdkCli::initRequestWorkerNum(int num) {
    this->requestWorkerNum = num;

}

int AndroidSdkCli::start() {
    callbacksWorkerPool.init(this->jvm,this->requestWorkerNum);
    return 0;
}

AbstractCallback* AndroidSdkCli::create(uint32_t type, uint32_t opt) {
    CallbackCreatorFn  fn = getCppCallbackCreator(type,opt);
    if (fn!=0) {
        BaseCallback *callback = fn();
        return callback;
    }
    return 0;
}

void AndroidSdkCli::sendRequestCallback(AbstractCallback *callback) {
    this->callbacksWorkerPool.addTask(callback);
}

//通过数据发送java callback
void AndroidSdkCli::sendRequestCallbackData(uint32_t type, uint32_t opt, void *data) {
     CallbackCreatorFn  fn = getCppCallbackCreator(type,opt);
     if (fn!=0)
     {
         BaseCallback *callback = fn();
         jobject  javaCallback = this->getJavaCallback(type,opt);
         callback->adapterJavaReponseCallback(javaCallback);
         callback->setReadyReponseCallbackParam(data);
         this->sendRequestCallback(callback);
     }
}



jobject AndroidSdkCli::getJavaCallback(uint32_t type, uint32_t opt) {
    return (jobject)this->javaCallbackReg.getCallback(type,opt);
}

bool AndroidSdkCli::existJavaCallback(uint32_t type, uint32_t opt) {
    return this->javaCallbackReg.existCallback(type,opt);
}

void AndroidSdkCli::putJavaCallback(uint32_t type, uint32_t opt, jobject callback) {

    this->javaCallbackReg.put(type,opt,callback);
}

int AndroidSdkCli::removeJavaCallback(uint32_t type, uint32_t opt) {
    return this->removeJavaCallback(type,opt);
}


CallbackCreatorFn AndroidSdkCli::getCppCallbackCreator(uint32_t type, uint32_t opt) {
    return (CallbackCreatorFn)this->cppCallbackCreatorReg.getCallback(type,opt);
}

bool AndroidSdkCli::existCppCallbackCreator(uint32_t type, uint32_t opt) {
    return this->cppCallbackCreatorReg.existCallback(type,opt);
}

void AndroidSdkCli::putCppCallbackCreator(uint32_t type, uint32_t opt, CallbackCreatorFn creator) {
    this->cppCallbackCreatorReg.put(type,opt,(void*)&creator);
}
int AndroidSdkCli::removeCppCallbackCreator(uint32_t type, uint32_t opt) {
    return this->cppCallbackCreatorReg.remove(type,opt);
}

void* AppCallbackRegster::getCallback(uint32_t type, uint32_t opt) {
    if (this->existCallback(type,opt))
    {
        uint64_t key = type;
        key += (key << 32) + opt;
        return this->callbackMap[key];
    }
    return 0;
}


void AppCallbackRegster::put(uint32_t type, uint32_t opt, void* callback) {
    uint64_t key = type;
    key += (key << 32) + opt;
    if (!this->existCallback(type, opt)) {
        this->callbackMap[key] = callback;
    }
}


bool AppCallbackRegster::existCallback(uint32_t type, uint32_t opt) {
        uint64_t  key = type;
        key = (key<<32) + opt;
        std::map<uint64_t, void*>::iterator iter = this->callbackMap.find(key);
        return (iter != this->callbackMap.end());
}

int AppCallbackRegster::remove(uint32_t type, uint32_t opt) {
        if (this->existCallback(type,opt))
        {
            uint64_t  key = type;
            key+= (key<<32)+opt;
            std::map<uint64_t, void*>::iterator iter = this->callbackMap.find(key);
            this->callbackMap.erase(iter);
            return 0;
        }
        return -1;
}
