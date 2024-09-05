#!/usr/bin/bash
############################ Script Description #########################################
#                     *Bash Script to Analyze Network Traffic*             
# 1. Objective :
# This Script used to analyze network traffic using Wireshark and automate specific tasks
# with Bash script , generating a summary report.

# 2. Scope :
# 1.Capture network traffic using Wireshark.(in pcap file)
# 2.Take file path as input (From Terminal) Then Analyze the captured data which saved in file.
# 3.Extract relevant information like total packets, protocols, and top source/destination IP addresses.
# 4.Generate a summary report based on the analysis.
#
# Author : Mariam Reda Ibrahim
#
############################ Global Variables & Function decleration ###########################
# - Variables: 

LOG_FILE="log.txt"

# Configuration File :  
CONFIG_FILE="Network_analyze.conf"

   if [[ -f "$CONFIG_FILE" ]]; then
      source "${CONFIG_FILE}"
   else
      Print "Log[ERROR]: Configuration File Not Exist" > ${LOG_FILE}
      exit 1
   fi 

# Input: Path to the Wireshark pcap file
pcap_file=$1 

# File used to save extracted IP Addresses
FILE_IP="ip_packets.txt"

# - Functions :

# Function Used To Print Messages 
function Print () {
   echo $1
}

# Function Check existance of pcap File
function Check_file_existance () {

   if [[ ! -f ${pcap_file} ]]; then 
      Print "Log[ERROR]: Input .pcap File not exists" > ${LOG_FILE}
      exit 1;
   fi
}

# Function Used to Extract Packets From .pcap File
function Extract_Packets () {

   declare -i total_packets=$(tshark -r ${pcap_file} | wc -l)
   Print "- Total Packets: $total_packets"

   Print "- Protocols:"

   for element in "${PROTOCOL_PACKETS[@]}"; do
      declare -i PACKETS=$(tshark -r capture.pcap -Y $element | wc -l)
      Print "-${element}:  ${PACKETS}  Packets"
   done

   Print ""
}

# Function Used to Count  Required (src/dst) IP_Addresses
function Extract_IP_Addresses() {
    
   for element in "${IP_ADDRESSES[@]}"; do
      Print " - Top ${TOP_COUNT_IP} of ${element} IP Addresses:"
      tshark -r ${pcap_file} -T fields -e ip.${element} > ${FILE_IP}
      awk '{ count[$1]++; } END { for (ip in count) { printf "%d :  %s\n", count[ip], ip; } }' ${FILE_IP} | sort -r -n | head -n ${TOP_COUNT_IP}
      Print " "
   done

}

# Function to Analyze information from the pcap file
function analyze_traffic() {

   Print "----- Network Traffic Analysis Report -----"

  # Extract Packets of Protocols 
   Extract_Packets

  # Extract Top IP_Addresses
   Extract_IP_Addresses
    
   Print "----- End of Report -----"
}
############################ main Function #########################################################
function main () {

 # Check existance of pcap file before start analyizing
  Check_file_existance

 # Run the analysis function
 analyze_traffic

}
############################ Calling main ##########################################################
 main




