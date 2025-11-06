#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo "-----------------------------"
    echo " Address Book Menu"
    echo "-----------------------------"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert a Record"
    echo "4. Search a Record"
    echo "5. Delete a Record"
    echo "6. Modify a Record"
    echo "7. Exit"
    echo -n "Enter your choice: "
    read choice

    case $choice in
        1)
            > $FILE
            echo "Address Book created (cleared old records)."
            ;;
        2)
            if [ -s $FILE ]; then
                echo "------ Address Book ------"
                cat $FILE
            else
                echo "Address Book is empty."
            fi
            ;;
        3)
            echo -n "Enter Name: "; read name
            echo -n "Enter Phone: "; read phone
            echo -n "Enter Email: "; read email
            echo "$name | $phone | $email" >> $FILE
            echo "Record added."
            ;;
        4)
            echo -n "Enter name to search: "; read name
            grep -i "$name" $FILE || echo "Record not found."
            ;;
        5)
            echo -n "Enter name to delete: "; read name
            grep -iv "$name" $FILE > temp && mv temp $FILE
            echo "Record deleted (if existed)."
            ;;
        6)
            echo -n "Enter name to modify: "; read name
            grep -iv "$name" $FILE > temp
            echo -n "Enter New Name: "; read new_name
            echo -n "Enter New Phone: "; read new_phone
            echo -n "Enter New Email: "; read new_email
            echo "$new_name | $new_phone | $new_email" >> temp
            mv temp $FILE
            echo "Record modified."
            ;;
        7)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid choice, try again!"
            ;;
    esac
done
