#include "Artist.hpp"
#include "utility.hpp"
#include "Parser.hpp"

    vector<Artist> musician_list;
    map<int,Artist> musician_map;

std::pair<int,std::pair<int,int>> influence(string _name) 
{
    int i1 = 0, i2 = 0, i3 = 0;
    for(auto& iter : musician_map) {
        auto tmp = iter.second.crossEdge(_name);
        i1 += tmp.first;
        i2 += tmp.second.first;
        i3 += tmp.second.second;
    }
    return std::make_pair(i1, std::make_pair(i2, i3));
}

int main()
{
    Parser parser =  Parser(string("E:\\Dataset\\MCM\\2021_ICM_Problem_D_Data"), string("\\influence_data.csv"));
    vector<DataFrame> df = parser.parse();

    for(auto& iter : df) {
        int id_1 = iter.influencer_id, id_2 = iter.follower_id;
        Artist influencer, follower;
        if(musician_map.find(id_1) == musician_map.end()) {
            Artist tmpArtist = Artist(iter.influencer_id, iter.influencer_main_genre, iter.influencer_active_start);
            musician_list.emplace_back(tmpArtist);
            musician_map.insert(std::pair<int,Artist>(id_1, tmpArtist));
        }
        if(musician_map.find(id_2) == musician_map.end()) {
            Artist tmpArtist = Artist(iter.follower_id, iter.follower_main_genre, iter.follower_active_start);
            musician_list.emplace_back(tmpArtist);
            musician_map.insert(std::pair<int,Artist>(id_2, tmpArtist));
        }
        
        musician_map.find(id_1)->second.add_son(musician_map.find(id_2)->second);
        musician_map.find(id_2)->second.add_fa(musician_map.find(id_1)->second);

    }

    string str;

    // output
    std::ofstream outFile;
	outFile.open("E:\\Dataset\\MCM\\2021_ICM_Problem_D_Data\\InfluenceData4.csv", std::ios::out); // 打开模式可省略
    //outFile << str << ',' << tmp.first << ',' << tmp.second << ',' << double(tmp.first) / tmp.second << std::endl;
    
    while(true) {
        std::cout << "Input genre name ";
        std::cin >> str;
        if(str == "EOF")    break;
        auto tmp = influence(str);
        outFile << str << ',' << tmp.first << ',' << tmp.second.first << ',' << tmp.second.second << std::endl;
    }

}