#ifndef TESTUNIT_H
#define TESTUNIT_H
#include <stdio.h>
#include "Stock.h"
#include "Option.h"
#include "Price_Option.h"

class testUnit
{
    public:
        testUnit();
        virtual ~testUnit();
        void testCallPrice();
        void testCallImpliedVol();
        int testing_func();

    protected:

    private:
};

#endif // TESTUNIT_H
