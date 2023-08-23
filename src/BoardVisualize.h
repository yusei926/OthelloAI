#pragma once
#define NO_S3D_USING
#include <Siv3D.hpp>
#include "Board.h"
#include "BoardUtils.h"

namespace OthelloAI{

class BoardVisualize{
public:
    BoardVisualize(int x, int y, int size);
    void setup(int x, int y, int size);
    void resize();
    void draw(const Board & board);
    void drawEnablePlaces(const std::vector<Disk> & places);
    void drawInfo(const Board & board, const Color & now_color);
    void drawResult(const Board & board);
    const std::optional<Point> getMouseSquare() const;
private:
    int x_;
    int y_;
    int size_;
    double square_ratio_=0.95;
    double disk_ratio_=0.9;
    const int board_size_=8;
    const double board_window_offset_=0.05;
    std::vector<std::vector<s3d::Circle> > disks_;
    BoardUtils utils_;
};

void BoardVisualize::setup(int x, int y, int size){
    x_=x;
    y_=y;
    size_=size/board_size_;
    for(int x=0;x<board_size_;x++){
        for(int y=0;y<board_size_;y++){
            disks_[x][y].set( x_+int(0.5*size_)+x*size_, y_+int(0.5*size_)+y*size_, int(0.5*size_*square_ratio_));
        }
    }
}

void BoardVisualize::resize(){
    int x,y,size;
    if(s3d::Scene::Size().x>s3d::Scene::Size().y){
        x=s3d::Scene::Size().x*0.5-s3d::Scene::Size().y*(0.5-board_window_offset_);
        y=s3d::Scene::Size().y*board_window_offset_;
        size=s3d::Scene::Size().y*(1.0-2.0*board_window_offset_);
    }
    else{
        y=s3d::Scene::Size().y*0.5-s3d::Scene::Size().x*(0.5-board_window_offset_);
        x=s3d::Scene::Size().x*board_window_offset_;
        size=s3d::Scene::Size().x*(1.0-2.0*board_window_offset_);
    }
    setup(x,y,size);
}

 BoardVisualize::BoardVisualize(int x, int y, int size)
    :disks_(board_size_, std::vector<s3d::Circle>(board_size_)){
    setup(x,y,size);
 }

void BoardVisualize::draw(const Board & board){
    s3d::Rect{x_,y_,size_*board_size_}.draw(s3d::Palette::Black);
    for(int x=0;x<board.getBoard().size();x++){
        for(int y=0;y<board.getBoard().size();y++){
            s3d::Rect{ x_+int((1-square_ratio_)*0.5*size_)+x*size_, y_+int((1-square_ratio_)*0.5*size_)+y*size_, int(size_*square_ratio_)}.draw(s3d::Palette::Green);
            auto disk_color=s3d::Palette::Green;
            if(board.getBoard()[x][y]==OthelloAI::Color::black){
                disk_color=s3d::Palette::Black;
            }
            if(board.getBoard()[x][y]==OthelloAI::Color::white){
                disk_color=s3d::Palette::White;
            }
            disks_[x][y].draw(disk_color);
        }
    }
}

const std::optional<Point> BoardVisualize::getMouseSquare() const{
    for(int x=0;x<board_size_;x++){
        for(int y=0;y<board_size_;y++){
            if(disks_[x][y].leftClicked()){
                std::optional<Point> point=Point(x,y);
                return point;
            }
        }
    }
    return std::nullopt;
}

void BoardVisualize::drawEnablePlaces(const std::vector<Disk> & places){
    for(const auto & place : places){
        auto disk_color=s3d::Palette::Green;
        if(place.color_==OthelloAI::Color::black){
            disk_color=s3d::Palette::Black;
        }
        if(place.color_==OthelloAI::Color::white){
            disk_color=s3d::Palette::White;
        }
        s3d::Circle{x_+int(0.5*size_)+place.point_.x_*size_, y_+int(0.5*size_)+place.point_.y_*size_, int(0.5*size_*square_ratio_/4.0)}.draw(disk_color);
    }
}

void BoardVisualize::drawInfo(const Board & board, const Color & now_color){
    //s3d::Rect{x_+size_*board_size_,y_+size_*0,size_*3,size_*2}.draw(s3d::Palette::Green);
    static const double disp_ratio=0.7;
    static const s3d::Font font{ s3d::FontMethod::MSDF, size_};
    int white_cou=utils_.count(board,OthelloAI::Color::white);
    int black_cou=utils_.count(board,OthelloAI::Color::black);
    if(s3d::Scene::Size().x>s3d::Scene::Size().y){  
        s3d::Circle{x_+size_*board_size_+size_*0.5,y_+size_*0.5,int(0.5*size_*square_ratio_*disp_ratio)}.draw(s3d::Palette::White);
        s3d::Circle{x_+size_*board_size_+size_*0.5,y_+size_*1.5,int(0.5*size_*square_ratio_*disp_ratio)}.draw(s3d::Palette::Black);
        font(white_cou).drawAt(double(size_)*disp_ratio,x_+size_*board_size_+size_*1.5,y_+size_*0.5, s3d::Palette::Black);
        font(black_cou).drawAt(double(size_)*disp_ratio,x_+size_*board_size_+size_*1.5,y_+size_*1.5, s3d::Palette::Black);
    }
    else{
        s3d::Circle{x_+size_*0.5,y_-size_*0.5,int(0.5*size_*square_ratio_*disp_ratio)}.draw(s3d::Palette::White);
        s3d::Circle{x_+size_*6.5,y_-size_*0.5,int(0.5*size_*square_ratio_*disp_ratio)}.draw(s3d::Palette::Black);
        font(white_cou).drawAt(double(size_)*disp_ratio,x_+size_*1.5,y_-size_*0.5, s3d::Palette::Black);
        font(black_cou).drawAt(double(size_)*disp_ratio,x_+size_*7.5,y_-size_*0.5, s3d::Palette::Black);
    }

}

void BoardVisualize::drawResult(const Board & board){
    static const s3d::Font font{ s3d::FontMethod::MSDF, size_};
    s3d::Rect{x_+size_,y_+size_*3,size_*6,size_*2}.draw(s3d::ColorF{s3d::Palette::White,0.7});
    int white_cou=utils_.count(board,OthelloAI::Color::white);
    int black_cou=utils_.count(board,OthelloAI::Color::black);
    if(white_cou>black_cou){
        font(U"White Win").drawAt(double(size_),s3d::Scene::Center(), s3d::Palette::Black);
    }
    else if(white_cou<black_cou){
        font(U"Black Win").drawAt(s3d::Scene::Center(), s3d::Palette::Black);
    }
    else{
        font(U"  Draw  ").drawAt(double(size_),s3d::Scene::Center(), s3d::Palette::Black);
    }
}

}// namespace OthelloAI