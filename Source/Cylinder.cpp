//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Cylinder.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Cylinder.h"
#include "Group.h"
#include "Reader.h"
#include "Disc.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"
#include "Shape.h"
#include "Collision.h"
#include "Block.h"
#include "Puck.h"
#include "Post.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read cylinder
bool Cylinder::read(istream &in, string &token, Group &group) {
    if (token == "Cylinder") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing cylinder opening brace");
        }
        in >> token;
        Cylinder *cylinder = new Cylinder();
        group.push_back(cylinder);
        cylinder->read(in, token);
        return true;
    }
    else if (Puck::read(in, token, group)) {
        return true;
    }
    else if (Post::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read cylinder
void Cylinder::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (_material.read(in, token)) {
        }
        else if (_physical.read(in, token)) {
        }
        else if (token == "Radius") {
            in >> _radius >> token;
        }
        else if (token == "Height") {
            in >> _height >> token;
        }
        else if (token == "Top") {
            in >> _top >> token;
        }
        else if (token == "Bottom") {
            in >> _bottom >> token;
        }
        else if (token == "Rows") {
            in >> _rows >> token;
        }
        else if (token == "Columns") {
            in >> _columns >> token;
        }
        else {
            throw string("Error : Invalid cylinder attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// render cylinder
void Cylinder::render(const Game &game) const {
    glPushMatrix();
    _material.render(game);
    _physical.render(game);
    if (_top) {
        glPushMatrix();
        glTranslated(0.0, 0.0, 0.5 * _height);
        Physical physical;
        Disc disc = Disc(_material, physical, _radius, _rows, _columns);
        disc.render(game);
        glPopMatrix();
    }
    if (_bottom) {
        glPushMatrix();
        glTranslated(0.0, 0.0, -0.5 * _height);
        glRotated(180.0, 1.0, 0.0, 0.0);
        Physical physical;
        Disc disc = Disc(_material, physical, _radius, _rows, _columns);
        disc.render(game);
        glPopMatrix();
    }
    glTranslated(0.0, 0.0, -0.5 * _height);
    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricTexture(cylinder, GL_TRUE);
    gluCylinder(cylinder, _radius, _radius, _height, _columns, _rows);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

//------------------------------------------------------------------------------
// block collision with cylinder
bool Cylinder::block(Collision &collision, Block &collider) {
    bool intersect = false;
    Vectors a = physical().position();
    Vectors b = physical().velocity();
    Vectors c = collider.physical().position();
    Vectors d = collider.physical().velocity();
    a.z(0.0);
    b.z(0.0);
    c.z(0.0);
    d.z(0.0);
    // convert spin to velocity
    double sinSpin = sin(collider.physical().spin() / (double)RESOLUTION * DEG_TO_RAD);
    double cosSpin = cos(collider.physical().spin() / (double)RESOLUTION * DEG_TO_RAD);
    Vectors position = a + b / (double)RESOLUTION;
    position -= c;
    position = Vectors(cosSpin * position.x() + sinSpin * position.y(),
        -sinSpin * position.x() + cosSpin * position.y(), 0.0, 1.0);
    position += c;
    d += b - (position - a) * (double)RESOLUTION;
    // four faces
    double sinAngle = sin(collider.physical().angle() * DEG_TO_RAD);
    double cosAngle = cos(collider.physical().angle() * DEG_TO_RAD);
    Vectors normalBottom = Vectors(sinAngle, -cosAngle, 0.0, 0.0);
    Vectors normalRight = Vectors(cosAngle, sinAngle, 0.0, 0.0);
    Vectors normalTop = Vectors(-sinAngle, cosAngle, 0.0, 0.0);
    Vectors normalLeft = Vectors(-cosAngle, -sinAngle, 0.0, 0.0);
    enum { BOTTOM, RIGHT, TOP, LEFT, FACES };
    for (int face = 0; face < FACES; face++) {
        Vectors normal;
        double thickness;
        double length;
        switch (face) {
            case BOTTOM: {
                normal = normalBottom;
                thickness = collider.height();
                length = collider.width();
                break;
            }
            case RIGHT: {
                normal = normalRight;
                thickness = collider.width();
                length = collider.height();
                break;
            }
            case TOP: {
                normal = normalTop;
                thickness = collider.height();
                length = collider.width();
                break;
            }
            case LEFT: {
                normal = normalLeft;
                thickness = collider.width();
                length = collider.height();
                break;
            }
        }
        double r = radius() + 0.5 * thickness;
        double A = (b - d).dot(normal);
        double B = (a - c).dot(normal) - r;
        if (A < 0.0) {
            if (A > -EPSILON) {
                A = -EPSILON;
            }
            double t = -B / A;
            if (t > 0.0 && t < collision.time()) {
                Vectors position  = (a - c) + (b - d) * t;
                position -= r * normal;
                if (position.magnitude() < 0.5 * length) {
                    collision.collision(true);
                    collision.time(t);
                    collision.collider(&collider);
                    collision.obstacle(this);
                    collision.normal(-normal);
                    collision.position(a + b * t + collision.normal() * radius());
                    if (collider.player()) {
                        collider.physical().velocity(d);
                        collider.physical().spin(0.0);
                    }
                    intersect = true;
                }
            }
        }
    }
    // four edges
    enum { BOTTOM_RIGHT, TOP_RIGHT, TOP_LEFT, BOTTOM_LEFT, EDGES };
    for (int edge = 0; edge < EDGES; edge++) {
        Vectors centre;
        switch (edge) {
            case BOTTOM_RIGHT: {
                centre = c + 0.5 * collider.height() * normalBottom + 0.5 * collider.width() * normalRight;
                break;
            }
            case TOP_RIGHT: {
                centre = c + 0.5 * collider.height() * normalTop + 0.5 * collider.width() * normalRight;
                break;
            }
            case TOP_LEFT: {
                centre = c + 0.5 * collider.height() * normalTop + 0.5 * collider.width() * normalLeft;
                break;
            }
            case BOTTOM_LEFT: {
                centre = c + 0.5 * collider.height() * normalBottom + 0.5 * collider.width() * normalLeft;
                break;
            }
        }
        double r = radius();
        double A = (b - d).dot(b - d);
        double B = 2.0 * (a - centre).dot(b - d);
        double C = (a - centre).dot(a - centre) - r * r;
        double root = B * B - 4.0 * A * C;
        if (root >= EPSILON) {
            double t = (-B - sqrt(root)) / (2.0 * A);
            if (t > 0.0 && t < collision.time()) {
                collision.collision(true);
                collision.time(t);
                collision.collider(&collider);
                collision.obstacle(this);
                collision.normal((centre - a).unit());
                collision.position(a + b * t + collision.normal() * radius());
                if (collider.player()) {
                    collider.physical().velocity(d);
                    collider.physical().spin(0.0);
                }
                intersect = true;
            }
        }
    }
    return intersect;
}

//------------------------------------------------------------------------------
// cylinder collision with cylinder
bool Cylinder::cylinder(Collision &collision, Cylinder &collider) {
    bool intersect = false;
    Vectors a = collider.physical().position();
    Vectors b = collider.physical().velocity();
    Vectors c = physical().position();
    Vectors d = physical().velocity();
    a.z(0.0);
    b.z(0.0);
    c.z(0.0);
    d.z(0.0);
    double r = collider.radius() + radius();
    double A = (b - d).dot(b - d);
    double B = 2.0 * (a - c).dot(b - d);
    double C = (a - c).dot(a - c) - r * r;
    double root = B * B - 4.0 * A * C;
    if (root >= EPSILON) {
        double t = (-B - sqrt(root)) / (2.0 * A);
        if (t > 0.0 && t < collision.time()) {
            collision.collision(true);
            collision.time(t);
            collision.collider(&collider);
            collision.obstacle(this);
            collision.normal((a - c).unit());
            collision.position(c + d * t + collision.normal() * radius());
            intersect = true;
        }
    }
    return intersect;
}

//------------------------------------------------------------------------------
// cylinder mass
double Cylinder::mass() const {
    return _physical.density() * PI * radius() * radius() * height();
}

//------------------------------------------------------------------------------
// cylinder inertia
double Cylinder::inertia() const {
    return mass() * radius() * radius() / 2.0;
}

//------------------------------------------------------------------------------
