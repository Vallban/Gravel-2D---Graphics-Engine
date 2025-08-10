cmake_minimum_required(VERSION 3.15)
project(Gravel2D LANGUAGES CXX)

# Establecer estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Rutas a los códigos
set(ENGINE_DIR "${CMAKE_SOURCE_DIR}/Engine")
set(CORE_DIR "${ENGINE_DIR}/Core")
    set(SCENE_DIR "${CORE_DIR}/Scenes")
set(GRAPHICS_DIR "${ENGINE_DIR}/Graphics")
set(UTILS_DIR "${ENGINE_DIR}/Utils")

# Listado general de fuentes para el ejecutable
file(GLOB_RECURSE ENGINE_SOURCES
    ${ENGINE_DIR}/*.cpp
)

# Función para eliminar las librerías de la lista
function(remove_libraries_from_list listVar)
    foreach(fileToRemove IN ITEMS ${ARGN})
        list(REMOVE_ITEM ${listVar} ${fileToRemove})
    endforeach()
    # Actualiza la variable original
    set(${listVar} ${${listVar}} PARENT_SCOPE)
endfunction()

# Llamada a quitar librerías de la lista
remove_libraries_from_list(ENGINE_SOURCES
        ${SCENE_DIR}/Scene.cpp
        ${SCENE_DIR}/SceneManager.cpp
    ${CORE_DIR}/Loader.cpp
    ${CORE_DIR}/ResourceManager.cpp
    ${GRAPHICS_DIR}/Framebuffer.cpp
    ${GRAPHICS_DIR}/RenderEngine.cpp
    ${UTILS_DIR}/BMP.cpp
    ${UTILS_DIR}/DynamicSceneJSON.cpp
)

# Función para crear librerías estáticas estándar
function(add_engine_library libname srcdir)
    add_library(${libname} STATIC
        ${srcdir}/${libname}.cpp
    )
    target_include_directories(${libname} PUBLIC ${srcdir})
    target_compile_definitions(${libname} PRIVATE UNICODE _UNICODE)
endfunction()

# Llamada a añadir librerías
    add_engine_library(Scene ${SCENE_DIR})
    add_engine_library(SceneManager ${SCENE_DIR})
add_engine_library(Loader ${CORE_DIR})
add_engine_library(ResourceManager ${CORE_DIR})
add_engine_library(Framebuffer ${GRAPHICS_DIR})
add_engine_library(RenderEngine ${GRAPHICS_DIR})
add_engine_library(BMP ${UTILS_DIR})
add_engine_library(DynamicSceneJSON ${UTILS_DIR})

# Añadir ejecutable principal
add_executable(Gravel2D ${ENGINE_SOURCES})

# Indicamos que es aplicación Windows (WinMain, no main)
set_target_properties(Gravel2D PROPERTIES WIN32_EXECUTABLE ON)

# Activar soporte Unicode en Windows
if (WIN32)
    target_compile_definitions(Gravel2D PRIVATE UNICODE _UNICODE)
endif()

# Añadir includes al ejecutable
target_include_directories(Gravel2D PRIVATE
    ${ENGINE_DIR}/Core
        ${ENGINE_DIR}/Core/Scenes
    ${ENGINE_DIR}/Graphics
    ${ENGINE_DIR}/Input
    ${ENGINE_DIR}/Utils
    ${ENGINE_DIR}/Window
)

# Incluir librerías del sistema (WinAPI ya está implícita)
if (WIN32)
    target_link_libraries(Gravel2D PRIVATE user32 gdi32)
endif()

target_link_libraries(Gravel2D PRIVATE
        Scene
        SceneManager 
    Loader
    ResourceManager
    Framebuffer
    RenderEngine
    BMP
    DynamicSceneJSON
)