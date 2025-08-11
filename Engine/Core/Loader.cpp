#include "Loader.h"
#include "Images.h"
#include <fstream>
#include "../Utils/json.hpp"
#include <stdexcept> // Para std::runtime_error
#include <windows.h>

namespace Core{

void Loader::cargar(Core::ResourceManager& recursos, std::vector<Imagen>& imagenesDeLaEscena) {
    
    try {
        std::ifstream archivo("Assets/escena.json");
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir escena.json");
        }

        nlohmann::json datos;
        archivo >> datos;

        for (const auto& imagenJson : datos["escena"]["imagenes"]) {
            Imagen imagenDeLaEscena;
            std::string nombre_str = imagenJson["id"].get<std::string>();
            imagenDeLaEscena.id = std::wstring(nombre_str.begin(), nombre_str.end());

            std::string ruta_str = imagenJson["ruta"].get<std::string>();
            std::wstring ruta_w(ruta_str.begin(), ruta_str.end());
            // Concatenar carpeta base Assets + ruta relativa del JSON
            std::wstring basePath = L"Assets\\";
            imagenDeLaEscena.ruta = basePath + ruta_w;

            imagenDeLaEscena.coordenadas.x = imagenJson["x"];
            imagenDeLaEscena.coordenadas.y = imagenJson["y"];

            recursos.cargarTextura(imagenDeLaEscena.id, imagenDeLaEscena.ruta);

            imagenesDeLaEscena.push_back(imagenDeLaEscena);
        }

    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error cargando recursos: ") + e.what());
    }
}

} // namespace Graphics