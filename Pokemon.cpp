
#include "Pokemon.h"
#include<random>
#include<chrono>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

int stoi(string input) { //string to int.
    int Result;
    std::stringstream convert(input);
    if ( !(convert >> Result) )
        Result = -1;
    return Result;
}

bool is_int(string text) { //check if a number is a legal integer.
    if(text.size()==0) { return false; }
    for(int i = 0; i < text.size(); ++i)
        if(!isdigit(text[i]) && (i!=0 || text[0]!='-' || text.size()<2)) {
            return false;
        }
    return true;
}

void Pokemon::Open_Base_Pokemon(string name, int seed_mod) {
    string value = "-";
    std::ifstream file;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + seed_mod;
    std::mt19937 random_num(seed);
    file.open("Pokemon.txt");

    //Remove the format lines
    while(value.size() != 0) {
        getline(file, value);
    }

    //find the correct line
    file >> value;
    while(value != name) {
        while(!file.eof() and value.size() != 0) {
            getline(file, value);
        }
        file >> value;
    }

    //Get the basic values
    species_name = name;
    file >> value;
    pokedex_number = stoi(value);
    file >> value;
    base_hp = stoi(value);
    file >> value;
	base_attack = stoi(value);
    file >> value;
	base_defense = stoi(value);
    file >> value;
	base_sp_attack = stoi(value);
    file >> value;
	base_sp_defense = stoi(value);
    file >> value;
	base_speed = stoi(value);
	file >> value;
	catch_rate = stoi(value);
	file >> value;
	exp_yield = stoi(value);
	file >> value;
	leveling_speed = stoi(value);
	file >> value;
	evolves_at = stoi(value);
	file >> value;
	evolves_to = value;

    //Get the type(s)
    type.clear();
    getline(file, value);
	while(file.peek() != '\n') {
        file >> value;
        type.push_back(value);
	}

	//Get the abilities and choose a random ability
	getline(file, value);
	if(random_num()%150 == 0) {
        getline(file, value);
        getline(file, value);
        ability = value;
	} else {
	    vector<string> temp_abilities;
	    temp_abilities.clear();
	    while(file.peek() != '\n') {
            file >> value;
            if(value[0] == '"') {
                temp_abilities.push_back(value.substr(1, value.size()));
                file >> value;
                while(value[value.size()-1] != '"') {
                    temp_abilities[-1] += " " + value;
                    file >> value;
                }
                temp_abilities[1] += " " + value.substr(0, value.size()-1);
            } else { temp_abilities.push_back(value);}
	    }
        ability = temp_abilities[random_num()%temp_abilities.size()];
        getline(file, value);
        getline(file, value);
	}
	learnset.clear();
	while(!file.eof() and file.peek()!='\n') {
        file >> value;
        learnset.push_back(make_pair(stoi(value), ""));
        getline(file, value);
        learnset[learnset.size()-1].second = value;
	}
	file.close();
}

Pokemon::Pokemon(string name, int seed_mod) {
    Open_Base_Pokemon(name, seed_mod);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count()+seed_mod;
    std::mt19937 random_num(seed+1);

	iv_hp = random_num()%32;
	iv_attack = random_num()%32;
	iv_defense = random_num()%32;
	iv_sp_attack = random_num()%32;
	iv_sp_defense = random_num()%32;
	iv_speed = random_num()%32;

	shiny = 0;
	if(random_num()%8192 == 0) {
        shiny = 1;
	}
	nature[0] = random_num()%5+1;
	nature[1] = random_num()%5+1;
	while(nature[0]==nature[1]) {
        nature[1] = random_num()%5+1;
	}

	level = random_num()%100+1;

	set_stats();
	current_hp = max_hp;
	current_xp = exp_for_level(level);
	gender = random_num()%2;
	held_item.clear();
	held_item = "Empty";
	status = "";
	moveset.push_back("Empty");
	moveset.push_back("Empty");
	moveset.push_back("Empty");
	moveset.push_back("Empty");
	for(auto i = learnset.begin(); i != learnset.end(); ++i) {
        if(i->first <= level) {
            moveset.erase(moveset.begin());
            moveset.push_back(i->second);
        }
        else break;
	}
}

void Pokemon::set_stats() {
    max_hp = base_hp + base_hp/50*level + iv_hp;
    attack = base_attack + base_attack/50*level + iv_attack;
    defense = base_defense + base_defense/50*level + iv_defense;
    sp_attack = base_sp_attack + base_sp_attack/50*level + iv_sp_attack;
    sp_defense = base_sp_defense + base_sp_defense/50*level + iv_sp_defense;
    speed = base_speed + base_speed/50*level + iv_speed;
}

void Pokemon::level_up() {
    if(level < 100) {
        level += 1;
        for(auto i = learnset.begin(); i != learnset.end(); ++i) {
            if(i->first == level) {
                string selection = "";
                cout << species_name << " is learning a new move!\n";
                print_moveset();
                cout << "(5) " << i->second << endl;
                do {
                    cout << "Please choose a move to forget (or 5 to stop learning " << i->second << ")\n"
                         << "Selection: ";
                    cin >> selection;
                    if(is_int(selection)) {
                        if(stoi(selection) < 0 or stoi(selection) > 5) {
                            selection = "-";
                        }
                    }
                    if(!is_int(selection)) {
                        cout << "Valid input is an integer between 1 and 5.\n";
                    }
                } while(!is_int(selection));
                if(stoi(selection) != 5) {
                    cout << species_name << " forgot " << moveset[stoi(selection)-1]
                         << " and learned " << i->second << "!\n";
                    moveset[stoi(selection)-1] = i->second;

                }
                else {
                    cout << species_name << " stopped trying to learn " << i->second << ".\n";
                }
            }
        }
    }
}

void Pokemon::add_exp(int exp) {
    current_xp += exp;
    while(current_xp >= exp_for_level(level + 1)) {
        level_up();
    }
}

int Pokemon::exp_for_level(int level) {
    if(leveling_speed == 1) {
        return 5*level*level*level/4;
    }
    if(leveling_speed == 2) {
        return 6*level*level*level/5-15*level*level+100*level-140;
    }
    if(leveling_speed == 3) {
        return level*level*level;
    }
    if(leveling_speed == 4) {
        return 4*level*level*level/5;
    }
    return 0;
}

void Pokemon::progress_bar(int value, int total, int length) {
    int progress = (((double) value)/((double) total)*((double) length));
    cout << "<";
    while(--length > 0) {
        if(--progress > 0) {
            cout << (char) 219;
        } else {
            cout << " ";
        }
    }
    cout << ">";
}

void Pokemon::battle_display() {


    cout << species_name << " " << (char) (12-gender) << "    Lvl " << level << endl
         << "   HP ";
    progress_bar(current_hp, max_hp);
    cout << "\n                 " << current_hp << "/" << max_hp << endl;
}

void Pokemon::display() {
    cout << "Lvl " << level << " " << species_name << "  " << (char) (12-gender) << endl;
    cout << "HP: " << current_hp << "/" << max_hp << "  ";
    progress_bar(current_hp, max_hp);
    cout << "\nAttack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "Sp.Atk: " << sp_attack << endl;
    cout << "Sp.Def: " << sp_defense << endl;
    cout << "Speed: " << speed << endl;
    cout << "Exp. Points: " << current_xp << "  |  " << "Exp. Needed: " << exp_for_level(level+1)-current_xp << endl;
    progress_bar(current_xp-exp_for_level(level), exp_for_level(level+1)-exp_for_level(level));
    cout << "\nAbility: " << ability << endl;
}

void Pokemon::print_moveset() {
    cout << "(1) " << moveset[0] << "      (2) " << moveset[1] << endl;
    cout << "(3) " << moveset[2] << "      (4) " << moveset[3] << endl;
}

void Pokemon::print_learnset() {
	for(auto i = learnset.begin(); i != learnset.end(); ++i) {
        cout << i->first << "  " << i->second << endl;
	}
}

void Pokemon::print_ivs() {
    cout << "HP: " << iv_hp << endl;
    cout << "Attack: " << iv_attack << endl;
    cout << "Defense: " << iv_defense << endl;
    cout << "Special Attack:" << iv_sp_attack << endl;
    cout << "Special Defense: " << iv_sp_defense << endl;
    cout << "Speed: " << iv_speed << endl;
}

void Pokemon::full_display() {
    cout << "======================New Pokemon====================\n";
    cout << "Name: " << species_name << endl;
    cout << "Number: " << pokedex_number << endl;
    cout << "Gender: ";
    if(gender)
        cout << "Male";
    else cout << "Female";
    cout << "\nLevel: " << level << endl;
    cout << "Exp Yield: " << exp_yield << endl;
    cout << "Leveling Speed: " << leveling_speed << endl;
    cout << "Evolves at " << evolves_at;
    cout << " to " << evolves_to << endl;
    cout << "Type: ";
    for(auto i = type.begin(); i != type.end(); ++i) {
        cout << *i;
        if(i + 1 != type.end()) {
            cout << ", ";
        }
    }
    cout << "\nNature: " << nature[0] << nature[1] << endl;
    cout << "Shiny: " << shiny << endl;
    //cout << "" << moveset;
    cout << "Held item: " << held_item << endl;
    cout << "Current HP: " << current_hp << endl;
    cout << "Current XP: " << current_xp << endl;
    cout << "Catch Rate: " << catch_rate << endl;
    cout << "Status: " << status << endl;
    cout << "Ability: " << ability << endl;
    cout << "Max HP: " << max_hp << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "Special Attack: " << sp_attack << endl;
    cout << "Special Defense: " << sp_defense << endl;
    cout << "Speed: " << speed << endl;
    cout << "=========================IVS=========================\n";
    cout << "HP: " << iv_hp << endl;
    cout << "Attack: " << iv_attack << endl;
    cout << "Defense: " << iv_defense << endl;
    cout << "Special Attack:" << iv_sp_attack << endl;
    cout << "Special Defense: " << iv_sp_defense << endl;
    cout << "Speed: " << iv_speed << endl;
    cout << "======================Base Stats=====================\n";
    cout << "HP: " << base_hp << endl;
    cout << "Attack: " << base_attack << endl;
    cout << "Defense: " << base_defense << endl;
    cout << "Special Attack: " << base_sp_attack << endl;
    cout << "Special Defense: " << base_sp_defense << endl;
    cout << "Speed: " << base_speed << endl;
    print_learnset();
    print_moveset();

}
