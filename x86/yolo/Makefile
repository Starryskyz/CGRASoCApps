

VPATH=./src/:./include/:./work

EXEC=test
OBJDIR=./obj/


#CPP=g++
NVCC=nvcc 




#arm-xilinx-linux-gnueabi-g++
#CC=arm-xilinx-linux-gnueabi-gcc
#CPP=arm-xilinx-linux-gnueabi-g++
#AR=arm-xilinx-linux-gnueabi-ar
CC=gcc
CPP=g++
AR=ar

ARFLAGS=rcs

OPTS=-Ofast
LDFLAGS= -lm -static
COMMON= -Iinclude/ -Isrc/ -Iwork/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -O3
# CFLAGS+=-march=rv64imafdcvxtheadc -mabi=lp64dv -mtune=c906 -g
# CFLAGS+=-march=rv64imafdcxtheadc -mabi=lp64d -mtune=c906 -g

#SOBJ = convolutional_layer.o
#SOBJS = $(addprefix $(OBJDIR), $(SOBJ))
#OBJ=gemm.o utils.o  convolutional_layer.o maxpool_layer.o list.o image.o activations.o im2col.o col2im.o blas.o data.o matrix.o network.o parser.o option_list.o route_layer.o upsample_layer.o box.o layer.o shortcut_layer.o tree.o yolo_layer.o detector.o mac_operation.o
OBJ= utils.o  convolutional_layer.o maxpool_layer.o list.o image.o activations.o im2col.o col2im.o blas.o data.o matrix.o network.o parser.o option_list.o route_layer.o upsample_layer.o box.o layer.o shortcut_layer.o yolo_layer.o detector.o
EXECOBJA= yolo_test_riscv.o


EXECOBJ = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile include/darknet.h

all: obj backup results $(EXEC)
#all: obj  results $(SLIB) $(ALIB) $(EXEC)


$(EXEC): $(EXECOBJ) $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

#$(ALIB): $(OBJS)
#	$(AR) $(ARFLAGS) $@ $^ 

#$(SLIB): $(OBJS)
#	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

#$(OBJDIR)mac_operation.o: mac_operation.s $(DEPS)
#	$(CC) $(COMMON) $(CFLAGS) -c $< -o $(OBJDIR)mac_operation.o

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CPP) $(COMMON) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@


$(OBJDIR)%.o: %.cu $(DEPS)
	$(NVCC) $(ARCH) $(COMMON) --compiler-options "$(CFLAGS)" -c $< -o $@

obj:
	mkdir -p obj
# backup:
# 	mkdir -p backup
# results:
# 	mkdir -p results

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(EXECOBJ) $(OBJDIR)/*

