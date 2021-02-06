#include <iostream>
#include <conio.h>

#include "structures/vector.h"
#include "structures/trie.h"
#include "Graph.h"
#include "FileReader.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "MrtLine.h"

#include "helper.h"
#include "test.h"

using namespace std;

// Name: Abicharan Bhaskaran (S10177176J)
// Name: Chua Ze Ming (S10177361C)
// Group: 02

// Global variables in main
Graph graph;
Dictionary<Node*> dic;
Vector<MrtLine> mrtlines;
Trie trie;

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

int enterInputForInt()
{
    int option;
    cin >> option;
    errorDetect(option);
    cin.clear();
    cin.ignore(10000, '\n');
    return option;
}

int enterInputForString(Trie trie, Vector<string> names)
{
    int option;
    bool cont;
    string inputString;

    // Input loop to get the string of the input.
    while (true)
    {
        // Get a character without waiting for the user to press enter.
        // This is from conio.h, originally defined for C. For
        // C++ compatibility, the naming scheme has changed to _getch().
        // '\r' -> Carriage Return / Enter
        // Concatenate to string.
        char c = _getch();
        if (c == '\r')  // Enter key
        {
            cout << endl;
            break;
        }
        else if (c == '\b')  // Backspace key
        {
            // Remove the last character
            inputString.pop_back();

            // VT100 escape code. Supported on Windows 10
            // Clears the current line before CR
            // Without this, the user would not bee the 'deleted key'
            printf("%c[2K", 27);
        }
        else if (c == '\t')  // Tab key
        {
            cout << "Suggestions for : " << inputString << endl;
            Vector<string> suggestions = trie.complete(inputString);
            for (uint32_t i = 0; i < suggestions.size(); i++)
            {
                cout << suggestions[i] << endl;
            }
        }
        else
        {
            inputString += c;
        }

        // Carriage return so that the user does not see the history of his inputs
        cout << "\r" << flush;
        // Show what the current string is.
        cout << inputString;
    }
    cout << endl;

    return 0;
}

// for display station
void displayAllStations()
{
    for (int i = 0; i < mrtlines.size(); i++)
    {
        mrtlines[i].printStationsAll();
    }
    cout << "---------------------------------------------------------" << endl;
}

// This func allows the user to add a mrtline to the vector of mrt lines
// The function also checks if the prefix given exists
// The prefix is used to name the mrt station ids (E.g. EW1)
void addMrtLine()
{
    string mrtPrefix;
    cout << "Please enter the prefix of your new mrt line [No numbers allowed]" << endl;
    cin >> mrtPrefix;
    cin.clear();
    cin.ignore(10000, '\n');

    // this is to make we remove any numbers from the input
    extractString(mrtPrefix);

    auto toUpperCase = [](string& str) {
        for (auto& c : str) c = toupper(c);
    };

    toUpperCase(mrtPrefix);

    // We check if the prefix already exists
    for (int i = 0; i < mrtlines.size(); i++)
    {
        if (mrtlines[i].getMrtPrefix() == mrtPrefix)
        {
            cout << "Mrt prefix already exists! " << endl;
            return;
        }
    }

    string mrtName;
    cout << "Please enter the name of your new mrt line/extension" << endl;
    std::getline(std::cin, mrtName);

    MrtLine mrtline(&graph);
    mrtline.setMrtPrefix(mrtPrefix);
    mrtline.setMrtLineName(mrtName);
    mrtlines.pushBack(mrtline);
}

/* SHORTEST PATH TO STATION BEGINS HERE*/
// The fucntion allows the user to enter a start and end station
// In order to get the shortest path
// Entries are rejected if they are the same station or
// If the station id provided does not exist
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

    // The graph shortest path func returns the shortest path
    // However it is from the end node to the start node
    // Thus, we need to print from the end to the start of the list
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

/* Helper func for add/remove mrt interchange*/
// This function acts as a validator for the add and remove connections between mrt lines
// It checks
// 1. If the stations given are the same
// 2. If the station ids provided exist
// 3. Stations given are on the same mrt line

bool removeAddMrtConnectionsValidation(string& fromNodeId, string& toNodeId)
{
    cout << "[Station IDs must be from different mrt lines]" << endl;
    auto printStep = [](string num) {
        cout << "Please enter the " << num << " station ID: " << endl;
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
        return false;
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
        return false;
    }

    if (extractString(fromNodeId) == extractString(toNodeId))
    {
        cout << "You have given stations on the same mrt line!" << endl;
        return false;
    }

    return true;
}

/* REMOVE STATION INTERCHANGE STARTS HERE*/
// This function allows the user to remove a connection
// Between two mrt lines/extensions
void removeStationInterchangeOrConnectionBetweenMrtLines()
{
    displayAllStations();
    string fromNodeId;
    string toNodeId;

    bool valid = removeAddMrtConnectionsValidation(fromNodeId, toNodeId);

    if (valid)
    {
        if (!(graph.hasConnection(fromNodeId, toNodeId)))
        {
            cout << "There are no connections between these two stations!" << endl;
            return;
        }
        else
        {
            // remove connection
            graph.removeConnection(fromNodeId, toNodeId);
            graph.removeConnection(toNodeId, fromNodeId);
        }
    }
}

/* REMOVE STATION INTERCHANGE ENDS HERE*/

/* ADD STATION INTERCHANGE BEGINS HERE*/
// This function allows the user to add a connection
// Between two mrt lines/extensions
void addStationInterchangeOrConnectionBetweenMrtLines()
{
    displayAllStations();
    string fromNodeId;
    string toNodeId;

    bool valid = removeAddMrtConnectionsValidation(fromNodeId, toNodeId);

    if (valid)
    {
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
}
/* ADD STATION INTERCHANGE ENDS HERE*/

/* REMOVE STATION METHODS BEGIN HERE*/
// This function allows the user to remove a mrt station
// From a line
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
        costBetweenStations = enterInputForInt();
    }

    mrt->removeStation(selected->id, costBetweenStations);
    mrt->printStationsAll();
}

// This function allows the user to remove a mrt station
// From a line
void removeStationToMrtLine()
{
    // based on that line print the train stations
    int lineSelected = enterInputForInt();
    if (lineSelected >= 0 && lineSelected < mrtlines.size())
    {
        MrtLine* mrt = &mrtlines[lineSelected];
        mrt->printStationsAll();
        cout << "Select a station index you want to remove" << endl;
        int station = enterInputForInt();

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

/* REMOVE STATION METHODS END HERE*/

/* ADD STATION METHODS BEGIN HERE*/
// For add stationDetails
void enterCostForAddStationDetails(int& beforeCost, int& afterCost, int beforeAfter, Node* selected,
                                   MrtLine* mrt, int station, string name)
{
    auto costBetweenText = [](string fromName, string toName) {
        cout << "Cost between " << fromName << " to " << toName << "?";
    };

    // beforeAfter states if the new station will be added before or
    // after the selected station
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

// This function allow the user to specify
// If they would like the new station before or after the selected station
void addStationDetails(int station, MrtLine* mrt)
{
    int beforeCost, afterCost = 0;
    string name;
    Node* selected = mrt->getMrtStation(station);
    cout << "[You have selected " << selected->name << "]" << endl;
    cout << "Would you like the new station to be before or after the selected station?" << endl;
    cout << "[0 == before/1 == after]" << endl;
    int beforeAfter = enterInputForInt();

    // Check range
    while (beforeAfter > 1 || beforeAfter < 0)
    {
        cout << "Enter the correct option (0 or 1)" << endl;
        beforeAfter = enterInputForInt();
    }

    cout << "What is the name of your station?" << endl;
    std::getline(std::cin, name);

    // Enter the details for cost between stations
    enterCostForAddStationDetails(beforeCost, afterCost, beforeAfter, selected, mrt, station, name);

    // Add new station and update costs
    mrt->addNewStation(selected->id, name, beforeAfter, beforeCost, afterCost);

    // Print all of the stations
    mrt->printStationsAll();
}

void addStationToMrtLineTest()
{
    // based on that line print the train stations
    int lineSelected = enterInputForInt();
    if (lineSelected >= 0 && lineSelected < mrtlines.size())
    {
        MrtLine* mrt = &mrtlines[lineSelected];

        // If there is no mrt stations
        // We cannot request for the index
        if (mrt->getSize() == 0)
        {
            string name;
            cout << "What is the name of your station?" << endl;
            std::getline(std::cin, name);
            Node* newStation = new Node();

            newStation->id = mrt->getMrtPrefix() + "1";
            newStation->name = name;
            dic.add(newStation->id, newStation);
            mrt->addStationFront(newStation);
        }
        // If there are mrt stations we can request for the index
        else
        {
            mrt->printStationsAll();
            cout << "Select a station index you would like to add your station to" << endl;
            // int station = enterInputForInt();
            int station = enterInputForString(trie, mrt->getMrtStationNames());

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
}
/* ADD STATION METHODS END HERE*/

// Function displays all of the mrt lines one can select
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
    cout << "Option 8: Quit" << endl;
    cout << endl;
}

int main()
{
    graph.setNodeList(&dic);

    // Fill up all the data structures.
    FileReader filereader(&graph, &dic, mrtlines, trie);

    // testing purposes as there is no unit tests
    // testVector();
    // testGraphConnections();
    // testDoublyLinkedList();
    // testDictionary();
    // testTrie(trie);

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
                // Add a train station
                case 1:
                    displayMrtLinesToSelect(addStationToMrtLineTest);
                    break;
                // Remove a train station
                case 2:
                    displayMrtLinesToSelect(removeStationToMrtLine);
                    break;
                // Add an interchange/connection between mrt lines
                case 3:
                    addStationInterchangeOrConnectionBetweenMrtLines();
                    break;
                // Remove an interchange/connection between mrt lines
                case 4:
                    removeStationInterchangeOrConnectionBetweenMrtLines();
                    break;
                // Add a new mrt line/extension
                case 5:
                    addMrtLine();
                    break;
                // Find the shortest path between stations
                case 6:
                    shortestPath();
                    break;
                // Print all Mrt Lines and stations
                case 7:
                    displayAllStations();
                    break;
                case 8:
                    option = -1;
                    break;
                // None of the above, go back.
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
