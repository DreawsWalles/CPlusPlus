#pragma once
#include "Attack_Weight.h"
#include <string>

using namespace std;

class Cell :
    public Attack_Weight
{
private:
    int _count = 0;
protected:
    char _fig;
    int _inpossible_attacks[8];
    float _weight_x;
    float _weight_o;
public:
    Cell(char fig);
    Cell();
    char get_fig();
    float get_weight(char fig);
    void update_fig(char fig);
    void update_weight(char fig, float weight);
    void set_attack(int attack);
    bool check_attack(int attack);
};

