/*
** EPITECH PROJECT, 2022
** Texture.hpp
** File description:
** texture
*/

#pragma once

#include <string>
#include "raylib.hpp"

namespace raylib
{
    class Texture : public ::Texture {
      public:
        Texture();
        Texture(const ::Image &image, int layout);
        Texture(const ::Image &image);
        Texture(const Texture &other);
        Texture(const ::Texture &texture);

        void SetShaderValue(::Shader &shader, int locIndex);
        void SetShapes(::Rectangle &source);
        void Draw(::Vector2 position, float rotation, float scale = 1.0f, ::Color tint = {255, 255, 255, 255});
        void Draw(::Vector2 position, ::Color tint = {255, 255, 255, 255});
        void Draw(::Rectangle source, ::Vector2 position, ::Color tint = {255, 255, 255, 255});
        void SetWrap(int wrapMode);
        void SetFilter(int filterMode);
        void Update(::Rectangle rec, const void *pixels);
        void Update(const void *pixels);
        void Unload();
        bool IsReady() const;
        bool Load(const std::string &fileName);
        bool Load(const ::Image &image, int layout);
        bool Load(const ::Image &image);
        std::string getTexturePath() const;

      private:
        void _setTexture(const ::Texture &texture);
        std::string _texturePath;
    };
} // namespace raylib
