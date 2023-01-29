#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <ctime>
#include <stdlib.h>

char input[8192];
char inputDecompressed[4096];
short inputNumConverted[2048];
char output[8192];
short multiplier[2];
char separator = 248;

std::string decompressOutput;
std::string compressOutput;

int convertToNumber(char input, short firstmultiplier, short secondmultiplier){
    if(input < 33 || input > 122){
        return 200;
    }
    for(short i = 33; i<= 121; i=i+2){
        if(input == i){
            return ((123 - input + 95) * firstmultiplier);
        }
    }
    for(short i = 34; i<= 122; i=i+2){
        if(input == i){
            return ((124 - input) * secondmultiplier);
        }
    }
}

char convertToText(short input, short firstmultiplier, short secondmultiplier){
    for(short i = 33; i<= 121; i=i+2){
        if(input == (123 - i + 95) * firstmultiplier){
            return i;
        }
    }
    for(short i = 34; i<= 122; i=i+2){
        if(input == (124 - i) * secondmultiplier){
            return i;
        }
    }
    return ' ';
}

std::string &compress(int input){
    std::stringstream convertIntToString;
    std::string stringInput;

    convertIntToString << input;
    convertIntToString >> stringInput;

    if(stringInput.length() > 1){
        for(int i = stringInput.length() - 1; i >= 0; i=i-2){
            if(i < 1){
                compressOutput += (char)((char)(stringInput[i] - 48) + 33);
                break;
            }
            if(stringInput[i-1] - 48 == 0){
                compressOutput += (char)((char)((stringInput[i-2] - 48) * 10 + (stringInput[i] - 48) + 134));
                i--;
            } else {
                compressOutput += (char)((char)((stringInput[i-1] - 48) * 10 + (stringInput[i] - 48) + 33));
            }
        }
        return compressOutput;
    }
    return (std::string&)"";
}

std::string &decompress(std::string input){
    for(int i = 7;i < input.length();i++){
        if(input[i] <= 251 && input[i] >= 241){
            for(int j = i; j > 6; j--){
                if(input[j] <= 251 && input[j] >= 241)break;
                if(input[j] >= 33 && input[j] <= 133){
                    decompressOutput += (int)(input[j] - 33);
                } else if(input[j] >= 134 && input[j] <= 234){
                    std::string decompressBuffer;
                    std::stringstream convertIntToString;
                    convertIntToString << input[j] - 134;
                    convertIntToString >> decompressBuffer;
                    decompressBuffer.erase(0, 1);
                    decompressOutput += (int)(((input[j] - 134) / 10) * 100 + (decompressBuffer[0] - 48));
                }
            }
            decompressOutput += "a";
        }
    }
    return decompressOutput;
}

int main(){
    while(1){
        srand((unsigned)time(0));
        printf("Input:");
        scanf(" %[^\n]", input);

        if(input[0]=='~'){
            std::string inputDecompressionString;
            std::stringstream inputDecompressionStringStream;

            inputDecompressionStringStream << input;
            inputDecompressionStringStream >> inputDecompressionString;

            strcpy(input, decompress(inputDecompressionString).c_str());

            short numberConversionMemory = 0;
            short inputNumConvertedSlotMemory = 0;

            multiplier[1] = (((input[3] - 48) * 10 ) + (input[2] - 48) * 10 ) + (input[1] - 48) * 10;
            multiplier[2] = (((input[6] - 48) * 10 ) + (input[5] - 48) * 10 ) + (input[4] - 48) * 10;

            for(short i = 7; i <= 2048; i++){
                if(input[i]=='\0')break;
                if(input[i] >= 48 && inputDecompressed[i] <= 57)numberConversionMemory++;
                if(input[i] == 'a'){
                    switch(numberConversionMemory){
                        case 1 : inputNumConverted[inputNumConvertedSlotMemory] = input[i-1] - 48;break;
                        case 2 : inputNumConverted[inputNumConvertedSlotMemory] = (input[i-2] - 48) * 10 + (input[i-1] - 48);break;
                        case 3 : inputNumConverted[inputNumConvertedSlotMemory] = ((input[i-3] - 48) * 10 + (input[i-2] - 48)) * 10 + (input[i-1] - 48);break;
                        case 4 : inputNumConverted[inputNumConvertedSlotMemory] = (((input[i-4] - 48) * 10 + (input[i-3] - 48)) * 10 + (input[i-2] - 48)) * 10 + (input[i-1] - 48);break;
                        case 5 : inputNumConverted[inputNumConvertedSlotMemory] = ((((input[i-5] - 48) * 10 + (input[i-4] - 48)) * 10 + (input[i-3] - 48)) * 10 + (input[i-2] - 48)) * 10 + (input[i-1] - 48);break;
                        case 6 : inputNumConverted[inputNumConvertedSlotMemory] = 100 + rand() % 422;
                    }
                    inputNumConvertedSlotMemory++;
                    numberConversionMemory = 0;
                }
            }
            for(short i = 0;i <= inputNumConvertedSlotMemory;i++)output[i] = convertToText(inputNumConverted[i], multiplier[1], multiplier[2]);
        } else {
            std::string inputConverted;
            std::stringstream inputConvertedStringStream;

            multiplier[1] = 100 + rand() % 400;
            multiplier[2] = 501 + rand() % 498;

            inputConvertedStringStream << "~" << multiplier[1] << multiplier[2];
            inputConvertedStringStream >> inputConverted;

            for(short i = 0;i < 2048;i++){
                if(input[i]=='\0')break;
                inputConverted += compress(convertToNumber(input[i], multiplier[1], multiplier[2]));
                inputConverted += separator;
                strcpy(output, inputConverted.c_str());

                printf("output after strcpy = %s\n", output);
            }
        }

        printf("\nOutput: %s\n\n", output);
        for(short i = 0;i < 8192;i++){
            input[i] = '\0';
            output[i] = '\0';
            if(i < 2048)inputNumConverted[i] = '\0';
            if(i < 4096)inputDecompressed[i] = '\0';
            if(i < 3)multiplier[i]=0;
        }
    }
}