#include<cstdio>
#include"complex.h"
#include<cmath>

using namespace std;

int main()
{
  float x,y,a,b;
  scanf("%f %f %f %f",&x,&y,&a,&b);
  complex A(x,y),B(a,b),C=A+B;
  //C.print();
  /*C=A*B;
  C.print();
  C=A-B;
  C.print();
  C=A/B;
  C.print();*/
  C=A%B;
  C.print();
  return 0;
}
