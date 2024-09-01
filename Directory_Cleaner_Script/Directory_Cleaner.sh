#!/usr/bin/bash
############################### Description ##########################################################
#                        * Directory Cleaner *
# Objective :
# Create a Bash script that cleans up a specified directory by removing files older than a certain number of days.
# The script should accept the directory path and the number of days as arguments.
# Implement a dry-run option that shows which files would be deleted without actually deleting them.
# Input : directory Path , Number of days , required option
# Output : Clean --> remove files older than number of days 
#          dry-run --> Print files older than number of days 
# Author: Mariam Reda
#
############################### Global Variables & Functions #########################################

declare DIRECTORY_PATH=$1
declare -i NUMBER_OF_DAYS=$2
declare OPTION

 ############################### main Function ########################################################
function main () {

    declare -i FILE_DATE
    declare -i CURRENT_DATE
    declare -i FILE_AGE
    declare FILE_PATH
    
    if [[ ! -d $DIRECTORY_PATH ]]; then
       echo "Directory not exist $DIRECTORY_PATH"
       exit 1
    fi
    
    echo " 1. Clean directory "
    echo " 2. Dry-Run "
    read -p "Select Option(1-2) :" OPTION
    
    # List Content of Input directory to Processing on Files

    ls -a $DIRECTORY_PATH | while read line;do
    FILE_PATH="$DIRECTORY_PATH/$line"

    # Check if file is not current (.) or (..)
    if [[ ! ($FILE_PATH == "$DIRECTORY_PATH/.") && ! ($FILE_PATH == "$DIRECTORY_PATH/..") ]]; then
        # get date of file and Current date
        FILE_DATE=$(date +%s -r $FILE_PATH)
        CURRENT_DATE=$(date +%s)

        # get difference of dates to compute age of file in days
        FILE_AGE=$((($CURRENT_DATE - $FILE_DATE)/ 86400))

        # check on file age according to input number of days.
        if (( $NUMBER_OF_DAYS <= $FILE_AGE )); then

            # true case : based on input Option > Clear or just Print
            case $OPTION in
            1)
                if [[ -f $FILE_PATH ]]; then
                    rm $FILE_PATH
                fi  
                ;;
            2)
                if [[ -f $FILE_PATH ]]; then
                    echo "$FILE_PATH"
                fi
                ;;
            *)
                echo "Invalid Option"
                ;;
            esac
        fi
    fi
 done
    
}
############################### Calling main ########################################################
main 
