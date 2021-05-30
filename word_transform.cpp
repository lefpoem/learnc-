/*A program to transform words
 *Takes two arguments : The first is name of word transform file
 *The second is name of the input to transform
 */
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
ifstream& open_file(ifstream& in,const string& file);
int main(int argc,char **argv)
{
    //map to hold the word transformation pairs:
    //key is the word to look for in the input;value is word to use in the output
    map<string,string> trans_map;
    string key,value;
    if(argc!=3)
       throw runtime_error("wrong number of arguments");
    //open transformation file and  check that open succeeded
    ifstream map_file("m.text");
    if(!open_file(map_file,argv[1]))
       throw runtime_error("no transformation file");
    //read the transformation map and build the map
    while (map_file >> key >> value)
    {
        trans_map.insert(make_pair(key,value));/* ok,now we're ready to do the trans
        *-formations ,open the input file and check that the open succeeded */
    }
    ifstream input;  
    if(!open_file(input,argv[2])) 
      throw runtime_error("no input file");
    string line; // hold each line from the input
    //read the text to transform it a line at a time
    while(getline(input,line)){
        istringstream stream(line);
        string word;
        bool firstword = true;//controls whether a space is
        while(stream >> word)
        {
            //ok:the actual mapwork,this part is the herat of the program
            map<string,string>::const_iterator map_it = 
                trans_map.find(word);
            //if this word is in the transformation map
            if(map_it!=trans_map.end())
            //repalce it by the transformation value in the map
              word = map_it->second;
            if(firstword)
               firstword = false;
            else
               cout << " "; //print space between words
            cout << word;
        }
        cout << endl;//done with this line of input
    }
    return 0;
}
ifstream& open_file(ifstream& in,const string& file)
{
    in.close();
    in.clear();
    in.open(file.c_str());
    return in;
}