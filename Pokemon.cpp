
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

void Pokemon::Open_Base_Pokemon(string name) {
    string value = "-";
    std::ifstream file;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 random_num(seed);
    file.open("Pokemon.txt");

    //Remove the format line
    getline(file, value);

    //find the correct line
    cout << "2\n";
    file >> value;
    while(value != name) {
        cout << value << endl;
        getline(file, value);
        file >> value;
    }
    cout << value << endl;
    cout << "3\n";
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

    //Get the type(s)
    type.clear();
	file >> value;
	if(value[0]=='<') {
        value = value.substr(1, value.size());
        type.push_back(value);
        file >> value;
        value = value.substr(0, value.size()-1);
	}
	type.push_back(value);

    //Get the catch rate
	file >> value;
	catch_rate = stoi(value);

	//Get the abilities and choose a random ability
	if(random_num()%150 == 0) {
        cout << "4\n";
        file >> value;
        if(value[0] == '<') {
            while(value[-1] != '>') {
                file >> value;
            }
        }
        file >> value;
        if(value[0] == '"') {
            ability = "";
            value = value.substr(1, value.size());
            while(value[-1] != '"') {
                ability  += " " + value;
                file >> value;
            }
            ability += value.substr(0, value.size()-1);
        } else {
            ability = value;
        }
	} else {
	    vector<string> temp_abilities;
	    temp_abilities.clear();
        file >> value;
        if(value[0]=='<') {
            value = value.substr(1, value.size());
            temp_abilities.push_back(value);
            file >> value;
            while(value[-1] != '>') {
                cout << "4\n";
                temp_abilities.push_back(value);
                file >> value;
            }
            value = value.substr(0, value.size()-1);
        }
        temp_abilities.push_back(value);
        ability = temp_abilities[random_num()%temp_abilities.size()];
        file >> value;
        if(value[0] == '"') {
            while(value[value.size()-1] != '"') {
                file >> value;
            }
        }
	}
    cout << "5\n";

	file >> value;
	exp_yield = stoi(value);
	file >> value;
	leveling_speed = stoi(value);
	file >> value;
	evolves_at = stoi(value);
	file >> value;
	evolves_to = value;
}

Pokemon::Pokemon() {
    cout << "1\n";
    Open_Base_Pokemon("Pikachu");
    cout << "10\n";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
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
	current_xp = 0;
	gender = random_num()%2;
	moveset.clear();
	moveset.push_back("Tackle");
	held_item.clear();
	held_item = "Empty";
	status = "";
}

void Pokemon::set_stats() {
    max_hp = base_hp + base_hp/50*level + iv_hp;
    attack = base_attack + base_attack/50*level + iv_attack;
    defense = base_defense + base_defense/50*level + iv_defense;
    sp_attack = base_sp_attack + base_sp_attack/50*level + iv_sp_attack;
    sp_defense = base_sp_defense + base_sp_defense/50*level + iv_sp_defense;
    speed = base_speed + base_speed/50*level + iv_speed;
}

void Pokemon::display() {
    cout << "name: " << species_name << endl;
    cout << "number: " << pokedex_number << endl;
    cout << "gender: ";
    if(gender)
        cout << "male";
    else cout << "female";
    cout << "\n level: " << level << endl;
    cout << "exp yield: " << exp_yield << endl;
    cout << "leveling speed: " << leveling_speed << endl;
    cout << "evolves at " << evolves_at;
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
    cout << "===IVS===\n";
    cout << "HP: " << iv_hp << endl;
    cout << "Attack: " << iv_attack << endl;
    cout << "Defense: " << iv_defense << endl;
    cout << "Special Attack:" << iv_sp_attack << endl;
    cout << "Special Defense: " << iv_sp_defense << endl;
    cout << "Speed: " << iv_speed << endl;
    cout << "===Base Stats===\n";
    cout << "HP: " << base_hp << endl;
    cout << "Attack: " << base_attack << endl;
    cout << "Defense: " << base_defense << endl;
    cout << "Special Attack: " << base_sp_attack << endl;
    cout << "Special Defense: " << base_sp_defense << endl;
    cout << "Speed: " << base_speed << endl;
}
