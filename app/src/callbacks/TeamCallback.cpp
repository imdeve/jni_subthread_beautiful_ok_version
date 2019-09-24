
#include "TeamCallback.h"
#include "../main/cpp/WlAndroidLog.h"
#include <iostream>


using  namespace std;

std::string TeamCallback::getResultType() {

    return "";
}

int TeamCallback::onPreDo() {
    BaseCallback::onPreDo();

    return 0;
}
jobject TeamCallback::transformData(void *callbackParam) {

    return 0;

}


int TeamCallback::onDo() {
    BaseCallbackObject::onDo();
    //process resp-callback to java
    LOGD( "TeamCallback::onDo <<  this->id =%d<<  wid:%d" , this->id, this->getWid());

    return 0;
}

void TeamCallback::onSuccess() {
    JNIEnv * env;
    this->jvm->AttachCurrentThread(&env, 0);
    std::string msg = "hello world";
    jstring msgJs= env->NewStringUTF(msg.c_str());

    env->CallVoidMethod(resultRespd, this->successMethod, msgJs);
  //  env->DeleteLocalRef(msgJs);
    jvm->DetachCurrentThread();
    LOGD("TeamCallback::onSuccess reponseCallback");
}


void TeamCallback::onFail() {
}

static int c=0;
int TeamCallback::onRelease() {
    BaseCallback::onRelease();
    LOGD( "TeamCallback::onRelease <<  this->id =%d<<  wid:%d, jvm=%p" , this->id, this->getWid(),this->jvm);
    return 0;
}

TeamCallback::~TeamCallback() {
  //  cout <<"TeamCallback::~TeamCallback..~~~~~~~~.."<<endl;
}

CallbackCreatorInfo  TeamCallback::getCallbackCreatorInfo() {
    CallbackCreatorInfo  info ={0};
    info.fn = TeamCallback::callbackCreatorFn;
    info.type = 1;
    info.opt =2;
    return info;
}

BaseCallback * TeamCallback::callbackCreatorFn() {
    return new TeamCallback();
}