#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cpustats.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 Cpustats previousCpuStats;
};

#endif