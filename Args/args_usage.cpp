#include <iostream>

#include "args.hpp"

/**
 * argv: -l -p 8080 -d /usr/logs
 * 
 * -l: boolean flag, true is present, false if not
 * -p: port has a integer value
 * -d: directory has a string value
 */
int main(int argc, char const* argv[]) {
    if (argc > 1) {
        try {
            std::vector<std::string> arg_str(argv + 1, argv + argc);
            Args* args = new Args("l, p#, f##, d*", arg_str);
            bool logging = args->get_bool('l');
            int port = args->get_int('p');
            double time = args->get_double('f');
            std::string directory = args->get_string('d');
            std::cout << "bool[" << logging << "] int[" << port << "] double[" << time << "] string[" << directory << "]" << std::endl;
        } catch (ArgsException& e) {
            // std::cerr << e.what() << '\n';
        }
    }

    return 0;
}
