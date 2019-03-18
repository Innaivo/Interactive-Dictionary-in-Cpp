# Interactive-Dictionary-in-C-
This repository is a translation of Interactive Dictionary in Python to C++. Sourse codes in Python and data in .json format are available at https://github.com/Dhrumilcse/Interactive-Dictionary-in-Python .

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
> Load the data. Created function ```retrieve_definition``` that returns vector of definitions, given the word, entered by user (key). Display all the definitions by iterating over vector. 

```c++
dictionary_2.cpp
```
> Check for non-existing words: updated function ```retrieve_definition```.

```c++
dictionary_3.cpp
```
> Removing case sensitivity from the program and ensuring that program returns definition for words that start with capital letter and achronyms. Created function ```check_conditions``` that encapsulates all the checks. 

```c++
dictionary_4_1.cpp
```
> Added function ```similarity.c``` (sourse: https://github.com/wernsey/miscsrc/blob/master/simil.c) that returns returns a value between 0 and 100 which indicates how alike two strings are; based on the Ratcliff-Obershelp algorithm.

```c++
dictionary_4_2.cpp
```
> Created function ```get_close_matches``` that returns list of close matches.  

```c++
dictionary_5.cpp
```
> Use function ```get_close_matches``` to suggest the closest match.

```c++
dictionary_6.cpp
```

> If suggested word is what user wants, retrieve meaning of it. 
