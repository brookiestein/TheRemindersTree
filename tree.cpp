#include "tree.hpp"
#include "utils.hpp"

#include <algorithm>
#include <print>
#include <ranges>
#include <string>

bool Tree::insert(const Person &person)
{
    if (m_root)
        return false;

    m_root = std::make_unique<Node>(person);
    return true;
}

bool Tree::insert(std::string_view parentName, const Person &person)
{
    auto parent = find(m_root.get(), parentName);
    if (!parent)
        return false;

    parent->children.push_back(std::make_unique<Node>(person));
    return true;
}

Tree::Node *Tree::find(Node *node, std::string_view name) noexcept
{
    if (!node)
        return nullptr;

    if (node->person.name() == name)
        return node;

    for (auto &child : node->children) {
        if (auto result = find(child.get(), name))
            return result;
    }

    return nullptr;
}

const Tree::Node *Tree::find(const Node *node, std::string_view name) noexcept
{
    if (!node)
        return nullptr;

    if (node->person.name() == name)
        return node;

    for (const auto &child : node->children) {
        if (auto result = find(child.get(), name))
            return result;
    }

    return nullptr;
}

const Person *Tree::find(std::string_view name) const noexcept
{
    auto node = find(m_root.get(), name);
    if (!node)
        return nullptr;

    return &node->person;
}

bool Tree::contains(std::string_view name) const noexcept
{
    return find(name) != nullptr;
}

void Tree::print(const Node *node, std::size_t depth) noexcept
{
    if (!node)
        return;

    std::println("{}{}, {}, {}", std::string(depth * 4, ' '),
                 node->person.name(), node->person.birthDate(),
                 Utils::Family::toString(node->person.kindship()));

    for (const auto &child : node->children)
        print(child.get(), depth + 1);
}

void Tree::print() const noexcept
{
    print(m_root.get(), 0);
}

std::size_t Tree::generations(const Node *node) noexcept
{
    if (!node)
        return 0;

    std::size_t maxGenerations {};

    for (const auto &child : node->children)
        maxGenerations = std::max(maxGenerations, generations(child.get()));

    return maxGenerations + 1;
}

std::size_t Tree::generations() const noexcept
{
    return generations(m_root.get());
}

std::size_t Tree::descendantCount(const Node *node) noexcept
{
    if (!node)
        return 0;

    std::size_t count {};

    for (const auto &child : node->children)
        count += 1 + descendantCount(child.get());

    return count;
}

std::size_t Tree::descendantCount(std::string_view name) const noexcept
{
    auto node = find(m_root.get(), name);
    if (!node)
        return 0;

    return descendantCount(node);
}

void Tree::printGeneration(const Node *node, std::size_t generation,
                           std::size_t currentGeneration) noexcept
{
    if (!node)
        return;

    if (generation == currentGeneration) {
        std::println("{}, {}, {}", node->person.name(), node->person.birthDate(),
                     Utils::Family::toString(node->person.kindship()));
        return;
    }

    for (const auto &child : node->children)
        printGeneration(child.get(), generation, currentGeneration + 1);
}

void Tree::printChildren(std::string_view name) const noexcept
{
    auto node = find(m_root.get(), name);
    if (!node) {
        std::println(stderr, "No se encontró a {} en el árbol.", name);
        return;
    }

    if (node->children.empty()) {
        std::println("{} no tiene hijos registrados.", name);
        return;
    }

    printGeneration(node, 1, 0);
}

void Tree::printGrandchildren(std::string_view name) const noexcept
{
    auto node = find(m_root.get(), name);
    if (!node) {
        std::println(stderr, "No se encontró a {} en el árbol.", name);
        return;
    }

    bool hasGrandchildren {};
    for (const auto &child : node->children) {
        if (!child->children.empty()) {
            hasGrandchildren = true;
            break;
        }
    }

    if (!hasGrandchildren) {
        std::println("{} no tiene nietos registrados.", name);
        return;
    }

    printGeneration(node, 2, 0);
}

void Tree::collectDescendants(const Node *node,
                              std::vector<const Person *> &people)
{
    if (!node)
        return;

    for (const auto &child : node->children) {
        people.push_back(&child->person);
        collectDescendants(child.get(), people);
    }
}

void Tree::printDescendantsByBirthDate(std::string_view name) const
{
    auto node = find(m_root.get(), name);
    if (!node) {
        std::println(stderr, "No se encontró a {} en el árbol.", name);
        return;
    }

    std::vector<const Person *> descendants;
    collectDescendants(node, descendants);

    if (descendants.empty()) {
        std::println("{} no tiene descendientes registrados.", name);
        return;
    }

    std::ranges::sort(descendants, {}, [](const Person *person) {
        return person->birthDate();
    });

    for (const auto person : descendants) {
        std::println("{}, {}, {}", person->name(), person->birthDate(),
                     Utils::Family::toString(person->kindship()));
    }
}
