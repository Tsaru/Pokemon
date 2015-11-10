
#include<vector>
#include<string>

using std::string;
using std::vector;

class Pokemon {

private:
    string species_name;
	int species_number;
	int level;
	int nature;
	bool shiny;
	vector<string> moveset;
	string held_item;
	int current_hp;
	int current_xp;
	float catch_rate;
	vector<string> status_effects;
	string ability;
	int hp;
	int attack;
	int defense;
	int sp_attack;
	int sp_defense;
	int speed;
	int ivs_hp;
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
	int leveling_speed;
	void set_stats();
	void add_experience(int);

    public:

};
