//
// Created by Administrator on 2019/9/18.
//

#include <unistd.h>
#include <string.h>
#include "Task.h"
#include <stdlib.h>

#include <iostream>

#define  BZERO(buf,size)\
         memset(buf,0,size);

Task::Task():job(0){

    this->job = (job_t*) malloc(sizeof(job_t));
    BZERO(this->job,sizeof(job_t));
    this->job->user_data = this;
    this->job->job_function = Task::onJobPorcess;
}
void Task::onJobPorcess(job_t *job) {
    Task * qthis = (Task*)job->user_data;
    qthis->process();
    qthis->exit();
}
void Task::exit(){
    //release
    if (this->job!=0)
    {
        free(this->job);
        this->job =0;
    }
    //endout
    this->onExit();
}

int Task::onPreDo() {
   //开始执行前，获得其workerid
    if (this->job!=0)
    {
        this->wid = this->job->wid;
    }

return 0;
}

void Task::onExit() {

}

Task::~Task() {
    std::cout << "Task::~Task() 释放了xxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
}

int Task::onDo() {

    return 0;
}

int Task::onPostDo() {

    return 0;
}

int Task::process() {
     this->onPreDo();
     this->onDo();
     this->onPostDo();
    return 0;
}
int Task::getWid() {
    return this->wid;
}
void Task::onInPool(ThreadPool *threadPool) {

}

ThreadPool::ThreadPool() {
    BZERO(&this->workQueue, sizeof(workqueue_t));
    this->workQueue.userData = this;
}
void ThreadPool::init(int numWorkers,int isDetachMode) {
    this->isDetachMode = isDetachMode;
    this->workQueue.onWorkInitFn =  &workInit;
    this->workQueue.onWorkDestoryFn =  &workDestory;
    this->workQueue.onWorkThreadEnterFn =  &workThreadEnterFn;
    this->workQueue.onWorkThreadExitFn =  &workThreadExitFn;

    threadpool_init(&this->workQueue,numWorkers,isDetachMode);
}
void ThreadPool::addTask(Task *task) {
    workqueue_add_job(&this->workQueue,task->job);
    task->onInPool(this);
}


void ThreadPool::workInit(workqueue_t *wq, int wid) {
    ThreadPool* tar = (ThreadPool*) wq->userData;
    tar->onWorkInit(wq,wid);
}

void ThreadPool::workDestory(workqueue_t *wq, int wid) {
    ThreadPool* tar = (ThreadPool*) wq->userData;
    tar->onWorkDestory(wq,wid);
}

void ThreadPool::workThreadEnterFn(workqueue_t *wq, int wid) {
    ThreadPool* tar = (ThreadPool*) wq->userData;
    tar->onWorkThreadEnter(wq,wid);
}



void ThreadPool::onWorkThreadEnter(workqueue_t *wq, int wid) {

}

void ThreadPool::workThreadExitFn(workqueue_t *wq, int wid) {
    ThreadPool* tar = (ThreadPool*) wq->userData;
    tar->onWorkThreadExit(wq,wid);
}


void ThreadPool::onWorkThreadExit(workqueue_t *wq, int wid) {

}

void ThreadPool::onWorkDestory(workqueue_t *wq, int wid) {

}

void ThreadPool::onWorkInit(workqueue_t *wq, int wid) {


}

int ThreadPool::getWorkNum() {
    return this->workQueue.workNum;
}
int ThreadPool::exit() {
    threadpool_exit(&this->workQueue);
    return 0;
}

worker_t* ThreadPool::queryWorker(int wid) {
    return threadpool_queryWorker(&this->workQueue,wid);
}


ThreadPool::~ThreadPool() {
    ThreadPool::exit();
}