#pragma once
#include <string>
#include "Graph.h"
#include "DoublyLinkedList.h"

using namespace std;
class MrtLine
{
   private:
    string mrtLineName;
    DoublyLinkedList<Node*> stationList;
    Graph* graph;

   public:
    MrtLine();
    MrtLine(Graph * graph);
    void setMrtLineName(string name)
    {
        mrtLineName = name;
    }

    string getMrtLineName()
    {
        return mrtLineName;
    }
    void addStationFront(Node*& newNode);
    void addStationBack(Node*& newNode);
    void removeStation(Node*& newNode);
    void removeConnectionBetweenStations(string fromNodeId, string toNodeId);
    void printStationsAll();
    void printStationsBasedOnDirection(string stationId);
    ~MrtLine();

};
