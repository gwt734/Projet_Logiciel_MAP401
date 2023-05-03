#!/bin/bash

degres="2 3"
distances="1 3 10 30"
fichiers="Asterix3.pbm lettre-L-cursive.pbm ColombesDeLaPaix.pbm"

for fichier in $fichiers
do
    echo $fichier
    for degre in $degres
    do
        echo $degre
        for distance in $distances
        do
            echo $distance
            echo ./main ../IMAGES/$fichier $distance $degre
            ./main ../IMAGES/$fichier $distance $degre
        done
    done
done
