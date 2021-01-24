#include <iostream>
#include "structures/vector.h"
#include "Graph.h"
#include "FileReader.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"

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
    filereader.readStations();
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

void testDoublyLinkedList()
{
    Node * fromNode = new Node();

    // has interchange connections
    fromNode->id = "EW13";


    Node* fromNodeAnother = new Node();

    // has interchange connections
    fromNodeAnother->id = "EW14";

    Node toNode;
    toNode.id = "EW2";

    Node toNode2;
    toNode2.id = "EW4";

    DoublyLinkedList<Node> list;
    list.addFront(toNode);
    cout <<"size of doubly: " << list.getSize() << endl;
    list.remove(toNode);
    cout << "size of doubly: " << list.getSize() << endl;
   
     list.addFront(toNode);
     Node node = list.getAt(0);
     cout << node.id << endl;


    DoublyLinkedList<Node*> listptr;
    listptr.addFront(fromNode);
    cout << "size of doubly: " << listptr.getSize() << endl;
    listptr.remove(fromNode);
    cout << "size of doubly: " << listptr.getSize() << endl;

    listptr.addFront(fromNode);
    listptr.addFront(fromNodeAnother);
    cout << "size of doubly: " << listptr.getSize() << endl;
    listptr.removeAt(0);
    cout << "size of doubly: " << listptr.getSize() << endl;

    Node * getNode = listptr.getAt(0);
    cout << getNode->id << endl;


    //Dictionary 
    Dictionary<Node*> * d = new Dictionary<Node*>();
    d->add(fromNodeAnother->id, fromNodeAnother);
    Node* nodetest = d->get("EW14");
    cout << nodetest->id << endl;
}

int main()
{
    cout << "np-dsa-assignment" << endl;

    // testing purposes as there is no unit tests
    testVector();
    testGraphConnections();
    testDoublyLinkedList();

    return 0;
}
