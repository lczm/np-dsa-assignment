#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 
#include "structures/vector.h"
#include "Graph.h"
#include "Dictionary.h"


using namespace std;
class FileReader
{
   private:
    string routesName = "data/Routes.csv";
    string interchangesName = "data/Interchanges.csv";
    string stationsName = "data/StationsInfo.csv";
    string faresName = "Fares";
    Graph* graph;
    Dictionary<Node*>* dictionary;

   public:
    FileReader();
    FileReader(Graph* graph, Dictionary<Node*> * dictionary);
    void readStations();
    void readRoutes();
    void readInterchanges();
    void readFares();
    void addToVector(Vector<string>& vectorList, string excelLine);
};
