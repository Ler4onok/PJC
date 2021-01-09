#include <cstddef>
#include <vector>
#include <iterator>
#include <set>

namespace pjc {

    class lcs {

    private:
        std::set<std::string> dictionary;

    public:
        lcs() = default;

        explicit lcs(std::istream&);
        std::tuple<std::string, int> check(const std::string&);
        int get_lcs_of_2_strings(std::string str1, std::string str2);
        int get_lcs_of_3_strings(std::string str1, std::string str2, std::string std3);

    };
}

