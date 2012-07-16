/*a simple class to implement matrices
 * provides basic operations
 * T => float,double,long long int,int
 */

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

template < class T >
class matrix
{
  
private:
  
  vector< vector<T> > matrix_elements; 
  int num_row;
  int num_col;
  
public:
  
  matrix<T>(int row,int col)
  {
    num_row=row;
    num_col=col;
  }
  
  matrix<T>(const matrix<T> &temp)
  {
    num_row=temp.num_row;
    num_col=temp.num_col;
    for(int i=0;i<num_row;i++)
    {
      for(int j=0;j<num_col;j++)
      {
	matrix_elements[i][j]=temp.matrix_elements[i][j];
      }
    }
  }
  
  bool check_invalid()
  {
    if(num_row==0 && num_col==0)
      return 1;
    else
      return 0;
  }
  
  /*operators and functions
   * % every element of the matrix by a constant
   * addition
   * subtraction
   * multiplication
   * transpose
   */
  
  void operator%(int mod);
  
  matrix<T> operator+(matrix<T> param);
  matrix<T> operator-(matrix<T> param);
  matrix<T> operator*(matrix<T> param);
  matrix<T> transpose();
  
  friend ostream& operator<<(ostream& out,matrix<T> param)
  {
    for(int i=0;i<param.num_row;i++)
    {
      for(int j=0;j<param.num_col;j++)
      {
	out<<param.matrix_elements[i][j]<<" ";
      }
      out<<"\n";
    }
  }
  
};

template < class T >
void matrix<T>::operator%(int mod)
{
  for(int i=0;i<num_row;i++)
  {
    for(int j=0;j<num_col;j++)
    {
      matrix_elements[i][j]=matrix_elements[i][j]%mod;
    }
  }
}

template < class T >
matrix<T> matrix<T>::operator+(matrix<T> param)
{
  if(num_row!=param.num_row || num_col!=param.num_col)
  {
    cout<<"These matrices cannot be added\n";
    return matrix<T>(0,0);
  }
  
  matrix<T> ret(num_row,num_col);
  for(int i=0;i<num_row;i++)
  {
    for(int j=0;j<num_col;j++)
    {
      ret.matrix_elements[i][j]=matrix_elements[i][j]+param.matrix_elements[i][j];
    }
  }
  return ret;
}

template < class T >
matrix<T> matrix<T>::operator-(matrix<T> param)
{
  if(num_row!=param.num_row || num_col!=param.num_col)
  {
    cout<<"These matrices cannot be subtracted\n";
    return matrix<T>(0,0);
  }
  
  matrix<T> ret(num_row,num_col);
  for(int i=0;i<num_row;i++)
  {
    for(int j=0;j<num_col;j++)
    {
      ret.matrix_elements[i][j]=matrix_elements[i][j]+param.matrix_elements[i][j];
    }
  }
  return ret;
}

template < class T >
matrix<T> matrix<T>::operator*(matrix<T> param)
{
  if(num_col!=param.num_row)
  {
    cout<<"These matrices cannot be multiplied\n";
    return matrix<T>(0,0);
  }
  
  matrix<T> ret(num_row,num_col);
  for(int i=0;i<num_row;i++)
  {
    for(int j=0;j<param.num_col;j++)
    {
      ret.matrix_elements[i][j]=0;
      for(int k=0;k<num_col;k++)
      {
	ret.matrix_elements[i][j]+=matrix_elements[i][k]*param.matrix_elements[k][j];
      }
    }
  }
  return ret;
}

template < class T >
matrix<T> matrix<T>::transpose()
{
  matrix ret(num_row,num_col);
  for(int i=0;i<num_row;i++)
  {
    for(int j=0;j<num_col;j++)
    {
      ret.matrix_elements[i][j]=matrix_elements[j][i];
    }
  }
  return ret;
}