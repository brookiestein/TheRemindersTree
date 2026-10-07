#include <format>
#include <print>
#include <string>
#include <tuple>

#include "input.hpp"
#include "person.hpp"
#include "tree.hpp"
#include "utils.hpp"

int main()
{
    std::println("Árbol genealógico de Lucía\n");

    auto luciaData =
        Utils::Input::person("Primero, introduce los datos de Lucía");
    Person lucia(std::get<0>(luciaData), std::get<1>(luciaData),
                 std::get<2>(luciaData));

    Tree tree;
    tree.insert(lucia);

    const std::string luciaName {lucia.name()};

    while (true) {
        std::println("\n========== MENÚ ==========");
        std::println("1. Registrar familiar");
        std::println("2. Mostrar árbol genealógico");
        std::println("3. Buscar familiar por nombre");
        std::println(
            "4. Mostrar descendientes de Lucía por fecha de nacimiento");
        std::println("5. Mostrar cantidad de generaciones");
        std::println("6. Contar descendientes de Lucía");
        std::println("7. Mostrar hijos de una persona");
        std::println("8. Mostrar nietos de una persona");
        std::println("0. Salir");

        auto option = Input::number<int>(
            "Selecciona una opción",
            [](int option) {
                return (option >= 0 && option <= 8);
            },
            "Debes seleccionar una opción entre 0 y 8.");

        if (option == 0)
            break;

        switch (option) {
        case 1: {
            auto parentName = Input::text(
                "Introduce el nombre del padre o madre registrado en el árbol");

            if (!tree.contains(parentName)) {
                std::println(stderr,
                             "No se encontró a {}. Registra primero a esa "
                             "persona.",
                             parentName);
                break;
            }

            auto personData = Utils::Input::person(std::format(
                "Introduce los datos del familiar de {}", parentName));
            Person person(std::get<0>(personData), std::get<1>(personData),
                          std::get<2>(personData));

            if (tree.insert(parentName, person))
                std::println("{} fue agregado correctamente.", person.name());
            else
                std::println(stderr, "No fue posible agregar a {}.",
                             person.name());

            break;
        }
        case 2:
            tree.print();
            break;
        case 3: {
            auto name = Input::text("Introduce el nombre que deseas buscar");
            auto person = tree.find(name);

            if (!person) {
                std::println("No se encontró a {}.", name);
                break;
            }

            std::println("{}, {}, {}", person->name(), person->birthDate(),
                         Utils::Family::toString(person->kindship()));
            break;
        }
        case 4:
            tree.printDescendantsByBirthDate(luciaName);
            break;
        case 5:
            std::println("El árbol tiene {} generación(es).",
                         tree.generations());
            break;
        case 6:
            std::println("Lucía tiene {} descendiente(s) registrado(s).",
                         tree.descendantCount(luciaName));
            break;
        case 7: {
            auto name = Input::text(
                "Introduce el nombre de la persona cuyos hijos deseas ver");
            tree.printChildren(name);
            break;
        }
        case 8: {
            auto name = Input::text(
                "Introduce el nombre de la persona cuyos nietos deseas ver");
            tree.printGrandchildren(name);
            break;
        }
        }
    }
}
