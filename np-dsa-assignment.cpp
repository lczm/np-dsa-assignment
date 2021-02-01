#include <iostream>
#include "structures/vector.h"
#include "structures/trie.h"
#include "Graph.h"
#include "FileReader.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "MrtLine.h"

using namespace std;

// Global variables in main
Graph graph;
Dictionary<Node*> dic;
Vector<MrtLine> mrtlines;

void testVector()
{
    Vector<int> v(10, 1);

    for (uint32_t i = 0; i < v.size(); i++)
    {
        v[i] = i;
    }

    for (uint32_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }

    struct Test
    {
        int a = 5;
    };

    Vector<Test> t(15);
    for (uint32_t i = 0; i < t.size(); i++)
    {
        cout << t[i].a << endl;
    }

    Vector<int> test;
    for (uint32_t i = 0; i < 10; i++)
    {
        test.pushBack(i);
        cout << test[i] << endl;
    }

    test.remove(0);
    cout << test.size() << endl;

    for (uint32_t i = 0; i < test.size(); i++)
    {
        cout << test[i] << endl;
    }

    // Attempt to index out of range
    // cout << test[10] << endl;

    Vector<int> testPushBack;
    testPushBack.pushBack(10);
    testPushBack.pushBack(20);
    testPushBack.pushBack(30);
    testPushBack.pushBack(40);
    testPushBack.pushBack(50);
    cout << testPushBack.size() << endl;

    for (uint32_t i = 0; i < testPushBack.size(); i++)
    {
        cout << testPushBack[i] << endl;
    }

    Vector<Test*> vPointers;
    vPointers.pushBack(new Test{1});
    vPointers.pushBack(new Test{2});
    vPointers.pushBack(new Test{3});
    vPointers.pushBack(new Test{4});

    Vector<Test*> altPointers;
    for (uint32_t i = 0; i < vPointers.size(); i++)
    {
        altPointers.pushBack(vPointers[i]);
    }

    cout << vPointers.size() << endl;
    cout << altPointers.size() << endl;

    cout << "---" << endl;
    Vector<int> removeTest;
    removeTest.pushBack(1);
    removeTest.pushBack(2);
    removeTest.pushBack(3);
    removeTest.pushBack(4);
    removeTest.pushBack(5);
    removeTest.pushBack(6);
    removeTest.remove(2);

    for (size_t i = 0; i < removeTest.size(); i++)
    {
        cout << removeTest[i] << endl;
    }
    cout << "---" << endl;
    cout << "---" << endl;

    // Copy constructor test
    Vector<int> a;
    a.pushBack(1);
    a.pushBack(2);
    a.pushBack(3);

    Vector<int> b;
    b.pushBack(4);
    b = a;

    cout << b.size() << endl;
    for (uint32_t i = 0; i < b.size(); i++)
    {
        cout << b[i] << endl;
    }
}

void testTrie()
{
    cout << "---testTrie---" << endl;
    Trie trie;

    trie.insert("0");
    trie.insert("a");
    trie.insert("A");
    trie.insert("Hello");
    trie.insert("HelloThere");
    trie.insert("Hey");
    trie.insert("Here");
    trie.insert("Boop");
    trie.insert("Book");

    cout << trie.search("Hello") << endl;
    cout << trie.search("there") << endl;
    cout << trie.search("a") << endl;
    cout << trie.search("ay") << endl;

    Vector<string> a;
    a.pushBack("Hello");
    a.pushBack("Hello2");

    Vector<string> b;
    b = a;

    Vector<string> completions = trie.complete("Boo");
    for (uint32_t i = 0; i < completions.size(); i++)
    {
        cout << completions[i] << endl;
    }

    Vector<string> completions2 = trie.complete("H");
    for (uint32_t i = 0; i < completions2.size(); i++)
    {
        cout << completions2[i] << endl;
    }

    cout << "---testTrie---" << endl;
}

// void testGraphConnections()
//{
//    Graph graph;
//    Dictionary<Node*> dic;
//    Vector<MrtLine> mrtlines;
//    graph.setNodeList(&dic);
//    FileReader filereader(&graph, &dic, mrtlines);
//    Vector<Connection*> c;
//
//
//    graph.removeConnection("EW13", "EW8");
//    //graph.getAllConnectionsForNode("EW13", c);
//
//    Vector<Connection*> d;
//   // graph.getAllConnectionsForNode("EW2", d);
//
//    cout << "EW13 connections: ";
//    for (uint32_t i = 0; i < c.size(); i++)
//    {
//        cout << c[i]->toNode->id << " ";
//    }
//    cout << " " << endl;
//    cout << "EW2 connections: ";
//    for (uint32_t i = 0; i < d.size(); i++)
//    {
//        cout << d[i]->toNode->id << endl;
//    }
//
//    cout << "\n";
//
//    cout << "mrt size:" <<  mrtlines.size() << endl;
//    cout << "mrt name:" << mrtlines[0].getMrtLineName() << endl;
//    graph.getAllGraphConnections(d);
//
//    cout << "d size: " << d.size() << endl;
//    mrtlines[0].addNewStation("EW13", "test", true, 10, 10);
//    mrtlines[0].addNewStation("EW13", "test2", false, 10, 10);
//    cout << "mrt name:" << mrtlines[0].getMrtLineName() << endl;
//    mrtlines[0].printStationsAll();
//
//    graph.getAllGraphConnections(c);
//    cout << "c size: " << c.size() << endl;
//    for (uint32_t i = 0; i < c.size(); i++)
//    {
//        cout << c[i]->fromNode->id << " ";
//        cout << c[i]->toNode->id << " ";
//    }
//
//    mrtlines[0].removeStation("EW1", 10);
//    mrtlines[0].printStationsAll();
//
//     Vector<Connection*> f;
//    graph.getAllGraphConnections(f);
//    cout << "c size: " << f.size() << endl;
//    for (uint32_t i = 0; i < f.size(); i++)
//    {
//        cout << f[i]->fromNode->id << " ";
//        cout << f[i]->toNode->id << " ";
//    }
//}
//

// void testDoublyLinkedList()
//{
//    Node * fromNode = new Node();
//
//    // has interchange connections
//    fromNode->id = "EW13";
//
//
//    Node* fromNodeAnother = new Node();
//
//    // has interchange connections
//    fromNodeAnother->id = "EW14";
//
//    Node toNode;
//    toNode.id = "EW2";
//
//    Node toNode2;
//    toNode2.id = "EW4";
//
//    DoublyLinkedList<Node> list;
//    list.addFront(toNode);
//    cout <<"size of doubly: " << list.getSize() << endl;
//    list.remove(toNode);
//    cout << "size of doubly: " << list.getSize() << endl;
//
//     list.addFront(toNode);
//     Node node = list.getAt(0);
//     cout << node.id << endl;
//
//
//    DoublyLinkedList<Node*> listptr;
//    listptr.addFront(fromNode);
//    cout << "size of doubly: " << listptr.getSize() << endl;
//    listptr.remove(fromNode);
//    cout << "size of doubly: " << listptr.getSize() << endl;
//
//    listptr.addFront(fromNode);
//    listptr.addFront(fromNodeAnother);
//    cout << "size of doubly: " << listptr.getSize() << endl;
//    listptr.removeAt(0);
//    cout << "size of doubly: " << listptr.getSize() << endl;
//
//    Node * getNode = listptr.getAt(0);
//    cout << getNode->id << endl;
//
//}

// void testDictionary()
//{
//    Node* fromNodeAnother = new Node();
//
//    // has interchange connections
//    fromNodeAnother->id = "EW14";
//    Dictionary<Node*> d;
//    d.add(fromNodeAnother->id, fromNodeAnother);
//    Node* nodetest = d.get("EW14");
//    cout << nodetest->id << endl;
//
//
//    Node toNode;
//    toNode.id = "EW2";
//    Dictionary<Node> nonPtr;
//    nonPtr.add(toNode.id, toNode);
//    Node nodetest2 = nonPtr.get("EW2");
//    cout << nodetest2.id << endl;
//}

void displayMenu();
template <typename TCallback>
void displayMrtLinesToSelect(TCallback Evt);
void errorDetect(int& option);
void enterInputForInt(int& option);
string extractStringMain(string stationId);
    // void addStationToMrtLine();
void addStationToMrtLineTest();
void addStationDetails(int station, MrtLine* mrt);
void enterCostForAddStationDetails(int& beforeCost, int& afterCost, int beforeAfter, Node* selected,
                                   MrtLine* mrt, int station, string name);
void removeStationToMrtLine();
void removeStationDetails(int station, MrtLine* mrt);
void shortestPath();
void addStationInterchangeOrConnectionBetweenMrtLines();
void displayAllStations();

int main()
{
    graph.setNodeList(&dic);
    FileReader filereader(&graph, &dic, mrtlines);
    cout << "np-dsa-assignment" << endl;
    // testing purposes as there is no unit tests
    // testVector();
    // testGraphConnections();
    // testDoublyLinkedList();
    // testDictionary();
    // testTrie();

    bool exit = false;
    while (exit != true)
    {
        int option = 0;
        while (option != -1)
        {
            displayMenu();
            cout << "Enter option: ";
            cin >> option;
            cin.clear();
            cin.ignore(10000, '\n');
            switch (option)
            {
                case 1:
                    displayMrtLinesToSelect(addStationToMrtLineTest);
                    break;
                case 2:
                    displayMrtLinesToSelect(removeStationToMrtLine);
                    break;
                case 3:
                    addStationInterchangeOrConnectionBetweenMrtLines();
                    break;
                case 5:
                    shortestPath();
                    break;
                case 6:
                    displayAllStations();
                    break;
                default:
                    cout << "Please select the correct option" << endl;
                    break;
            }
        }

        cout << "Are you sure you want to exit? (y/n) " << endl;
        char ans;
        cin >> ans;
        if (toupper(ans) == 'Y')
        {
            exit = true;
        }
        else
        {
            exit = false;
        }
    }
    return 0;
}

void displayMenu()
{
    cout << "\n";
    cout << "Welcome to Railway inc. (Enter -1 to log off) " << endl;
    cout << "Please select an option " << endl;
    cout << "Option 1: Add a train station" << endl;
    cout << "Option 2: Remove a train station" << endl;
    cout << "Option 3: Add an interchange/connection between mrt lines" << endl;
    cout << "Option 4: Remove an interchange/connection between mrt lines" << endl;
    cout << "Option 5: Add a new mrt line/extension" << endl;
    cout << "Option 6: Find the shortest path between stations" << endl;
    cout << "Option 7: Print all Mrt Lines and stations" << endl;
    cout << "\n";
}

template <typename TCallback>
void displayMrtLinesToSelect(TCallback Evt)
{
    // Ask user to select a line
    bool exit = false;
    while (exit != true)
    {
        cout << "[Please enter a mrt index]" << endl;
        for (int i = 0; i < mrtlines.size(); i++)
        {
            cout << "Option " << i << ") "
                 << "Mrt Line name: " << mrtlines[i].getMrtLineName() << endl;
        }
        Evt();
        exit = true;
    }
}

/* ADD STATION METHODS BEGIN HERE*/
void addStationToMrtLineTest()
{
    // based on that line print the train stations
    int lineSelected = 0;
    enterInputForInt(lineSelected);
    if (lineSelected >= 0 && lineSelected < mrtlines.size())
    {
        MrtLine* mrt = &mrtlines[lineSelected];
        mrt->printStationsAll();
        cout << "Select a station index you would like to add your station to" << endl;
        int station;
        enterInputForInt(station);

        if (station >= 0 && station < mrt->getSize())
        {
            addStationDetails(station, mrt);
        }
        else
        {
            cout << "Please select the correct station index!";
        }
    }
}

void addStationDetails(int station, MrtLine* mrt)
{
    int beforeCost, afterCost, beforeAfter = 0;
    string name;
    Node* selected = mrt->getMrtStation(station);
    cout << "[You have selected " << selected->name << "]" << endl;
    cout << "Would you like the new station to be before or after the selected station?" << endl;
    cout << "[0 == before/1 == after]" << endl;
    enterInputForInt(beforeAfter);

    // check range
    while (beforeAfter > 1 || beforeAfter < 0)
    {
        cout << "Enter the correct option (0 or 1)" << endl;
        enterInputForInt(beforeAfter);
    }

    cout << "What is the name of your station?" << endl;
    std::getline(std::cin, name);

    enterCostForAddStationDetails(beforeCost, afterCost, beforeAfter, selected, mrt, station, name);
    mrt->addNewStation(selected->id, name, beforeAfter, beforeCost, afterCost);
    mrt->printStationsAll();
}

// For add stationDetails
void enterCostForAddStationDetails(int& beforeCost, int& afterCost, int beforeAfter, Node* selected,
                                   MrtLine* mrt, int station, string name)
{
    auto costBetweenText = [](string fromName, string toName) {
        cout << "Cost between " << fromName << " to " << toName << "?";
    };
    if (beforeAfter == 1)
    {
        costBetweenText(selected->name, name);
        cin >> beforeCost;
        errorDetect(beforeCost);
        if (station + 1 < mrt->getSize())
        {
            Node* afterNewMrt = mrt->getMrtStation(station + 1);
            costBetweenText(name, afterNewMrt->name);
            cin >> afterCost;
            errorDetect(afterCost);
        }
    }
    else if (beforeAfter == 0)
    {
        if (station - 1 >= 0)
        {
            Node* afterNewMrt = mrt->getMrtStation(station - 1);
            costBetweenText(afterNewMrt->name, name);
            cin >> beforeCost;
            errorDetect(beforeCost);
        }

        costBetweenText(name, selected->name);
        cin >> afterCost;
        errorDetect(afterCost);
    }
}
/* ADD STATION METHODS END HERE*/

/* REMOVE STATION METHODS BEGIN HERE*/
void removeStationToMrtLine()
{
    // based on that line print the train stations
    int lineSelected = 0;
    enterInputForInt(lineSelected);
    if (lineSelected >= 0 && lineSelected < mrtlines.size())
    {
        MrtLine* mrt = &mrtlines[lineSelected];
        mrt->printStationsAll();
        cout << "Select a station index you want to remove" << endl;
        int station;
        enterInputForInt(station);

        if (station >= 0 && station < mrt->getSize())
        {
            removeStationDetails(station, mrt);
        }
        else
        {
            cout << "Please select the correct station index!";
        }
    }
}

void removeStationDetails(int station, MrtLine* mrt)
{
    Node* selected = mrt->getMrtStation(station);
    cout << "[You have selected " << selected->name << "]" << endl;
    int costBetweenStations = 0;

    Node* prevStation = NULL;
    Node* afterStation = NULL;
    if (station - 1 >= 0)
    {
        prevStation = mrt->getMrtStation(station - 1);
    }
    if (station + 1 < mrt->getSize())
    {
        afterStation = mrt->getMrtStation(station + 1);
    }

    if ((prevStation != NULL) && (afterStation != NULL))
    {
        cout << "Cost between " << prevStation->name << " and " << afterStation->name << "? "
             << endl;
        enterInputForInt(costBetweenStations);
    }

    mrt->removeStation(selected->id, costBetweenStations);
    mrt->printStationsAll();
}
/* REMOVE STATION METHODS END HERE*/


/* ADD STATION INTERCHANGE BEGINS HERE*/
void addStationInterchangeOrConnectionBetweenMrtLines()
{   
    displayAllStations();
    string fromNodeId;
    string toNodeId;

    cout << "[Station IDs must be from different mrt lines]" << endl;
    auto printStep = [](string num) {
        cout << "Please enter the " << num << " station ID: "
             << endl;
    };

    cout << "[Station IDs are case sensitive]" << endl;
    printStep("first");
    cin >> fromNodeId;

    printStep("second");
    cin >> toNodeId;

    // check if the same station
    if (fromNodeId == toNodeId)
    {
        cout << "You have given the same station ID!" << endl;
        return;
    }

    auto checkIfValidStation = [](string nodeId) {
        auto printInvalid = [](string nodeId) {
            cout << "The station Id " << nodeId << " does not exist!" << endl;
        };

        if (!dic.hasKey(nodeId))
        {
            printInvalid(nodeId);
            return false;
        }
        return true;
    };

    if (!checkIfValidStation(fromNodeId) || !checkIfValidStation(toNodeId))
    {
        return;
    }

    if (extractStringMain(fromNodeId) == extractStringMain(toNodeId))
    {
        cout << "You have given stations on the same mrt line!" << endl;
        return;
    }

    if (graph.hasConnection(fromNodeId, toNodeId))
    {
        cout << "There is already a connection between these two stations!" << endl;
        return;
    }
    else
    {   
        int cost = 0;
        cout << "Cost between the two stations (0 for interchange)" << endl;
        cin >> cost;
        errorDetect(cost);
        graph.addConnection(fromNodeId, toNodeId, cost);
    }
}
/* ADD STATION INTERCHANGE ENDS HERE*/

/* SHORTEST PATH TO STATION BEGINS HERE*/
void shortestPath()
{
    displayAllStations();
    string fromNodeId;
    string toNodeId;

    auto printStep = [](string startEnd) {
        cout << "Please enter the station ID you would like to " << startEnd << " at" << endl;
    };

    cout << "[Station IDs are case sensitive]" << endl;
    printStep("start");
    cin >> fromNodeId;

    printStep("end");
    cin >> toNodeId;

    // check if the same station
    if (fromNodeId == toNodeId)
    {
        cout << "You have given the same station ID!" << endl;
        return;
    }

    auto checkIfValidStation = [](string nodeId) {
        auto printInvalid = [](string nodeId) {
            cout << "The station Id " << nodeId << " does not exist!" << endl;
        };

        if (!dic.hasKey(nodeId))
        {
            printInvalid(nodeId);
            return false;
        }
        return true;
    };

    if (!checkIfValidStation(fromNodeId) || !checkIfValidStation(toNodeId))
    {
        return;
    }

    Vector<Connection*> connections;
    graph.shortestPathBetweenStations(fromNodeId, toNodeId, connections);

    if (connections.size() > 0)
    {
        cout << "\n" << endl;
        cout << "Shortest path: " << endl;
        for (int i = connections.size() - 1; i >= 0; i--)
        {
            cout << connections[i]->fromNode->id << " to " << connections[i]->toNode->id
                 << "| cost: " << connections[i]->cost << endl;
        }
    }
    else
    {
        cout << "There are no paths between these stations." << endl;
    }
}

/* SHORTEST PATH TO STATION ENDS HERE*/

// for display station
void displayAllStations()
{
    for (int i = 0; i < mrtlines.size(); i++)
    {
        mrtlines[i].printStationsAll();
    }
    cout << "---------------------------------------------------------" << endl;
}

void enterInputForInt(int& option)
{
    cin >> option;
    errorDetect(option);
    cin.clear();
    cin.ignore(10000, '\n');
}

void errorDetect(int& option)
{
    while (cin.fail())
    {
        cout << "Please enter the correct option!:";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> option;
    }
}
string extractStringMain(string stationId)
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
