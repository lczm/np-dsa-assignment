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
    string mrtPrefix;
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

    void setMrtPrefix(string mrtPrefix)
    {
        this->mrtPrefix = mrtPrefix;
    }

    string getMrtPrefix()
    {
        return mrtPrefix;
    }

    
    // Adds a new mrt station along with the costs associated with it
    // For example I want to add a station infront of NS11
    // The new station is now called NS12*
    // The affected stations would be NS11 and NS13 (previously NS12)
    // Thus now, I would need the cost from NS11 to NS12 (costPrev) and from NS12 to NS13 (costForward)

    // pre : stationId, newStationName, infront, costPrev and costForward
    // post: Adds the station to the DLL, updates connections between the affected stations
    void addNewStation(string stationId, string newStationName, bool infront, int costPrev, int costForward);

    // Updates the ids of the stations
    // pre : selectedStationId, decreaseOrIncreaseId
    // post: Updates the ids of the train stations by adding or removing one
    void updateLineIdsForStations(string selectedStationId, int decreaseOrIncreaseId);

    //Updates the connections between the affected stations
    void updateConnBetweenStationsForAddNewStation(int selectedStationPtr, int oldStationIndex, int costPrev,
                                          int costForward, Node* newStation, int beforeAfter);

    //Adds station to the front of the DLL
    void addStationFront(Node*& newNode);

    //Adds station to the end of the DLL
    void addStationBack(Node*& newNode);

    //Removes a station
    void removeStation(string stationId, int costBetween);

    //Removes all connections between these two stations
    void removeConnectionBetweenStations(string fromNodeId, string toNodeId);

    //Prints all stations and the associated cost between them
    void printStationsAll();
    void printStationsBasedOnDirection(string stationId);
    int getSize()
    {
        return stationList.getSize();
    }
    Node* getMrtStation(int index);

    ~MrtLine();

};
