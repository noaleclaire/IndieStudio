/*
** EPITECH PROJECT, 2022
** ComponentCollider.hpp
** File description:
** ComponentCollider.hpp
*/

#pragma once

class ComponentCollider {
    public:
        ComponentCollider(bool takeCollider = false) : _takeCollider(takeCollider) {};
        ~ComponentCollider() = default;

        bool getTakeCollider() const;

        void setTakeCollider(bool takeCollider);

    protected:
    private:
        bool _takeCollider;
};