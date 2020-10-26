#include "trie.hpp"

#include <utility>
#include <algorithm>
#include <iostream>
//#include <stack>
#include <queue>
#include <cassert>
#include <stack>

#define STRING_END '\0'

trie::trie() {
    m_size = 0;
    m_root = new trie_node;
}

trie::~trie() {
    // if root is empty
    if (m_root == nullptr) {

        m_root= nullptr;
        m_size=0;
    }
    // if trie exists
    else {
        //stack lifo queue fifo
        std::queue <trie_node* > trie;
        trie.push(m_root);

        while (!trie.empty()) {
            //check the children of root
            trie_node* parent_node = trie.front(); trie.pop();
            for (auto &child : parent_node->children) {
                if(child != nullptr){
                    //add children to queue to work with them later
                    trie.push(child);
                }
                else{
                    break;
                }
            }
            //delete parent because we get all his children
            delete parent_node;
        }
    }
}


trie::trie(std::vector<std::string> const &strings){
    //the first node to be created is root
    m_root = new trie_node;
    //add children to trie
    for (const auto &string : strings) {
        insert(string);
    }
}

int check_length(int length){
    if (length <= 0){
        return length+1;
    }
    return length;
}


bool trie::erase(const std::string &str) {
    int string_length = check_length(str.length());
    if (trie::contains(str)) {
        //start from root node
        auto* parent_node = m_root;
        for (int i = 0; i < string_length; i++) {
            //get letter for compare by index
            char letter_for_compare = str[i];
            //go through all the children
            for (auto &child : parent_node->children) {
                    //if child exists
                    //check child's value with letter of the word we search
                    if (child != nullptr && child->payload == letter_for_compare) {
                        //if they are equal go deeper and make this child parent
                        parent_node = child;
                        break;
                    }
            }
        }
        if (parent_node->is_terminal) {
            //if parent doesn't have children
            if (parent_node->children == nullptr) {
//                trie_node *parent = parent_node->parent;
//                for (auto& child : parent->children) {
//                    if (child) {
//                        if (child == parent_node) {
//                            break;
//                        }
//                    }
//                }
                delete (parent_node);
            } else {
                //to delete parent we need to delete all the children first
                parent_node->is_terminal = false;
            }
            m_size--;
            return true;
        }
    }
    return false;
}


//bool new_insert(trie_node* node, const char* ptr_char_array){
//    std::cout<<ptr_char_array;
//    std::cout<<ptr_char_array;
//}

bool equals(char char1, char char2){
   return char1 == char2;
}


bool trie::contains(const std::string &str) const {
    // len can't be 0 that's why check
    int string_length = check_length(str.length());
    // do if trie has nodes
    if (!trie::empty())  {
        trie_node* parent_node = m_root;
        for (int i = 0; i < string_length; i++) {
            char letter_for_compare = str[i];
            //check all children of the node
            for (auto &child : parent_node->children) {
                //such string do not exist
                if (child == nullptr) {
                    return false;
                }
                else{
                    //standard case
                    if (string_length > 1) {
                        //if search result and letter for compare are equal
                        if ( equals(child->payload, letter_for_compare)) {
                            //continue search
                                parent_node = child;
                                break;
                        }
                    } else {
                        //if string has only one or zero chars
                        if (child->is_terminal && equals(child->payload, letter_for_compare) ) {
                            parent_node = child;
                            break;

                        }
                    }
                }
            }
        }
        bool result = parent_node->is_terminal;
        return result;
    }

    return false;
}

bool trie::insert(const std::string &str) {
    // check len != 0
    int string_length = check_length(str.length());

    //if str is new in trie
    if (!(contains(str))){
        trie_node* current = m_root;
        if (current == nullptr){
            return false;
        }
        for (int i = 0; i < string_length; i++) {
            for (auto &child : current->children) {
                // if there is no such child
                if (child == nullptr) {
                    // create new node
                    auto* new_child = new trie_node;
                    //the end of str
                    new_child->is_terminal = string_length==1;
                    new_child->parent = current;
                    new_child->payload = str[i];
                    child = new_child;
                    current = child;
                    break;

                } else {
                    // if such child exist, continue
                    if (equals(child->payload, str[i])) {
                        current = child;
                        break;
                    }

                }
            }
        }
        m_size++;
        current->is_terminal = true;
        return true;
    }

    return false;
}

trie_node *find_next(const trie_node *node, const char prev) {
    for (const auto &child : node->children) {
        if (!child) continue;
        if (child->payload <= prev) continue;
        return child->is_terminal ? child : find_next(child, STRING_END);
    }
    trie_node* found_node;
    if (node->parent){
       found_node = find_next(node->parent, node->payload);
    }
    else{
        found_node = nullptr;
    }
    return found_node;
}

bool trie::empty() const {
    bool is_empty = m_size == 0;
    return is_empty;
}

size_t trie::size() const {
    return m_size;
}

trie::const_iterator trie::begin() const {
    trie_node *parent_node = m_root;

    while (true) {
        if (parent_node != nullptr){
            if (parent_node->children[0] != nullptr) {
                parent_node = parent_node->children[0];
            }

            if (parent_node->is_terminal) {
                break;
            }

        }
        else{
            break;
        }

    }
    return parent_node;

}

trie::const_iterator trie::end() const {
    return nullptr;
}



trie &trie::operator=(const trie &rhs) {
    std::cout<<'Y';
    return *this;
}

trie::trie(trie &&rhs) {
    m_root = rhs.m_root;
    rhs.m_root = nullptr;
}

trie::trie(const trie &rhs) {
    std::cout<<'h';
}

trie &trie::operator=(trie &&rhs) {
    
    std::vector<trie_node *> to_del;
    std::stack<trie_node *> stack;
    stack.push(m_root);
    while (!stack.empty()) {
        trie_node* curr = stack.top();stack.pop();
        if (curr == nullptr)continue;
        for (auto child : curr->children) {
            if (child != nullptr){
                stack.push(child);
            } 
        }
        
        to_del.push_back(curr);
    }
    for (auto r : to_del) {
        delete r;
    }
    
    m_root = rhs.m_root;
    m_size = rhs.m_size;
    
    rhs.m_root = nullptr;
    rhs.m_size = 0;
    return *this;
}


std::vector<std::string> trie::search_by_prefix(const std::string &prefix) const {
    return std::vector<std::string>();
}

std::vector<std::string> trie::get_prefixes(const std::string &str) const {
    return std::vector<std::string>();

}

bool trie::operator==(const trie &rhs) const {
    return false;

}

bool trie::operator<(const trie &rhs) const {
    return false;
}

trie trie::operator&(trie const &rhs) const {
    return trie();
}

trie trie::operator|(trie const &rhs) const {
    return trie();

}

void trie::swap(trie &rhs) {
}


bool operator!=(const trie &lhs, const trie &rhs) {
    return false;
}

bool operator<=(const trie &lhs, const trie &rhs) {
    return false;
}

bool operator>(const trie &lhs, const trie &rhs) {
    return false;
}

bool operator>=(const trie &lhs, const trie &rhs) {
    return false;
}

void swap(trie &lhs, trie &rhs) {

}


trie::const_iterator::const_iterator(const trie_node *node) {
    current_node = node;
}

trie::const_iterator &trie::const_iterator::operator++() {
    current_node = find_next(current_node, STRING_END);
    return *this;
}

trie::const_iterator trie::const_iterator::operator++(int x) {
    for (int i = 0; i < x + 1; ++i) {
        current_node = find_next(current_node, STRING_END);
    }
    return *this;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    std::string x;
    const trie_node* current = current_node;
    while (current != nullptr && current->payload) {
        x = current->payload + x;
        current = current->parent;
    }
    return x;
}

bool trie::const_iterator::operator==(const trie::const_iterator &rhs) const {
    return current_node == rhs.current_node;
}

bool trie::const_iterator::operator!=(const trie::const_iterator &rhs) const {
    return current_node != rhs.current_node;
}

std::ostream &operator<<(std::ostream &out, trie const &trie) {
    return out;
}