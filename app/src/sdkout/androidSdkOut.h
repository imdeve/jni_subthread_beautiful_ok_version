//
// Created by Administrator on 2019/9/20.
//

#ifndef TASKOK_ANDROIDSDKOUT_H
#define TASKOK_ANDROIDSDKOUT_H

#include "jni.h"

#include "../task/JNIThreadPool.h"
#include "../callbacks/BaseCallback.h"

#include <map>

enum AppMod{
    USER=0,
    MSG=1
};
enum AppOpt{
   ADD_FRIEND
};

class IAppCallbackSender{
public:

    virtual void sendRequestCallback(AbstractCallback * callback)=0;
    virtual void sendRequestCallbackData(uint32_t type,uint32_t opt,void*data)=0;
    virtual AbstractCallback * create(uint32_t type, uint32_t opt)=0;
};


class AppCallbackRegster{

protected:
    std::map<uint64_t ,void *> callbackMap;
public:
    virtual void put(uint32_t type,uint32_t opt,void * callback);
    virtual bool existCallback(uint32_t type,uint32_t opt);
    virtual int remove(uint32_t type,uint32_t opt);
    virtual void* getCallback(uint32_t type,uint32_t opt);
};






class AndroidSdkCli:public IAppCallbackSender{
private:
    int requestWorkerNum;
    JavaVM * jvm;
    JNIThreadPool callbacksWorkerPool;

    AppCallbackRegster javaCallbackReg;
    AppCallbackRegster cppCallbackCreatorReg;

private:
    AndroidSdkCli();
public:
    static AndroidSdkCli& getInstance();

      void initJNIEnv(JavaVM * javaVm);
      void initRequestWorkerNum(int num);
      int  start();

      void sendRequestCallbackData(uint32_t type,uint32_t opt,void*data);
      void sendRequestCallback(AbstractCallback * callback);
      AbstractCallback* create(uint32_t type,uint32_t opt);


     void putJavaCallback(uint32_t type,uint32_t opt,jobject callback);
     bool existJavaCallback(uint32_t type,uint32_t opt);
     int removeJavaCallback(uint32_t type,uint32_t opt);
     jobject getJavaCallback(uint32_t type,uint32_t opt);

    void putCppCallbackCreator(uint32_t type,uint32_t opt,CallbackCreatorFn creator);
    bool existCppCallbackCreator(uint32_t type,uint32_t opt);
    int  removeCppCallbackCreator(uint32_t type,uint32_t opt);
    CallbackCreatorFn getCppCallbackCreator(uint32_t type,uint32_t opt);
};

#endif //TASKOK_ANDROIDSDKOUT_H
