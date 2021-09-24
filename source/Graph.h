#pragma once




class Graph
{
private:
	vector<vector<float>> adjacency_matrix;                           //adjacency matrix of graph
	static float const infinity;                                      //infinitely large weight of the edge
	
	Graph(const Graph&);                                              //constructor of copy
	Graph(Graph&&);                                                   //constructor of move
	Graph operator=(const Graph&)const;                               //= with copy
	Graph operator=(Graph&&) const;                                   //= with move
	string getTag(int);                                               //getting string tag by the vertex number
	bool stringRowToMatrixRow(string, int&);                          //user row to adjacency matrix row
	void clearMatrix();                                               //delete adjacency matrix of the graph
	int getIntTag(string);                                            //getting number of the vertex by string tag   
	void outputResultOfDijkstra(int, int, vector<int>, vector<float>);//output results of work of Dijkstra's algorithm
	

public:
	static enum { POSITIVE, NEGATIVE };         //positive or negative graph
	Graph();                                    //no-argument constructor
	~Graph();                                   //no-argument destructor
	bool keyboardInput();                       //input graph from user by keyboard
	bool fileInput();                           //input graph from file
	void generation(bool flag);                 //generation of random graph
	void output();                              //output adjacency matrix of the graph
	bool algorithmOfFloyd();                    //algorithm of Floyd
	bool algorithmOfDijkstra();                 //algorithm of Dijkstra
	bool rarefiedGraphAlgorithmOfDijkstra();    //algorithm of Dijkstra for rarefied graphs
};

