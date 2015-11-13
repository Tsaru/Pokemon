    #include "Pokemon.h"
    #include<iostream>
    #include<windows.h>
     using namespace std;

     int main() {
        string name = "Pikachu";
        int attempts = 0;
        Pokemon *my_pokemon;
        my_pokemon = new Pokemon(name, attempts++);
        my_pokemon->display();

        /*while(!my_pokemon->isshiny()) {
            //cin >> value;
            delete my_pokemon;
            my_pokemon = new Pokemon(name, attempts);
            my_pokemon->display();
            cout << "\n======================\n"<< "Attempts: " << ++attempts << "\n======================\n";
        }*/
        return 0;
     }
