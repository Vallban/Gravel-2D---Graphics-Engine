#pragma once
#include <string>

namespace Core {
    struct BiVector{
        int x, y;
    };
    struct Entidad {
        std::wstring nombre;
        std::wstring ruta;
        BiVector coordenadas;
    };
}
