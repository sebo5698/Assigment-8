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
    int counter=0;
    int checkcounter=0;
    int secoundcounter=0;
    while(counter<thesize)
    {
        if (vertices[counter]->num==v1)
        {
            while  (checkcounter < vertices[counter]->adj.size())
            {
                if (vertices[counter]->adj[n].v->num==v2)
                {
                    return;
                }
                checkcounter++;
                
            }
            while(secoundcounter < thesize)
            {
                if (vertices[secoundcounter]->num==v2 && counter != secoundcounter)
                {
                    if(vertices[counter]!=NULL)
                    {
                        adjVertex thev;
                        thev.v=vertices[secoundcounter];
                        vertices[counter]->adj.push_back(thev);
                    }
                    if(vertices[secoundcounter] != NULL)
                    {
                        adjVertex thev2;
                        thev2.v =vertices[counter];
                        vertices[secoundcounter]->adj.push_back(thev2);
                    }

                }
                secoundcounter++;
            }
            
            
        }
        counter++;
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
        }else
        {
            break;
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
                for(int n = 0; n < findOpenAdjacentPaths(i, b).size(); n++)
                {
                    position2=findOpenAdjacentPaths(i, b)[n];
                    addEdge(position, position2);
                    addEdge(position2, position);
                }
            }
        }
    }
}  
bool auxiliarPathdfs(vertex *traveler,int paths,vector<int>& highway)
{
    if (traveler->num==paths*paths-1)
    {
        return true;
    }
    traveler->visited=true;
    for (int i = 0; i < traveler->adj.size(); i++)
    {
        if (traveler[i].visited==true)
        {
            break;
        }
        cout<<"Reached vertex: "<<traveler[i].num<<endl;
        if (auxiliarPathdfs(traveler,paths,highway)==true)
        {
            highway.push_back(traveler[i].num);
            cout<<"adding to path: "<<traveler[i].num<<endl;
            return true;
        }
        cout<<"Backtracked to vertex: "<<traveler->num<<endl;
        
    }
    return false;
}

bool Maze::findPathThroughMaze(){

    cout<<"starting at vertex: 0"<<endl;
    if (auxiliarPathdfs(path,vertices[0],n))
    {
        path.push_back(0);
        return true
    }
    
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
