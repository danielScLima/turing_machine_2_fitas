#ifndef ENTRY_H
#define ENTRY_H

struct Entry
{
    Entry
    (
        char symbol_on_ribbon_1,
        char symbol_on_ribbon_2,
        char symbol_to_write_on_ribbon_1,
        char symbol_to_write_on_ribbon_2,
        char movement_on_ribbon_1,
        char movement_on_ribbon_2
    )
    {
        this->symbol_on_ribbon_1 = symbol_on_ribbon_1;
        this->symbol_on_ribbon_2 = symbol_on_ribbon_2;
        this->symbol_to_write_on_ribbon_1 = symbol_to_write_on_ribbon_1;
        this->symbol_to_write_on_ribbon_2 = symbol_to_write_on_ribbon_2;
        this->movement_on_ribbon_1 = movement_on_ribbon_1;
        this->movement_on_ribbon_2 = movement_on_ribbon_2;
    }

    char symbol_on_ribbon_1;
    char symbol_on_ribbon_2;
    char symbol_to_write_on_ribbon_1;
    char symbol_to_write_on_ribbon_2;
    char movement_on_ribbon_1;
    char movement_on_ribbon_2;
};

#endif // ENTRY_H
