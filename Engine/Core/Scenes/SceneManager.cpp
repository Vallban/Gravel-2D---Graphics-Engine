#include "SceneManager.h"
#include <iostream>

    void SceneManager::establecerEA(const std::wstring& nombre){
        auto it = escenas.find(nombre);
        if (it != escenas.end()) {
            if (escenaActiva) {
                escenaActiva->activaSalida();
            }
            escenaActiva = it->second;
            escenaActiva->activaEntrada();

            std::wcout << L"[SceneManager] Escena activa establecida: " << nombre << std::endl;
        } else {
            std::wcout << L"[SceneManager] No se encontró la escena: " << nombre << std::endl;
        }
    }
    
    void SceneManager::anyadirEscena(const std::wstring& nombre, std::shared_ptr<Scene> escena){
        escenas[nombre] = escena;
        std::wcout << L"[SceneManager] Escena añadida: " << nombre << std::endl;
    }

    std::shared_ptr<Scene> SceneManager::recogeEA(){
        return escenaActiva;
    }

    void SceneManager::actualizaEA(float deltaTime){
        if (escenaActiva) {
            escenaActiva->actualizar(deltaTime);
        }
    }

    void SceneManager::renderizarEA(){
        if (escenaActiva) {
            escenaActiva->renderizar();
        }
    }