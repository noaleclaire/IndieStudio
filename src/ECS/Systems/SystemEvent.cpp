/*
** EPITECH PROJECT, 2022
** SystemEvent
** File description:
** SystemEvent
*/

#include "SystemEvent.hpp"
#include "../../raylib/include/Gamepad.hpp"

namespace ecs {
    bool SystemEvent::_isControllerAssign(ecs::Core &index, int gamepadNumber)
    {
        for (auto *it : index.getEntities()) {
            if (it->has<ComponentControllable>() &&
                it->get<ComponentControllable>()->getGamepadId() == gamepadNumber)
                return (true);
        }
        return (false);
    }

    void SystemEvent::_assignController(ecs::Core &index, int gamepadNumber)
    {
        for (auto *it : index.getEntities()) {
            if (it->has<ComponentControllable>() &&
                it->get<ComponentControllable>()->getGamepadId() == -1) {
                it->get<ComponentControllable>()->setGamepadId(gamepadNumber);
                return;
            }
        }
        return;
    }

    void SystemEvent::_reassignControllers(ecs::Core &index, int gamepadNumber)
    {
    }

    void SystemEvent::_detectNbControllers()
    {
        // if (raylib::Gamepad::IsAvailable(0)) { // && !IsControllerAssign(0)
        //     // assign to player
        //     raylib::Gamepad::gamepadNumber++;
        if (!raylib::Gamepad::IsAvailable(0)) { // && IsControllerAssign(0)
            // reassign all controllers to players
            raylib::Gamepad::gamepadNumber--;
        }
        // if (raylib::Gamepad::IsAvailable(1)) { // && !IsControllerAssign(1)
        //     // assign to player
        //     raylib::Gamepad::gamepadNumber++;
        if (!raylib::Gamepad::IsAvailable(1)) { // && IsControllerAssign(1)
            // reassign all controllers to players
            raylib::Gamepad::gamepadNumber--;
        }
        // if (raylib::Gamepad::IsAvailable(2)) { // && !IsControllerAssign(2)
        //     // assign to player
        //     raylib::Gamepad::gamepadNumber++;
        if (!raylib::Gamepad::IsAvailable(2)) { // && IsControllerAssign(2)
            // reassign all controllers to players
            raylib::Gamepad::gamepadNumber--;
        }
        // if (raylib::Gamepad::IsAvailable(3)) { // && !IsControllerAssign(3)
        //     // assign to player
        //     raylib::Gamepad::gamepadNumber++;
        if (!raylib::Gamepad::IsAvailable(3)) { // && IsControllerAssign(3)
            // reassign all controllers to players
            raylib::Gamepad::gamepadNumber--;
        }
    }

    void SystemEvent::_resetStateButtons(ecs::Core &index, int idButton)
    {
        for (auto *it : index.getEntities()) {
            if (it->has<ComponentButton>() && it->get<ComponentButton>()->getIdButton() != idButton)
                it->get<ComponentButton>()->setState(false);
        }
    }

    void SystemEvent::_handleButtonsMoveUpDown(ecs::Core &index, int upOrDown)
    {
        static int tmpIdButton = 0;
        int idMax = 0;
        bool isId = false;

        for (auto *it : index.getEntities()) {
            if (it->has<ComponentButton>()) {
                if (it->get<ComponentButton>()->getIdButton() > idMax)
                    idMax = it->get<ComponentButton>()->getIdButton();
                if (it->get<ComponentButton>()->getIdButton() == tmpIdButton + upOrDown) {
                    isId = true;
                    break;
                }
            }
        }
        if (upOrDown > 0 && !isId)
            tmpIdButton = -1;
        else if (upOrDown < 0 && !isId)
            tmpIdButton = idMax + 1;
        for (auto *it : index.getEntities()) {
            if (it->has<ComponentButton>() &&
            it->get<ComponentButton>()->getIdButton() == tmpIdButton + upOrDown) {
                it->get<ComponentButton>()->setState(true);
                tmpIdButton = it->get<ComponentButton>()->getIdButton();
                _resetStateButtons(index, it->get<ComponentButton>()->getIdButton());
                break;
            }
        }
    }

    void SystemEvent::_handleClickOnButtons(ecs::Core &index)
    {
        for (auto *it : index.getEntities()) {
            if (it->has<ComponentButton>() && it->get<ComponentButton>()->getState()) {
                //it->get<ComponentButton>()->setTexture("//texturePath");
                break;
            }
        }
    }

    void SystemEvent::handleControllersMenu(ecs::Core &index)
    {
        if (raylib::Gamepad::IsAvailable(0)) {
            if (raylib::Gamepad::IsButtonReleased(0, raylib::Gamepad::GamepadButtonRightFaceDown())) {
                _handleClickOnButtons(index);
            }
            if (raylib::Gamepad::GetAxisMovement(0, raylib::Gamepad::GamepadAxisLeftY()) == 1 ||
            raylib::Gamepad::IsButtonReleased(0, raylib::Gamepad::GamepadButtonLeftFaceDown())) {
                _handleButtonsMoveUpDown(index, 1);
            }
            if (raylib::Gamepad::GetAxisMovement(0, raylib::Gamepad::GamepadAxisLeftY()) == -1 ||
            raylib::Gamepad::IsButtonReleased(0, raylib::Gamepad::GamepadButtonLeftFaceUp())) {
                _handleButtonsMoveUpDown(index, -1);
            }
        }
    }

    void SystemEvent::handleControllersConnectPlayers(ecs::Core &index)
    {
        for (int i = 0; i <= raylib::Gamepad::gamepadNumber; i++) {
            if (raylib::Gamepad::IsAvailable(i)) {
                if (raylib::Gamepad::IsButtonReleased(i, raylib::Gamepad::GamepadButtonRightFaceDown())) {
                    //create a player
                    _assignController(index, i);
                }
            }
        }
    }

    void SystemEvent::handleControllersGame(ecs::Core &index)
    {
        for (int i = 0; i <= raylib::Gamepad::gamepadNumber; i++) {
            if (raylib::Gamepad::IsAvailable(i) && _isControllerAssign(index, i)) {
                // Draw buttons: xbox home
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonMiddle())) std::cout << "home" << std::endl;

                // Draw buttons: basic
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonMiddleRight())) std::cout << "start" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonMiddleLeft())) std::cout << "select" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonRightFaceRight())) std::cout << "O" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonRightFaceDown())) std::cout << "X" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonRightFaceLeft())) std::cout << "[]" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonRightFaceUp())) std::cout << "/\\" << std::endl;

                // Draw buttons: d-pad
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonLeftFaceUp())) std::cout << "up" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonLeftFaceDown())) std::cout << "down" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonLeftFaceLeft())) std::cout << "left" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonLeftFaceRight())) std::cout << "right" << std::endl;

                // Draw buttons: left-right back
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonLeftTrigger1())) std::cout << "a" << std::endl;
                if (raylib::Gamepad::IsButtonDown(i, raylib::Gamepad::GamepadButtonRightTrigger1())) std::cout << "b" << std::endl;

                // Draw axis: left joystick
                // std::cout << "GAMEPAD_AXIS_LEFT_X: " << raylib::Gamepad::GetAxisMovement(i, raylib::Gamepad::GamepadAxisLeftX()) << std::endl;
                // std::cout << "GAMEPAD_AXIS_LEFT_Y: " << raylib::Gamepad::GetAxisMovement(i, raylib::Gamepad::GamepadAxisLeftY()) << std::endl;

                // Draw axis: right joystick
                // std::cout << "GAMEPAD_AXIS_RIGHT_X: " << raylib::Gamepad::GetAxisMovement(i, raylib::Gamepad::GamepadAxisRightX()) << std::endl;
                // std::cout << "GAMEPAD_AXIS_RIGHT_Y: " << raylib::Gamepad::GetAxisMovement(i, raylib::Gamepad::GamepadAxisRightY()) << std::endl;

                // Draw axis: left-right triggers
                // std::cout << "GAMEPAD_AXIS_LEFT_TRIGGER: " << raylib::Gamepad::GetAxisMovement(i, raylib::Gamepad::GamepadAxisLeftTrigger()) << std::endl;
                // std::cout << "GAMEPAD_AXIS_RIGHT_TRIGGER: " << raylib::Gamepad::GetAxisMovement(i, raylib::Gamepad::GamepadAxisRightTrigger()) << std::endl;
            }
        }
    }

    void SystemEvent::handleControllersGameSettings(ecs::Core &index)
    {
        if (raylib::Gamepad::IsAvailable(0)) {
            return;
        }
    }

    void SystemEvent::handleControllersWin(ecs::Core &index)
    {
        if (raylib::Gamepad::IsAvailable(0)) {
            return;
        }
    }


    void SystemEvent::update(ecs::Core &index)
    {
        raylib::Gamepad::gamepadNumber = 3;
        _detectNbControllers();
        if (index.getScene() == ecs::Scenes::Menu)
            handleControllersMenu(index);
        if (index.getScene() == ecs::Scenes::ConnectPlayers)
            handleControllersConnectPlayers(index);
        if (index.getScene() == ecs::Scenes::Game)
            handleControllersGame(index);
        if (index.getScene() == ecs::Scenes::GameSettings)
            handleControllersGameSettings(index);
        if (index.getScene() == ecs::Scenes::Win)
            handleControllersWin(index);
    }
}