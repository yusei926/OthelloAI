#pragma once
#include "Board.h"
#include <memory>
#include <vector>

namespace OthelloAI{

class Tree{
public:
    Board board_;
    Disk disk_;
    int count_=0;
    double score_=0.0;
    std::shared_ptr<Tree> parent_;
    std::vector<std::shared_ptr<Tree> > children_;
};

}// namespace OthelloAI