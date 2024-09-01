# Project Idea: File Organizer

## 🔍 Overview:

The goal of this project is to create a Bash script that organizes files in a specified directory based on their file types into separate subdirectories. 

This can be useful to keep your directories clean and tidy by automatically sorting files into appropriate categories.

## 📌 Features:

    1.The script should take a directory path as an argument and organize the files within that directory.
    
    2.It should create subdirectories based on the file extensions (e.g., "txt" for text files, "jpg" for image files).
    
    3.Files with unknown or no file extensions should be placed in a "misc" subdirectory.
    
    4.If a subdirectory for a particular file type already exists, the script should move the files into that existing directory.
    
    5.The script should handle edge cases, such as files with no extensions or hidden files (those starting with a dot).
## ⌨️ Run Script:
```
chmod +x File_Organizer.sh
./File_Organizer.sh {{directory path}}

```


