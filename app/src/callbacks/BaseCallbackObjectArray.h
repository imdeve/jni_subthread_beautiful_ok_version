//
// Created by Administrator on 2019/9/22.
//

#ifndef HELLO_BASECALLBACKOBJECTARRAY_H
#define HELLO_BASECALLBACKOBJECTARRAY_H

#include <jni.h>
#include "BaseCallback.h"


/**
 *
 * 返回类型是 基础数据类型数组  自定义类型数组 或者 数组类型 都用这个作为基类
 *如java类型
 * String[]
 * 自定义类型 XXX[]
 *
 * 基础数据类型数组
 * float[]
 * int[]
 * double []
 *
 *
 **/

class BaseCallbackObjectArray : public BaseCallback{

protected:
    virtual jobjectArray transformData( void * callbackParam);
    virtual void onSuccess();
    virtual void onFail();

    virtual jmethodID getSuccessMethodId();
    virtual jmethodID getFailMethodId();
};


#endif //HELLO_BASECALLBACKOBJECTARRAY_H
