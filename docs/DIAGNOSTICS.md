# Diagnostics

UART reports state, DTC, current and fault count. CAN payload: byte 0 state, bytes 1-2 DTC, bytes 3-4 current in 0.01 A, byte 5 fault counter. This is a project-defined diagnostic payload, not an OEM protocol.
