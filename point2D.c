#include "point2D.h"

/** Equals **/
bool equals( Point2D p1, Point2D p2 ){
    return (p1.x==p2.x)&&(p1.y==p2.y);
}

/** Equals **/
Point2D createPoint( int x, int y, bool alive ){
    Point2D p;
    p.x = x;
    p.y = y;
    p.alive = alive;
    return p;
}
