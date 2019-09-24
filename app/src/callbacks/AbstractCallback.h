//
// Created by Administrator on 2019/9/23.
//

#ifndef POOLENV_ABSTRACTCALLBACK_H
#define POOLENV_ABSTRACTCALLBACK_H


#include "../task/Task.h"

class AbstractCallback: public Task {
protected:
    void *   callbackParam;
public:
    virtual  void setReadyReponseCallbackParam(void * param)=0;
};


#endif //POOLENV_ABSTRACTCALLBACK_H
