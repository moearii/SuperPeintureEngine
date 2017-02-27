#!/bin/sh
# Indique au système que l'argument qui suit est le programme utilisé pour exécuter ce fichier
# En règle générale, les "#" servent à mettre en commentaire le texte qui suit comme ici
echo Transformer fichiers .cpp en fichier .xml

# Récupérer tous les fichiers .cpp du répertoire Pigments
list=`ls *.cpp`
for i in $list
do
echo file: $i
# supprimer les 2 premières lignes du fichier
sed '1,2d' $i > newfile ; mv newfile $i
# supprimer tous les espaces
sed -i 's/ //g' $i
# supprimer toutes les lignes vides
sed '/./!d' $i > newfile ; mv newfile $i
# supprimer les fins de ligne
sed 's/},\\/ /g' $i > newfile ; mv newfile $i
sed 's/}\(.*\);/ /' $i > newfile ; mv newfile $i
# ouvrir balise
sed -e 's/{/<scattering>/g' $i > newfile ; mv newfile $i
# fermer balise
sed -e 's/.*/&<\\scattering>/' $i > newfile ; mv newfile $i
sed -i 's/ //g' $i

# ajouter racine
#sed '1 i\<pigment>' $i > newfile ; mv newfile $i
# fermer racine
#sed '$ i\<\\pigment>'  $i > newfile ; mv newfile $i

done

 
exit 0
