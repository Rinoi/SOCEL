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

FUNCTION(CIMG_CONFIGURATION)

  EXTERNALPROJECT_ADD(
    cimg

    GIT_REPOSITORY "https://github.com/dtschump/CImg.git"
    GIT_TAG "master"

    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""

    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/cimg"
  )

  add_dependencies(${CMAKE_PROJECT_NAME} cimg)

  set(CIMG_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/deps/cimg")
  include_directories(${CIMG_INCLUDE_DIRS})

ENDFUNCTION()
