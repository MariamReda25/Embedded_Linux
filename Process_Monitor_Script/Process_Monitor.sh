#!/usr/bin/bash
############################### Description ##########################################################
#                         * Process Mointor Script*
#  Project Objectaive: Create a Bash script that serves as a simple process monitor, 
#  allowing users to view, manage, and analyze running processes on a Unix-like system.
#  Author : Mariam Reda
#
############################### Global Variables & Functions #########################################

declare -i USER_OPTION

CONFIG_FILE="Process_Monitor.conf"

if [[ -f "$CONFIG_FILE" ]]; then
    source "${CONFIG_FILE}"
else
    echo "Error: Configuration file not found."
    exit 1
fi
#####
# Set a default values only used if the config varaible is
UPDATE_INTERVAL=${UPDATE_INTERVAL:-5}
CPU_ALERT_THRESHOLD=${CPU_ALERT_THRESHOLD:-90}
MEMORY_ALERT_THRESHOLD=${MEMORY_ALERT_THRESHOLD:-80}
######

# Function list all running processes with essential information (PID, name, CPU/Memory usage).
function ListRunningProcesses() {

    echo " **************** Running Processes List ********************"

    ps axo pid -Ao user,fname -eo pcpu,pmem

}

# Function terminate a specific process by entering its PID.
function KillProcess () {

    ps -p "$1" >/dev/null 2>&1
    if [[ $? -ne 0 ]]; then
      echo "Process does not exist"
    else
       kill $1 && echo "Process with ID: $1 is Killed "
    fi 

}

# Function Allow users to search for processes based on criteria such as name,user.
function SearchFilter () {
     
     declare -i FILTER_OPTION
     declare -i PID
     declare USER_NAME
     declare PROCESS_NAME
     

     echo " Search for processes based on which option : "
     echo " 1. User "
     echo " 2. Process Name "

    read -p "Enter Your choice : " FILTER_OPTION
    echo " "

    case $FILTER_OPTION in 

    1) 
      read -p "Enter User Name: " USER_NAME
      echo " "
      ps -u "$USER_NAME" >/dev/null 2>&1
       if [[ $? -ne 0 ]]; then
           echo "User does not exist"
      else
            ps --user $USER_NAME
       fi
       ;;
    2)
        read -p "Enter Process Name: " PROCESS_NAME
        echo " "
        PID=$(pgrep $PROCESS_NAME)
        ps -p "$PID" >/dev/null 2>&1
       if [[ $? -ne 0 ]]; then
           echo "Process does not exist"
      else
            ps --pid $PID
       fi
       ;;
    *)   
        echo " Invalid Option "
       ;;
    esac
} 

# Function Provide detailed information about a specific process, including its PID, 
# parent process ID, user, CPU and memory usage.
function GetProcessInformation () {
     
   declare -i PID=$(pgrep $1)

   ps -p "$PID" >/dev/null 2>&1
       if [[ $? -ne 0 ]]; then
           echo "Process does not exist"
      else
            ps -o ppid,pid,user,pcpu,pmem,comm= -p $PID
       fi

}

# Function for real-time monitoring updating the display at regular intervals 
# to show the latest process information.
function RealTimeMonitoring () {

    top -d ${UPDATE_INTERVAL}
    
}

# Function Set up alerts for processes exceeding predefined resource usage thresholds.(in background)
function ResourceUsageAlerts () {

# Continuous monitoring loop
while true; do

    # Get CPU usage with process ID
    CPU_DATA=$(ps aux | awk '{print $2, $3}')
    CPU_USAGE=$(echo "$CPU_DATA" | awk '{print $2}' | sort -n | tail -1)
    CPU_PID=$(echo "$CPU_DATA" | awk '{print $1}' | sort -n | tail -1)

    # Get memory usage with process ID
    MEM_DATA=$(ps aux |  awk '{print $2, $4}')
    MEM_USAGE=$(echo "$MEM_DATA" | awk '{print $2}' | sort -n | tail -1)
    MEM_PID=$(echo "$MEM_DATA" | awk '{print $1}' | sort -n | tail -1)

    # Check thresholds
    if [[ $MEM_USAGE -ge $CPU_ALERT_THRESHOLD ]]; then
        echo "CPU usage exceeds threshold: $CPU_USAGE% by process ID $CPU_PID"
        
    fi

    if [[ $MEM_USAGE -ge $MEMORY_ALERT_THRESHOLD ]]; then
        echo "Memory usage exceeds threshold: $MEM_USAGE% by process ID $MEM_PID"
    fi

    # Sleep for a specified interval
    sleep 60
done &
}

# Function Display overall system process statistics, 
# such as the total number of processes, memory usage, and CPU load
function ProcessStatistics () {
    echo "********** Processes Statistics ***************"
    echo " Total Number of Processes "
    echo " $(ps aux | wc -l) "
    echo " "
    echo "********** CPU Statistics ***************" 
    echo "$(mpstat)"
    echo " "
     echo "********** Memory Usage ***************: "
     echo " $(free)"

}
############################### main Function ########################################################
function main () {

   declare PNAME
   declare -i PID

   while (true); do
   echo " "
   echo " ******** Process Monitoring Script ********* "
   echo " 1. List Running Processes "
   echo " 2. Get Process Information"
   echo " 3. Kill Process "
   echo " 4. Process Statistics "
   echo " 5. Real-time Monitoring "
   echo " 6. Search and Filter "
   echo " 7. Exit "
   
   read -p "Enter your option (1-7): " USER_OPTION

   case $USER_OPTION in
    1)
        ListRunningProcesses
        ;;
    2)
        read -p "Enter Process Name: " PNAME
        echo " "
        GetProcessInformation "$PNAME"
        ;;
    3)
        read -p "Enter Process ID: " PID
        echo " "
        KillProcess "$PID"
        ;;
    4)
        ProcessStatistics
        ;;
    5)
        RealTimeMonitoring  
        ;;
    6) 
          SearchFilter 
        ;;
    7)
       exit 1
       ;;

    *)
        echo "Invalid option"
        ;;
   esac
done

}
############################### Calling main ########################################################
 main
