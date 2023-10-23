#include "turingmachinesamples.h"
#include <tupleofidofacceptancestateandstructure.h>

TuringMachineSamples::TuringMachineSamples()
{

}

TupleOfIdOfAcceptanceStateAndStructure TuringMachineSamples::get_structure_of_q7()
{
    std::vector<std::vector<std::vector<Entry>>> st = {
        //vetor partindo 0
        {
            {}, //vetor chegando no 0
            {Entry('0','B','T','T','R','R'),Entry('1','B','V','V','R','R')}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {}, //vetor chegando no 3
            {}, //vetor chegando no 4
            {Entry('#','B','#','#','R','R')}, //vetor chegando no 5
        },

        //vetor partindo do 1
        {
            {}, //vetor chegando no 0
            {Entry('0','B','X','X','R','R'),Entry('1','B','Y','Y','R','R')}, //vetor chegando no 1
            {Entry('#','B','#','#','P','L')}, //vetor chegando no 2
            {}, //vetor chegando no 3
            {}, //vetor chegando no 4
            {}, //vetor chegando no 5
        },

        //vetor partindo do 2
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {Entry('#','X','#','X','S','L'),Entry('#','Y','#','Y','S','L')}, //vetor chegando no 2
            {Entry('#','T','#','X','R','S'),Entry('#','V','#','Y','R','S')}, //vetor chegando no 3
            {}, //vetor chegando no 4
            {}, //vetor chegando no 5
        },

        //vetor partindo do 3
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {Entry('0','X','X','X','R','R'),Entry('1','Y','Y','Y','R','R')}, //vetor chegando no 3
            {Entry('B','#','B','#','R','R')}, //vetor chegando no 4
            {}, //vetor chegando no 5
        },

        //vetor partindo do 4
        //4 é o de aceitação
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {}, //vetor chegando no 3
            {}, //vetor chegando no 4
            {}, //vetor chegando no 5
        },

        //vetor partindo do 5
        {
            {}, //vetor chegando no 0
            {}, //vetor chegando no 1
            {}, //vetor chegando no 2
            {}, //vetor chegando no 3
            {Entry('B','B','B','B','R','R')}, //vetor chegando no 4
            {}, //vetor chegando no 5
        },
    };

    return TupleOfIdOfAcceptanceStateAndStructure(4, st, "Question7", 0);
}
