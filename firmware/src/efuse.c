#include <stdio.h>
#include "efuse.h"
#define VREF 3.3f
#define ADCMAX 4095.0f
#define SHUNT 0.010f
#define GAIN 20.0f
#define OC 8.0f
#define SHORT 15.0f
#define QUAL 50U
static EfuseStatus s;
static float fbuf[8];static unsigned fi,fc;
float adc_to_current(float adc){return ((adc/ADCMAX)*VREF)/(SHUNT*GAIN);}
static float filt(float x){float sum=0;fbuf[fi]=x;fi=(fi+1)%8;if(fc<8)fc++;for(unsigned i=0;i<fc;i++)sum+=fbuf[i];return sum/fc;}
void efuse_init(void){s.state=EFUSE_OFF;s.fault=DTC_NONE;s.current_a=0;s.fault_count=0;s.oc_ms=0;fi=fc=0;for(int i=0;i<8;i++)fbuf[i]=0;}
void efuse_enable(void){if(s.fault==DTC_NONE)s.state=EFUSE_ON;}
void efuse_reset(void){s.state=EFUSE_OFF;s.fault=DTC_NONE;s.oc_ms=0;}
void efuse_sample(float adc,uint32_t dt_ms,uint8_t thermal_fault){if(s.state!=EFUSE_ON)return;s.current_a=filt(adc_to_current(adc));EfuseFault f=DTC_NONE;if(thermal_fault)f=DTC_THERMAL;else if(s.current_a>=SHORT)f=DTC_SHORT;else if(s.current_a>=OC){s.oc_ms+=dt_ms;if(s.oc_ms>=QUAL)f=DTC_OVERCURRENT;}else s.oc_ms=0;if(f!=DTC_NONE){s.fault=f;s.state=EFUSE_FAULT;s.fault_count++;}}
EfuseStatus efuse_status(void){return s;}
int efuse_uart(EfuseStatus*x,char*out,unsigned n){return snprintf(out,n,"EFUSE state=%u dtc=0x%04X current=%.2fA faults=%lu\r\n",x->state,x->fault,x->current_a,(unsigned long)x->fault_count);}
void efuse_can(EfuseStatus*x,uint8_t d[8]){uint16_t ma=(uint16_t)(x->current_a*100);d[0]=x->state;d[1]=x->fault>>8;d[2]=x->fault;d[3]=ma>>8;d[4]=ma;d[5]=x->fault_count;d[6]=d[7]=0;}
