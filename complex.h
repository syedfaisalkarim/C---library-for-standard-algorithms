#include<cmath>

using namespace std;

class complex
{
  float r,i;
public:
  complex(float a,float b)
  {
    r=a;
    i=b;
  }
  friend complex operator+(complex a,complex b)
  {
    return complex(a.r+b.r,a.i+b.i);
  }
  friend complex operator-(complex a,complex b)
  {
    return complex(a.r-b.r,a.i-b.i);
  }
  friend complex operator*(complex a,complex b)
  {
    return complex(a.r*b.r-a.i*b.i,a.r*b.i+b.r*a.i);
  }
  friend complex operator/(complex a,complex b)
  {
    return complex((a.r*b.r+a.i*b.i)/(b.r*b.r+b.i*b.i),-a.r*b.i+b.r*a.i/(b.r*b.r+b.i*b.i));
  }
  friend complex operator%(complex a,complex b)
  {
    complex c=a/b;
    c.r=floor(c.r);
    c.i=floor(c.i);
    return (a-(c)*b);
  }
  void print()
  {
    printf("\n%.2f+i%.2f\n",r,i);
  }
};