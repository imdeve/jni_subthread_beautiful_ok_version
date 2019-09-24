//
// Created by Administrator on 2019/9/22.
//

#ifndef HELLO_BASECALLBACKINT_H
#define HELLO_BASECALLBACKINT_H

#include "BaseCallback.h"


/**
 *
 * 返回类型是基本类型 int
 **/
class BaseCallbackInt : public BaseCallback{

protected:
    virtual jint transformData( void * callbackParam);
    virtual void onSuccess();
    virtual void onFail();
    virtual jmethodID getSuccessMethodId();
    virtual jmethodID getFailMethodId();
};


#endif //HELLO_BASECALLBACKINT_H
