#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "structures/vector.h"
#include "structures/trie.h"
#include "Graph.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "MrtLine.h"

using namespace std;

// Name: Abicharan Bhaskaran (S10177176J)
// Name: Chua Ze Ming (S10177361C)
// Group: 02
// Class: P07
class FileReader
{
   private:
    const string routesName = "data/Routes.csv";
    const string interchangesName = "data/Interchanges.csv";
    const string stationsName = "data/StationsInfo.csv";
    const string faresName = "data/fares.csv";
    const string mrtLineName = "data/mrtLineNames.csv";

    Graph* graph;
    Dictionary<Node*>* dictionary;

   public:
    FileReader();
    FileReader(Graph* graph, Dictionary<Node*>* dictionary, Vector<MrtLine>& mrtLines,
               Vector<float>& distances, Vector<uint32_t>& fares);

    // Read all stations (Id and name)
    void readStations();

    // Read all routes between stations
    void readRoutes(Vector<MrtLine>& mrtLines);

    // Read all interchanges in the network
    void readInterchanges();

    void readFares(Vector<float>& distances, Vector<uint32_t>& fares);

    // Read the names of the mrt lines
    void readMrtLineNames(Vector<MrtLine>& mrtLines);

    // Converts a string with commas into a vector of strings
    // Example: EW1, [random name]
    // Result: ["EW1", "Random name"]
    void addToVector(Vector<string>& vectorList, string excelLine);
};
