make后得到test二进制程序，运行即可



main在test_yolo_riscv.c，在这里可以修改传入的图片

主要的kernel计算在convolutional_layer.c

```c
void convolutional_compute(layer_params para, float* input, float* weight, float* output)
```

