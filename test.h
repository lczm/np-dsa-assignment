#pragma once

#include "structures/vector.h"
#include "structures/trie.h"

static void testVector()
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

static void testTrie(Trie& trie)
{
    cout << "---testTrie---" << endl;

    trie.insert("0");
    trie.insert("a");
    trie.insert("A");
    trie.insert("Hello");
    trie.insert("HelloThere");
    trie.insert("Hey");
    trie.insert("Here");
    trie.insert("Boop");
    trie.insert("Book");
    trie.insert("EW1,PasirRis");

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

    Vector<string> completions3 = trie.complete("EW");
    for (uint32_t i = 0; i < completions3.size(); i++)
    {
        cout << completions3[i] << endl;
    }

    cout << "---" << endl;

    Vector<string> completions4 = trie.complete("East");
    for (uint32_t i = 0; i < completions4.size(); i++)
    {
        cout << completions4[i] << endl;
    }

    cout << "---testTrie---" << endl;
}

// static void testGraphConnections()
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

// static void testDoublyLinkedList()
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

// static void testDictionary()
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
