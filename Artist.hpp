#include "utility.hpp"
#ifndef ARTIST_HPP
#define ARTIST_HPP

// e^-1 = 0.3679

class Artist {
    int id, active_start_;
    string genre_;
    vector<Artist*> follower, influencer;
    int _activate() const { return follower.size(); }
public:
    Artist() = default;
    Artist(int _id, string _genre, int _start): id(_id), genre_(_genre), active_start_(_start) {}
    void operator=(const Artist& _other) {
        this->id = _other.id;
        this->active_start_ = _other.active_start_;
        this->follower = _other.follower;
        this->influencer = _other.influencer;
    }

    // mask values
    string genre() const { return genre_; }
    int active_start() const { return active_start_; }

    void add_son(Artist& _follower) {
        follower.emplace_back(&_follower);
    }
    void add_fa(Artist& _influencer) {
        influencer.emplace_back(&_influencer);
    }

    double activate() const {
        int second_influence = 0;
        int third_influence = 0;
        for(auto& iter : follower) {
            second_influence += iter->_activate();
            for(auto& ii : iter->influencer) {
                third_influence += ii->_activate();
            }
        }
        return this->_activate() + std::exp(-1) * second_influence + std::exp(-2) * third_influence;
    }

    std::pair<int,std::pair<int,int>> crossEdge(string str) {
        int in = 0, out_inf = 0, out_flw = 0; 
        if(this->genre_ == str) {
            for(auto& iter : follower) {
                if(iter->genre_ == this->genre_)    
                    ++in;
                else
                    ++out_inf;    
            }
        }
        else {
            for(auto& iter : follower) {
                if(iter->genre_ == str) ++out_flw;  
            }
        }
        return std::make_pair(in, std::make_pair(out_flw, out_inf));
    }
    
    friend std::ostream& operator<<(std::ostream &output, const Artist& _A){ 
        output << "artist_id  " << _A.id << std::endl
            << "artist_main_genre  " << _A.genre_ << std::endl
            << "artist_active_start  " << _A.active_start_;
        return output;            
    }

};

#endif