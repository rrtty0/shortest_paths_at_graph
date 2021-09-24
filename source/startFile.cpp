#include "Graph.h"

int main()
{
    srand(time(NULL));
    Graph graph;

    //graph.keyboardInput();
    graph.fileInput();
    //graph.generation(graph.NEGATIVE);
    graph.output();

    graph.algorithmOfDijkstra();
    //graph.rarefiedGraphAlgorithmOfDijkstra();
    //graph.algorithmOfFloyd();

    cout << "\n\n";
    system("pause");
    return 0;
}