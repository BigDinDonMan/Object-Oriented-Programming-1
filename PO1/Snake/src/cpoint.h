#ifndef __CPOINT_H__
#define __CPOINT_H__

#include <list>

using namespace std;

struct CPoint
{
  int x;
  int y;
  CPoint(int _x=0, int _y=0): x(_x), y(_y) {};
  CPoint(const CPoint& other) : x(other.x), y(other.y){}
  CPoint& operator+=(const CPoint& delta)
  {
    x+=delta.x;
    y+=delta.y;
    return *this;
  }
  friend bool operator==(const CPoint& first, const CPoint& second) {
    return first.x == second.x && first.y == second.y;
  }
  void operator=(const CPoint& other) {
    this->x = other.x;
    this->y = other.y;
  }
};

struct CRect
{
  CPoint topleft;
  CPoint size;
  CRect(CPoint t1=CPoint(), CPoint s=CPoint()):
    topleft(t1), size(s) {};
};

#endif
