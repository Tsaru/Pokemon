
#include<vector>
#include<string>
#include<utility>
#ifndef _Pokemon_
#define _Pokemon_

using std::string;
using std::vector;
using std::pair;

class Pokemon {

    private:
        string species_name;
        int pokedex_number;
        int gender;
        int level;
        int exp_yield;
        int leveling_speed;
        int evolves_at;
        string evolves_to;
        vector<string> type;
        int nature [2];
        bool shiny;
        vector<string> moveset;
        vector<pair<int, string>> learnset;
        string held_item;
        int current_hp;
        int current_xp;
        int catch_rate;
        string status;
        string ability;
        int max_hp;
        int attack;
        int defense;
        int sp_attack;
        int sp_defense;
        int speed;
        int iv_hp;
        int iv_attack;
        int iv_defense;
        int iv_sp_attack;
        int iv_sp_defense;
        int iv_speed;
        int base_hp;
        int base_attack;
        int base_defense;
        int base_sp_attack;
        int base_sp_defense;
        int base_speed;
        void set_stats();
        void Open_Base_Pokemon(string, int);
        void progress_bar(int value, int total, int length = 40);
        int exp_for_level(int);
        void level_up();

    public:
        int get_gender(){return gender;}
        int get_level(){return level;}
        bool get_shininess(){return shiny;}
        int get_current_hp(){return current_hp;}
        int get_current_xp(){return current_xp;}
        string get_ability(){return ability;}
        string get_status(){return status;}
        vector<string> get_moveset(){return moveset;}
        int get_attack(){return attack;}
        int get_defense(){return defense;}
        int get_sp_attack(){return sp_attack;}
        int get_sp_defense(){return sp_defense;}
        int get_speed(){return speed;}
        string get_move(int slot) {return moveset[slot-1];}
        vector<string> get_type(){return type;}
        //Pokemon();
        Pokemon(string, int);
        Pokemon(string species_name, int gender, int level, bool shiny, int current_hp, int current_xp, string ability,
                string status_condition, vector<string> moveset, int attack, int defense, int sp_attack, int sp_defense,
                int speed);
        void add_exp(int);
        void full_display();
        void battle_display();
        void display();
        void print_moveset();
        void print_learnset();
        void print_ivs();
        bool isshiny() { return shiny;}
};

int stoi(std::string input);

bool is_int(std::string text);

#endif
