#!/bin/bash

CSV="personas.csv"

echo "Insertando el primer dataset"
cd ..
echo "El dataset se esta introduciendo en .csv"
echo "El .csv esta en la ruta:"
pwd

if [ -f $CSV ]
then
  rm -f personas.csv
else
  :  
fi


echo "1, Kevin" >> personas.csv
echo "2, Nicolas" >> personas.csv
echo "3, Tomas" >> personas.csv
echo "4, Simar" >> personas.csv




