#include <stdio.h>
#include "efuse.h"
int main(void){char msg[128];efuse_init();efuse_enable();for(int i=0;i<10;i++)efuse_sample(2500,10,0);EfuseStatus s=efuse_status();efuse_uart(&s,msg,sizeof msg);puts(msg);return 0;}
