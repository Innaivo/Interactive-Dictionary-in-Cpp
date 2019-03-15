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

vector <string> get_close_matches (string wordIn,
                        vector <string> list_words, int n = 1, double threshold = 75)
/* First parameter is the word for which we want to find close matches
 * Second is a list of words against which to match the word
 *[optional]Third is maximum number of close matches
 *[optional]Fourth is matching threshold
*/
       { vector<pair<int, string>> matchWords;

         const char* b = wordIn.c_str(); // convert string to const char
         for (string dictWord: list_words)
         { const char* a = dictWord.c_str();
           int simRat = simil (a, b);
           if (simRat >= threshold)
            matchWords.push_back(make_pair(simRat, dictWord));
         }
         /* sort vector of pairs in ascending order, based on first element:*/
         sort(matchWords.begin(), matchWords.end());
         vector <string> resultWords;
         int sw = matchWords.size();
         for (int i=1; i< n+1; i++)
         {  // return last 'n' words:
            resultWords.push_back(matchWords[sw-i].second);
         }
         return resultWords;
       }

int main ()
  { string wordIn = "rain";
    vector <string> list_words = {"mate","help","rainy", "rainn"};
    vector <string> matchWordpair = get_close_matches (wordIn,
                            list_words, 1, 80);
    for (const auto& x: matchWordpair)
    {
      cout << x << endl;
    }
  }
