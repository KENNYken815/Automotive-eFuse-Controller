class EFuse:
    def __init__(self): self.state='OFF';self.fault='NONE';self.oc_ms=0;self.faults=0
    def enable(self):
        if self.fault=='NONE': self.state='ON'
    def reset(self): self.state='OFF';self.fault='NONE';self.oc_ms=0
    def sample(self,current,dt=10,thermal=False):
        if self.state!='ON': return
        if thermal:self.fault='THERMAL'
        elif current>=15:self.fault='SHORT_CIRCUIT'
        elif current>=8:
            self.oc_ms+=dt
            if self.oc_ms>=50:self.fault='OVERCURRENT'
        else:self.oc_ms=0
        if self.fault!='NONE':self.state='FAULT_LATCHED';self.faults+=1
if __name__=='__main__':
    e=EFuse();e.enable();[e.sample(9) for _ in range(5)];print(e.state,e.fault)
    e.reset();e.enable();e.sample(20);print(e.state,e.fault)
