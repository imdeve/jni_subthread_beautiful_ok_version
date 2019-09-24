//
// Created by Administrator on 2019/9/22.
//

#include "BaseCallbackObject.h"


jobject BaseCallbackObject::transformData(void *callbackParam) {

    return 0;
}


int BaseCallbackObject::onPreDo() {
    BaseCallback::onPostDo();


    return 0;
}

void BaseCallbackObject::onSuccess() {

}

void BaseCallbackObject::onFail() {


}

jmethodID BaseCallbackObject::getFailMethodId() {

    return 0;
}

jmethodID BaseCallbackObject::getSuccessMethodId() {

    return 0;
}
