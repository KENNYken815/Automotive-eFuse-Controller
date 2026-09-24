# Automotive eFuse Controller

Low-voltage automotive-style eFuse reference project: monitor load current, drive a MOSFET power channel, detect overcurrent/short circuit, shut down safely, and report DTC-style faults over UART/CAN.

> Educational/reference implementation. Hardware-specific ADC, GPIO/PWM, UART and CAN drivers are integration hooks; no vehicle or target-board validation is claimed.

## Implemented
- 12 V-class channel model
- Shunt current sensing and filtering
- 8 A overcurrent threshold with 50 ms qualification
- 15 A short-circuit threshold with immediate shutdown
- Latched fault state and explicit reset
- UART diagnostic formatter
- CAN 8-byte diagnostic payload encoder
- Portable C implementation
- Python protection simulation and unit tests

## Reference configuration
| Parameter | Value |
|---|---:|
| Battery | 12.0 V |
| Shunt | 10 mOhm |
| Sense gain | 20 V/V |
| Overcurrent | 8 A |
| Short circuit | 15 A |
| Qualification | 50 ms |

## State flow
```text
OFF -> ON -> FAULT_LATCHED
       |          ^
       +--SHORT---+
FAULT_LATCHED -> OFF (reset)
```

## DTCs
`0x1001` Overcurrent, `0x1002` Short Circuit, `0x1003` Current-Sense Fault, `0x1004` Thermal Fault, `0x1005` Output-Stage Fault.

## Build/test
```bash
make
python3 simulation/efuse_sim.py
python3 -m unittest discover -s tests -v
```

## Hardware integration
ADC -> current-sense amplifier; GPIO/PWM -> MOSFET gate driver; timer -> protection timing; UART/CAN -> diagnostics. A production design also needs transient/reverse-battery protection, SOA/thermal analysis, EMC validation, watchdogs and HIL/compliance testing.

## Safety
This is not certified automotive safety software. Use a current-limited bench supply and dummy load for experiments; do not connect it to vehicle-critical power without engineering review and validation.
