#include<numbertheory.h>

class fraction
{
  int num,den;
  void normalize()
  {
    hcf=gcd(num,den);
    num=num/hcf;
    den=den/hcf;
  }
public:
  fraction(float a,float b)
  {
    num=a/gcd(a,b);
    den=b/gcd(a,b);
  }
  friend fraction operator+(fraction a,fraction b)
  {
    return fraction(a.num*b.den+b.num*a.den,a.den*b.den);
  }
  friend fraction operator-(fraction a,fraction b)
  {
    return fraction(a.num*b.den-b.num*a.den,a.den*b.den);
  }
  friend fraction operator*(fraction a,fraction b)
  {
    return fraction(a.num*b.num,a.den*b.den);
  }
  friend fraction operator/(fraction a,fraction b)
  {
    return fraction(a.num*b.den,a.den*b.num);
  }
  void print()
  {
    printf("\n%d/i%d\n",r,i);
  }
};