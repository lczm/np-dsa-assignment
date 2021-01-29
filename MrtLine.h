#pragma once
#include <string>
#include "Graph.h"
#include <sstream>
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

    /*
    * stationId is where you want to add the newStation to
    * infront is a bool -> True is add infront of the stationId
    * 
    * 
    */
    void addNewStation(string stationId, string newStationName, bool infront, int costPrev, int costForward);
    void updateLineIdsForStations(string selectedStationId, int decreaseOrIncreaseId);
    void updateConnBetweenStationsForAddNewStation(int selectedStationPtr, int oldStationIndex, int costPrev,
                                          int costForward, Node* newStation, int beforeAfter);
    void addStationFront(Node*& newNode);
    void addStationBack(Node*& newNode);
    void removeStation(string stationId, int costBetween);
    void removeConnectionBetweenStations(string fromNodeId, string toNodeId);
    void printStationsAll();
    void printStationsBasedOnDirection(string stationId);
    ~MrtLine();

};
