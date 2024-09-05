#!/usr/bin/bash
############################### Description ##########################################################
#                          * File Organizer Script*
#  Project Objectaive : The goal of this project is to create a Bash script that organizes files in 
#  aspecified directory based on their file types into separate subdirectories. 
#  Input : Directory Path
#  Output: Tree of Organized directory
#  Author: Mariam Reda 
#
############################### Global Variables & Functions #########################################
# - Variables :

# input directory path from terminal
declare DIRECTORY_PATH=$1

declare LOG_FILE="log.txt"

# Configuration File :
declare CONFIG_FILE="File_Organizer.conf"

   if [[ -f $CONFIG_FILE ]]; then
      source $CONFIG_FILE
   else 
      Print " Log[ERROR] : Configuration File Not exist " >> $LOG_FILE
      exit 1
   fi

declare FILE_EXTENSION

# - FUnctions :

# Function print date of running Script in log file
function Start_script () {

   date > $LOG_FILE
}
# Function used to Print Messages
function Print () {
   echo "$1"
}

# Function Check existance of input directoy
function Check_dierctory_existance () {

  if [[ ! -d $DIRECTORY_PATH ]]; then
      Print "Log[ERROR]:Input directory Not Exist" >> $LOG_FILE
       exit 1 
  fi
}

# Function used to extract extension of file
function Extract_file_extension () {

   FILE_EXTENSION="${1##*.}"
}

# Function Create new directory 
function Create () {
     
     mkdir "$1"
}

# Function Move files 
function Move () {
  
     mv "$1" "$2"
}

# Function List content of directory
function List () {

   ls -a "$1"
}

# Function Organize Files based on extension
function Organize_Files () {
   
   # Case 1. File with No extension
   if [[ $1 == $2 ]]; then
      if [[ ! -d "$DIRECTORY_PATH/$NO_EXTENSION_DIR" ]]; then
            Create "$DIRECTORY_PATH/$NO_EXTENSION_DIR"
      fi
      Move "$3" "$DIRECTORY_PATH/$NO_EXTENSION_DIR"

   # Case 2. Hidden Files except (.) / (..)
   elif [[ (! -z $1) && ( -z "${2%.*}") ]]; then
      if [[ ! -d "$DIRECTORY_PATH/$HIDDEN_DIR" ]]; then
         Create "$DIRECTORY_PATH/$HIDDEN_DIR"
      fi
      Move "$3" "$DIRECTORY_PATH/$HIDDEN_DIR"
   
   # Case 3. Unknown 
   elif [[ $1 == "unknown" ]]; then 
      if [[ ! -d "$DIRECTORY_PATH/$UNKNOWN_DIR" ]]; then
         Create "$DIRECTORY_PATH/$UNKNOWN_DIR"
      fi
      Move "$3" "$DIRECTORY_PATH/$UNKNOWN_DIR"
   
   # Case 4 . file with specific extension
   else 
      if [[ ! -d "$DIRECTORY_PATH/$1" ]]; then
              Create "$DIRECTORY_PATH/$1"
           fi
           Move "$3" "$DIRECTORY_PATH/$1"
   fi
 
}

# Function used to Process on files within directory 
function Process_directory () {
      
   List "$DIRECTORY_PATH" | while read file; do
      FILE_PATH="$DIRECTORY_PATH/$file"
      if [[ -f $FILE_PATH ]]; then
         Extract_file_extension "$file"
         Organize_Files "$FILE_EXTENSION" "$file" "$FILE_PATH"

      fi
   done
}

# Function Print Content of directory in tree fashion
function Print_Tree () {
    
   tree $1
}

############################### main Function #################################################################

function main () {
  
    Start_script

  # Check existance of input directory
   Check_dierctory_existance
   
    # Start Proceesing on Files within this directory by Passing it to organize Function 
   Process_directory

   # After organizing Files within input directory > Print Tree of Organized directory
   Print_Tree $DIRECTORY_PATH

}
############################### Calling main ########################################################
 main
