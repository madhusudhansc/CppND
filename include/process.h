#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() const;                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() ;                  // TODO: See src/process.cpp                   // TODO: See src/process.cpp
  float CpuUtilization(int) ;
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator>(Process const& a) const;  // TODO: See src/process.cpp
  Process(){};
  Process(int id):pid_(id){};

  // TODO: Declare any necessary private members
 private:
 int pid_{0};
 long uptime_{0};
 float cpuutilization_{0.00};
};

#endif