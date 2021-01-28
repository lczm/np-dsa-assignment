#include "MrtLine.h"

MrtLine::MrtLine()
{
}

void MrtLine::addStationFront(Node*& newNode)
{
    stationList.addFront(newNode);
}

void MrtLine::addStationBack(Node*& newNode)
{
    stationList.addBack(newNode);
}

MrtLine::~MrtLine()
{
}
