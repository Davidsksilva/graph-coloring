# Graph Coloring

This code is a project for the discipline Analysis and Project of Algorithms, in the Federal University of Paraiba, Brazil.

In this project, we aim to implement a heuristic to resolve the Graph Coloring problem.

## Introduction to the problem

In the Graph Coloring problem, we aim to color the verticies of a graph, in a way that two vertices of the same color are not adjacent to each other. Using the minimum number of colors possible.

![Vertex_Coloring](vertex_coloring.png)

You can see above a valid coloring for the graph.

## Algorithms implemented

* **Construction Heuristic** - Used to build a first coloring.
````
for each myvertex on the adjacent matrix
  mycolor = 0;
  while(there is a adjacent vertex colored with mycolor)
    mycolor++;
  myvertex.color = mycolor;
````
* **DSATUR**

* **VND** - Used to try to eliminate colors from an early coloring.
````
for each mycolor on the graph coloring
  for each myvertex colored with mycolor
    for each other proposedcolor on the graph coloring
      if(there is no adjacent vertex colored with proposedcolor && proposedcolor != mycolor && proposedcolor is colored in the graph)
        myvertex.color=proposedcolor;
        break;
    check which colors are on the graph
````



## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them

```
G++ or compatible installed.
```

### Installing

To run the code in LINUX, in the directoy file:

```
make
```

And next:

```
./build/graphcoloring
```

## Change input graph

There is a directory called inputs with a number of graphs to test, to change the graph that's going to be colored, in /source/graph.cpp , on Graph::Graph():

```
adjacent_matrix = ReadFile("inputs/input-name.col", &vertices_number);
```
With **input-name** being the name of the .col input to be tested.

To find more test inputs, click [Here](http://cse.unl.edu/~tnguyen/npbenchmarks/graphcoloring.html)

## Built With

* [Atom](https://atom.io/) - Used for code editting.

## Authors

* **David Simon**- [Davidsksilva](https://github.com/Davidsksilva)
* **Leoberto Soares**- [leossoaress](https://github.com/leossoaress)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
