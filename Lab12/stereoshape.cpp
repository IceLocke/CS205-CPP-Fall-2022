#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

class CStereoShape {
  private:
    static int numberOfObject;
  public:
    virtual double getArea() {return 0.0;}
    virtual double getVolumn() {return 0.0;}
    virtual void show() {}
    int getNumOfObject() {
        return numberOfObject;
    }

    CStereoShape() {
        numberOfObject++;
    }
};

int CStereoShape::numberOfObject = 0;

class CCube: public CStereoShape {
  private:
    double length, width, height;
  public:
    double getArea() {
        return 2.0 * (length * width + length * height + width * height);
    } 
    double getVolumn() {
        return length * width * height;
    }
    CCube(CCube &c) {
        length = c.length;
        width = c.width;
        height = c.height;
    }
    CCube(double len = 1.0, double wid = 1.0, double hei = 1.0): length(len), width(wid), height(hei) {}
    void show() {
        printf("Cube: %.1lf*%.1lf*%.1lf, area = %.2lf, volume = %.2lf\n", 
               length, width, height, this->getArea(), this->getVolumn());
    }
};

class CSphere: public CStereoShape {
  private:
    #define PI 3.1415926
    double radius;
  public:
    double getArea() {
        return 4.0 * PI * radius * radius;
    }
    double getVolumn() {
        return 4.0 / 3.0 * PI * radius * radius * radius;
    }
    CSphere(CSphere &c) {
        radius = c.radius;
    }
    CSphere(double r = 1.0) {
        radius = r;
    }
    void show() {
        printf("Sphere: r = %.1lf, area = %.2lf, volume = %.2lf\n", radius, this->getArea(), this->getVolumn());
    }
};

int main() {
    CCube *a_cube= new CCube(4.0, 5.0, 6.0);
    CSphere *c_sphere = new CSphere(7.9);
    CStereoShape *p = a_cube;
    p->show();
    p = c_sphere;
    p->show();
    cout << "Number of Stereo graphics: " << p->getNumOfObject() << endl;
}