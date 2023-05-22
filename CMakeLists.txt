cmake_minimum_required(VERSION 3.10)

project(tokenizer CXX)
include(CMakePackageConfigHelpers)
include(CTest)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)


# ABI version
# http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html
set(SONAME 10)

set(LIBRE2 /usr/lib/x86_64-linux-gnu/libre2.so)

# add_subdirectory(re2)

add_library(tokenizer tokenizer/bpe.cc tokenizer/bpe.h tokenizer/tokenizer.h tokenizer/tokenizer.cpp)
target_link_libraries(tokenizer ${LIBRE2})
# target_include_directories(tokenizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/re2)
set_target_properties(tokenizer PROPERTIES SOVERSION ${SONAME} VERSION ${SONAME}.0.0)

FOREACH (TEST bpe_test tokenizer_test)
  add_executable(${TEST} tokenizer/${TEST}.cc)
  set_target_properties(${TEST}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
  )
  target_link_libraries(${TEST} PRIVATE tokenizer ${LIBRE2} )
ENDFOREACH()