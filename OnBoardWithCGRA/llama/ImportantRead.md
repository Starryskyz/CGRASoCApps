LLM CGRA demo vitis手工修改的部分包括：

1. Ld script里面的heap 改为0x2000_0000
2. C++ build setting linker library 填写m
3. 编译优化-O2
4. 添加bsp的xilff文件读写库