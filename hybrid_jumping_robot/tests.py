#!/usr/bin/env python3
import unittest
from hybrid_jumping_robot.tests.Conversions import conversion_test

if __name__ == "__main__":
    suite = unittest.TestLoader.loadTestsFromModule(conversion_test)
    unittest.TextTestRunner().run(suite)
