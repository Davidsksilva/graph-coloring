#include "graph.hpp"
#include "readmatrix.hpp"
#include <vector>
#include <algorithm>
#include <limits.h>

Graph::Graph(){
  adjacent_matrix = ReadFile("inputs/miles500.col", &vertices_number);
  vertices = new Vertex[vertices_number];
  for(int i=0;i<vertices_number;i++){
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
int Graph::count_colors(Vertex* vertices){
  std::vector<int> aux;
  int colors=0;
  for(int i=0;i<vertices_number;i++){
    if(!(std::find(aux.begin(), aux.end(), vertices[i].color) != aux.end())){
      aux.push_back(vertices[i].color);
      colors++;
    }
  }
  return colors;
}
void Graph::print_graph_coloring(){
  for(int i=0;i<vertices_number;i++)
  {
      std::cout<<"V"<<vertices[i].id+1<<" C"<<vertices[i].color<<std::endl;
  }
}
bool Graph::search_color_adjacent(const int id,const int color){
  for(int j=0;j<vertices_number;j++){
    if(adjacent_matrix[id][j] != 0)
    {
      if(vertices[j].color == color)
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

Vertex* Graph::heuristic_constructor(){
    for(int i=0;i<vertices_number;i++){
      int proposed_color=0;
      while(search_color_adjacent(i,proposed_color)){
        proposed_color++;
      }
      vertices[i].color=proposed_color;
    }
    print_graph_coloring();
    return vertices;
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
void Graph::vnd(){
  Vertex* base_solution=heuristic_constructor();
  int color_count=count_colors(base_solution);
  std::cout<<color_count<<std::endl;
  std::vector<int> actual_colors;
  for(int u=0;u<vertices_number;u++){
    if(!(std::find(actual_colors.begin(), actual_colors.end(),base_solution[u].color) != actual_colors.end())){
      actual_colors.push_back(base_solution[u].color);
    }
  }
  for(int i=0;i<color_count;i++){
    for(int j=0;j<vertices_number;j++){
      if(base_solution[j].color == i){
        for(int k=0;k<color_count;k++){
          if(k != i && ((std::find(actual_colors.begin(), actual_colors.end(),k) != actual_colors.end()))){
            if(!search_color_adjacent_dsatur(base_solution[j].id,k)){
              base_solution[j].color=k;
              break;
            }
          }
        }
      }
    }
    for(int u=0;u<vertices_number;u++){
      if(!(std::find(actual_colors.begin(), actual_colors.end(),base_solution[u].color) != actual_colors.end())){
        actual_colors.push_back(base_solution[u].color);
      }
    }
  }
  color_count=count_colors(base_solution);
  print_graph_coloring();
  std::cout<<color_count<<std::endl;
}
/*void Graph::neighbourhood_search(){
  std::vector<int> excluded_colors;
 Vertex* optimized_vertex=heuristic_constructor();
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
}*/
