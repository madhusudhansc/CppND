#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
std::string appendZeroes (long input, int length){
  std:string input_s = std::to_string(input);
  return std::string(length - input_s.length(), '0') + input_s;
  };
std::string appendZeroes (int input, int length){
  std:string input_s = std::to_string(input);
  return std::string(length - input_s.length(), '0') + input_s;
  };
std::string Format::ElapsedTime(long seconds) { 
    std::string elapsedTime;
    //First convert to Hour
    int hh = (seconds/3600);
    //save remaining seconds
    seconds%=3600;

    //Now get minutes
    int mm = seconds/60;
    seconds%=60;
    return appendZeroes(hh, 2) + ":" + appendZeroes(mm,2) + ":" + appendZeroes(seconds, 2);
  }