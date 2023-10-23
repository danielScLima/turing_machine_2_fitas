#ifndef TURINGMACHINESAMPLES_H
#define TURINGMACHINESAMPLES_H

#include <vector>
#include <iostream>

using namespace std;

#include <Entry.h>
#include "tupleofidofacceptancestateandstructure.h"


class TuringMachineSamples
{
public:
    TuringMachineSamples();

    static TupleOfIdOfAcceptanceStateAndStructure get_structure_of_q7();
};

#endif // TURINGMACHINESAMPLES_H
