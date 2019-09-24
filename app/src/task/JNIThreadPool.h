//
// Created by Administrator on 2019/9/19.
//

#ifndef TASKOK_JNITHREADPOOL_H
#define TASKOK_JNITHREADPOOL_H

#include <jni.h>
#include <map>
#include "Task.h"

/****
#define NO_JNI 0

#ifdef NO_JNI
class JNIEnv;
class JavaVM;

class JNIEnv
{

};
class JavaVM{
public:
   inline void DetachCurrentThread(){};
   inline void AttachCurrentThread(JNIEnv** env,int a)
   {
   }

}
;
#endif
***/

class JNIThreadPool :public ThreadPool {
public:
    JNIThreadPool();
    void init(JavaVM *jvm,int numWorkers);
    ~JNIThreadPool();
protected:
    virtual  void  onWorkThreadEnter(workqueue_t *wq, int wid);
    virtual  void  onWorkThreadExit(workqueue_t *wq, int wid);
protected:
    JavaVM *jvm;
};


#endif //TASKOK_JNITHREADPOOL_H
