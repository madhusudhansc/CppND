#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "cpustats.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Cpustats::Cpustats(string cpustatsLine) {
   vector<long> cpustats {};
   string somestats;
   std::istringstream cpustatsstream(cpustatsLine);
   cpustatsstream >> somestats;
   while(cpustatsstream >> somestats) {
     cpustats.push_back(LinuxParser::convertToLong(somestats));
   }

   if (cpustats.size() == 10) {
      kUser = cpustats[0];
      kNice=cpustats[1];
      kSystem=cpustats[2];
      kIdle=cpustats[3];
      kIOwait=cpustats[4];
      kIRQ=cpustats[5];
      kSoftIRQ=cpustats[6];
      kSteal=cpustats[7];
      kGuest=cpustats[8];
      kGuestNice=cpustats[9];
   }

}

void Cpustats::copyFromOther(const Cpustats &otherObejct) {
    *this = otherObejct;
}