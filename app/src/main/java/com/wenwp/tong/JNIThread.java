package com.wenwp.tong;

public class JNIThread {

    public native  void jniStartCallBack();

    public native void pushJavaCallback(RequestCallback req);

    public native void addCallback() ;

    public native void testcpool();

    public native void testCppPool();

    public native void testInit() ;
}
