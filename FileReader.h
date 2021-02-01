#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 
#include "structures/vector.h"
#include "Graph.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "MrtLine.h"
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
    FileReader(Graph* graph, Dictionary<Node*>* dictionary , Vector<MrtLine>& mrtLines);
    void readStations();
    void readRoutes(Vector<MrtLine> & mrtLines);
    void readInterchanges();
    void readFares();
    void readMrtLineNames(Vector<MrtLine>& mrtLines);
    void addToVector(Vector<string>& vectorList, string excelLine);
};
