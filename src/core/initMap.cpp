/*
** EPITECH PROJECT, 2022
** B-YEP-400-NAN-4-1-indiestudio-matthis.lesur
** File description:
** initMap
*/

#include "initMap.hpp"
#include "ECS/ecs.hpp"
#include "raylib/include/Texture.hpp"

static ecs::IEntity *meshEntityCreation(raylib::Vector3 posMesh, raylib::Vector3 sizeMesh, raylib::Color color, raylib::Texture texture)
{
    ecs::IEntity *mesh = new ecs::IEntity();

    mesh->add<ComponentDrawable>(false, true);
    mesh->add<ComponentMesh>(posMesh, sizeMesh, color, texture);
    return (mesh);
}

void createPlayer(ecs::Core &mapCreation, std::string modelPath, raylib::Vector3 pos, int id, ComponentMovable::Direction dir)
{
    ecs::IEntity *playerEntity = new ecs::IEntity();

    playerEntity->add<ComponentDrawable>(false, true);
    playerEntity->add<ComponentModel>(modelPath, pos, raylib::Vector3(0.3f, 0.3f, 0.3f));
    playerEntity->get<ComponentModel>()->setRotateAngle(dir);
    playerEntity->add<ComponentControllable>();
    playerEntity->get<ComponentControllable>()->setGamepadId(id);
    playerEntity->add<ComponentCollider>();
    playerEntity->add<ComponentKills>();
    playerEntity->add<ComponentKillable>();
    playerEntity->add<ComponentMovable>(dir);
    mapCreation.addEntity(playerEntity);
}

void initGame(ecs::Core &mapCreation, std::vector<int> &idControllers)
{
    for (std::size_t i = 0; i < idControllers.size(); i++) {
        switch (i) {
            case 0:
                createPlayer(mapCreation, "assets/models3D/Among_Us_red.obj", raylib::Vector3(-7.0f, 0.0f, -(MAP_SIZE / 2) + 1), i, ComponentMovable::UP);
                break;
            case 1:
                createPlayer(mapCreation, "assets/models3D/Among_Us_blue.obj", raylib::Vector3((MAP_SIZE / 2) - 1, 0.0f, -(MAP_SIZE / 2) + 1), i,
                    ComponentMovable::DOWN);
                break;
            case 2:
                createPlayer(mapCreation, "assets/models3D/Among_Us_black.obj", raylib::Vector3(-7.0f, 0.0f, (MAP_SIZE / 2) - 1), i, ComponentMovable::UP);
                break;
            case 3:
                createPlayer(mapCreation, "assets/models3D/Among_Us_white.obj", raylib::Vector3((MAP_SIZE / 2) - 1, 0.0f, (MAP_SIZE / 2) - 1), i,
                    ComponentMovable::DOWN);
                break;
            default: break;
        }
    }
}

ecs::Core mapCreation(std::vector<int> &idControllers)
{
    raylib::Texture floorTex;
    raylib::Texture wallTex;
    raylib::Texture boxTex;
    raylib::Texture backgroundTex;
    raylib::Texture wallupTex;
    raylib::Texture blockTex;
    floorTex.Load("assets/mapTextures/game_floor.png");
    backgroundTex.Load("assets/mapTextures/background_space.png");
    wallTex.Load("assets/mapTextures/wall.png");
    boxTex.Load("assets/mapTextures/box.png");
    wallupTex.Load("assets/mapTextures/wall_up.png");
    blockTex.Load("assets/mapTextures/block_texture.png");
    Map *map = new Map;
    map->generateMap();
    ecs::Core mapCreation;
    initGame(mapCreation, idControllers);

    raylib::Vector3 pos = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 size = {1.0f, 1.0f, 1.0f};

    ecs::IEntity *FloorGame;
    raylib::Vector3 posFloorGame = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 sizeFloorGame = {MAP_SIZE, 0.1f, MAP_SIZE};
    FloorGame = meshEntityCreation(posFloorGame, sizeFloorGame, raylib::Color::White(), floorTex);

    ecs::IEntity *Floor;
    raylib::Vector3 posFloor = {0.0f, -0.01f, 0.0f};
    raylib::Vector3 sizeFloor = {MAP_SIZE * 3, 0.1f, MAP_SIZE * 3};
    Floor = meshEntityCreation(posFloor, sizeFloor, raylib::Color::White(), backgroundTex);

    ecs::IEntity *Floor2;
    raylib::Vector3 posFloor2 = {0.0f, (MAP_SIZE * 3) / 2, (MAP_SIZE * 3) / 2};
    raylib::Vector3 sizeFloor2 = {MAP_SIZE * 3, MAP_SIZE * 3, 0.1f};
    Floor2 = meshEntityCreation(posFloor2, sizeFloor2, raylib::Color::White(), backgroundTex);

    ecs::IEntity *Floor3;
    raylib::Vector3 posFloor3 = {(-MAP_SIZE * 3) / 2, (MAP_SIZE * 3) / 2, 0.0f};
    raylib::Vector3 sizeFloor3 = {0.5f, MAP_SIZE * 3, MAP_SIZE * 3};
    Floor3 = meshEntityCreation(posFloor3, sizeFloor3, raylib::Color::White(), backgroundTex);

    ecs::IEntity *Floor4;
    raylib::Vector3 posFloor4 = {(MAP_SIZE * 3) / 2, (MAP_SIZE * 3) / 2, 0.0f};
    raylib::Vector3 sizeFloor4 = {0.5f, MAP_SIZE * 3, MAP_SIZE * 3};
    Floor4 = meshEntityCreation(posFloor4, sizeFloor4, raylib::Color::White(), backgroundTex);

    ecs::IEntity *Floor5;
    raylib::Vector3 posFloor5 = {0.0f, (MAP_SIZE * 3) / 2, -((MAP_SIZE * 3) / 2)};
    raylib::Vector3 sizeFloor5 = {MAP_SIZE * 3, MAP_SIZE * 3, 0.1f};
    Floor5 = meshEntityCreation(posFloor5, sizeFloor5, raylib::Color::White(), backgroundTex);

    ecs::IEntity *mesh1;
    raylib::Vector3 posMesh = {0.0f, 0.5f, (-1.0f * (MAP_SIZE - MAP_SIZE % 2)) / 2};
    raylib::Vector3 sizeMesh = {MAP_SIZE, 1.0f, 1.0f};
    mesh1 = meshEntityCreation(posMesh, sizeMesh, raylib::Color::White(), wallTex);

    ecs::IEntity *mesh2;
    raylib::Vector3 posMesh2 = {-8.0f, 0.5f, 0.5f};
    raylib::Vector3 sizeMesh2 = {1.0f, 1.0f, MAP_SIZE - 1};
    mesh2 = meshEntityCreation(posMesh2, sizeMesh2, raylib::Color::White(), wallupTex);

    ecs::IEntity *bis;
    raylib::Vector3 posbis = {-8.00f, 0.5f, 0.5f};
    raylib::Vector3 sizebis = {1.01f, 1.0f, MAP_SIZE - 1};
    bis = meshEntityCreation(posbis, sizebis, raylib::Color::White(), wallTex);

    ecs::IEntity *mesh3;
    raylib::Vector3 posMesh3 = {8.0f, 0.5f, 0.5f};
    raylib::Vector3 sizeMesh3 = {1.0f, 1.0f, MAP_SIZE - 1};
    mesh3 = meshEntityCreation(posMesh3, sizeMesh3, raylib::Color::White(), wallupTex);

    ecs::IEntity *bis2;
    raylib::Vector3 posbis2 = {8.00f, 0.5f, 0.5f};
    raylib::Vector3 sizebis2 = {1.01f, 1.0f, MAP_SIZE - 1};
    bis2 = meshEntityCreation(posbis2, sizebis2, raylib::Color::White(), wallTex);

    ecs::IEntity *mesh4;
    raylib::Vector3 posMesh4 = {0.0f, 0.5f, 8.0f};
    raylib::Vector3 sizeMesh4 = {MAP_SIZE - 2, 1.0f, 1.0f};
    mesh4 = meshEntityCreation(posMesh4, sizeMesh4, raylib::Color::White(), wallTex);

    mapCreation.add<ecs::SystemRender3D>();
    mapCreation.add<ecs::SystemRender2D>();
    mapCreation.addEntity(mesh1);
    mapCreation.addEntity(bis);
    mapCreation.addEntity(bis2);
    mapCreation.addEntity(mesh2);
    mapCreation.addEntity(mesh3);
    mapCreation.addEntity(mesh4);
    mapCreation.addEntity(FloorGame);
    mapCreation.addEntity(Floor);
    mapCreation.addEntity(Floor2);
    mapCreation.addEntity(Floor3);
    mapCreation.addEntity(Floor4);
    mapCreation.addEntity(Floor5);

    raylib::Vector3 sizeCube = {1.0f, 1.0f, 1.0f};
    Vector3 initial = {-8.0f, 0.5f, -1.0f * (MAP_SIZE / 2) + 1};
    for (int j = 1; j < MAP_SIZE - 1; j++) {
        for (int i = 1; i < MAP_SIZE - 1; i++) {
            initial.x += 1;
            if (map->getMap()[i][j] == 2) {
                ecs::IEntity *cube = new ecs::IEntity();
                cube->add<ComponentDrawable>(false, true);
                cube->add<ComponentCube>(initial, sizeCube, raylib::Color::White(), boxTex);
                mapCreation.addEntity(cube);
            } else if (map->getMap()[i][j] == 1) {
                ecs::IEntity *cube = new ecs::IEntity();
                cube->add<ComponentDrawable>(false, true);
                cube->add<ComponentCube>(initial, sizeCube, raylib::Color::White(), blockTex);
                mapCreation.addEntity(cube);
            }
        }
        initial.x = (-1.0f * (MAP_SIZE - MAP_SIZE % 2)) / 2;
        initial.z += 1.0f;
    }
    return (mapCreation);
}
