//
// Created by Administrator on 2019/9/22.
//

#ifndef HELLO_BASECALLBACKOBJECT_H
#define HELLO_BASECALLBACKOBJECT_H

#include "BaseCallback.h"


/**
 *
 * 返回类型是 String 或者 自定义类型  或者  java集合类型  都用这个作为基类
 *如java类型
 * String
 * 自定义类型 XXX
 * Arraylist<T>
 * Vector<T>
 *
 **/
class BaseCallbackObject: public BaseCallback {

protected:
    virtual jobject transformData( void * callbackParam);
    virtual int onPreDo();
    virtual void onSuccess();
    virtual void onFail();

    virtual jmethodID getSuccessMethodId();
    virtual jmethodID getFailMethodId();

};


#endif //HELLO_BASECALLBACKOBJECT_H
