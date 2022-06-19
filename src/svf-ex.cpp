//===- svf-ex.cpp -- A driver example of SVF-------------------------------------//
//
//                     SVF: Static Value-Flow Analysis
//
// Copyright (C) <2013->  <Yulei Sui>
//

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//===-----------------------------------------------------------------------===//

/*
 // A driver program of SVF including usages of SVF APIs
 //
 // Author: Yulei Sui,
 */

#include "SVF-FE/LLVMUtil.h"
#include "Graphs/SVFG.h"
#include "WPA/Andersen.h"
#include "SVF-FE/SVFIRBuilder.h"
#include "Util/Options.h"

using namespace llvm;
using namespace std;
using namespace SVF;

static llvm::cl::opt<std::string> InputFilename(cl::Positional,
        llvm::cl::desc("<input bitcode>"), llvm::cl::init("-"));


extern "C" {

    // Segmentation Fault
    SVFModule* svfModule;

    SVFIRBuilder *builder;
    SVFIR* pag;

    // Create Andersen's pointer analysis
    Andersen* ander;

    /// Call Graph
    PTACallGraph* callgraph;

    ICFG* icfg;
    VFG* vfg;
    SVFGBuilder* svfBuilder;
    SVFG* svfg;

    void initSVFModule(char* moduleName) {
        static std::vector<std::string> moduleNameVec;
        moduleNameVec = {moduleName};
        svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
    }



    void buildSymbolTableInfo() {
        svfModule->buildSymbolTableInfo();

    }

    void buildSVFIR() {
        SVFIRBuilder builder;
        pag = builder.build(svfModule);
    }

    void createAndersenWaveDiff() {
        ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
    }

    void getPTACallGraph() {
        callgraph = ander -> getPTACallGraph();
    }

    void getICFG() {
        icfg = pag -> getICFG();
    }

    void getVFG() {
        vfg = new VFG(callgraph);
    }

    void buildFullSVFG() {
        SVFGBuilder svfBuilder;
        svfg = svfBuilder.buildFullSVFG(ander);
    }

    void release() {
        delete vfg;
        delete svfg;
        AndersenWaveDiff::releaseAndersenWaveDiff();
        SVFIR::releaseSVFIR();

        LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf.bc");
        SVF::LLVMModuleSet::releaseLLVMModuleSet();

        llvm::llvm_shutdown();
    }
}
