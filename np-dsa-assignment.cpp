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
Dictionary<Trie*> trieMapping;
Dictionary<string> nameToIdMapping;
Vector<uint32_t> fares;
Vector<float> distances;

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

int enterInputForString(Vector<string> names, uint32_t lineSelected = -1)
{
    string inputString;

    // Get the prefix and only show the trie for the given prefix.
    // This is so that the trie doesnt suggest something that is
    // out of the scope of the acceptable values.
    Trie* trie;
    if (lineSelected == -1)
    {
        trie = trieMapping.get("all");
    }
    else
    {
        MrtLine mrtLine = mrtlines[lineSelected];
        string prefix = mrtLine.getMrtPrefix();
        trie = trieMapping.get(prefix);
    }

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

            // There is nothing to enter, just continue
            if (inputString.size() == 0)
            {
                continue;
            }

            // If the string input are integers, convert the string to an int and return
            if (std::all_of(inputString.begin(), inputString.end(), ::isdigit))
            {
                return stoi(inputString);
            }
            else  // Otherwise, it is a string. Check if it matches the names
            {
                for (uint32_t i = 0; i < names.size(); i++)
                {
                    if (names[i] == inputString)
                    {
                        return i;
                    }
                }
                cout << "Not found : please check your spelling!" << endl;
            }
        }
        else if (c == '\b')  // Backspace key
        {
            // Remove the last character, if the string is not empty.
            if (!inputString.empty()) inputString.pop_back();

            // VT100 escape code. Supported on Windows 10
            // Clears the current line before CR
            // Without this, the user would not see the 'deleted key'
            printf("%c[2K", 27);
        }
        else if (c == '\t')  // Tab key
        {
            Vector<string> suggestions = trie->complete(inputString);

            // If there is only one suggestion left. Just make this the inputString
            // Note that there is no need to do anything is there are 0 completions.
            if (suggestions.size() == 1)
            {
                inputString = suggestions[0];
            }
            else if (suggestions.size() > 1)
            {
                // Clear the output buffer and flush the buffer before printing
                printf("%c[2K", 27);
                cout << "\r" << flush;

                cout << "Suggestions for : " << inputString << endl;
                for (uint32_t i = 0; i < suggestions.size(); i++)
                {
                    cout << suggestions[i] << endl;
                }
                cout << endl;
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

    // Add new prefix to the dictionary and insert the trie
    trieMapping.add(mrtPrefix, new Trie());
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
        cout << "Please enter the station ID or station name you would like to " << startEnd
             << " at" << endl;
    };

    cout << "[Station IDs are case sensitive]" << endl;
    Vector<string> names;
    Vector<string> stationIds;

    nameToIdMapping.getAllKeys(names);
    dic.getAllKeys(stationIds);

    Vector<string> merge;
    for (uint32_t i = 0; i < names.size(); i++)
    {
        merge.pushBack(names[i]);
    }
    for (uint32_t i = 0; i < stationIds.size(); i++)
    {
        merge.pushBack(stationIds[i]);
    }

    printStep("start");
    // cin >> fromNodeId;
    int fromIndex = enterInputForString(merge);
    // if (nameToIdMapping.hasKey(merge[fromIndex]))
    if (fromIndex < names.size())
    {
        fromNodeId = nameToIdMapping.get(merge[fromIndex]);
    }
    else
    {
        fromNodeId = merge[fromIndex];
    }

    printStep("end");
    // cin >> toNodeId;
    int toIndex = enterInputForString(merge);
    // if (nameToIdMapping.hasKey(merge[toIndex]))
    if (toIndex < names.size())
    {
        toNodeId = nameToIdMapping.get(merge[toIndex]);
    }
    else
    {
        toNodeId = merge[toIndex];
    }

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

    uint32_t totalCost = 0;

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
            totalCost += connections[i]->cost;
        }

        // Convert total cost into kilometers.
        float costInKms = totalCost / 1000;

        // Calculate the index using the distance : fare vec-vec mapping
        uint32_t fareIndex = 0;
        for (uint32_t i = 0; i < distances.size(); i++)
        {
            if (costInKms < distances[i])
            {
                // First index to satisfy the minimum distance.
                fareIndex = i;
                break;
            }
        }

        // Calculate the price in dollars instead of cents
        float fare = fares[fareIndex];

        uint32_t dollars = 0;
        uint32_t cents = 0;
        dollars = floor(fare / 100);
        cents = fare - (dollars * 100);

        cout << "Total cost : $" << dollars << "." << cents << endl;
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
        cout << "Please enter the " << num << " station ID or station name: " << endl;
    };

    cout << "[Station IDs are case sensitive]" << endl;
    Vector<string> names;
    Vector<string> stationIds;

    nameToIdMapping.getAllKeys(names);
    dic.getAllKeys(stationIds);

    Vector<string> merge;
    for (uint32_t i = 0; i < names.size(); i++)
    {
        merge.pushBack(names[i]);
    }
    for (uint32_t i = 0; i < stationIds.size(); i++)
    {
        merge.pushBack(stationIds[i]);
    }

    printStep("first");
    // cin >> fromNodeId;
    int fromIndex = enterInputForString(merge);
    if (fromIndex < names.size())
    {
        fromNodeId = nameToIdMapping.get(merge[fromIndex]);
    }
    else
    {
        fromNodeId = merge[fromIndex];
    }

    printStep("second");
    // cin >> toNodeId;
    int toIndex = enterInputForString(merge);
    if (toIndex < names.size())
    {
        toNodeId = nameToIdMapping.get(merge[toIndex]);
    }
    else
    {
        toNodeId = merge[toIndex];
    }

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
        cout << "Distance between " << prevStation->name << " and " << afterStation->name
             << " in meters? " << endl;
        costBetweenStations = enterInputForInt();
    }

    mrt->removeStation(selected->id, costBetweenStations);
    mrt->printStationsAll();

    trieMapping.get(mrt->getMrtPrefix())->remove(selected->name);
    trieMapping.get("all")->remove(selected->name);
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
        cout << "Select a station index or station nameyou want to remove" << endl;
        // int station = enterInputForInt();
        int station = enterInputForString(mrt->getMrtStationNames(), lineSelected);

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
        cout << "Distance between " << fromName << " to " << toName << " in meters?";
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

    // Insert the new name into the trieMapping
    trieMapping.get(mrt->getMrtPrefix())->insert(name);
    trieMapping.get("all")->insert(name);
}

void addStationToMrtLine()
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

            trieMapping.get(mrt->getMrtPrefix())->insert(name);
            trieMapping.get("all")->insert(name);
        }
        // If there are mrt stations we can request for the index
        else
        {
            mrt->printStationsAll();
            cout << "Select a station index or station name you would like to add your station to"
                 << endl;
            // int station = enterInputForInt();
            int station = enterInputForString(mrt->getMrtStationNames(), lineSelected);

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
    cout << "Welcome to Railway inc. " << endl;
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
    FileReader filereader(&graph, &dic, mrtlines, distances, fares);

    Vector<string> keys;
    Vector<Node*> values;
    dic.getAllKeys(keys);
    dic.getAllItems(values);

    // Init nameToIdMapping
    for (uint32_t i = 0; i < keys.size(); i++)
    {
        nameToIdMapping.add(values[i]->name, keys[i]);
    }

    // Has all the stations.
    trieMapping.add("all", new Trie());

    // Fill up trie with station names
    for (uint32_t i = 0; i < mrtlines.size(); i++)
    {
        string prefix = mrtlines[i].getMrtPrefix();

        if (!trieMapping.hasKey(prefix))
        {
            Trie* trie = new Trie();
            trieMapping.add(prefix, new Trie());
            trieMapping.get(prefix)->insert(mrtlines[i].getMrtStationNames());
            trieMapping.get("all")->insert(mrtlines[i].getMrtStationNames());
        }
    }

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
                // Add a train station
                case 1:
                    displayMrtLinesToSelect(addStationToMrtLine);
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
