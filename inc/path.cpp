#include "path.h"

Point::Point()
{
    x = new float(0.f);
    y = new float(0.f);
}

Point::Point(float _x, float _y)
{
    x = new float(_x);
    y = new float(_y);
}

Point::~Point()
{
    *x = 0.f;
    *y = 0.f;
    delete x;
    delete y;
}

float Point::GetX()
{
    return *x;
}

float Point::GetY()
{
    return *y;
}

float *Point::GetPTX()
{
    return x;
}

float *Point::GetPTY()
{
    return y;
}

void Point::SetPosFromPoint(Point p)
{
    *x = p.GetX();
    *y = p.GetY();
}

void Point::SetX(float _x)
{
    *x = _x;
}

void Point::SetY(float _y)
{
    *y = _y;
}

float Point::Lenght(Point *p2)
{
    if (*x == p2->GetX())
    {
        if((*y - p2->GetY()) < 0){
            return (-1.0f * (*y - p2->GetY()));
        }else{
            return (*y - p2->GetY());
        }
    }
    else if (*y == p2->GetY())
    {
        if((*x - p2->GetX()) < 0){
            return (-1.0f * (*x - p2->GetX()));
        }else{
            return (*x - p2->GetX());
        }
    }
    float _y = 0.f, _x = 0.f;
    if((*y - p2->GetY()) < 0){
        _y = -1.0f * (*y - p2->GetY());
    }else{
        _y = *y - p2->GetY();
    }
    if((*x - p2->GetX()) < 0){
        _x = -1.0f * (*x - p2->GetX());
    }else{
        _x = *x - p2->GetX();
    }
    return sqrt((pow(_x, 2)) + (pow(_y, 2)));
}

Path::Path(std::vector<Point *> _points, float thistime, float f, bool type)
{
    points = _points;
    spawntime = thistime;
    float lenght = 0.f;
    for (int i = 0; i < _points.size() - 1; i++)
    {
        lenght = lenght + _points.at(i)->Lenght(_points.at(i + 1));
        lenghts.push_back(_points.at(i)->Lenght(_points.at(i + 1)));
    }
    if (type == true)
    {
        speed = lenght / f;
    }
    else
    {
        speed = f;
    }
    offset = 0.f;
    cycled = false;
    loop = false;
    curr_pos = 0;
    curr_time = spawntime;
    curr_len = lenghts[0];
}

Path::Path(std::vector<Point *> _points, float thistime, float f, bool type, float _offset)
{
    points = _points;
    spawntime = thistime;
    float lenght = 0.f;
    for (int i = 0; i < _points.size() - 1; i++)
    {
        lenght = lenght + _points.at(i)->Lenght(_points.at(i + 1));
        lenghts.push_back(_points.at(i)->Lenght(_points.at(i + 1)));
    }
    if (type == true)
    {
        speed = lenght / f;
    }
    else
    {
        speed = f;
    }
    offset = _offset;
    cycled = false;
    loop = false;
    curr_pos = 0;
    curr_time = spawntime;
    curr_len = lenghts[0];
}

Path::Path(std::vector<Point *> _points, float thistime, bool _loop, bool _cycled, float f, bool type, float _offset)
{
    cycled = _cycled;
    if (cycled)
    {
        _points.push_back(_points.at(0));
    }
    points = _points;
    spawntime = thistime;
    float lenght = 0.f;
    for (int i = 0; i < _points.size() - 1; i++)
    {
        lenght = lenght + _points.at(i)->Lenght(_points.at(i + 1));
        lenghts.push_back(_points.at(i)->Lenght(_points.at(i + 1)));
    }
    if (type == true)
    {
        speed = lenght / f;
    }
    else
    {
        speed = f;
    }
    offset = _offset;
    loop = _loop;
    curr_pos = 0;
    curr_time = spawntime;
    curr_len = lenghts[0];
}

Path::Path(std::vector<Point *> _points, float thistime, bool _loop, bool _cycled, float f, bool type)
{
    cycled = _cycled;
    if (cycled)
    {
        _points.push_back(_points.at(0));
    }
    points = _points;
    spawntime = thistime;
    float lenght = 0.f;
    for (int i = 0; i < _points.size() - 1; i++)
    {
        lenght = lenght + _points.at(i)->Lenght(_points.at(i + 1));
        lenghts.push_back(_points.at(i)->Lenght(_points.at(i + 1)));
    }
    if (type == true)
    {
        speed = lenght / f;
    }
    else
    {
        speed = f;
    }
    offset = 0.f;

    loop = _loop;
    curr_pos = 0;
    curr_time = spawntime;
    curr_len = lenghts[0];
    /*for(int i =0; i < lenghts.size();i++){
        std::cout << "lenghts(at - i): " << lenghts.at(i) << std::endl;
    }*/
}

Path::Path(mathfunF1 _fun, float thistime, float _speed)
{
    fun2 = _fun;
    offset = 0;
    speed = _speed;
    spawntime = thistime;
    loop = false;
    cycled = false;
    curr_pos = 0;
    curr_time = 0;
    curr_len = 0;
}

Path::Path(mathfunD1 _fun, float thistime, float _speed)
{
    fun = _fun;
    offset = 0;
    speed = _speed;
    spawntime = thistime;
    loop = false;
    cycled = false;
    curr_pos = 0;
    curr_time = 0;
    curr_len = 0;
}

Path::Path(mathfunF1 _fun, float thistime, float _offset, float _speed)
{
    fun2 = _fun;
    offset = _offset;
    speed = _speed;
    loop = false;
    cycled = false;
    curr_pos = 0;
    curr_time = 0;
    curr_len = 0;
}

Path::Path(mathfunD1 _fun, float thistime, float _offset, float _speed)
{
    fun = _fun;
    offset = _offset;
    speed = _speed;
    spawntime = thistime;
    loop = false;
    cycled = false;
    curr_pos = 0;
    curr_time = 0;
    curr_len = 0;
}

Point Path::GetPos(float thistime)
{
 //   std::cout << "thistime: " << thistime << std::endl;
    float time = (thistime - spawntime) + offset;

    if (time >= (curr_len / speed))
    {
        if (curr_pos == points.size() - 1)
        {
            // if is at end
            if (loop)
            {
               // std::cout << "reseting " << std::endl;
                // reset
                spawntime = thistime;
                curr_pos = 0;
                curr_time = spawntime;
                curr_len = lenghts[0];
                return GetPos((time - curr_time), points[curr_pos], points[curr_pos + 1]);
            }
            else
            {
                // stop move
                return *points.at((points.size() - 1));
            }
        }
        else
        {
            /*std::cout << "adding curr_pos: " << curr_pos << "-curr_len: " << curr_len << "-curr_time: " << curr_time << std::endl;
            std::cout << "time:  " << time << "-curr_len/speed: " << (curr_len/speed) <<  std::endl;
            std::cout << "points.size():  " << points.size() << std::endl;*/
            //points.size() - 1
            curr_pos++;
            curr_len = curr_len + lenghts[curr_pos];
            curr_time = time;
            //must be secnod control else -> segmentation fault because of (curr_pos+1)
            if(curr_pos == (points.size() -1)){
                // if is at end
                if (loop)
                {
                   // std::cout << "reseting " << std::endl;
                    // reset
                    spawntime = thistime;
                    curr_pos = 0;
                    curr_time = spawntime;
                    curr_len = lenghts[0];
                    return GetPos((time - curr_time), points[curr_pos], points[curr_pos + 1]);
                }
                else
                {
                    // stop move
                    return *points.at((points.size() - 1));
                }
            }else{
                return GetPos((time - curr_time), points[curr_pos], points[curr_pos + 1]);
            }
        }
    }
    return GetPos((time - curr_time), points[curr_pos], points[curr_pos + 1]);
}

Point Path::GetPos(float time, Point *start, Point *end)
{
  //  std::cout << "Path::GetPos() called with: " << time << "-sx: " << start->GetX() << "-sy: " << start->GetY()<< "-ex: " << end->GetX() << "-ey: " << end->GetY() << std::endl;
    Point pos(0.f, 0.f);
    float h = time * speed;
    if (start->GetX() == end->GetX())
    {
        if (start->GetY() < end->GetY())
        {
            pos.SetY(start->GetY() + h);
            pos.SetX(start->GetX());
        }
        else
        {
            pos.SetY(start->GetY() - h);
            pos.SetX(start->GetX());
        }
    }
    else if (start->GetY() == end->GetY())
    {
        if (start->GetX() < end->GetX())
        {
            pos.SetY(start->GetY());
            pos.SetX(start->GetX() + h);
        }
        else
        {
            pos.SetY(start->GetY());
            pos.SetX(start->GetX() - h);
        }
    }
    else if (start->GetX() < end->GetX())
    {
        if (start->GetY() < end->GetY())
        {
            float alpha = atan(((end->GetY() - start->GetY()) / (end->GetX() - start->GetX())));
            pos.SetY(start->GetY() + (h * sin(alpha)));
            pos.SetX(start->GetX() + (h * cos(alpha)));
        }
        else
        {
            float alpha = atan(((start->GetY() - end->GetY()) / (end->GetX() - start->GetX())));
            pos.SetY(start->GetY() - (h * sin(alpha)));
            pos.SetX(start->GetX() + (h * cos(alpha)));
        }
    }
    else if (start->GetX() > end->GetX())
    {
        if (start->GetY() < end->GetY())
        {
            float alpha = atan(((end->GetY() - start->GetY()) / (end->GetX() - start->GetX())));
            pos.SetY(start->GetY() + (h * sin(alpha)));
            pos.SetX(start->GetX() - (h * cos(alpha)));
        }
        else
        {
            float alpha = atan(((start->GetY() - end->GetY()) / (start->GetX() - end->GetX())));
            pos.SetY(start->GetY() - (h * sin(alpha)));
            pos.SetX(start->GetX() - (h * cos(alpha)));
        }
    }
    return pos;
}

Point Path::GetFunPosF(float thistime)
{
    Point p(thistime + offset, fun2(thistime + offset));
    return p;
}

Point Path::GetFunPosD(float thistime)
{
    Point p(thistime + offset, fun(thistime + offset));
    return p;
}

float Path::GetSpeed()
{
    return speed;
}

float Path::GetOffset()
{
    return offset;
}

bool Path::GetCycling()
{
    return cycled;
}

bool Path::GetLooped()
{
    return loop;
}

int Path::GetCurrPos()
{
    return curr_pos;
}

float Path::GetCurrTime()
{
    return curr_time;
}

float Path::GetSpawnTime()
{
    return spawntime;
}

std::vector<Point *> Path::GetPoints()
{
    return points;
}

void Path::SetSpeed(float _speed)
{
    speed = _speed;
}

void Path::SetOffset(float _offset)
{
    offset = _offset;
}

void Path::SetCycling(bool _cycled)
{
    cycled = _cycled;
}

void Path::SetLooped(bool _loop)
{
    loop = _loop;
}

void Path::SetPoints(std::vector<Point *> _points)
{
    points = _points;
}

float Path::GetLenght()
{
    float lenght = 0.f;
    for (int i = 0; i < lenghts.size(); i++)
    {
        lenght = lenght + lenghts.at(i);
    }
    return lenght;
}

float Path::GetLenght(unsigned int at)
{
    return lenghts.at(at);
}

Path Path::clone()
{
    return *this;
}

bool Path::SaveToFile(std::string filename)
{
    std::fstream File;
    File.open(filename.c_str(), std::ios::binary | std::ios::out);
    if (!File)
    {
        return false;
    }
    File.write((char *)this, sizeof(Path));
    if (!File.good())
    {
        return false;
    }
    File.close();
    if (!File.good())
    {
        return false;
    }
    return true;
}

bool Path::LoadFromFile(std::string filename)
{
    std::fstream File;
    File.open(filename.c_str(), std::ios::binary | std::ios::in);
    if (!File)
    {
        return false;
    }
    File.read((char *)this, sizeof(Path));
    if (!File.good())
    {
        return false;
    }
    File.close();
    if (!File.good())
    {
        return false;
    }
    return true;
}

bool Path::isTrivialyCopiable()
{
    if (std::is_trivially_copyable<Path>::value)
    {
        return true;
    }
    else
    {
        return false;
    }
}