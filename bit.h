#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<string>
#include<algorithm>

#define si(n) {scanf("%d",&n);}
#define ss(n) {scanf("%s",n);}
#define sf(n) {scanf("%f",n);}
#define foru(i,a,b) for(i=a;i<b;i++)
#define ford(i,a,b) for(i=a;i>=b;i--)
#define vi vector<int> 
#define pii pair<int,int> 
#define pb push_back
#define mp make_pair
#define max_val 1000000
#define maxn 1000000
#define maxind 2500000

using namespace std;

int tree[max_val+2]={0},m[maxind],a[maxn];

int read(int idx)
{
  int sum=0;
  while(idx>0)
  {
    sum+=tree[idx];
    idx-=(idx&(-idx));
  }
  return sum;
}

void update(int idx,int val)
{
  while(idx<=max_val+1)
  {
    tree[idx]+=val;
    idx+=(idx&(-idx));
  }
}

int readsingle(int idx)
{
  int sum=tree[idx];
  if(idx>0)
  {
    int z=idx-(idx&(-idx));
    idx--;
    while(idx!=z)
    {
      sum-=tree[idx];
      idx-=(idx&(-idx));
    }
  }
  return sum;
}

void scale(int c)
{
  int i;
  foru(i,1,max_val+2)
    tree[i]=tree[i]/c;
}

int find(int cumfre)
{
  int idx=0;
  int bitmask,temp=max_val+1;
  while(temp)
  {
    bitmask=temp;
    temp-=(temp&(-temp));
  }
  while((bitmask!=0) && (idx<max_val))
  {
    int tidx=idx+bitmask;
    printf("\n%d %d\n",tidx,tree[tidx]);
    if(cumfre==tree[tidx])
      return tidx;
    else if(cumfre>tree[tidx])
    {
      idx=tidx;
      cumfre-=tree[idx];
    }
    bitmask>>=1;
  }
  if(cumfre!=0)
    return -1;
  else
    return idx;
}
