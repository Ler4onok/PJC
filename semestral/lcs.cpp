#include "lcs.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>

namespace pjc {

    pjc::lcs::lcs(std::istream &stream) {
        std::string word;
        while (stream >> word)
            dictionary.insert(word);
    }


    std::tuple<std::string, int> pjc::lcs::check(const std::string& word) {
        int max_lcs = 0;
        std::string res;
        for(const auto& w : dictionary) {
            int lcs = get_lcs_of_2_strings(word, w);
            if (lcs > max_lcs){
                max_lcs = lcs;
                res = w;
            }
        }
        std::tuple<std::string, int> lala = std::make_tuple(res, max_lcs);
        return lala;
    }

    int max(int a, int b){
        return a>b? a:b;
    }

    int pjc::lcs::get_lcs_of_2_strings(std::string s1, std::string s2){
        int x = s1.length(), y = s2.length();
        int L[x+1][y+1];
        for(int i = 0; i<=x; i++){
            for(int j = 0; j<=y; j++){
                if(!j || !i) L[i][j] = 0;
                else if(s1[i-1] == s2[j-1]) L[i][j] = L[i-1][j-1] + 1;
                else L[i][j] = max(L[i][j-1], L[i-1][j]);
            }
        }
        return L[x][y];
    }
}
