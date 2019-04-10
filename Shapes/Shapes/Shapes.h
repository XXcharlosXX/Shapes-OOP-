//
//  Header.h
//  Ass4 (shapes)
//
//  Created by Charlie  Velazquez on 9/22/16.
//  Copyright © 2016 GoonPlatoon. All rights reserved.
//

#include <iostream>
#include <math.h>

double const pi = 3.1415926535;
enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, INVALID };

class Shape
{
public:
    Shape(Color c):hue(c){}                         //:hue(c) - initialization list = hue = c
    virtual ~Shape(){};
    Color color() const {return hue;};              //get color
    virtual void color(Color c){hue=c;};                    //set color
    virtual void move(double dx, double dy)=0;
    virtual double area()const =0;
    virtual double perimeter()const=0;
    virtual void render(std::ostream &os)const=0;
    virtual bool inside(double x,double y)const =0;
    virtual double thickness()const{return area()/perimeter();};
    static Color colorAtPoint(Shape* shps[],int num,double X,double Y);
private:
    Color hue;
    //disallow
    Shape(const Shape &other);
    void operator=(const Shape &other);
};

class Box : public Shape
{
public:
    Box(Color c,double _left,double _top,double _right,double _bottom):Shape(c){l=_left,r=_right,t=_top,b=_bottom;}
    ~Box(){};
    //getters
    double left() const {return l;};
    double top() const{return t;};
    double right()const{return r;};
    double bottom()const{return b;};
    //functions
    bool inside(double x,double y)const;
    double area()const{return ((r-l)*(t-b));};
    double perimeter()const{return ((r-l)*2)+((t-b)*2);};
    void move(double x,double y){l+=x;r+=x;t+=y;b+=y;}
    // setters
    void left(double _left){l=_left;};
    void top(double _top){t=_top;};
    void right (double _right){r=_right;};
    void bottom (double _bottom){b=_bottom;};
    //render
    void render(std::ostream &os) const;
private:
    double t,r,l,b;
};

class Circle : public Shape
{
public:
    Circle(Color c,double cirX,double cirY,double rad):Shape(c),cx(cirX),cy(cirY),r(rad){};         // center-x, center-y, radius;
    ~Circle(){};
    //Circle getters
    double centerX() const {return cx;};
    double centerY() const{return cy;};
    double radius() const{return r;};
    //functions
    bool inside(double x,double y)const;
    double area()const{return (pi)*(r*r);};
    double perimeter()const{return (2*pi*r);};
    void move(double x,double y){cx+=x;cy+=y;};
    //Circle setters
    void centerX(double x){cx=x;};
    void centerY(double y){cy=y;};
    void radius(double radd){r=radd;};
    //render
    void render(std::ostream &os) const;
private:
    double cx,cy,r;
};

class Triangle : public Shape
{
public:
    Triangle(Color c,double _v1x,double _v1y,double _v2x,double _v2y,double _v3x,double _v3y):Shape(c),v1x(_v1x),v1y(_v1y),v2x(_v2x),v2y(_v2y),v3x(_v3x),v3y(_v3y){};  // x,y for each corner
    ~Triangle(){};
    // Triangle getters
    double cornerX1()const{return v1x;};
    double cornerY1()const{return v1y;};
    double cornerX2()const{return v2x;};
    double cornerY2()const{return v2y;};
    double cornerX3()const{return v3x;};
    double cornerY3()const{return v3y;};
    // Triangle functions
    bool inside(double x,double y)const;
    double area()const;
    double perimeter()const;
    void move(double x,double y){v1x+=x;v2x+=x;v3x+=x;v1y+=y;v2y+=y;v3y+=y;};
    // Triangle setters
    void cornerX1(double _v1x){v1x=_v1x;};
    void cornerY1(double _v1y){v1y=_v1y;};
    void cornerX2(double _v2x){v2x=_v2x;};
    void cornerY2(double _v2y){v2y=_v2y;};
    void cornerX3(double _v3x){v3x=_v3x;};
    void cornerY3(double _v3y){v3y=_v3y;};
    //render
    void render(std::ostream &os) const;
private:
    double v1x,v1y,v2x,v2y,v3x,v3y;
};

class Polygon : public Shape
{
public:
    Polygon(Color c, double* pts, int v);
    ~Polygon(){delete [] vertices;}; // must deallocate data
    //getters
    int points() const {return vertCount;};
    double vertexX(int place) const {return vertices[place*2];};
    double vertexY(int place) const {return vertices[place*2+1];};
    //setters
    void vertexX(int place, double value) const {vertices[place*2] = value;};
    void vertexY(int place, double value) const {vertices[place*2+1] = value;};
    //functions
    bool inside(double x,double y)const;
    void move(double dx, double dy);
    double area() const;
    double perimeter() const;
    //render
    void render(std::ostream &os) const;
    
    
private:
    double* vertices;
    int vertCount;
};

class Line : public Shape
{
public:
    Line(Color c, double _x1,double _y1, double _x2, double _y2):Shape(c),x1(_x1),y1(_y1),x2(_x2),y2(_y2){};
    ~Line(){};
    //getters
    double end1X()const{return x1;};
    double end1Y()const{return y1;};
    double end2X()const{return x2;};
    double end2Y()const{return y2;};
    //setters
    void end1X(double z){x1 = z;};
    void end1Y(double z){y1 = z;};
    void end2X(double z){x2 = z;};
    void end2Y(double z){y2 = z;};
    //functions
    bool inside(double x,double y)const{(void)x;(void)y; return 0;};
    double area()const{return 0;};
    double perimeter()const;
    void move(double x,double y){x1+=x;x2+=x;y1+=y;y2+=y;};
    //render
    void render(std::ostream &os) const;
    
private:
    double x1,y1,x2,y2;
};

class RoundBox : public Shape
{
public:
    RoundBox(Color c,double _left,double _top,double _right,double _bottom,double _r) : Shape(c){l=_left,r=_right,t=_top,b=_bottom,radi=_r;}
    ~RoundBox(){};
    //getters
    double left() const {return l;};
    double top() const{return t;};
    double right()const{return r;};
    double bottom()const{return b;};
    double radius()const{return radi;};
    //functions
    bool inside(double x,double y)const;
    double area()const;
    double perimeter()const;
    void move(double x,double y){l+=x;r+=x;t+=y;b+=y;}
    // setters
    void left(double _left){l=_left;};
    void top(double _top){t=_top;};
    void right (double _right){r=_right;};
    void bottom (double _bottom){b=_bottom;};
    void radius (double _r){radi=_r;};
    //render
    void render(std::ostream &os) const;
private:
    double t,r,l,b,radi;
};


class Group : public Shape
{
public:
    Group(Color c, int n,Shape* shps[]): Shape (c),amnt(n)
    {
        shap = new Shape*[n];
        for (int i=0; i<amnt; i++)
        {
            shap[i]=shps[i];
            shap[i]->color(c);
        }
    };
    ~Group()
    {
        for (int i=0; i<amnt; i++)
        {
            delete shap[i];
        }
        delete[] shap;
    };
    bool inside(double x,double y)const
    {
        for (int i=0; i<amnt; i++)
        {
            if(shap[i]->inside(x,y))
                return true;
        }
        return false;
    };
    double area()const
    {
        double a=0;
        for (int i=0; i<amnt; i++)
        {
            a+=shap[i]->area();
        }
        return a;
    };
    double perimeter()const
    {
        double p=0;
        for (int i=0; i<amnt; i++)
        {
            p+=shap[i]->perimeter();
        }
        return p;
    };
    void move(double x,double y)
    {
        for (int i=0; i<amnt; i++)
        {
            shap[i]->move(x,y);
        }
    };
    void color(Color c)
    {
        Shape::color(c);
        for (int i=0; i<amnt; i++)
        {
            shap[i]->color(c);
        }
    };
    void shapes(int n,Shape* shps[])
    {
        for (int i=0; i<amnt; i++)
        {
            delete shap[i];
        }
        delete[] shap;
        amnt=n;
        shap = new Shape*[n];
        for (int i=0; i<amnt; i++)
        {
            shap[i]=shps[i];
        }
        
    };
    int shapes()const{return amnt;};
    Shape* shape(int x)const{return shap[x];};
    void render(std::ostream &os) const;
private:
    int amnt;
    Shape** shap;
};

