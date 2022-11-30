#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "model.h"
#include "transform3d.h"

class InteractiveSphere{
public:
    InteractiveSphere(std::string sphere_path);
    InteractiveSphere();

    void Draw(Camera &cam, Shader & shaderprogram);
    void Draw(Camera &cam, Shader & shaderprogram, Texture & tex);
    void Draw(Camera &cam, Shader & shaderprogram, glm::fvec4 color);
    void Draw(Camera &cam, Shader & shaderprogram, glm::fvec3 color, float alpha=1.0f);



    void Translate(float _x=0, float _y=0, float _z=0);


    //recompute position
    void Update();

    void clone(InteractiveSphere &_to);


    // compute force about cicle
    // time      -  force time
    // r         -  circle diameter
    // speed     -  force speed
    // type      -  force direction
    //     1 - x = computed_x
    //       - y = computed_y
    //     2 - x = computed_x
    //       - z = computed_y
    //     3 - y = computed_y
    //       - z = computed_x
    // inverse1  -  inverse 1. value
    // inverse2  -  inverse 2. value
    void CircleForce(float time, float r, int speed,  float time_diff = 0.0f, int type = 1, bool inverse1 = false,  bool inverse2= false);

    // time   -  force time
    // r      -  circle diameter
    // speed  -  force speed
    // offset -  time offset for differencing
    // type   -  movement type (startpos & direction) -> see documentation
    //      c -  z       |  smer
    //      ----------------------
    //      1 -  vpravo  |  nahoru
    //      2 -  vpravo  |  dolu
    //      3 -  vlevo   |  nahoru
    //      4 -  vlevo   |  dolu
    //      5 -  nahore  |  vpravo
    //      6 -  nahore  |  vlevo
    //      7 -  dole    |  vpravo
    //      8 -  dole    |  vlevo
    void CircleMove(float time, float r, int speed, float offset = 0.f, int type = 1, float *px = NULL, float *py = NULL);

    // time   -  force time
    // a      -  elipse size 1
    // b      -  elipse size 2
    // speed  -  force speed
    // offset -  time offset for differencing
    // type   -  movement type (startpos & direction) -> see documentation
    //      c -  z       |  smer
    //      ----------------------
    //      1 -  vpravo  |  nahoru
    //      2 -  vpravo  |  dolu
    //      3 -  vlevo   |  nahoru
    //      4 -  vlevo   |  dolu
    //      5 -  nahore  |  vpravo
    //      6 -  nahore  |  vlevo
    //      7 -  dole    |  vpravo
    //      8 -  dole    |  vlevo
    void ElipseMove(float time, float a, float b, int speed, float offset = 0.f, int type = 1, float *px = NULL, float *py = NULL);

    // computes vertical litter force
    // angle  -  angle of force in degrees
    // v0     -  starting force speed
    void VerticalLitterForce(float time, float angle, int v0 = 0, float g = 9.81f);

    void SetX(float _x);
    void SetY(float _y);
    void SetZ(float _z);
    void SetScale(float _scale);
    void SetPos(float _x, float _y, float _z);

    float GetX();
    float GetY();
    float GetZ();
    float GetScale();

    float *GetPTX();
    float *GetPTY();
    float *GetPTZ();


    /*//recompute by phisics
    void Update(float time){

    }*/
    float x=0,y=0,z=0, scale= 1.0f;
private:
    //Mesh
    Model mesh;
    //positions
    Transform3D pos;


};


#endif