#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

void splitString(string str, vector<int>& numVector, vector<int>& numVector2, vector<int>& numVector3);
void extractInt(string inStr, string inStr2, vector<int>& numVector, vector<int>& numVector2, vector<int>& numVector3);

void extractInt(string inStr, string inStr2, vector<int> &numVector, vector<int> &numVector2, vector<int> &numVector3)
{
    stringstream str1, str2;

    str1 << inStr;
    

    string temp;
    int num;

    numVector.clear();
    numVector2.clear();

    

    while (!str1.eof()) //Extract each word
    {
        
        str1 >> temp;

        if ((stringstream(temp) >> num))
        {
            numVector.push_back(stoi(temp));
        }
        
        temp = "";
    }


    str2 << inStr2;
    num = 0;
    while (!str2.eof()) 
    {
        str2 >> temp;

        if ((stringstream(temp) >> num))
        {
            numVector2.push_back(stoi(temp));
        }

        temp = "";
    }
    
    /*Debug code
    for (int i = 0; i < numVector.size(); i++ )
    {
        cout << " Vector 2 Index " << i << " number " << numVector[i] << " ";
   
    }
    cout << endl;
    for (int i = 0; i < numVector2.size(); i++)
    {
        cout << " Index " << i << " number" << numVector2[i] << " ";
    }
    
   
    cout << "Matches " << match << endl;
    cout << "Temp total " << tempTotal << endl;
    cout << "Total " << total << endl;*/
    
}

void splitString(string str, vector<int>& numVector, vector<int>& numVector2, vector<int>& numVector3)
{
    regex pattern("\\w+\\s+\\d+:(\\s+(?:\\d+\\s+)+)\\|((?:\\s+\\d+)+)");
    string firstPart, secondPart;
    smatch match;

    if (regex_match(str, match, pattern)) 
    {
        
        firstPart = match[1];
        secondPart = match[2];

        //Debug code
        //cout << "First part: " << firstPart << std::endl;
        //cout << "Second part: " << secondPart << std::endl;
    }
    else 
    {
        std::cout << "Error: No match found." << std::endl;
    }
    extractInt(firstPart, secondPart, numVector, numVector2, numVector3);
}

int calcTotal(int &total, vector<int>& numVector, vector<int>& numVector2)
{
    int match = 0;
    int tempTotal = 0;
    bool firstMatch = false;
    for (auto& i : numVector) //Loop through each element of v1
        for (auto& j : numVector2)
        {//Same for v2

            if (i == j)
            {

                match++;
                if (!firstMatch)
                {
                    tempTotal += 1;
                    firstMatch = true;
                }
                else
                {
                    tempTotal = tempTotal * 2;
                }

            }
        }

        return total += tempTotal;
}


int main()
{
    fstream file;
    int total = 0;
    file.open("input2.txt", ios::in);
    vector<int> numVector;
    vector<int> numVector2;
    vector<int> numVector3;

    if (file.is_open())
    {
        string str;

        while (getline(file, str))
        {
            splitString(str, numVector, numVector2, numVector3);
            total = calcTotal(total, numVector, numVector2);
            
        }
    }
    cout << total << endl;
    file.close();
}
