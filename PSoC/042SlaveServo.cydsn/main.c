#include <project.h>

CY_PACKED typedef struct {
    uint8 pos0;
    uint8 pos1;
} CY_PACKED_ATTR i2cReg_t;

i2cReg_t i2cReg;
uint16_t m1=50; // start at 50%
uint16_t m2=50; // start at 50%

// 800us --> 1800us works well for the pulse
#define CALCPWM(v) (3*(800 + v*10))

inline void setMotorPWMs()
{  
    PWM_1_WriteCompare(CALCPWM(m1));
    PWM_2_WriteCompare(CALCPWM(m2));
}

int main()
{   
    CyGlobalIntEnable;
    CapSense_Start();
    CapSense_ScanAllWidgets();
    PWM_1_Start(); PWM_2_Start();
    setMotorPWMs();
    EZI2C_Start();
    EZI2C_EzI2CSetBuffer1(sizeof(i2cReg),sizeof(i2cReg),(uint8 *)&i2cReg);
    
    for(;;)
    {   
        if(CapSense_NOT_BUSY == CapSense_IsBusy())
        {
            CapSense_ProcessAllWidgets();
            uint32 val=CapSense_GetCentroidPos(CapSense_LINEARSLIDER0_WDGT_ID);
            if(val != 0xFFFF)
            {
                m1 = val;
                setMotorPWMs();
            }
            CapSense_ScanAllWidgets();
        }
        
        if(EZI2C_EzI2CGetActivity() & EZI2C_EZI2C_STATUS_WRITE1)
        {
            if(i2cReg.pos0 != 0xFF)
                m1 = i2cReg.pos0;
            if(i2cReg.pos1 != 0xFF)
                m2 = i2cReg.pos1;
            setMotorPWMs();
        }
    }
}