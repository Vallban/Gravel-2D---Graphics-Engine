#pragma once
#include <string>
#include <memory>
#include <vector>
#include <optional>
#include "../Images.h"
#include "../../Graphics/RenderEngine.h"

class Scene {
    public:
        Scene(const std::wstring& nombre);
        virtual ~Scene();

        virtual void cargar();
        virtual void liberar();
        virtual void activaEntrada();
        virtual void activaSalida();

        virtual void actualizar(float dt);
        virtual void renderizar(Graphics::RenderEngine& render);

        std::wstring getName() const;

        void anyadirImagen(const Core::Imagen& imagen);
        bool escenaVisible();

        std::optional<std::reference_wrapper<Core::Imagen>> obtenerImagen(const std::wstring& id);
    
        protected:
            std::wstring name;
            std::vector<Core::Imagen> imagenesDeLaEscena;
};