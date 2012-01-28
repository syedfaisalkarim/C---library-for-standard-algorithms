#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class matrix
{
public:
  float mat[100][100];
  int n,m;
  matrix(int a,int b)
  {
    n=a;
    m=b;
  }
  friend matrix operator+(matrix a,matrix b);
  friend matrix operator*(matrix a,matrix b);
};

matrix operator+(matrix a,matrix b)
{
  matrix d(a.n,a.m);
  cout<<"\nim here\n";
  for(int i=0;i<d.n;i++)
  {
    for(int j=0;j<d.m;j++)
      d.mat[i][j]=a.mat[i][j]+b.mat[i][j];
  }
  return d;
}

matrix operator*(matrix a,matrix b)
{
  matrix d(a.n,b.m);
  for(int i=0;i<a.n;i++)
  {
    for(int j=0;j<b.m;j++)
    {
      d.mat[i][j]=0;
      for(int k=0;k<a.m;k++)
	d.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
    }
  }
  return d;
}

matrix transpose(matrix a)
{
  matrix d(a.n,a.m);
  cout<<"\nim here\n";
  for(int i=0;i<d.n;i++)
  {
    for(int j=0;j<d.m;j++)
      d.mat[i][j]=a.mat[j][i];
  }
  return d;
}

int det(matrix a)
{
  if(a.n==2 && a.m==2)
    return a.mat[0][0]*a.mat[1][1]-a.mat[0][1]*a.mat[1][0];
  int d=0,flag=1;
  matrix b(a.n-1,a.m-1);
  for(int i=0;i<a.m;i++)
  {
    for(int j=1,l=0;j<a.n;j++,l++)
    {
      for(int k=0,h=0;k<a.m;k++)
      {
	if(k==i)
	  continue;
	b.mat[l][h]=a.mat[j][k];
	h++;
      }
    }
    d+=(a.mat[0][i]*det(b))*flag;
    flag=(-1)*flag;
  }
  return d;
}

void lup_decomposition(matrix a)
{
  int n=a.n;
  int i,k,p=0,k_,j;
  vector<int> pi(n);
  for(i=0;i<n;i++)
    pi[i]=i;
  for(k=0;k<n;k++)
  {
    p=0;
    for(i=k;i<n;i++)
    {
      if(fabs(a.mat[i][k])>p)
      {
	p=fabs(a.mat[i][k]);
	k_=i;
      }
    }
    if(p<1e-10)
    {
      cout<<"\nerror singular matrix\n";
      return;
    }
    int temp;
    temp=pi[k];
    pi[k]=pi[k_];
    pi[k_]=temp;
    for(i=0;i<n;i++)
    {
      temp=a.mat[k][i];
      a.mat[k][i]=a.mat[k_][i];
      a.mat[k_][i]=temp;
    }
    for(i=k+1;i<n;i++)
    {
      a.mat[i][k]=a.mat[i][k]/a.mat[k][k];
      for(j=k+1;j<n;j++)
	a.mat[i][j]=a.mat[i][j]-a.mat[i][k]*a.mat[k][j];
    }
  }
  for(int f=0;f<n;f++)
  {
    cout<<"\n"<<pi[f]<<" ";
    for(int g=0;g<n;g++)
      cout<<a.mat[f][g]<<" ";
  }
  cout<<"\n";
  return;
}
