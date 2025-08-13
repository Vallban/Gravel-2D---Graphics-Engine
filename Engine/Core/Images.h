#pragma once
#include <string>
#include <windows.h>

namespace Core {
    struct Imagen {
        std::wstring id;
        std::wstring ruta;
        POINT coordenadas;
    };
}