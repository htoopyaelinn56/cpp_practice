//
//  pointer_test.hpp
//  CppTest
//
//  Created by Htoo Pyae Linn on 29/02/2024.
//

#ifndef pointer_test_hpp
#define pointer_test_hpp

#include <iostream>
using namespace std;

namespace pointer_test
{

    void test1()
    {
        int i = 5;          // store in stack
        int *p = new int(); // allocate int in heap
        *p = 3;

        cout << *p << endl;

        delete p;
    }

    void test2()
    {
        int a = 3;
        int *p = &a;
        cout << "address of pointer " << &p << endl;
        cout << "pointer value " << *p << endl;
        cout << "size " << sizeof(a) << endl;
        cout << "address " << &a << endl;
        cout << "value " << *(&a) << endl;
    }

    void test3()
    {
        char ch1 = 'a', ch2 = 'b';
        char ch3[4] = {'c', 'd', 'e', 'f'};
        char *ptr[3];

        ptr[0] = &ch1;
        ptr[1] = &ch2;
        ptr[2] = ch3; // == &ch3[0]; ch3 itself is memory address

        cout << "value of ptr[0] " << *ptr[0] << endl;
        cout << "value of ptr[1] " << *ptr[1] << endl;
        cout << "value of ptr[2] " << *ptr[2] << endl;
        cout << "value of first item of ch3 " << ch3 << endl;
    }

    void test4()
    {
        int *p = new int;

        *p = 30;

        cout << "address of pointer " << &p << endl;
        cout << "pointer value " << *p << endl;

        (*p)++;

        cout << "new pointer value " << *p << endl;

        delete p;

        p = new int[2];

        *(p + 0) = 1;
        *(p + 1) = 2;

        cout << "pointer array p[0] " << *(p + 0) << endl;
        cout << "pointer array p[1] " << *(p + 1) << endl;

        // can access like array also

        p[0] = 5;
        p[1] = 6;

        cout << "pointer array p[0] " << p[0] << endl;
        cout << "pointer array p[1] " << p[1] << endl;

        delete[] p;
    }

    void test5()
    {
        int i;
        int *ptr;
        int **ptr2;

        i = 10;
        ptr = &i;
        ptr2 = &ptr;

        cout << i << endl;
        cout << *ptr << endl;
        cout << **ptr2 << endl;
    }

    int *add(int *a, int *b)
    {
        int *result = new int;
        *result = *a + *b;
        return result;
    }

    int add_normal(int a, int b)
    {
        return a + b;
    }

    void test6()
    {
        int (*a)(int, int) = &add_normal;

        int result = (*a)(5, 5);
    }

}

#endif /* pointer_test_hpp */
