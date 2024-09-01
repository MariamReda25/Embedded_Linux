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
declare directory_path=$1

declare File_Extension

# Function used to Organize Files based on it's extension
function Organize_Files () {

        # Extract File's extension
        File_Extension="${1##*.}"

        # Check for (Files with no extension , hidden Files , Files with unknown extinsion)
       if [[ ($File_Extension == $1) || ($File_Extension == "unknown") || ((! -z $File_Extension) &&( -z "${1%.*}"))]]; then
            if [[ ! -d "misc" ]]; then
                mkdir misc
            fi
            mv "$1" "misc"
        else 
           if [[ ! -d "$File_Extension" ]]; then
              mkdir "$File_Extension"
           fi
           mv "$1" "$File_Extension"
        fi
 
}
############################### main Function #################################################################

function main () {
  
  # check if input directory is exist or not
  if [[ ! -d $directory_path ]]; then
       echo "directory Not Exist"
       exit 1 
  fi
    
   # Start Proceesing on Files within this directory by Passing it to organize Function

    cd ${directory_path}
     ls -a | while read file; do
        if [[ -f $file ]]; then
         Organize_Files $file
        fi
   done

   # After organizing Files within input directory > Print Tree of Organized directory
   tree

}
############################### Calling main ########################################################
main
