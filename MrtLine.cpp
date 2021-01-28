#include "MrtLine.h"

MrtLine::MrtLine()
{
}

MrtLine::MrtLine(Graph* graph)
{
    this->graph = graph;
}

void MrtLine::addStationFront(Node*& newNode)
{
    stationList.addFront(newNode);
}

void MrtLine::addStationBack(Node*& newNode)
{
    stationList.addBack(newNode);
}

void MrtLine::removeStation(Node*& newNode)
{
}

void MrtLine::removeConnectionBetweenStations(string fromNodeId, string toNodeId)
{
}

void MrtLine::printStationsAll()
{
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
