#include "utility.hpp"
#ifndef PARSER_HPP
#define PARSER_HPP

struct DataFrame {
    int influencer_id, follower_id, influencer_active_start, follower_active_start;
    string influencer_main_genre, follower_main_genre;
    DataFrame(vector<string>& _strVec) {
        if(_strVec.size() != 6) std::cerr << "Construct_DataFrame_Error";
        influencer_id = std::stoi(_strVec[0]);
        influencer_main_genre = _strVec[1];
        influencer_active_start = std::stoi(_strVec[2]);
        follower_id = std::stoi(_strVec[3]);
        follower_main_genre = _strVec[4];
        follower_active_start = std::stoi(_strVec[5]);
    }
};

class Parser{
    string root, filename;
public:
    Parser(string _root, string _filename): root(_root), filename(_filename) {}
    vector<DataFrame> parse() {
        std::ifstream inFile(root + filename, std::ios::in);
	    string lineStr;
	    vector<DataFrame> df;

	    getline(inFile, lineStr); // Read in the csv's headline
	    while(getline(inFile, lineStr)) {
		    // 存成二维表结构
		    std::stringstream ss(lineStr);
		    string str;
		    vector<string> lineArray;
		    // 按照逗号分隔
		    while(getline(ss, str, ',')) {
			    lineArray.push_back(str);
            }
		    df.push_back(DataFrame(lineArray));
        }
    
        return df;
    }

};

#endif