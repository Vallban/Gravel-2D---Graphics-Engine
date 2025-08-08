#include "RenderEngine.h"
#include <stdexcept>

namespace Graphics{
    RenderEngine::RenderEngine(Framebuffer& fb, Core::ResourceManager& rm)
        : framebuffer(fb), recursos(rm) {}

    void RenderEngine::iniciarFrame(uint32_t colorFondo) {
        framebuffer.limpiar(colorFondo);
    }

    void RenderEngine::dibujarImagen(const std::wstring& nombre, int x, int y) {
        const auto& img = recursos.obtenerTextura(nombre);
        framebuffer.dibujarImagen(img, x, y);
    }

    void RenderEngine::finalizarFrame() {
        // TODO: aplicar efectos, overlays, blending futuro
    }
}