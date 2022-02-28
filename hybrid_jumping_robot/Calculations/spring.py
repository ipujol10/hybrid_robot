#!/usr/bin/env python3


g = 9.81  # gravity


class SpringCalculation:
    front_wheel_mass = 0.3
    rear_wheel_mass = 0.3
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
        self.total_mass = self.base_mass + self.motor_base_mass + self.extension_mass + 2 * self.front_wheel_mass + \
                          2 * self.rear_wheel_mass
        self.max_d = maximum_extension - minimum_extension

    def work(self, height=.3, show: bool = False):
        """
        Work needed to jump the specified height
        :param height: The height target to reach
        :param show: If the result of the work wants to be printed in the screen
        :return: The needed work in J
        """
        work = self.total_mass * g * height
        if show:
            print(f'The amount of work needed to jump {height}m is: {work}J')
        return work

    def needed_force(self, work, show: bool = False):
        """
        The force needed to perform the work
        :param work: The amount of work needed in J
        :param show: If the result of the work wants to be printed in the screen
        :return: The needed force in N
        """
        force = work / self.max_d
        if show:
            print(f'The amount of force needed to perform {work}J is: {force}N')
        return force

    def needed_acceleration(self, force, show: bool = False):
        """
        The acceleration achieved with the force
        :param force: The amount of force needed in N
        :param show: If the result of the work wants to be printed in the screen
        :return: The needed acceleration in m/s²
        """
        extension_weight = 2 * self.rear_wheel_mass + self.extension_mass
        acceleration = force / extension_weight
        if show:
            print(f'The acceleration achieved with the {force}N is: {acceleration}m/s²')
            print(f'Extension weight: {extension_weight}kg')
        return acceleration


if __name__ == "__main__":
    spring = SpringCalculation()
    w = spring.work(show=True)
    f = spring.needed_force(w, True)
    a = spring.needed_acceleration(f, True)
    # print("Spring done")
