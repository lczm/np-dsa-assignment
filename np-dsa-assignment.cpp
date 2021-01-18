#include <iostream>
#include "structures/vector.h"

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

int main()
{
    cout << "np-dsa-assignment" << endl;

    // testing purposes as there is no unit tests
    testVector();

    return 0;
}
