#pragma once
#include <string>
#include "../Utils/json.hpp"

// Clase para generar dinámicamente un archivo de escena.json
class DynamicSceneJSON {
public:
    // Crea un archivo JSON de escena con el nombre y ruta indicados
    static void crearEscena(const std::string& rutaArchivo);

    // Añadir imagen al JSON interno (antes de guardarlo)
    static void anyadirImagen(
        const std::string& id,
        const std::string& ruta,
        int x,
        int y
    );

private:
    static nlohmann::json escena; // Estructura JSON que se irá llenando
};