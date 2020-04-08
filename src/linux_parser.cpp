#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
string::size_type sz;
long systemAvailableMemory = 0;
bool availbaleMemeoryNotRead = true;
int LinuxParser::convertToInt(const string &inputString) {
  int returnValue{0};
  try { returnValue = std::stoi (inputString, &sz);} catch (...) {}
  return returnValue;
}

long LinuxParser::convertToLong(const string &inputString) {
  int returnValue{0};
  try { returnValue = std::stol (inputString, &sz);} catch (...) {}
  return returnValue;
}

string LinuxParser::getLineForKey(string path, string inputKey) {
  string line;
  string key, value;
  std::ifstream inputFile(path);
  if (inputFile.is_open()) {
    while (std::getline(inputFile, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == inputKey) {
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::getLineForKey(string path, string inputKey, int i) {
  string line;
  string key, value;
  std::ifstream inputFile(path);
  if (inputFile.is_open() && i==1) {
    while (std::getline(inputFile, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == inputKey) {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  return getLineForKey(kOSPath, "PRETTY_NAME", 1);
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  if (availbaleMemeoryNotRead) {
    availbaleMemeoryNotRead = false;
    string totalMemory_s = getLineForKey(kProcDirectory + kMeminfoFilename, "MemTotal:");
    systemAvailableMemory = convertToLong(totalMemory_s);
  }
  string activeMemory_s = getLineForKey(kProcDirectory + kMeminfoFilename, "MemFree:");
  long availableMemory = convertToLong(activeMemory_s);
  
  string bufferMemory_s = getLineForKey(kProcDirectory + kMeminfoFilename, "Buffers:");
  long bufferMemory = convertToLong(bufferMemory_s);
  
  string CachedMemory_s = getLineForKey(kProcDirectory + kMeminfoFilename, "Cached:");
  long CachedMemory = convertToLong(CachedMemory_s);
  
  string SReclaimableMemory_s = getLineForKey(kProcDirectory + kMeminfoFilename, "SReclaimable:");
  long SReclaimableMemory = convertToLong(SReclaimableMemory_s);
  
  string ShmemMemory_s = getLineForKey(kProcDirectory + kMeminfoFilename, "Shmem:");
  long ShmemMemory = convertToLong(ShmemMemory_s);
  
  if (systemAvailableMemory==0) return 100.00;
  long totalMemory = systemAvailableMemory - availableMemory;
  long cachedmemory = CachedMemory + SReclaimableMemory - ShmemMemory; 
  long numerator = totalMemory - (bufferMemory   + cachedmemory);
  float returnvalue = (float) numerator/(float)systemAvailableMemory;
  return returnvalue;
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, timeItIsRunning{"0"};
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> timeItIsRunning;
  }
  return convertToLong(timeItIsRunning);
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string numberOfProcesses_ = getLineForKey(kProcDirectory + kStatFilename, "processes");
  return convertToInt(numberOfProcesses_);
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {  
  string procs_running_ = getLineForKey(kProcDirectory + kStatFilename, "procs_running");
  return convertToInt(procs_running_);
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }