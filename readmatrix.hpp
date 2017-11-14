#include <iostream>
#include<fstream>
#include <vector>

int getMatrixSize(const char* input)
{
  int n;
  std::ifstream f(input);
  f >> n;
  return n;
}

int** readMatrix( const int n, const char* input)
{
  int **arr;
  arr = new int*[n];
  for(int i = 0; i < n; i++)
    arr[i] = new int[n];
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      arr[i][j]=0;
  std::ifstream f(input);
  int data;
  f >> data;
  for(int i=0;i<n-1;i++)
  {
    for(int j=i+1;j<n;j++)
    {
      f >> data;
      arr[i][j]=data;
      arr[j][i]=data;
    }
  }
  return arr;
}
