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
    Dictionary<Node*> dic;
    Vector<DoublyLinkedList<Node*>> vector;
    graph.setNodeList(&dic);
    FileReader filereader(&graph, &dic, &vector);
    Vector<Connection*> c;


    graph.getAllConnectionsForNode("EW13", c);

    Vector<Connection*> d;
    graph.getAllConnectionsForNode("EW2", d);

    cout << "EW13 connections: ";
    for (uint32_t i = 0; i < c.size(); i++)
    {
        cout << c[i]->toNode->id << " ";
    }
    cout << " " << endl;
    cout << "EW2 connections: ";
    for (uint32_t i = 0; i < d.size(); i++)
    {
        cout << d[i]->toNode->id << endl;
    }

    cout << "Dictionary length: " <<  dic.getLength() << endl;
    cout << "Vector length: " << vector.size() << endl;
    cout << "First station in first line of the doubly linked list: " << vector.at(0).getAt(0)->name << endl;
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

}

void testDictionary()
{   
    Node* fromNodeAnother = new Node();

    // has interchange connections
    fromNodeAnother->id = "EW14";
    Dictionary<Node*> d;
    d.add(fromNodeAnother->id, fromNodeAnother);
    Node* nodetest = d.get("EW14");
    cout << nodetest->id << endl;


    Node toNode;
    toNode.id = "EW2";
    Dictionary<Node> nonPtr;
    nonPtr.add(toNode.id, toNode);
    Node nodetest2 = nonPtr.get("EW2");
    cout << nodetest2.id << endl;
}


//Menu_Function_Railway is a pointer to a function that takes no arguments
typedef void (*Menu_Function_Railway)(void);

struct Menu_Option
{
    char choice;
    char const* text;
    Menu_Function_Railway p_processing_function;
};

void option_One()
{   
    cout << "Hello there" << endl;
    return;
};
void option_Two()
{
    return;
};

static const Menu_Option main_menu[] = {
    {'1', "Option: 1", option_One},
    {'2', "Option: 2", option_Two},
};

//size of the entire thing divided by size of one array
static const size_t quantity_selections = sizeof(main_menu) / sizeof(main_menu[0]);
int main()
{
    cout << "np-dsa-assignment" << endl;

    // testing purposes as there is no unit tests
    testVector();
    testGraphConnections();
    testDoublyLinkedList();
    testDictionary();

    bool set = true;
    while (set)
    {
        string menu_title =
            "\n"
            "-------------------------------\n"
            "   Main Menu for railway inc\n"
            "-------------------------------\n";
        cout << menu_title << endl;
        for (int i = 0; i < quantity_selections; ++i)
        {
            std::cout << main_menu[i].text << "\n";
        }
        cout << "Enter option, press 0 to quit: ";
        char choice;
        cin >> choice;
        for (int i = 0; i < quantity_selections; ++i)
        {
            if (choice == main_menu[i].choice)
            {   
                cout << "\n";
                Menu_Function_Railway p_function = main_menu[i].p_processing_function;
                (p_function)();//executes function
                break;
            }
            else if (choice == '0')
            {
                set = false;
            }
            else
            {
                cout << "Please select the correct option" << endl;
                break;
            }
        }
    }
    return 0;
}
