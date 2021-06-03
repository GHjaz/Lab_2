#pragma once


#include <stdio.h>

class MyClass {

public:

 void testFunc1() {}
 virtual void testFunc3() const {}

protected:

    static void testFunc4() {
        printf( "Hello, world!\n" );
    }

private:

    static void testFunc2() {}

};
