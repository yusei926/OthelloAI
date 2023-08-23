#pragma once
#define NO_S3D_USING
#include <Siv3D.hpp>
#include "Board.h"
#include "BoardUtils.h"
#include "BoardVisualize.h"

namespace OthelloAI{

class PlayerAgent{
public:
    PlayerAgent(Color mycolor, std::shared_ptr<BoardVisualize> board_viz);
    //PlayerAgent(){}
    std::optional<Disk> getPlace(const Board & board);
    const Color & getColor() const{return mycolor_;}

private:
    Color mycolor_=Color::black;
    BoardUtils utils_;
    std::shared_ptr<BoardVisualize> viz_;
};

PlayerAgent::PlayerAgent(Color mycolor, std::shared_ptr<BoardVisualize> board_viz){
    mycolor_=mycolor;
    viz_=board_viz;
}

std::optional<Disk> PlayerAgent::getPlace(const Board & board){
    const auto point=viz_->getMouseSquare(); 
    if(point){
        const auto disk=OthelloAI::Disk(point.value(),mycolor_);
        if(utils_.isPlace(board,disk)){
            std::optional<Disk> disk_opt(disk);
            return disk_opt;
        }
    }
    return std::nullopt;
}

}