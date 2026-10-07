#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <memory>
#include <string_view>
#include <vector>

#include "person.hpp"

class Tree
{
    struct Node {
        Person person;
        std::vector<std::unique_ptr<Node>> children;

        explicit Node(const Person &person)
            : person(person)
        {
        }
    };

    std::unique_ptr<Node> m_root;

    static Node *find(Node *node, std::string_view name) noexcept;
    static const Node *find(const Node *node, std::string_view name) noexcept;
    static void print(const Node *node, std::size_t depth) noexcept;
    static std::size_t generations(const Node *node) noexcept;
    static std::size_t descendantCount(const Node *node) noexcept;
    static void printGeneration(const Node *node, std::size_t generation,
                                std::size_t currentGeneration) noexcept;
    static void collectDescendants(const Node *node,
                                   std::vector<const Person *> &people);

public:
    bool insert(const Person &person);
    bool insert(std::string_view parentName, const Person &person);

    [[nodiscard]] const Person *find(std::string_view name) const noexcept;
    [[nodiscard]] bool contains(std::string_view name) const noexcept;
    [[nodiscard]] std::size_t generations() const noexcept;
    [[nodiscard]] std::size_t descendantCount(std::string_view name) const
        noexcept;

    void print() const noexcept;
    void printChildren(std::string_view name) const noexcept;
    void printGrandchildren(std::string_view name) const noexcept;
    void printDescendantsByBirthDate(std::string_view name) const;
};

#endif // TREE_HPP
