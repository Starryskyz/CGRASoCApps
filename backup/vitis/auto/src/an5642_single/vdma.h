
#ifndef VDMA_H_
#define VDMA_H_

#include "xaxivdma.h"


int vdma_read_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr);
int vdma_write_init(short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr);
//int vdma_write_init(XAxiVdma *Vdma, short DeviceID,short HoriSizeInput,short VertSizeInput,short Stride,unsigned int FrameStoreStartAddr);
u32 vdma_version();
int vdma_write_stop(XAxiVdma *Vdma);
int vdma_write_start(XAxiVdma *Vdma);

int gvdma_write_stop();
int gvdma_write_start();

#endif /* VDMA_H_ */
