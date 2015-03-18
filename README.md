# ORACLE-haCpp
// HackthonCPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include"CSVUtility.h"
#include"buildUndirectedGraph.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
     int option;
	 int source,destination;
     bool result = false;
	 undirectedGraph obj;
     do 
     {
        //Displaying Options for the menu
        cout << "WELCOME TO  STARSHIP ENTERPRISE" << endl;
        cout << "1) Load Star deta " << endl;
        cout << "2) Find shortest path " << endl;
        cout << "3) Exit Program " << endl;
        //Prompting user to enter an option according to menu
        cout << "Please select an option : ";
        cin >> option;  // taking option value as input and saving in variable "option"
        if(option == 1) // Checking if user selected option 1
        {
            string fileName;
            cout<<"Please enter data file name : "<<endl;
            cin>>fileName;
            cout<<"Reading .. "<<endl;
			result = obj.loadFile(fileName);
		    if(result)
                cout<<"Success"<<endl;
            else
                cout<<"Failure"<<endl;
        }else if(option == 2 && result)
        {
			cout<<"Please enter Source Location : "<<endl;
			cin>>source;
			cout<<"Please enter Destination Location : "<<endl;
			cin>>destination;
			obj.findShortestPath(source,destination);
        }
        else if(option == 3)
        {

          cout << "Terminating Program" << endl;

        }
        else
        {

          //Displaying error message
          cout << "Invalid Option entered" << endl;
        }
     }while(option != 3);  //condition of do-while loop

	return 0;
}
