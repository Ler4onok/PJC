#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include "lcs.h"

using namespace std;

int max(int a, int b){
    return a>b? a:b;
}

int get_lcs_of_2_strings(string str1, string str2){

    int len1 = str1.length();
    int len2 = str2.length();

    int LCS[len1+1][len2+1];

    for(int i = 0; i<=len1; i++){

        for(int ii = 0; ii<=len2; ii++){

            if(!ii || !i){
                LCS[i][ii] = 0;
            }
            else if (str1[i-1] == str2[ii-1]) {
                LCS[i][ii] = LCS[i-1][ii-1] + 1;
            }
            else {
                LCS[i][ii] = max(LCS[i][ii-1], LCS[i-1][ii]);
            }
        }

    }
    return LCS[len1][len2];
}

int get_lcs_of_3_strings(string str1, string str2, string str3)
{

    int m = str1.length();
    int n = str2.length();
    int o = str3.length();

    int LCS[m+1][n+1][o+1];

    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            for (int k=0; k<=o; k++)
            {
                if (i == 0 || j == 0||k ==0){
                    LCS[i][j][k] = 0;

                }

                else if (str1[i-1] == str2[j-1] && str1[i-1]==str3[k-1]){
                    LCS[i][j][k] = LCS[i-1][j-1][k-1] + 1;
                }


                else{
                    LCS[i][j][k] = max(max(LCS[i-1][j][k], LCS[i][j-1][k]), LCS[i][j][k-1]);
                }

            }
        }
    }

    return LCS[m][n][o];
}

int main(int argc, char** argv){
//    vector<string> dictionary = vector<string>();
    pjc::lcs lcs;
//    sem::LCS lcs;
    for(int i = 1; i < argc; i++) {
        string argument(argv[i]);
        // add - check x
        if (argument == "--help"){
            cout << "\n"
                    "LCS (Longest Common Subsequence) is a command line tool for finding the longest common subsequence of 2, 3 or more words.\n"
                    "It has 3 modes and you can choose the needed.\n"
                    "\n"
                    "Usage:  [option] [words]\n"
                    "  option:\n"
                    "      -c: compare 2 or 3 written words. \n"
                    "      -d: takes your word and finds words in a dictionary with the largest LCS number. \n"

                 ;
        }
        else if (argument == "-c"){
            i++;
            vector<string> words = vector<string>();
            string word;

            for (int ii = 2; ii < argc;  ){
                word = string(argv[ii]);
                if (word.rfind('-', 0) != 0){
                    words.push_back(word);
                }
                ii++;
            }

            if (words.size() == 2){
                cout << "2 words were written\n";
                int result = get_lcs_of_2_strings(words[0], words[1]);
                cout << "LCS of words " << words[0] << " and " << words[1] << " is " << result;
            }
            else if (words.size() == 3){
                cout << "3 words were written\n";
                int result = get_lcs_of_3_strings(words[0], words[1], words[2]);
                cout << "LCS of words " << words[0] << ", " << words[1] << " and " << words[2] << " is " << result;
            } else{
                cerr << "Wrong number of words! You can write only 2 or 3 words.";
            }

        } else if (argument == "-f"){

            ifstream file;
            //to open a file edit a directory in the configurations
            file.open("words.txt");
            if(file.is_open())
            {
                clog << "The file was successfully opened!";
                //read the words from the file
                lcs = pjc::lcs(file);

            }
            else{
                cerr << "Can not open a file. Check the path and try again.";
            }

            file.close();
            std::string word = argv[3];
            std::tuple<std::string, int> res = lcs.check(word);
            cout << "The lcs for word " << word <<  " is " << std::get<1>(res) << " in word " << std::get<0>(res);





//            string filename(argv[++i]);
//            std::fstream myfile;
//            myfile.open("words.txt");
//            myfile << "lala";
//            lcs = pjc::lcs(myfile);
//            myfile.close();

        }

        else{
            cerr << "Please, choose the option!";
            break;
        }
    }

}


