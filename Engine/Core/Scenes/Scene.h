#pragma once
#include <string>
#include <memory>

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
    
        protected:
            std::wstring name;
};