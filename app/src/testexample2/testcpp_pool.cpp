//
// Created by Administrator on 2019/9/21.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <Task.h>
#include <TeamCallback.h>
#include "testcpp_pool.h"


static Task* newTask(int id){
    TeamCallback *add = new  TeamCallback();
    add->id = id;
    return  add;
}

static JNIThreadPool pool;
void test_cpp_init(){
    pool.init(0,3);

}
void test_cpp_task(){
    for (int i=0;i<100;i++)
    {
        pool.addTask(newTask(i));
    }
}
