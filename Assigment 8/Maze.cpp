#include "Maze.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Maze::Maze(int n)
{
    this->n = n; 
    maze = new int*[n];
}

void Maze::addEdge(int v1, int v2)
{
    int thesize=vertices.size();
    bool isthere=false;
    for(int i = 0; i < thesize; i++)
    {
        if(vertices[i]->num==v1)
        {
            for(int b=0; b < thesize; b++)
            {
                if(vertices[b]->num==v2 && i!=b)
                {
                    isthere=false;
                    for(int z=0; z < vertices[i]->adj.size(); z++)
                    {
                        if(vertices[i]->adj[z].v->num==v2)
                        {
                            isthere=true;
                        }
                    }
                    if(isthere==false)
                    {
                        adjVertex av;
                        av.v=vertices[b];
                        vertices[i]->adj.push_back(av);
                        adjVertex av2;
                        av2.v=vertices[i];
                        vertices[b]->adj.push_back(av2);
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
    if(exist==false)    
    {
        vertex* racoon= new vertex;
        racoon->num=num;
        vertices.push_back(racoon);
    }
    
}


void Maze::displayEdges()
{
    cout<<"Adjacency List Graph: "<<endl;
    for (int i = 0; i < vertices.size(); i++)
    {
        cout<<vertices[i]->num<<" --> ";
        for (int b = 0; b < vertices[i]->adj.size(); b++)
        {
            cout<<vertices[i]->adj[b].v->num<<" ";
        }
        cout<<endl;
        
    }
}

int Maze::findVertexNumFromPosition(int x, int y)
{
    return y + n * x;
}

// Creates a default maze of all 1s of size n x n, except for positions (0,0) and (n-1, n-1)
void Maze::createDefaultMaze()
{
    for (int i = 0; i < n; i++)
    {
        maze[i] = new int[n];
        for (int b = 0; b < n; b++) 
        {
            maze[i][b] = 1;
        }
    }
    maze[0][0] = 0;
    maze[n-1][n-1] = 0;
}

void Maze::createPath(int i, int j){
    maze[i][j]=0;
}

void Maze::printMaze(){
    
    cout<<"Maze of size "<<"("<<n<<"x"<<n<<")"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"| ";
        for (int b = 0; b < n; b++)
        {
            cout<<maze[i][b]<<" | ";
        }
        cout<<endl;
        
    }
    
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

void Maze::convertMazeToAdjacencyListGraph()
{
    int position=0;
    int position2=0;
   for(int i = 0; i < n; i++)
    {
        for(int b = 0; b < n; b++)
        {
            if(maze[i][b] == 0)
            {
                position=findVertexNumFromPosition(i, b);
                addVertex(position);
                for(int z = 0; z < findOpenAdjacentPaths(i, b).size(); z++)
                {
                    position2=findOpenAdjacentPaths(i, b)[z];
                    addEdge(position, position2);
                    addEdge(position2, position);
                }
            }
        }
    }
} 

bool auxiliarPathdfs(vertex* traveler,int paths,vector<int> &highway)
{
    if (traveler->num == paths*paths-1)
    {
        return true;
    }
    traveler->visited=true;
    for (int i = 0; i < traveler->adj.size(); i++)
    {
        if (traveler->adj[i].v->visited==true)
        {
            continue;
        }
        else
        {
            cout<<"Reached vertex: "<<traveler->adj[i].v->num<<endl;
            if (auxiliarPathdfs(traveler->adj[i].v,paths,highway)==true)
            {
                highway.insert(highway.begin(),traveler->adj[i].v->num);
                return true;
            }
            cout<<"Backtracked to vertex: "<<traveler->num<<endl;
        }
        
    }
    return false;
}

bool Maze::findPathThroughMaze(){

    cout<<"Starting at vertex: 0"<<endl;
    cout<<"Reached vertex: 0"<<endl;
    if (auxiliarPathdfs(vertices[0],n,path)==true)
    {
        path.insert(path.begin(),0);
        return true;
    }
    
    return false; 
}


bool Maze::checkIfValidPath()
{
    if(path.front() == 0 && path.back() == n*n - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
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
