#pragma once
#include "Scenes/Scene.h"
#include "Images.h"
#include "ResourceManager.h"
#include <string>

namespace Core{
    // Encapsula la carga de recursos necesarios para el renderizado
    class Loader {
    public:
        static void cargar(Core::ResourceManager& estado, Scene& escena);
    };

}