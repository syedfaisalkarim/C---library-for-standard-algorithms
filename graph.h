#include<cstdio>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<set>
#include<algorithm>
#include<map>
#include<iostream>

#define si(n) {scanf("%d",&n);}
#define ss(n) {scanf("%s",n);}
#define sf(n) {scanf("%f",n);}
#define foru(i,a,b) for(i=a;i<b;i++)
#define ford(i,a,b) for(i=a;i>=b;i--)
#define vi vector<int> 
#define pii pair<int,int> 
#define pb push_back
#define mp make_pair

using namespace std;

void dfs(vector<list<int> >& graph)
{
  int i,temp,time=1;
  vector<int> included,d,f,p;
  stack<int> gray;
  list<int>::iterator lit;
  included.resize(graph.size(),0);
  d.resize(graph.size(),0);
  f.resize(graph.size(),0);
  p.resize(graph.size(),0);
  for(i=0;i<graph.size();i++)
  {
    if(included[i]==0)
    {
      d[i]=time;
      time++;
      p[i]=-1;
      printf("discovery time of %d :- %d \n",i,d[i]);
      printf("parent of %d :- %d \n",i,p[i]);
      gray.push(i);
      included[i]=1;
      while(!gray.empty())
      {
	temp=gray.top();
	printf("%d ",temp);
	for(lit=graph[temp].begin();lit!=graph[temp].end();lit++)
	{
	  if(included[*(lit)]==0)
	  {
	    d[*(lit)]=time;
	    time++;
	    p[*(lit)]=temp;
	    printf("discovery time of %d :- %d \n",*(lit),d[*(lit)]);
	    printf("parent of %d :- %d \n",*(lit),p[*(lit)]);
	    gray.push(*(lit));
	    included[*(lit)]=1;
	    break;
	  }
	}
	if(lit==graph[temp].end())
	{
	  f[temp]=time;
	  time++;
	  printf("finish time of %d :- %d \n",temp,f[temp]);
	  gray.pop();
	}
      }
      f[i]=time;
      time++;
      printf("finish time of %d :- %d \n",i,f[i]);
    }
  }
}

void bfs(vector<list<int> >& graph)
{
  int temp;
  vector<int> included,d,p; 
  queue<int> gray;
  list<int>::iterator lit;
  included.resize(graph.size(),0);
  d.resize(graph.size(),0);
  p.resize(graph.size(),0);
  gray.push(0);
  included[0]=1;
  d[0]=1;
  p[0]=-1;
  while(!gray.empty())
  {
    temp=gray.front();
    gray.pop();
    printf("%d ",temp);
    for(lit=graph[temp].begin();lit!=graph[temp].end();lit++)
    {
      if(included[*(lit)]==0)
      {
	d[*(lit)]=d[temp]+1;
	p[*(lit)]=temp;
	printf("discovery time of %d :- %d \n",*(lit),d[*(lit)]);
	printf("parent of %d :- %d \n",*(lit),p[*(lit)]);
	gray.push(*(lit));
	included[*(lit)]=1;
      }
    }
  }
}

int bipartite_matching(vector<list<int> >& graph)
{
  int temp,i;
  vector<int> included;
  vector<bool> flag;
  queue<int> gray;
  list<int>::iterator lit;
  included.resize(graph.size(),0);
  flag.resize(graph.size(),0);
  gray.push(0);
  included[0]=1;
  flag[0]=0;
  while(!gray.empty())
  {
    temp=gray.front();
    gray.pop();
    for(lit=graph[temp].begin();lit!=graph[temp].end();lit++)
    {
      if(included[*(lit)]==0)
      {
	flag[*(lit)]=!flag[temp];
	gray.push(*(lit));
	included[*(lit)]=1;
      }
      else
      {
	if(flag[temp]==flag[*(lit)])
	  return 0;
      }
    }
  }
  printf("\n");
  for(i=0;i<graph.size();i++)
  {
    if(flag[i])
      printf("%d ",i);
  }
  printf("\n");
  for(i=0;i<graph.size();i++)
  {
    if(!flag[i])
      printf("%d ",i);
  }
  return 1;
}


int topological_sort(vector<list<int> >& graph)
{
  int i,temp;
  vector<int> included,sorted;
  stack<int> gray;
  list<int>::iterator lit;
  included.resize(graph.size(),0);
  for(i=0;i<graph.size();i++)
  {
    if(included[i]==0)
    {
      gray.push(i);
      included[i]=2;
      while(!gray.empty())
      {
	temp=gray.top();
	for(lit=graph[temp].begin();lit!=graph[temp].end();lit++)
	{
	  if(included[*(lit)]==0)
	  {
	    gray.push(*(lit));
	    included[*(lit)]=2;
	    break;
	  }
	  else if(included[*(lit)]==2)
	  {
	    return 0;
	  }
	}
	if(lit==graph[temp].end())
	{
	  sorted.push_back(temp);
	  included[temp]=1;
	  gray.pop();
	}
      }
    }
  }
  printf("\n");
  for(i=sorted.size()-1;i>=0;i--)
    printf("%d ",sorted[i]);
  return 1;
}

void ssc(vector<list<int> >& graph)
{
  int i,temp;
  vector<int> included,new_v;
  stack<int> gray;
  list<int>::iterator lit;
  included.resize(graph.size(),0);
  for(i=0;i<graph.size();i++)
  {
    if(included[i]==0)
    {
      gray.push(i);
      included[i]=1;
      while(!gray.empty())
      {
	temp=gray.top();
	for(lit=graph[temp].begin();lit!=graph[temp].end();lit++)
	{
	  if(included[*(lit)]==0)
	  {
	    gray.push(*(lit));
	    included[*(lit)]=1;
	    break;
	  }
	}
	if(lit==graph[temp].end())
	{
	  new_v.push_back(temp);
	  gray.pop();
	}
      }
      new_v.push_back(i);
    }
  }
  vector<list<int> > transpose(graph.size());
  for(i=0;i<graph.size();i++)
  {
    for(lit=graph[i].begin();lit!=graph[i].end();lit++)
      transpose[*(lit)].push_back(i);
  }
  included.clear();
  included.resize(transpose.size(),0);
  printf("\n");
  for(i=new_v.size()-1;i>=0;i--)
  {
    {
      printf("%d ",new_v[i]);
      gray.push(new_v[i]);
      included[new_v[i]]=1;
      while(!gray.empty())
      {
	temp=gray.top();
	for(lit=transpose[temp].begin();lit!=transpose[temp].end();lit++)
	{
	  if(included[*(lit)]==0)
	  {
	    gray.push(*(lit));
	    included[*(lit)]=1;
	    break;
	  }
	}
	if(lit==transpose[temp].end())
	{
	  gray.pop();
	}
      }
    }
  }  
}

vector<vector<int> > flloyd_warshall(vector<list<pair<int,int> > >& graph)
{
  int i,j,k;
  vector<vector<int> > original(graph.size());
  for(i=0;i<graph.size();i++)
  {
    original[i].resize(graph.size(),32000);
  }
  for(i=0;i<graph.size();i++)
  {
    original[i][i]=0;
    for(list<pair<int,int> >::iterator lit=graph[i].begin();lit!=graph[i].end();lit++)
    {
      original[i][(lit)->first]=(lit)->second;
    }
  }

  for(i=0;i<graph.size();i++)
  {
    for(j=0;j<graph.size();j++)
    {
      for(k=0;k<graph.size();k++)
      {
	if(original[i][j]>original[i][k]+original[k][j])
	  original[i][j]=original[i][k]+original[k][j];
      }
    }
  }
  return original;
}

void relax(int &a,int b,int c)
{
  if(a>b+c)
    a=b+c;
  return;
}

vector<int> bellman_ford(vector<list<pair<int,int> > >& graph)
{
  vector<int> d(graph.size(),32000);
  d[0]=0;
  int i,j;
  for(i=0;i<graph.size()-1;i++)
  {
    for(j=0;j<graph.size();j++)
    {
      for(list<pair<int,int> >::iterator lit=graph[j].begin();lit!=graph[j].end();lit++)
	relax(d[j],d[(lit)->first],(lit)->second);
    }
  }
  for(j=0;j<graph.size();j++)
  {
    for(list<pair<int,int> >::iterator lit=graph[j].begin();lit!=graph[j].end();lit++)
      if(d[j]>(d[(lit)->first]+(lit)->second))
      {
	cout<<"\n-ve wgt cycle\n";
	break;
      }
  }
  return d;
}

vector<int> dijkstra(vector<list<pair<int,int> > >& graph)
{
  int i;
  set<pair<int,int> > pq;
  vector<int>res(graph.size());
  for(i=1;i<graph.size();i++)
  {
    pq.insert(make_pair(32000,i));
    res[i]=32000;
  }
  pq.insert(make_pair(0,0));
  while(!pq.empty())
  {
    pair<int,int> temp=*(pq.begin());
    //printf("\n%d %d\n",temp.first,temp.second);
    res[temp.second]=temp.first;
    pq.erase(pq.begin());
    for(list<pair<int,int> >::iterator lit=graph[temp.second].begin();lit!=graph[temp.second].end();lit++)
    {
      if(res[(lit)->second]>res[temp.second]+((lit)->first))
      {
	pq.erase(pq.find(make_pair(res[(lit)->second],(lit)->second)));
	res[(lit)->second]=res[temp.second]+(lit)->first;
	pq.insert(make_pair(res[(lit)->second],(lit)->second));
      }
    }
  }
  return res;
}

vector<int> prim(vector<list<pair<int,int> > >& graph)
{
  int i;
  set<pair<int,int> > pq;
  vector<int> parent(graph.size()),res(graph.size());
  vector<bool> included(graph.size());
  for(i=1;i<graph.size();i++)
  {
    pq.insert(make_pair(32000,i));
    res[i]=32000;
    included[i]=0;
    parent[i]=-1;
  }
  pq.insert(make_pair(0,0));
  parent[0]=-1;
  res[0]=0;
  while(!pq.empty())
  {
    pair<int,int> temp=*(pq.begin());
    included[temp.second]=1;
    //printf("\n%d %d\n",temp.first,temp.second);
    pq.erase(pq.begin());
    for(list<pair<int,int> >::iterator lit=graph[temp.second].begin();lit!=graph[temp.second].end();lit++)
    {
      //printf("\n%d %d %d\n",res[(lit)->second],res[temp.second],(lit)->first);
      if(res[(lit)->second]>((lit)->first) && included[(lit)->second]==0)
      {
	pq.erase(pq.find(make_pair(res[(lit)->second],(lit)->second)));
	//printf("\n%d\n",res[(lit)->second]);
	parent[(lit)->second]=temp.second;
	res[(lit)->second]=(lit)->first;
	pq.insert(make_pair(res[(lit)->second],(lit)->second));
	//printf("\n%d\n",res[(lit)->second]);
      }
    }
  }
  return parent;
}

vector<int> dag_shortest_path(vector<list<pair<int,int> > >& graph)
{
  int i,temp;
  vector<int> included,sorted;
  stack<int> gray;
  list<pair<int,int> >::iterator lit;
  included.resize(graph.size(),0);
  for(i=0;i<graph.size();i++)
  {
    if(included[i]==0)
    {
      gray.push(i);
      included[i]=2;
      while(!gray.empty())
      {
	temp=gray.top();
	for(lit=graph[temp].begin();lit!=graph[temp].end();lit++)
	{
	  if(included[(lit)->second]==0)
	  {
	    gray.push((lit)->second);
	    included[(lit)->second]=2;
	    break;
	  }
	}
	if(lit==graph[temp].end())
	{
	  sorted.push_back(temp);
	  included[temp]=1;
	  gray.pop();
	}
      }
    }
  }
  vector<int> d(32000,graph.size());
  d[sorted[sorted.size()-2]]=0;
  for(i=sorted.size()-2;i>=0;i--)
  {
    for(list<pair<int,int> >::iterator lit2=graph[sorted[i]].begin();lit2!=graph[sorted[i]].end();lit2++)
      relax(d[(lit2)->second],d[sorted[i]],(lit2)->first);
  }
  return d;
}

map<int,int> belongs_to;

void merge_set(set<pair<int,int> >& a,set<pair<int,int> >& b)
{
  int x=(a.begin())->second;
  for(set<pair<int,int> >::iterator sit=b.begin();sit!=b.end();sit++)
  {
    a.insert(make_pair((sit)->first,x));
    belongs_to[(sit)->first]=x;
  }
  //printf("\n");
  for(set<pair<int,int> >::iterator sit=a.begin();sit!=a.end();sit++)
  {
    //printf("%d ",(sit)->first);
  }
  //printf("\n");
  b.clear();
}

vector<pair<int,int> > kruskal(vector<list<pair<int,int> > >& graph)
{
  vector<set<pair<int,int> > > forest;
  vector<pair<int,pair<int,int> > > edge;
  vector<pair<int,int> > tree;
  int i;
  for(i=0;i<graph.size();i++)
  {
    set<pair<int,int> > temp;
    temp.insert(make_pair(i,i));
    forest.push_back(temp);
    belongs_to[i]=i;
  }
  for(i=0;i<graph.size();i++)
  {
    for(list<pair<int,int> >::iterator lit=graph[i].begin();lit!=graph[i].end();lit++)
    {
      edge.push_back(make_pair((lit)->first,make_pair(i,(lit)->second)));
    }
  }
  sort(edge.begin(),edge.end());
  for(i=0;i<edge.size();i++)
  {
    //printf("\n%d %d\n",belongs_to[edge[i].second.first],belongs_to[edge[i].second.second]);
    /*for(int j=0;j<forest.size();j++)
     *    {
     *      printf("\nthis forest %d:-\n",j);
     *      for(set<pair<int,int> >::iterator sit=forest[j].begin();sit!=forest[j].end();sit++)
     *	printf("%d ",(sit)->first);
     *      printf("\n");
     }
     */
    if(belongs_to[edge[i].second.first]!=belongs_to[edge[i].second.second])
    {
      tree.push_back(make_pair(edge[i].second.first,edge[i].second.second));
      merge_set(forest[belongs_to[edge[i].second.first]],forest[belongs_to[edge[i].second.second]]);
    }
  }
  return tree;
}

map<pair<int,int>,int > cap,flow;
vector<int> h,e;
int dest;
int n,edge,t,i,x,y,z;

void push(int u,int v)
{
  int temp=min(e[u],cap[make_pair(u,v)]-flow[make_pair(u,v)]);
  flow[make_pair(u,v)]=flow[make_pair(u,v)]+temp;
  flow[make_pair(v,u)]=-flow[make_pair(u,v)];
  e[u]=e[u]-temp;
  e[v]=e[v]+temp;
}

void push_relabel(vector<vector<int> >& graph)
{
  h.resize(graph.size(),0);
  e.resize(graph.size(),0);
  h[0]=graph.size();
  for(i=0;i<graph[0].size();i++)
  {
    int v=graph[0][i];
    flow[make_pair(0,v)]=cap[make_pair(0,v)];
    flow[make_pair(v,0)]=-cap[make_pair(0,v)];
    e[v]=cap[make_pair(0,v)];
    e[0]-=cap[make_pair(0,v)];
  }
  queue<int> q;
  vector<bool> l(graph.size(),0);
  int u,v,m;
  for(int i=0;i<graph[0].size();i++)
  {
    if(graph[0][i]!=dest)
    {
      q.push(graph[0][i]);
      l[graph[0][i]]=1;
    }
  }
  while(!q.empty())
  {
    u=q.front();
    m=-1;
    for(int i=0;i<graph[u].size() && e[u]>0;i++)
    {
      v=graph[u][i];
      if(cap[make_pair(u,v)]-flow[make_pair(u,v)]>0)
      {
	if(h[u]>h[v])
	{
	  push(u,v);
	  if(l[v]==0 && v!=0 && v!=dest)
	  {
	    l[v]=1;
	    q.push(v);
	  }
	}
	else if(m==-1)
	  m=h[v];
	else
	  m=min(m,h[v]);
      }
    }
    if(e[u]!=0)
      h[u]=1+m;
    else
    {
      l[u]=0;
      q.pop();
    }
  }
}

void stable_matching()
{
  vector<queue<int> > men;
  vector<vector<int> > women;
  queue<int> single;
  vector<int> included;
  int t;
  si(t)
  while(t--)
  {
    int n;
    si(n);
    included.resize(n,-1);
    men.resize(n);
    women.resize(n);
    int i;
    foru(i,0,n)
    {
      int m;
      si(m);
      int j;
      int x;
      foru(j,0,m)
      {
	si(x);
	men[i].push(x-1);
      }
      single.push(i);
    }
    foru(i,0,n)
    {
      int m,j,x;
      si(m);
      foru(j,0,m)
      {
	si(x);
	women[i].push_back(x-1);
      }
    }
    while(!single.empty())
    {
      int x=single.front();
      single.pop();
      while(!men[x].empty())
      {
	int y=men[x].front();
	men[x].pop();
	if(included[y]==-1)
	{
	  included[y]=x;
	  break;
	}
	else
	{
	  if(find(women[y].begin(),women[y].end(),included[y])-women[i].begin()>find(women[y].begin(),women[y].end(),x)-women[i].begin())
	  {
	    single.push(included[y]);
	    included[y]=x;
	    break;
	  }
	}
      }
    }
    foru(i,0,n)
    {
      printf("\n%d %d\n",included[i],i+1);
    }
  }
}
