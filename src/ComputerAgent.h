#pragma once
#include <optional>

#include "Board.h"
#include "BoardUtils.h"
#include "Tree.h"
#include "MonteCarlo.h"

namespace OthelloAI{

class ComputerAgent{
public:
    ComputerAgent(Color mycolor);
    //ComputerAgent(){}
    std::optional<Disk> getPlace(const Board & board);
    const Color & getColor() const{return mycolor_;}

private:
    Color mycolor_=Color::black;
    BoardUtils utils_;
    std::shared_ptr<Tree> root_;
};

ComputerAgent::ComputerAgent(Color mycolor):root_(std::make_shared<Tree>()){
    mycolor_=mycolor;
}

std::optional<Disk> ComputerAgent::getPlace(const Board & board){
    root_->board_=board;
    root_->children_.clear();
    auto enable_places=utils_.getEnablePlaces(board,mycolor_);
    //置く場所の候補
    for(const auto & place : enable_places){
        Board next_board=board;
        utils_.place(next_board,place);
        root_->children_.emplace_back(std::make_shared<Tree>());
        root_->children_.back()->board_=next_board;
        root_->children_.back()->parent_=root_;
        root_->children_.back()->disk_=place;
        for(int i=0; i<3000; ++i){
            if(utils_.randomPlay(next_board,!mycolor_)==mycolor_){
                root_->children_.back()->count_++;
            }
        }
    }
    int max_index=0;
    int max_val=0;
    int index=0;
    for(const auto & child : root_->children_){
        if(child->count_>max_val){
            max_val=child->count_;
            max_index=index;
        }
        ++index;
    }
    return root_->children_[max_index]->disk_;
    return std::nullopt;
}

}
