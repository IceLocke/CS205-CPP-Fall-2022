#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class OutOfRangeException {
public:
    int parameter, value;
    OutOfRangeException(int para = 0, int v = 0) {
        parameter = para;
        value = v;
    }
};

double caculateAverage() {
    int sum = 0;
    OutOfRangeException *e = NULL;
    for (int i = 1, t; i <= 4; i++) {
        cin >> t;
        if (t < 0 || t > 100)
            if (!e)
                e = new OutOfRangeException(i, t);
        sum += t;
    }
    if (e) throw *e;
    else return 1.0 * sum / 4.0;
}

int main() {

    char op;

    while (true) {
        cout << "Please enter marks for 4 courses: ";
        try {
            double res = caculateAverage();
            cout << "Averange is " << res << endl;
        }
        catch (OutOfRangeException &e) {
            cout << "The parameter " << e.parameter << " is " << e.value << " is out of range." << endl;
        }
        cout << "Enter another 4 marks? (y/n) ";
        cin >> op;
        if (op == 'y') continue;
        else if (op == 'n') break;
    }

    return 0;
}