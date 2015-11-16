
#include "Battle.h"

pair<int, string> Battle::input_main(int player) {
    Pokemon *p;
    if(player = 1)
        p = P1;
    else
        p = P2;
    string input = "-";
    while(1) {
        while(!is_int(input)) {
            p.battle_display();
            cout << "(1) Fight    (2) Bag\n"
                 << "(3) Pokemon  (4) Run\n";
            cin >> input;
            if(is_int(input)) {
                if(stoi(input) < 1 or stoi(input) > 4) {
                    input = "-";
                    cout << "Please enter a number between 1 and 4\n";
                }
            }
        }
        if(input = "1") {
            input = input_move(player);
            if(input != "-")
                return make_pair(1, input);
        }
        else if(input == "2") {
            selection = input_bag(player);
        }
        else if(input == "3") {
            selection = input_pokemon(player);
        }
        else return 4;
    }
}

string Battle::input_bag(int player) {
    return "-";
}

string Battle::input_move(int player) {
    string input = "-";
    Pokemon *p;
    if(player = 1)
        p = P1;
    else
        p = P2;
    while(!is_int(input)) {
        cls();
        p.battle_display();
        p.print_moveset();
        cout << "(5) Back\nSelection: ";
        cin >> input;
        if(is_int(input)) {
            if(stoi(input) < 1 or stoi(input) > 5) {
                input = "-";
                cout << "Please enter an integer between 1 and 5.\n";
            }
            else {
                if(input != "5") {
                    if(p->get_move(stoi(input)) == "Empty") {
                        input = "-";
                        cout << "Please select a non-empty move slot.\n";
                    }
                }
            }
        }
    }
    if(input == "5") {
        return "-";
    }
    return p.get_move(stoi(input));
}

string Battle::input_pokemon(int player) {
    return "-";
}

void Battle::Run() {
    pair<int, string> p1_move, p2_move;
    while(P1->get_current_hp()>0 and P2->get_current_hp()>0) {
        p1_move = input_main(1);
        p2_move = input_main(2);
        if(speed_calc(p1_move) >= speed_calc(p2_move)) {
            if(p1_move.first == 1) {
                //Player1's pokemon is attacking with the move named p1_move.second
                //Everything that entails needs to be implemented
                //Make sure to include the case where players2's pokemon faints
                //This code will change slightly when we've made a team class
                //The team class will have 6 pokemon slots and will just make interacting with a team easy
            }
        }
    }
}

void Battle::cls() {
    cout << string(60, '\n');
}
