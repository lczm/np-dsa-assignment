#include "helper.h"

string extract_string(string str)
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
