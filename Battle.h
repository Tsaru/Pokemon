
#include "Pokemon.h"

#ifndef _Battle_
#define _Battle_

class Battle {

    private:
        Pokemon *P1;
        Pokemon *P2;
        pair<int, string> input_main(int);
        string input_bag(int);
        string input_move(int);
        string input_pokemon(int);
        void main_menu();
        void cls();
        int speed_calc(pair<int, string>);

    public:
        void Run();
        Battle(Pokemon *Poke1, Pokemon *Poke2);

};

#endif // _Battle_
