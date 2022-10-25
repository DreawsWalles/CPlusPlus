#include "Cell.h"

Cell::Cell(char fig) :_fig(fig)
{
	_count = 0;
	_weight_o = 0;
	_weight_x = 0;
}
Cell::Cell()
{
	_count = 0;
	_weight_o = 0;
	_weight_x = 0;
	_fig = '0';
}
void Cell::update_fig(char fig)
{
	_fig = fig;
}

char Cell::get_fig()
{
	return _fig;
}

void Cell::update_weight(char fig, float weight)
{
	if (fig == 'x')
		_weight_x = weight;
	else
		_weight_o = weight;
}

bool Cell::check_attack(int attack)
{
	int i = 0;
	while (i < 8)
	{
		if (_inpossible_attacks[i] == attack)
			return false;
		else
			i++;
	}
	return true;
}

void Cell::set_attack(int attack)
{
	_inpossible_attacks[_count] = attack;
	_count++;
}

float Cell::get_weight(char fig)
{
	if (fig == 'x')
		return _weight_x;
	else
		return _weight_o;
}