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

vector<string> retrieve_definition(string wordIn)
  { vector<string> wordDef;
    for (auto& item: pt.get_child(wordIn))
    {
      wordDef.push_back(item.second.get_value(""));
    }
    return wordDef;
  }

vector<string> check_conditions(string wordIn)
  { vector<string> wordDef = {};
  /*removing case-sensitivity from the program, by converting all
   * letters to lower, using transform from std library:*/
    transform(wordIn.begin(),
              wordIn.end(), wordIn.begin(), ::tolower);
    // Check for non-existing words:
    if (pt.find(wordIn) != pt.not_found())
     {
       wordDef = retrieve_definition(wordIn);
     }
    else
     {// Return the definition of words that start with Capital letter;
      wordIn[0] = toupper(wordIn[0]);
      if (pt.find(wordIn) != pt.not_found())
      {
       wordDef = retrieve_definition(wordIn);
      }
      else
      {// Return the definition of ACHRONYMS (e.g.NATO);
       transform(wordIn.begin(), wordIn.end(), wordIn.begin(), ::toupper);
       if (pt.find(wordIn) != pt.not_found())
        {
          wordDef = retrieve_definition(wordIn);
        }
      }// if def. for Titel wordIn is not found;
     } // if def. for lowcups wordIn is not found;
     return wordDef;
  }


int main ()
  { string word_user;
    dataStream.open("dictionary.json");
    read_json (dataStream, pt); // take data from stream and write down into pt;
    // ask user to enter the word:
    cout << "Enter the word to retrieve the definition \n";
    getline (cin, word_user); // cin itself takes only 1 word
    // if >1 word is given; therefore -> use getline;

    // check conditions + retrieve definition:
    vector<string> defVect = check_conditions(word_user);
    /* Check if defVect is an empty vector:*/
    if (defVect.empty())
    {/* find a similar word from dictionary: */
     // transform word_user to lower:
     transform(word_user.begin(), word_user.end(), word_user.begin(), ::tolower);
      /* form vector of strings from ptree object (keys of .json dictionary):*/
     vector <string> keysVect;
     for (auto it: pt)
      {
        keysVect.push_back(it.first);
      }
     vector <string> matchWordpair = get_close_matches (word_user,
                                keysVect, 1, 80);
     if (matchWordpair.size() != 0)
      {
        cout<< "Did you mean "<< matchWordpair[0]<<" instead? [y or n]";
      }
    }

    for (string sepDef : defVect)
    {
      cout << sepDef << '\n';
    }
  }
