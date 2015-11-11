    #include "Pokemon.h"
    #include<iostream>
     using namespace std;

     int main() {
        Pokemon my_pokemon;
        my_pokemon = Pokemon();
        my_pokemon.display();

        int attempts = 0;
        cout << my_pokemon.isshiny();
        while(!my_pokemon.isshiny());
        {
          my_pokemon = Pokemon();
          my_pokemon.display();
          ++attempts;
        }


        return 0;
     }
