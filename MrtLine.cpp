#include "MrtLine.h"

int extractIntegers(string stationId)
{
    string number;

    for (int i = 0; i < stationId.size(); i++)
    {
        if (isdigit(stationId[i]))
        {
            number += stationId[i];
        }
    }

    stringstream geek(number); 
    int x = 0;
    geek >> x; 

    return x;
}

string extractString(string stationId)
{
    string lineIdentifier;

    for (int i = 0; i < stationId.size(); i++)
    {
        if (isalpha(stationId[i]))
        {
            lineIdentifier += stationId[i];
        }
    }

    return lineIdentifier;
}

MrtLine::MrtLine()
{
}

MrtLine::MrtLine(Graph* graph)
{
    this->graph = graph;
}


//will refactor
void MrtLine::addNewStation(string stationId, string newStationName, bool infront, int costPrev,
                            int costForward)
{   
    //extracting the string and integers
    int extractedId = extractIntegers(stationId);
    string mrtLineIdentifier = extractString(stationId);
    int selectedStationIndex = 0;


    for (int i = 0; i < stationList.getSize(); i++)
    {
        if (stationList.getAt(i)->id == stationId)
        {
            selectedStationIndex = i;
        }
    }

    Node* newStation = new Node();
    newStation->name = newStationName;

    //added infront of the selected station
    if (infront)
    {   
        newStation->id = mrtLineIdentifier + to_string(extractedId + 1);
        updateLineIdsForAddNewStation(newStation->id);
        updateConnBetweenStationsForAddNewStation(selectedStationIndex, selectedStationIndex + 1,
                                                  costPrev,
                                         costForward, newStation, 1);
    }
    //added behind the selected station
    else
    {   
        newStation->id = mrtLineIdentifier + to_string(extractedId);
        updateLineIdsForAddNewStation(newStation->id);
        updateConnBetweenStationsForAddNewStation(selectedStationIndex, selectedStationIndex - 1,
                                         costForward,
                                         costPrev, newStation, 0);
    }
  
}

void MrtLine::updateLineIdsForAddNewStation(string newStationId)
{
    // Update all the stationIds
    string mrtLineIdentifier = extractString(newStationId);
    Dictionary<Node*>* nodeList = graph->getNodeList();
    for (int i = stationList.getSize()-1; i >= 0; i--)
    {
        if (extractIntegers(stationList.getAt(i)->id) >= extractIntegers(newStationId))
        {
            //Update the dictionary in containing all the nodes
            Node* current = nodeList->get(stationList.getAt(i)->id);
            nodeList->remove(stationList.getAt(i)->id);

            int ChangeExtractedId = extractIntegers(stationList.getAt(i)->id) + 1;
            string id = mrtLineIdentifier + to_string(ChangeExtractedId);

            stationList.getAt(i)->id = id;
            nodeList->add(stationList.getAt(i)->id, current);
        }
    }
}

void MrtLine::updateConnBetweenStationsForAddNewStation(int selectedStationIndex, int oldStationIndex,
                                               int costPrev,
                                               int costForward, Node* newStation, 
                                               int beforeAfter)
{   
    //getting ids
    string selectedStationId = stationList.getAt(selectedStationIndex)->id;
    string oldConnectionStationId = stationList.getAt(oldStationIndex)->id;

    // removing old connections
    removeConnectionBetweenStations(selectedStationId, oldConnectionStationId);

    // adding the new station to the dictionary 
    Dictionary<Node*>* nodeList = graph->getNodeList();
    nodeList->add(newStation->id, newStation);

    //Adding connections between the two stations
    graph->addConnection(selectedStationId, newStation->id, costPrev);
    graph->addConnection(newStation->id, oldConnectionStationId, costForward);
    
    //adding to station list
    stationList.addAt(newStation, selectedStationIndex + beforeAfter);
}

void MrtLine::addStationFront(Node*& newNode)
{
    stationList.addFront(newNode);
}

void MrtLine::addStationBack(Node*& newNode)
{
    stationList.addBack(newNode);
}

//TODO: Update ids of stations after removal
void MrtLine::removeStation(string stationId, int costBetween)
{
    Dictionary<Node*>* nodeList = graph->getNodeList();
    Node* removeStation = nodeList->get(stationId);

    Node* prevStation = nullptr;
    Node* afterStation = nullptr;

    if (removeStation != nullptr)
    {
        for (int i = 0; i < stationList.getSize(); i++)
        {
            if (stationList.getAt(i)->id == stationId)
            {
                prevStation = stationList.getAt(i - 1);
                afterStation = stationList.getAt(i + 1);
                stationList.removeAt(i);
                nodeList->remove(stationId);
                break;
            }
        }

        graph->removeAllConnectionsForNodeBothWays(stationId);
        if ((prevStation != nullptr)&& (afterStation != nullptr))
        {
            graph->addConnection(prevStation->id, afterStation->id, costBetween);
        }
    }
}

void MrtLine::removeConnectionBetweenStations(string fromNodeId, string toNodeId)
{
    graph->removeConnection(fromNodeId, toNodeId);
    graph->removeConnection(toNodeId, fromNodeId);
}

void MrtLine::printStationsAll()
{   

    cout << "MRT Line Name: "<< mrtLineName << endl;
    cout << "Stations:  " <<  endl;
    for (int i = 0; i < stationList.getSize(); i++)
    {
        cout << "Id:" << stationList.getAt(i)->id << " Name:" << stationList.getAt(i)->name << endl;
    }
}

void MrtLine::printStationsBasedOnDirection(string stationId)
{
}

MrtLine::~MrtLine()
{
}

