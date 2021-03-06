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

#include <stack>

#include <limits.h>

#include "CImg.h"
#include "SOCEL.hpp"

// IChar

Socel::IChar::~IChar() {}

Socel::IChar::IChar() {}

Socel::IChar::IChar(Socel::IChar::Type type)
{
  this->type = type;
}

Socel::IChar::IChar(const IChar &Ichar) {
  *this = Ichar;
}

Socel::IChar::IChar(const ScaleImage<uchar> &img,
		    uint posX, uint posY,
		    uint width, uint height)
{
  this->img = img;
  this->type = Socel::IChar::IMG;
  this->bound = Bound(posX, posY, width, height);
}

Socel::IChar::IChar(const ScaleImage<uchar> &img,
		    const Bound &bound)
{
  this->img = img;
  this->bound = bound;
}

const Socel::IChar &
Socel::IChar::operator=(const IChar &Ichar) {
  this->img = Ichar.img;
  this->type = Ichar.type;
  this->bound = Ichar.bound;
  return (*this);
}

void
Socel::IChar::save(const std::string &path) {

  cimg_library::CImg<uint> img;

  if (this->type == Socel::IChar::IMG)
    {
      img = cimg_library::CImg<uint>(this->img.getWidth(), this->img.getHeight());
      for (uint y = 0; y < this->img.getHeight(); y += 1)
	for (uint x = 0; x < this->img.getWidth(); x += 1)
	  {
	    uint	color;
	    uchar	*ptn = (uchar*)(&color);
	
	    ptn[0] = this->img.valueAt(x, y);
	    ptn[1] = this->img.valueAt(x, y);
	    ptn[2] = this->img.valueAt(x, y);
	    ptn[3] = this->img.valueAt(x, y);
	    img(x, y) = color;
	  }
    }
  else if (this->type == Socel::IChar::SPACE)
    {
      img = cimg_library::CImg<uint>(1, 1);
      img(0, 0) = 0xFFFFFFFF;
    }
  else
    {
      img = cimg_library::CImg<uint>(1, 1);
      img(0, 0) = 0x0;
    }
  img.save(path.c_str());
}

void
Socel::IChar::resize(uint width, uint height) {
  *this = this->getResize(width, height);
}

Socel::IChar
Socel::IChar::getResize(uint width, uint height) const {
  ScaleImage<uchar> img(width, height);

  for (uint y = 0; y < height; y += 1)
    for (uint x = 0; x < width; x += 1)
      {
	img.setValueAt(x, y,
		       this->img.valueAt(((double)(x) / (double)(width)) *
					 (double)(this->img.getWidth()),
					 ((double)(y) / (double)(height)) *
					 (double)(this->img.getHeight()))
		       );
      }
  return (Socel::IChar(img, this->bound));
}

bool				Socel::IChar::isSpace() const
{
  return (this->type == Socel::IChar::SPACE);
}

bool				Socel::IChar::isReturn() const
{
  return (this->type == Socel::IChar::RETURN);
}

bool				Socel::IChar::isImg() const
{
  return (this->type == Socel::IChar::IMG);
}

const ScaleImage<uchar>		&Socel::IChar::getImg() const
{
  return (this->img);
}

const Bound			&Socel::IChar::getBound() const
{
  return (this->bound);
}

Socel::IChar::Type		Socel::IChar::getType() const
{
  return (this->type);
}

//SOCEL

Socel::~Socel() {}

Socel::Socel() {}

Socel::Socel(const std::string &s) {
  this->init(s);
}

bool
Socel::init(const std::string &s) {
  cimg_library::CImg<uint> img(s.c_str());

  this->img = ScaleImage<uchar>(img.width(), img.height());
  for (int y = 0; y < img.height(); y += 1)
    for (int x = 0; x < img.width(); x += 1)
      {
	uint	v;

	v = 0;
	v += img(x, y, 0, 0);
	v += img(x, y, 0, 1);
	v += img(x, y, 0, 2);
	v /= 3;
	this->img.setValueAt(x, y, v);
      }
  return (true);
}

typedef struct {
  uint x;
  uint y;
} t_ptn;

static void
verifMaxMinV(uint &max, uint &min, uint &v) {
  if (v > max)
    max = v;
  if (v < min)
    min = v;
}

Socel::IChar			Socel::getIChar(int x, int y, int width, int height) const
{
  ScaleImage<uchar>		img(width, height);

  for (int iy = 0; iy < height; iy += 1)
    for (int ix = 0; ix < width; ix += 1)
      img.setValueAt(ix, iy,
		     this->img.valueAt(x + ix, y + iy));
  return (IChar(img,
		x, y,
		width, height));
 
}

Socel::IChar			Socel::getIChar(uint x, uint y,
						ScaleImage<bool> &binImg,
						ScaleImage<bool> &testImg) const
{
  std::stack<t_ptn>		stack;
  std::list<t_ptn>		list;
  uint				maxX = x;
  uint				minX = x;
  uint				maxY = y;
  uint				minY = y;

  stack.push({x, y});
  // std::cout << "start";
  while (stack.empty() == false) {
    t_ptn ptn = stack.top();

    x = ptn.x;
    y = ptn.y;
    // std::cout << "a";
    stack.pop();
    if (testImg.valueAt(x, y) == true)
      continue;
    testImg.setValueAt(x, y, true);
    if (binImg.valueAt(x, y) == true) {
      list.push_back(ptn);
      verifMaxMinV(maxX, minX, x);
      verifMaxMinV(maxY, minY, y);
      stack.push({x + 1, y});
      stack.push({x - 1, y});
      stack.push({x, y + 1});
      stack.push({x, y - 1});
    }
  }
  // std::cout << "end";
  // return
  {
    /*maxX += 2;
      minX -= 2;
      maxY += 2;
      minY -= 2;*/
    ScaleImage<uchar> img(maxX - minX, maxY - minY);

    for (uint y = minY; y < maxY; y += 1)
      for (uint x = minX; x < maxX; x += 1)
	img.setValueAt(x - minX, y - minY,
		       255);
    for (auto it = list.begin(); it != list.end(); it++)
      img.setValueAt((*it).x - minX, (*it).y - minY,
      this->img.valueAt((*it).x, (*it).y));
    return (IChar(img,
		  minX, minY,
		  maxX - minX, maxY - minY));
  }
}

static double			getDist(double x, double y)
{
  return (sqrt(x * x + y * y));
}

Socel::IChar			Socel::getFirstChar(std::list<Socel::IChar> &list) const
{
  double			dist = getDist(list.front().getBound().getX(),
					    list.front().getBound().getY());
  auto				tmp = list.begin();
  IChar				c;

  for (auto it = list.begin(); it != list.end(); it++)
    {
      double d = getDist((*it).getBound().getX(),
			 (*it).getBound().getY());

      if (dist > d)
	{
	  dist = d;
	  tmp = it;
	}
    }
  c = (*tmp);
  list.erase(tmp);
  return (c);
}

Socel::IChar			Socel::getNext(const Socel::IChar &ichar,
					       std::list<Socel::IChar> &list,
					       int &prev, unsigned int meanX) const
{
  auto				i2 = list.begin();
  int				d = INT_MAX;
  int				tmp;
  IChar				c;

  prev = 0;
  for (auto it = list.begin(); it != list.end(); it++)
    {
      tmp = Bound::getDistX(ichar.getBound(), (*it).getBound());
      if (Bound::getDistY(ichar.getBound(), (*it).getBound()) <= 0 &&
	  (tmp < d && tmp >= 0))
	{
	  i2 = it;
	  d = tmp;
	}
    }
  if (d == INT_MAX)
    {
      prev = 2;
      return (this->getFirstChar(list));
    }
  if (d >= meanX * 0.45)
      prev = 1;
  c = (*i2);
  list.erase(i2);
  return (c);
}

void				Socel::sortList(std::list<Socel::IChar> &Alist) const
{
  std::list<Socel::IChar>	list;
  Bound				bound;
  Socel::IChar			tmp;
      
  //init
  list = Alist;
  if (list.empty() == true)
    return ;
  Alist.clear();
  //end

  tmp = this->getFirstChar(list);
  Alist.push_back(tmp);
  while (list.empty() == false)
    {
      int prev;

      tmp = this->getNext(tmp, list, prev, this->getMeanX(Alist));
      if (prev == 1)
	Alist.push_back(Socel::IChar(Socel::IChar::SPACE));
      else if (prev == 2)
	Alist.push_back(Socel::IChar(Socel::IChar::RETURN));
      Alist.push_back(tmp);
    }
}

unsigned int			Socel::getMeanY(const std::list<Socel::IChar> &list) const
{
  unsigned int			mean = 0;

  for (auto it = list.begin(); it != list.end(); it++)
    mean += (*it).getBound().getHeight();
  mean /= list.size();
  return (mean);
}

unsigned int			Socel::getMeanX(const std::list<Socel::IChar> &list) const
{
  unsigned int			mean = 0;

  for (auto it = list.begin(); it != list.end(); it++)
    mean += (*it).getBound().getWidth();
  mean /= list.size();
  return (mean);
}

void				Socel::fixAccend(std::list<Socel::IChar> &list) const
{
  auto				it = list.begin();
  int			lim = (double)(this->getMeanY(list)) * 0.25;

 start:
  while (it != list.end())
    {
      Bound bound = (*it).getBound();

      for (auto itt = list.begin(); itt != list.end(); itt++)
	{
	  int	dY = Bound::getDistY(bound, (*itt).getBound());
	  int	dX = Bound::getDistX(bound, (*itt).getBound());

	  /*
	  std::cout << "y1 " << bound.getY() << " y2 "<< (*itt).getBound().getY() <<
	    " lim = " << lim << " test = " <<
	    Bound::getDistY(bound, (*itt).getBound()) << std::endl;*/
	  if (dX <= 0 && dY <= lim && dY > 0)
	    {
	      int maxX = bound.getX() + bound.getWidth();
	      int minX = bound.getX();
	      int maxY = bound.getY() + bound.getHeight();
	      int minY = bound.getY();
	      bound = (*itt).getBound();

	      if (maxX < bound.getX() + bound.getWidth())
		maxX = bound.getX() + bound.getWidth();
	      if (minX > bound.getX())
		minX = bound.getX();
	      if (maxY < bound.getY() + bound.getHeight())
		maxY = bound.getY() + bound.getHeight();
	      if (minY > bound.getY())
		minY = bound.getY();
	      
	      (*itt) = getIChar(minX, minY, maxX - minX, maxY - minY);
	      it = list.erase(it);
	      goto start;
	    }
	}
      it++;
    }
}

std::list<Socel::IChar>		Socel::getChar(uint CWidth, uint CHeight) const
{
  ScaleImage<bool>		binImg(this->img.getWidth(), this->img.getHeight());
  ScaleImage<bool>		testImg(this->img.getWidth(), this->img.getHeight());
  std::list<Socel::IChar>	list;

  // init
  for (uint y = 0; y < this->img.getHeight(); y += 1)
    for (uint x = 0; x < this->img.getWidth(); x += 1)
      {
	testImg.setValueAt(x, y, false);
	binImg.setValueAt(x, y,
			  this->img.valueAt(x, y) <= 233 ? true : false);
      }
  //iterate
  for (uint y = 0; y < this->img.getHeight(); y += 1)
    for (uint x = 0; x < this->img.getWidth(); x += 1) {
      if (testImg.valueAt(x, y) == true)
        continue;
      if (binImg.valueAt(x, y) == true) {
        Socel::IChar Ichar = this->getIChar(x, y, binImg, testImg);
        list.push_back(Ichar.getResize(CWidth, CHeight));
      }
    }
  this->fixAccend(list);
  this->sortList(list);
  return (list);
}


const std::string	&Socel::getPathName() const
{
  return (this->pathName);
}

const ScaleImage<uchar> &
Socel::getImg() const {
  return (this->img);
}

void				Socel::save(const std::string &path)
{
  cimg_library::CImg<uint>	img(this->img.getWidth(), this->img.getHeight());

  for (uint y = 0; y < this->img.getHeight(); y += 1)
    for (uint x = 0; x < this->img.getWidth(); x += 1)
      {
	uint	color;
	uchar	*ptn = (uchar*)(&color);
	
	ptn[0] = this->img.valueAt(x, y);
	ptn[1] = this->img.valueAt(x, y);
	ptn[2] = this->img.valueAt(x, y);
	ptn[3] = this->img.valueAt(x, y);
	img(x, y) = color;
      }
  img.save(path.c_str());
}
