#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Point{
    std::string name = "";
    int X = 0;
    int Y = 0;
    public:
        bool hasName = false;
        int getX(){ return X;}
        int getY(){ return Y;}
        void setX(int x){ X = x; }
        void setY(int y){ Y = y; }
        std::string getName(){ return name; }  
        Point() = default;
        Point(int, int);
        Point(int x, int y, std::string n);
        bool at(int, int);
};

class Vector{
    Point *P1;
    Point *P2;
    public:
        Point *getP1(){ return P1;}
        Point *getP2(){ return P2;}
        Vector() = default;
        Vector(Point *, Point *);
};

class Label{

};

class Panel{
    bool showLabels = true;
    int width = 0;
    int height = 0;
    std::vector<std::vector<char>> panelArr;
    std::vector<Point> points; 
    std::vector<Vector> vectors;
    std::vector<Label> labels;
    char borderChar = '#';
    char blankChar = ' ';
    char pointChar = '@';
    char vectChar = '~'; 

    public:
        Panel(int w, int h);
        Panel(int w, int h, char brdr, char pnt, char vect);
        int getWidth(){return width; };
        int getHeight(){return height; };
        // Panel(int w, int h, bool labels);
        void add(Point &);
        // void add(Label l);
        // void add(Square s);
        bool checkPointPresent(Point);
        bool checkConnected(Point &, Point &);
        bool checkPointsEqual(Point *, Point *);
        void connectPoints(Point &, Point &);
        void Display();

    private:
        bool checkBothPointsPresent(Point, Point);
        void DrawPoints();
        void DrawVectors();
        // void DrawLabels();
        void DrawBlankPanel();
        void Draw();
        void toggleLabels();      
};
