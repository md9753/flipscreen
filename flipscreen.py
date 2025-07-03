# this should probably have some ability to restart listening
# also maybe don't hardcode the monitor names in future
import os
from serial import Serial

# magic number from kde display configuration screen
vAlignment = 750

def flipScreen(byte):
    if byte == b"0":
        os.system("kscreen-doctor output.DP-3.rotation.normal")
        os.system("kscreen-doctor output.DP-3.position.2560,0")
        os.system("kscreen-doctor output.DP-1.position.0,0")
    if byte == b"1":
        os.system("kscreen-doctor output.DP-3.rotation.right")
        os.system("kscreen-doctor output.DP-3.position.2560,0")
        os.system(f"kscreen-doctor output.DP-1.position.0,{vAlignment}")
    if byte == b"2":
        os.system("kscreen-doctor output.DP-3.rotation.left")
        os.system("kscren-doctor output.DP-3.position.2560,0")
        os.system(f"kscreen-doctor output.DP-1.position.0,{vAlignment}")
        # I don't rotate my monitor left and therefore this part probably doesn't work
    os.system("randpaper")


def listen():
    serialPort = Serial("/dev/ttyACM0")
    while True:
        data = serialPort.read()
        if data in (b"0", b"1", b"2"):
            flipScreen(data)


listen()
