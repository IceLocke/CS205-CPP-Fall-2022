#include "src/expression_phaser.cpp"
#include "src/function.cpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::cerr;

string WELCOME_TEXT = "----------\n Simple caculator v1.0 \n Copyright Gong Linghu \n Tip: Enter 'quit' (without quote) to end the program. \n---------\n";

int main() {
    cout << WELCOME_TEXT;
    string user_input;

    // init part
    expression e;
    number res;
    map<string, number> var;
    
    map<string, function<number(number)>> functions = get_functions();
    ExpressionPhaser *phaser = new ExpressionPhaser(&var, &functions);

    while (true) {
        cin >> e.str;
        if (e.str != "quit") {
            if (phaser->is_equation(e)) {
                int pos;
                for (pos = 0; pos < e.str.length(); pos++)
                    if (e.str[pos] == '=')
                        break;
                if (pos != 0) {
                    var[e.str.substr(0, pos)] = number(e.str.substr(2, e.str.length()-1));
                }
                else cerr << "No variable name!";               
            }
            else {
                res = phaser->calculate_expression(e);
                cout << res.to_string() << endl;
            }
        }
        else break;
    }

    free(phaser);

    return 0;
}
