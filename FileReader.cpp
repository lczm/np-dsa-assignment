#include "FileReader.h"
#include "Graph.h"

FileReader::FileReader()
{
}

FileReader::FileReader(Graph* graph)
{
    this->graph = graph;
}

void FileReader::readStations()
{
}

void FileReader::readRoutes()
{
    ifstream myfile;
    myfile.open(this->routesName);

    Vector<Connection*> connections;
    while (myfile.good())
    {
        Vector<string> mrts;
        Vector<string> weights;

        string mrtLine;
        string distLine;

        std::getline(myfile, mrtLine, '\n');
        std::getline(myfile, distLine, '\n');

        addToVector(mrts, mrtLine);
        addToVector(weights, distLine);

        int vectorSizeMrt = mrts.size();
        vectorSizeMrt = vectorSizeMrt - 1;

        for (int i = 0; i < vectorSizeMrt; i++)
        {
            stringstream stringWeight(weights[i]);
            int x = 0;
            stringWeight >> x;
            graph->addConnection(mrts[i], mrts[i + 1], x);
        }

        // cout << mrtLine << endl;
        // cout << distLine << endl;
        cout << "2 lines" << endl;
        // g1.push_back(line);
    }

    myfile.close();

}

void FileReader::readInterchanges()
{
}

void FileReader::readFares()
{
}

void FileReader::addToVector(Vector<string>& vectorList, string excelLine)
{
    string placeHolder;
    for (int i = 0; i < excelLine.size(); i++)
    {
        if (excelLine[i] == ',')
        {
            vectorList.pushBack(placeHolder);
            placeHolder = "";
        }
        else
        {
            placeHolder.push_back(excelLine[i]);
        }
    }
}
