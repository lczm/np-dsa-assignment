#include <iostream>
#include "structures/vector.h"
#include "Graph.h"
#include "FileReader.h"

using namespace std;

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
}

void testGraphConnections()
{
    Graph graph;
    FileReader filereader(&graph);

    filereader.readRoutes();
    filereader.readInterchanges();
    Node fromNode;

    //has interchange connections
    fromNode.id = "EW13";
    Node toNode;
    toNode.id = "EW2";

    Node toNode2;
    toNode2.id = "EW4";



    Vector<Connection*> c;
    graph.getAllConnectionsForNode(fromNode.id, c);

    Vector<Connection*> d;
    graph.getAllConnectionsForNode(toNode.id, d);

    cout << "EW13 connections: ";
    for (uint32_t i = 0; i < c.size(); i++)
    {
        cout << c[i]->toNodeId << " ";
    }
    cout << " " << endl;
    cout << "EW2 connections: ";
    for (uint32_t i = 0; i < d.size(); i++)
    {
        cout << d[i]->toNodeId << endl;
    }

}

int main()
{
    cout << "np-dsa-assignment" << endl;

    // testing purposes as there is no unit tests
    testVector();
    testGraphConnections();

    return 0;
}
