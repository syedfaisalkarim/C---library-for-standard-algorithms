#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

struct polynomial
{
  vector<int> coefficient;
  int degree;
};

float evaluate(polynomial a,int x)
{
  int i;
  float ans=0;
  for(int i=0;i<a.coefficient.size();i++)
    ans=(ans*x)+a.coefficient[i];
  return ans;
}

polynomial operator+(polynomial a,polynomial b)
{
  int i;
  polynomial c;
  c.degree=max(a.degree,b.degree);
  c.coefficient.resize(c.degree+1);
  for(i=0;i<a.coefficient.size() && i<b.coefficient.size();i++)
    c.coefficient[i]=a.coefficient[i]+b.coefficient[i];
  while(i<a.coefficient.size())
  {
    c.coefficient[i]=a.coefficient[i];
    i++;
  }
  while(i<b.coefficient.size())
  {
    c.coefficient[i]=b.coefficient[i];
    i++;
  }
  return c;
}

void input(polynomial &p)
{
  int i,n;
  cin>>p.degree;
  p.coefficient.resize(p.degree+1);
  for(i=0;i<p.coefficient.size();i++)
    cin>>p.coefficient[i];
  return;
}

void output(polynomial p)
{
  for(int i=0;i<p.coefficient.size();i++)
  {
    cout<<p.coefficient[i]<<" ";
  }
  return;
}

polynomial operator*(polynomial a,polynomial b)
{
  polynomial c;
  c.degree=a.degree+b.degree;
  c.coefficient.resize(c.degree+1);
  for(int i=0;i<c.coefficient.size();i++)
  {
    c.coefficient[i]=0;
    for(int k=0;k<=i;k++)
      c.coefficient[i]+=a.coefficient[k]*b.coefficient[i-k];
  }
  return c;
}
