#!/bin/bash

# Verifica se foram fornecidos os argumentos corretos
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 <arquivo_dot> <arquivo_saida_png>"
    exit 1
fi

# Executa o comando dot para gerar o arquivo PNG
dot -Tpng "../outputs/$1" -o "../outputs/$2"
