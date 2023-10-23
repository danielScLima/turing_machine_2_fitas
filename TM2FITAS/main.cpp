#include <QCoreApplication>

#include <turingmachinesamples.h>
#include <turingmachine.h>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    std::string local_url = "C:/Users/Daniel/Documents/GitHub/turing_machine_2_fitas/TM2FITAS/images";

    TuringMachine tm(true);

    //Questão 7
    tm.configure_sample(TuringMachineSamples::get_structure_of_q7());
    tm.draw_machine(local_url, tm.getNameOfTuringMachine()+".png");

    //tm.is_this_input_string_in_the_language_with_message("0#0BBB", true);   //Ex1: This must be accepted
    //tm.is_this_input_string_in_the_language_with_message("1#1BBB", true);   //Ex2: This must be accepted
    //tm.is_this_input_string_in_the_language_with_message("#BBB", true);   //Ex3: This must be accepted
    //tm.is_this_input_string_in_the_language_with_message("01#01BBB", true);   //Ex4: This must be accepted
    //tm.is_this_input_string_in_the_language_with_message("10#10BBB", true);   //Ex5: This must be accepted
    //tm.is_this_input_string_in_the_language_with_message("0#1BBB", true);   //Ex6: This must NOT be accepted
    //tm.is_this_input_string_in_the_language_with_message("1#0BBB", true);   //Ex7: This must NOT be accepted
    tm.is_this_input_string_in_the_language_with_message("01#10BBB", true);   //Ex8: This must NOT be accepted

    //return a.exec();
    return 0;
}
