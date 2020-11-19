package com.maxzuo.jni;

/**
 * 声明native方法
 * <p>
 * Created by zfh on 2020/11/19
 */
public class StringUtils {

    /**
     * 向底层传递int型参数，并返回string型值
     */
    public static native String getRandStr(int length);
}
