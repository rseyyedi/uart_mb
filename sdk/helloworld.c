
#include <stdio.h>
#include "platform.h"
#include "xil_io.h"

/* Write to memory location or register */
#define X_mWriteReg(BASE_ADDRESS, RegOffset, data) \
           *(unsigned int *)(BASE_ADDRESS + RegOffset) = ((unsigned int) data);
/* Read from memory location or register */
#define X_mReadReg(BASE_ADDRESS, RegOffset) \
           *(unsigned int *)(BASE_ADDRESS + RegOffset);

//void print(char *str);

// The BaseAddress is 0xE0001000
// 0x2C is the Channel Status Register
// Bit 2 is the REMPTY
#define XUartChanged_IsTransmitFull(BaseAddress)			 \
	((Xil_In32((BaseAddress) + 0x2C) & 	\
	 0x10) == 0x10)

void XUartChanged_SendByte(u32 BaseAddress, u8 Data)
{
		/*
		 * Wait until there is space in TX FIFO
		 */
		while (XUartChanged_IsTransmitFull(BaseAddress));

		/*
		 * Write the byte into the TX FIFO
		 */
		X_mWriteReg(BaseAddress, 0x30, Data);
}

void outbyte(char c) {
	 XUartChanged_SendByte(0xE0001000, c);
}

void ChangedPrint(char *ptr)
{
  while (*ptr) {
    outbyte (*ptr++);
  }
}


int main()
{

	ChangedPrint("Hello World from MicroBlaze\n\r");

    return 0;
}
