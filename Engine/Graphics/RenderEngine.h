#pragma once
#include <cstdint>
#include <string>
#include "Framebuffer.h"
#include "../Core/ResourceManager.h"

namespace Graphics{
    class RenderEngine{
    public:
        RenderEngine(Framebuffer& fb, Core::ResourceManager& rm);

        void iniciarFrame(uint32_t colorFondo);
        void dibujarImagen(const std::wstring& nombre, int x, int y);
        void finalizarFrame();

    private:
        Framebuffer& framebuffer;
        Core::ResourceManager& recursos;
    };
}
