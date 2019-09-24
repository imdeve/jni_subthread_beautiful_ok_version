//
// Created by Administrator on 2019/9/21.
//

#include <job.h>
#include <string.h>
#include "testcpool.h"
#include "stdlib.h"
#include <atomic>
#include "../main/cpp/WlAndroidLog.h"

static bool  flag =true;

#define BZERO(buf,size) do {\
        if (buf!=0) \
        {   \
            memset(buf,0,size);\
        }\
}while(0);

typedef struct {
    int a;
    int b;
}client_t;

/*static int  user_addInc(int *a,int delta){
    int ret =0;
    //xaddl reg,mem
    __asm__ __volatile__(
    "xadd %2,%1;"
    :"=a"(ret)
    :"m"(*a),"0"(delta)
    :"memory","cc"
    );
    return ret;
}*/

int total_jobs_count;
void client_job(job_t* job){
    client_t* client = (client_t*) job->user_data;
    if (client!= nullptr)
    {

        int res = (client->a)+(client->b);
        total_jobs_count++;
        LOGD("client_job result：%d now_total=%d", res,total_jobs_count);
        //释放
        free(client);
        free(job);
    }
}
client_t* spoutClentData(){
    client_t *rClient = (client_t*)malloc(sizeof(client_t));
    BZERO(rClient,sizeof(client_t));
    rClient->b=10;
    rClient->a=20;
    return rClient;
}

job_t* spoutTask(){
    job_t* job = (job_t*)malloc(sizeof(job_t));
    BZERO(job,sizeof(job_t));
    job->job_function = client_job;
    job->user_data = spoutClentData();

    return job;
}

static void onWorkInitFn(workqueue_t* wkqueue, int wid){

    // printf("worker   ptr init :%p wid=%d \n",wkqueue->workDict[wid],wid);

    LOGD("main onWorkInitFn ：%d", wid);
}

static void onWorkExitFn(workqueue_t* wkqueue, int wid){
    LOGD("main onWorkInitFn ：%d", wid);
    //printf("worker ptr exit :%p wid=%d \n",wkqueue->workDict[wid],wid);
}
workqueue_t wq;
void  test_c_taskpool_init(){
    BZERO(&wq, sizeof(workqueue_t));
    wq.onWorkInitFn =  &onWorkInitFn ;
    wq.onWorkDestoryFn =  &onWorkExitFn;
    threadpool_init(&wq,2,true);
}

void  test_c_addjob(job_t *job)
{
    workqueue_add_job(&wq,job);
}

void  test_c_taskpool() {
    int i=0;
    for(;i<100;i++){
        workqueue_add_job(&wq,spoutTask());
    }

}






