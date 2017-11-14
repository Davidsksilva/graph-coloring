#include <iostream>
#include<fstream>
#include <vector>
#include "readmatrix.hpp"

struct Vertex{
  int color=-1;
};

void heuristic_constructor(int** adjacent_matrix,const int nVertices)
{
  Vertex vertex_array[nVertices];
  for(int i=0;i<nVertices;i++){ // matrix i
    vertex_array[i].color= 0;
    for(int j=0;j<nVertices;j++){ // matrix j
      if(adjacent_matrix[i][j] != 0) // if vertex is adjacent
      {
        if(vertex_array[j].color == vertex_array[i].color) //
          vertex_array[i].color++;
      }
    }
  }
  for(int k=0;k<nVertices;k++)
  {
    std::cout<<"V"<<k+1<<" C"<<vertex_array[k].color<<std::endl;
  }
}

int main(){
  int nVertices = getMatrixSize("teste.txt");
  int** adjacent_matrix;
  adjacent_matrix = readMatrix(nVertices ,"teste.txt");
  for(int i=0;i<nVertices;i++){ // matrix i
    for(int j=0;j<nVertices;j++){
      std::cout<<adjacent_matrix[i][j]<<" ";
    }
    std::cout<<std::endl;
    }
  heuristic_constructor(adjacent_matrix,nVertices);


}
