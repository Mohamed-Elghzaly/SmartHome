#include "mcc_generated_files/mcc.h"

uint8_t ReadData;

static void Custom_I2C_SlaveDefRdInterruptHandler() {
    ReadData = SSPBUF;
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    I2C_Open();
    I2C_SlaveSetReadIntHandler(Custom_I2C_SlaveDefRdInterruptHandler);
    while (1)
    {
        if(ReadData > 35){
            DC_Motor1_SetHigh();
            DC_Motor2_SetLow();
        }else{
            DC_Motor1_SetLow();
            DC_Motor2_SetLow();
        }
    }
}
/**
 End of File
*/