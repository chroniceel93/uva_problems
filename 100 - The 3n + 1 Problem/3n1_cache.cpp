/* @JUDGE_ID:   1318761   100     CPP   */

/* @BEGIN_OF_SOURCE_CODE */

// This is a dead simple problem, with the algorithm in question simply present-
// ed to the student as follows.
// 1. input n
// 2. print n
// 3. if n = 1 then STOP
// 4.   if n is odd then n <-- 3n+1
// 5.   else n <-- n/2
// 6. GOTO 2
//
// It is said that for any given number, this algorithm will generate a sequence
// of numbers that eventually terminates in 1. Our goal is to determine, given
// two numbers i and j, which number between them has the longest cycle length-
// or more simply, what number between i and j takes the longest to terminate in
// 1 when you apply the 3n+1 algorithm.

#include <iostream>
#include <string>

int recurse(int num, int *cache);

int test(int low, int high, int *cache);

int main() {
    bool cont = true;
    int first, second, temp, max = 0;
    // In this version of the solution, I settled on a fairly simple fixed-size
    // cache. This lets us avoid a lot of recomputation, and greatly speeds up
    // the program.
    // For one particular set of test cases, this algorithm took approximately
    // 0.323 seconds to complete. With the cache this was reduced to 0.071
    // seconds. Needless to say, this is a fairly significant speedup brought
    // about by simply reducing redundant calculations.
    int *cache = new int[100000]{0};
    std::size_t space = 0; // use this variable to keep track of where a space
                           // is in the input string
    // Assume exit condition is blank line
    while (cont == true) {
        // Reading in and writing out data is one of the most challenging
        // aspects of working with an automated judge- At least at first. They
        // are very, very picky about whitespace, so you have to be very delib-
        // erate about what you write to stdio.
        std::string input = "";
        std::getline(std::cin, input);

        if (input.size() != 0) {
            // reset space
            space = 0; 
            // stoi finds first number in string, and saves index after end of
            // num to space
            first = std::stoi(input, &space);
            // substr removes first number from string, and stoi copies final
            // number
            second = std::stoi(input.substr(space));
            temp = 0;

            max = test(first, second, cache);
            std::cout << first << " " << second << " " << max << "\n";
        } else {
            cont = false;
        }
    }
    return 0;
}

/** Parses line**/

/** Recursive function executes 3n+1 algorithm, counting each iteration, terminating at 1 **/
int recurse(int num, int *cache) {
    int res = 0;
    int tick = 0;

    if (num % 2) {
        res = (3 * num) + 1;
    } else {
        res = num / 2;
    }

    if (res >= 100000) { //fall back in case any case ends up larger than can be cached
        tick = recurse(res, cache);
    } else if (cache[res] == 0 && res != 1) {
        tick = recurse(res, cache);
        cache[res] = tick;
    } else if (res == 1) {
        tick = 1;
    } else {
        tick = cache[res];
    }
    // expecting an ob1

    return tick + 1;
}

/** Given i and j, sweeps through the range and finds max cycle length**/
int test(int low, int high, int *cache) {
    int test, max = 0;
    if (low > high) {
        test = low; // re-using test as temp var
        low = high;
        high = test;
    }
    for (int i = low; i <= high; i++) {
        if (i == 1) {
            test = 1;
        } else {
            test = recurse(i, cache);
        }
        if (test > max) {
            max = test;
        }
    }
    return max;
}


/* @END_OF_SOURCE_CODE */