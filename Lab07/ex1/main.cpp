#include <iostream>
using namespace std;

void displaySquare(int side = 4, char filledCharacter = '*') {
    for (int i = 1; i <= side; i++) {
        for (int j = 1; j <= side; j++)
            cout << filledCharacter;
        cout << endl;
    }
}

int main() {

    displaySquare();
    displaySquare(5, '^');

}
