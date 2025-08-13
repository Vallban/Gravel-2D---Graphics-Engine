#include "Loader.h"
#include "../Core/Scenes/Scene.h"
#include "Images.h"
#include "../Utils/json.hpp"
#include <fstream>
#include <stdexcept>
#include <windows.h>

namespace Core{

void Loader::cargar(Core::ResourceManager& recursos, Scene& escena) {
    
    try {
        std::ifstream archivo("Assets/escena.json");
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir escena.json");
        }

        nlohmann::json datos;
        archivo >> datos;

        for (const auto& imagenJson : datos["escena"]["imagenes"]) {
            Imagen imagenDeLaEscena;
            std::string id = imagenJson["id"].get<std::string>();
            imagenDeLaEscena.id = std::wstring(id.begin(), id.end());

            std::string ruta = imagenJson["ruta"].get<std::string>();
            std::wstring ruta_w(ruta.begin(), ruta.end());
            // Concatenar carpeta base Assets + ruta relativa del JSON
            std::wstring rutaBase = L"Assets\\";
            imagenDeLaEscena.ruta = rutaBase + ruta_w;

            imagenDeLaEscena.coordenadas.x = imagenJson["x"];
            imagenDeLaEscena.coordenadas.y = imagenJson["y"];

            recursos.cargarTextura(imagenDeLaEscena.id, imagenDeLaEscena.ruta);

            escena.anyadirImagen(imagenDeLaEscena);
        }

    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error cargando recursos: ") + e.what());
    }
}

} // namespace Core