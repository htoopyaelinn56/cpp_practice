#include <iostream>
using namespace std;

int sumToNthTail(int n, int accumulator)
{
    if (n == 0)
        return accumulator;
    return sumToNthTail(n - 1, accumulator + n);
}

int sumToNthNonTail(int n)
{
    if (n == 0)
        return 0;
    return n + sumToNthNonTail(n - 1);
}

int main()
{
    // sumToNthTail(3, 0) Return 3
    // -> sumToNthTail(2, 3) Return 5
    // -> sumToNthTail(1, 5) Return 6
    // -> sumToNthTail(0, 6) Return 6 *Base Case
    cout << "tail recursion" << endl;
    cout << sumToNthTail(3, 0) << endl;

    cout << endl;

    // sumToNthNonTail(3) Stack 1
    // -> sumToNthNonTail(2) Stack 2
    // -> sumToNthNonTail(1) Stack 3
    // -> sumToNthNonTail(0) Stack 4 *Base Case Return 0
    // Goes to Stack 3 -> Return 1+0 = 1
    // Goes to Stack 2 -> Return 2+1 = 3
    // Goes to Stack 1 -> Return 3+3 = 6
    cout << "non tail recursion" << endl;
    cout << sumToNthNonTail(3) << endl;

    return 0;
}