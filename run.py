import subprocess as sp
import argparse
from os import path

SUFFIX = ".ll"
SVF_BIN = "./bin/svf-ex"

if __name__ == '__main__':
    
    # argument parser
    parser = argparse.ArgumentParser(description='SVF Python port')
    parser.add_argument('--file', default=None, help='Input source file')
    args = parser.parse_args()

    source = args.file
    
    # Check if file exists
    assert str(source).endswith("c") or str(source).endswith("cpp"), "Should input c or cpp file"
    assert path.exists(source), "File not existed"
    
    # LLVM compile the source code
    sp.run(["clang -S -c -g -fno-discard-value-names -emit-llvm {} -o {}".format(source, source.split(".")[0] + SUFFIX)], shell=True)

    # Use svf-ex to analysis the program
    sp.run([SVF_BIN, source.split(".")[0] + SUFFIX])
