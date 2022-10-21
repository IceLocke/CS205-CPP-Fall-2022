#include <iostream>

using std::cout;
using std::endl;

struct point {
    float x;
    float y;
};

void setValue(point p1, point p2, float x1, float y1, float x2, float y2) {
    p1.x = x1, p1.y = y1;
    p2.x = x2, p2.y = y2;
}

point* getMiddlePoint(point *p1, point *p2) {
    point* middle = new point();
    middle->x = (p1->x + p2->x) / 2.0f;
    middle->y = (p1->y + p2->y) / 2.0f;
    return middle;
}

int main() {

    point *a = new point(),
          *b = new point(),
          *middle;
    
    setValue(*a, *b, 1.0, 2.0, 3.0, 4.0);
    middle = getMiddlePoint(a, b);
    cout << middle->x << " " << middle->y << endl;
    delete middle;

    a->x = 1.0, a->y = 2.0, b->x = 3.0, b->y = 4.0;
    middle = getMiddlePoint(a, b);
    cout << middle->x << " " << middle->y << endl;
    delete middle;

    return 0;
}