#include "job.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#define TIME_SUB_MS(tv1, tv2)  ((tv1.tv_sec - tv2.tv_sec) * 1000 + (tv1.tv_usec - tv2.tv_usec) / 1000)

static void freeWorker(worker_t *worker){
    if (worker!=0)
    {
        if (worker->workqueue!=0 && worker->workqueue->onWorkDestoryFn!=0)
        {
            worker->workqueue->onWorkDestoryFn(worker->workqueue,worker->wid);
        }
        free(worker);
        printf(" ..freeWorker..id=%d. \n",worker->wid);
    }
}

static void initWorker(worker_t *worker){
    if (worker!=0)
    {
        if (worker->workqueue!=0 && worker->workqueue->onWorkInitFn!=0)
        {
            worker->workqueue->onWorkInitFn(worker->workqueue,worker->wid);
        }
    }
}


static void workThreadEnter(worker_t *worker){
    if (worker!=0)
    {
        if (worker->workqueue!=0 && worker->workqueue->onWorkThreadEnterFn!=0)
        {
            worker->workqueue->onWorkThreadEnterFn(worker->workqueue,worker->wid);
        }
    }
}

static void workThreadExit(worker_t *worker){
    if (worker!=0)
    {
        if (worker->workqueue!=0 && worker->workqueue->onWorkThreadExitFn!=0)
        {
            worker->workqueue->onWorkThreadExitFn(worker->workqueue,worker->wid);
        }
    }
}
static int c = 0;
static void *worker_function(void *ptr) {
    worker_t *worker = (worker_t *)ptr;
    int wid =worker->wid;
    if (worker->workqueue->isDetachMode!=0)
    {
        pthread_detach(pthread_self());
    }

    workThreadEnter(worker);
    job_t *job;
    c++;
    printf("worker_function  %d.... \n",c);
    while (1) {
        pthread_mutex_lock(&worker->workqueue->jobs_mutex);
        while (worker->workqueue->waiting_jobs == NULL) {
            if (worker->terminate) break;
            pthread_cond_wait(&worker->workqueue->jobs_cond, &worker->workqueue->jobs_mutex);
        }
        if (worker->terminate) break;
        job = worker->workqueue->waiting_jobs;
        if (job != NULL) {
            LL_REMOVE(job, worker->workqueue->waiting_jobs);
        }
        pthread_mutex_unlock(&worker->workqueue->jobs_mutex);

        if (job == NULL) continue;

        /* Execute the job. */
        job->wid =wid;
        job->job_function(job);
    }
    workThreadExit(worker);

    freeWorker(worker);
    pthread_exit(NULL);
    return (void*)0;
}

static int workqueue_init(workqueue_t *workqueue, int numWorkers,int isDetachMode) {
    int i;
    worker_t *worker;
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;

    if (numWorkers < 1) numWorkers = 1;
    //memset(workqueue, 0, sizeof(*workqueue));

    workqueue->workNum = numWorkers;
    workqueue->isDetachMode = isDetachMode;

    memcpy(&workqueue->jobs_mutex, &blank_mutex, sizeof(workqueue->jobs_mutex));
    memcpy(&workqueue->jobs_cond, &blank_cond, sizeof(workqueue->jobs_cond));

    if (numWorkers>0) {
        workqueue->workDict = (struct worker **) malloc(numWorkers * sizeof(struct worker *));
        memset(workqueue->workDict, 0, numWorkers * sizeof(struct worker *));
        for (i = 0; i < numWorkers; i++) {
            if ((worker = (worker_t *) malloc(sizeof(worker_t))) == NULL) {
                perror("Failed to allocate all workers");
                threadpool_exit(workqueue);
                return 1;
            }
            memset(worker, 0, sizeof(worker_t));
            worker->wid = i;
            workqueue->workDict[i] = worker;
            worker->workqueue = workqueue;
            initWorker(worker);


            if (pthread_create(&worker->thread, NULL, worker_function, (void *) worker)) {
                perror("Failed to start all worker threads");
                //    freeWorker(worker); free in threadpool_exit
                threadpool_exit(workqueue);
                return 1;
            }
            LL_ADD(worker, worker->workqueue->workers);
        }
    }

    return 0;
}


void workqueue_shutdown(workqueue_t *workqueue) {

    worker_t *worker = NULL;
    for (worker = workqueue->workers; worker != NULL; worker = worker->next) {
        worker->terminate = 1;
    }
    pthread_mutex_lock(&workqueue->jobs_mutex);
    workqueue->workers = NULL;
    workqueue->waiting_jobs = NULL;
    pthread_cond_broadcast(&workqueue->jobs_cond);
    pthread_mutex_unlock(&workqueue->jobs_mutex);

}


void workqueue_add_job(workqueue_t *workqueue, job_t *job) {

    pthread_mutex_lock(&workqueue->jobs_mutex);

    LL_ADD(job, workqueue->waiting_jobs);

    pthread_cond_signal(&workqueue->jobs_cond);
    pthread_mutex_unlock(&workqueue->jobs_mutex);

}
int  threadpool_init(workqueue_t* workQueue,int maxThreadSize,int isDetachMode) {
    assert(workQueue!=NULL);
    if (maxThreadSize<=0)
    {
        maxThreadSize = 1;
    }
    return workqueue_init(workQueue, maxThreadSize,isDetachMode);
}

int threadpool_exit(workqueue_t *workqueue)
{
    if (workqueue!=0)
    {
        if (workqueue->onWorkqueueExitFn!=0)
        {
            workqueue->onWorkqueueExitFn(workqueue);
        }
        if (workqueue->workDict!=0 && workqueue->workNum>0)
        {

            int i=0;
            //release worker
            for  (;i<workqueue->workNum;++i){
                        if (workqueue->workDict[i]!=0)
                        {
                            freeWorker(workqueue->workDict[i]);
                            workqueue->workDict[i]=0;
                        }
            }
            free(workqueue->workDict);
            workqueue->workDict =0;
            printf("threadpool_exit .......workqueue->workDict has free it \n");
        }
    }
    return 0;
}

worker_t* threadpool_queryWorker(workqueue_t *workqueue,int wid)
{
    if (workqueue!=0 && workqueue->workNum>0)
    {
        return workqueue->workDict[wid];
    }
    return (worker_t*)0;
}