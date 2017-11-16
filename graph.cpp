#include "graph.hpp"
#include "readmatrix.hpp"
#include <vector>
#include <algorithm>
#include <limits.h>

Graph::Graph(){
  vertices_number= getMatrixSize("teste.txt");
  adjacent_matrix = readMatrix(vertices_number,"teste.txt");
  vertex_colors = new int[vertices_number];
  vertices = new Vertex[vertices_number];
  for(int i=0;i<vertices_number;i++){
    vertex_colors[i]=-1;
    vertices[i].color=-1;
    vertices[i].saturation=0;
    vertices[i].id=i;
    vertices[i].degree=0;
    vertices[i].colored=false;
  }

  for(int i=0;i<vertices_number;i++){
    for(int j=0;j<vertices_number;j++){
      if(adjacent_matrix[i][j] != 0){
        vertices[i].degree++;
      }
    }
  }
}
bool Graph::vertex_left(){
  for(int i=0;i<vertices_number;i++){
    if(vertices[i].colored == false)
      return true;
  }
  return false;
}
void Graph::order_vertices(char op){
  switch(op){
    case 's':{
      int a;
      Vertex temp;
      for(int i=0;i<vertices_number;i++){
        a=i;
        for(int j=i+1;j<vertices_number;j++){
          if(vertices[j].saturation > vertices[a].saturation)
            a=j;
          else if(vertices[j].saturation == vertices[a].saturation){
            if(vertices[j].degree > vertices[a].degree)
              a=j;
          }
        }
        temp=vertices[i];
        vertices[i]=vertices[a];
        vertices[a]=temp;
      }
      break;
    }
    case 'd':{
      int a;
      Vertex temp;
      for(int i=0;i<vertices_number;i++){
        a=i;
        for(int j=i+1;j<vertices_number;j++){
          if(vertices[j].degree > vertices[a].degree)
            a=j;
        }
        temp=vertices[i];
        vertices[i]=vertices[a];
        vertices[a]=temp;
      }
      break;
    }
  }
}
void Graph::sum_adjacent_saturation(const int id){
  for(int i=0;i<vertices_number;i++){
    if(adjacent_matrix[id][i] != 0){
      for(int j=0;j<vertices_number;j++){
        if(!vertices[j].colored && vertices[j].id == i){
          vertices[j].saturation++;
        }
      }
    }
  }
}
void Graph::dsatur(){
  order_vertices('d');
  vertices[0].colored=true;
  vertices[0].saturation= INT_MIN;
  sum_adjacent_saturation(vertices[0].id);
  vertices[0].color=0;
  std::cout<<vertices[0].id+1<<std::endl;
  order_vertices('s');
  while(vertex_left()){
    for(int i=0;i<vertices_number;i++){
      if(!vertices[i].colored){
        vertices[i].colored=true;
        vertices[i].saturation= INT_MIN;
        sum_adjacent_saturation(vertices[i].id);
        int proposed_color=0;
        while(search_color_adjacent_dsatur(vertices[i].id,proposed_color)){
          proposed_color++;
        }
        vertices[i].color=proposed_color;
      }
      break;
    }
    order_vertices('s');
  }

  for(int i=0;i<vertices_number;i++){
    std::cout<<"V"<<vertices[i].id+1<<" C"<<vertices[i].color<<std::endl;
  }
}
int Graph::count_colors(int* color_array){
  std::vector<int> aux;
  int colors=0;
  for(int i=0;i<vertices_number;i++){
    if(!(std::find(aux.begin(), aux.end(), color_array[i]) != aux.end())){
      aux.push_back(color_array[i]);
      colors++;
    }
  }
  return colors;
}
void Graph::print_graph_coloring(){
  for(int k=0;k<vertices_number;k++)
  {
    std::cout<<"V"<<k+1<<" C"<<vertex_colors[k]<<std::endl;
  }
}
bool Graph::search_color_adjacent(const int id,const int color){
  for(int j=0;j<vertices_number;j++){
    if(adjacent_matrix[id][j] != 0)
    {
      if(vertex_colors[j] == color)
        return true;
    }
  }
  return false;
}
bool Graph::search_color_adjacent_dsatur(const int id,const int color){
  for(int j=0;j<vertices_number;j++){
    if(adjacent_matrix[id][j] != 0)
    {
      for(int i=0;i<vertices_number;i++){
        if(vertices[i].id == j && vertices[i].color == color){
            return true;
        }
      }
    }
  }
  return false;
}

int* Graph::heuristic_constructor(){
    for(int i=0;i<vertices_number;i++){
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
  for(int i=0;i<vertices_number;i++){
    if(vertex_colors[i] == color_in){
      if(search_color_adjacent(i,color_out))
        return false;
    }
  }
  return true;
}
void Graph::neighbourhood_search(){
  std::vector<int> excluded_colors;
 int* optimized_vertex_colors=heuristic_constructor();
 int color_count=count_colors(optimized_vertex_colors);
 std::cout<<"Initial colors: "<<color_count<<std::endl;
 for(int i=0;i<color_count;i++){
   for(int j=0;j<color_count;j++){
     if((i!=j) && !(std::find(excluded_colors.begin(), excluded_colors.end(), j) != excluded_colors.end())){
       if(check_vertices_color(i,j,optimized_vertex_colors)){
         for(int k=0;k<vertices_number;k++){
           if(optimized_vertex_colors[k] == i){
             optimized_vertex_colors[k]=j;
             excluded_colors.push_back(i);
           }
         }
       }
     }
   }
 }
 color_count=count_colors(optimized_vertex_colors);
std::cout<<"Final colors: "<<color_count<<std::endl;
}
