#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
	int edgesList;
	int edgesMat;
	int nodes;
		vector<int> *adjList;
	int *adjMatrix;

public:
	void loadGraphList(string, int);
	void loadGraphMat(string, int, int);
	Graph(int);
	Graph();
	void addEdgeAdjMatrix(int, int);
	string printAdjList();
	string printAdjMat();
	string DFS(int, int);
	string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
	string BFS(int, int);
	string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
	string print_call(list<int>);
	string print_path(vector<vector<int>>&,int ,int);
	bool contains(list<int>, int);

};

void Graph::loadGraphList(string data, int a){
    nodes = a;
    adjList = new vector<int>[nodes];
    
    stringstream doc(data);
    char openParenthesis, comma, closeParenthesis;
    int x, y;

    while (doc >> openParenthesis >> x >> comma >> y >> closeParenthesis) {
        adjList[x].push_back(y);
        adjList[y].push_back(x);
        edgesList++;

    }
}

void Graph::loadGraphMat(string data, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	int x, y, i = 0;
	for (int i = 0; i < a*b; i++){adjMatrix[i] = 0;}
	while (i < data.size()) {
		x = (int)data[i+1] - 48;
		y = (int)data[i+3] - 48;
		i = i + 6;
		addEdgeAdjMatrix(x,y);
	}
}

Graph::Graph() {
    edgesList = 0;
    edgesMat = 0;
    nodes = 0;
    adjList = 0;
    adjMatrix = 0;

}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++){adjMatrix[i] = 0;}
	edgesList= 0;
	edgesMat= 0;
}

void Graph::addEdgeAdjMatrix(int x, int y) {
    if (x >= 0 && x < nodes && y >= 0 && y < nodes) {
        adjMatrix[x * nodes + y] = 1;
        adjMatrix[y * nodes + x] = 1;
        edgesMat++;
    }
}

string Graph::printAdjList() {
    string res;

    for (int i = 0; i < nodes; i++) {
        res += "vertex " + to_string(i) + " : ";
        sort(adjList[i].begin(), adjList[i].end());
        for (int j = 0; j < adjList[i].size(); j++) {
            res += to_string(adjList[i][j]) + " ";
        }
    }
    return res;
}

string Graph::printAdjMat() {
    string res;
    
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            res += to_string(adjMatrix[i * nodes + j]) + " ";
        }
        
    }
    return res;
}

string Graph::DFS(int start, int end) {
    stack<int> bolsa;
    list<int> call;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    bolsa.push(start);
    string ans = depthHelper(start, end, bolsa, call, path);
    ans = ans + print_path(path, start, end);
    return ans;
}

string Graph::depthHelper(int curry, int end, stack<int>& bolsa, list<int>& call, vector<vector<int>>& path) {
   if (curry == end){
        return print_call(call);
   } 
   else if (bolsa.empty()){
        return "No se encontro el nodo";
   } 
   else {
        curry = bolsa.top();
        bolsa.pop();
        call.push_back(curry);
        for (int i = 0; i < adjList[curry].size(); i++)
           if (!contains(call, adjList[curry][i])){
                bolsa.push(adjList[curry][i]);
                path[adjList[curry][i]][0] = curry;
           }
        return depthHelper(curry, end, bolsa, call, path);
   }
}

string Graph::BFS(int start, int end) {
    queue<int> row;
    list<int> call;
    vector<vector<int>> path(nodes, vector<int>(1, -1));

    row.push(start);
    string ands = breadthHelper(start, end, row, call, path);
    ands = ands + print_path(path, start, end);
    return ands;
}

string Graph::breadthHelper(int curry, int goal, queue<int> &row, list<int> &call, vector<vector<int>> &path){
	if(curry == goal){
		return print_call(call);
	} 
	else if (row.empty()){
		return "No se encontro el nodo";
	}
	else{
		curry = row.front();
		row.pop();
		call.push_back(curry);
		
		for (int i = 0; i < adjList[curry].size(); i++){
			if (!contains(call, adjList[curry][i])){    
				row.push(adjList[curry][i]);    
				if (path[adjList[curry][i]][0] == -1){
					path[adjList[curry][i]][0] = curry;
				}
			}
		}
		return breadthHelper(curry, goal, row, call, path);
   }
}

string Graph::print_call(list<int> call){
	stringstream temp;
	temp << "visited: ";
	while (!call.empty()){
    temp << call.front() << " ";
    call.pop_front();
  	}
	return temp.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> rev;
	rev.push(goal);
	stringstream temp;
	temp  << "path:";
	while (node != start) {
		rev.push(node);
    	node = path[node][0];
  	}
	rev.push(start);
	while (!rev.empty()) {
		temp << " " << rev.top() ;
		rev.pop();
  	}
	return temp.str();
}

bool Graph::contains(list<int> s, int node){
		list<int>::iterator va;
		va = find(s.begin(), s.end(), node);
		if(va != s.end()) {return true;}
		else {return false;}
}

#endif /* Graph_H_ */
