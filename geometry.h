#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<set>


#define si(n) {scanf("%d",&n);}
#define ss(n) {scanf("%s",n);}
#define sf(n) {scanf("%lf",&n);}
#define foru(i,a,b) for(i=a;i<b;i++)
#define ford(i,a,b) for(i=a;i>=b;i--)
#define vi vector<int> 
#define pii pair<int,int> 
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define forc(it, c) for(typeof(c.begin()) it=c.begin(); it!=c.end(); ++it)
#define eps 1e-9

using namespace std;

const double pi=3.14;

class point
{
public:
  double x,y;
  point()
  {
    x=y=0;
  }
  point(double a,double b)
  {
    x=a;
    y=b;
  }
};

point operator-(point a,point b)
{
  return point(a.x-b.x,a.y-b.y);
}

point operator+(point a,point b)
{
  return point(a.x+b.x,a.y+b.y);
}

point operator*(point a,point b)
{
  return point(a.x*b.x,a.y*b.y);
}

int operator%(point a,point b)
{
  return (a.x*b.y)-(a.y*b.x);
}

bool operator<(point a,point b)
{
  if(a.x<b.x)
    return 1;
  else if(a.x==b.x && a.y<b.y)
    return 1;
  return 0;
}

int direction(point a,point b,point c)
{
  return (c-a)%(b-a);
}

double dist(point a,point b)
{
  return sqrt(fabs((a.x-b.x)*(a.x-b.x)+(a.x-b.x)*(a.x-b.x)));
}

class line
{
public:
  double a,b,c;
  line(point x,point y)
  {
    if(x.x==y.x)
    {
      a=1;
      b=0;
      c=-x.x;
    }
    else
    {
      b=1;
      a=-(x.y-y.y)/(x.x-y.x);
      c=-(a*x.x)-(b*x.y);
    }
  }
  line(point p,double m)
  {
    a=-m;
    b=1;
    c=-(a*p.x)+(b*p.y);
  }
};

bool is_parallel(line l1,line l2)
{
  return ((fabs(l1.a-l2.a)<= eps) && (fabs(l1.b-l2.b)<= eps));
}

bool same_line(line l1,line l2)
{
  return (is_parallel(l1,l2) && (fabs(l1.c-l2.c)<= eps));
}

point intersection_point(line l1,line l2)
{
  point p;
  if(same_line(l1,l2))
  {
    printf("\nsame line\n");
    return p;
  }
  if(is_parallel(l1,l2))
  {
    printf("\nparallel lines\n");
    return p;
  }
  p.x=(l2.b*l1.c-l1.b*l2.c)/(l2.a*l1.b-l1.a*l2.b);
  if(fabs(l1.b)> eps)
    p.y=-(l1.a*p.x+l1.c)/l1.b;
  else
    p.y=-(l2.a*p.x+l2.c)/l2.b;
  return p;
}

double intersection_angle(line l1,line l2)
{
  return atan((l1.a*l2.b-l2.a*l1.b)/(l1.a*l2.a-l1.b*l2.b));
}

line perpendicular_line(line l1,point a)
{
  if(fabs(l1.a)>eps)
  {
    line temp(a,l1.b/l1.a);
    return temp;
  }
  else
  {
    point b;
    b.x=a.x;
    b.y=l1.c;
    line temp(a,b);
    return temp;
  }
}

point closest_point(line l1,point p)
{
  line perp=perpendicular_line(l1,p);
  return intersection_point(l1,perp);
}

point reflection(point p,line l)
{
  line temp=perpendicular_line(l,p);
  point p1=intersection_point(l,temp);
  return p1-(p-p1);
}

point rotation(point p,point o,double theta)
{
  return point(((p.x-o.x)*cos(theta)-(p.y-o.y)*sin(theta))+o.x,((p.x-o.x)*sin(theta)+(p.y-o.y)*cos(theta))+o.y);
}

double signed_triangle_area(point a,point b,point c)
{
  return ( float(a.x*b.y-a.y*b.x+a.y*c.x-a.x*c.y+b.x*c.y-c.x*b.y)/2.0);
}

double triangle_area(point a,point b,point c)
{
  return fabs(signed_triangle_area(a,b,c));
}

class polygon
{
public:
  int n;
  vector<point> vertex;
  polygon(int a)
  {
    n=a;
    vertex.resize(n);
  }
  polygon()
  {
    n=0;
  }
};

class triangulation
{
public:
  int n;
  vector<int*> t;
  int curr[2];
  triangulation(polygon poly)
  {
    int i;
    n=poly.n;
    t.resize(n);
    foru(i,0,n)
      t[i]=new int[3];
    vector<bool> included(n,0);
    curr[0]=0;
    curr[1]=1;
    bool flag=1;
    i=2;
    int k=0;
    while(flag)
    {
      if(included[i]==0)
      {
	if(direction(poly.vertex[curr[0]],poly.vertex[curr[1]],poly.vertex[i])>0)
	{
	  included[curr[1]]=1;
	  t[k][0]=curr[0];
	  t[k][1]=curr[1];
	  t[k][2]=i;
	  k++;
	  curr[1]=i;
	  i++;
	}
	else
	{
	  curr[0]=i;
	  curr[1]=(i+1)%n;
	  i=(i+2)%n;
	}
      }
      else
	i++;
      i=i%n;
      int j,count=0;
      printf("\n");
      foru(j,0,n)
      {
	if(included[j]==0)
	  count++;
	printf("%d",(int)included[j]);
      }
      printf("\n");
      if(count<=2)
	flag=0;
    }
  }
};

double area(polygon poly)
{
  double total=0.0;
  int i,j;
  foru(i,0,poly.n)
  {
    j=(i+1)%poly.n;
    total+=(poly.vertex[i].x*poly.vertex[j].y)-(poly.vertex[j].x*poly.vertex[i].y);
  }
  return total/2.0;
}


bool on_segment(point a,point b,point c)
{
  return (min(a.x,b.x)<=c.x && c.x<=max(a.x,b.x) && min(a.y,b.y)<=c.y && c.y<=max(a.y,b.y));
}

bool segment_intersect(point a,point b,point c,point d)
{
  int d1=direction(c,d,a), d2=direction(c,d,b), d3=direction(a,b,c), d4=direction(a,b,d);
  if(((d1>0 && d2<0) || (d1<0 && d2>0)) && ((d3>0 && d4<0) || (d3<0 && d4>0)))
    return 1;
  else if(d1==0 && on_segment(c,d,a))
    return 1;
  else if(d2==0 && on_segment(c,d,b))
    return 1;
  else if(d3==0 && on_segment(a,b,c))
    return 1;
  else if(d4==0 && on_segment(a,b,d))
    return 1;
  else
    return 0;
}

struct line_segment
{
  point a,b;
  friend bool operator<(line_segment,line_segment);
};

bool operator<(line_segment l1,line_segment l2)
{
  if(l1.a.x<l2.a.x)
    return 1;
  else if(l1.a.y<l2.a.y)
    return 1;
  return 0;
}

bool operator!=(point p1,point p2)
{
  if(p1.x!=p2.x || p1.y!=p2.y)
    return 1;
  return 0;
}

bool operator!=(line_segment l1,line_segment l2)
{
  if(l1.a!=l2.a || l1.b!=l2.b)
    return 1;
  return 0;
}

bool any_segment_intersect(vector<line_segment>& l)
{
  set<line_segment> curr;
  set<line_segment>::iterator sit,sup,sdown;
  vector<pair<point,pair<int,int> > > p;
  for(int i=0;i<l.size();i++)
  {
    p.push_back(make_pair(l[i].a,make_pair(i,0)));
    p.push_back(make_pair(l[i].b,make_pair(i,1)));
  }
  sort(p.begin(),p.end());
  for(int i=0;i<p.size();i++)
  {
    if(p[i].second.second==0)
    {
      sit=(curr.insert(l[p[i].second.first])).first;
      sit++;
      sup=sit;
      sit--;
      if(sup!=curr.end() && segment_intersect((sit)->a,(sit)->b,(sup)->a,(sup)->b))
      {
	return 1;
      }
      if(sit!=curr.begin())
      {
	sit--;
	sdown=sit;
	sit++;
	if(segment_intersect((sit)->a,(sit)->b,(sdown)->a,(sdown)->b))
	{
	  return 1;
	}
      }
    }
    else
    {
      sit=curr.find(l[p[i].second.first]);
      sit++;
      sup=sit;
      sit--;
      if(sit!=curr.begin())
      {
	sit--;
	sdown=sit;
	sit++;
	if(sup!=curr.end() && sit!=curr.begin() && segment_intersect((sup)->a,(sup)->b,(sdown)->a,(sdown)->b))
	{
	  return 1;
	}
      }
      curr.erase(l[p[i].second.first]);
    }
  }
  return 0;
}

vector<point> graham_convex_hull(vector<point> all_points)
{
  point p0=all_points[0];
  int i,n=all_points.size();
  for(i=1;i<all_points.size();i++)
  {
    if(all_points[i]<p0)
      p0=all_points[i];
  }
  vector<pair<pair<double,double>,int> > polar(n-1),fin_polar(n-1);
  double r,theta;
  for(i=1;i<n;i++)
  {
    r=sqrt((all_points[i].x-p0.x)*(all_points[i].x-p0.x)+(all_points[i].y-p0.y)*(all_points[i].y-p0.y));
    if(all_points[i].x==p0.x)
      theta=pi/2;
    else
      theta=atan((all_points[i].y-p0.y)/(all_points[i].x-p0.x));
    polar.push_back(make_pair(make_pair(theta,r),i));
  }
  sort(polar.begin(),polar.end());
  for(i=0;i<n-2;i++)
  {
    while(polar[i].first.second==polar[i+1].first.second)
      i++;
    fin_polar.push_back(polar[i]);
  }
  vector<point> c_hull;
  c_hull.push_back(p0);
  c_hull.push_back(all_points[fin_polar[0].second]);
  c_hull.push_back(all_points[fin_polar[1].second]);
  for(i=2;i<n-1;i++)
  {
    while(c_hull.size()>1 && direction(c_hull[c_hull.size()-2],c_hull[c_hull.size()-1],all_points[fin_polar[i].second])>=0)
      c_hull.pop_back();
    c_hull.push_back(all_points[fin_polar[i].second]);
  }
  return c_hull;
}

pii closest;
double shortest_dist;
vector<pair<double,int> > x,y;
vector<point> p;

void closest_point(int s,int e)
{
  int mid=(s+e)/2;
  if(s-e<=2)
  {
    int i;
    foru(i,s+1,e+1)
    {
      if(dist(p[x[i].second],p[x[i-1].second])<shortest_dist)
      {
	shortest_dist=dist(p[x[i].second],p[x[i-1].second]);
	closest=mp(x[i].second,x[i-1].second);
	printf("\n%d %d\n",x[i].second,x[i-1].second);
      }
    }
  }
  else
  {
    int mid=(s+e)/2,i;
    vi left;
    vector<pair<double,int> > temp1,temp2;
    foru(i,s,e+1)
    {
      left.push_back(x[i].second);
    }
    foru(i,s,e+1)
    {
      if(find(left.begin(),left.end(),y[i].second)!=left.end())
	temp1.push_back(y[i]);
      else
	temp2.push_back(y[i]);
    }
    i=s;
    forc(vit,temp1)
    {
      y[i]=*(vit);
      i++;
    }
    forc(vit,temp2)
    {
      y[i]=*(vit);
      i++;
    }
    closest_point(s,mid-1);
    closest_point(mid,e);
    foru(i,s,e+1)
    {
      int j;
      for(j=0;j<7 && i+j<=e;j++)
      {
	if(dist(p[x[i].second],p[x[j].second])<shortest_dist)
	{
	  shortest_dist=dist(p[x[i].second],p[x[j].second]);
	  closest=mp(x[i].second,x[j].second);
	  printf("\n%d %d\n",x[i].second,x[j].second);
	}
      }
    }
  }
}