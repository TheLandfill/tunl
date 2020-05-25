#!/usr/bin/env python3
import sys
import os
import subprocess

class cd:
    """Context manager for changing the current working directory"""
    def __init__(self, newPath):
        self.newPath = os.path.expanduser(newPath)

    def __enter__(self):
        self.savedPath = os.getcwd()
        os.chdir(self.newPath)

    def __exit__(self, etype, value, traceback):
        os.chdir(self.savedPath)

def gen_toolchain(toolchains):
    for toolchain in toolchains:
        with cd(toolchain):
            os.makedirs("Release", exist_ok=True)
            with cd("Release"):
                subprocess.run(['cmake', '-DCMAKE_BUILD_TYPE=Release', '-DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake', '../../../'])
            os.makedirs("Debug", exist_ok=True)
            with cd("Debug"):
                subprocess.run(['cmake', '-DCMAKE_BUILD_TYPE=Debug', '-DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake', '../../../'])

def create_cur_toolchain_symlink(toolchain):
    if os.path.isfile('Debug'):
        os.remove('Debug')
    if os.path.isfile('Release'):
        os.remove('Release')
    os.symlink(toolchain + '/Debug', 'Debug', target_is_directory=True)
    os.symlink(toolchain + '/Release', 'Release', target_is_directory=True)


if __name__ == "__main__":
    if len(sys.argv) >= 2:
        gen_toolchain(sys.argv[1:])
        create_cur_toolchain_symlink(sys.argv[1])
