#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  std::string line;
  std::ifstream stream(LinuxParser::kProcDirectory + "/" + Pid() + "/" + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  } else {
      return 0.00;
  }
  //Convert long line of string to vector of strings.
  std::stringstream linestream(line);
  std::istream_iterator<std::string> begin(linestream);
  std::istream_iterator<std::string> end;
  std::vector<std::string> statsParts(begin, end);
  //Now line has full content 
  if (statsParts.size() != 52) {return 0.00;} //We should get 52 stats from /proc/[pid]/stat file
  long systemUptime = LinuxParser::UpTime();
  long hertz = sysconf(_SC_CLK_TCK);
  if (hertz==0) return 0.0;
  long utime = LinuxParser::convertToLong(statsParts[13]);
  long stime = LinuxParser::convertToLong(statsParts[14]);
  long cutime = LinuxParser::convertToLong(statsParts[15]);
  long cstime = LinuxParser::convertToLong(statsParts[16]);
  long starttime = LinuxParser::convertToLong(statsParts[21]);

  long total_time = utime + stime + cutime + cstime;
  float seconds = (float) systemUptime - ((float) starttime/(float) hertz);
  float tbyh = (float) total_time / (float) hertz ;
  if (seconds==0) return 0.0;
  
  return 100.00 * tbyh/seconds; 
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }