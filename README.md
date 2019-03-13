# Interactive-Dictionary-in-C-
This repository is a translation of Interactive Dictionary in Python to C++. Sourse codes in Python and data in .json formats are available at https://github.com/Dhrumilcse/Interactive-Dictionary-in-Python .

This dictionary retrieves definition of the word, entered by user. If the user has made a type, it suggest the closest match.

## Installing dependencies

The following dependencies are used to parse data in .json format:

```C++
#include <fstream>
#include <vector>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
```
## Step by step solution
```C++
dictionary_1.cpp
```
> Load the data. Created function ```retrieve_definition``` that returns vector of definitions, given the word, entered by user (key). 

