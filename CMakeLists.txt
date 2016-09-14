##
## @copyright Copyright (c) 2016-, Issam SAID <said.issam@gmail.com>
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permetted provided that the following conditions
## are met:
##
## 1. Redistributions of source code must retain the above copyright
##    notice, this list of conditions and the following disclaimer.
## 2. Redistributions in binary form must reproduce the above copyright
##    notice, this list of conditions and the following disclaimer in the
##    documentation and/or other materials provided with the distribution.
## 3. Neither the name of the UPMC nor the names of its contributors
##    may be used to endorse or promote products derived from this software
##    without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
## INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
## HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
## PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
## LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
## NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
## @file CMakeLists.txt
## @author Issam SAID
## @brief CMake main build script for urb_tree.
##
project (urb_tree_distribution C CXX)
cmake_minimum_required (VERSION 2.8)

## Overwrite the install prefix
set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

## Add extra cmake modules dir
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

## Configurable options for how we want to build urb_tree
option(urb_tree_debug   "Build urb_tree with the debug mode."             OFF)
option(urb_tree_verbose "Build urb_tree with the verbose mode activated."  ON)

## Set the build type (DEFAULT is Release)
if (NOT CMAKE_BUILD_TYPE)
   set (CMAKE_BUILD_TYPE Release)
endif ()
if (urb_tree_debug)
	set (CMAKE_BUILD_TYPE Debug)
endif ()
message(STATUS "... CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

## Set the compilation flags 
if ("${CMAKE_C_COMPILER_ID}"     MATCHES "Cray")
  	# using Cray C
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    include(${CMAKE_MODULE_PATH}/gnu_c.cmake)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "Intel")
    include(${CMAKE_MODULE_PATH}/intel_c.cmake)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "MSVC")
  	# using Visual Studio 
endif()

if ("${CMAKE_Fortran_COMPILER_ID}"     MATCHES "Cray")
  	# using Cray Fortran
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "GNU")
	include(${CMAKE_MODULE_PATH}/gnu_fortran.cmake)
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "Intel")
  	include(${CMAKE_MODULE_PATH}/intel_fortran.cmake)
elseif ("${CMAKE_Fortran_COMPILER_ID}" MATCHES "MSVC")
  	# using Visual Studio Fortran
endif()

if ("${CMAKE_CXX_COMPILER_ID}"     MATCHES "Cray")
  	# using Cray C++
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	include(${CMAKE_MODULE_PATH}/gnu_cxx.cmake)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
    include(${CMAKE_MODULE_PATH}/intel_cxx.cmake)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
  	# using Visual Studio C++
endif()

if (urb_tree_verbose)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__URB_TREE_VERBOSE")
endif (urb_tree_verbose)

## Skip dependencies between builds and installs
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE) 

## Build the urb_tree C/C++ library.
add_subdirectory(src)

## Build the urb_tree unit testing suit.
enable_testing()
add_subdirectory(test EXCLUDE_FROM_ALL)

## Build the urb_tree examples.
add_subdirectory(examples EXCLUDE_FROM_ALL)

## Build the urb_tree documentation.
add_subdirectory(doc EXCLUDE_FROM_ALL)
