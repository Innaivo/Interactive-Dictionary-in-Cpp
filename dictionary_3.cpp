#include <iostream>
#include <fstream>
#include <vector>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using namespace std;

std::ifstream dataStream;
ptree pt;

vector<string> retrieve_definition(string wordIn)
  { vector<string> wordDef;
    for (auto &item: pt.get_child(wordIn))
    {
      wordDef.push_back(item.second.get_value(""));
    }
    return wordDef;
  }

vector<string> check_conditions(string wordIn)
  { vector<string> wordDef = {};

    /*removing case-sensitivity from the program, by converting all
     * letters to lower, using transform is from std library:*/
    transform(wordIn.begin(), //
    wordIn.end(), wordIn.begin(), ::tolower);
    // Check for non-existing words:
    if (pt.find(wordIn) != pt.not_found())
    {
      wordDef = retrieve_definition(wordIn);
    }
    else
    {// Return the definition of words that start with Capital letter:
      wordIn[0] = toupper(wordIn[0]);
      if (pt.find(wordIn) != pt.not_found())
      {
        wordDef = retrieve_definition(wordIn);
      }
      else
      {// Return the definition of ACHRONYMS (e.g.NATO):
        transform(wordIn.begin(), wordIn.end(), wordIn.begin(), ::toupper);
        if (pt.find(wordIn) != pt.not_found())
        {
          wordDef = retrieve_definition(wordIn);
        }
        else
        {
          wordDef = {"The word doesn't exist, please double check it."};
        }
      }// if def. for Titel wordIn is not found;
    } // if def. for lowcups wordIn is not found;
    return wordDef;
  }


int main ()
  {
    string word_user;
    dataStream.open("dictionary.json");
    read_json (dataStream, pt); // take data from stream and write down into pt;

    // ask user to enter the word:
    cout << "Enter the word to retrieve the definition \n";
    /* cin itself takes only 1 word
     * if >1 word is given; therefore -> use getline */
    getline (cin, word_user);

    // check conditions + retrieve definition:
    vector<string> defVect = check_conditions(word_user);
    for (string sepDef : defVect)
    {
      cout << sepDef << '\n';
    }
  }
