
"""
Copyright (c) 2025 ADORA
All rights reserved.
Automatically generated file for pytest/cocotb based CGRA call function from ADORA.
Generated on: 2026-03-03 12:29:28

"""
from test_runif import DeviceData, DeviceConfig, DeviceStream, DeviceRuntime
from typing import List
from numpy import ndarray
import numpy as np

async def aux_stream(
    stream: DeviceStream, config: List[DeviceConfig], 
    iptrs: List[DeviceData], idata: List, 
    optrs: List[DeviceData], odata: List, olen: List):
    """
    Execute a device stream workflow.

    Parameters
    ----------
    stream : DeviceStream
        The device stream instance to operate on.
    config : List[DeviceConfig]
        Configuration objects to apply before execution.
    iptrs : List[DeviceData]
        Device pointers for input buffers.
    idata : List
        Host-side input data corresponding to `iptrs`.
    optrs : List[DeviceData]
        Device pointers for output buffers.
    odata : List
        Host-side output data containers corresponding to `optrs`.
    olen : List[int]
        Expected output lengths for each output buffer.
    """
    # ------------------------------
    # 1. Apply stream configuration
    # ------------------------------
    await stream.apply(config)
    await stream.config(config_id=0)
    # ------------------------------
    # 2. Host -> Device transfer
    # ------------------------------
    for i in range(len(iptrs)):
        await stream.memcpyHostToDevice(d_data=iptrs[i], h_data=idata[i], size=len(idata[i]))
    # ------------------------------
    # 3. Execute on device
    # ------------------------------
    await stream.execution_start()
    # await stream.execution_finish()
    # ------------------------------
    # 4. Device → Host transfer
    # ------------------------------
    for i in range(len(optrs)):
        await stream.memcpyDeviceToHost(d_data=optrs[i], h_data=odata[i], size=olen[i])

    await stream.release()
    return

def DeviceData_Pong(ptr : DeviceData) -> DeviceData:
    new_ptr = DeviceData(ptr.address+ptr.size, ptr.size)
    return new_ptr
  
async def aux_stream_pingpong(
    stream: DeviceStream, 
    # config: List[DeviceConfig], 
    config_id:int,
    iptrs: List[DeviceData], idata: List[ndarray], 
    optrs: List[DeviceData], odata: List, olen: List, 
    pingpong: bool):
    """
    Execute a device stream workflow.

    Parameters
    ----------
    stream : DeviceStream
        The device stream instance to operate on.
    config : List[DeviceConfig]
        Configuration objects to apply before execution.
    iptrs : List[DeviceData]
        Device pointers for input buffers.
    idata : List
        Host-side input data corresponding to `iptrs`.
    optrs : List[DeviceData]
        Device pointers for output buffers.
    odata : List
        Host-side output data containers corresponding to `optrs`.
    olen : List[int]
        Expected output lengths for each output buffer.
    pingpong : bool
        Indicates the pingpong phase(ping-phase or pong-phase)
    """
    # ------------------------------
    # 1. Apply stream configuration
    # ------------------------------     
    await stream.config(config_id=config_id)
        # ------------------------------
    # 2. Host -> Device transfer
    # ------------------------------
    for i in range(len(iptrs)):
        if(pingpong == 0):
            await stream.memcpyHostToDevice(d_data=iptrs[i], h_data=idata[i], size=len(idata[i]), depend_type=2)
        else:
            await stream.memcpyHostToDevice(DeviceData_Pong(iptrs[i]), h_data=idata[i], size=len(idata[i]), depend_type=2)

    # ------------------------------
    # 3. Execute on device
    # ------------------------------
    await stream.execution_start()
    await stream.execution_finish()
    # ------------------------------
    # 4. Device → Host transfer
    # ------------------------------
    for i in range(len(optrs)):
        if(pingpong == 0):
            await stream.memcpyDeviceToHost(d_data=optrs[i], h_data=odata[i], size=olen[i])
        else :
            await stream.memcpyDeviceToHost(DeviceData_Pong(optrs[i]), h_data=odata[i], size=olen[i])
    
    # await stream.synchronize()

    # await stream.release()
    return

async def aux_stream_pingpong_init(
    stream: DeviceStream, config: List[DeviceConfig]
    ):
    """
    Apply stream configuration
    """
    cfg_copy = list(config)
    await stream.apply(cfg_copy)  
    await stream.config(config_id=0)
    
    # await stream.release()
    return

## ===----------------------------------------------------------------------===//
## Configuration Data 
## ===----------------------------------------------------------------------===//
""" kernel: mmpart,  cfgNum: 103"""
cfgbit_mmpart = [
		0x0800, 0x0000, 0x0008,
		0x0090, 0x0040, 0x0009,
		0x0000, 0x0000, 0x000a,
		0x0000, 0x12c4, 0x000b,
		0x0040, 0x0000, 0x000c,
		0x4000, 0x0000, 0x0010,
		0x0090, 0x0040, 0x0011,
		0x0000, 0x0000, 0x0012,
		0x0000, 0x0004, 0x0013,
		0x0003, 0x0000, 0x0020,
		0x0200, 0x0000, 0x0038,
		0x0000, 0x0000, 0x0040,
		0x0819, 0x0000, 0x0041,
		0x0000, 0x0000, 0x0060,
		0x0006, 0x0000, 0x0061,
		0x200a, 0x1100, 0x0069,
		0x002c, 0x0300, 0x0071,
		0x0000, 0x0000, 0x0072,
		0x0010, 0x8009, 0x0073,
		0x0010, 0x0000, 0x0074,
		0x0000, 0x0000, 0x0080,
		0x0006, 0x0000, 0x0081,
		0x0000, 0x0000, 0x00a0,
		0x4800, 0x0000, 0x00a8,
		0x0090, 0x004f, 0x00a9,
		0x0000, 0x0000, 0x00aa,
		0x0000, 0x0004, 0x00ab,
		0x4000, 0x0000, 0x00b0,
		0x0090, 0x004f, 0x00b1,
		0x0000, 0x0000, 0x00b2,
		0x0000, 0x0004, 0x00b3,
		0x4000, 0x0000, 0x00b8,
		0x0090, 0x004f, 0x00b9,
		0x0000, 0x0000, 0x00ba,
		0x0000, 0x0004, 0x00bb,
		0x4800, 0x0000, 0x00c0,
		0x0090, 0x0040, 0x00c1,
		0x0000, 0x0000, 0x00c2,
		0x0000, 0x0004, 0x00c3,
		0x0000, 0x0000, 0x00c8,
		0x0000, 0x0000, 0x00d0,
		0x000a, 0x0a00, 0x00d9,
		0x0000, 0x0000, 0x00f0,
		0x002c, 0x0100, 0x0101,
		0x0000, 0x0000, 0x0102,
		0x0010, 0x8006, 0x0103,
		0x0010, 0x0000, 0x0104,
		0x0080, 0x0000, 0x0131,
		0x0000, 0x0080, 0x0148,
		0x0000, 0x0100, 0x0150,
		0x4000, 0x0000, 0x0158,
		0x0090, 0x004f, 0x0159,
		0x0000, 0x0000, 0x015a,
		0x0000, 0x0004, 0x015b,
		0x0000, 0x0000, 0x0168,
		0x0090, 0x0040, 0x0169,
		0x0000, 0x0000, 0x016a,
		0x0000, 0x1204, 0x016b,
		0x0000, 0x0000, 0x016c,
		0x0030, 0x0000, 0x0178,
		0x0000, 0x0000, 0x0199,
		0x0040, 0x0000, 0x01d9,
		0x0040, 0x0000, 0x01e1,
		0x0000, 0x0100, 0x01f8,
		0x0000, 0x0100, 0x0200,
		0x4000, 0x0000, 0x0220,
		0x0090, 0x0040, 0x0221,
		0x0000, 0x0000, 0x0222,
		0x0000, 0x0004, 0x0223,
		0x0000, 0x0000, 0x0230,
		0x0800, 0x0000, 0x0251,
		0x0000, 0x0000, 0x0270,
		0x100a, 0x1300, 0x0279,
		0x002c, 0x0300, 0x0281,
		0x0000, 0x0000, 0x0282,
		0x0010, 0x8008, 0x0283,
		0x0010, 0x0000, 0x0284,
		0x0200, 0x0000, 0x0288,
		0x0100, 0x0000, 0x0290,
		0x0000, 0x0000, 0x0291,
		0x100a, 0x2300, 0x0299,
		0x002c, 0x0100, 0x02a1,
		0x0000, 0x0000, 0x02a2,
		0x0010, 0x8008, 0x02a3,
		0x0010, 0x0000, 0x02a4,
		0x0020, 0x0000, 0x02a8,
		0x2002, 0x0000, 0x02b0,
		0x0000, 0x0000, 0x02b8,
		0x0090, 0x0040, 0x02b9,
		0x0000, 0x0000, 0x02ba,
		0x0000, 0x1244, 0x02bb,
		0x0040, 0x0000, 0x02bc,
		0x0000, 0x0003, 0x0358,
		0x0000, 0x0001, 0x0360,
		0x0800, 0x0000, 0x0368,
		0x0090, 0x0040, 0x0369,
		0x0000, 0x0000, 0x036a,
		0x0000, 0x1244, 0x036b,
		0x0000, 0x0000, 0x036c,
		0x4000, 0x0000, 0x0370,
		0x0090, 0x0040, 0x0371,
		0x0000, 0x0000, 0x0372,
		0x0000, 0x0004, 0x0373,
	]


async def mmpart(runtime: DeviceRuntime, arg_0: ndarray, arg_1: ndarray, arg_2: ndarray):
    # runtime.log.info("[ADORA] Starting CGRA call (mmpart)")
    iptrs, idata = [],[]
    optrs, odata, olen = [],[],[]
    configs, data_ptr = [],[]
    stream = runtime.create_stream()
    
    ## %0 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "1", KernelName = "mmpart"}
    idata.append(arg_0[0:0+512])
    iptrs.append(DeviceData(0x8000, 2048))

    
    ## %1 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "2", KernelName = "mmpart"}
    idata.append(arg_0[0:0+512])
    iptrs.append(DeviceData(0xc000, 2048))

    
    ## %2 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "3", KernelName = "mmpart"}
    idata.append(arg_0[0:0+512])
    iptrs.append(DeviceData(0x4000, 2048))

    
    ## %3 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "4", KernelName = "mmpart"}
    idata.append(arg_0[0:0+512])
    iptrs.append(DeviceData(0x6000, 2048))

    
    ## %4 = ADORA.BlockLoad %arg1 [0] : memref<?xf32> -> memref<2048xf32>  {Id = "5", KernelName = "mmpart"}
    idata.append(arg_1[0:0+2048])
    iptrs.append(DeviceData(0xa000, 8192))

    
    ## %5 = ADORA.BlockLoad %arg1 [2048] : memref<?xf32> -> memref<2048xf32>  {Id = "6", KernelName = "mmpart"}
    idata.append(arg_1[2048:2048+2048])
    iptrs.append(DeviceData(0x18000, 8192))

    
    ## %6 = ADORA.BlockLoad %arg1 [4096] : memref<?xf32> -> memref<2048xf32>  {Id = "7", KernelName = "mmpart"}
    idata.append(arg_1[4096:4096+2048])
    iptrs.append(DeviceData(0x24000, 8192))

    
    ## %7 = ADORA.BlockLoad %arg1 [6144] : memref<?xf32> -> memref<2048xf32>  {Id = "8", KernelName = "mmpart"}
    idata.append(arg_1[6144:6144+2048])
    iptrs.append(DeviceData(0x0, 8192))

    
    ## %8 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "9", KernelName = "mmpart"}
    data_ptr.append(DeviceData(0x10000, 16))
    
    ## %9 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "10", KernelName = "mmpart"}
    data_ptr.append(DeviceData(0x26000, 16))
    
    ## %10 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "11", KernelName = "mmpart"}
    data_ptr.append(DeviceData(0x1c000, 16))
    
    ## %11 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "12", KernelName = "mmpart"}
    data_ptr.append(DeviceData(0x2000, 16))
    
    ### mmpart
    data_ptr.append(iptrs)
    config_mmpart= DeviceConfig(
    	config_values=cfgbit_mmpart,
    	iob_en=[0x7f,0x61,0x0c],
    	tile_en=[0x1f],
    	data_ptr=data_ptr
    )
    configs.append(config_mmpart)
    

    
    ## ADORA.BlockStore %8, %arg2 [0] : memref<4xf32> -> memref<?xf32>  {Id = "9", KernelName = "mmpart"}
    odata.append(arg_2[0:0+4])
    optrs.append(DeviceData(0x10000, 16))
    olen.append(16)

    
    ## ADORA.BlockStore %9, %arg2 [4] : memref<4xf32> -> memref<?xf32>  {Id = "10", KernelName = "mmpart"}
    odata.append(arg_2[4:4+4])
    optrs.append(DeviceData(0x26000, 16))
    olen.append(16)

    
    ## ADORA.BlockStore %10, %arg2 [8] : memref<4xf32> -> memref<?xf32>  {Id = "11", KernelName = "mmpart"}
    odata.append(arg_2[8:8+4])
    optrs.append(DeviceData(0x1c000, 16))
    olen.append(16)

    
    ## ADORA.BlockStore %11, %arg2 [12] : memref<4xf32> -> memref<?xf32>  {Id = "12", KernelName = "mmpart"}
    odata.append(arg_2[12:12+4])
    optrs.append(DeviceData(0x2000, 16))
    olen.append(16)

    await aux_stream(
    	stream=stream, config=configs,
    	iptrs=iptrs, idata=idata,
    	optrs=optrs, odata=odata, olen =olen,
    )

    configs.clear()
    iptrs.clear(), idata.clear()
    optrs.clear(), odata.clear(), olen.clear()


    await stream.synchronize()
