#pragma once
#include "../Core/ResourceManager.h"

namespace Core{

// Encapsula la carga de recursos necesarios para el renderizado
class Loader {
public:
    static void cargar(Core::ResourceManager& estado);
};

}