#include "Attack_Weight.h"

using namespace std;


float Attack_Weight::get_weight(int cap, int pot)
{
	_capability = cap;
	_potential = pot;
	switch (_potential)
	{
	case 0:
		if (_capability == 5)
			return 200;
		else
			return 0;
		break;
	case 1:
		switch (_capability)
		{
		case 0:return 0;
			break;
		case 1: return 0.1;
			break;
		case 2: return 2;
			break;
		case 3: return 4;
			break;
		case 4: return 6;
			break;
		case 5: return 200;
			break;
		}
		break;
	case 2:
		switch (_capability)
		{
		case 0:return 0;
			break;
		case 1: return 0.25;
			break;
		case 2: return 5;
			break;
		case 3: return 7;
			break;
		case 4: return 100;
			break;
		case 5: return 200;
			break;
		}
		break;
	}
}