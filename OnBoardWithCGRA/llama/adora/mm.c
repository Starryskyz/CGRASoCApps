
//===----------------------------------------------------------------------===//
//
// Copyright (c) 2025 ADORA
// All rights reserved.
//
// Automatically generated file for Vitis SDK based CGRA call function from ADORA.
// Generated on: 2026-03-03 17:11:30
//
//===----------------------------------------------------------------------===//

#include "cgra_cdma.h"
#include "cgra_axil.h"
static uint8_t _task_id = 0;
#define CGRA_BASE_ADDR 0x90000000
#define CGRA_LITE_ADDR 0x90040000

static void HostToDeviceTransfer(
  XScuGic* IntcController, XAxiCdma* AxiCdmaInstance, 
  void* src_h, void* dst_d, int64_t bytelen){
  int Status;
  Status = XAxiCdma_DataTransfer(IntcController, AxiCdmaInstance, (UINTPTR)src_h, (UINTPTR)dst_d, bytelen);
  if (Status != XST_SUCCESS) {
    xil_printf("XAxiCdma Data Transfer Failed. Status: %d\r\n", Status);
    abort();
  }
}

static void DeviceToHostTransfer(
  XScuGic* IntcController, XAxiCdma* AxiCdmaInstance, 
  void* src_d, void* dst_h, int64_t bytelen){
  int Status;
  Status = XAxiCdma_DataTransfer(IntcController, AxiCdmaInstance, (UINTPTR)src_d, (UINTPTR)dst_h, bytelen);
  if (Status != XST_SUCCESS) {
    xil_printf("XAxiCdma Data Transfer Failed. Status: %d\r\n", Status);
    abort();
  }
}


//===----------------------------------------------------------------------===//
// Configuration Data 
//===----------------------------------------------------------------------===//
/// mmpart
volatile unsigned short cin_mmpart[112][3] __attribute__((aligned(16))) = {
		{0x4000, 0x0000, 0x0008},
		{0x0090, 0x004f, 0x0009},
		{0x0000, 0x0000, 0x000a},
		{0x0000, 0x0004, 0x000b},
		{0x0000, 0x0000, 0x0020},
		{0x002c, 0x0400, 0x0031},
		{0x0000, 0x0000, 0x0032},
		{0x0010, 0x8009, 0x0033},
		{0x0010, 0x0000, 0x0034},
		{0x0060, 0x0000, 0x0041},
		{0x0080, 0x0000, 0x0081},
		{0x0000, 0x0000, 0x00a0},
		{0x4800, 0x0000, 0x00a8},
		{0x0090, 0x004f, 0x00a9},
		{0x0000, 0x0000, 0x00aa},
		{0x0000, 0x0004, 0x00ab},
		{0x4000, 0x0000, 0x00b0},
		{0x0090, 0x004f, 0x00b1},
		{0x0000, 0x0000, 0x00b2},
		{0x0000, 0x0004, 0x00b3},
		{0x0000, 0x0000, 0x00b8},
		{0x0090, 0x0040, 0x00b9},
		{0x0000, 0x0000, 0x00ba},
		{0x0000, 0x1284, 0x00bb},
		{0x0000, 0x0000, 0x00bc},
		{0x0010, 0x0000, 0x00c8},
		{0x4000, 0x0000, 0x00e8},
		{0x3000, 0x0000, 0x00f1},
		{0x020a, 0x2100, 0x00f9},
		{0x8004, 0x0000, 0x0110},
		{0x002c, 0x0100, 0x0121},
		{0x0000, 0x0000, 0x0122},
		{0x0010, 0x800a, 0x0123},
		{0x0010, 0x0000, 0x0124},
		{0x0040, 0x0000, 0x0129},
		{0x0040, 0x0000, 0x0131},
		{0x020a, 0x2300, 0x0141},
		{0x0000, 0x0080, 0x0148},
		{0x2020, 0x0000, 0x0150},
		{0x0800, 0x0000, 0x0158},
		{0x0090, 0x0040, 0x0159},
		{0x0000, 0x0000, 0x015a},
		{0x0000, 0x12c4, 0x015b},
		{0x0040, 0x0000, 0x015c},
		{0x4000, 0x0000, 0x0160},
		{0x0090, 0x004f, 0x0161},
		{0x0000, 0x0000, 0x0162},
		{0x0000, 0x0004, 0x0163},
		{0x0000, 0x0000, 0x0170},
		{0x0090, 0x0040, 0x0171},
		{0x0000, 0x0000, 0x0172},
		{0x0000, 0x12c4, 0x0173},
		{0x0000, 0x0000, 0x0174},
		{0x0030, 0x0080, 0x0180},
		{0x0000, 0x0000, 0x0198},
		{0x0001, 0x0000, 0x0199},
		{0x0804, 0x0000, 0x01a1},
		{0x002c, 0x0300, 0x01b1},
		{0x0000, 0x0000, 0x01b2},
		{0x0010, 0x8008, 0x01b3},
		{0x0010, 0x0000, 0x01b4},
		{0x0000, 0x3000, 0x01b8},
		{0x3006, 0x0000, 0x01b9},
		{0x0100, 0xb000, 0x01c0},
		{0x0000, 0x0000, 0x01c1},
		{0x000a, 0x1300, 0x01c9},
		{0x0200, 0x0002, 0x01d8},
		{0x0000, 0x0000, 0x01d9},
		{0x020a, 0x0b00, 0x01e9},
		{0x002c, 0x0300, 0x01f1},
		{0x0000, 0x0000, 0x01f2},
		{0x0010, 0x8008, 0x01f3},
		{0x0010, 0x0000, 0x01f4},
		{0x0012, 0x0000, 0x01f8},
		{0x0000, 0x0003, 0x0200},
		{0x0800, 0x0000, 0x0208},
		{0x0090, 0x0040, 0x0209},
		{0x0000, 0x0000, 0x020a},
		{0x0000, 0x1244, 0x020b},
		{0x0040, 0x0000, 0x020c},
		{0x4000, 0x0000, 0x0210},
		{0x0090, 0x0040, 0x0211},
		{0x0000, 0x0000, 0x0212},
		{0x0000, 0x0004, 0x0213},
		{0x4000, 0x0000, 0x0220},
		{0x0090, 0x0040, 0x0221},
		{0x0000, 0x0000, 0x0222},
		{0x0000, 0x0004, 0x0223},
		{0x0000, 0x0002, 0x0228},
		{0x0000, 0x0000, 0x0230},
		{0x0000, 0x8000, 0x0248},
		{0x0000, 0x0000, 0x0249},
		{0x0000, 0x0000, 0x0250},
		{0x0001, 0x0000, 0x0251},
		{0x0000, 0x3000, 0x0268},
		{0x0001, 0x0000, 0x0269},
		{0x0000, 0x3000, 0x0270},
		{0x0002, 0x0000, 0x0271},
		{0x0006, 0x0000, 0x0289},
		{0x0000, 0x0003, 0x02a8},
		{0x0000, 0x0001, 0x02b0},
		{0x4000, 0x0000, 0x02c0},
		{0x0090, 0x0040, 0x02c1},
		{0x0000, 0x0000, 0x02c2},
		{0x0000, 0x0004, 0x02c3},
		{0x0000, 0x4000, 0x0318},
		{0x0018, 0x0000, 0x0339},
		{0x0000, 0x0000, 0x0358},
		{0x4000, 0x0000, 0x0368},
		{0x0090, 0x0040, 0x0369},
		{0x0000, 0x0000, 0x036a},
		{0x0000, 0x0004, 0x036b},
	};


void mmpart(XAxiCdma* AxiCdmaInstance, XScuGic* IntcController, void* arg_0, void* arg_1, void* arg_2){
  int Status;
  int16_t *SrcPtr, *DesPtr;

  {
  /// %0 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "1", KernelName = "mmpart"}
  uint64_t dramoffset_1 = 0;
  uint64_t spadoffset_1 = 0;
  uint64_t roffset_1 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_0 + dramoffset_1 + roffset_1, 0x0 + spadoffset_1 + 0x90000000, 2048);
  spadoffset_1 = spadoffset_1 + 2048;
  
  }
  {
  /// %1 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "2", KernelName = "mmpart"}
  uint64_t dramoffset_2 = 0;
  uint64_t spadoffset_2 = 0;
  uint64_t roffset_2 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_0 + dramoffset_2 + roffset_2, 0x4000 + spadoffset_2 + 0x90000000, 2048);
  spadoffset_2 = spadoffset_2 + 2048;
  
  }
  {
  /// %2 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "3", KernelName = "mmpart"}
  uint64_t dramoffset_3 = 0;
  uint64_t spadoffset_3 = 0;
  uint64_t roffset_3 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_0 + dramoffset_3 + roffset_3, 0xc000 + spadoffset_3 + 0x90000000, 2048);
  spadoffset_3 = spadoffset_3 + 2048;
  
  }
  {
  /// %3 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "4", KernelName = "mmpart"}
  uint64_t dramoffset_4 = 0;
  uint64_t spadoffset_4 = 0;
  uint64_t roffset_4 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_0 + dramoffset_4 + roffset_4, 0x6000 + spadoffset_4 + 0x90000000, 2048);
  spadoffset_4 = spadoffset_4 + 2048;
  
  }
  {
  /// %4 = ADORA.BlockLoad %arg1 [0] : memref<?xf32> -> memref<2048xf32>  {Id = "5", KernelName = "mmpart"}
  uint64_t dramoffset_5 = 0;
  uint64_t spadoffset_5 = 0;
  uint64_t roffset_5 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_1 + dramoffset_5 + roffset_5, 0x24000 + spadoffset_5 + 0x90000000, 8192);
  spadoffset_5 = spadoffset_5 + 8192;
  
  }
  {
  /// %5 = ADORA.BlockLoad %arg1 [2048] : memref<?xf32> -> memref<2048xf32>  {Id = "6", KernelName = "mmpart"}
  uint64_t dramoffset_6 = 4 * 2048;
  uint64_t spadoffset_6 = 0;
  uint64_t roffset_6 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_1 + dramoffset_6 + roffset_6, 0x1c000 + spadoffset_6 + 0x90000000, 8192);
  spadoffset_6 = spadoffset_6 + 8192;
  
  }
  {
  /// %6 = ADORA.BlockLoad %arg1 [4096] : memref<?xf32> -> memref<2048xf32>  {Id = "7", KernelName = "mmpart"}
  uint64_t dramoffset_7 = 4 * 4096;
  uint64_t spadoffset_7 = 0;
  uint64_t roffset_7 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_1 + dramoffset_7 + roffset_7, 0x14000 + spadoffset_7 + 0x90000000, 8192);
  spadoffset_7 = spadoffset_7 + 8192;
  
  }
  {
  /// %7 = ADORA.BlockLoad %arg1 [6144] : memref<?xf32> -> memref<2048xf32>  {Id = "8", KernelName = "mmpart"}
  uint64_t dramoffset_8 = 4 * 6144;
  uint64_t spadoffset_8 = 0;
  uint64_t roffset_8 = 0;
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, arg_1 + dramoffset_8 + roffset_8, 0x18000 + spadoffset_8 + 0x90000000, 8192);
  spadoffset_8 = spadoffset_8 + 8192;
  
  }
  {
  /// mmpart
  HostToDeviceTransfer(IntcController, AxiCdmaInstance, (void*)cin_mmpart, 0x28000 + 0x90000000, 672);
  cgra_config(0x0, 112, 0x0000001f);
  cgra_exe(0x0004aedd, 0x0000001f);
  wait_cgra_all_finish();
  
  }
  {
  /// ADORA.BlockStore %8, %arg2 [0] : memref<4xf32> -> memref<?xf32>  {Id = "9", KernelName = "mmpart"}
  uint64_t dramoffset_9 = 0;
  uint64_t spadoffset_9 = 0;
  uint64_t roffset_9 = 0;
  DeviceToHostTransfer(IntcController, AxiCdmaInstance, 0x8000 + spadoffset_9 + 0x90000000, arg_2 + dramoffset_9 + roffset_9, 16);
  spadoffset_9 = spadoffset_9 + 16;
  
  }
  {
  /// ADORA.BlockStore %9, %arg2 [4] : memref<4xf32> -> memref<?xf32>  {Id = "10", KernelName = "mmpart"}
  uint64_t dramoffset_10 = 4 * 4;
  uint64_t spadoffset_10 = 0;
  uint64_t roffset_10 = 0;
  DeviceToHostTransfer(IntcController, AxiCdmaInstance, 0xe000 + spadoffset_10 + 0x90000000, arg_2 + dramoffset_10 + roffset_10, 16);
  spadoffset_10 = spadoffset_10 + 16;
  
  }
  {
  /// ADORA.BlockStore %10, %arg2 [8] : memref<4xf32> -> memref<?xf32>  {Id = "11", KernelName = "mmpart"}
  uint64_t dramoffset_11 = 4 * 8;
  uint64_t spadoffset_11 = 0;
  uint64_t roffset_11 = 0;
  DeviceToHostTransfer(IntcController, AxiCdmaInstance, 0x16000 + spadoffset_11 + 0x90000000, arg_2 + dramoffset_11 + roffset_11, 16);
  spadoffset_11 = spadoffset_11 + 16;
  
  }
  {
  /// ADORA.BlockStore %11, %arg2 [12] : memref<4xf32> -> memref<?xf32>  {Id = "12", KernelName = "mmpart"}
  uint64_t dramoffset_12 = 4 * 12;
  uint64_t spadoffset_12 = 0;
  uint64_t roffset_12 = 0;
  DeviceToHostTransfer(IntcController, AxiCdmaInstance, 0x10000 + spadoffset_12 + 0x90000000, arg_2 + dramoffset_12 + roffset_12, 16);
  spadoffset_12 = spadoffset_12 + 16;
  
  }
  _task_id++;
  return ;
}
