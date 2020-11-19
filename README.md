## 1.JNI是什么？

JNI(Java Native Interface) Java本地接口，又叫Java原生接口。它允许Java调用C/C++的代码，同时也允许在C/C++中调用Java的代码。
可以把JNI理解为一个桥梁，连接Java和底层。其实根据字面意思，JNI就是一个介于Java层和Native层的接口，而Native层就是C/C++层面。

### 2.为什么要用JNI？

1. 能够重复使用一些现成的、具有相同功能的的C/C++代码
2. 因为C/C++是偏向底层的语言，所以使用C/C++能够更加的高效，而且也使得Java能够访问操作系统中一些底层的特性。

### 3.怎么使用JNI？

1. 使用Java声明native方法

```java
// com/maxzuo/jni/StringUtils.java
public class StringUtils {

    public static native String getRandStr(int length);
}
```

2. 使用javac编译StringUtils.java成StringUtils.class

```
// 在src/main/java目录下执行
javac com/maxzuo/jni/StringUtils.java
```

3. 使用上面生成的class文件生成头文件用于编写C/C++代码的头文件：

```
// 在src/main/java目录下执行
javah -jni com.maxzuo.jni.StringUtils

// 执行完命令后，生成了com_maxzuo_jni_StringUtils.h文件
```

4. 用C语言来实现函数

```
#include "com_maxzuo_jni_StringUtils.h"

JNIEXPORT jstring JNICALL Java_com_maxzuo_jni_StringUtils_getRandStr(JNIEnv *env,jobject obj, int length){
    ...
}
```

其中：

将java的native方法转换成C函数声明的规则是这样的：Java_{package_and_classname}_{function_name}(JNI arguments)，包名中的点换成单下划线。
参数介绍：

- JNIEnv *：这是一个指向JNI运行环境的指针，后面我们会看到，我们通过这个指针访问JNI函数
- jobject：这里指代java中的this对象

5. 生成动态库文件

```
// 将生成的头文件放在native目录, 在native目录下执行如下命令：
gcc -dynamiclib -I /Library/Java/JavaVirtualMachines/jdk1.8.0_211.jdk/Contents/Home/include -I /Library/Java/JavaVirtualMachines/jdk1.8.0_211.jdk/Contents/Home/include/darwin StringUtils.c -o libStringUtils.jnilib
```

注意在不同的操作系统，能够生成的动态库文件也是不一样的，在Windows中，要生成.dll文件，在Linux中要生成.so文件，在Mac OS X中要生成.jnilib文件。
同时定义生成的库文件名的时候也要遵循：lib+文件名＋扩展名的原则。本例中我们在Mac OS X中所以我们定义生成的库文件为：libStringUtils.jnilib。

6. 使用生成的动态库文件

```java
// com/maxzuo/jni/Main.java
public class Main {

    static {
        System.load("/xxx/java-native-interface/native/libStringUtils.jnilib");
    }

    public static void main(String[] args) {
        String randStr = StringUtils.getRandStr(4);
        System.out.println("call StringUtils.getRandStr str = " + randStr);
    }
}
```

其中，运行时加载本地库, JDK提供了两个方法：

- System.loadLibrary(String libname) 加载由libname参数指定的系统，参数为库文件名，不包含库文件的扩展名；会自动加载依赖。
譬如libA.so和libB.so有依赖关系，虚拟机在载入libA.so的时候会先去java.library.path下查找libB.so。

- System.load(String filename)：参数为库文件的绝对路径且带文件后缀；不会自动加载依赖。同等场景下，不会自动加载依赖。

补充：

1）通过JVM启动参数指定：-Djava.library.path=/path
    
2）通过设置环境变量指定：export LD_LIBRARY_PATH=/path
