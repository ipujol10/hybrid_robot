#!/usr/bin/env python3

class SpringCalculation:
    wheel_mass = 0.3
    base_mass = 0.4
    extension_mass = 0.4
    motor_base_mass = 0.4
    base_length = 0.215
    extension_length = 0.2
    motor_base_length = 0.0585

    def __init__(self, minimum_extension=0.02, maximum_extension=0.16):
        if minimum_extension < 0 or minimum_extension > self.extension_length or \
                maximum_extension > self.extension_length or maximum_extension < minimum_extension:
            raise ValueError("The maximum and/or minimum extensions are not correct")
        basic_length = self.base_length + self.motor_base_length
        self.min_length = basic_length + minimum_extension
        self.max_length = basic_length + maximum_extension


if __name__ == "__main__":
    spring = SpringCalculation()
    print("Spring done")
