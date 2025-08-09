#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

// EA = Escena Activa

class SceneManager {
    public:
        void establecerEA(const std::wstring& name);
        void anyadirEscena(const std::wstring& name, std::shared_ptr<Scene> scene);
        std::shared_ptr<Scene> recogeEA();
        void actualizaEA(float deltaTime);
        void renderizarEA();

    private:
        std::unordered_map<std::wstring, std::shared_ptr<Scene>> escenas;
        std::shared_ptr<Scene> escenaActiva; //EA

};