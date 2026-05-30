#!/bin/bash

CSV="personas.csv"

echo "Insertando el segundo dataset, de datos medianos"
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


echo "10, Kevin" >> personas.csv
echo "30, Nicolas" >> personas.csv
echo "25, Tomas" >> personas.csv
echo "4, Simar" >> personas.csv
echo "22, Sofia" >> personas.csv
echo "7, Juan" >> personas.csv
echo "50, Manu" >> personas.csv
echo "8, Diego" >> personas.csv
echo "60, Peralta" >> personas.csv
echo "45, Claudia" >> personas.csv
echo "3, Karen" >> personas.csv
echo "1, Nubia" >> personas.csv
echo "4, Lilian" >> personas.csv
echo "2, Sans" >> personas.csv
echo "100, Morgana" >> personas.csv


echo "Se ha introducido el dataset de manera desorganizada, ejecute el programa para organizarlo y probar con el"



