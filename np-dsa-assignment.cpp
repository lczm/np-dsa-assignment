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
        test.push_back(i);
        cout << test[i] << endl;
    }
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

    graph.addNode(fromNode);
    graph.addNode(toNode);
    graph.addNode(toNode2);

    graph.addConnection(fromNode, toNode, 100);
    graph.addConnection(fromNode, toNode2, 100);

    Vector<Connection*> c;
    graph.getAllConnectionsForNode(fromNode, c);

    Vector<Connection*> d;
    graph.getAllConnectionsForNode(toNode, d);


    cout << "EW01 connections: ";
    for (uint32_t i = 0; i < c.size(); i++)
    {
        cout << c[i]->toNode.id << " ";
    }
    cout << " "<< endl;
    cout << "EW02 connections: ";
    for (uint32_t i = 0; i < d.size(); i++)
    {
        cout << d[i]->toNode.id << endl;
    }

    cout << "All node" << endl;
    Vector<Node*> n;
    graph.getAllNodesFromGraph(n);

    for (uint32_t i = 0; i < n.size(); i++)
    {
        cout << n[i]->id << endl;
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
