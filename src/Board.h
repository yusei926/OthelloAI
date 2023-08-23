#pragma once
#include<vector>
#include "Disk.h"
namespace OthelloAI{

class Board{
    private:
    static const int board_size_=8;
    public:
    Board(int size=board_size_):board_(size, std::vector<int8_t>(size, 0)){};

    void setDisk(Disk disk){board_[disk.point_.x_][disk.point_.y_]=disk.color_.color_;}
    void setDisk(int x, int y, int8_t color){setDisk(Disk(x,y,color));}
    void setDisk(Point point, int8_t color){setDisk(point.x_, point.y_,color);}
    const Disk getDisk(const Point & point)const{return Disk(point.x_,point.y_,board_[point.x_][point.y_]);}
    const Color getColor(const Point & point)const{return Color(board_[point.x_][point.y_]);}
    void setDefaultDisk(){
        board_.assign(board_size_, std::vector<int8_t>(board_size_,0));
        setDisk(3,3,Color::white);
        setDisk(3,4,Color::black);
        setDisk(4,3,Color::black);
        setDisk(4,4,Color::white);
    }

    void setBoard(std::vector<std::vector<int8_t> > board){board_=board;}
    const std::vector<std::vector<int8_t> > & getBoard() const{return board_;}

    private:
     std::vector<std::vector<int8_t> > board_;

};

}// namespace OthelloAI