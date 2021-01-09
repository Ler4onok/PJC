#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include "lcs.h"

using namespace std;

int main(int argc, char** argv){
    pjc::lcs lcs;
    for(int argument = 1; argument < argc; argument++) {
        string option(argv[argument]);
        if (option == "--help"){
            cout << "\n"
                    "LCS (Longest Common Subsequence) is a command line tool for finding the longest common subsequence of 2, 3 or more words.\n"
                    "It has 3 modes and you can choose the needed.\n"
                    "\n"
                    "Usage:  [option] [words]\n"
                    "  option:\n"
                    "      -c: compare 2 or 3 written words. \n"
                    "      -d: takes your word and finds words in a dictionary with the largest LCS number. \n"

                 ;
            break;
        }
            //option compare
        else if (option == "-c"){
            argument++;
            //create a vector of the words from the command line
            vector<string> words = vector<string>();
            string word;

            for (int ii = 2; ii < argc; ii++){
                word = string(argv[argument]);
                // add the words from the command lite to the vector of words
                if (word.rfind('-', 0) != 0){
                    words.push_back(word);
                    argument++;
                }
                else{
                    // if the next argument contains "-" , it means it's another option
                    break;
                }
            }

            if (words.size() == 2){
                cout << "2 words were written.\n";
                int result = lcs.get_lcs_of_2_strings(words[0], words[1]);
                cout << "LCS of words " << words[0] << " and " << words[1] << " is " << result << ".\n";
                argument--;
            }
            else if (words.size() == 3){
                cout << "3 words were written.\n";
                int result = lcs.get_lcs_of_3_strings(words[0], words[1], words[2]);
                cout << "LCS of the words -" << words[0] << "-, -" << words[1] << "- and -" << words[2] << "- is " << result<< ".\n";
                argument--;
                // if there are more than 3 words in command line
            } else{
                cerr << "Wrong number of words! You can write only 2 or 3 words.\n";
                argument--;
            }

        } else if (option == "-f"){

            ifstream file;
            argument++;
            //to open a file edit a directory in the configurations
            // open the dictionary
            file.open(argv[argument]);
            if(file.is_open())
            {
                clog << "The file was successfully opened!\n";
                //read the words from the file
                lcs = pjc::lcs(file);
            }
            else{
                cerr << "Can not open a file. Check the path and try again.\n";
            }
            file.close();

            argument++;
            //read the word from the command line to compare with the words from the dictionary (txt file)
            std::string word = argv[argument];
            std::tuple<std::string, int> res = lcs.check(word);
            cout << "The largest LCS for the word -" << word <<  "- is " << std::get<1>(res) << " with the word -" << std::get<0>(res)<< "- from the dictionary.\n";
        }
            // if an unknown option was written
        else{
            cerr << "Please, choose the defined option: --help, -c or -f!\n";
            break;
        }

    }

}


