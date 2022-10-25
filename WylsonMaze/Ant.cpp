#include "AntsAlgorithm.h"
#include <algorithm>

using namespace std;

Ant::Ant(int sizeMaze, Maze::Point start, Maze::Point end)
{
	_size = sizeMaze;
	_start = start;
	_end = end;
	_length = 1;
	_found = false;
}

Ant::~Ant()
{

}



double Ant::getRandom()
{
	return double((rand() % 101)) / 100.0;
}


void Ant::Clear()
{
	
}

//реруксивный алгоритм, для обработки развилок
bool Ant::getWay(AntsAlgorithm::AddicionalLayers**& maze, Maze::Point previous, Maze::Point current, Maze::Point startPoint, Maze::Point direction)
{
	//ситуация, когда мы врезались в тупик
	//мы храним позицию начала развилки, и направление в котором мы начали движения, чтобы в дальнейшем убрать это направление, в случае, если это тупик
	if (maze[current.y][current.x].layer_2.critical == 1)
	{
		vector<Maze::Point> dir;
		for (int i = 0; i < maze[startPoint.y][startPoint.x].layer_2.directions.size(); i++)
			if(maze[startPoint.y][startPoint.x].layer_2.directions[i] != direction)
				dir.push_back(maze[startPoint.y][startPoint.x].layer_2.directions[i]);
		maze[startPoint.y][startPoint.x].layer_2.directions = dir;
		maze[startPoint.y][startPoint.x].layer_2.critical--;
		return false;
	}
	//вариант, когда мы дошли до конца
	if (current == _end)
	{
		//говорим о том, что мы в нашли выигрышный вариант
		_found = true;
		vector<Maze::Point> dir;
		ant_memory.push_back(current);
		//удаляем это напрвление для того, чтобы небыло дубликатов решения 
		for (int i = 0; i < maze[startPoint.y][startPoint.x].layer_2.directions.size(); i++)
			if (maze[startPoint.y][startPoint.x].layer_2.directions[i] != direction)
				dir.push_back(maze[startPoint.y][startPoint.x].layer_2.directions[i]);
		maze[startPoint.y][startPoint.x].layer_2.directions = dir;
		maze[startPoint.y][startPoint.x].layer_2.critical--;
		return true;
	}
	//вариант, когда мы движемся по прямой, до момента пока не встрим развилку, при этом мы каждый раз вызываем эти процедуры рекурсивно
	else if (maze[current.y][current.x].layer_2.critical == 2 &&
		find(ant_memory.begin(), ant_memory.end(), previous) != ant_memory.end())
	{
		maze[current.y][current.x].layer_2.feromon += _length * rho;
		_length++;
		ant_memory.push_back(current);
		int i = 0;
		while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
			//i = rand() % maze[current.y][current.x].layer_2.directions.size();
			i++;
		return getWay(maze, current, maze[current.y][current.x].layer_2.directions[i], startPoint, direction);
	}
	//вариант когда мы встретили развилку
	else
	{
		int i = 0;
		while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
			//i = rand() % maze[current.y][current.x].layer_2.directions.size();
			i++;
		ant_memory.push_back(current);
		return getWay(maze, current, maze[current.y][current.x].layer_2.directions[i], current, maze[current.y][current.x].layer_2.directions[i]);
	}
}

//основной алгоритм
//в данном алгоритме под понятием движение по прямой подразумевается то, что у нас на пути нет никаких развилок.
vector<Maze::Point> Ant::GetWays(AntsAlgorithm::AddicionalLayers** &maze)
{
	Maze::Point current = _start;
	Maze::Point previous = _start;
	vector<Maze::Point> result;
	//запускаем цикл, для случаев, когда мы находимся в старте и нам нужно пройтись по прямой
	while (!_found && maze[current.y][current.x].layer_2.critical != 0)
	{
		//проверяем, не пришли ли мы в конец лабиринта
		if (current == _end)
		{
			_found = true;
		}
		//проверка на то, двигаемся ли мы про прямой или же у нас есть вариант с развилкой
		else if (maze[current.y][current.x].layer_2.critical == 1 || (maze[current.y][current.x].layer_2.critical == 2 && find(ant_memory.begin(), ant_memory.end(), previous) != ant_memory.end()))
		{
			//если мы уперлись в тупик, и при этом это последний вариант, то мы просто удаляем из стартовой позиции все возможные ходы
			if (maze[current.y][current.x].layer_2.critical == 1 && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[0]) != ant_memory.end())
			{
				maze[_start.y][_start.x].layer_2.directions.clear();
				maze[_start.y][_start.x].layer_2.critical = 0;
				return result;
			}
			//перемещение по прямой
			maze[current.y][current.x].layer_2.feromon += _length * rho;
			_length++;
			ant_memory.push_back(current);
			previous = current;
			int i = 0;
			while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
				//i = rand() % maze[current.y][current.x].layer_2.directions.size();
				i++;
			current = maze[current.y][current.x].layer_2.directions[i];
		}
		//вариант, когда мы подошли к точке развилке. Здесь рекурсивно запускаем алгоритм, по которому мы либо получим выигрышный путь, либо упремся в тупик
		else
		{
			if (previous == _start)
				ant_memory.push_back(previous);
			int i = 0;
			while (i < maze[current.y][current.x].layer_2.directions.size() && find(ant_memory.begin(), ant_memory.end(), maze[current.y][current.x].layer_2.directions[i]) != ant_memory.end())
				//i = rand() % maze[current.y][current.x].layer_2.directions.size();
				i++;
			return getWay(maze, _start, maze[current.y][current.x].layer_2.directions[i], current, maze[current.y][current.x].layer_2.directions[i]) == false ? result :  ant_memory;
		}
	}
	return result;
}