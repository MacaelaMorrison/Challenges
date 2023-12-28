#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void findFirstAndLast(string str, int &num)
{
    string temp;
    if (str.length() == 1)
    {
        temp += str;
        temp += str;
    }
    else if (str.length() == 0)
    {
        return;
    }
    else
    {
        temp += str[0];
        temp += str[str.length() - 1];
    }
    num += stoi(temp);
}

void findDigit(string& str, int &num)
{
    string digits = "";
    for (char ch : str) 
    {
        if (isdigit(ch)) 
        {
            digits += ch;
        }  
    }
    if (digits.length() != 0)
    {
        findFirstAndLast(digits, num);
    } 
}

int main()
{
    fstream file;
    file.open("input.txt", ios::in);
    int num = 0;
    if (file.is_open())
    {
        string str;

        while (getline(file, str))
        {
            findDigit(str, num);
        }
    }
    file.close();
    cout << num << endl;
    return 0;
}