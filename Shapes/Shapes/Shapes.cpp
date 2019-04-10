//
//  main.cpp
//  Ass4 (Shapes)
//
//  Created by Charlie  Velazquez on 9/22/16.
//  Copyright © 2016 GoonPlatoon. All rights reserved.
//

#include <iostream>
#include "Shapes.h"
#include <sstream>
#include <cassert>
using namespace std;
std::string const names[] = {"BLACK","RED","GREEN","YELLOW","BLUE","MAGENTA","CYAN","WHITE","INVALID"};

//absolute value function
double abso(double x)
{
    if (x<0)
        return x *=-1;
    return x;
}
//print the attibutes of a given Box (color,left,top,right,bottom)
void Box:: render(std::ostream &os) const
{
    os<<"Box("<< names[color()]<<","<<l<<","<<t<<","<<r<<","<<b<<")";
}
//print the attibutes of a given Circle (color,center_x,center_y,radius)
void Circle:: render(std::ostream &os) const
{
    os<<"Circle("<< names[color()]<<","<<cx<<","<<cy<<","<<r<<")";
}
//print the attibutes of a given Triangle (color,vertex1_x,vertex1_y,vertex2_x,vertex2_y,vertex3_x,vertex3_y)
void Triangle:: render(std::ostream &os) const
{
    os<<"Triangle("<< names[color()]<<","<<v1x<<","<<v1y<<","<<v2x<<","<<v2y<<","<<v3x<<","<<v3y<<")";
}
//print the attibutes of a given Line (color,point1_x,point1_y,point2_x,point2_y)
void Line:: render(std::ostream &os) const
{
    os<<"Line("<< names[color()]<<","<<x1<<","<<y1<<","<<x2<<","<<y2<<")";
}
//print the attibutes of a given Polygon (color,vertex_count,verticies[x],verticies[y]...)
void Polygon::render(std::ostream &os) const
{
    os << "Polygon(" << names[color()] << "," << vertCount;
    for (int i = 0; i < (vertCount*2); i++)
    {
        os << "," << vertices[i];
    }
    os << ")";
}
//print the attibutes of a given RoundBox (color,left,top,right,bottom,radius)
void RoundBox:: render(std::ostream &os) const
{
    os<<"RoundBox("<< names[color()]<<","<<l<<","<<t<<","<<r<<","<<b<<","<<radi<<")";
}

void Group:: render(std::ostream &os) const
{
    os<<"Group("<< names[Shape::color()]<<","<<amnt;
    for (int i=0; i<amnt; i++)
    {
        os<<",";
        shap[i]->render(os);
    }
    os<<")";
}

double Triangle::perimeter()const
{
    
    double dx1 = abso(v2x-v1x)*abso(v2x-v1x);       //finds the length of one side of triangle a
    double dy1 = abso(v2y-v1y)*abso(v2y-v1y);       //finds the length of another side of triangle a
    double dx2 = abso(v3x-v1x)*abso(v3x-v1x);       //finds the length of one side of triangle b
    double dy2 = abso(v3y-v1y)*abso(v3y-v1y);       //finds the length of another side of triangle b
    double dx3 = abso(v2x-v3x)*abso(v2x-v3x);       //finds the length of one side of triangle c
    double dy3 = abso(v2y-v3y)*abso(v2y-v3y);       //finds the length of another side of triangle c
    double a = sqrt(dx1+dy1);                       //finding the hypotenuse of dx1 and dy1 - side a
    double b = sqrt(dx2+dy2);                       //finding the hypotenuse of dx2 and dy2 - side b
    double c = sqrt(dx3+dy3);                       //finding the hypotenuse of dx3 and dy3 side a
    return (a+b+c);
}
double Triangle:: area()const
{
    //first find the height - largest difference between y coordinates
    double h,b;
    double h1 = abso(v1y-v2y);
    double h2 = abso(v1y-v3y);
    double h3 = abso(v2y-v3y);
    if ((h1>=h2) && (h1>=h3))
        h = h1;
    else if ((h2>=h1) && (h2>=h3))
        h = h2;
    else if ((h3>=h1) && (h3>=h2))
        h = h3;
    //then find the base - largest difference between x coordinates
    double b1 = abso(v1x-v2x);
    double b2 = abso(v1x-v3x);
    double b3 = abso(v2x-v3x);
    if ((b1>=b2) && (b1>=b3))
        b = b1;
    else if ((b2>=b1) && (b2>=b3))
        b = b2;
    else if ((b3>=b1)&&(b3>=b2))
        b = b3;
    //area of a triangle formula
    return (.5*(b*h));
}

Polygon::Polygon(Color c, double* pts,int v):Shape(c)
{
    //allocate an array to hold the given verticies
    vertices = new double[v*2];
    for (int i = 0; i < v*2; i++)
    {
        vertices[i] = pts[i];
    }
    vertCount = v;
}

void Polygon::move(double dx, double dy)
{
    //move each of the x vertecies
    for (int i=0; i<vertCount*2; i=i+2)
    {
        vertices[i] = vertices[i]+dx;
    }
    //then move the y verticies
    for (int i=1; i<vertCount*2; i=i+2)
    {
        vertices[i] = vertices[i]+dy;
    }
}

double Polygon::area() const
{
    //Paul Bourkes method
    double a = 0;
    int i = 0;
    for (; i < (vertCount*2)-2; i += 2)
    {
        a+= (vertices[i]*vertices[i+3])-(vertices[i+2]*vertices[i+1]);
    }
    a += (vertices[i]*vertices[1])-(vertices[i+1]*vertices[0]);
    return abso(a/2);
}

double Polygon::perimeter() const
{
    double peri = 0;
    int i = 0;
    //loop through each point and find the distance between each consecutive point and add them.
    for (; i < (vertCount*2)-2; i+=2)
    {
        peri +=sqrt(pow((vertices[i] - vertices[i+2]), 2)+(pow((vertices[i+1] - vertices[i+3]), 2))); //distance formula
    }
    //distance between first point and last point
    peri +=sqrt(pow((vertices[i] - vertices[0]), 2)+(pow((vertices[i+1] - vertices[1]), 2)));
    return peri;
}


bool Box::inside(double x,double y) const
{
    if (x<l || x>r || y<b || y>t)
    {
        return false;
    }
    else
        return true;
    
}
bool Circle::inside(double x,double y) const
{
    double a = abso(x-cx);
    double b = abso(y-cy);
    double c = sqrt((a*a)+(b*b));
    //uses the distance formula to determine whether the distance between the point and
    //the center of the circle are greater than or less than the radius.
    if (c >= r)
    {
        return false;
    }
    return true;
}

double AA(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return abso((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

bool Triangle::inside(double _x, double _y) const
{
    //used ktodisco's (stackoverflow) method of calculating whether a point is inside a triangle given the coordinates.
    //    double alpha = ((v2y - v3y)*(_x - v3x) + (v3x - v2x)*(_y - v3y)) /
    //    ((v2y - v3y)*(v1x - v3x) + (v3x - v2x)*(v1y - v3y));
    //    float beta = ((v3y - v1y)*(_x - v3x) + (v1x - v3x)*(_y - v3y)) /
    //    ((v2y - v3y)*(v1x - v3x) + (v3x - v2x)*(v1y - v3y));
    //    double gamma = 1.0f - alpha - beta;
    //    if (gamma>0 && alpha>0 && beta>0)
    //        return true;
    //    return false;
    double A = AA(v1x,v1y,v2x,v2y,v3x,v3y); //area of the triangle
    double A1 = AA(_x,_y,v2x,v2y,v3x,v3y);  //area of a triangle using given points as the values for the 1st point
    double A2 = AA(v1x,v1y,_x,_y,v3x,v3y);  //area of a triangle using given points as the values for the 2nd point
    double A3 = AA(v1x,v1y,v2x,v2y,_x,_y);  //area of a triangle using given points as the values for the 3rd point
    //    if the sum of the three (sub)areas of the triangle is == the the area of the triangle then the point is inside
    return (A == A1 + A2 + A3);
}
bool Polygon::inside(double _x, double _y) const
{
    int i, j, c = 0;
    for (i = 0, j = vertCount-1; i < vertCount; j = i++) {
        if (((vertexY(i)>_y)!=(vertexY(j)>_y))&&(_x<(vertexX(j)-vertexX(i))*(_y-vertexY(i))/(vertexY(j)-vertexY(i))+vertexX(i)))
            c = !c;
    }
    return c;
}
//same function used to find the hypotenuse given two points(x,y)
double Line:: perimeter() const
{
    double a = abso(x2-x1);
    double b = abso(y2-y1);
    double c = sqrt((a*a)+(b*b));
    return c;
}
double RoundBox:: area()const
{
    double len = abso(r-l);
    double wid = abso(t-b);
    double a1 = len*wid;                //first find the area of the box without rounded corners.
    double a2 = (radi*2)*(radi*2);      //find the area of a box with the same radius as the corners
    double a3 = (pi)*(radi*radi);       //find the area of a circle given the radius
    //(-)the area of the smallbox from the big box, then (+) the result to the area of the circle(a3).
    return (a1-a2)+a3;
    
    //    same function in one line
    //    return (2*(len-(2*radi)*radi))+(2*(wid-(2*radi)*radi))+ pi*(radi*radi)+((len-(2*radi))*(wid-(2*radi)));
}
double RoundBox:: perimeter() const
{
    double len = abso(r-l);
    double wid = abso(t-b);
    double p1 = (2*len)+(2*wid);        //first find the perimeter of the box without rounded corners.
    double p2 = 8*radi;                 //find the perimeter of a box with the same radius as the corners
    double OOP = 2*pi*radi;             //find the perimeter of a circle given the radius
    //(-)the perimeter of the smallbox from the big box, then (+) the result to the perimeter of the circle(a3).
    return (p1-p2)+OOP;
    
    //    same function in one line
    //    return (2*(len-(2*radi)))+(2*(wid-(2*radi)))+(2*pi*radi);
}

//function to calculate the inside of a circle -- used in RoundBox.inside
bool insideCircle(double x,double y,double cx,double cy,double r)
{
    double a = abso(x-cx);
    double b = abso(y-cy);
    double c = sqrt((a*a)+(b*b));
    if (c >= r)
    {
        return false;
    }
    return true;
}
bool RoundBox:: inside(double x,double y)const
{
    //check if its outside the box (no rounded corners)
    bool flag = false;
    if (x>r || y>t || x<l || y<b)
    {
        return false;
    }
    //check inside height box
    if ((x<(r-radi)) && (x>(l+radi)) && (y<t) && (y>b))
    {
        return true;
    }
    //check inside width box
    if ((x<r) && (x>l) && (y<(t-radi)) && (y>(b+radi)))
    {
        return true;
    }
    
    if (x>(r-radi) && y>(t-radi))
    {
        //top right circle of the RRectangle
        if (insideCircle(x, y, (r-radi), (t-radi), radi))
            flag = true;
    }
    else if (x>(r-radi) && y<(b+radi))
    {
        //bottom right circle of the RRectangle
        if(insideCircle(x, y, (r-radi), (b+radi), radi))
            flag = true;
    }
    else if (x<(l+radi) && y>(t-radi))
    {
        //top left circle of the RRectangle
        if (insideCircle(x, y, (l+radi), (t-radi), radi))
            flag = true;
    }
    else if (x<(l+radi) && y<(b+radi))
    {
        //bottom left circle of the RRectangle
        if (insideCircle(x, y, (l+radi), (b+radi), radi))
            flag = true;
    }
    return flag;
}
//given an array of shapes, check if the given coordinates lie w/in each shape, if they do return the color of that shape.
Color Shape::colorAtPoint(Shape* shps[],int num,double X,double Y)
{
    for (int i=0; i<num; i++)
    {
        if (shps[i]->inside(X, Y))
            return shps[i]->color();
    }
    return INVALID;
}

//***********************for_testing************************
int main()
{
//    Box b(BLUE,1,4,3,2);
//    Circle c(BLUE,1,2,3);
//    Triangle t(BLUE,1,2,3,4,3,2);
//    double pts[] = {1,2,3,5,5,6,5,3,4,1};
//    Polygon p(BLUE,pts,5);
//    RoundBox rb(WHITE,0,3,4,0,1);
//    Shape * shapes[2];
//    shapes[0] = new Box(BLUE,0,1,2,0);
//    shapes[1] = new Circle(RED,-1,-1,1);
//    Group g(RED,2,shapes);
//    assert(g.inside(1,.5));
//    Box b(BLUE,1,4,3,2);
//    Circle c(BLUE,1,2,3);
//    Triangle t(BLUE,1,2,3,4,3,2);
//    double pts[] = {1,2,3,4,5,6,7,8,9,10};
//    Polygon p(BLUE,pts,5);
//    Box bb(BLUE,0,1,1,0);
//    Circle cc(BLACK,5,5,2);
//    Triangle tt(RED,0,0,10,0,0,1);
//    double pts2[] = {0,0,1,0,1,1, 0,2,0,1};
//    Polygon pp(YELLOW,pts2,5);
//    RoundBox rb(WHITE,0,3,4,0,1);
//    Shape * shapes[5];
//    shapes[0] = new Box(BLUE,1,4,3,2);
//    shapes[1] = new Circle(BLUE,1,2,3);
//    shapes[2] = new Triangle(BLUE,1,2,3,4,3,2);
//    shapes[3] = new Polygon(BLUE,pts,5);
//    shapes[4] = new RoundBox(WHITE,0,3,4,0,1);
//    double atotal = 0;
//    double ptotal = 0;
//    for(int i = 0; i < 5; i++)
//    {
//        atotal += shapes[i]->area();
//        ptotal += shapes[i]->perimeter();
//    }
//    Group g(RED,5,shapes);
//    assert(fabs(g.thickness()-(atotal/ptotal)) < 0.0000001);
//    std::string name[]={"BLACK","RED","GREEN","YELLOW","BLUE","MAGENTA","CYAN","WHITE"};
//    for (int i=0; i<8; i++) {
//        Color j = (Color)((i+1)%8);
//        Shape * s1[]={new Box(RED,2,5,9,3),new Circle(CYAN,2,2,2)};
//        Group * g = new Group((Color)i,2,s1);
//        std::stringstream ss;
//        g->render(ss);
//        g->color(j);
//        ss.str("");
//        g->render(ss);
//        Shape * s2[]={new Box(CYAN,1,2,2,1),g,new RoundBox(CYAN,2,2,2,2,2)};
//        Group h((Color)i,3,s2);
//        ss.str("");
//        h.render(ss);
//        
//        cout << ss.str() << endl;
//        cout << "Group(" + name[i] + ",3,Box(" + name[i] + ",1,2,2,1),Group(" + name[i] + ",2,Box("+name[i]+",2,5,9,3),Circle("+name[i]+",2,2,2)),RoundBox("+name[i]+",2,2,2,2,2))" << endl;
//        cout<<endl;
//        cout<<endl;
//        assert(ss.str() == "Group(" + name[i] + ",3,Box(" + name[i] + ",1,2,2,1),Group(" + name[i] + ",2,Box("+name[i]+",2,5,9,3),Circle("+name[i]+",2,2,2)),RoundBox("+name[i]+",2,2,2,2,2))");
//        h.color(j);
//        ss.str("");
//        h.render(ss);
//    }
//    Shape * list[2];
//    list[0] = new Box(GREEN, 0, 1, 1, 0);
//    list[1] = new Circle(YELLOW, 2, 2, 2);
//    Group g(BLUE, 2, list);
//    
//    cout << "Group area: " << g.area() << "\n";
//    cout << "Group perimeter: " << g.perimeter() << "\n";
//    
//    g.move(1,1);
//    g.render(cout); cout << "\n";
//    g.color(RED);
//    g.render(cout); cout << "\n";
//    
//    cout << "Count: " << g.shapes() << "\n";
//    g.shape(1)->render(cout); cout << "\n";
//    
//    Shape * list2[3];
//    list2[0] = new Circle(WHITE,5,5,1);
//    list2[1] = new Box(GREEN,7,1,9,-10);
//    list2[2] = new RoundBox(BLACK,5,5,8.5,4.5,0.1);
//    g.shapes(3,list2);
//    g.render(cout); cout << "\n";
//    RoundBox rb(WHITE,0,3,4,0,1);
//    assert(rb.inside(2.5,2.5));
//    Box b(BLUE,1,2,3,4);
//    Circle c(BLUE,1,2,3);
//    Triangle t(BLUE,1,2,3,4,5,6);
//    b.left(4);
//    b.top(3);
//    b.right(2);
//    b.bottom(1);
//    std::cout<<b.inside(5,5)<<std::endl;
//    c.centerX(3);
//    c.centerY(1);
//    c.radius(2);
//    std::cout<<c.inside(1, 1)<<std::endl;
//    std::cout<<true<<std::endl;
//    t.cornerX1(6);
//    t.cornerY1(5);
//    t.cornerX2(4);
//    t.cornerY2(3);
//    t.cornerX3(2);
//    t.cornerY3(1);
//    static double pts[] = {1,2,3,4,5,6,7,8,9,10};
//    Polygon p(BLUE,pts,5);
//    std::cout<<p.vertexY(0)<<std::endl;
//    assert(p.vertexY(0) == 2);
//    Box b(RED,1,5,3,-1);            // left, top, right, bottom bounds of the box
//    b.left(2.5);                    // set/get box's left side coordinate
//    double left = b.left();         // similar for: right, top, bottom
//    left = left;
//    double area = b.area();         // get the area of a shape
//    double peri = b.perimeter();    // get the perimeter distance of a shape
//    b.render(cout);
//    std::cout<<"l :"<<b.left()<<std::endl;
//    std::cout<<"r :"<<b.right()<<std::endl;
//    std::cout<<"b :"<<b.bottom()<<std::endl;
//    std::cout<<"t :"<<b.top()<<std::endl;
//    std::cout<<area<<std::endl;
//    std::cout<<peri<<std::endl;
//    b.move(3,-1.5);
//    b.render(cout);
//    Circle c(BLUE,3,4,2.1);         // center-x, center-y, radius
//    c.centerX(2.5);                 // set/get circle's center-x coordinate
//    double cx = c.centerX();        // similar for: circleY, radius
//    cout<<cx<<endl;
//    c.render(cout);                 // should print: Circle(BLUE,2.5,4,2.1)
//    Triangle t(WHITE,1,1,5,1,3,3);  // x,y for each corner
//    t.cornerX1(2.5);                // set/get triangles's corner-x-1 coordinate
//    double cx1 = t.cornerX1();      // similar for X/Y, and 1/2/3
//    std::cout<<cx1<<std::endl;
//    std::cout<<"perimeter"<<t.perimeter()<<std::endl;
//    std::cout<<"area"<<t.area()<<std::endl;
//    t.render(std::cout);               // should print: Triangle(WHITE,1,1,5,1,3,3)
//    std::cout<<t.inside(4.99,1.001)<<std::endl;
//    double pts[] = {1,1,5,1,3,3};
//    Polygon p(BLACK,pts,3);         // array contains x,y for each corner
//    int z = p.points();             // get polygon's vertex count
//    std::cout<<z<<std::endl;
//    p.vertexX(2,4.5);               // set/get third vertex's x-coordinate to 4.5
//    double x = p.vertexX(2);        // similar for: vertexY
//    std::cout<<x<<std::endl;
//    std::cout<<p.area()<<std::endl;
//    p.render(std::cout);
//    std::cout<<p.inside(4, 2)<<std::endl;// should print: Polygon(BLACK,3,1,1,5,1,4.5,3)
//    RoundBox DD(BLACK,0,2,4,0,1);
//    std::cout<<DD.area()<<std::endl;
//    std::cout<<DD.perimeter()<<std::endl;
//    std::cout<<DD.inside(3.5,.5)<<std::endl;
//    std::cout<<DD.inside(3.75,.25)<<std::endl;
}
