
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
	int ivs_hp;
	int IV_Attack;
	int IV_Defense;
	int IV_Special Attack;
	int IV_Special Defense;
	int IV_Speed;
	int Base_HP;
	int Base_Attack;
	int Base_Defense;
	int Base_Special Attack;
	int Base_Special Defense;
	int Base_Speed;
	int Leveling_Speed;
	void set_stats();

public:



};
