#ifndef __BOUND__
#define __BOUND__

class Bound
{

public:
  
  static int	getDistX(const Bound &b1, const Bound &b2)
  {
    if (b2.x <= b1.x && b1.x <= b2.x + b2.width)
      return (0);
    if (b1.x <= b2.x && b2.x <= b1.x + b1.width)
      return (0);

    if (b1.x > b2.x)
	return (b1.x - (b2.x + b2.width));
    return (b2.x - (b1.x + b1.width));
  }

  static int	getDistY(const Bound &b1, const Bound &b2)
  {
    if (b2.y <= b1.y && b1.y <= b2.y + b2.height)
      return (0);
    if (b1.y <= b2.y && b2.y <= b1.y + b1.height)
      return (0);

    if (b1.y > b2.y)
      return (b1.y - (b2.y + b2.height));
    return (b2.y - (b1.y + b1.height));
  }

public:
  
  ~Bound()
  {}

  Bound()
  {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
  }

  Bound(const Bound &bound)
  {
    *this = bound;
  }

  Bound(int posX, int posY,
	int width, int height)
  {
    this->x = posX;
    this->y = posY;
    this->width = width;
    this->height = height;
  }

  const Bound		&operator=(const Bound &bound)
  {
    this->x = bound.x;
    this->y = bound.y;
    this->width = bound.width;
    this->height = bound.height;
    return (*this);
  }

  int		getDX(const Bound &b2)
  {
    return (Bound::getDistX(*this, b2));
  }

  int		getDY(const Bound &b2)
  {
    return (Bound::getDistY(*this, b2));
  }


public:

  int		getX() const
  {return (this->x);}

  int		getY() const
  {return (this->y);}

  int		getWidth() const
  {return (this->width);}

  int		getHeight() const
  {return (this->height);}

private:

  int	x;
  int	y;
  int	width;
  int	height;

};

#endif
