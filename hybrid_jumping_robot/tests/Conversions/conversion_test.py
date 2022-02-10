#!/usr/bin/env python3
import unittest
from hybrid_jumping_robot.scripts import Conversions
from geometry_msgs.msg import Quaternion


class TestConversionQuaternionToEuler(unittest.TestCase):
    def test_normal(self):  # need to start with test_
        self.assertEqual(Conversions.quaternion_to_rpy([0, 0, 0, 1]), (0, 0, 0))
        self.assertAlmostEqual(Conversions.quaternion_to_rpy([0, 0, 1, 1])[-1], 1.5707963)
        self.assertAlmostEqual(Conversions.quaternion_to_rpy([1, 0, 0, 1])[0], 1.5707963)
        self.assertAlmostEqual(Conversions.quaternion_to_rpy([0.707106781, 0, 0, 0.707106781])[0], 1.5707963)

    def test_weird(self):
        self.assertEqual(Conversions.quaternion_to_rpy([0, 0, 0, 80000]), (0, 0, 0))
        self.assertAlmostEqual(Conversions.quaternion_to_rpy([234, 47536, 353, 5])[0], 3.1267403)
        self.assertAlmostEqual(Conversions.quaternion_to_rpy([234, 47536, 353, 5])[1], 0.0001372)
        self.assertAlmostEqual(Conversions.quaternion_to_rpy([234, 47536, 353, 5])[2], 3.1317465)

    def test_quaternion(self):
        self.assertEqual(Conversions.quaternion_to_rpy(Quaternion(0, 0, 0, 1)), (0, 0, 0))
        self.assertAlmostEqual(Conversions.quaternion_to_rpy(Quaternion(0, 0, 1, 1))[-1], 1.5707963)
        self.assertAlmostEqual(Conversions.quaternion_to_rpy(Quaternion(1, 0, 0, 1))[0], 1.5707963)
        self.assertAlmostEqual(Conversions.quaternion_to_rpy(Quaternion(0.707106781, 0, 0, 0.707106781))[0], 1.5707963)


if __name__ == "__main__":
    unittest.main()
