#ifndef CPUSTATS_H
#define CPUSTATS_H

#include <string>
#include <vector>

class Cpustats {
 private:
  public:
  Cpustats();
  Cpustats(std::string);
  void copyFromOther(const Cpustats &otherObject);
  long kUser = 0,
  kNice=0,
  kSystem=0,
  kIdle=0,
  kIOwait=0,
  kIRQ,
  kSoftIRQ=0,
  kSteal=0,
  kGuest=0,
  kGuestNice=0;
};

#endif