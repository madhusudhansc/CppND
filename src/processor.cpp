#include<string>
#include "processor.h"
#include "linux_parser.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::ifstream os, version, kernel;
  std::string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  Cpustats presentCpuStats(line);
  //Logic from https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  long PrevIdle = previousCpuStats.kIdle + previousCpuStats.kIOwait;
  long currIdle = presentCpuStats.kIdle + presentCpuStats.kIOwait;
  long PrevNonIdle = previousCpuStats.kUser + previousCpuStats.kNice + previousCpuStats.kSystem
   + previousCpuStats.kIRQ + previousCpuStats.kSoftIRQ + previousCpuStats.kSteal;
  long NonIdle = presentCpuStats.kUser + presentCpuStats.kNice + presentCpuStats.kSystem
   + presentCpuStats.kIRQ + presentCpuStats.kSoftIRQ + presentCpuStats.kSteal;
  
  previousCpuStats.copyFromOther(presentCpuStats);
  long PrevTotal = PrevIdle + PrevNonIdle;
  long currTotal = currIdle + PrevIdle;
  long totald = currTotal - PrevTotal;
  long idled = currIdle - PrevIdle;

  if (totald==0) return 100.00;

  float CPU_Percentage = (float) (totald - idled)/ (float) totald;
  return CPU_Percentage; 
}