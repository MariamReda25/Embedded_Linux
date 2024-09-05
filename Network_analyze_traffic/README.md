x# 🚀 Network Analyzer Traffic

## 📌 Objective:

The primary objective of this network task is to analyze network traffic using Wireshark and automate specific tasks with a Bash script, 

generating a summary report.

## 🔍 Scope :
 
    1.Capture network traffic using Wireshark.
    
    2.Develop a Bash script to analyze the captured data.
    
    3.Extract relevant information like total packets, protocols, and top source/destination IP addresses.
    
    4.Generate a summary report based on the analysis.
    
## 🐋 Wireshark Capture

    1.Start Wireshark and capture network traffic.
    
    2.Save the captured data in a pcap file (e.g., your_capture_file.pcap).

## ⚙️ Configuration File :

 used to configure :
 
  1. Protocols
  2. IP_Addresses
  3. Number Of Top ip Addresses

## ⌨️ Run Script:
```
. chmod +x ./analyze_traffic.sh
. ./analyze_traffic.sh {capture_file.pcap}
```

