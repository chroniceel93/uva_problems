/* @JUDGE_ID:   1318761   10204     CPP     */

/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <string>
#include <vector>

struct Shuffle {
    char order[52];

    Shuffle() {
        for (auto i = 0; i < 52; i++) {
            order[i] = 0;
        }
        return;
    }

    ~Shuffle() {
        return;
    }

};

std::string cardName(char value);

int main() {
    std::size_t space = 0; // Helper var used for parsing strings
    std::string input = "";
    char alpha_deck[52]; // main working deck
    char swap_deck[52]; // temporary deck used to hold swapped order
    bool shuffling = 0;
    std::vector<Shuffle> shuffles;
    int test_cases = 0; // number of test cases
    int shuffle_count = 0; // number of shuffles in the test case

    // get first line of input, test case count
    std::getline(std::cin, input);

    test_cases = std::stoi(input);

    for (auto i = 0; i < test_cases; i++) {
        // re-initialize deck for every test case
        for (auto i = 0; i < 52 ; i++) {
            alpha_deck[i] = i;
        }

        // get first line of test case, number of shuffles

        do {
            std::getline(std::cin, input);
        } while (input == "");

        shuffle_count = std::stoi(input);

        // read in shuffles.
        for (auto j = 0; j < shuffle_count; j++) {
            std::getline(std::cin, input);
            shuffles.push_back(*(new Shuffle()));
            for (auto k = 0; k < 52; k++) {
                if (input == "") {
                    std::getline(std::cin, input);
                } else {
                    // do_nothing
                }
                shuffles[j].order[k] = std::stoi(input, &space) - 1;
                input = input.substr(space);
            }
        }

        // read out order
        shuffling = true;
        int set = 0;

        std::getline(std::cin, input);
        set = std::stoi(input) - 1;
        do {
            for (auto j = 0; j < 52; j++) {
                swap_deck[j] = alpha_deck[static_cast<int>(shuffles[set].order[j])];
            }
            for (auto j = 0; j < 52; j++) {
                alpha_deck[j] = swap_deck[j];
            }
            std::getline(std::cin, input);
            if (input == "") {
                shuffling = false;
            } else {
                set = std::stoi(input) - 1;
            }
            
        } while (shuffling);
        //output final order
        for (auto j: alpha_deck) {
            std::cout << cardName(j) << '\n';
        }
        if (i < (test_cases - 1)) {
            std::cout << '\n' << std::flush;
        }
        shuffles.clear();
    }
    return 0;
}

std::string cardName(char value) {
    std::string result = "";
    int card = value % 13;

    switch (card) {
        case 0:
            result = "2";
            break;
        case 1:
            result = "3";
            break;
        case 2:
            result = "4";
            break;
        case 3:
            result = "5";
            break;
        case 4:
            result = "6";
            break;
        case 5:
            result = "7";
            break;
        case 6:
            result = "8";
            break;
        case 7:
            result = "9";
            break;
        case 8:
            result = "10";
            break;
        case 9:
            result = "Jack";
            break;
        case 10:
            result = "Queen";
            break;
        case 11:
            result = "King";
            break;
        case 12:
            result = "Ace";
            break;
        default:
            result = "N/A";
            break;
    }

    result += " of ";

    if ( value <= 12) {
        result += "Clubs";
    } else if (value > 12 && value <= 25) {
        result += "Diamonds";
    } else if (value > 25 && value <= 38) {
        result += "Hearts";
    } else if (value > 38) {
        result += "Spades";
    }

    return result;
}

/* @END_OF_SOURCE_CODE */