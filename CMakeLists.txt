cmake_minimum_required(VERSION 3.22)
project(AyED_TP2_1c2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

add_compile_options(-Wall -Werror -Wconversion)

include_directories(include)

# Si crean otros archivos .cpp, los tienen que agregar acá de la forma:
#   "directorio/archivo.cpp"
set(ARCHIVOS_FUENTE
        "include/vector.hpp"
	"src/gacha.cpp"
        "src/salto.cpp"
        "src/generador_salto.cpp"
        "src/recompensa.cpp"
        )

add_executable(AyED_TP2_1c2024
        ${ARCHIVOS_FUENTE}
        main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e4fdb87e76b9fc4b01c54ad81aea19d6e994b994
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_subdirectory(tests/gacha)
add_subdirectory(tests/vector)

target_sources(gacha_test PRIVATE ${ARCHIVOS_FUENTE})
target_sources(vector_test PRIVATE ${ARCHIVOS_FUENTE})