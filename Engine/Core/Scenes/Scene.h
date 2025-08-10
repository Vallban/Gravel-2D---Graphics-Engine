#pragma once
#include <string>
#include <memory>
#include <vector>
#include <optional>
#include "../Images.h"

class Scene {
    public:
        Scene(const std::wstring& nombre);
        virtual ~Scene();

        virtual void cargar();
        virtual void liberar();
        virtual void activaEntrada();
        virtual void activaSalida();

        virtual void actualizar(float dt);
        virtual void renderizar();

        std::wstring getName() const;

        void anyadirImagen(const Core::Imagen& imagen);
        /*
        bool mostrarImagen(const std::wstring& id);
        bool ocultarIagen(const std::wstrig& id);
        
        revisar porque a mi me parece más intuitivo
        que haya una sola funcio e.g. "visible()"
        que si es true sea visible y que si es
        false que no lo sea, pero veremos
        */
        std::optional<std::reference_wrapper<Core::Imagen>> obtenerImagen(const std::wstring& id);
    
        protected:
            std::wstring name;
            std::vector<Core::Imagen> imagenesConPosiciones;
};