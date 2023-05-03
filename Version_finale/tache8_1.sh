#!/bin/bash

# Tache 8.1

for image in zebres-1000x0750.pbm zebres-2000x1500.pbm zebres-3000x2250.pbm zebres-4000x3000.pbm
do
    echo -e "\t\033[0;31m$image\033[0m"
    time ./main ../IMAGES/$image 0 1
    echo
done