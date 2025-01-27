#include <cassert>

#include "Trie.hpp"
#include "SharedPtr.hpp"

#include <format>
#include <iostream>

using namespace DataStructures;
using namespace Memory;

struct TestStruct {
    int i;
    int j;
    double k;
};

int main(int argc, char* argv[])
{

    /* A trie data structure */
    Trie trie;
    std::shared_ptr<int> ptr;
    std::vector<std::string> testStrings = { "abc", "abcd", "ac" };

    for (const auto& str : testStrings) {
        trie.insert(str);
        std::cout << std::format("Word [{}] inserted into the trie\n", str);
    }
    std::cout << "\n";

    testStrings.emplace_back("a");
    testStrings.emplace_back("abcde");
    for (const auto& str : testStrings) {
        if (trie.find(str)) {
            std::cout << std::format("The word [{}] is found in the trie\n", str);
        } else if (trie.findPrefix(str)) {
            std::cout << std::format("The prefix [{}] is found in the trie\n", str);
        } else {
            std::cout << std::format("The word|prefix [{}] is not found in the trie\n", str);
        }
    }


    /* Smart pointer */
    SharedPtr ptr1(new TestStruct());
    {
        SharedPtr ptr2 = ptr1;
        assert(ptr2.getCount() == 2);
        assert(ptr2.getCount() == ptr1.getCount());

        SharedPtr ptr3(ptr2);
        assert(ptr3.getCount() == 3);
        assert(ptr3.getCount() == ptr2.getCount());

        SharedPtr ptr4(std::move(ptr3));
        assert(ptr4.getCount() == 3);
        assert(ptr3.getCount() == 0);

        SharedPtr<TestStruct> ptr5;
        ptr5 = std::move(ptr4);
        assert(ptr5.getCount() == 3);
        assert(ptr4.getCount() == 0);
        assert(ptr1.getCount() == 3);

    }
    assert(ptr1.getCount() == 1);

    ptr1.reset(nullptr);
    assert(ptr1.getCount() == 0);

    return 0;
}