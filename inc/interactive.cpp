#include "interactive.h"

InteractiveSphere::InteractiveSphere(std::string sphere_path) : mesh(sphere_path.c_str())
{
    pos.SetRotation(glm::vec3(0, 0, 0));
    pos.SetScale(1.0f);
    pos.SetPositionF(glm::fvec3(0.0f, 0.0f, 0.0f));
}

InteractiveSphere::InteractiveSphere() : mesh("../res/models/crow/scene.gltf")
{
    pos.SetRotation(glm::vec3(0, 0, 0));
    pos.SetScale(1.0f);
    pos.SetPositionF(glm::fvec3(0.0f, 0.0f, 0.0f));
}

void InteractiveSphere::Draw(Camera &cam, Shader &shaderprogram)
{
    mesh.DrawF(shaderprogram, cam);
}

void InteractiveSphere::Draw(Camera &cam, Shader &shaderprogram, Texture &tex)
{
    mesh.DrawF(shaderprogram, cam, tex);
}

void InteractiveSphere::Draw(Camera &cam, Shader &shaderprogram, glm::fvec4 color)
{
    glm::fvec3 _col(color.x, color.y, color.z);
    mesh.DrawColF(shaderprogram, cam, _col, color.w);
}

void InteractiveSphere::Draw(Camera &cam, Shader &shaderprogram, glm::fvec3 color, float alpha)
{
    mesh.DrawColF(shaderprogram, cam, color, alpha);
}

void InteractiveSphere::SetPos(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    pos.SetPositionF(glm::fvec3(x, y, z));
}

void InteractiveSphere::Translate(float _x, float _y, float _z)
{
    x = x + _x;
    y = y + _y;
    z = z + _z;
    pos.TranslateF(glm::fvec3(_x, _y, _z));
}

void InteractiveSphere::SetScale(float _scale)
{
    scale = _scale;
    pos.SetScale(scale);
}

// recompute position
void InteractiveSphere::Update()
{
    pos.SetPositionF(glm::fvec3(x, y, z));
    pos.SetScale(scale);
    std::vector<glm::fmat4> matricesf;
    for (int i = 0; i < mesh.GetNumMatricesMeshes(); i++)
    {
        matricesf.push_back(pos.GetMatrixF());
    }
    mesh.SetMatricesMeshesF(matricesf);
}

void InteractiveSphere::clone(InteractiveSphere &_to)
{
    _to.x = x;
    _to.z = z;
    _to.y = y;
    _to.scale = scale;
    _to.pos = pos;
    _to.mesh = mesh;
}

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
void InteractiveSphere::CircleForce(float time, float r, int speed, float time_diff, int type, bool inverse1, bool inverse2)
{
    time = time + time_diff;
    // computed values
    float _x = r * sin((time * speed) * (3.14f / 180.0f));
    float _y = r * cos((time * speed) * (3.14f / 180.0f));
    if (type == 1)
    {
        if (inverse1)
        {
            x = -1 * _x;
        }
        else
        {
            x = _x;
        }
        if (inverse2)
        {
            y = -1 * _y;
        }
        else
        {
            y = _y;
        }
        pos.SetPositionF(glm::fvec3(x, y, z));
    }
    else if (type == 2)
    {
        if (inverse1)
        {
            x = -1 * _x;
        }
        else
        {
            x = _x;
        }
        if (inverse2)
        {
            z = -1 * _y;
        }
        else
        {
            z = _y;
        }
        pos.SetPositionF(glm::fvec3(x, y, z));
    }
    else if (type == 3)
    {
        if (inverse1)
        {
            y = -1 * _y;
        }
        else
        {
            y = _y;
        }
        if (inverse2)
        {
            z = -1 * _x;
        }
        else
        {
            z = _x;
        }
        pos.SetPositionF(glm::fvec3(x, y, z));
    }
}

// computes vertical litter force
// angle  -  angle of force in degrees
// v0     -  starting force speed
void InteractiveSphere::VerticalLitterForce(float time, float angle, int v0, float g)
{
    float horni = g * std::pow(time, 2), dolni = 2 * (v0 * std::cos(angle * (3.14f / 180.0f)));
    float _z = ((std::tan(angle * (3.14f / 180.0f)) * time) + ((-1 * horni) / dolni));
    y = _z;
    pos.SetPositionF(glm::fvec3(x, y, z));
}

void InteractiveSphere::SetX(float _x)
{
    x = _x;
}

void InteractiveSphere::SetY(float _y)
{
    y = _y;
}

void InteractiveSphere::SetZ(float _z)
{
    z = _z;
}

float InteractiveSphere::GetX()
{
    return x;
}

float InteractiveSphere::GetY()
{
    return y;
}

float InteractiveSphere::GetZ()
{
    return z;
}

float InteractiveSphere::GetScale()
{
    return z;
}

float *InteractiveSphere::GetPTX()
{
    return &x;
}

float *InteractiveSphere::GetPTY()
{
    return &y;
}

float *InteractiveSphere::GetPTZ()
{
    return &z;
}


void InteractiveSphere::CircleMove(float time, float r, int speed, float offset, int type, float *px, float *py){
    time = time + offset;
    if(px == NULL){
        px = GetPTX();
    }
    if(py == NULL){
        py = GetPTZ();
    }
    
   switch (type)
    {
    case 1:
    {
        float _x1 = *px, _y1 = *py;
        _x1 = r * cos((time * speed) * (3.14f / 180.0f));
        _y1 = (r * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x1;
        *py = _y1;
        break;
    }
    case 2:
    {
        float _x2 = *px, _y2 = *py;
        _x2 = r * cos((time * speed) * (3.14f / 180.0f));
        _y2 = (-1 * r) * sin((time * speed) * (3.14f / 180.0f));
        *px = _x2;
        *py = _y2;
        break;
    }
    case 3:
    {
        float _x3 = *px, _y3 = *py;
        _x3 = (r*-1) * cos((time * speed) * (3.14f / 180.0f));
        _y3 = (r * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x3;
        *py = _y3;
        break;
    }
    case 4:
    {
        float _x4 = *px, _y4 = *py;
        _x4 = ((r*-1) * cos((time * speed) * (3.14f / 180.0f)));
        _y4 = ((r*-1) * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x4;
        *py = _y4;
        break;
    }
    case 5:
    {
        float _x5 = *px, _y5 = *py;
        _x5 = (r * sin((time * speed) * (3.14f / 180.0f)));
        _y5 = (r * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x5;
        *py = _y5;
        break;
    }
    case 6:
    {
        float _x6 = *px, _y6 = *py;
        _x6 = ((r*-1) * sin((time * speed) * (3.14f / 180.0f)));
        _y6 = (r * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x6;
        *py = _y6;
        break;
    }
    case 7:
    {
        float _x7 = *px, _y7 = *py;
        _x7 = ((r*-1) * sin((time * speed) * (3.14f / 180.0f)));
        _y7 = (r * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x7;
        *py = _y7;
        break;
    }
    case 8:
    {
        float _x8 = *px, _y8 = *py;
        _x8 = ((r*-1) * sin((time * speed) * (3.14f / 180.0f)));
        _y8 = ((r*-1) * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x8;
        *py = _y8;
        break;
    }
    default:
    {
        float _x9 = *px, _y9 = *py;
        _x9 = (r * cos((time * speed) * (3.14f / 180.0f)));
        _y9 = (r * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x9;
        *py = _y9;
        break;
    }
    }

}

void InteractiveSphere::ElipseMove(float time, float a, float b, int speed, float offset, int type, float *px, float *py){
    time = time + offset;
    if(px == NULL){
        px = GetPTX();
    }
    if(py == NULL){
        py = GetPTZ();
    }
    
    switch (type)
    {
    case 1:
    {
        float _x1 = *px, _y1 = *py;
        _x1 = (a * cos((time * speed) * (3.14f / 180.0f)));
        _y1 = (b * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x1;
        *py = _y1;
        break;
    }
    case 2:
    {
        float _x2 = *px, _y2 = *py;
        _x2 =(a * cos((time * speed) * (3.14f / 180.0f)));
        _y2 = ((-1 * b) * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x2;
        *py = _y2;
        break;
    }
    case 3:
    {
        float _x3 = *px, _y3 = *py;
        _x3 = ((a*-1) * cos((time * speed) * (3.14f / 180.0f)));
        _y3 = (b * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x3;
        *py = _y3;
        break;
    }
    case 4:
    {
        float _x4 = *px, _y4 = *py;
        _x4 = ((a*-1) * cos((time * speed) * (3.14f / 180.0f)));
        _y4 =((b*-1) * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x4;
        *py = _y4;
        break;
    }
    case 5:
    {
        float _x5 = *px, _y5 = *py;
        _x5 = (a * sin((time * speed) * (3.14f / 180.0f)));
        _y5 = (b * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x5;
        *py = _y5;
        break;
    }
    case 6:
    {
        float _x6 = *px, _y6 = *py;
        _x6 = ((a*-1) * sin((time * speed) * (3.14f / 180.0f)));
        _y6 = (b * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x6;
        *py = _y6;
        break;
    }
    case 7:
    {
        float _x7 = *px, _y7 = *py;
        _x7 = ((a*-1) * sin((time * speed) * (3.14f / 180.0f)));
        _y7 = (b * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x7;
        *py = _y7;
        break;
    }
    case 8:
    {
        float _x8 = *px, _y8 = *py;
        _x8 = ((a*-1) * sin((time * speed) * (3.14f / 180.0f)));
        _y8 = ((b*-1) * cos((time * speed) * (3.14f / 180.0f)));
        *px = _x8;
        *py = _y8;
        break;
    }
    default:
    {
        float _x9 = *px, _y9 = *py;
        _x9 = (a * cos((time * speed) * (3.14f / 180.0f)));
        _y9 = (b * sin((time * speed) * (3.14f / 180.0f)));
        *px = _x9;
        *py = _y9;
        break;
    }
    }

}