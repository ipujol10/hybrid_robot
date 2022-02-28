#!/usr/bin/env python3

class SpringCalculation:
    wheel_mass = 0.3
    base_mass = 0.4
    extension_mass = 0.4
    motor_base_mass = 0.4
    base_length = 0.215
    extension_length = 0.2
    motor_base_length = 0.0585

    def __init__(self, minimum_extension=0.1, maximum_extension):
        a = 1
