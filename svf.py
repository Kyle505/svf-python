# import the module
from ctypes import cdll
from ctypes import create_string_buffer
# load the library


lib = cdll.LoadLibrary('./src/libsvf.so')

## Test
class SVF(object):
  
    # constructor
    def __init__(self, module_name):
        # attribute
        self.obj = lib.initSVFModule(module_name)

    def buildSymbolTableInfo(self):
        lib.buildSymbolTableInfo()
    
    def buildSVFIR(self):
        lib.buildSVFIR()

    def createAndersenWaveDiff(self):
        lib.createAndersenWaveDiff()

    def getICFG(self):
        lib.getICFG()

    def getVFG(self):
        lib.getVFG()

    def buildFullSVFG(self):
        lib.buildFullSVFG()

    def release(self):
        lib.release()


class SVFModule(object):

    # constructor
    def __init__(self, module_name):
        # attribute
        self.obj = lib.initSVFModule(module_name)


    def buildSymbolTableInfo(self):
        lib.buildSymbolTableInfo()


module_name = create_string_buffer(b"example.ll")

# Init
svf = SVF(module_name)
svf.buildSymbolTableInfo()

svf.buildSVFIR()

svf.createAndersenWaveDiff()

svf.getICFG()
svf.getVFG()

svf.buildFullSVFG()

svf.release()

