/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-indiestudio-matthis.lesur
** File description:
** main
*/

#include "core/core.hpp"
#include "core/mainMenu.hpp"
#include "core/connectPlayers.hpp"

int mainLoop(ecs::Core index)
{
    int res = 0;

    while (res != -1) {
        switch (index.getScene()) {
            case ecs::Scenes::Menu: index.setScene(mainMenu()); break;
            case ecs::Scenes::Game: res = coreLoop(index); break;
            case ecs::Scenes::GameSettings:
                // res = reload();
                break;
            case ecs::Scenes::ConnectPlayers: index.setScene(connectPlayers());
            case ecs::Scenes::Win: break;
            case ecs::Close: return (-1);
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    ecs::Core index = initEntities();
    index.setScene(ecs::Scenes::ConnectPlayers);
    mainLoop(index);
    return 0;
}
