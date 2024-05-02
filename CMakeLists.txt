cmake_minimum_required(VERSION 3.12)
project(dcc001-trabalho)

# Configurações do executável
add_executable(main src/main.cpp)

# Configurações de compilação (opcional)
set(CMAKE_CXX_STANDARD 17)

# Adicione os arquivos .cpp da biblioteca MinhaBiblioteca ao executável
target_sources(main PRIVATE
    include/Graph.h
    include/Utils.h
)

# Caminho completo para o arquivo grafo.dot
set(GRAFO_PATH ../outputs/)

add_custom_target(
    gerar_grafo
    COMMAND dot -Tpng $ -o ${CMAKE_ARGV3}.png
    WORKING_DIRECTORY ${GRAFO_PATH}
    COMMENT "Gerando imagem do grafo..."
)

# Inclua o diretório que contém os cabeçalhos da biblioteca
target_include_directories(main PRIVATE include)
target_include_directories(main PRIVATE object)
target_include_directories(main PRIVATE src)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION 1.0.0)
include(CPack)
