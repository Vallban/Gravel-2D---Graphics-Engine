#include "../Utils/BMP.h"
#include <cstdio>
#include <stdexcept>

namespace Utils {

    ImagenBMP cargarBMP(const std::wstring& ruta) {
        FILE* archivo = _wfopen(ruta.c_str(), L"rb");
        if (!archivo) throw std::runtime_error("No se pudo abrir el archivo BMP");

        // Encabezado BMP
        uint16_t tipo;
        fread(&tipo, sizeof(tipo), 1, archivo);
        if (tipo != 0x4D42) throw std::runtime_error("No es un archivo BMP válido");

        fseek(archivo, 10, SEEK_SET);
        uint32_t offsetDatos;
        fread(&offsetDatos, sizeof(offsetDatos), 1, archivo);

        // Encabezado DIB
        uint32_t tamHeader;
        fread(&tamHeader, sizeof(tamHeader), 1, archivo);
        if (tamHeader < 40) throw std::runtime_error("Solo se soporta BITMAPINFOHEADER o superiores - tamHeader("+ std::to_string(tamHeader) + ")");

        int32_t ancho, alto;
        fread(&ancho, sizeof(ancho), 1, archivo);
        fread(&alto, sizeof(alto), 1, archivo);

        uint16_t planes, bpp;
        fread(&planes, sizeof(planes), 1, archivo);
        fread(&bpp, sizeof(bpp), 1, archivo);

        if (planes != 1 || bpp != 32)
            throw std::runtime_error("Solo se soportan BMPs de 32 bits");

        fseek(archivo, offsetDatos, SEEK_SET);

        bool abajoArriba = alto > 0;
        int h = std::abs(alto);
        int w = ancho;

        std::vector<uint32_t> pixeles(h * w);

        for (int y = 0; y < h; ++y) {
            int fila = abajoArriba ? (h - 1 - y) : y;
            for (int x = 0; x < w; ++x) {
                uint8_t bgra[4];
                fread(bgra, 1, 4, archivo);
                uint32_t color = (bgra[3] << 24) | (bgra[2] << 16) | (bgra[1] << 8) | (bgra[0]);
                pixeles[fila * w + x] = color;
            }
        }

        fclose(archivo);

        return ImagenBMP{ w, h, std::move(pixeles) };
    }

}