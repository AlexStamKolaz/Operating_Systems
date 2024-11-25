#! bin/usr/bash

#read csv data
insert_data(){
echo "insert the name of the file"
read filename
if [ $filename != "NULL" ]
then
    cat $filename
else
    filename=passenger_data.csv
    cat $filename
fi

}

search_passenger(){
echo "name or surname of passenger"
read  name surname
grep $name -w $filename >>tmp.csv # δεν ξερς αν ειναι ονομα ή επωνυμο βοηθα με την δημιοργια ενος αρχειου tmp
grep $surname -w tmp.csv

}


echo "Welcome to PassFinder...\n"
echo "Please insert your choice\n"
read choice
while  [[ $choise -gt 0 ]] || [[ $choice -lt 6 ]]
do
    if [ $choice -eq 1 ]
    then
        insert_data
    elif [ $choice -eq 2 ]
    then
        search_passenger
        rm tmp.txt
    else
    echo "hello"
    fi
    echo "Please insert your choice\n"
    read choice

done

# change data
echo "give code or fullname"
read code
echo "Please insert the the field you want to place"
read field
if [ $field == "fullname" ]
then
    read name



