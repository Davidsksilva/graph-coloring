#include "graph.hpp"
#include <iostream>

int main(){
  Graph graph;
  graph.heuristic_constructor();
  //graph.neighbourhood_search();
  std::cout<<std::endl;
  graph.dsatur();
  return 0;
}
