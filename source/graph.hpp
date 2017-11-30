#include <iostream>
#include<fstream>
#include <vector>
#include <string>

class Vertex{
public:
  int id;
  int saturation;
  int degree;
  int color;
  bool colored;
  Vertex(){};
};

class Graph{
int vertices_number;
int* vertex_colors;
Vertex* vertices;
int** adjacent_matrix;
bool check_colorability(std::vector<Vertex>);
bool search_color_adjacent(const int,const int);
bool search_color_adjacent(const int,const int,Vertex*);
bool search_color_adjacent_grasp(const int,const int,std::vector<Vertex>);
bool search_color_adjacent_dsatur(const int,const int);
bool check_vertices_color(const int,const int,int*);
void change_vertices_color(const int,const int,int*);
bool vertex_left();
void sum_adjacent_saturation(const int);
void sum_adjacent_saturation(const int,std::vector<Vertex>&);
void print_graph_coloring();
int count_colors(Vertex*);
int count_colors_grasp(std::vector<Vertex>);
void order_vertices(char);
void order_vertices(char,std::vector<Vertex>&);
Vertex* grasp_constructor();

public:
  Vertex* heuristic_constructor();
  void vnd();
  void neighbourhood_search();
  Vertex* dsatur();
  void grasp();
  Graph();

};
