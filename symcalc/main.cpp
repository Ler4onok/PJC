#include <vector>
#include <iostream>
#include "cmdline.hpp" // parse_command
#include "app.hpp" // handle_expr_line

using namespace std;

int main(int argc, char *argv[])
{
    int params = argc - 1;
    string str;

    vector<Commands::Command> commands(static_cast<unsigned int>(params));
    for(int i = 0; i < params; i++){
        commands[i] = parse_command(argv[i+1]);
    }

    while (getline(cin, str)) {
        handle_expr_line(cout, str, commands);
    }

    return 0;
}
