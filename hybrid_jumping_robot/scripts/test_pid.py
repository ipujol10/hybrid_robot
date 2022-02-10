import PID
import numpy as np


class SimpleControl:
    def __init__(self, angle: float = 0, x: float = 0):
        self.A = np.array([[0, 1], [2, -1]], dtype=np.float16)
        self.B = np.array([[0], [1]], dtype=np.float16)
        self.x0 = np.array([[angle], [x]], dtype=np.float16)
        self.x = self.x0
        self.timeStep = 0.01

    def update(self, u):
        x1 = np.matmul(self.A, self.x) + self.B * u
        self.x += x1 * self.timeStep

    def output(self):
        return self.x[0][0]

    def print(self):
        print("angle = {}\nx= {}\n".format(self.x[0, 0], self.x[1, 0]))


if __name__ == "__main__":
    c = SimpleControl(0.1)
    c.print()
    pid = PID.PID(100, 1, 10, current_time=0)
    pid.setSampleTime(c.timeStep)
    pid.SetPoint = 0
    for i in range(int(10/0.1)):
        pid.update(c.output(), (i + 1) * c.timeStep)
        u = pid.output
        c.update(u)
        c.print()
    c.print()
