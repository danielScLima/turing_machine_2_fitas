#include "turingmachine.h"
#include <algorithm>    // std::find
#include <fstream>

TuringMachine::TuringMachine(bool show_debug_messages)
{
    reset();
    this->show_debug_messages = show_debug_messages;
}

void TuringMachine::reset()
{
    current_state = 0;
    current_index_of_input1 = -1;
    current_index_of_input2 = -1;
}

std::vector<Entry> TuringMachine::getTransitionsOfXStateToYState(int x, int y)
{
    return this->structure[x][y];
}

void TuringMachine::configureMachineSample(int index_of_sample)
{

}

void TuringMachine::configure_sample
(
    TupleOfIdOfAcceptanceStateAndStructure p
    //int id_of_acceptance_state,
    //const std::vector<std::vector<std::vector<Entry>>> &structure,
    //std::string name
)
{
    this->id_of_acceptance_state = p.idOfAcceptanceState;
    this->structure = p.structure;
    this->nameOfTuringMachine = p.nameOfTuringMachine;
    this->start_state = p.start_state;
    reset();
}

void TuringMachine::configure_input_string(const std::string& input)
{
    this->input1 = input;

    this->input2 = input;
    for(int index = 0; index < this->input2.size(); ++index)
        this->input2[index] = 'B';

    reset();
}

void TuringMachine::consume_current_symbol()
{
    char current_char_input1 = this->input1[this->current_index_of_input1];
    char current_char_input2 = this->input2[this->current_index_of_input2];

    for(int dest_state_index = 0;dest_state_index < this->structure.size();dest_state_index++)
    {
        std::vector<Entry> entries = getTransitionsOfXStateToYState(
            this->current_state,
            dest_state_index
        );

        //if (this->show_debug_messages)
            //std::cout << "Chars: " << entries << std::endl;

        //if (chars.find(current_char_input) != std::string::npos)

        const auto look_for_char = [current_char_input1,current_char_input2](const Entry& entry){
            return entry.symbol_on_ribbon_1 == current_char_input1 && entry.symbol_on_ribbon_2 == current_char_input2;
        };
        const auto find_it = std::find_if(std::begin(entries), std::end(entries), look_for_char);

        if (find_it != entries.end())
        {
            //Encontrou uma transição definida

            //Vai para o seguinte estado: dest_state_index
            this->current_state = dest_state_index;

            //Deve alterar o símbolo atual para: find_it->symbol_to_write
            this->input1[this->current_index_of_input1] = find_it->symbol_to_write_on_ribbon_1;
            this->input2[this->current_index_of_input2] = find_it->symbol_to_write_on_ribbon_2;

            //Fita 1
            //Deve mover a posição de leitura na entrada de acordo com: find_it->movement
            if (find_it->movement_on_ribbon_1 == 'R')
            {
                if ( this->current_index_of_input1 < (this->input1.length()-1) )
                    this->current_index_of_input1++;
            }
            else if (find_it->movement_on_ribbon_1 == 'L')
            {
                if ( this->current_index_of_input1 > 0 )
                    this->current_index_of_input1--;
            }
            else if (find_it->movement_on_ribbon_1 == 'S')
            {}

            //Fita 2
            //Deve mover a posição de leitura na entrada de acordo com: find_it->movement
            if (find_it->movement_on_ribbon_2 == 'R')
            {
                if ( this->current_index_of_input2 < (this->input2.length()-1) )
                    this->current_index_of_input2++;
            }
            else if (find_it->movement_on_ribbon_2 == 'L')
            {
                if ( this->current_index_of_input2 > 0 )
                    this->current_index_of_input2--;
            }
            else if (find_it->movement_on_ribbon_2 == 'S')
            {}

            return;
        }
    }

    //Não encontrou uma transição definida
    throw std::exception();
}

bool TuringMachine::is_this_input_string_in_the_language(const std::string& input, bool make_draw)
{
    int index_to_image = 0;
    std::string local_url = "C:/Users/Daniel/Documents/GitHub/turing_machine_2_fitas/TM2FITAS/images";

    try
    {
        configure_input_string(input);

        draw_machine_considering_input(
            local_url,
            getNameOfTuringMachine()+"_"+std::to_string(index_to_image++)+".png",
            index_to_image,
            "Before to read any input",
            -1,
            -1,
            0     //acceptance status
        );

        this->current_index_of_input1 = 0;
        this->current_index_of_input2 = 0;
        int previous_input_symbol_index_1 = this->current_index_of_input1;
        int previous_input_symbol_index_2 = this->current_index_of_input2;

        while(true)
        {
            if (this->show_debug_messages)
            {
                std::cout << "Processando index " << std::to_string(this->current_index_of_input1) <<
                             " " << std::to_string(this->current_index_of_input2) << std::endl;
            }

            previous_input_symbol_index_1 = this->current_index_of_input1;
            previous_input_symbol_index_2 = this->current_index_of_input2;
            char backup_current_char_input1 = this->input1[this->current_index_of_input1];
            char backup_current_char_input2 = this->input2[this->current_index_of_input2];

            consume_current_symbol();

            std::cout << "previous_index_of_input1: " << std::to_string(previous_input_symbol_index_1) << std::endl;
            std::cout << "previous_index_of_input2: " << std::to_string(previous_input_symbol_index_2) << std::endl;

            draw_machine_considering_input(
                local_url,
                getNameOfTuringMachine()+"_"+std::to_string(index_to_image++)+".png",
                index_to_image,
                //"After to read "+std::string(1, this->input[previous_input_symbol_index]),
                "After to read "+std::string(1, backup_current_char_input1)+" "+std::string(1, backup_current_char_input2),
                previous_input_symbol_index_1,
                previous_input_symbol_index_2
            );

            if (this->current_state == this->id_of_acceptance_state)
            {
                draw_machine_considering_input(
                    local_url,
                    getNameOfTuringMachine()+"_"+std::to_string(index_to_image++)+".png",
                    index_to_image,
                    //"After to read "+std::string(1, this->input[previous_input_symbol_index]),
                    "After to read "+std::string(1, backup_current_char_input1)+" "+std::string(1, backup_current_char_input2),
                    -1, //previous_input_symbol_index1,
                    -1, //previous_input_symbol_index2,
                    1   //acceptance status: aceita
                );
                return true;
            }
        }
    }
    catch (std::exception ex)
    {
        draw_machine_considering_input(
            local_url,
            getNameOfTuringMachine()+"_"+std::to_string(index_to_image++)+".png",
            index_to_image,
            "",
            -1,
            2   //acceptance status: rejected
        );
        return false;
    }
}

void TuringMachine::is_this_input_string_in_the_language_with_message
(
    const std::string &input,
    bool make_draw
)
{
    bool ret = is_this_input_string_in_the_language(input, make_draw);

    if (ret)
        std::cout << "The word " << input << " was accepted!!" << std::endl;
    else
        std::cout << "The word " << input << " was NOT accepted!!" << std::endl;
}

std::string TuringMachine::produce_content_of_draw()
{
    std::string content = "digraph G {\n";
    content += "\tsubgraph cluster_1 {\n";
    content += "\t\tnode [style=filled];\n";
    content += "\t\tlabel = \"Turing Machine: "+this->nameOfTuringMachine+"\"\n"
        "\t\tcolor=blue;\n"
        "\n";

    for (int index = 0; index < this->structure.size(); ++index)
    {
        if (index == this->id_of_acceptance_state)
            content += "\t\tq"+std::to_string(index)+" [shape=\"doublecircle\"];\n";
        else
            content += "\t\tq"+std::to_string(index)+";\n";
    }

    for (int index = 0; index < this->structure.size(); ++index)
    {
        for (int index2 = 0; index2 < this->structure.size(); ++index2)
        {
            std::string s;
            std::vector<Entry> transitions = getTransitionsOfXStateToYState(index, index2);

            if (transitions.size() == 0)
                continue;

            for (int entryindex = 0;entryindex<transitions.size();entryindex++)
            {
                auto entry = transitions[entryindex];

                std::string tmp = std::string(1, entry.symbol_on_ribbon_1)+","+
                        std::string(1, entry.symbol_on_ribbon_2)+
                        " -> "+std::string(1, entry.symbol_to_write_on_ribbon_1)+","+
                        std::string(1, entry.symbol_to_write_on_ribbon_2)+
                        ","+std::string(1, entry.movement_on_ribbon_1)+
                        ","+std::string(1, entry.movement_on_ribbon_2);
                if (entryindex == 0)
                    s = tmp;
                else
                    s = s + "\n" + tmp;

            }

            content += "\t\tq"+std::to_string(index)+"->q"+std::to_string(index2)+
                    "[label=\""+s+"\"];\n";
        }
    }

    content += "x [color=white, label=\"\"];";
    content += "\t\tx->q"+std::to_string(this->start_state);

    content += "\t}\n"
        "\n"
        "}";

    return content;
}

std::string TuringMachine::getCharTransformedAsString(char c)
{
    if (c == '<')
        return std::string("&lt;");
    else if (c == '>')
        return std::string("&gt;");
    else
        return std::string(1, c);
}

std::string TuringMachine::produce_content_of_draw_considering_input
(
    const string &message,
    int previous_input_symbol_index1,
    int previous_input_symbol_index2,
    int write_acceptance_status
)
{
    std::string content = "digraph G {\n";

    content += "\tsubgraph cluster_0 {\n";
    content += "\t\tnode [shape=plaintext];\n";
    content += "\n";
    content += "struct1 [label=<<TABLE>\n";
    content += "<TR>\n";

    //string1
    for(int index = 0; index < this->input1.size();++index)
    {
        //if (index == previous_input_symbol_index)
        if (index == current_index_of_input1)
        {
            content += "<TD BGCOLOR=\"gray\"><FONT>"+getCharTransformedAsString(this->input1[index])+"</FONT></TD>\n";
        }
        else
        {
            content += "<TD><FONT>"+getCharTransformedAsString(this->input1[index])+"</FONT></TD>\n";
        }
    }

    content += "</TR>\n";
    content += "</TABLE>>];\n";
    content += "label = \"Word 1\";\n";
    content += "color=red;\n";
    content += "}\n";

    content += "\tsubgraph cluster_2 {\n";
    content += "\t\tnode [shape=plaintext];\n";
    content += "\n";
    content += "struct2 [label=<<TABLE>\n";
    content += "<TR>\n";

    //word2
    for(int index = 0; index < this->input2.size();++index)
    {
        //if (index == previous_input_symbol_index)
        if (index == current_index_of_input2)
        {
            content += "<TD BGCOLOR=\"gray\"><FONT>"+getCharTransformedAsString(this->input2[index])+"</FONT></TD>\n";
        }
        else
        {
            content += "<TD><FONT>"+getCharTransformedAsString(this->input2[index])+"</FONT></TD>\n";
        }
    }

    content += "</TR>\n";
    content += "</TABLE>>];\n";
    content += "label = \"Word 2\";\n";
    content += "color=red;\n";
    content += "}\n";


    content += "\tsubgraph cluster_1 {\n";
    content += "\t\tnode [style=filled];\n";
    content += "\t\tlabel = \"Turing Machine: "+message+"\"\n"
        "\t\tcolor=blue;\n"
        "\n";

    for (int index = 0; index < this->structure.size(); ++index)
    {
        if (index == this->current_state)
        {
            if (index == this->id_of_acceptance_state)
                content += "\t\tq"+std::to_string(index)+" [shape=\"doublecircle\",color=\"lightblue\"];\n";
            else
                content += "\t\tq"+std::to_string(index)+" [color=\"lightblue\"];\n";
        }
        else
        {
            if (index == this->id_of_acceptance_state)
                content += "\t\tq"+std::to_string(index)+" [shape=\"doublecircle\"];\n";
            else
                content += "\t\tq"+std::to_string(index)+";\n";
        }
    }

    for (int index = 0; index < this->structure.size(); ++index)
    {
        for (int index2 = 0; index2 < this->structure.size(); ++index2)
        {
            std::string s;
            std::vector<Entry> transitions = getTransitionsOfXStateToYState(index, index2);

            if (transitions.size() == 0)
                continue;

            for (int entryindex = 0;entryindex<transitions.size();entryindex++)
            {
                auto entry = transitions[entryindex];

                std::string tmp = std::string(1, entry.symbol_on_ribbon_1)+","+
                        std::string(1, entry.symbol_on_ribbon_2)+
                        " -> "+std::string(1, entry.symbol_to_write_on_ribbon_1)+","+
                        std::string(1, entry.symbol_to_write_on_ribbon_2)+
                        ","+std::string(1, entry.movement_on_ribbon_1)+
                        ","+std::string(1, entry.movement_on_ribbon_2);
                if (entryindex == 0)
                    s = tmp;
                else
                    s = s + "\n" + tmp;

            }

            content += "\t\tq"+std::to_string(index)+"->q"+std::to_string(index2)+
                    "[label=\""+s+"\"];\n";
        }
    }

    content += "x [color=white, label=\"\"];";
    content += "\t\tx->q"+std::to_string(this->start_state);

    content += "\t}\n"
        "\n";

    //inserir aceito ou rejeitado
    if (write_acceptance_status == 1)
    {
        content += "subgraph cluster_1s {\n"
                   "node [style=filled, shape=rect];\n"
                "cluster_1_n [label=\"Accepted word\", color=\"green\"];\n"
                "label = \"Status\";\n"
                "color=green;\n"
                "}\n"
                ;
    }
    else if(write_acceptance_status == 2)
    {
        content += "subgraph cluster_0s {\n"
                   "node [style=filled, shape=rect];\n"
                "cluster_0_n [label=\"Rejected word\", color=\"red\"];\n"
                "label = \"Status\";\n"
                "color=red;\n"
                "}\n"
                ;
    }

    content += "}";

    return content;
}


void TuringMachine::write_to_file(const string &url, const string &content)
{
    ofstream myfile;
    myfile.open (url);
    myfile << content;
    myfile.close();
}

void TuringMachine::draw_machine(const std::string& local_url, const string &url)
{
    std::string content = produce_content_of_draw();
    write_to_file(local_url+"/file.dot", content);
    std::string command = "dot "+local_url+"/file.dot -Tpng > "+local_url+"/"+url;
    system(command.c_str());
}

void TuringMachine::draw_machine_considering_input
(
    const std::string& local_url,
    const string &url,
    int index,
    const string &message,
    int previous_input_symbol_index1,
    int previous_input_symbol_index2,
    int write_acceptance_status
)
{
    std::string content = produce_content_of_draw_considering_input(
        message,
        previous_input_symbol_index1,
        previous_input_symbol_index2,
        write_acceptance_status
    );
    write_to_file(local_url+"/file"+std::to_string(index)+".dot", content);
    std::string command = "dot "+local_url+"/file"+std::to_string(index)+".dot -Tpng > "+local_url+"/"+url;
    system(command.c_str());
}

string TuringMachine::getNameOfTuringMachine()
{
    return this->nameOfTuringMachine;
}
