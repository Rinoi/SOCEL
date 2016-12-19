#include <iostream>
#include <list>
#include "ScaleImage.hpp"

#ifndef __SOCEL__
#define __SOCEL__

typedef unsigned int uint;
typedef unsigned char uchar;

class Socel
{

public:

  class IChar
  {

  public:
    ~IChar();
    IChar();
    IChar(const IChar &);
    IChar(const ScaleImage<uchar> &);

    const IChar			&operator=(const IChar &);

    void			save(const std::string &path);
    void			resize(uint width, uint height);
    IChar			getResize(uint width, uint height) const;

  public:

    const ScaleImage<uchar>	&getImg(const std::string &) const;

  private:

    ScaleImage<uchar>		img;
  };


public:
  ~Socel();

  Socel();
  Socel(const std::string &);

  bool				init(const std::string &);
  std::list<Socel::IChar>	getChar(uint CWidth = 28, uint CHeight = 28) const;

private:

  Socel::IChar			getIChar(uint x, uint y,
					 ScaleImage<bool> &, ScaleImage<bool> &) const;

public:

  bool				setCOp(uint CWidth, uint CHeight);

  const std::string		&getPathName() const;
  const ScaleImage<uchar>	&getImg() const;

private:

  std::string			pathName;
  ScaleImage<uchar>		img;
};

#endif
