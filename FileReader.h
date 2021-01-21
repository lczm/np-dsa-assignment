#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 
#include "structures/vector.h"
#include "Graph.h"

using namespace std;
class FileReader
{
   private:
    string routesName = "data/Routes.csv";
    string interchangesName = "Interchanges.csv";
    string stationsName = "Stations";
    string faresName = "Fares";
    Graph* graph;

   public:
    FileReader();
    FileReader(Graph* graph);
    void readStations();
    void readRoutes();
    void readInterchanges();
    void readFares();
    void addToVector(Vector<string>& vectorList, string excelLine);
};
