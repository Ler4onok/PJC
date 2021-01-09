#include <cstddef>
#include <vector>
#include <iterator>
#include <set>

//#include <omp.h>

//using std::size_t;

namespace pjc {

    class lcs {

    private:

        std::set<std::string> dictionary;

    public:
        lcs() = default;

        explicit lcs(std::istream&);
        std::tuple<std::string, int> check(const std::string&);
        int get_lcs_of_2_strings(std::string s1, std::string s2);
//
    };
}

