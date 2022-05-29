llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )
file (GLOB SOURCES
   *.cpp
)

add_library(
        svf
        SHARED
        ${SOURCES}
)

target_link_libraries(svf ${SVF_LIB} ${LLVMCudd} ${llvm_libs})
target_link_libraries(svf ${Z3_LIBRARIES})

