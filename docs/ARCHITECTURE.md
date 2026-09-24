# Architecture

```text
12 V source -> protected MOSFET -> load
                    ^
                    | gate command
MCU ADC <- shunt/current amplifier
MCU timer -> protection qualification
MCU -> UART diagnostics
MCU -> CAN diagnostics
```

The portable core separates measurement, protection policy and diagnostics. A target MCU adapter supplies the real peripheral drivers.
