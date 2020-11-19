package com.maxzuo.jni;

/**
 * Created by zfh on 2020/11/19
 */
public class Main {

    static {
        System.load("/Users/dazuo/workplace/java-native-interface/native/libStringUtils.jnilib");
    }

    public static void main(String[] args) {
        String randStr = StringUtils.getRandStr(4);
        System.out.println("call StringUtils.getRandStr str = " + randStr);
    }
}
