#include "DynamicSceneJSON.h"
#include "../Utils/json.hpp"
#include <fstream>
#include <string>

nlohmann::json DynamicSceneJSON::escena = {
    {"escena", {{"entidades", nlohmann::json::array()}}}
};


void DynamicSceneJSON::crearEscena(const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo);
    archivo << escena.dump(4);
    archivo.close();
}

void DynamicSceneJSON::anyadirImagen(const std::string& id, const std::string& ruta, int x, int y){
    nlohmann::json imagen;

    imagen["id"] = id;
    imagen["ruta"] = ruta;
    imagen["x"] = x;
    imagen["y"] = y;
    escena["escena"]["imagenes"].push_back(imagen);
}