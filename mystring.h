#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

int modular_exponentiation(int a,int b,int m)
{
  int result=1;
  while(b)
  {
    if(b&1)
      result=(result*a)%m;
    if(b>>=1)
      result=(result*result)%m;    
  }
  return result;
}


int rabin_karp_matcher(string s,string sub,int d,int q)
{
  int i,n=s.size(),m=sub.size(),h=modular_exponentiation(d,m-1,q),p=0,t=0,count=0;
  for(i=0;i<m;i++)
  {
    p=(d*p+(sub[i]-'a'))%q;
    t=(d*t+(s[i]-'a'))%q;
  }
  cout<<"\n"<<p;
  for(i=0;i<=n-m;i++)
  {
    cout<<"\n"<<p<<" "<<t;
    if(p==t)
    {
      bool flag=1;
      for(int k=0,l=i;k<m;k++,l++)
      {
	if(sub[k]!=s[l])
	{
	  flag=0;
	  break;
	}
      }
      if(flag)
      {
	count++;
	printf("\npattern occurs with shift:- %d\n",i);
      }
    }
    if(i<n-m)
      t=(d*(t-(s[i]-'a')*h)+(s[i+m]-'a'))%q;
  }
  return count;
}

map<pair<char,int>,int > compute_transition_function(string sub,vector<char> alphabet)
{
  map<pair<char,int>,int > automata;
  int m=sub.size(),q;
  pair<char,int> temp;
  for(q=0;q<=m;q++)
  {
    for(int i=0;i<alphabet.size();i++)
    {
      int k=min(m+1,q+2);
      while(1)
      {
	bool flag=1;
	for(int f=0,g=0;f<k;f++,g++)
	{
	  if(sub[f]!=sub[g] && g<q)
	    flag=0;
	  else if(sub[f]!=alphabet[i])
	    flag=0;
	}
	if(flag)
	  break;
	k--;
      }
      temp.first=alphabet[i];
      temp.second=q;
      automata[temp]=k;
    }
  }
  return automata;
}

int finite_automaton_matcher(string s,map<pair<char,int>,int > delta,int m)
{
  int n=s.size(),q=0,i,count=0;
  for(i=0;i<n;i++)
  {
    pair<char,int> temp;
    temp.first=s[i];
    temp.second=q;
    q=delta[temp];
    if(q==m)
    {
      printf("\npattern occurs with shift :-%d",i-m+1);
      count++;
    }
  }
  return count;
}

vector<int> compute_prefix_function(string p)
{
  int m=p.size(),k=0;
  vector<int> pre(m,0);
  pre[0]=0;
  for(int q=1;q<m;q++)
  {
    while(k>0 && p[k]!=p[q])
      k=pre[k];
    if(p[k]==p[q])
      k++;
    pre[q]=k;
  }
  return pre;
}

int kmp_matcher(string s,string sub)
{
  int n=s.size(),m=sub.size(),q=0,count=0;
  vector<int> pre=compute_prefix_function(sub);
  printf("\n");
  for(int i=0;i<pre.size();i++)
    printf("%d ",pre[i]);
  printf("\n");
  for(int i=0;i<n;i++)
  {
    while(q>0 && sub[q]!=s[i])
      q=pre[q-1];
    if(sub[q]==s[i])
      q++;
    if(q==m-1)
    {
      printf("\npattern occurs with shift :- %d",i-m+2);
      count++;
      q=pre[q-1];
    }
  }
  return count;
}

void lcs(string a,string b)
{
  int n=a.size(),m=b.size(),i,j;
  printf("\n%d %d\n",n,m);
  vector<vi> c(n+1);
  foru(i,0,n+1)
    c[i].resize(m+1,0);
  foru(i,1,n+1)
  {
    foru(j,1,m+1)
    {
      if(a[i-1]==b[j-1])
	c[i][j]=c[i-1][j-1]+1;
      else 
      {
	if(c[i-1][j]>c[i][j-1])
	  c[i][j]=c[i-1][j];
	else
	  c[i][j]=c[i][j-1];
      }
    }
  }
  printf("\n%d\n",c[n][m]);
  return;
}

int string_compare(string a,string b)
{
  int cost[3],i,j;
  int n=a.size(),m=b.size();
  vector<vi> c(n+1);
  foru(i,0,n+1)
  {
    c[i].resize(m+1);
    c[i][0]=i;
  }
  foru(j,0,m+1)
    c[0][j]=j;
  foru(i,1,n+1)
  {
    foru(j,1,m+1)
    {
      if(a[i-1]==b[j-1])
	cost[0]=c[i-1][j-1];
      else
	cost[0]=c[i-1][j-1]+1;
      cost[1]=c[i][j-1]+1;
      cost[2]=c[i-1][j]+1;
      c[i][j]=cost[0];
      int k;
      foru(k,1,3)
      {
	if(cost[k]<c[i][j])
	  c[i][j]=cost[k];
      }
    }
  }
  printf("%d\n",c[n][m]);
}
