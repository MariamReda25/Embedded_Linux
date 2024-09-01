#!/usr/bin/bash
############################### Description ##########################################################
#                          * File Organizer Script*
#  Project Objectaive : The goal of this project is to create a Bash script that organizes files in 
#  aspecified directory based on their file types into separate subdirectories. 
#  Input : Directory Path
#  Output: Tree of Organized directory
#  Author: Mariam Reda 
############################### Global Variables & Functions #########################################
# input directory path from terminal
declare DIRECTORY_PATH=$1

declare FILE_EXTENSION

# Function used to Organize Files based on it's extension
function Organize_Files () {

        # Extract File's extension
        FILE_EXTENSION="${1##*.}"

        # Check for (Files with no extension , hidden Files , Files with unknown extinsion)
       if [[ ($FILE_EXTENSION == $1) || ($FILE_EXTENSION == "unknown") || ((! -z $FILE_EXTENSION) &&( -z "${1%.*}"))]]; then
            if [[ ! -d "$DIRECTORY_PATH/misc" ]]; then
                mkdir "$DIRECTORY_PATH/misc"
            fi
            mv "$2" "$DIRECTORY_PATH/misc"
        else 
           if [[ ! -d "$DIRECTORY_PATH/$FILE_EXTENSION" ]]; then
              mkdir "$DIRECTORY_PATH/$FILE_EXTENSION"
           fi
           mv "$2" "$DIRECTORY_PATH/$FILE_EXTENSION"
        fi
 
}
############################### main Function #################################################################

function main () {
   
   declare FILE_PATH

  # check if input directory is exist or not
  if [[ ! -d $DIRECTORY_PATH ]]; then
       echo "directory Not Exist"
       exit 1 
  fi
    
   # Start Proceesing on Files within this directory by Passing it to organize Function

     
     ls -a $DIRECTORY_PATH | while read file; do
         FILE_PATH="$DIRECTORY_PATH/$file"
        if [[ -f $FILE_PATH ]]; then
         Organize_Files $file $FILE_PATH
        fi
   done

   # After organizing Files within input directory > Print Tree of Organized directory
   tree $DIRECTORY_PATH

}
############################### Calling main ########################################################
 main
