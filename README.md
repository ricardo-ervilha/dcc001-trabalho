# DCC001 (2024.1) - Análise e Projeto de Algoritmos
Repositório associado ao trabalho da disciplina.

# Instruções para compilação
```bash
# Clone o repositório
$ git clone https://github.com/ricardo-ervilha/dcc001-trabalho.git

$ cd dcc001-trabalho

# Crie uma pasta chamada build
$ mkdir build

# Entre na pasta build
$ cd build

# Configure o projeto com cmake
$ cmake ..

# Compile o projeto e gere o executável
$ make

# Outra opção para compilar e gerar o executável 
$ cmake --build .

# Rode o programa
$ ./main

# Alternativa para compilar, gerar o executável e rodar o programa
$ cmake --build . && ./main

#Para gerar a imagem dos grafos, rode o seguinte (arq1 e arq2 são os respectivos nomes para o dot gerado ao executar o programa e o nome da imagem de saída)
../graphviz.sh arq1.dot arq2.png

```
