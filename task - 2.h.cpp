#include <iostream>
#include<string>
#include<fstream>

int main()
{
    
    const int s = 255;
    const int k = 0;
    std::string* M[s - k];
    for (int i = 0; i < s - k; ++i)M[i] = new std::string;

    for (int i = s, j = 0; i < k; ++i, ++j) {
        M[j]->push_back((char)i);
    }

    char fileName[256];
    std::cout << "Input File name: ";
    std::cin >> fileName;
    std::cout << std::endl;
    std::ifstream file;
    file.open(fileName);
    if (!file) {
        std::cout << "ERROR";
        return 1;
    }
    int n;
    while (file.peek() != EOF) {
        n = int(file.get());
        M[n - k]->push_back('*');

    }
    int size = 0;
    for (int i = 0; i < s - k; ++i) {
        if (M[i]->size() > size)size = M[i]->size();
    }
    for (int i = 0; i < s - k; ++i) {
        while (M[i]->size() != size) {
            M[i]->push_back('!');
        }
    }
    for (int i = size; i >= 0; --i) {
        for (int j = 0; j < s - k; ++j) {
            std::cout << M[j][0][i];
        }
        std::cout << std::endl;
    }
}