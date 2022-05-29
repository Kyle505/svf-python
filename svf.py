# import the module
from ctypes import cdll
from ctypes import create_string_buffer
# load the library


lib = cdll.LoadLibrary('./lib/libsvf.so')

class SVF(object):
  
    # constructor
    def __init__(self, module_name):
        # attribute
        self.obj = lib.GetSVFModule(module_name)
    
  

module_name = create_string_buffer(b"example.ll")
f = SVF(module_name)

