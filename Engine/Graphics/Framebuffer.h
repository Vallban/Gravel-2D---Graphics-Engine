#pragma once
#include <windows.h>
#include <cstdint>
#include "../Utils/BMP.h" 

class Framebuffer {
    public:
        int ancho = 0;
        int alto = 0;
        uint32_t* pixels = nullptr;
        HBITMAP bitmap = nullptr;

        ~Framebuffer(); // Liberar recursos

        bool crear(int ancho, int alto);
        void limpiar(uint32_t color);
        void dibujarImagen(const Utils::ImagenBMP& img, int x, int y);
};
