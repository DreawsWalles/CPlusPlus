#include "workWithFile.h"

void checkUpdate(string filename)
{
	fstream File(filename, ios_base::in);
	File.seekp(0, ios::end);
	int size = File.tellp();
	File.close();
	int newSize = size;
	while (newSize == size)
	{
		fstream File(filename, ios_base::in);
		File.seekp(0, ios::end);
		newSize = File.tellp();
		File.close();
	}
}