#include <windows.h> // Librería Windows
#include <iostream> // Librería estándar
#include <cstdint> // Librería 32bits
#include <vector>
#include <string>
#include <chrono>
#include "Core/Images.h"
#include "Core/Loader.h"
#include "Core/ResourceManager.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/RenderEngine.h"
#include "Utils/BMP.h"
#include "../Utils/DynamicSceneJSON.h"

#define ANCHO 1920
#define ALTO 1080

struct VentanaBase {
    int anchoPantallaInvitado;
    int altoPantallaInvitado;
    Framebuffer framebuffer;
    Core::ResourceManager recursos;
    Graphics::RenderEngine renderEngine;

    std::vector<Core::Imagen> imagenesConPosiciones;

    VentanaBase(int ancho = ANCHO, int alto = ALTO)
        : anchoPantallaInvitado(ancho),
          altoPantallaInvitado(alto),
          framebuffer(),
          recursos(),
          renderEngine(framebuffer, recursos){
        if (!framebuffer.crear(ancho, alto)){
            throw std::runtime_error("Error al crear framebuffer");
        }
    }
};

void processInput(){

}

void update(float dt){
    // mas adelante
}

void render(VentanaBase& estado){
    auto& render = estado.renderEngine;
    render.iniciarFrame(0xFF000000); // negro
    for(const auto& imagen : estado.imagenesConPosiciones){
        try {
            render.dibujarImagen(imagen.id, imagen.coordenadas.x, imagen.coordenadas.y);
        } catch (const std::exception& e) {
            // Imagen no cargada, error
        }
    }

    render.finalizarFrame(); // si implementas overlays, post-procesado, etc.
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    VentanaBase* estado = reinterpret_cast<VentanaBase*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    switch(uMsg){
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HDC hdcMem = CreateCompatibleDC(hdc);
            
            if (estado && estado->framebuffer.bitmap) {
                RECT clientRect;
                GetClientRect(hwnd, &clientRect);
                int anchoActual = clientRect.right;
                int altoActual = clientRect.bottom;

                HGDIOBJ oldBitmap = SelectObject(hdcMem, estado->framebuffer.bitmap);
                StretchBlt(hdc, 0, 0, anchoActual, altoActual, hdcMem, 0, 0, estado->framebuffer.ancho, estado->framebuffer.alto, SRCCOPY);
                SelectObject(hdcMem, oldBitmap);
            }

            DeleteDC(hdcMem);
            
            EndPaint(hwnd, &ps);
            return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow){
    const wchar_t CLASS_NAME[] = L"MotorVentanaClase";
    int anchoPantallaInvitado = GetSystemMetrics(SM_CXSCREEN);
    int altoPantallaInvitado = GetSystemMetrics(SM_CYSCREEN);
    VentanaBase estado(anchoPantallaInvitado, altoPantallaInvitado);

    WNDCLASSEXW wc = {};
    wc.lpszClassName = CLASS_NAME;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME, L"Gravel2D iniciándose",
        WS_POPUP,
        CW_USEDEFAULT, CW_USEDEFAULT, anchoPantallaInvitado, altoPantallaInvitado,
        nullptr, nullptr, hInstance, nullptr
    );
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&estado));

    if (!hwnd) return 0;

    DynamicSceneJSON::anyadirImagen("InterfazPrueba1", "InterfazPrueba1.bmp", 0, 0);
    DynamicSceneJSON::anyadirImagen("TextoPrueba1", "Pruebas/TextoPrueba1.bmp", 300, 150);
    DynamicSceneJSON::anyadirImagen("TextoPrueba2", "Pruebas/TextoPrueba2.bmp", 100, 200);
    DynamicSceneJSON::crearEscena("Assets/escena.json");

    try {
        Core::Loader::cargar(estado.recursos, estado.imagenesConPosiciones);
    } catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "Error al cargar recursos", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    using namespace std::chrono;
    MSG msg = {};
    bool running = true;
    auto tiempoPrevio = high_resolution_clock::now();

    while (running) {
        // Gestionar mensajes de Windows (cierre, inputs, etc.)
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) running = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Calcular deltaTime
        auto tiempoAhora = high_resolution_clock::now();
        float dt = duration<float>(tiempoAhora - tiempoPrevio).count();
        tiempoPrevio = tiempoAhora;

        // Actualización y renderizado
        processInput();
        update(dt);
        render(estado);
        InvalidateRect(hwnd, nullptr, FALSE);
        float frameTime = 1.0f / 60.0f; // 60 FPS
        if (dt < frameTime) {
            Sleep(static_cast<DWORD>((frameTime - dt) * 1000.0f));
        }
    }
    return 0;
}