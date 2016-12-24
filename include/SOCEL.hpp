//
// MIT License
//
// Copyright (c) 2016 Lucas Mayol
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#pragma once

#include "ScaleImage.hpp"
#include <iostream>
#include <list>

typedef unsigned int  uint;
typedef unsigned char uchar;

class Socel {

public:
  class IChar {

  public:
    ~IChar();
    IChar();
    IChar(const IChar &);
    IChar(const ScaleImage<uchar> &);

    const IChar &operator=(const IChar &);

    void save(const std::string &path);
    void resize(uint width, uint height);
    IChar getResize(uint width, uint height) const;

  public:
    const ScaleImage<uchar> &getImg(const std::string &) const;

  private:
    ScaleImage<uchar> img;
  };

public:
  ~Socel();

  Socel();
  Socel(const std::string &);

  bool                    init(const std::string &);
  std::list<Socel::IChar> getChar(uint CWidth = 28, uint CHeight = 28) const;

private:
  Socel::IChar getIChar(uint x, uint y, ScaleImage<bool> &,
                        ScaleImage<bool> &) const;

public:
  bool setCOp(uint CWidth, uint CHeight);

  const std::string &      getPathName() const;
  const ScaleImage<uchar> &getImg() const;

private:
  std::string       pathName;
  ScaleImage<uchar> img;
};
