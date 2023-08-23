#pragma once
#include<iostream>

namespace OthelloAI{

class Point{
public:
    int x_;
    int y_;
    Point(int x, int y){
        x_=x;
        y_=y;
    }
    Point(){set(0,0);}
    void set(int x, int y){
        x_=x;
        y_=y;
    }
};

class Color{
public:
    //color
    static const int8_t white=1;
    static const int8_t black=-1;
    static const int8_t free=0;

    int8_t color_;
    Color(int8_t color){color_=color;}
    Color(){color_=free;}
    void set(int8_t color){color_=color;}
    operator int8_t() const { return color_; }
    Color operator !() const {return Color(color_*(-1));}
    bool operator==(Color color){
        return color.color_==color_;
    }
    void reverse(){color_*=(-1);}
};

class Disk{
public:
    Point point_;
    Color color_;

    Disk(int x, int y, int8_t color):
        point_(x,y),
        color_(color){}
    Disk(Point point, Color color){
        point_=point;
        color_.color_=color.color_;
    }
    Disk(Point point, int8_t color):
         point_(point),
        color_(color){}
    Disk():
        point_(0,0),
        color_(Color::free){}
    void set(Point point, Color color){
        point_=point;
        color_.color_=color.color_;
    }
};

}// namespace OthelloAI