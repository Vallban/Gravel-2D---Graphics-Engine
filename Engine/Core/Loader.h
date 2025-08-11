#pragma once
#include "../Core/Images.h"
#include "../Core/ResourceManager.h"
#include <string>

namespace Core{
    // Encapsula la carga de recursos necesarios para el renderizado
    class Loader {
    public:
        static void cargar(Core::ResourceManager& estado, std::vector<Imagen>& imagenesDeLaEscena);
    };

}