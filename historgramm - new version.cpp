#include <iostream>
#include <fstream>
#include <string>

std::fstream Open_file()
{
	std::fstream f;
	std::string fname;
	std::cout << "Enter the file name: ";
	std::cin >> fname;
	f.open(fname);
	while (!f.is_open())
	{
		std::cout << "The file name was entered inncorrectly." << std::endl << "Enter the file name again: ";
		std::cin >> fname;
		f.open(fname);
	}
	std::cout << "File opened.";
	return f;
}

void main()
{
	std::fstream f;
	std::ofstream f2;
	std::string fname2;
	f = Open_file();
	int l;
	int* mas = new int[255];
	for (int i = 0; i < 255; ++i)
		mas[i] = 0;

	while (!f.eof())
		if (f.get() != '\n')
			++mas[int(f.get())];

	std::cout << std::endl << "Enter file name for histogram: ";
	std::cin >> fname2;
	f2.open(fname2);
	if (!f2.is_open())
	{
		std::cout << "Error opening file.";
		exit(-1);
	}
	int max = 0;
	for (int i = 0; i < 255; ++i)
		if (mas[i] > max)
			max = mas[i];
	for (int i = 0; i < max; ++i)
	{
		for (int j = 0; j < 255; ++j)
		{
			if (max - mas[j] > i && mas[j] > 0)
				f2 << "   ";
			else if (mas[j] > 0 && max - mas[j] <= i)
				f2 << " * ";
		}
		f2 << std::endl;
	}
	bool first = false;
	for (int i = 0; i < 255; ++i)
	{
		if (i == 10)
		{
			if (first == false)
				f2 << "\n" << " ";
			else
				f2 << "" << "\n" << "";
			continue;
		}
		if (mas[i] > 0)
		{
			if (first == false)
			{
				std::cout << char(i) << "\n";
				first = true;
			}
			f2 << " " << char(i) << " ";
		}
	}
}