#include "Loader.h"
#include "Entity.h"
#include <fstream>
#include "../Utils/json.hpp"
#include <stdexcept> // Para std::runtime_error

namespace Core{

void Loader::cargar(Core::ResourceManager& recursos) {
    std::vector<Entidad> entidades;
    
    try {
        recursos.cargarTextura(L"TextoPrueba1", L"assets/TextoPrueba1.bmp");
        recursos.cargarTextura(L"TextoPrueba2", L"assets/TextoPrueba2.bmp");
        std::ifstream archivo("assets/escena.json");
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir escena.json");
        }

        nlohmann::json datos;
        archivo >> datos;

        for (const auto& entidadJson : datos["entidades"]) {
            Entidad entidad;
            std::string nombre_str = entidadJson["nombre"].get<std::string>();
            entidad.ruta = std::wstring(nombre_str.begin(), nombre_str.end());
            entidad.coordenadas.x = entidadJson["x"];
            entidad.coordenadas.y = entidadJson["y"];
            entidades.push_back(entidad);
        }
        
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error cargando recursos: ") + e.what());
    }
}

} // namespace Graphics