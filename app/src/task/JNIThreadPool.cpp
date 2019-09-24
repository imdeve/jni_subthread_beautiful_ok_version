//
// Created by Administrator on 2019/9/19.
//

#include "JNIThreadPool.h"
#include "../main/cpp/WlAndroidLog.h"
#include <stdlib.h>
#include <pthread.h>
JNIThreadPool::JNIThreadPool() {

}

void JNIThreadPool::init(JavaVM* jvm,int numWorkers) {
     this->jvm = jvm;
     ThreadPool::init(numWorkers,ThreadPool::DETACH);
}

void JNIThreadPool::onWorkThreadEnter(workqueue_t *wq, int wid) {
    ThreadPool::onWorkThreadEnter(wq,wid);

     LOGD("JNIThreadPool WORKER =%d is started",wid);
/*
    JNIEnv *env =0;
    if (jvm!=0)
    {
        jvm->AttachCurrentThread(&env, 0);
        worker_t *worker= this->queryWorker(wid);
        worker->userData = env;
    }*/
}

void JNIThreadPool::onWorkThreadExit(workqueue_t *wq, int wid) {
    ThreadPool::onWorkThreadExit(wq,wid);
    worker_t *worker= this->queryWorker(wid);
    worker->userData = 0;
/*    if (jvm!=0)
    {
        jvm->DetachCurrentThread();
    }*/
}



JNIThreadPool::~JNIThreadPool() {

}