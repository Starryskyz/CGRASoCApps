module {
  func.func @mmpart(%arg0: memref<?xf32>, %arg1: memref<?xf32>, %arg2: memref<?xf32>) attributes {llvm.linkage = #llvm.linkage<external>} {
    %a1 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "1", KernelName = "mmpart"}
    %a2 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "2", KernelName = "mmpart"}
    %a3 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "3", KernelName = "mmpart"}
    %a4 = ADORA.BlockLoad %arg0 [0] : memref<?xf32> -> memref<512xf32>  {Id = "4", KernelName = "mmpart"}
    %b1 = ADORA.BlockLoad %arg1 [0] : memref<?xf32> -> memref<2048xf32>  {Id = "5", KernelName = "mmpart"}
    %b2 = ADORA.BlockLoad %arg1 [2048] : memref<?xf32> -> memref<2048xf32>  {Id = "6", KernelName = "mmpart"}
    %b3 = ADORA.BlockLoad %arg1 [4096] : memref<?xf32> -> memref<2048xf32>  {Id = "7", KernelName = "mmpart"}
    %b4 = ADORA.BlockLoad %arg1 [6144] : memref<?xf32> -> memref<2048xf32>  {Id = "8", KernelName = "mmpart"}
    %c1 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "9", KernelName = "mmpart"}
    %c2 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "10", KernelName = "mmpart"}
    %c3 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "11", KernelName = "mmpart"}
    %c4 = ADORA.LocalMemAlloc memref<4xf32>  {Id = "12", KernelName = "mmpart"}
    
    %c512 = arith.constant 512 : index
    
    ADORA.kernel {
      affine.for %arg3 = 0 to 4 {
        %init0 = arith.constant 0.0 : f32
        %init1 = arith.constant 0.0 : f32
        %init2 = arith.constant 0.0 : f32
        %init3 = arith.constant 0.0 : f32
        
        // 使用一个循环同时计算四个点积
        %res0, %res1, %res2, %res3 = affine.for %arg4 = 0 to 512 
            iter_args(%acc0 = %init0, %acc1 = %init1, %acc2 = %init2, %acc3 = %init3) -> (f32, f32, f32, f32) {
          
          // 加载所有a数组的值
          %a1_val = affine.load %a1[%arg4] : memref<512xf32>
          %a2_val = affine.load %a2[%arg4] : memref<512xf32>
          %a3_val = affine.load %a3[%arg4] : memref<512xf32>
          %a4_val = affine.load %a4[%arg4] : memref<512xf32>
          

 
          
          // 加载所有b数组的值
          %b1_val = affine.load %b1[%arg4 + %arg3 * 512] : memref<2048xf32>
          %b2_val = affine.load %b2[%arg4 + %arg3 * 512] : memref<2048xf32>
          %b3_val = affine.load %b3[%arg4 + %arg3 * 512] : memref<2048xf32>
          %b4_val = affine.load %b4[%arg4 + %arg3 * 512] : memref<2048xf32>
          
          // 计算乘积并累加
          %mul0 = arith.mulf %a1_val, %b1_val : f32
          %new_acc0 = arith.addf %acc0, %mul0 : f32
          
          %mul1 = arith.mulf %a2_val, %b2_val : f32
          %new_acc1 = arith.addf %acc1, %mul1 : f32
          
          %mul2 = arith.mulf %a3_val, %b3_val : f32
          %new_acc2 = arith.addf %acc2, %mul2 : f32
          
          %mul3 = arith.mulf %a4_val, %b4_val : f32
          %new_acc3 = arith.addf %acc3, %mul3 : f32
          
          affine.yield %new_acc0, %new_acc1, %new_acc2, %new_acc3 : f32, f32, f32, f32
        }
        
        // 存储结果
        affine.store %res0, %c1[%arg3] : memref<4xf32>
        affine.store %res1, %c2[%arg3] : memref<4xf32>
        affine.store %res2, %c3[%arg3] : memref<4xf32>
        affine.store %res3, %c4[%arg3] : memref<4xf32>
      }
      ADORA.terminator
    } {KernelName = "mmpart"}

    ADORA.BlockStore %c1, %arg2 [0] : memref<4xf32> -> memref<?xf32>  {Id = "9", KernelName = "mmpart"}
    ADORA.BlockStore %c2, %arg2 [4] : memref<4xf32> -> memref<?xf32>  {Id = "10", KernelName = "mmpart"}
    ADORA.BlockStore %c3, %arg2 [8] : memref<4xf32> -> memref<?xf32>  {Id = "11", KernelName = "mmpart"}
    ADORA.BlockStore %c4, %arg2 [12] : memref<4xf32> -> memref<?xf32>  {Id = "12", KernelName = "mmpart"}
    return
  }
}