#!/usr/bin/env python3
from pynput import keyboard
import Robot

r = Robot.Robot('hybrid_jumping_robot')


def on_press(key):
    try:
        print('Alphanumeric key pressed: {0} '.format(
            key.char))
    except AttributeError:
        print('special key pressed: {0}'.format(
            key))
    if key == 'w':
        pass  # go forward
    if key == 'x':
        pass  # Full break


# Collect events until released
with keyboard.Listener(
        on_press=on_press) as listener:
    listener.join()

while True:
    pass
