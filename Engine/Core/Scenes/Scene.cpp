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
void Scene::renderizar(Graphics::RenderEngine& render) {
    for (const auto& imagen : imagenesDeLaEscena) { // Dibujar todas las imágenes de la escena
        try {
            render.dibujarImagen(imagen.id, imagen.coordenadas.x, imagen.coordenadas.y);
        } catch (...) {
            // Manejo de error
        }
}
}

std::wstring Scene::getName() const {
    return name;
}

void Scene::anyadirImagen(const Core::Imagen& imagen) {
    imagenesDeLaEscena.push_back(imagen);
}

bool Scene::escenaVisible(){
    return false;
}

std::optional<std::reference_wrapper<Core::Imagen>> Scene::obtenerImagen(const std::wstring& id) {
    auto it = std::find_if(imagenesDeLaEscena.begin(), imagenesDeLaEscena.end(),
        [&](const Core::Imagen& imagen){ return imagen.id == id; });
    if (it != imagenesDeLaEscena.end()) {
        return *it;
    }
    return std::nullopt;
}