
#include "Pokemon.h"

class Battle {

    private:
        Pokemon *P1;
        Pokemon *P2;

    public:
        void Run_Battle();
        Battle(Pokemon *Poke1, Pokemon *Poke2);

};
