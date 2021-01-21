#include <iostream>
#include "structures/vector.h"
#include "Graph.h"

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

    Node fromNode;
    fromNode.id = "EW01";
    Node toNode;
    toNode.id = "EW02";

    Node toNode2;
    toNode2.id = "EW04";

    graph.addConnection(fromNode, toNode, 100);
    graph.addConnection(fromNode, toNode2, 100);

    Vector<Connection*> c;
    graph.getAllConnections(fromNode, c);

    Vector<Connection*> d;
    graph.getAllConnections(toNode, d);

    cout << "EW01 connections: ";
    for (uint32_t i = 0; i < c.size(); i++)
    {
        cout << c[i]->toNode.id << " ";
    }
    cout << " " << endl;
    cout << "EW02 connections: ";
    for (uint32_t i = 0; i < d.size(); i++)
    {
        cout << d[i]->toNode.id << endl;
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
