#include <vector>
#include <iostream>
#include "cmdline.hpp" // parse_command
#include "app.hpp" // handle_expr_line

int main(int argc, char *argv[])
{
    std::vector<Commands::Command> cmd;
    std::string str;
    int i=1;
    while (true){
        if(i<argc){
            mapbox::util::variant<Commands::Print, Commands::Derive, Commands::Evaluate, Commands::Simplify> command = parse_command(argv[i]);
            cmd.push_back(command);
            i++;
        }else{
            break;
        }
    }
    while (getline(std::cin, str)) {
        handle_expr_line(std::cout, str, cmd);
    }
}
