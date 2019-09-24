//
// Created by Administrator on 2019/9/23.
//

#ifndef POOLENV_JNIOJBECTACCESSOR_H
#define POOLENV_JNIOJBECTACCESSOR_H

#include <string>
#include <jni.h>


class JNIOjbectAccessor {
private:
    JNIEnv * env;
    std::string javaClassSign;

public:
    void setIntField(std::string fieldName,int value);
    void setDoubleField(std::string fieldName, double value);
    void setStringField(std::string fieldName, std::string value);
    void setUInt64Field(std::string fieldName,uint64_t value);
    void setInt64Field(std::string fieldName,int64_t value);
};


#endif //POOLENV_JNIOJBECTACCESSOR_H
