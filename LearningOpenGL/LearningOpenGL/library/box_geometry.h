#pragma once
#include "geometry.h"
class BoxGeometry : public Geometry
{
public:
    BoxGeometry();

private:
    static const VertList s_vertices;
};

