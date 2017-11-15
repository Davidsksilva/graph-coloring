#include "graph.hpp"
#include "readmatrix.hpp"
#include <vector>
#include <algorithm>

Graph::Graph(){
  vertex_number= getMatrixSize("teste.txt");
  adjacent_matrix = readMatrix(vertex_number,"teste.txt");
  vertex_colors = new int[vertex_number];
  for(int i=0;i<vertex_number;i++){
    vertex_colors[i]=-1;
  }
}

int Graph::count_colors(int* color_array){
  std::vector<int> aux;
  int colors=0;
  for(int i=0;i<vertex_number;i++){
    if(std::find(aux.begin(), aux.end(), color_array[i]) != aux.end()){
      aux.push_back(color_array[i]);
      colors++;
    }
  }
  return colors;
}
void Graph::print_graph_coloring(){
  for(int k=0;k<vertex_number;k++)
  {
    std::cout<<"V"<<k+1<<" C"<<vertex_colors[k]<<std::endl;
  }
}
bool Graph::search_color_adjacent(const int id,const int color){
  for(int j=0;j<vertex_number;j++){
    if(adjacent_matrix[id][j] != 0)
    {
      if(vertex_colors[j] == color)
        return true;
    }
  }
  return false;
}

int* Graph::heuristic_constructor(){
    for(int i=0;i<vertex_number;i++){
      int proposed_color=0;
      while(search_color_adjacent(i,proposed_color)){
        proposed_color++;
      }
      vertex_colors[i]=proposed_color;
    }
    print_graph_coloring();
    return vertex_colors;
}
bool Graph::check_vertices_color(const int color_in,const int color_out,int* vertex_colors){
  for(int i=0;i<vertex_number;i++){
    if(vertex_colors[i] == color_in){
      if(search_color_adjacent(i,color_out))
        return false;
    }
  }
  return true;
}
void Graph::change_vertices_color(const int color_in, const int color_out, int * vertex_colors){
    if(check_vertices_color(color_in,color_out,vertex_colors)){

    }
}
void Graph::neighbourhood_search(){
 int* optimized_vertex_colors=heuristic_constructor();
 int color_count=count_colors(optimized_vertex_colors);
 int colors[color_count];
 for(int i=0;i<color_count;i++){
   colors[i]=i;
 }
 for(int i=0;i<color_count;i++){
   for(int j=0;j<color_count;j++){
     if(i!=j){
       if(check_vertices_color(i,j,optimized_vertex_colors)){
         for(int k=0;k<vertex_number;k++){
           if(optimized_vertex_colors[k] == i)
            optimized_vertex_colors[k]=j;
         }
       }
     }
   }
 }




}
