#include "Framebuffer.h"
#include <stdexcept>

Framebuffer::~Framebuffer() {
    if (bitmap) {
        DeleteObject(bitmap);
        bitmap = nullptr;
        pixels = nullptr;
    }
}

bool Framebuffer::crear(int ancho_, int alto_) {
    ancho = ancho_;
    alto = alto_;

    BITMAPINFO bmpInfo = {};
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = ancho;
    bmpInfo.bmiHeader.biHeight = -alto; // orientado arriba
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32;
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    bitmap = CreateDIBSection(nullptr, &bmpInfo, DIB_RGB_COLORS, (void**)&pixels, nullptr, 0);
    if (!bitmap || !pixels) {
        bitmap = nullptr;
        pixels = nullptr;
        return false;
    }

    return true;
}

void Framebuffer::limpiar(uint32_t color) {
    if (!pixels) return;
    for (int i = 0; i < ancho * alto; ++i) {
        pixels[i] = color;
    }
}

void Framebuffer::dibujarImagen(const Utils::ImagenBMP& img, int xPos, int yPos) {
    if (!pixels) return;

    for (int y = 0; y < img.alto; ++y) {
        int fy = yPos + y;
        if (fy < 0 || fy >= alto) continue;  // Evitar fuera de alto

        for (int x = 0; x < img.ancho; ++x) {
            int fx = xPos + x;
            if (fx < 0 || fx >= ancho) continue;  // Evitar fuera de ancho

            uint32_t color = img.pixeles[y * img.ancho + x];
            if ((color >> 24) > 0) { // Si el canal alfa no es 0 (completamente transparente)
                pixels[fy * ancho + fx] = color;
            }
        }
    }
}