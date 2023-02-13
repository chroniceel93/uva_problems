/* @JUDGE_ID:   1318761   10033   CPP */

/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <string>

// max possible value is 81*3+17 = 260, so bitfeild is 9 bits
struct cell {
    unsigned int a : 9;
    unsigned int b : 9;
    unsigned int c : 9;
public: 
    int toint() {
        int result = 0;
        result += this->a *100;
        result += this->b *10;
        result += this->c;
        return result;
    }

    bool isZero() {
        bool res = false;
        if (this->a == 0 && this->b == 0 && this->c == 0) {
            res = true;
        }
        return res;
    }

    void operator=(const cell& b) {
        this->a = b.a;
        this->b = b.b;
        this->c = b.c;
        return;
    }

    void operator=(const int& a) {
        this->a = (a / 100) % 10;
        this->b = (a / 10) % 10;
        this->c = a % 10;
        return;
    }

    cell operator+(const cell& b) {
        cell res;

        res.a = b.a + this->a;
        res.b = b.b + this->b;
        res.c = b.c + this->c;

        if (res.c > 9) {
            res.b++;
            res.c = res.c % 10;
        }

        if (res.b > 9) {
            res.a++;
            res.b = res.b % 10;
        }

        if (res.a > 9) {
            res.a = res.a % 10;
        }
        return res;
    }

    cell operator+(const int& b) {
        cell n;
        n = b;
        return *this + n;
    }

    cell operator*(const cell& b) {
        cell res;
// multiplication is fun!
        res.c = (this->c * b.c);
        res.b = (this->b * b.c) + (this->c * b.b);
        res.a = (this->c * b.a) + (this->b * b.b) + (this->a * b.c);
        
        if (res.c > 9) {
            res.b += res.c / 10;
            res.c = res.c % 10;
        }

        if (res.b > 9) {
            res.a += res.b / 10;
            res.b = res.b % 10;
        }

        if (res.a > 9) {
            res.a = res.a % 10;
        }
        return res;
    }

    cell operator*(const int& b) {
        cell a;
        a = b;
        return a * *this;
    }

};

void reset_PC(cell *ram, cell *reg);

void read_RAM(cell *ram);

void dump_PC(cell *ram, cell *reg);

int exec_PRG(cell *ram, cell *reg);

int main() {
    bool cont = true;

    cell *ram = new cell[1000]{0}; // All must be modulo 1000

    cell *reg = new cell[10]{0};

    std::string input = "";
    std::getline(std::cin, input);

    int count = std::stoi(input);
    int insc = 0;
    // get blank line
    std::getline(std::cin, input);

    while (cont == true) {
        reset_PC(ram, reg);
        insc = 0;

        // READ IN PROGRAM
        read_RAM(ram);
        
        // EXECUTE PROGRAM
        insc = exec_PRG(ram, reg);

        count--;
        if (count <= 0) {
            cont = false;
            std::cout << insc << '\n' << std::flush;
        } else {
            std::cout << insc << "\n\n";
        }
    }

    return 0;
}

void reset_PC(cell *ram, cell *reg) {
    for (int i = 0; i < 1000; i++) {
        *(ram+i) = 0;
    }
    for (auto i = 0; i < 10; i++) {
        *(reg+i) = 0;
    }
}

void read_RAM(cell *ram) {
    std::string input = "";
    int rawin = 0;
    int index = 0;
    bool read = true;
    while (read == true && index < 1000) {
        std::getline(std::cin, input);
        if (input.size() != 0) {
            rawin = std::stoi(input);
            ram[index] = rawin;
        } else {
            read = false;
        }
        index++;
    }
}

int exec_PRG(cell *ram, cell *reg) {
    int PC = 0;
    int count = 0;
    bool halt = false;

    while (!halt) {
        switch((ram+PC)->a) {
            case 1: //HALT
                halt = true;
                break;
            case 2: // SET REG B TO VAL C
                *(reg+(ram+PC)->b) = (ram+PC)->c;
                break;
            case 3: // ADD VAL C TO REG B
                *(reg+(ram+PC)->b) = *(reg+(ram+PC)->b) + (ram+PC)->c;
                break;
            case 4: // MUL VAL C TO REG B
                *(reg+(ram+PC)->b) = *(reg+(ram+PC)->b) * (ram+PC)->c;
                break;
            case 5: // CPY REG C TO REG B
                *(reg+(ram+PC)->b) = *(reg+(ram+PC)->c);
                break;
            case 6: // ADD REG C TO REG B
                *(reg+(ram+PC)->b) = *(reg+(ram+PC)->b) + *(reg+(ram+PC)->c);
                break;
            case 7: // MUL REG C TO REG B
                *(reg+(ram+PC)->b) = *(reg+(ram+PC)->b) * *(reg+(ram+PC)->c);
                break;
            case 8: // SET REG B TO VAL IN RAM AT ADDR IN C
                *(reg+(ram+PC)->b) = *(ram+(reg+(ram+PC)->c)->toint());
                break;
            case 9: // SET RAM AT ADDR IN C TO VAL IN REG B
                *(ram+(reg+(ram+PC)->c)->toint()) = *(reg+(ram+PC)->b);
                break;
            case 0: // SET PC TO REG B UNLESS REG C HOLDS 0
                if (!(reg+(ram+PC)->c)->isZero()) {
                    PC = (reg+(ram+PC)->b)->toint() - 1;
                }
                break;
            default:
                break;
        }
        PC++;
        count++;
        if (PC > 10000) {
            halt = true;
        }
    }

    return count;
}
/* @END_OF_SOURCE_CODE */
