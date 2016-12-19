#ifndef __SCALE_IMAGE__
#define __SCALE_IMAGE__

#include <iostream>
#include "math.h"

template <typename T>
class ScaleImage
{

 public:

  ScaleImage()
  {
    this->data = NULL;
  }

  ScaleImage(unsigned int width, unsigned int height)
  {
    this->data = NULL;
    this->width = width;
    this->height = height;
    this->newData(width, height);
  }

  ScaleImage(const ScaleImage &source)
  {
    this->data = NULL;
    this->copy(source);
  }

  ~ScaleImage()
  {
    this->freeData();
  }

 public:

  void			newData(unsigned int width, unsigned int height)
  {
    this->freeData();
    this->height = height;
    this->width = width;

    this->data = new T[this->height * this->width];
  }

  void			freeData()
  {
    if (this->data != NULL)
      delete[] this->data;
    this->data = NULL;
  }

  ScaleImage		erosion(unsigned int b)
  {
    ScaleImage		img(this->width, this->height);

    for (int y = 0; y < (int)(this->height); y += 1)
      for (int x = 0; x < (int)(this->width); x += 1)
	{
	  /*if (y < (int)(b) || y >= (int)(this->height - b) ||
	      x < (int)(b) || x >= (int)(this->width - b))
	    img.setValueAt(x, y, this->valueAt(x, y));
	    else*/
	    img.setValueAt(x, y, this->minOf(x, y, b));
	}
    return (img);
  }

  ScaleImage		dilation(unsigned int b)
  {
    ScaleImage		img(this->width, this->height);

    for (int y = 0; y < (int)(this->height); y += 1)
      for (int x = 0; x < (int)(this->width); x += 1)
	{
	  /*if (y < (int)(b) || y >= (int)(this->height - b) ||
	      x < (int)(b) || x >= (int)(this->width - b))
	    img.setValueAt(x, y, this->valueAt(x, y));
	    else*/
	    img.setValueAt(x, y, this->maxOf(x, y, b));
	}
    return (img);
  }

  ScaleImage		closing(unsigned int b)
  {
    ScaleImage		img;

    img = this->dilation(b);
    img = img.erosion(b);
    return (img);
  }

  ScaleImage		opening(unsigned int b)
  {
    ScaleImage		img;

    img = this->erosion(b);
    img = img.dilation(b);
    return (img);
  }

private:

  void             sort(int *tab, int nb)
  {
      bool                b = true;
      int                 tmp;

      while (b == true)
      {
          b = false;
          for (int i = 1; i < nb; i += 1)
              if (tab[i - 1] > tab[i])
              {
                  tmp = tab[i - 1];
                  tab[i - 1] = tab[i];
                  tab[i] = tmp;
                  b = true;
              }
      }
  }

  int              medianOf(int *tab, int nb)
  {
      sort(tab, nb);

      if (nb % 2 == 0)
          return ((tab[nb / 2] + tab[(nb / 2) + 1]) / 2);
      return (tab[nb / 2]);
  }

public:

  ScaleImage              medianFilter(unsigned int b)
  {
      int                 tab[(b + 2) * (b + 2)];
      int                 v_x;
      int                 v_y;
      int                 t;
      ScaleImage          img = *this;

      for (unsigned int y = b; y < this->height - b; y += 1)
          for (unsigned int x = b; x < this->width - b; x += 1)
          {
              v_x = x - b;
              t = 0;
              for (unsigned int a = 0; a < (b + 2); a += 1)
              {
                  v_y = y - b;
                  for (unsigned int c = 0; c < (b + 2); c += 1)
                  {
                      tab[t] = this->valueAt(v_x, v_y);
                      v_y += 1;
                      t += 1;
                  }
                  v_x += 1;
              }
              img.setValueAt(x, y, medianOf(tab, (b + 2) * (b + 2)));
          }
      return (img);
  }
  //ScaleImage		medianFilter(unsigned int b);

  void			copy(const ScaleImage &source)
  {
    if (source.data == NULL)
      return ;
    this->newData(source.width, source.height);
    for (unsigned int i = 0; i < this->width * this->height; i += 1)
      this->data[i] = source.data[i];
  }

  bool			areIn(int x, int y)
  {
    if (x < 0 || y < 0)
      return (false);
    if ((unsigned int)(x) >= this->width || (unsigned int)(y) >= this->height)
      return (false);
    return (true);
  }

  void			setValueAt(unsigned int x, unsigned int y, T value)
  {
    if (this->width * y + x >= this->width * this->height)
      return;
    this->data[this->width * y + x] = value;
  }

  T			valueAt(unsigned int x, unsigned int y) const
  {
    if (x >= this->width || y >= this->height)
      return ((T)(0));
    return (this->data[this->width * y + x]);
  }

  const ScaleImage	&operator=(const ScaleImage &source)
  {
    this->copy(source);
    return (*this);
  }

  ScaleImage		operator-(const ScaleImage &right) const
  {
    ScaleImage		img;

    if (this->width != right.width || this->height != right.height)
      return (img);
    img.newData(this->width, this->height);
    for (unsigned int y = 0; y < this->height; y += 1)
      for (unsigned int x = 0; x < this->width; x += 1)
	{
	  if (this->valueAt(x, y) < right.valueAt(x, y))
	    img.setValueAt(x, y, 0);
	  else
	    img.setValueAt(x, y, this->valueAt(x, y) - right.valueAt(x, y));
	}
    return (img);
  }


 public:

  T			minOf(int x, int y, int b)
  {
    T			min;
    int			v_x;
    int			v_y;

    min = this->valueAt(x, y);
    if (b <= 0)
      return (min);
    v_x = x - b;
    v_y = y - b;
    for (int a = 0; a < b * 2 + 1; a += 1)
      {
	v_y = y - b;
	for (int t = 0; t < b * 2 + 1; t += 1)
	  {
	    if (this->areIn(v_x, v_y) == true)
	      if (this->onCircle(v_x, v_y, x, y, b) == true)
		if (this->valueAt(v_x, v_y) < min)
		  min = this->valueAt(v_x, v_y);
	    v_y += 1;
	  }
	v_x += 1;
      }
    return (min);
  }

  T			maxOf(int x, int y, int b)
  {
    T			max;
    int                 v_x;
    int                 v_y;

    max = this->valueAt(x, y);
    if (b <= 0)
      return (max);
    v_x = x - b;
    v_y = y - b;
    for (int a = 0; a < b * 2; a += 1)
      {
	v_y = y - b;
	for (int t = 0; t < b * 2; t += 1)
	  {
	    if (this->areIn(v_x, v_y) == true)
	      if (this->onCircle(v_x, v_y, x, y, b) == true)
		if (this->valueAt(v_x, v_y) > max)
		  max = this->valueAt(v_x, v_y);
	    v_y += 1;
	  }
	v_x += 1;
      }
    return (max);
  }

  bool			onCircle(int x, int y, int cx, int cy, int b)
  {
    int			vx;
    int			vy;
    double		v;
   
    vx = x - cx;
    vy = y - cy;
    v = sqrt(vx * vx + vy * vy);
    return (v <= (double)(b));
  }


 public:

  unsigned int            getHeight() const
  {
    return (this->height);
  }

  unsigned int            getWidth() const
  {
    return (this->width);
  }

 private:

  T			*data;
  unsigned int		height;
  unsigned int		width;
};

#endif // GRAYSCALEIMAGE_H
