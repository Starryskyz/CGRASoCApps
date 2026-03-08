该工程实现了摄像头采集、拍照和yolov3tiny和fastest的识别，main在displaydemo.c

复现注意点：

1. bsp包要选上xliff文件库，并且打开文件字符串操作
2. heap在ld.script里面空间开大一些，目前是0x2000_0000
3. 内存泄漏问题已经修复了一部分，现在可以至少连续拍10次识别不会崩
3. 编译优化-O2