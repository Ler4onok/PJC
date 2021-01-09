#include "lcs.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <tuple>

namespace pjc {

    pjc::lcs::lcs(std::istream &stream) {
        std::string word;
        while (stream >> word) {
            // insert the words from the txt file to the dictionary
            dictionary.insert(word);
        }
    }


    std::tuple<std::string, int> pjc::lcs::check(const std::string& word) {
        int max_lcs = 0;
        std::string res;
        //get words from the dictionary
        for(const auto& w : dictionary) {
            // get the lcs num for every pair of words
            int lcs = get_lcs_of_2_strings(word, w);
            if (lcs > max_lcs){
                max_lcs = lcs;
                res = w;
            }
        }
        std::tuple<std::string, int> result = std::make_tuple(res, max_lcs);
        return result;
    }


    int max(int a, int b){
        return a>b? a:b;
    }

    int lcs::get_lcs_of_2_strings(std::string str1, std::string str2){

        int len1 = str1.length();
        int len2 = str2.length();

        int LCS[len1+1][len2+1];

        for(int i = 0; i<=len1; i++){

            for(int ii = 0; ii<=len2; ii++){

                if(ii == 0 || i == 0){
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

    int lcs::get_lcs_of_3_strings(std::string str1, std::string str2, std::string str3)
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

                    else if (str1[i-1] == str2[j-1] && str1[i-1] == str3[k-1]){
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
}
