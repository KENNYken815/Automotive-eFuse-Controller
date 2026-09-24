#ifndef EFUSE_H
#define EFUSE_H
#include <stdint.h>
typedef enum{EFUSE_OFF,EFUSE_ON,EFUSE_FAULT}EfuseState;
typedef enum{DTC_NONE=0,DTC_OVERCURRENT=0x1001,DTC_SHORT=0x1002,DTC_CURRENT=0x1003,DTC_THERMAL=0x1004,DTC_OUTPUT=0x1005}EfuseFault;
typedef struct{EfuseState state;EfuseFault fault;float current_a;uint32_t fault_count;uint32_t oc_ms;}EfuseStatus;
void efuse_init(void);void efuse_enable(void);void efuse_reset(void);void efuse_sample(float adc,uint32_t dt_ms,uint8_t thermal_fault);EfuseStatus efuse_status(void);float adc_to_current(float adc);int efuse_uart(EfuseStatus*s,char*out,unsigned n);void efuse_can(EfuseStatus*s,uint8_t d[8]);
#endif
