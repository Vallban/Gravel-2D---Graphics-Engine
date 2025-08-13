#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"
#include "../../Graphics/RenderEngine.h"

// EA = Escena Activa

class SceneManager {
    public:
        SceneManager(std::shared_ptr<Scene> escenaInicial)
        : escenaActiva(escenaInicial) {}
        
        void establecerEA(const std::wstring& name);
        void anyadirEscena(const std::wstring& name, std::shared_ptr<Scene> scene);
        std::shared_ptr<Scene> recogeEA();
        void actualizaEA(float deltaTime);
        void renderizarEA(Graphics::RenderEngine& render);

    private:
        std::unordered_map<std::wstring, std::shared_ptr<Scene>> escenas;
        std::shared_ptr<Scene> escenaActiva;

};