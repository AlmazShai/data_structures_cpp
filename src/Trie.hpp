#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace DataStructures {

class Trie {
public:
    Trie() {};

    explicit Trie(const std::vector<std::string>& words)
    {
        for (const auto& word : words) {
            insert(word);
        }
    }

    void insert(std::string_view word)
    {
        std::reference_wrapper<Node> currentNode = root;
        for (const auto ch : word) {
            if (!currentNode.get().children.contains(ch)) {
                currentNode.get().children[ch] = std::make_unique<Node>();
            }
            currentNode = *currentNode.get().children[ch];
        }
        currentNode.get().isLeaf = true;
    }

    bool find(std::string_view word)
    {
        std::reference_wrapper<Node> currentNode = root;

        for (const auto ch : word) {
            if (const auto it = currentNode.get().children.find(ch); it != currentNode.get().children.end()) {
                currentNode = *it->second;
            } else {
                return false;
            }
        }
        return currentNode.get().isLeaf;
    }

    bool findPrefix(std::string_view word)
    {
        std::reference_wrapper<Node> currentNode = root;

        for (const auto ch : word) {
            if (const auto it = currentNode.get().children.find(ch); it != currentNode.get().children.end()) {
                currentNode = *it->second;
            } else {
                return false;
            }
        }
        return true;
    }

private:
    struct Node {
        bool isLeaf { false };
        std::map<char, std::unique_ptr<Node>> children;
    };

private:
    Node root;
};
}