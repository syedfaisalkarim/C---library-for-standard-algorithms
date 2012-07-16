/*a simple class to use complex numbers
 * provides basic operations
 * T => float,double,long long int,int
 */

#include<cmath>
#include<iostream>

using namespace std;

template < class T >
class complex
{
  
private:
  T real,imaginary;
  
public:
  
  /*constructors
   */
  complex<T>(T a,T b)
  {
    real=a;
    imaginary=b;
  }
  
  complex<T>()
  {
    real=0;
    imaginary=0;
  }
  
  complex<T>(const complex<T> &temp)
  {
    real=temp.real;
    imaginary=temp.imaginary;
  }
  
  /*operators and functions:-
   * floor
   * absolute value
   * add
   * subtract
   * multiply
   * divide
   * modulus
   */
  
  void floor()
  {
    real=std::floor(real);
    imaginary=std::floor(imaginary);
  }
  
  //for explanation of functions below assume complex number of type:- <<  a+ib  >>
  
  
  /*absolute value of a+ib= a^2 + b^2
   */
  T abs()
  {
    return real*real+imaginary*imaginary;
  }
  
  /*c1 + c2= ( a1 + a2 ) + i( b1 + b2 )
   */
  complex operator+(complex<T> param)
  {
    return complex<T>(real+param.real,imaginary+param.imaginary);
  }
  
  /*c1 - c2= ( a1 - a2 ) + i( b1 - b2 )
   */
  complex operator-(complex<T> param)
  {
    complex<T> result(real-param.real,imaginary-param.imaginary);
    return result;
  }
  
  /*c1 * c2= ( a1 * a2 - b1 * b2 ) + i( a1 * b2 + a2 * b1 )
   */
  complex operator*(complex<T> param)
  {
    return complex<T>(real*param.real-imaginary*param.imaginary,real*param.imaginary+param.real*imaginary);
  }
  
  /*c1 / c2 = ( a1 * a2 + b1 * b2 ) / ( a2 *a2 + b2 * b2 ) - i( a1 * b2 + a2 * b1 ) / ( a2 *a2 + b2 * b2 )
   */
  complex operator/(complex<T> param)
  {
    return complex<T>((real*param.real+imaginary*param.imaginary)/(param.real*param.real+param.imaginary*param.imaginary),-real*param.imaginary+param.real*imaginary/(param.real*param.real+param.imaginary*param.imaginary));
  }
  
  complex operator%(complex<T> param)
  {
    complex<T> c;
    c=*(this)/param;
    c.floor();
    return complex<T>(*(this)-(c)*param);
  }
  
  friend ostream& operator<<(ostream& out,complex<T> param)
  {
    out<<param.real<<" + i"<<param.imaginary<<"\n";
  }
};