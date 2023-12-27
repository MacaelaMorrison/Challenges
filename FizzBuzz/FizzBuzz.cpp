#include <iostream>
#include <vector>
using namespace std;

void printIfMultiple(int num)
{
    if (num % 3 == 0 && num % 5 == 0)
    {
        cout << "FizzBuzz" << endl;
    }
    else if (num % 3 == 0)
    {
        cout << "Fizz" << endl;
    }
    else if (num % 5 == 0)
    {
        cout << "Buzz" << endl;
    }
    else
    {
        cout << num << endl;
    }
}

int main() 
{ 
    vector<int> list;

    for (int i = 0; i <= 100; i++)
    {
        list.push_back(i);        
    } 

    for (int i = 1; i < 101; i++)
    {
        printIfMultiple(list.at(i));      
    }
    return 0;
}