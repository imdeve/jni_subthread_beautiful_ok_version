package com.wenwp.tong;

import java.io.Serializable;

public interface RequestCallback<T> extends Serializable {
    /**
     * 通知产生后的回调函数
     * @param t 事件参数
     */
    public void success(T t);
    public void failed(String errorMsg);
}
