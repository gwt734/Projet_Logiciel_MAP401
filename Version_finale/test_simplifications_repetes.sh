#!/bin/bash

# Teste la simplification répétée d'une image
echo a > tmp
for ((i=1; i <= $1; i++))
do
    ./test_simplifications >> tmp
    if [ $? -ne 0 ]
    then
        echo "Erreur lors de la simplification"
        exit 1
    fi

    
done

echo "Simplifications réussies"