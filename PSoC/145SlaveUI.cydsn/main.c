#include <project.h>

CY_PACKED typedef struct  {
    uint8_t pos0;
    uint8_t pos1;
} CY_PACKED_ATTR i2cRegMap_t ;

i2cRegMap_t i2cRegMap = {50,50};
    
int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    EZI2C_Start();
    EZI2C_EzI2CSetBuffer1(sizeof(i2cRegMap),0,(uint8 *)&i2cRegMap);
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanAllWidgets();
    
    uint32_t b0,b1,b2;
    for(;;)
    {
        if(CapSense_NOT_BUSY == CapSense_IsBusy())
        {
            CapSense_ProcessAllWidgets();
            b0=CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID);
            b1=CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID);
            b2=CapSense_IsWidgetActive(CapSense_BUTTON2_WDGT_ID);
            
            if(b0) { i2cRegMap.pos1=25; led_0_Write(0); led_1_Write(1); led_2_Write(1); }
            if(b1) { i2cRegMap.pos1=50; led_0_Write(1); led_1_Write(0); led_2_Write(1); }
            if(b2) { i2cRegMap.pos1=75; led_0_Write(1); led_1_Write(1); led_2_Write(0); }
            
            i2cRegMap.pos0 = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0_WDGT_ID);
            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
        }        
    }
}
