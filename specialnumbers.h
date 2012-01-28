#include<iostream>
#include<vector>

using namespace std;

vector<vector<unsigned long long int> > stirling_second,stirling_first,eulerian,combination,int_partition;
vector<double> harmonic;
vector<int> fibonnaci,catalan,factorial;

void harmonic_init(int n)
{
  harmonic.resize(n+1);
  harmonic[0]=0;
  for(int i=1;i<=n;i++)
    harmonic[i]=harmonic[i-1]+1/(double)i;
  return;
}

void fib_init(int n)
{
  fibonnaci.resize(n+1);
  fibonnaci[0]=0;
  fibonnaci[1]=1;
  for(int i=2;i<=n;i++)
    fibonnaci[i]=fibonnaci[i-1]+fibonnaci[i-2];
  return;
}

void stirling_second_init(int n,int k)
{
  int i,j;
  stirling_second.resize(n+1);
  for(i=0;i<=n;i++)
  {
    stirling_second[i].resize(k+1,0);
  }
  stirling_second[0][0]=1;
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=k && j<=i;j++)
      stirling_second[i][j]=j*stirling_second[i-1][j]+stirling_second[i-1][j-1];
  }
  return;
}

void stirling_first_init(int n,int k)
{
  int i,j;
  stirling_first.resize(n+1);
  for(i=0;i<=n;i++)
  {
    stirling_first[i].resize(k+1,0);
  }
  stirling_first[0][0]=1;
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=k && j<=i;j++)
      stirling_first[i][j]=(i-1)*stirling_first[i-1][j]+stirling_first[i-1][j-1];
  }
  return;
}

void eulerian_init(int n,int k)
{
  int i,j;
  eulerian.resize(n+1);
  for(i=0;i<=n;i++)
  {
    eulerian[i].resize(k+1,0);
    eulerian[i][0]=1;
  }
  eulerian[0][0]=1;
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=k && j<=i;j++)
      eulerian[i][j]=(j+1)*eulerian[i-1][j]+(i-j)*eulerian[i-1][j-1];
  }
  return;
}

void combination_init(int n,int k)
{
  int i,j;
  combination.resize(n+1);
  for(i=0;i<=n;i++)
  {
    combination[i].resize(k+1,0);
    combination[i][0]=combination[i][i]=1;
  }
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=k && j<=i;j++)
      combination[i][j]=combination[i-1][j]+combination[i-1][j-1];
  }
  return;
}

void int_partition_init(int n,int k)
{
  int i,j;
  int_partition.resize(n+1);
  for(i=0;i<=n;i++)
  {
    int_partition[i].resize(k+1,0);
    if(i==1)
      int_partition[1][1]=1;
    for(j=0;j<i;j++)
    {
      if(i-j>=0 && j-1>=0)
	int_partition[i][j]=int_partition[i-j][j]+int_partition[i][j-1];
    }
  }
  return;
}

void factorial_init(int n)
{
  int i,j;
  factorial.resize(n+1,0);
  factorial[0]=1;
  for(i=1;i<=n;i++)
  {
    factorial[i]=factorial[i-1]*i;
  }
  return;
}

void catalan_init(int n)
{
  int i,k;
  catalan.resize(n+1,0);
  catalan[0]=1;
  for(i=1;i<=n;i++)
  {
    for(k=0;k<=i-1;k++)
      catalan[i]+=catalan[k]*catalan[i-1-k];
  }
  return;
}

