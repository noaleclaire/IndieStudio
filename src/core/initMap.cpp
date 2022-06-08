/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-indiestudio-matthis.lesur
** File description:
** initMap
*/

#include "core/core.hpp"
#include "core/mainMenu.hpp"
#include "core/settingsMenu.hpp"
#include "raylib/include/Vector3.hpp"

#define GAME_BOARD_SIZE 17

// static ecs::IEntity *createCube(float x, float y, float width, float height)
// {
//     ecs::IEntity *entity = new ecs::IEntity();

//     entity->add<ComponentDrawable>(true, false);
//     entity->add<ComponentTransform>(height, width, x, y);
//     return (entity);
// }

void mapCreation(Map *map)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Camera3D camera = {};
    Vector3 initialCamPos = {0.0f, 10.0f, 10.0f};
    camera.position = initialCamPos;
    Vector3 initialCamTarget = {0.0f, 0.0f, 0.0f};
    camera.target = initialCamTarget;
    Vector3 initialCamUp = {0.0f, 1.0f, 0.0f};
    camera.up = initialCamUp;
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    int i = 0;

    raylib::Vector3 initialFloorPos = {0.0f, -0.05f, 0.0f};
    raylib::Vector3 initialPos = {-8.0f, 0.5f, -8.0f};
    std::vector<raylib::Vector3> cubes;
    for (int j = 0; j < GAME_BOARD_SIZE; j++) {
        for (i = 0; i < GAME_BOARD_SIZE; i++) {
            cubes.push_back(initialPos);
            initialPos.x += 1;
        }
        if (i == GAME_BOARD_SIZE) {
            initialPos.x = -8.0f;
            initialPos.z += 1.0f;
        }
    }
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        initialFloorPos.DrawCube(17.0f, 0.1f, 17.0f, RED);
        initialFloorPos.DrawCubeWires(17.0f, 0.1f, 17.0f, BLACK);
        for (i = 0; i < MAPSIZE; i++) {
            for (size_t j = 0; j < MAPSIZE; j++) {
                if (map->getMap()[i][j] == 1) {
                    cubes[i * MAPSIZE + j].DrawCube(1.0f, 1.0f, 1.0f, raylib::Color::Green());
                    cubes[i * MAPSIZE + j].DrawCubeWires(1.0f, 1.0f, 1.0f, raylib::Color::Black());
                } else if (map->getMap()[i][j] == 2) {
                    cubes[i * MAPSIZE + j].DrawCube(1.0f, 1.0f, 1.0f, raylib::Color::Blue());
                    cubes[i * MAPSIZE + j].DrawCubeWires(1.0f, 1.0f, 1.0f, raylib::Color::Black());
                }
            }
        }
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
}
