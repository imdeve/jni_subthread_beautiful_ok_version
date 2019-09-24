//
// Created by Administrator on 2019/9/18.
//

#ifndef TASKOK_TEAMCALLBACK_H
#define TASKOK_TEAMCALLBACK_H


#include "BaseCallback.h"
#include "BaseCallbackObject.h"



/***
 *
 * 自定义回调类 每一个自定义回调类 对应了，上层的JAVA的RequestCallback
 *
 *   举例子:void getUserDetail(String account, RequestCallback<UserInfo> callback);
 * **/

class TeamCallback : public BaseCallbackObject {
public:
    int id;
    JavaVM * jvm;
    jmethodID  successMethod;
    jmethodID  failedMethod;
    jclass     claz;
    JNIEnv *  passEnv;
protected:
     jobject transformData( void * callbackParam);

     std::string getResultType();
     int onPreDo();
     void onDestroy();
     virtual  int onRelease();
     int onDo();

    CLASS_CALLBACK_CREATOR;
    ~TeamCallback();

     void onSuccess();
     void onFail();


};


#endif //TASKOK_TEAMCALLBACK_H
