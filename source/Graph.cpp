#include "stdafx.h"
#include "Graph.h"


//infinitely large weight of the edge
const float Graph::infinity = 10000;

//no-argument constructor
Graph::Graph()
{
}

//input graph from user by keyboard
bool Graph::keyboardInput()
{
	string current_row;
	
	int num = 0;
	int n;

	cout << "Input adjacency matrix: \n";
	do
	{
		cout << "Node " << getTag(num++) << ": ";
		getline(cin, current_row);
		if (!stringRowToMatrixRow(current_row, n))
			return false;
	}
	while (adjacency_matrix.size() != n);
	
	return true;
}

//input graph from file
bool Graph::fileInput()
{
	string str;
	ifstream file("input.txt");
	int n;

	if (file)
	{
		while (getline(file, str))
		{
			if (!stringRowToMatrixRow(str, n))
				return false;
			if (n < adjacency_matrix.size())
			{
				cout << "Error! Number of rows must be = " << n << endl;
				clearMatrix();
				return false;
			}
		}
	}
	file.close();

	return true;
}

//user row to adjacency matrix row
bool Graph::stringRowToMatrixRow(string current_row, int& n)
{
	regex reg_row("(( )*(((-)?\\d{1,2}(,\\d{1,2})?)|-)( )+)+");
	regex reg_length("((-)?\\d{1,2}(,\\d{1,2})?)|-");
	cmatch result;
	
	current_row += " ";
	if (regex_match(current_row.c_str(), result, reg_row))
	{
		sregex_iterator begin = sregex_iterator(current_row.begin(), current_row.end(), reg_length);
		sregex_iterator i = begin;

		if (adjacency_matrix.size() == 0)
			n = distance(begin, sregex_iterator());
		else
			if (n != distance(begin, sregex_iterator()))
			{
				cout << "Error! Number of elements in the row must be = " << n << endl;
				clearMatrix();
				return false;
			}
		adjacency_matrix.resize(adjacency_matrix.size() + 1);
		for (i; i != sregex_iterator(); ++i)
		{
			smatch m = *i;
			try
			{
				//if current symbol is -
				if (m.str()[0] == '-' && m.str().length() == 1)
					adjacency_matrix[adjacency_matrix.size() - 1].push_back(infinity);
				else
				{
					float num = stof(m.str());
					adjacency_matrix[adjacency_matrix.size() - 1].push_back(num);
				}
			}
			catch (exception e)
			{
				cout << "Error! Float can not contain so much!" << endl;
				clearMatrix();
				return false;
			}
		}
	}
	else
	{
		cout << "Error! The entered string is not valid!" << endl;
		clearMatrix();
		return false;
	}

	return true;
}

//generation of random graph
void Graph::generation(bool flag)
{
	int size = rand() % 4 + 2;
	
	for (int i = 0; i < size; ++i)
	{
		short int row = rand();
		adjacency_matrix.resize(adjacency_matrix.size() + 1);
		for (int j = 0; j < size; ++j)
		{
			float value = ((row >> size - 1 - j) & 1);
			if (!value)
				adjacency_matrix[i].push_back(infinity);
			else
			{
				value *= ((rand() % 100) + 0.01 * (rand() % 100));
				if (flag && i != j)
					value *= pow(-1, rand() % 2);
				adjacency_matrix[i].push_back(value);
			}
		}
	}
}

//getting string tag by the vertex number
string Graph::getTag(int v)
{
	string str;
	int i = 0, k = 0, res;
	
	if (v <= 25)
		return str + char('A' + v % 26);

	v++;

	while (v >= pow(26, k + 1))
		++k;
	
	while (i != k)
	{
		v /= pow(26, i != 0);
		res = v % 26;
		if (res < 1)
			res += 26;
		str = char('A' + (res - 1)) + str;
		v -= res;
		++i;
	}

	if (v == 0)
		return str;

	str = char('A' + (v / 26 - 1)) + str;

	return str;
}

//getting number of the vertex by string tag
int Graph::getIntTag(string str)
{
	regex pattern("[A-Z]+");
	cmatch m;
	int result = 0;

	if (!regex_match(str.c_str(), m, pattern))
		return -1;

	for (int i = 0; i < str.length(); ++i)
		result += pow(26, str.length() - i - 1)*(str[i] - 'A' + 1);
	--result;

	return result;
}

//no-argument destructor
Graph::~Graph()
{
}

//output adjacency matrix of the graph
void Graph::output()
{
	for (int i = 0; i < adjacency_matrix.size(); ++i)
	{
		cout << "Node " << getTag(i) << ":  ";
		for (int j = 0; j < adjacency_matrix[i].size(); ++j)
			if (adjacency_matrix[i][j] == infinity)
				cout << "inf" << "\t";
		    else
				cout << adjacency_matrix[i][j] << "\t";
		cout << "\n";
	}
}

//delete adjacency matrix of the graph
void Graph::clearMatrix()
{
	for (int i = 0; i < adjacency_matrix.size(); ++i)
		adjacency_matrix[i].clear();
	adjacency_matrix.clear();
}

//algorithm of Floyd
bool Graph::algorithmOfFloyd()
{
	vector<vector<float>> current_matrix = adjacency_matrix;
	vector<vector<int>> pre(adjacency_matrix.size(), vector<int>(adjacency_matrix.size()));
	string input_string;
	int start;
	int finish;
	bool negative_cycle = false;

	cout << "\nInput tags of nodes:\nstart: ";
	cin >> input_string;
	start = getIntTag(input_string);
	
	if (start == -1 || start >= adjacency_matrix.size())
	{
		cout << "Error! Tag is not valid!";
		return false;
	}

	cout << "finish: ";
	cin >> input_string;
	finish = getIntTag(input_string);

	if (finish == -1)
	{
		cout << "Error! Tag is not valid!";
		return false;
	}

	for (int i = 0; i < adjacency_matrix.size(); ++i)
		for (int j = 0; j < adjacency_matrix.size(); ++j)
			if (adjacency_matrix[i][j] != infinity)
				pre[i][j] = i;
			else
				pre[i][j] = -1;
	
	
	for (int k = 0; k < current_matrix.size(); ++k)
	{
		for (int i = 0; i < current_matrix.size(); ++i)
			for (int j = 0; j < current_matrix.size(); ++j)
				if (current_matrix[i][k] < infinity && current_matrix[k][j] < infinity && (current_matrix[i][j] > (current_matrix[i][k] + current_matrix[k][j])))
				{
					current_matrix[i][j] = current_matrix[i][k] + current_matrix[k][j];
					if (i == j && current_matrix[i][j] < 0)
						negative_cycle = true;
					pre[i][j] = pre[k][j];
				}
		for (int i = 0; i < current_matrix.size(); ++i)
		{
			for (int j = 0; j < current_matrix[i].size(); ++j)
				if (current_matrix[i][j] == infinity)
					cout << "inf" << "\t\t";
				else
					cout << current_matrix[i][j] << "\t\t";
			cout << "\n";
		}

		cout << "\n\n";
	}

	system("pause");
	cout << "\nMatrix with shortest paths:\n\n";
	for (int i = 0; i < current_matrix.size(); ++i)
	{
		for (int j = 0; j < current_matrix[i].size(); ++j)
			if (current_matrix[i][j] == infinity)
				cout << "inf" << "\t\t";
			else
				cout << current_matrix[i][j] << "\t\t";
		cout << "\n";
	}

	if (negative_cycle)
		cout << "\nThis graph contains negative weight cycle!\n";

	for (int t = 0; t < adjacency_matrix.size(); ++t)
		if (current_matrix[t][t] < 0 && current_matrix[start][t] != infinity && current_matrix[t][finish] != infinity)
		{
			cout << "\nShortest path from " << getTag(start) << " to " << getTag(finish) << " is not exist, because exist negative weight cycle between them in node: " << getTag(t);
			return true;
		}

	cout << "\nShortest path from " << getTag(start) << " to " << getTag(finish) << " ";
	if (current_matrix[start][finish] == infinity)
		cout << "is not exist!";
	else
	{
		cout << "is " << current_matrix[start][finish] << "\n";
		vector<int> path;
		int cur = finish;
		while (cur != -1 && cur != start)
		{
			path.push_back(cur);
			cur = pre[start][cur];
		}
		path.push_back(cur);
		reverse(path.begin(), path.end());
		cout << "\nShortest path is: ";
		for (int i = 0; i < path.size() - 1; ++i)
			cout << getTag(path[i]) << " -> ";
		cout << getTag(path[path.size() - 1]);
	}

	return true;
}

//algorithm of Dijkstra
bool Graph::algorithmOfDijkstra()
{
	vector<float> shortest_paths(adjacency_matrix.size(), infinity);
	vector<bool> not_cased(adjacency_matrix.size(), true);
	vector<int> pre(adjacency_matrix.size(), -1);
	string input_node;
	int cur_minimum_case = infinity;
	int start;
	int finish;
	int cur_node;
	
	
	cout << "\nInput tags of nodes:\nstart: ";
	cin >> input_node;
	start = getIntTag(input_node);

	if (start == -1 || start >= adjacency_matrix.size())
	{
		cout << "Error! Tag is not valid!" << endl;
		return false;
	}
	
	cur_node = start;
	
	cout << "finish: ";
	cin >> input_node;
	finish = getIntTag(input_node);

	if (finish == -1 || finish >= adjacency_matrix.size())
	{
		cout << "Error! Tag is not valid!" << endl;
		return false;
	}
	
	shortest_paths[cur_node] = 0;
	for (int i = 0; i < adjacency_matrix.size(); ++i)
	{
		not_cased[cur_node] = false;
		for (int i = 0; i < adjacency_matrix.size(); ++i)
			if (not_cased[i] && adjacency_matrix[cur_node][i] != infinity && (adjacency_matrix[cur_node][i] + shortest_paths[cur_node]) < shortest_paths[i])
			{
				shortest_paths[i] = adjacency_matrix[cur_node][i] + shortest_paths[cur_node];
				pre[i] = cur_node;
			}
		
		cur_minimum_case = infinity;
		for (int i = 0; i < adjacency_matrix.size(); ++i)
			if (not_cased[i] && shortest_paths[i] < cur_minimum_case)
			{
				cur_minimum_case = shortest_paths[i];
				cur_node = i;
			}
	}

	outputResultOfDijkstra(start, finish, pre, shortest_paths);
		
	return true;
}

//algorithm of Dijkstra for rarefied graphs
bool Graph::rarefiedGraphAlgorithmOfDijkstra()
{
	vector<float> shortest_paths(adjacency_matrix.size(), infinity);
	set<pair<int, int>> not_used;
	vector<int> pre(adjacency_matrix.size(), -1);
	string input_node;
	int cur_minimum_case = infinity;
	int start;
	int finish;
	int cur_node;


	cout << "\nInput tags of nodes:\nstart: ";
	cin >> input_node;
	start = getIntTag(input_node);

	if (start == -1 || start >= adjacency_matrix.size())
	{
		cout << "Error! Tag is not valid!" << endl;
		return false;
	}

	cout << "finish: ";
	cin >> input_node;
	finish = getIntTag(input_node);

	if (finish == -1 || finish >= adjacency_matrix.size())
	{
		cout << "Error! Tag is not valid!" << endl;
		return false;
	}

	not_used.insert(make_pair(0, start));
	shortest_paths[start] = 0;

	while (!not_used.empty())
	{
		cur_node = not_used.begin()->second;
		not_used.erase(not_used.begin());
		for (int v = 0; v < adjacency_matrix.size(); ++v)
		{
			if (shortest_paths[cur_node] + adjacency_matrix[cur_node][v] < shortest_paths[v])
			{
				not_used.erase(make_pair(shortest_paths[v], v));
				shortest_paths[v] = shortest_paths[cur_node] + adjacency_matrix[cur_node][v];
				pre[v] = cur_node;
				not_used.insert(make_pair(shortest_paths[v], v));
			}
		}
	}
	outputResultOfDijkstra(start, finish, pre, shortest_paths);

	return true;
}

//output results of work of Dijkstra's algorithm 
void Graph::outputResultOfDijkstra(int start, int finish, vector<int> pre, vector<float> shortest_paths)
{
	for (int i = 0; i < adjacency_matrix.size(); ++i)
	{
		cout << "\nShortest path from " << getTag(start) << " to " << getTag(i) << ": ";
		if (shortest_paths[i] == infinity)
			cout << "inf";
		else
			cout << shortest_paths[i];
	}


	if (shortest_paths[finish] == infinity)
		cout << "\n\nFrom " << getTag(start) << " to " << getTag(finish) << " path is not exist!";
	else
	{
		vector<int> path;
		for (int i = finish; i != start; i = pre[i])
			path.push_back(i);
		path.push_back(start);

		reverse(path.begin(), path.end());

		cout << "\n\nShortest path from " << getTag(start) << " to " << getTag(finish) << " is: ";

		for (int i = 0; i < path.size() - 1; ++i)
			cout << getTag(path[i]) << " -> ";
		cout << getTag(path[path.size() - 1]);
	}
}
