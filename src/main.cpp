#include <cassert>

#include "Trie.hpp"
#include "SharedPtr.hpp"
#include "Vector.hpp"

#include <format>
#include <iostream>

using namespace DataStructures;
using namespace Memory;

struct TestStruct {
    TestStruct()
        : i(0), k(0.0)
    {
        std::cout << "TestStruct()\n";
    }

    ~TestStruct()
    {
        std::cout << "~TestStruct()\n";
    }

    TestStruct(const int i, const double k)
        : i (i), k(k)
    {
        std::cout << "TestStruct(const int i, const double k)\n";
    }

    TestStruct(const TestStruct& other)
        : i(other.i), k(other.k)
    {
        std::cout << "TestStruct(const TestStruct& other)\n";
    }

    TestStruct(TestStruct&& other) noexcept
        :i(other.i), k(other.k)
    {
        std::cout << "TestStruct(TestStruct&& other)\n";
    }

    TestStruct& operator=(const TestStruct& other)
    {
        i = other.i;
        k = other.k;
        std::cout << "TestStruct& operator=(const TestStruct& other)\n";
        return *this;
    }

    TestStruct& operator=(TestStruct&& other) noexcept
    {
        i = other.i;
        k = other.k;
        std::cout << "TestStruct& operator=(TestStruct&& other)\n";
        return *this;
    }

    int i;
    double k;

    bool operator==(const TestStruct& other) const {
        return i == other.i && k == other.k;
    }
};

int main()
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


    /* Vector */
    TestStruct val1(1, 3.0);
    Vector<TestStruct> vec1;
    vec1.pushBack(val1);
    assert(vec1.size() == 1);
    assert(vec1[0] == val1);

    vec1.emplaceBack(2,4.0);
    vec1.pushBack(TestStruct(1,1.0));


    return 0;
}