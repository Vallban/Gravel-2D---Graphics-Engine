#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Utils {
    struct ImagenBMP {
        int ancho;
        int alto;
        std::vector<uint32_t> pixeles;
    };

    ImagenBMP cargarBMP(const std::wstring& ruta);
}