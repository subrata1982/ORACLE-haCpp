#ifndef _CSV_UTILITY_H
#define _CSV_UTILITY_H
#include<iostream>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
struct node
{
   double x,y,z;
   char fuelPoint;
   //char hostile;
};

//map<int,node*> starData;

class csvUtil
{

public:

 static bool csvReader(string fileName,map<int,node*> &starData)
 {
     ifstream file(fileName.c_str());
     string line;
     if(!file.good())
     {
         cout<<"File Error"<<endl;
         return false;
     }
	 getline(file,line);
     while(file)
     {
         line.clear();
         getline(file,line);
         if(line.empty())
             continue;
         else
         {
             string cell;
             stringstream ss(line);
             vector<string> v;
             struct node *D = new struct node;
             v.clear();
             while(std::getline(ss, cell, ',')) 
			 {
                 v.push_back(cell);
                // cout<<cell<<endl;
             }
             if(v.size() == 6  )
             {
                if(v.at(5)=="Y")
                {
                    D->x = 0;
                    D->y = 0;
                    D->z = 0;                    
                    D->fuelPoint='H';
                    starData.insert(std::pair<int,node*>(atoi(v.at(0).c_str()),D));
                }else{
                    D->x = atof(v.at(1).c_str());
                    D->y = atof(v.at(2).c_str());
                    D->z = atof(v.at(3).c_str());
                    if(v.at(4) == "Y")
                    D->fuelPoint='Y';
                    starData.insert(std::pair<int,node*>(atoi(v.at(0).c_str()),D));
                }
             }else{

                 cout<<"inVALID DATA"<<endl;
             }
         }
     }
     file.close();
     return true;
 }

 static double findDistanceBeetweenSrcDest(int srcID,int destID,map<int,node*> &starData)
 {
	 double x1,y1,z1;
	 double x2,y2,z2;
	 double actualDistance = 0;
	 map<int,node*>::iterator mapItr;
	 mapItr =starData.find(srcID);
	 if(mapItr == starData.end())
	 {
		 cout<< "Invalid Source Location: "<<srcID<<endl;
		 return -1;
	 }
	 else
	 {
		 x1 = mapItr->second->x;
		 y1 = mapItr->second->y;
		 z1 = mapItr->second->z;
	 }
	 mapItr = starData.find(destID);
	 if(mapItr == starData.end())
	 {
		 cout<< "Invalid Destination Location: "<<srcID<<endl;
		 return -1;
	 }
	 else
	 {
		 x2 = mapItr->second->x;
		 y2 = mapItr->second->y;
		 z2 = mapItr->second->z;
	 }

	 actualDistance = calculateDistance(x1,y1,z1,x2,y2,z2);
	 return actualDistance;
 }

static double calculateDistance(double x1,double y1,double z1,double x2,double y2,double z2)
{
   double distance, dx,dy,dz;
   dx = x2-x1;
   dy = y2-y1;
   dz = z2-z1;          
   distance = sqrt((dx*dx)+(dy*dy)+(dz*dz));
   return distance;
}

};
#endif
