#
# MIT License
#
# Copyright (c) 2016 Thibault Martinez
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#

########## GLOBAL CONFIGURATION ##########

PROJECT(socel CXX)
ENABLE_LANGUAGE(C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
set(CMAKE_VERBOSE_MAKEFILE OFF)
string(TOUPPER ${CMAKE_PROJECT_NAME} PROJECT_NAME)

########## PROJECT DIRECTORIES ##########

SET(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source/)
SET(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

######### VERSION ##########

SET(PROJECT_VERSION_MAJOR 0)
SET(PROJECT_VERSION_MINOR 1)
SET(PROJECT_VERSION_PATCH 0)

SET(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

CONFIGURE_FILE(${PROJECT_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/version.hpp.in
               ${PROJECT_INCLUDE_DIR}/${CMAKE_PROJECT_NAME}/version.hpp)

########## PROJECT FILES ##########

FILE(GLOB_RECURSE
     PROJECT_SOURCE_FILES
     ${PROJECT_SOURCE_DIR}/*.cpp)

FILE(GLOB_RECURSE
     PROJECT_INCLUDE_FILES
     ${PROJECT_INCLUDE_DIR}/*.hpp)

INCLUDE_DIRECTORIES(${PROJECT_INCLUDE_DIR})

########## LIBRARY ##########

ADD_LIBRARY(${CMAKE_PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES})

set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

########## INSTALL SETTINGS ##########

INSTALL(TARGETS ${CMAKE_PROJECT_NAME} ARCHIVE DESTINATION lib)

########## COMPILATION SETTINGS ##########

INCLUDE(cmake/compilation_settings.cmake)

########## EXTERNAL LIBRARIES SETTINGS ##########

INCLUDE(ExternalProject)

INCLUDE(cmake/x11_settings.cmake)

INCLUDE(cmake/cimg_settings.cmake)
