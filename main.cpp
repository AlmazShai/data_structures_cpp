#include "Trie.hpp"

#include <format>
#include <iostream>

using namespace DataStructures;

int main(int argc, char* argv[])
{

    /* A trie data structure */
    Trie trie;
    std::vector<std::string> testStrings = { "abc", "abcd", "ac" };

    for (const auto& str : testStrings) {
        trie.insert(str);
        std::cout << std::format("Word [{}] inserted into the trie\n", str);
    }
    std::cout << "\n";

    testStrings.push_back("a");
    testStrings.push_back("abcde");
    for (const auto& str : testStrings) {
        if (trie.find(str)) {
            std::cout << std::format("The word [{}] is found in the trie\n", str);
        } else if (trie.findPrefix(str)) {
            std::cout << std::format("The prefix [{}] is found in the trie\n", str);
        } else {
            std::cout << std::format("The word|prefix [{}] is not found in the trie\n", str);
        }
    }

    return 0;
}