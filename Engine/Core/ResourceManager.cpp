#include "ResourceManager.h"
#include <stdexcept>
#include <string>
#include <codecvt>
#include <locale>

namespace Core {

    // Excepción personalizada que acepta wstring y convierte a UTF-8 para what()
    class WRuntimeError : public std::exception {
        std::wstring mensaje_wide;
        std::string mensaje_utf8;

        static std::string convertirAUTF8(const std::wstring& wstr) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> convertidor;
            return convertidor.to_bytes(wstr);
        }

    public:
        explicit WRuntimeError(const std::wstring& mensaje)
            : mensaje_wide(mensaje), mensaje_utf8(convertirAUTF8(mensaje)) {}

        const char* what() const noexcept override {
            return mensaje_utf8.c_str();
        }

        const std::wstring& wwhat() const noexcept {
            return mensaje_wide;
        }
    };

    void ResourceManager::cargarTextura(const std::wstring& nombre, const std::wstring& ruta) {
        if (texturas.find(nombre) != texturas.end()) return;

        try {
            texturas.emplace(nombre, Utils::cargarBMP(ruta));
        } catch (const std::exception& e) {
            throw WRuntimeError(L"Error al cargar textura: '" + nombre + L"'");
        }
    }

    const Utils::ImagenBMP& ResourceManager::obtenerTextura(const std::wstring& nombre) const {
        auto it = texturas.find(nombre);
        if (it == texturas.end()) {
            throw WRuntimeError(L"Textura no encontrada: " + nombre);
        }
        return it->second;
    }

    void ResourceManager::eliminarTextura(const std::wstring& nombre) {
        texturas.erase(nombre);
    }

    void ResourceManager::limpiar() {
        texturas.clear();
    }
}