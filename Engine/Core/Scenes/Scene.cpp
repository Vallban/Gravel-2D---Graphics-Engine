#include "Scene.h"
#include <iostream>
#include <algorithm>

Scene::Scene(const std::wstring& nombre) : name(nombre){}
Scene::~Scene() {}

void Scene::cargar() {}
void Scene::liberar() {}
void Scene::activaEntrada(){}
void Scene::activaSalida(){}

void Scene::actualizar(float dt) {}
void Scene::renderizar() {
    // Revisar |vvv| porque hay lo mismo en render() en main
    for(const auto& imagen : imagenesConPosiciones){
        if (imagen.visible){

        }
    }
}

std::wstring Scene::getName() const {
    return name;
}

void Scene::anyadirImagen(const Core::Imagen& imagen) {
    imagenesConPosiciones.push_back(imagen);
}

/*
bool Scene::mostrarImagen(const std::wstring& id) {
    auto it = std::find_if(imagenesConPosiciones.begin(), imagenesConPosiciones.end(),
        [&](const Core::Imagen& img){ return img.id == id; });
    if (it != imagenesConPosiciones.end()) {
        it->visible = true;
        return true;
    }
    return false;
}

bool Scene::ocultarImagen(const std::wstring& id) {
    auto it = std::find_if(imagenesConPosiciones.begin(), imagenesConPosiciones.end(),
        [&](const Core::Imagen& img){ return img.id == id; });
    if (it != imagenesConPosiciones.end()) {
        it->visible = false;
        return true;
    }
    return false;
}
*/

std::optional<std::reference_wrapper<Core::Imagen>> Scene::obtenerImagen(const std::wstring& id) {
    auto it = std::find_if(imagenesConPosiciones.begin(), imagenesConPosiciones.end(),
        [&](const Core::Imagen& imagen){ return imagen.id == id; });
    if (it != imagenesConPosiciones.end()) {
        return *it;
    }
    return std::nullopt;
}