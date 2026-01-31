Make即可编译，但需要先去下载一个模型到该目录，比如stories42M.bin
模型下载地址 https://huggingface.co/karpathy/tinyllamas/tree/main
运行命令示例

```
./run stories42M.bin -i "One day, Tom met Bob" -s 66
```

-i 后面接起始的一句话 -s后面接随机数种子，可以保证输出结果是一样的。

完整的原工程仓库地址 https://github.com/karpathy/llama2.c.git

模型下载地址 https://huggingface.co/karpathy/tinyllamas/tree/main

主要的计算kernel是Matmul那里。
