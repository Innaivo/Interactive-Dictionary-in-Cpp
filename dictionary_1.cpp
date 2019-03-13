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


int main ()
  {
    dataStream.open("dictionary.json");
    read_json (dataStream, pt); // take data from stream and write down into pt;

    cout << "Enter the word to retrieve the definition \n";

    string word_user;
    /* cin itself takes only 1 word
     * if >1 word is given; therefore, use getline */
    getline (cin, word_user);

    vector<string> defVect = retrieve_definition(word_user);
    for (string sepDef : defVect)
    {
      cout << sepDef << '\n';
    }
  }
