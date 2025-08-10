#include "Scene.h"
#include <iostream>

Scene::Scene(const std::wstring& nombre) : name(nombre){}
Scene::~Scene() {}

void Scene::cargar() {}
void Scene::liberar() {}
void Scene::activaEntrada(){}
void Scene::activaSalida(){}

void Scene::actualizar(float dt) {}
void Scene::renderizar() {}

std::wstring Scene::getName() const {
    return name;
}