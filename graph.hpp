#include <iostream>
#include<fstream>
#include <vector>

class Graph{
int vertex_number;
int* vertex_colors;
int** adjacent_matrix;
bool search_color_adjacent(const int,const int);
bool check_vertices_color(const int,const int,int*);
void change_vertices_color(const int,const int,int*);
void print_graph_coloring();
int count_colors(int*);
public:
  int* heuristic_constructor();
  void neighbourhood_search();
  Graph();

};
