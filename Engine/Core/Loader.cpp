#include "Loader.h"
#include "Images.h"
#include <fstream>
#include "../Utils/json.hpp"
#include <stdexcept> // Para std::runtime_error
#include <windows.h>

namespace Core{

void Loader::cargar(Core::ResourceManager& recursos, std::vector<Imagen>& imagenesConPosiciones) {
    
    try {
        recursos.cargarTextura(L"TextoPrueba1", L"assets/TextoPrueba1.bmp");
        recursos.cargarTextura(L"TextoPrueba2", L"assets/TextoPrueba2.bmp");
        std::ifstream archivo("assets/escena.json");
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir escena.json");
        }

        nlohmann::json datos;
        archivo >> datos;

        for (const auto& imagenJson : datos["imagenes"]) {
            Imagen imagenConPosiciones;
            std::string nombre_str = imagenJson["id"].get<std::string>();
            imagenConPosiciones.id = std::wstring(nombre_str.begin(), nombre_str.end());
            std::string ruta_str = imagenJson["ruta"].get<std::string>();
            imagenConPosiciones.ruta = std::wstring(ruta_str.begin(), ruta_str.end());
            imagenConPosiciones.coordenadas.x = imagenJson["x"];
            imagenConPosiciones.coordenadas.y = imagenJson["y"];
            imagenesConPosiciones.push_back(imagenConPosiciones);
        }

    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error cargando recursos: ") + e.what());
    }
}

} // namespace Graphics