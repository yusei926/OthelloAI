#pragma once
#include <optional>

#include "Board.h"
#include "BoardUtils.h"

namespace OthelloAI{

class MonteCarlo{
public:
    MonteCarlo(int search_cou);
    void setSearchCount(int search_cou){search_cou_=search_cou;}
    Disk getBestPlace(const Board & board, const Color & mycolor, std::vector<double> & eval_array);
    Disk getBestPlace(const Board & board, const Color & mycolor);
private:
    int search_cou_=5000;
    BoardUtils utils_;

};

MonteCarlo::MonteCarlo(int search_cou){
    setSearchCount(search_cou);
}

Disk MonteCarlo::getBestPlace(const Board & board, const Color & mycolor, std::vector<double> & eval_array){
    auto enable_places=utils_.getEnablePlaces(board,mycolor);
    eval_array.clear();
    for(const auto & place : enable_places){
        Board next_board=board;
        utils_.place(next_board,place);
        int win_cou=0;
        for(int i=0; i<search_cou_; ++i){
            if(utils_.randomPlay(next_board,!mycolor)==mycolor){
                win_cou++;
            }
        }
        eval_array.emplace_back(win_cou/search_cou_);
    }

    int max_index=0;
    double max_val=0;
    int index=0;
    for(const auto & eval : eval_array){
        if(eval>max_val){
            max_val=eval;
            max_index=index;
        }
        ++index;
    }
    return enable_places[max_index];
}

Disk MonteCarlo::getBestPlace(const Board & board, const Color & mycolor){
    std::vector<double> eval_array;
    return getBestPlace(board, mycolor, eval_array);
}

}
