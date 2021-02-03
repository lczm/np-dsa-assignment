#include "FileReader.h"
#include "Graph.h"

//will create common file for this func
string extractStringFileReader(string stationId)
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

FileReader::FileReader()
{
}

FileReader::FileReader(Graph* graph, Dictionary<Node*>* dictionary, Vector<MrtLine>& mrtLines)
{
    this->graph = graph;
    this->dictionary = dictionary;
    this->readStations();
    this->readRoutes(mrtLines);
    this->readMrtLineNames(mrtLines);
    this->readInterchanges();
}

void FileReader::readStations()
{
    ifstream myfile;
    myfile.open(this->stationsName);

    while (myfile.good())
    {
        Vector<string> mrtInfo;
       
        string mrtInfoLine;
        std::getline(myfile, mrtInfoLine, '\n');
        addToVector(mrtInfo, mrtInfoLine);

        //will be changed to add to the graph's hashTable for nodes

        Node* node = new Node();
        node->id = mrtInfo[0];
        node->name = mrtInfo[1];

        dictionary->add(node->id, node);
        //cout <<"Mrt id: " << mrtInfo[0] << " Mrt Name:" << mrtInfo[1] << endl;
    }

    myfile.close();
}

void FileReader::readRoutes(Vector<MrtLine>& mrtLines)
{
    ifstream myfile;
    myfile.open(this->routesName);
    int lineNo = 0;

    Dictionary<int> mrtCount;

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

         MrtLine mrtLineNew(graph);
      /*   mrtLineNew.setMrtLineName("Line" + to_string(lineNo));
         lineNo++;*/

         for (int i = 0; i < vectorSizeMrt+1; i++)
         {       
           Node* p = dictionary->get(mrts[i]);

           if (!(mrtCount.hasKey(p->id)))
           {
             mrtCount.add(p->id, 1);
           }
           else
           {
               int count = mrtCount.get(p->id);
               count++;
               mrtCount.remove(p->id);
               mrtCount.add(p->id, count);
           }
           if (!(mrtCount.get(p->id) > 1))
           {
             mrtLineNew.addStationBack(p);
           }
         }

         string prefix = extractStringFileReader(mrtLineNew.getMrtStation(0)->id);
         mrtLineNew.setMrtPrefix(prefix);
         mrtLines.pushBack(mrtLineNew);
    }

    myfile.close();

}

void FileReader::readInterchanges()
{
    ifstream myfile;
    myfile.open(this->interchangesName);
    while (myfile.good())
    {   
        int weight = 0;
        Vector<string> mrts;
        string mrtLine;

        std::getline(myfile, mrtLine, '\n');
        addToVector(mrts, mrtLine);

        int vectorSizeMrt = mrts.size();
        vectorSizeMrt = vectorSizeMrt - 1;

        for (int i = 0; i < vectorSizeMrt; i++)
        {
            for (int j = i+1; j < vectorSizeMrt+1; j++)
            {
                graph->addConnection(mrts[i], mrts[j], weight);
            }
        }
    }
    myfile.close();
}

void FileReader::readFares()
{
}

void FileReader::readMrtLineNames(Vector<MrtLine>& mrtLines)
{
    ifstream myfile;
    myfile.open("data/mrtLineNames.csv");

    int num = 0;

    while (myfile.good())
    {

        string mrtLineName;
        std::getline(myfile, mrtLineName, '\n');
        // will be changed to add to the graph's hashTable for nodes
        mrtLines[num].setMrtLineName(mrtLineName);
      
        if (num < mrtLines.size()-1)
        {
            num++;
        }
    }
}

void FileReader::addToVector(Vector<string>& vectorList, string excelLine)
{
    string placeHolder;
    for (int i = 0; i < excelLine.size(); i++)
    {
        if (i == excelLine.size() - 1)
        {
            placeHolder.push_back(excelLine[i]);
            vectorList.pushBack(placeHolder);

            // This does not matter as it ends the line, but for completeness
            // just reset it.
            placeHolder = "";
        }
        else if (excelLine[i] == ',')
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
