# shortest paths at graph

![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/rrtty0/shortest_paths_at_graph)
![GitHub last commit](https://img.shields.io/github/last-commit/rrtty0/shortest_paths_at_graph)
![GitHub contributors](https://img.shields.io/github/contributors/rrtty0/shortest_paths_at_graph)

Realisation of [Graph](https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)), which provides an interface for create and work with this structure, and have functions for finding the shortest path at graph with several algorithms:
- [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
- [Dijkstra's algorithm for rarefied graphs](https://e-maxx.ru/algo/dijkstra_sparse)
- [Floyd's algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

It can be used as a library C++.

## Installation
- The sources for Graph can be downloaded from the [Github repo](https://github.com/rrtty0/shortest_paths_at_graph.git).

* You can either clone the public repository:
```
        $ git clone https://github.com/rrtty0/shortest_paths_at_graph.git 
```
## Usage

This project may be used as a library with functionality and realisation of Graph and finding shortest paths ay graphs for your project. For it, move files [Graph.h](./source/Graph.h) and [Graph.cpp](./source/Graph.cpp) at project's work directory, include [Graph.h](./source/Graph.h) as a header file at your source, like that:
```C++
# include "Graph.h"

//your code...
```

## How to Contribute
1. _Clone_ repo and _create_ a new branch:
```
        $ git clone https://github.com/rrtty0/shortest_paths_at_graph.git
        $ git branch name_for_new_branch
        $ git checkout name_for_new_branch
```
2. _Make changes_ and test
3. _Submit Pull Request_ with comprehensive description of changes