#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(size_t argc, char* argv[]){

    if(argc < 2){
        std::cout << "|   please enter path to file like argument   |";
        return 3;
    }
    // std::system("title " + *argv[1]);

//|     OPEN FILE      |
    std::ifstream program;
    program.open(argv[1]);
    if(!program.is_open()){    return 1;   }

//|     READ FILE      |
    std::string line;
    std::string code;
    while (std::getline(program, line)){
        code.append(line);
    }

//|   INTERPRETATION   |
    short memory[200][200] = {0};
    int ptrX = 0;
    int ptrY = 0;

    size_t i = 0;
    while (i != std::size(code)){

        switch (code[i]){
        case '^':
            if(code[i+1] == '@')
                std::cout << (char)memory[ptrY][ptrX];
            if(code[i+1] == '$')
                std::cout << memory[ptrY][ptrX];
            break;
        case 'v':
            std::cin >> memory[ptrY][ptrX];
            break;
        case ';':
            if(code[i+1] == '\0'){std::cout << "\n" << "|   program completed successfully   |";
                                                                                       return 0;}
            if(code[i+1] == '>'){                                                      ptrX = 0;
                                                                                         ptrY++;}
            if(code[i+1] == '<'){                                                      ptrX = 0;
                                                                                         ptrY--;}
            i++;
            break;
        case '#':
            memory[ptrY][ptrX] = 0;
            break;
        case '-':
            if(code[i+1] == '.')        memory[ptrY][ptrX] -= memory[ptrY][ptrX+1];
            else if(code[i+1] == ',')   memory[ptrY][ptrX] -= memory[ptrY][ptrX-1];
            else                        memory[ptrY][ptrX] -= std::atoi(std::string{code[i+1], code[i+2]}.c_str());
            break;
        case '+':
            if(code[i+1] == '.')        memory[ptrY][ptrX] += memory[ptrY][ptrX+1];
            else if(code[i+1] == ',')   memory[ptrY][ptrX] += memory[ptrY][ptrX-1];
            else                        memory[ptrY][ptrX] += std::atoi(std::string{code[i+1], code[i+2]}.c_str());
            
            break;
        case '}':
            ptrX++;
            break;
        case '{':
            ptrX--;
            break;
        case '(':
            i -= std::atoi(std::string{code[i+1],code[i+2]}.c_str());
            break;
        case ')':
            i += std::atoi(std::string{code[i+1],code[i+2]}.c_str());
            break;
        case '?':
            if (std::atoi(std::string{code[i+1],code[i+2]}.c_str()) != memory[ptrY][ptrX]) {
                i += 4;
            }
            break;
        case '|':
            if(code[i+1] == '.')        memory[ptrY][ptrX] |= memory[ptrY][ptrX+1];
            else if(code[i+1] == ',')   memory[ptrY][ptrX] |= memory[ptrY][ptrX-1];
            else                        memory[ptrY][ptrX] |= std::atoi(std::string{code[i+1], code[i+2]}.c_str());
            break;
        case '&':
            if(code[i+1] == '.')        memory[ptrY][ptrX] &= memory[ptrY][ptrX+1];
            else if(code[i+1] == ',')   memory[ptrY][ptrX] &= memory[ptrY][ptrX-1];
            else                        memory[ptrY][ptrX] &= std::atoi(std::string{code[i+1], code[i+2]}.c_str());
            break;
        case 'X':
            if(code[i+1] == '.')        memory[ptrY][ptrX] ^= memory[ptrY][ptrX+1];
            else if(code[i+1] == ',')   memory[ptrY][ptrX] ^= memory[ptrY][ptrX-1];
            else                        memory[ptrY][ptrX] ^= std::atoi(std::string{code[i+1], code[i+2]}.c_str());
            break;
        }
        if(ptrY > std::size(memory))       ptrY =   0;
        if(ptrY < 0)                       ptrY = 200;
        if(ptrX > std::size(memory[0]))    ptrX =   0;
        if(ptrX < 0)                       ptrX = 200;
        if(i < 0)                             i =   0;
        // if(i > std::size(code))   i = std::size(code)-1;
        i++;
    }

    std::cout << "\n" << "|    warning: the program does not end in ;   |";
    return -1;
}