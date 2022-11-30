#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <type_traits>

class Point
{
public:
    float *x, *y;

    Point(float _x, float _y);
    Point();
    ~Point();

    float GetX();
    float GetY();

    float *GetPTX();
    float *GetPTY();

    void SetPosFromPoint(Point p);

    void SetX(float _x);
    void SetY(float _x);

    float Lenght(Point *p2);
};

// 1-paramater 2D function(x =time, y=computed from function), 2 parameter - 3D function(x =time, z=time, y=computed from function)
// math functions prototypes - float with 1/2 paramateres(mathfunF1/2) and with doubles (mathwunD1/2)
typedef float (*mathfunF1)(float param1);
typedef float (*mathfunF2)(float param1, float param2);
typedef float (*mathfunD1)(double param1);
typedef float (*mathfunD2)(double param1, double param2);

class Path
{
public:
    float speed;     // move speed
    float offset;    // time offset
    bool cycled;     // is path cycled (ex. triangle)
    bool loop;       // move in loop or once (instant/pernament move)
    int curr_pos;    // current position(current line - array indexing - from 0)
    float curr_time; // current time from last start line
    float curr_len;  // current lenght to complete to get to next point (second point of it)
    float spawntime; // time when the part start
    std::vector<Point *> points;
    std::vector<float> lenghts; // lenghts of line between par of points
    mathfunD1 fun;
    mathfunF1 fun2;

    // type = 1 -> full_time
    // type = 0 -> speed
    Path(std::vector<Point *> _points, float thistime, float f, bool type);
    Path(std::vector<Point *> _points, float thistime, float f, bool type, float _offset);
    Path(std::vector<Point *> _points, float thistime, bool _loop, bool _cycled, float f, bool type);
    Path(std::vector<Point *> _points, float thistime, bool _loop, bool _cycled, float f, bool type, float _offset);

    Path(mathfunF1 _fun, float thistime, float _speed);
    Path(mathfunD1 _fun, float thistime, float _speed);
    Path(mathfunF1 _fun, float thistime, float _offset, float _speed);
    Path(mathfunD1 _fun, float thistime, float _offset, float _speed);

    Point GetPos(float thistime);
    // intern function
    Point GetPos(float time, Point *start, Point *end);

    // get pos from function (float)
    Point GetFunPosF(float thistime);
    // get pos from function (double)
    Point GetFunPosD(float thistime);

    float GetSpeed();
    float GetOffset();
    bool GetCycling();
    bool GetLooped();
    int GetCurrPos();
    float GetCurrTime();
    float GetSpawnTime();
    std::vector<Point *> GetPoints();

    void SetSpeed(float _speed);
    void SetOffset(float _offset);
    void SetCycling(bool _cycled);
    void SetLooped(bool _looped);
    void SetPoints(std::vector<Point *> _points);

    // returns full lenght of path
    float GetLenght();
    // note: at is in array format (from 0)
    float GetLenght(unsigned int at);

    Path clone();

    bool SaveToFile(std::string filename);
    bool LoadFromFile(std::string filename);

    // intern
    static bool isTrivialyCopiable();
};


#endif