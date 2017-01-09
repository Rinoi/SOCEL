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

#include <iostream>
#include <list>
#include "ScaleImage.hpp"
#include "bound.hpp"

typedef unsigned int  uint;
typedef unsigned char uchar;

class Socel {

public:
  class IChar {

  public:

    enum Type
      {SPACE, RETURN, IMG};

  public:
    ~IChar();
    IChar();
    IChar(Type type);
    IChar(const IChar &);
    IChar(const ScaleImage<uchar> &img,
	  uint posX, uint posY,
	  uint width, uint height);
    IChar(const ScaleImage<uchar> &img, const Bound &bound);

    const IChar &operator=(const IChar &);

    void			save(const std::string &path);
    void			resize(uint width, uint height);
    IChar			getResize(uint width, uint height) const;

    bool			isSpace() const;
    bool			isReturn() const;
    bool			isImg() const;

  public:
    const ScaleImage<uchar>	&getImg() const;

    const Bound			&getBound() const;

    Type			getType() const;

  private:

    Bound			bound;
    ScaleImage<uchar>		img;
    Type			type;
  };

public:
  ~Socel();

  Socel();
  Socel(const std::string &);

  bool				init(const std::string &);
  std::list<Socel::IChar>	getChar(uint CWidth = 28, uint CHeight = 28) const;

  void				save(const std::string &path);

private:

  unsigned int			getMeanY(const std::list<Socel::IChar> &) const;
  unsigned int			getMeanX(const std::list<Socel::IChar> &) const;
  void				sortList(std::list<Socel::IChar> &) const;
  void				fixAccend(std::list<Socel::IChar> &) const;
  Socel::IChar			getIChar(uint x, uint y,
					 ScaleImage<bool> &, ScaleImage<bool> &) const;
  Socel::IChar			getIChar(int x, int y, int width, int height) const;

  Socel::IChar			getFirstChar(std::list<Socel::IChar> &) const;
  //and erase

  Socel::IChar			getNext(const Socel::IChar &, std::list<Socel::IChar> &,
					int &xprev, unsigned int meanX) const;
  //and erase

public:
  bool				setCOp(uint CWidth, uint CHeight);

  const std::string &		getPathName() const;
  const ScaleImage<uchar>	&getImg() const;

private:
  std::string			pathName;
  ScaleImage<uchar>		img;
  unsigned int			meanX;
};
