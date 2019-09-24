package com.wenwp.tong;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private JNIThread jni;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        jni = new JNIThread();
        setContentView(R.layout.activity_main);
    }

    public native String stringFromJNI();

    public void jniStartCallBack(View view) {
        jni.jniStartCallBack();
    }

    public void pushJavaCallback(View view) {
        jni.pushJavaCallback(new RequestCallback<String> () {
            @Override
            public void success(String  o) {
                System.out.println("from sdk 问候 :"+o);
            }

            @Override
            public void failed(String errorMsg) {

            }
        });
    }

    public void addCallback(View view) {
        jni.addCallback();
    }

    public void testcpool(View view) {
        jni.testcpool();
    }

    public void testCppPool(View view) {
        jni.testCppPool();

    }

    public void testInit(View view) {
        jni.testInit();

    }
}
