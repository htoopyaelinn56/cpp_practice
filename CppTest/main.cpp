#include "queue.hpp"
#include <string>

// pass by value
void modify(int a)
{
    a = 5;
}

// pass by ref
void modify_by_ref(int &a)
{
    a = 5;
}

int main()
{
    int b = -1;
    int &a = b;
    a = 5;

    modify(b);
    cout << b << endl;
    modify_by_ref(b);
    cout << b << endl;
    return 0;
}