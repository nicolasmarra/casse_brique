cmake_minimum_required(VERSION 3.7)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/sdl2")

project(CasseBrique)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}/SDL2_ttf)

# Liste des fichiers source du projet (ajoutez les fichiers .cpp des classes ici)
set(SOURCES 
    src/main.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/Brick.cpp
    src/Ball.cpp
    src/Platform.cpp
    src/PowerUp.cpp
)

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Inclusion des répertoires d'en-tête
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    include  # Ajoutez le répertoire include pour inclure les fichiers d'en-tête de vos classes
)

# Ajout des bibliothèques
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${SDL2_LIBRARIES}
)


# Copie des ressources vers le répertoire de construction
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Configuration spécifique à Visual Studio
IF (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    VS_STARTUP_PROJECT(${PROJECT_NAME})
ENDIF()
