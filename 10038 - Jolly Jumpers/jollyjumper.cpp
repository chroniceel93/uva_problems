/* @JUDGE_ID:   1318761   10038     CPP   */

/* @BEGIN_OF_SOURCE_CODE */

#include <iostream>
#include <string>

int main() {
    bool isJumper = true;
    int size = 0;
    int diff = 0;

    int jumpers[3001]{0};
    int testers[3001]{0};

    std::size_t space = 0;
    // Assume exit condition is blank line
    while (true) {
        std::string input = "";
        std::getline(std::cin, input);

        if (input == "") {
            break;
        }

        space = 0;

        isJumper = true;

        // get size
        size = std::stoi(input, &space);
        input = input.substr(space);

        // Check size is in-bounds (not needed, but force of habit)
        if (size > 3000) {
            size = 3000;
        }

        // This loop breaks down string into array of numbers
        for (auto i = 0; space <= input.size(); i++) {
            jumpers[i] = std::stoi(input, &space);
            input = input.substr(space);
        }

        // This loop finds the difference of each successive pair
        // of items in the arr- Loop starts at index 0, goes to
        // size - 1 to avoid accessing OOB. For each loop, we set
        // the value to one at a given index = diff
        for (auto i = 0; (i < size - 1) && isJumper ; i++) {
            diff = jumpers[i] - jumpers[i+1];
            // abs
            if (diff < 0) {
                diff = diff * -1;
            } // else{do_nothing()}

            // If the value at testers[diff] is not zero, then
            // the sequence has a duplicate diff- and as it has
            // n numbers, and must have one of every number, then
            // it is, by definition, not a jolly number.
            if (testers[diff] == 0) {
                testers[diff] = 1;
            } else {
                isJumper = false;
                break;
            }
        }

        // This loop determines if the sequence was a jolly number- 
        // Skipping zero, we check every item in the array up to the
        // size of the sequence. If any value is zero, then it is not
        // a jolly number.
        for (auto i = 1; (i < size) && isJumper; i++) {
            if (testers[i] == 0) {
                isJumper = false;
                break;
            } else {
                /*do_nothing()*/
            }
        }

        // Print result for this loop
        if (isJumper) {
            std::cout << "Jolly\n" << std::flush; 
        } else {
            std::cout << "Not jolly\n" << std::flush;
        }

        // Clear our arrays for the next loop.
        for (auto i = 0 ; i <= 3000 ; i++) {
            jumpers[i] = 0;
            testers[i] = 0;
        }

    }
    return 0;
}

/* @END_OF_SOURCE_CODE */