/*
** EPITECH PROJECT, 2022
** Project
** File description:
** core
*/

#include "core.hpp"
#include "core/pauseMenu.hpp"
#include "information/info.hpp"
#include "initMap.hpp"

double clockToMilliseconds(clock_t ticks)
{
    return (ticks / ((double)CLOCKS_PER_SEC)) * ML_BASE;
}

ecs::Scenes coreLoop(std::vector<int> &idControllers, std::vector<int> &settings)
{
    clock_t sec_clock = clock();
    clock_t fps_clock = clock();
    ecs::Core core = mapCreation(idControllers, settings);
    int fps = 0;
    int avg_fps = FPS_CAP;
    raylib::Camera3D camera;
    raylib::Vector3 initialCamPos = {0.0f, 10.0f, 10.0f};
    camera.position = initialCamPos;
    raylib::Vector3 initialCamTarget = {0.0f, 0.0f, 0.0f};
    camera.target = initialCamTarget;
    raylib::Vector3 initialCamUp = {0.0f, 1.0f, 0.0f};
    camera.up = initialCamUp;
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    bool isOrbital = true;
    bool step = false;
    bool first = true;
    bool second = true;
    float step2 = (MAP_SIZE / 2) - 8;

    initInformations(core);
    camera.SetMode(CAMERA_ORBITAL);
    core.getEntity("MusicGame")->get<ComponentMusic>()->getMusic().Play();
    while (1) {
        if (clockToMilliseconds(clock() - fps_clock) >= FPS_CAP_REAL) {
            fps_clock = clock();
            fps++;

            camera.Update();

            if ((fps) == 1 && isOrbital == true) {
                camera.SetMode(CAMERA_CUSTOM);
                isOrbital = false;
            }
            if (first == true && step == false && camera.position.x >= -11) {
                camera.position.x -= 0.1f / 2;
            } else if (first == true && step == false && camera.position.x < -11) {
                first = false;
            }
            if (second == true && step == false && first == false && camera.position.z <= step2) {
                camera.position.z += 0.1f / 2;
                camera.position.x = -11;
            } else if (second == true && step == false && first == false && camera.position.z > step2) {
                second = false;
            }
            if (isOrbital == false && camera.position.y < 12.5f && first == false && second == false) {
                camera.position.y += 0.09f / 2;
                camera.position.x += 0.13f / 2;
                step = true;
            }
            if (core.getScene() == ecs::Scenes::Pause)
                core.setScene(pauseMenu());
            if (core.getScene() != ecs::Scenes::Game && core.getScene() != ecs::Scenes::Pause)
                break;
            core.getEntity("MusicGame")->get<ComponentMusic>()->getMusic().Update();
            raylib::Window::BeginDrawing();
            raylib::Window::Clear(raylib::Color::White());
            updateInformations(core);
            camera.BeginMode();
            if (step == true && camera.position.y >= 12.5f)
                core.get<ecs::SystemEvent>()->update(core);
            core.get<ecs::SystemRender3D>()->update(core);
            camera.EndMode();
            core.get<ecs::SystemRender2D>()->update(core);
            raylib::Window::EndDrawing();
        }

        if (clockToMilliseconds(clock() - sec_clock) >= ML_BASE) {
            sec_clock = clock();
            avg_fps = (avg_fps + fps) / 2;
            // do game logic and stuff like that here, eg: this action happens every X seconds, not X fps...;
            // printf("second tick, delta fps: %d, avg fps: %d fps is capped around: %d\n", fps, avg_fps, FPS_CAP);
            fps = 0;
        }
    }
    core.getEntity("MusicGame")->get<ComponentMusic>()->getMusic().Stop();
    return (core.getScene());
}
