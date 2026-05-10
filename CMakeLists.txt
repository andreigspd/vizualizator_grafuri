cmake_minimum_required(VERSION 3.28)
project(VizualizatorGrafuri)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp    "include/graf.h" "src/graf.cpp" "include/util.h" "include/aplicatie.h" "src/aplicatie.cpp" "include/nod.h" "include/muchie.h" "include/meniu.h" "include/manager_evenimente.h" "src/nod.cpp" "src/muchie.cpp" "src/manager_evenimente.cpp" "src/meniu.cpp" "include/buton.h" "src/buton.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
