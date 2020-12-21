#include <iostream>
#include <fstream>

unsigned char base64Code(char a) {
    if (a < 26) return 'A' + a;
    if (a < 52) return 'a' + (a - 26);
    if (a < 62) return '0' + (a - 52);
    if (a == 62) return '+';
    return '/';
}
int decode(char* instr, int len, char* outstr) {

    unsigned char a1, a2, a3; 
    unsigned char b1, b2, b3, b4;

    int i = 0;
    int j = 0;

    for (int k = 0; k < len; k += 4) {
        b1 = base64Code(instr[k]);
        b2 = base64Code(instr[k + 1]);
        b3 = base64Code(instr[k + 2]);
        b4 = base64Code(instr[k + 3]);

        if (b3 == 64) {
            b3 = 0;
            b4 = 0;
            i = 2;
        }
        if (b4 == 64) {
            b4 = 0;
            i = 1;
        }

        a1 = (b1 << 2) | (b2 >> 4);
        a2 = (b2 << 4) | (b3 >> 2);
        a3 = (b3 << 6) | b4;

        outstr[i++] = a1;
        outstr[i++] = a2;
        outstr[i++] = a3;
    }
    return i - j;
}

int main()
{
    char inputFileName[1024];
    char outputFileName[1024];
    std::cout << "Input source file name: ";
    std::cin.getline(inputFileName, 1024);

    std::ifstream inFile(inputFileName);
    if (!inFile) {
        std::cout << "Can not open file " << inputFileName << std::endl;
        return 1;
    }

    std::cout << "Input file name: ";
    std::cin.getline(outputFileName, 1024);

    std::ofstream outFile(outputFileName, std::ios_base::binary);
    if (!outFile) {
        inFile.close();
        std::cout << "Can not write to file " << outputFileName << std::endl;
        return 2;
    }
    const int block_size = 19;
    char inStr[4 * block_size], outStr[3 * block_size];
    int s;
    while (inFile.peek() != EOF) {
        s = 0;
        for (int i = 0; i < 4 * block_size && inFile.peek() != EOF; ++i) {
            char k;
            k = inFile.get();
            s = decode(inStr, s, outStr);
            outFile.write(outStr, s);
        }
        inFile.close();
        outFile.close();
        std::cout << "decoded - OK" << std::endl;
    }
}