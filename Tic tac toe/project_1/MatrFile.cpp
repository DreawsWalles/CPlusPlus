#include "MatrFile.h"

MatrFile::MatrFile(int size) : _size(size)
{
	_matr = new string* [_size];
	for (int i = 0; i < _size; i++)
		_matr[i] = new string[_size];
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			_matr[i][j] = "0";
	for (int i = 0; i < 5; i++)
	{
		_winCombinate[i].X = 0;
		_winCombinate[i].Y = 0;
	}
	_pos = new positions[_size];
}

void MatrFile::setFileName(string filename) 
{
	_filename = filename;
}

void MatrFile::printMatr()
{
	ofstream File (_filename);
	File << ' ';
	int i = 0;
	for (i = 0; i < _size; i++)
	{
		for (int k = 0; k < _size; k++)
			File << "====== ";
		File << '\n';
		_pos[i].x1 = File.tellp();
		_pos[i].x1++;
		for (int j = 0; j < _size; j++)
		{
			File << '|';
			if (_matr[i][j] == "0")
				File << "      ";
			else
				if (_matr[i][j] == "x")
					File << "  \\/  ";
				else
					if (_matr[i][j] == "o")
						File << "  /\\  ";
		}
		File << '|';
		_pos[i].x2 = File.tellp();
		File << '\n';
		_pos[i].x3 = _pos[i].x2 + 1;
		for (int j = 0; j < _size; j++)
		{
			File << '|';
			if (_matr[i][j] == "0")
				File << "      ";
			else
				if (_matr[i][j] == "x")
					File << "  /\\  ";
				else
					if (_matr[i][j] == "o")
						File << "  \\/  ";
		}
		File << '|';
		_pos[i].x4 = File.tellp();
		File << '\n';
		File << '|';
	}
	for (int k = 0; k < _size; k++)
		File << "====== ";
	File.close();
}


COORD MatrFile::get_coord()
{
	checkUpdate(_filename);
	COORD a;
	a.X = 0;
	a.Y = 0;
	
	return a;
}