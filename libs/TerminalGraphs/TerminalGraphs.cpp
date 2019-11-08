#include "TerminalGraphs.h"

Point::Point(int x, int y){
    X = x;
    Y = y;
    name = "point(" + x + ',' + y + ')';
}
Point::Point(int x, int y, std::string n){
    X = x;
    Y = y;
    name = n;
    hasName = true;
}
bool Point::at(int x, int y){
    if(x == X && y == Y)
        return true;
    else
        return false;
}

Vector::Vector(Point *p1, Point *p2){
    P1 = p1;
    P2 = p2;
}

// public
Panel::Panel(int w, int h){
    height = h;
    width = w;
    // super hacky workaround cause i dont know the actual way to do this
    for(int y = 0; y < h; y++){
        std::vector<char> temp(w, ' ');
        panelArr.push_back(temp);
    }
}
Panel::Panel(int w, int h, char brdr, char pnt, char vect){
    height = h;
    width = w;
    borderChar = brdr;
    pointChar = pnt;
    vectChar = vect;
    // super hacky workaround cause i dont know the actual way to do this
    for(int y = 0; y < h; y++){
        std::vector<char> temp(w, ' ');
        panelArr.push_back(temp);
    }
}  
// Panel(int w, int h, bool labels){
//     // added 2 to account for border on each side of panel
//     width = w + 2;
//     height = h + 2;
//     panelArr = new char[height, width];
//     showLabels = labels;
// }
void Panel::add(Point &p){ points.push_back(p); }
// void add(Label l){ labels.push_back(l); }
// void add(Square s){
//     for(auto p : s.points){
//         points.push_back(p);
//     }
//     for(auto v : s.vectors){
//         vectors.push_back(v);
//     }
// }
void Panel::connectPoints(Point & p1, Point & p2){
    // TODO: check if this is correct syntax for adding new vector
    if(checkBothPointsPresent(p1,p2)){
        Vector v = Vector(&p1,&p2);
        vectors.push_back(v);
    }
}
void Panel::Display(){
    system("clear");
    Draw();
    for( int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            std::cout << panelArr[y][x];
        }
        std::cout << std::endl;
    }
}
// private
bool Panel::checkPointPresent(Point pointGiven){
    bool match = false;
    for(auto p : points){
        if(p.getX() == pointGiven.getX() && p.getY() == pointGiven.getY())
            match = true;
    }
    return match;
}
bool Panel::checkBothPointsPresent(Point p1, Point p2){ 
    return checkPointPresent(p1) && checkPointPresent(p2);
}
bool Panel::checkConnected(Point & p1, Point & p2){
    bool match = false;
    for(auto v : vectors){
        if(checkPointsEqual(v.getP1(), &p1) && checkPointsEqual(v.getP2(), &p2))
            match = true;
    }
    return match;
}

bool Panel::checkPointsEqual(Point *p1, Point *p2){
    if(p1->getX() == p2->getX() && p1->getY() == p2->getY()){
        return true;
    } else {
        return false;
    }
}
void Panel::DrawPoints(){
    for(auto p : points){
        panelArr[p.getY()][p.getX()] = pointChar;
        if(p.hasName){
            int x = p.getX() + 1;
            for(auto c : p.getName()){  
                if(x >= width-1){
                    break;
                } else {
                    panelArr[p.getY()][x] = c;
                    x++;
                }
            }
        }
    }
}
void Panel::DrawVectors(){
    for(auto v : vectors){
        Point *p1 = v.getP1();
        Point *p2 = v.getP2();
        int steps;
        float x = p1->getX();
        float y = p1->getY();
        float Xincr = 0;
        float Yincr = 0;
        // work out difference
        int dx = p2->getX() - p1->getX();
        int dy = p2->getY() - p1->getY();
        // in order to work out steps we need non zero, posotive integer values for dx and dy (largest unsigned integer value)
        // work out steps needed (pixels needed)
        if(abs(dx) > abs(dy)) {
            steps = dx;
        } else { 
            steps = dy;
        }
        // if steps is negative convert to positive (steps is never negative)
        if(steps < 0){
            steps *= -1;
        }
        // calculate x and y increments
        Xincr = (float)dx / (float)steps;
        Yincr = (float)dy / (float)steps;
        // draw vector
        for (int i = 0; i < steps-1; i++){  // -1 so end point is not overwritten
            x += Xincr;
            y += Yincr;
            panelArr[(int)y][(int)x] = vectChar;   
        }
    }
}
// void Panel::DrawLabels(){
//     int x,y;
//     foreach(Label l in labels){
//         x = l.X;
//         y = l.Y;
//         foreach(char c in l.value){
//             if(c == '\n'){ 
//                 y += 1;
//                 x = l.X;
//                 continue;
//             }
//             if(x >= width-1){
//                 break;
//             } else {
//                 panelArr[y,x] = c;
//                 x++;
//             }    
//         }
//     }    
// }
void Panel::DrawBlankPanel(){
    for( int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(x == 0 || x == width-1 || y == 0 || y == height-1){
                panelArr[y][x] = borderChar;
            } else {
                panelArr[y][x] = blankChar;
            }
        }
    }
}
void Panel::Draw(){
    // draw panel
    DrawBlankPanel();
    // draw any shapes that are present
    DrawPoints();
    DrawVectors();
    if(showLabels){
        //DrawLabels();
    }
}
void Panel::toggleLabels(){ showLabels = !showLabels;}