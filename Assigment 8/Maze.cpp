#include "Maze.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Maze::Maze(int n){
    this->n = n; 
}

void Maze::addEdge(int v1, int v2){
    // add code here 
    int thesize= vertices.size();
    for (int i = 0; i < thesize; i++)
    {
        if (vertices[i]->num==v1)
        {
            for (int n = 0; n < vertices[i]->adj.size(); n++)
            {
                if (vertices[i]->adj[n].v->num==v2)
                {
                    return;
                }

                
            }
            for (int b = 0; b < thesize; b++)
            {
                if (vertices[b]->num==v2 && i!=b)
                {
                    if(vertices[i]!=NULL)
                    {
                        adjVertex thev;
                        thev.v=vertices[b];
                        vertices[i]->adj.push_back(thev);
                    }
                    if(vertices[b] != NULL)
                    {
                        adjVertex thev2;
                        thev2.v =vertices[i];
                        vertices[b]->adj.push_back(thev2);
                    }

                }
            }
            
            
        }
        
        
        

    }
    
}

void Maze::addVertex(int num){
    // add code here
    bool exist=false;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i]->num==num)
        {
            exist=true;
        }
        

    }
    if (exist==true)
    {
        return;    
    }
    else
    {
        vertex* racoon= new vertex;
        racoon->num=num;
        vertices.push_back(racoon);
    }
    
}

void Maze::displayEdges()
{
    
}

int Maze::findVertexNumFromPosition(int x, int y){
    // add code here 
    return 0; 
}

// Creates a default maze of all 1s of size n x n, except for positions (0,0) and (n-1, n-1)
void Maze::createDefaultMaze(){
    // add code here
}

void Maze::createPath(int i, int j){
    // add code here
}

void Maze::printMaze(){
    // add code here
}

vector<int> Maze::findOpenAdjacentPaths(int x, int y){
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<int> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= n){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= n){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && maze[i][j] == 0){
                neighbors.push_back(findVertexNumFromPosition(i, j));
            }
        }
    }
    return neighbors;
}

void Maze::convertMazeToAdjacencyListGraph(){
    // add all the vertices to the adjacency list

    // add all edges to the adjacency list
}

bool Maze::findPathThroughMaze(){

    // add code here
    return false; 
}


bool Maze::checkIfValidPath(){
    // add code here
    return false; 
}

Maze::~Maze(){
    if (n > 0){
        for(int i = 0; i < n; i++){
            delete[] maze[i];
        }
        delete[] maze;
    }
    for (unsigned int i = 0; i< vertices.size(); i++){
        delete vertices[i]; 
    }
}
