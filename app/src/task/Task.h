//
// Created by Administrator on 2019/9/18.
//

#ifndef TASKOK_TASK_H
#define TASKOK_TASK_H

#include "job.h"
class ThreadPool;

class Task {
    friend  class ThreadPool;
private:
    job_t *job;
public:
    Task();

    virtual ~Task();

protected:
    int wid;
    virtual int onPreDo();
    virtual int onDo();
    virtual int onPostDo();
    virtual void onInPool(ThreadPool *threadPool);

    virtual void onExit();

    int getWid();


private:
    void exit();
    virtual int process();
    static void onJobPorcess(job_t* job);

};

class ThreadPool{
private:
    int isDetachMode ;// 1 detach else joinable
    workqueue_t workQueue;

public:
    enum ThreadMod{
        JOINABLE=0,
        DETACH=1,
    };
    ThreadPool();
    void shutDown();
    virtual  void addTask(Task *task);
    virtual  void init(int numWorkers,int isDetachMod);

    virtual int exit();
    virtual  ~ThreadPool();

protected:
    worker_t *   queryWorker(int wid);
    virtual  void  onWorkInit(workqueue_t *wq, int wid);
    virtual  void  onWorkDestory(workqueue_t *wq, int wid);
    virtual  void  onWorkThreadEnter(workqueue_t *wq, int wid);
    virtual  void  onWorkThreadExit(workqueue_t *wq, int wid);

    int getWorkNum();

private:
    static void  workInit(workqueue_t *wq, int wid);
    static void  workDestory(workqueue_t *wq, int wid);

    static void  workThreadEnterFn(workqueue_t *wq, int wid);
    static void  workThreadExitFn(workqueue_t *wq, int wid);
};


#endif //TASKOK_TASK_H
