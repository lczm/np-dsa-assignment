#pragma once
#include <string>
#include "Graph.h"
#include <sstream>
#include "DoublyLinkedList.h"

// Name: Abicharan Bhaskaran
// ID: S10177176J
// Group: 02
// Class: P07
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
    // Example, If I were to add a station between NS11 and NS12
    // the new station will be NS12 and all the stations after it will have to update their ids by 1
    // pre : selectedStationId, decreaseOrIncreaseId
    // post: Updates the ids of the train stations by adding or removing one
    void updateLineIdsForStations(string selectedStationId, int decreaseOrIncreaseId);

    //Updates the connections between the affected stations
    // pre : int selectedStationPtr, int oldStationIndex, int costPrev, int costForward, 
    //            Node *newStation, int beforeAfter (Infront or before the selected station)
    // post: Updates the costs between the stations and adds the new station to the DLL
    void updateConnBetweenStationsForAddNewStation(int selectedStationPtr, int oldStationIndex, int costPrev,
                                          int costForward, Node* newStation, int beforeAfter);

    // Adds station to the front of the DLL
    // pre : Node*& newNode 
    // post: Adds the station to the front of the DLL
    void addStationFront(Node*& newNode);

    // Adds station to the end of the DLL
    // pre : Node*& newNode
    // post: Adds the station to the back of the DLL
    void addStationBack(Node*& newNode);

    //Removes a station
    // Example: NS11 <----Cost----> NS12(to be deleted) <----Cost---->NS13(Id to be updated)
    // NS11<----costBetween---->NS12(updated ID)

    // pre : stationId
    // post: removes the station from the DLL and from the global dic
    // all connections related to this station is also deleted
    // cost is updated between the two stations that the deleted station was 
    // connected with.
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
