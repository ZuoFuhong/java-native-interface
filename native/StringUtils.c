#include "com_maxzuo_jni_StringUtils.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char * getRandStr(int length) {
    srand((unsigned)time(NULL)); // NOLINT(cert-msc51-cpp)
    char str[7] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char *strTemp = malloc(length + 1);
    for (int i = 0; i < length; i++) {
        int index = rand() % 6; // NOLINT(cert-msc50-cpp)
        strTemp[i] = str[index];
    }
    return strTemp;
}

// C函数是用下划线(_)作为命名分隔（对应java的包名）
JNIEXPORT jstring JNICALL Java_com_maxzuo_jni_StringUtils_getRandStr(JNIEnv *env,jobject obj, int length){
    char *str = getRandStr(length);
    printf("StringUtils_getRandStr, length = %d, str = %s", length, str);
    return (*env)->NewStringUTF(env, str);
}
