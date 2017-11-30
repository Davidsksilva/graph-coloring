#include "graph.hpp"
#include "readmatrix.hpp"
#include <vector>
#include <algorithm>
#include <limits.h>

Graph::Graph(){
  adjacent_matrix = ReadFile("inputs/qgorder30.col", &vertices_number);
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
Vertex* Graph::dsatur(){
  order_vertices('d');
  vertices[0].colored=true;
  vertices[0].saturation= INT_MIN;
  sum_adjacent_saturation(vertices[0].id);
  vertices[0].color=0;
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

  int color_count=count_colors(vertices);
  //print_graph_coloring();
  std::cout<<color_count<<std::endl;
  return vertices;
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
int Graph::count_colors_grasp(std::vector<Vertex> vector){
  std::vector<int> aux;
  int colors=0;
  for(unsigned int i=0;i<vector.size();i++){
    if(!(std::find(aux.begin(), aux.end(), vector[i].color) != aux.end())){
      aux.push_back(vector[i].color);
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
    std::cout<<"--------------CONSTRUCTOR-------------"<<std::endl;
    for(int i=0;i<vertices_number;i++){
      int proposed_color=0;
      while(search_color_adjacent(i,proposed_color)){
        proposed_color++;
      }
      vertices[i].color=proposed_color;
    }
    int color_count=count_colors(vertices);
    //print_graph_coloring();
    std::cout<<color_count<<std::endl;
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
  std::cout<<"--------------VND-------------"<<std::endl;
  int color_count=count_colors(base_solution);
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
  //print_graph_coloring();
  std::cout<<color_count<<std::endl;
}
void Graph::sum_adjacent_saturation(const int id,std::vector<Vertex> &vector){
  for(int i=0;i<vertices_number;i++){
    if(adjacent_matrix[id][i] != 0){
      for(unsigned int j=0;j<vector.size();j++){
        if(!vector[j].colored && vector[j].id == i){
          vector[j].saturation++;
        }
      }
    }
  }
}
bool Graph::search_color_adjacent(const int id,const int color,Vertex* arr){
  for(int j=0;j<vertices_number;j++){
    if(adjacent_matrix[id][j] != 0)
    {
      if(arr[j].color == color)
        return true;
    }
  }
  return false;
}
bool Graph::search_color_adjacent_grasp(const int id,const int color,std::vector<Vertex> vector){
  for(int j=0;j<vertices_number;j++){
    if(adjacent_matrix[id][j] != 0)
    {
      for(unsigned int i=0;i<vector.size();i++){
        if(vector[i].id == j && vector[i].color == color){
            return true;
        }
      }
    }
  }
return false;
}
void Graph::order_vertices(char op,std::vector<Vertex> &vector){
  switch(op){
    case 's':{
      int a;
      Vertex temp;
      for(unsigned int i=0;i<vector.size();i++){
        a=i;
        for(unsigned int j=i+1;j<vector.size();j++){
          if(vector[j].saturation > vector[a].saturation)
            a=j;
          else if(vector[j].saturation == vector[a].saturation){
            if(vector[j].degree > vector[a].degree)
              a=j;
          }
        }
        temp=vector[i];
        vector[i]=vector[a];
        vector[a]=temp;
      }
      break;
    }
    case 'd':{
      int a;
      Vertex temp;
      for(unsigned int i=0;i<vector.size();i++){
        a=i;
        for(unsigned int j=i+1;j<vector.size();j++){
          if(vector[j].degree > vector[a].degree)
            a=j;
        }
        temp=vector[i];
        vector[i]=vector[a];
        vector[a]=temp;
      }
      break;
    }
  }
}
bool Graph::check_colorability(std::vector<Vertex> vector){
  for(int i=0;i<vertices_number;i++){
    for(int j=0;j<vertices_number;j++){
    if(adjacent_matrix[i][j] != 0){
      for(unsigned int k=0;k<vector.size();k++){
        for(unsigned int u=0;u<vector.size();u++)
        if(vector[k].id == j && vector[u].id== i){
          if(vector[k].color == vector[u].color)
            return false;
        }
      }
    }
    }
  }
  return true;
}
void Graph::grasp()
{
  std::vector<Vertex> bestsolution;
  std::vector<Vertex> basesolutions;
  std::vector<int> solutions;
  int bsolution;
  std::cout<<"--------------GRASP-------------"<<std::endl;
  for( int p = 0; p < 50; p++ )
  {
    if(bestsolution.empty()){
      bsolution=INT_MAX;
    }
    else{
          bsolution= count_colors_grasp(bestsolution);
    }
    Vertex* basesolution= grasp_constructor();
    std::vector<Vertex> basesolution_;
    for( int i = 0; i < vertices_number; ++i )
      basesolution_.push_back( basesolution[i] );

    int solution = count_colors_grasp( basesolution_ );
    std::vector<int> actualcolors;

    for( int l = 0; l < vertices_number; ++l )
      if( !( std::find( actualcolors.begin(), actualcolors.end(), basesolution[l].color ) != actualcolors.end() ) )
        actualcolors.push_back( basesolution_[l].color );

    int i = rand()%(solution-0 + 1) + 0;

    if( !(std::find( actualcolors.begin(), actualcolors.end(), i ) != actualcolors.end()) )
      continue;

    for( int j = 0; j < vertices_number; ++j )
    {
      if( basesolution_[j].color == i )
      {
        for( int k = 0; k < solution; ++k )
        {
          if( k != i && ( std::find( actualcolors.begin(), actualcolors.end(), k ) != actualcolors.end() ) )
          {
            if( !search_color_adjacent_grasp( basesolution_[j].id, k, basesolution_ ) )
            {
              basesolution_[j].color = k;
              break;
            }
          }
        }
      }
    }

    for( int l = 0 ; l < vertices_number; ++l )
    {
      if( !( std::find( actualcolors.begin(), actualcolors.end(), basesolution_[l].color ) != actualcolors.end() ) )
      {
        actualcolors.push_back( basesolution_[l].color );
      }
    }
    int color_count = count_colors_grasp( basesolution_ );
    //std::cout <<color_count<<" "<<count_colors_grasp(bestsolution)<< std::endl;
    if( color_count < bsolution ){
          bestsolution=basesolution_;
    }

    std::cout<<count_colors_grasp(bestsolution)<< std::endl;
  }
  std::cout<<count_colors_grasp(bestsolution)<< std::endl;
  if(check_colorability(bestsolution))
    std::cout<<"apropriate colorability"<<std::endl;
  else
    std::cout<<"inaproprieate colorability"<<std::endl;

}
Vertex* Graph::grasp_constructor(){
  //order_vertices('s');
  //Inicializa a lista inicial de candidatos
  std::vector<Vertex> candidatos_iniciais;
  Vertex* solucao = new Vertex[vertices_number];
  for(int i=0;i<vertices_number;i++){
  solucao[i]=vertices[i];
  }
  for(int i=0;i<vertices_number;i++){
    candidatos_iniciais.push_back(solucao[i]);
  }
  //Loop do grasp
  while(candidatos_iniciais.size() != 0){
    int a;
    order_vertices('s',candidatos_iniciais);
    //Calcula o alfa
    a=(candidatos_iniciais[0].saturation + candidatos_iniciais[candidatos_iniciais.size()-1].saturation)*0.4;
    std::vector<Vertex> candidatos_restritos;
    // Lista restrita com apenas os vertices com saturacao >= a
    for(unsigned int i=0;i<candidatos_iniciais.size();i++){
      if(candidatos_iniciais[i].saturation >= a){
        candidatos_restritos.push_back(candidatos_iniciais[i]);
      }
    }
     // Pega um vertice randomico da lita restrita
    int randNum = rand()%(candidatos_restritos.size()-1-0 + 1) + 0;
    // Colore o vertice randomico
    {
      //Soma saturacao dos vertices adjacentes ao randomico
      sum_adjacent_saturation(candidatos_restritos[randNum].id,candidatos_iniciais);
      int proposed_color=0;
      //Procura vertices adjacentes ao randomico com cor=proposed_color
      while(search_color_adjacent(candidatos_restritos[randNum].id,proposed_color,solucao)){
        proposed_color++;
      }
      //Colore a vertice randomico no array final da solucao
      solucao[candidatos_restritos[randNum].id].color=proposed_color;
    }
    //Exclui o vertice randomico da lista inicial
    for(unsigned int i=0;candidatos_iniciais.size();i++){
      if(candidatos_iniciais[i].id == candidatos_restritos[randNum].id){
        candidatos_iniciais.erase(candidatos_iniciais.begin() + i);
        break;
      }
    }
  }
  //Exibe a coloracao
// int color_count=count_colors(vertices);
  //print_graph_coloring();
  //std::cout<<color_count<<std::endl;
  return solucao;
}
