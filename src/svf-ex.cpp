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
    // std::vector<std::string> moduleNameVec;
    //SVFModule* svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);

    void GetSVFModule(char* moduleName) {
        static std::vector<std::string> moduleNameVec;
        moduleNameVec = {moduleName};
        SVFModule* svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
        svfModule->buildSymbolTableInfo();
        //SVFIRBuilder builder;
        //SVFIR* pag = builder.build(svfModule);
        /// Create Andersen's pointer analysis
        //Andersen* ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
        SVFIRBuilder builder;
        SVFIR* pag = builder.build(svfModule);

        /// Create Andersen's pointer analysis
        Andersen* ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
        /// Call Graph
        PTACallGraph* callgraph = ander->getPTACallGraph();

        /// ICFG
        ICFG* icfg = pag->getICFG();

        /// Value-Flow Graph (VFG)
        VFG* vfg = new VFG(callgraph);

        /// Sparse value-flow graph (SVFG)
        SVFGBuilder svfBuilder;
        SVFG* svfg = svfBuilder.buildFullSVFG(ander);
        delete vfg;
        delete svfg;
        AndersenWaveDiff::releaseAndersenWaveDiff();
        SVFIR::releaseSVFIR();

        LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf.bc");
        SVF::LLVMModuleSet::releaseLLVMModuleSet();

        llvm::llvm_shutdown();

    }

    void Analysis(SVFModule* svfModule) {
        SVFIRBuilder builder;
        SVFIR* pag = builder.build(svfModule);

        /// Create Andersen's pointer analysis
        Andersen* ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
        /// Call Graph
        PTACallGraph* callgraph = ander->getPTACallGraph();

        /// ICFG
        ICFG* icfg = pag->getICFG();

        /// Value-Flow Graph (VFG)
        VFG* vfg = new VFG(callgraph);

        /// Sparse value-flow graph (SVFG)
        SVFGBuilder svfBuilder;
        SVFG* svfg = svfBuilder.buildFullSVFG(ander);
        delete vfg;
        delete svfg;
        AndersenWaveDiff::releaseAndersenWaveDiff();
        SVFIR::releaseSVFIR();

        LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf.bc");
        SVF::LLVMModuleSet::releaseLLVMModuleSet();

        llvm::llvm_shutdown();
    }


    void svfModule() {
        static std::vector<std::string> moduleNameVec;
        moduleNameVec = {"example.ll"};
        //*moduleNameVec.insert(moduleNameVec.begin(), moduleName);
        SVFModule* svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
        svfModule->buildSymbolTableInfo();

        /// Build Program Assignment Graph (SVFIR)
        SVFIRBuilder builder;
        SVFIR* pag = builder.build(svfModule);

        /// Create Andersen's pointer analysis
        Andersen* ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
        /// Call Graph
        PTACallGraph* callgraph = ander->getPTACallGraph();

        /// ICFG
        ICFG* icfg = pag->getICFG();

        /// Value-Flow Graph (VFG)
        VFG* vfg = new VFG(callgraph);

        /// Sparse value-flow graph (SVFG)
        SVFGBuilder svfBuilder;
        SVFG* svfg = svfBuilder.buildFullSVFG(ander);
        delete vfg;
        delete svfg;
        AndersenWaveDiff::releaseAndersenWaveDiff();
        SVFIR::releaseSVFIR();

        LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf.bc");
        SVF::LLVMModuleSet::releaseLLVMModuleSet();

        llvm::llvm_shutdown();
    }
}
