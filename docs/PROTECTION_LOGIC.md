# Protection Logic

Short circuit has priority and trips immediately. Overcurrent is qualified for 50 ms to reject brief transients. Thermal fault is immediate. Any fault moves the channel to FAULT_LATCHED; reset is required before re-enabling. The project intentionally models a fail-safe software decision rather than claiming hardware-comparator response time.
