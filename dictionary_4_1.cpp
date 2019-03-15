#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "similarity.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using namespace std;

std::ifstream dataStream; 
ptree pt;


int main ()
  {
     const char* a = "rain";
     const char* b = "rainn";
     int similResult = simil (a, b);
    cout << similResult << endl;
  }
