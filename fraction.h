#include<vector>
#include<map>
#include<cstdio>
#include<cmath>
#include<iostream>

using namespace std;

vector<long long int> prime;
map<int,map<int,int> > dp_factor;

void find_prime()
{
  vector<bool> seive(1000010,0);
  long long int i,j;
  for(i=2;i*i<1000010;i++)
  {
    if(seive[i]==0)
    {
      for(j=2;j*i<1000010;j++)
  seive[i*j]=1;
    }
  }
  for(i=2;i<seive.size();i++)
  {
    if(seive[i]==0)
      prime.push_back(i);
  }
}

map<int,int> factorize(int a)
{
  map<int,int> factor;
  int i=0,x=a;
  while(a>1 && i<prime.size())
  {
    while(a%prime[i]==0)
    {
      if(dp_factor.find(a)!=dp_factor.end())
      {
	factor=factor+dp_factor[a];
	dp_factor[x]=factor;
	a=0;
	break;
      }
      factor[prime[i]]++;
      a/=prime[i];
    }
    i++;
  }
  return factor;
}

int gcd(int a,int b)
{
  if(b==0)
    return a;
  else
    return gcd(b,a%b);
}

int extended_euclid(int a,int b,int &x,int &y)
{
  if(b==0)
  {
    x=1;
    y=0;
    return a;
  }
  int gcd=extended_euclid(b,a%b,x,y),x_=x;
  x=y;
  y=x_-(a/b)*y;
  return gcd;
}

template < class T >
T modular_exponentiation(T base,T exponent,T mod)
{
  T result=1;
  while(exponent)
  {
    if(exponent&1)
      result=(result*base)%mod;
    if(exponent>>=1)
      result=(result*result)%mod;    
  }
  return result;
}

inline double short_exp(int a,int b)
{
  return exp(b*log(a));
}

int euler_totient(int a)
{
  map<int,int> x=factorize(a);
  float result=a;
  for(map<int,int>::iterator mit=x.begin();mit!=x.end();mit++)
  {
    printf("%d ",mit->first);
    result*=(1.0-1.0/float(mit->first));
  }
  return result;
}

int no_of_div(int a)
{
  map<int,int> x=factorize(a);
  int result=1;
  for(map<int,int>::iterator mit=x.begin();mit!=x.end();mit++)
  {
    result*=(1+(mit->second));
  }
  return result;
}
  
void modular_linear_equ_solver(int a,int b,int n)
{
  int x,y;
  int d=extended_euclid(a,n,x,y);
  if(b%d==0)
  {
    int x0=(x*(b/d))%n;
    if(x0<0)
      x0+=n;
    for(int i=0;i<d;i++)
      printf("%d ",(x0+i*(n/d))%n);
  }
  else
    printf("\nno solutions\n");
}
  
void modular_inverse(int a,int n)
{
  modular_linear_equ_solver(a,1,n);
}