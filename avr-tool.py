import os
import subprocess
import argparse
import requests


# URL of the arduino-cli installer
ARDUINO_CLI_DL_URL = "https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh"

def bootstrap():
    print("Bootstrapping")
    
    # Set up the toolchain directory
    if os.path.exists("./toolchain"):
        print("Wiping toolchain directory")
        subprocess.call(["rm", "-rf", "./toolchain"])
    print("Setting up new toolchains")
    
    # Download the arduino cli
    print("Downloading arduino-cli")
    resp = requests.get(ARDUINO_CLI_DL_URL)
    
    if resp.status_code != 200:
        print("Failed to download arduino-cli")
        exit(1)
    
    print("Writing installer to disk")
    with open("./toolchain/install.sh", "w") as fp:
        fp.write(resp.body)
        fp.close()
    
    print("Installing arduino-cli")