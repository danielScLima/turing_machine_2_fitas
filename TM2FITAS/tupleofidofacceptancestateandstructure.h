#ifndef TUPLEOFIDOFACCEPTANCESTATEANDSTRUCTURE_H
#define TUPLEOFIDOFACCEPTANCESTATEANDSTRUCTURE_H

#include <vector>
#include <Entry.h>
#include <string>

struct TupleOfIdOfAcceptanceStateAndStructure
{
    TupleOfIdOfAcceptanceStateAndStructure
    (
        int idOfAcceptanceState,
        std::vector<std::vector<std::vector<Entry>>> structure,
        std::string nameOfTuringMachine,
        int start_state
    )
    {
        this->idOfAcceptanceState = idOfAcceptanceState;
        this->structure = structure;
        this->nameOfTuringMachine = nameOfTuringMachine;
        this->start_state = start_state;
    }

    int idOfAcceptanceState;
    std::vector<std::vector<std::vector<Entry>>> structure;
    std::string nameOfTuringMachine;
    int start_state;
};

#endif // TUPLEOFIDOFACCEPTANCESTATEANDSTRUCTURE_H
