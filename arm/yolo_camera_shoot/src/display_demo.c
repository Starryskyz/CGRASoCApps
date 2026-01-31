
/************************************************************************/
/*																		*/
/*	display_demo.c	--	ALINX AX7010 HDMI Display demonstration 						*/
/*																		*/
/************************************************************************/

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "display_demo.h"
#include <stdio.h>
#include "math.h"
#include <ctype.h>
#include <stdlib.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xiicps.h"
#include "vdma.h"
#include "i2c/PS_i2c.h"
#include "xgpio.h"
#include "sleep.h"
#include "ov5640.h"
#include "dp/dp.h"
#include "xgpiops.h"

//--------------------yolo---------------------//
#include "darknet.h"
#include "ff.h"

extern void test_detector(char *name_list, char *cfgfile, char *weightfile, char *labelbin, char *pic, float thresh, float hier_thresh, char *outfile, int fullscreen);
//--------------------yolo---------------------//



#define CAM_VDMA_ID  XPAR_AXIVDMA_0_DEVICE_ID

#define S2MM_INTID XPAR_FABRIC_AXI_VDMA_0_S2MM_INTROUT_INTR

#define KEY_INTR_ID        XPAR_XGPIOPS_0_INTR
//#define MIO_0_ID           XPAR_PSU_GPIO_0_DEVICE_ID
#define MIO_0_ID           XPAR_XGPIOPS_0_DEVICE_ID
#define INTC_DEVICE_ID	   XPAR_SCUGIC_SINGLE_DEVICE_ID

#define GPIO_INPUT         0
#define GPIO_OUTPUT		   1
#define PS_KEY_MIO		   40


//static int freezeState = 0;

/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */

XIicPs ps_i2c0;
XGpio cmos_rstn;
//XAxiVdma camera_vdma;

XScuGic XScuGicInstance;
XGpioPs GpioInstance ;

/*
 * Framebuffers for video data
 */
u8 frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME] __attribute__ ((aligned(256)));
u8 *pFrames[DISPLAY_NUM_FRAMES]; //array of pointers to the frame buffers

u8 gray[1280*720] __attribute__ ((aligned(256)));

u8 picture[1280*720*3] __attribute__ ((aligned(256)));

u8 outpic[1280*720*3] __attribute__ ((aligned(256)));




//int IntrInitFuntion(XScuGic *InstancePtr, u16 DeviceId, XGpioPs *GpioInstancePtr)
//{
//	XScuGic_Config *IntcConfig;
//	int Status ;
//	/*
//	 * Initialize the interrupt controller driver so that it is ready to
//	 * use.
//	 */
//	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
//
//	Status = XScuGic_CfgInitialize(InstancePtr, IntcConfig, IntcConfig->CpuBaseAddress) ;
//	if (Status != XST_SUCCESS)
//		return XST_FAILURE ;
//
//	/*
//	 * set priority and trigger type
//	 */
//	XScuGic_SetPriorityTriggerType(InstancePtr, KEY_INTR_ID, 0xA0, 0x3);
//	/*
//	 * Connect the device driver handler that will be called when an
//	 * interrupt for the device occurs, the handler defined above performs
//	 * the specific interrupt processing for the device.
//	 */
//	Status = XScuGic_Connect(InstancePtr, KEY_INTR_ID,
//			(Xil_ExceptionHandler)GpioHandler,
//			(void *)GpioInstancePtr) ;
//	if (Status != XST_SUCCESS)
//		return XST_FAILURE ;
//
//	/*
//	 * Enable the interrupt for the device.
//	 */
//	XScuGic_Enable(InstancePtr, KEY_INTR_ID) ;
//
//	Xil_ExceptionInit();
//
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
//			(Xil_ExceptionHandler)XScuGic_InterruptHandler,
//			InstancePtr);
//	Xil_ExceptionEnable();
//
//	return XST_SUCCESS ;
//
//}


int KeyGpioSetup(XScuGic *InstancePtr, u16 IntrID/*KEY_INTR_ID*/, XGpioPs *GpioInstancePtr)
{
	XGpioPs_Config *GpioCfg ;
	int Status ;

	GpioCfg = XGpioPs_LookupConfig(MIO_0_ID) ;
	Status = XGpioPs_CfgInitialize(GpioInstancePtr, GpioCfg, GpioCfg->BaseAddr) ;
	if (Status != XST_SUCCESS){
		return XST_FAILURE ;
	}
	/* set MIO as input */
	XGpioPs_SetDirectionPin(GpioInstancePtr, PS_KEY_MIO, 0) ;
//	XGpioPs_SetOutputEnablePin(&psGpio, PS_KEY_MIO, 0);// cursor add
	/* set interrupt type */
	XGpioPs_SetIntrTypePin(GpioInstancePtr, PS_KEY_MIO, XGPIOPS_IRQ_TYPE_EDGE_FALLING) ;
	XGpioPs_IntrEnablePin(GpioInstancePtr, PS_KEY_MIO) ;

//	Status = IntrInitFuntion(InstancePtr, MIO_0_ID, GpioInstancePtr) ;
	if (Status != XST_SUCCESS)
		return XST_FAILURE ;

	/* set priority and trigger type */


	return XST_SUCCESS ;
}


void CGRA_Func(u32* src, u8* picture, u8* yoloout, u32* dst) {
	for (int i = 0; i < 1280 * 720; i++) {
		u32 pixel = src[i];
		// Extract components (Little Endian: R is LSB)
		u8 r = pixel & 0xFF;
		u8 g = (pixel >> 8) & 0xFF;
		u8 b = (pixel >> 16) & 0xFF;
		u8 a = (pixel >> 24) & 0xFF;
		// Calculate Grayscale using luminosity formula
		// Gray = 0.299*R + 0.587*G + 0.114*B
		// Integer approximation: (R*77 + G*150 + B*29) >> 8
//		u8 graynum = (r * 77 + g * 150 + b * 29) >> 8;
		// Reconstruct pixel (Keep Alpha, set R=G=B=Gray)
//		gray[i] = graynum;
		picture[i*3]=r;
		picture[i*3+1]=g;
		picture[i*3+2]=b;
//		dst[i] = (a << 24) | (graynum << 16) | (graynum << 8) | graynum;
	}

	test_detector("1:/cona", "1:/v3t.cfg", "1:/v3t.wgt", "1:/labels.bin", picture, 0.3, 0.3, yoloout, 0);

	for (int i = 0; i < 1280 * 720; i++) {
		dst[i] = (0xFF << 24) | (yoloout[i*3+2] << 16) | (yoloout[i*3+1] << 8) | yoloout[i*3];
	}
	Xil_DCacheFlushRange((INTPTR)dst, 1280 * 720 * 4);



//	int Gx, Gy, G, val;
//	uint8_t threshold = 30;
//	int ROW=720;
//	int COL=1280;
//
//	for (int i = 1; i < ROW - 1; i++) {
//		for (int j = 1; j < COL - 1; j++) {
//			Gx = (gray[(i-1)*COL+j+1] + 2 * gray[i*COL+j+1] + gray[(i+1)*COL+j+1]) -(gray[(i-1)*COL+j-1] + 2 * gray[i*COL+j-1] + gray[(i+1)*COL+j-1]);
//			Gy = (gray[(i-1)*COL+j-1] + 2 * gray[(i-1)*COL+j] + gray[(i-1)*COL+j+1]) -(gray[(i+1)*COL+j-1] + 2 * gray[(i+1)*COL+j] + gray[(i+1)*COL+j+1]);
//			G = abs(Gx) + abs(Gy);
//			//G = (int)sqrt((double)(Gx * Gx + Gy * Gy));
//			val = (G > threshold) ? 255 : 0;
//			dst[i*COL+j] = (0xFF << 24) | (val << 16) | (val << 8) | val;
////			result[i][j] = (G > threshold) ? 255 : 0;
//		}
//	}
}

static FATFS fatfs;
static FIL fil;

int main(void)
{

	int Status;
	int i ;
	int CGRA_en = 1;
	int CGRA_flag = 0;

    FRESULT rc;
    rc = f_mount(&fatfs, "1:/", 0);
    if (rc != FR_OK){
    	return 0 ;
    }

	Xil_DCacheDisable();
	Xil_ICacheDisable();


	/*
	 * Initialize an array of pointers to the 3 frame buffers
	 */
	for (i = 0; i < DISPLAY_NUM_FRAMES; i++)
	{
		pFrames[i] = frameBuf[i];
		memset(pFrames[i], 0, DEMO_MAX_FRAME);
	}

//	CURSOR SUGGEST

//	InterruptInit(XPAR_SCUGIC_0_DEVICE_ID,&XScuGicInstance);////


	i2c_init(&ps_i2c0, XPAR_XIICPS_0_DEVICE_ID,40000);
	XGpio_Initialize(&cmos_rstn, XPAR_AXI_GPIO_0_DEVICE_ID);   //initialize GPIO IP
	XGpio_SetDataDirection(&cmos_rstn, 1, 0x0);            //set GPIO as output
	XGpio_DiscreteWrite(&cmos_rstn, 1, 0x3);
	usleep(500000);
	XGpio_DiscreteWrite(&cmos_rstn, 1, 0x0);               //set GPIO output value to 0

	usleep(500000);
	XGpio_DiscreteWrite(&cmos_rstn, 1, 0x3);
	usleep(500000);

	/*
	 * Initialize Sensor
	 */
	sensor_init(&ps_i2c0);
	/*
	 * Setup PS KEY
	 */
	KeyGpioSetup(&XScuGicInstance, KEY_INTR_ID, &GpioInstance) ;////


	/*
	 * DP dma demo
	 */
	xil_printf("DPDMA Generic Video Example Test \r\n");

//	Status = DpdmaVideoExample(&RunCfg, pFrames[0]);
	Status = DpdmaVideoExample2(&RunCfg, pFrames[0], &GpioInstance);
	if (Status != XST_SUCCESS) {
		xil_printf("DPDMA Video Example Test Failed\r\n");
		return XST_FAILURE;
	}

	sleep(1) ;

	Xil_DCacheEnable();
	Xil_ICacheEnable();

	/* Start Sensor Vdma */
//	vdma_write_init(&camera_vdma, XPAR_AXIVDMA_0_DEVICE_ID,1280 * 4,720,1280 * 4,(unsigned int)pFrames[0]);
	vdma_write_init(XPAR_AXIVDMA_0_DEVICE_ID,1280 * 4,720,1280 * 4,(unsigned int)pFrames[0]);

//
//	Xil_DCacheEnable();
//	Xil_ICacheEnable();

	xil_printf("MAIN FINISHED\r\n");

	int inuuu=0;
	while(1){
		if(freez == 1){
			if(CGRA_en){
				xil_printf("CGRA EX\r\n");
//				CGRA_Func(u32* src, u8* picture, u8* yoloout, u32* dst) {
				CGRA_Func(pFrames[0], picture, outpic, pFrames[0]);
				xil_printf("CGRA DONE\r\n");
				CGRA_en = 0;
			}
		}else{
			CGRA_en = 1;
		}
	}

	xil_printf("MAIN FINISHED\r\n");


	return 0;
}


