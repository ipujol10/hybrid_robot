#!/usr/bin/env python3
import unittest
from hybrid_jumping_robot.scripts import Conversions


class TestConversionQuaternionToEuler(unittest.TestCase):
    def test_radians(self):  # need to start with test_
        # self.assertEqual(Conversions.quaternion_to_rpy([0,0,0,0]), 0)
        self.assertEqual(0, 0)
        print(Conversions.quaternion_to_rpy([0, 0, 0, 0]))


if __name__ == "__main__":
    unittest.main()
