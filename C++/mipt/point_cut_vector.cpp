#include <iostream>
#include <cstdlib>
#include <cmath>
#define DOES_NOT_BELONG 1
#define BELONG 2
//„то значит "с какой стороны от отрезка леж. точка?
//„то знач. "определени€ вектора, соотв. отрезку?
class Point; class Segment; class Vector;

class Point{
    double x;
    double y;
    public:
    Point (double _x, double _y): x (_x), y (_y) {}
    bool ps (Segment a);
    double Getx () {return x;}
    double Gety () {return y;}
    void Setx (double _x) {x = _x;}
    void Sety (double _y) {y = _y;}
    Point operator- (Point a) {Point b = *this; b.Setx (this -> Getx () - a.Getx());
                                                 b.Sety (this -> Gety () - a.Gety());
                                                                            return b;}
    bool operator== (Point a) {if (Getx () == a.Getx () && Gety () == a.Gety ()) return 1; return 0;}
};

class Segment{
    Point x;
    Point y;
    public:
    Segment (Point _x, Point _y): x (_x), y (_y) {}
    Segment cross (Segment a);
    double length () {return sqrt ((y - x).Getx ()* (y - x).Getx () + (y - x).Gety ()*(y - x).Gety ());}
    Point Getx () {return x;}
    Point Gety () {return y;}
    bool operator== (Segment a) {if (Getx () == a.Getx () && Gety () == a.Gety ()) return 1; return 0;}
    Vector whatvect ();
    bool wherepoint (Point a);
};

class Vector{
        Point x;
        public:
        Vector (Point _x): x (_x) {}
        void reverse () { x.Setx (-x.Getx ()), x.Sety (-x.Gety ());}
        void Setx (Point a) {x = a;}
        bool vect_mult (Vector a) { return (x.Getx ()*a.x.Gety () - x.Gety ()*a.x.Getx ()) > 0? 1: 0;}
};

bool Segment::wherepoint (Point a){
    if (!length ()) throw 1;

    //!-----------повтор

    /*
    double arr [3] = {};
    if (Getx ().Getx () == Gety ().Getx ())
        arr [0] = 1, arr [1] = 0, arr [2] = Getx ().Getx ();
    else if (Getx ().Gety () == Gety ().Gety ())
        arr [0] = 0, arr [1] = 1, arr [2] = Getx ().Gety ();
    else
        {
        arr [0] = - (Getx ().Gety () - Gety ().Gety ()) / (Getx ().Getx () - Gety ().Getx ());
        arr [1] = 1;
        arr [2] = Getx ().Gety () - arr [0]*Getx ().Getx ();
        }
    //---
    bool updown;
    double temp = a.Getx ()*arr [0] + arr [2] - a.Gety ();
    if (!temp) throw BELONG;
    if (temp > 0) updown = 1;
    else updown = 0;

    if (y.Getx() - x.Getx () < 0 && !updown ||
        y.Getx() - x.Getx () > 0 && updown
        ) return 1;
    return 0;
    */
    return (this -> whatvect ()).vect_mult (a);
    }

Vector Segment::whatvect (){

    if (length () == 0) return Point ({0, 0});

    double fi = (y.Gety () - x.Gety ()) / (y.Getx () - x.Getx ());
    if (!fi) return Point ({y.Getx () - x.Getx (), 0});
    return  Point ({length ()/ fi*sin (fi), length ()*fi*cos (fi)});

    }


bool Point::ps (Segment a) {
    Segment b (a.Getx (), *this);
    Segment c (*this, a.Gety ());
    if (b.length () + c.length () == a.length ()) return 1;
    return 0;
}

Segment Segment::cross (Segment a){


    if (Getx () == Gety ())
        if (Getx ().ps (a)) {Getx (), Getx ();}
        else throw DOES_NOT_BELONG;
    if (a.Getx () == a.Gety ())
        if (a.Getx ().ps (*this)) return {a.Getx (), a.Getx ()};
         else throw DOES_NOT_BELONG;

    double arr [6] = {};
    if (Getx ().Getx () == Gety ().Getx ())
        arr [0] = 1, arr [1] = 0, arr [2] = Getx ().Getx ();
    else if (Getx ().Gety () == Gety ().Gety ())
        arr [0] = 0, arr [1] = 1, arr [2] = Getx ().Gety ();
    else
        {
        arr [0] = - (Getx ().Gety () - Gety ().Gety ()) / (Getx ().Getx () - Gety ().Getx ());
        arr [1] = 1;
        arr [2] = Getx ().Gety () - arr [0]*Getx ().Getx ();
        }

    if (a.Getx ().Getx () == a.Gety ().Getx ())
        arr [3] = 1, arr [4] = 0, arr [5] = a.Getx ().Getx ();
    if (a.Getx ().Gety () == a.Gety ().Gety ())
        arr [3] = 0, arr [4] = 1, arr [5] = a.Getx ().Gety ();
    else
        {
        arr [3] = - (a.Getx ().Gety () - a.Gety ().Gety ()) / (a.Getx ().Getx () - a.Gety ().Getx ());
        arr [4] = 1;
        arr [5] = a.Getx ().Gety () - arr [3]*a.Getx ().Getx ();
        }

    double det = arr [0]*arr[4] - arr [1]*arr [3];

    if (det == 0)
        if (arr [2] != arr [5]) throw DOES_NOT_BELONG;
        else if (Getx ().ps (a))
                    {
                    if (a.Getx ().ps (*this))
                        return {Getx (), a.Getx ()};
                    else if (a.Gety ().ps (*this))
                        return {Getx (), a.Gety ()};
                    else return {Getx (), Getx ()};
                    }
              else if (Gety ().ps (a))
                    {
                    if (a.Getx ().ps (*this))
                        return {Gety (), a.Getx ()};
                    else if (a.Gety ().ps (*this))
                        return {Gety (), a.Gety ()};
                    else return {Gety (), Gety ()};
                    }
            else throw DOES_NOT_BELONG;

    return {{det/ arr [2]*arr[4] - arr [1]*arr [5], det/ arr [0]*arr[5] - arr [2]*arr [3]},
            {det/ arr [2]*arr[4] - arr [1]*arr [5], det/ arr [0]*arr[5] - arr [2]*arr [3]}};

}

int main (){
    ;
    }
