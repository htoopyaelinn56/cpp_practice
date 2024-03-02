//
//  pointer_test.hpp
//  CppTest
//
//  Created by Htoo Pyae Linn on 29/02/2024.
//

#ifndef pointer_test_hpp
#define pointer_test_hpp

#include<iostream>
using namespace std;

namespace pointer_test {
    void test()
    {
        int i = 5; // store in stack
        int* p = new int(); // allocate int in heap
        *p = 3;
        
        cout << *p << endl;
        
        delete p;
    }

}

#endif /* pointer_test_hpp */
