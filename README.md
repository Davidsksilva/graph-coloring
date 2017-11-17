# Graph Coloring

This code is a project for the discipline Analysis and Project of Algorithms, in the Federal University of Paraiba, Brazil.

## Introduction to the problem

In the Graph Coloring problem, we aim to color the verticies of a graph, in a way that two vertices of the same color are not adjacent to each other. Using the minimum number of colors possible.

## Solutions implemented

* **Greedy Coloring**
* **VND**
* **DSATUR**


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
