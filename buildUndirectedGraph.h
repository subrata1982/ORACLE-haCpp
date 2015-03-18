#ifndef _UNDIRECTED_GRAPH_H
#define _UNDIRECTED_GRAPH_H
#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
#include<map>
#include<list>
#include"CSVUtility.h"
using namespace std;

class undirectedGraph
{
	bool fileReadFlag;
	double distanceSrcDest;
	int numberOfVertices;
	const int fuelLimit;
    
	pair<double,char> **adjacencyMatrix;
	map<int,node*> starData;
    //map<int,pair<double, string>> adjList;
	
public:
	undirectedGraph():fuelLimit(10)
	{
		numberOfVertices = 0;
		fileReadFlag = false;
	}

	bool loadFile(string fileName)
	{
		fileReadFlag = csvUtil::csvReader(fileName,starData);
		return fileReadFlag;
	}


	bool findShortestPath(int srcID,int destID)
	{
		bool returnFlag = false;
		 if(srcID == destID)
		 {
			 cout<< "Exception:: Sorce Location and Destination Location are Same"<<endl;
			 returnFlag = false;
		 }
		 else
		 {
			 distanceSrcDest  = csvUtil::findDistanceBeetweenSrcDest(srcID,destID,starData);
			 if(distanceSrcDest == -1)
				 returnFlag = false;
			 else
			 {
				 if(distanceSrcDest <= fuelLimit)
				 {
					 cout<<"The shortest path between the Source and the Destination Node is: "<<distanceSrcDest<<endl;
					 cout<<srcID<<"-->"<<destID<<endl;
				 }
				 else
				 {
					 populateAdjancyMatrix();
					 dijkstra(srcID,destID);
				 }
			 }
		 }
	    return returnFlag;
	}

	void populateAdjancyMatrix()
	{
		double x1,y1,z1;
		double x2,y2,z2;
		char fuelPoint;
		double distance;
		numberOfVertices = starData.size();
		adjacencyMatrix = new pair<double,char>*[numberOfVertices];
		for (int i = 0; i < numberOfVertices; ++i) 
		{
           adjacencyMatrix[i] = new pair<double,char> [numberOfVertices];
        }	

		for(int outerCounter =0;outerCounter<numberOfVertices;outerCounter++)
        {
		  x1 = starData[outerCounter]->x;
		  y1 = starData[outerCounter]->y;
		  z1 = starData[outerCounter]->z;
          for(int inerCounter =0;inerCounter<numberOfVertices;inerCounter++)
          { 
			  x2 = starData[inerCounter]->x;
		      y2 = starData[inerCounter]->y;
		      z2 = starData[inerCounter]->z;
			  fuelPoint = starData[inerCounter]->fuelPoint;
			 if(outerCounter == inerCounter || fuelPoint == 'I' || fuelPoint == 'H' )
			 {
				 if(fuelPoint == 'H')
				   adjacencyMatrix[outerCounter][inerCounter]=make_pair(0,'H');
				 else
                   adjacencyMatrix[outerCounter][inerCounter]=make_pair(0,'I');
			 }
			 else
			 {
				 distance = csvUtil::calculateDistance(x1,y1,z1,x2,y2,z2);
                 adjacencyMatrix[outerCounter][inerCounter]=make_pair(distance,fuelPoint);
			 }
          }
        }
	}

 void dijkstra( int src,int destID)
 {

     // int dist[numberOfVertices];
     // bool sptSet[numberOfVertices]; 
	 list<int>shortestPath;
	 shortestPath.push_back(src);
	 int *dist = new int[numberOfVertices];
	 bool *sptSet = new bool[numberOfVertices];
	 int currentFuelLevel = fuelLimit;
      for (int i = 0; i < numberOfVertices; i++)
	  {
         dist[i] = INT_MAX;
		 sptSet[i] = false;
	  }
      dist[src] = 0;
      pair<double,char> tempPair;
	  double distance;
	  char refellingNode;
      for (int count = 0; count < numberOfVertices-1; count++)
      {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < numberOfVertices; v++)
		{
		  tempPair = adjacencyMatrix[u][v];		  
		  distance = tempPair.first;
		  refellingNode = tempPair.second;
		  
          if (!sptSet[v] && distance && dist[u] != INT_MAX && dist[u]+distance < dist[v]
		       && distance <= currentFuelLevel && refellingNode != 'H')
		  {
             dist[v] = dist[u] + distance;
			 currentFuelLevel = currentFuelLevel-distance;
			 shortestPath.push_back(v);
		  }
	      if(refellingNode == 'Y' && currentFuelLevel < fuelLimit)
				 currentFuelLevel = fuelLimit;
        }
	  }
      printSolution(dist, destID,shortestPath);
 }

 void printSolution(int dist[], int n,list<int> &shortestPath )

 {

    if(dist[n] == INT_MAX)
	{
		cout<<" No feasible path found between given source and destination: "<<endl;
		cout<< " Exiting the algorithm"<<endl;
	}
	else
	{
      cout<<" Shortest distance between Source and Destination Vertex is = ";
	  cout<<dist[n]<<endl;
	  list<int>::iterator lItr;
	  cout<<"shortest Path : ";
	  for(lItr = shortestPath.begin();lItr != shortestPath.end(); ++lItr)
	  {
		    cout<<"->"<<*lItr;
	  }
	  cout<<endl;
	}

 }

int minDistance(int dist[], bool sptSet[])
{
		// Initialize min value
		//numberOfVertices = starData.size();
		int min = INT_MAX, min_index;
		for (int v = 0; v < numberOfVertices; v++)
		{
		 if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
		}
		return min_index;
	}

};
#endif
