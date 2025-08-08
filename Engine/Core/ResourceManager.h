#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "../Utils/BMP.h"

namespace Core{
    class ResourceManager{
    public:
        void cargarTextura(const std::wstring& name, const std::wstring& ruta);
        const Utils::ImagenBMP& obtenerTextura(const std::wstring& name) const;
        void eliminarTextura(const std::wstring& name);
        void limpiar();

    private:
        std::unordered_map<std::wstring, Utils::ImagenBMP> texturas;
    };
}