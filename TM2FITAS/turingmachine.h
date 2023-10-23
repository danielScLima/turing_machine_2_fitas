#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <vector>
#include <iostream>
#include <Entry.h>
#include "tupleofidofacceptancestateandstructure.h"

using namespace std;

class TuringMachine
{
private:
    std::vector<std::vector<std::vector<Entry>>> structure;
    int start_state;
    int current_state;
    std::string input1;
    std::string input2;
    int current_index_of_input1 = -1;
    int current_index_of_input2 = -1;
    bool show_debug_messages;
    int id_of_acceptance_state;
    std::string nameOfTuringMachine;

    void reset();

    void write_to_file(const string &url, const string &content);
public:
    TuringMachine(bool show_debug_messages = false);

    std::vector<Entry> getTransitionsOfXStateToYState(int x, int y);

    void configureMachineSample(int index_of_sample);

    void configure_sample(TupleOfIdOfAcceptanceStateAndStructure p);

    void configure_input_string(const std::string& input);

    void consume_current_symbol();

    bool is_this_input_string_in_the_language(const std::string& input, bool make_draw);

    void is_this_input_string_in_the_language_with_message(const std::string &input, bool make_draw=false);

    std::string getCharTransformedAsString(char c);

    std::string produce_content_of_draw();

    //write_acceptance_status: 0=não desenhar 1=aceito 2=não aceita
    std::string produce_content_of_draw_considering_input
    (
        const string &message,
        int previous_input_symbol_index1,
        int previous_input_symbol_index2,
        int write_acceptance_status = 0
    );

    void draw_machine(const std::string& local_url, const std::string& url);

    //write_acceptance_status: 0=não desenhar 1=aceito 2=não aceita
    void draw_machine_considering_input
    (
        const std::string& local_url,
        const string &url,
        int index,
        const string &message,
        int previous_input_symbol_index1,
        int previous_input_symbol_index2,
        int write_acceptance_status = 0
    );

    std::string getNameOfTuringMachine();
};

#endif // TURINGMACHINE_H
