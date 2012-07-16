#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<map>
#include "numberthoery.h"

using namespace std;


/*string matching algo - O(n*m)
 * converts strings into numerical representation
 * since it can be very big numbers are stored mod of some prime chosen
 * if the main string and substring match numerically at point i then the expansion of the strings are compared to determine the match
 */

int rabin_karp_matcher(string main_str,string sub,int alpha_size,long long int mod)
{
  int main_str_size=main_str.size(),sub_size=sub.size(),count=0;
  
  long long int h=modular_exponentiation(alpha_size,sub_size-1,mod);
  long long int sub_num_representation=0,main_str_num_representation=0;
  /* h - the coefficient of the most significant character in the substring
   * sub_num_representation - stores numerical representation of substring
   * main_str_num_representation - stores numerical representation of main string
   */
  
  
  //initializes sub_num_representation and main_str_num_representation
  for(int i=0;i<sub_size;i++)
  {
    sub_num_representation=(alpha_size*sub_num_representation+(sub[i]-'a'))%mod;
    main_str_num_representation=(alpha_size*main_str_num_representation+(main_str[i]-'a'))%mod;
  }
  
  
  //iterate through main string checking if equal to substring numerically
  for(int main_str_idx=0;main_str_idx<=main_str_size-sub_size;main_str_idx++)
  {
    //if numerically equal then actual strings are matched to determine class
    if(sub_num_representation==main_str_num_representation)
    {
      bool possible_match=1;
      for(int k=0,l=main_str_idx;k<sub_size;k++,l++)
      {
	if(sub[k]!=main_str[l])
	{
	  possible_match=0;
	}
      }
      if(possible_match)
      {
	count++;
	printf("\npattern occurs with shift:- %d\n",main_str_idx);
      }
    }
    
    
    if(main_str_idx<main_str_size-sub_size)
    {
      main_str_num_representation=(alpha_size*(main_str_num_representation-(main_str[main_str_idx]-'a')*h)
                                   + (main_str[main_str_idx+sub_size]-'a'))%mod;
    }
  
    
  }
  return count;
}


/*creates the automata for the given substring - O(n*alpha_size)
 * here transitions are made in the automata such that delta(q,a) = length of largest prefix 
 */
map<pair<char,int>,int > compute_transition_function(string sub,vector<char> alphabet)
{
  map<pair<char,int>,int > automata;
  int sub_size=sub.size();
  pair<char,int> temp;
  for(int q=0;q<=sub_size;q++)
  {
    for(int i=0;i<alphabet.size();i++)
    {
      int k=min(sub_size+1,q+2);
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


/*string matching algorithm - O(n*alpha_size + n)
 * computes the automata for the substring in O(n*alpha_size)
 * then checks if substring satisfying the automata exists in main string
 */
int finite_automaton_matcher(string main_str,string sub,vector<char> alphabet)
{
  int main_str_size=main_str.size(),sub_size=sub.size(),curr_idx,count=0;
  
  //automata representing the substring
  map<pair<char,int>,int > delta=compute_transition_function(sub,alphabet);
  
  for(int i=0;i<main_str_size;i++)
  {
    pair<char,int> temp;
    temp.first=main_str[i];
    temp.second=curr_idx;
    curr_idx=delta[temp];
    //transition from prev state to current state based on the character and curr position in substring automata
    if(curr_idx==sub_size)
    {
      printf("\npattern occurs with shift :-%d",i-m+1);
      count++;
    }
  }
  
  return count;
}

vector<int> compute_prefix_function(string param)
{
  int param_size=param.size(),k=0;
  vector<int> pre(param_size,0);
  pre[0]=0;
  for(int q=1;q<param_size;q++)
  {
    while(k>0 && param[k]!=param[q])
      k=pre[k];
    if(param[k]==param[q])
      k++;
    pre[q]=k;
  }
  return pre;
}

int kmp_matcher(string main_str,string sub)
{
  int main_str_size=main_str.size(),sub_size=sub.size(),curr_idx=0,count=0;
  vector<int> pre=compute_prefix_function(sub);
  
  for(int i=0;i<main_str_size;i++)
  {
    while(curr_idx>0 && sub[curr_idx]!=main_str[i])
      curr_idx=pre[curr_idx-1];
    if(sub[curr_idx]==main_str[i])
      curr_idx++;
    if(curr_idx==sub_size-1)
    {
      printf("\npattern occurs with shift :- %d",i-sub_size+2);
      count++;
      curr_idx=pre[curr_idx-1];
    }
  }
  return count;
}


int lcs(string left_opr,string right_opr)
{
  int n=left_opr.size(),m=right_opr.size();
  vector<vector<int> > intermediate_cost(n+1);
  for(int i=0;i<=n;i++)
  {
    intermediate_cost[i].resize(m+1);
    intermediate_cost[i][0]=i;
  }
  for(int j=0;j<=m;j++)
  {
    intermediate_cost[0][j]=j;
  }
  
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      if(left_opr[i-1]==right_opr[j-1])
	intermediate_cost[i][j]=intermediate_cost[i-1][j-1]+1;
      else 
      {
	if(intermediate_cost[i-1][j]>intermediate_cost[i][j-1])
	  intermediate_cost[i][j]=intermediate_cost[i-1][j];
	else
	  intermediate_cost[i][j]=intermediate_cost[i][j-1];
      }
    }
  }
  
  return intermediate_cost[n][m];
}


int string_compare(string left_opr,string right_opr)
{
  int n=left_opr.size(),m=right_opr.size();
  int cost[3]
  vector<vector<int> > intermediate_cost(n+1);
  for(int i=0;i<=n;i++)
  {
    intermediate_cost[i].resize(m+1);
    intermediate_cost[i][0]=i;
  }
  for(int j=0;j<=m;j++)
  {
    intermediate_cost[0][j]=j;
  }
  
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      if(left_opr[i-1]==right_opr[j-1])
	cost[0]=intermediate_cost[i-1][j-1];
      else
	cost[0]=intermediate_cost[i-1][j-1]+1;
      cost[1]=intermediate_cost[i][j-1]+1;
      cost[2]=intermediate_cost[i-1][j]+1;
      intermediate_cost[i][j]=cost[0];
      for(int k=1;k<3;k++)
      {
	if(cost[k]<intermediate_cost[i][j])
	  intermediate_cost[i][j]=cost[k];
      }
    }
  }
  
  return intermediate_cost[n][m];
}