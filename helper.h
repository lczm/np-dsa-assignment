#pragma once

#include <string>
using namespace std;

static string extractString(string str)
{
    string lineIdentifier;

    for (int i = 0; i < str.size(); i++)
    {
        if (isalpha(str[i]))
        {
            lineIdentifier += str[i];
        }
    }

    return lineIdentifier;
}