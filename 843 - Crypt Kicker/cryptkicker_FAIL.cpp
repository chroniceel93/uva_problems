/* @JUDGE_ID:   1318761   843   CPP */

/* @BEGIN_OF_SOURCE_CODE */

// I plan on rewriting this solution from scratch

#include <iostream>
#include <string>
#include <map>

// We want identifiers to be as specific as possible, so seperate repetition
// fields for every character in a word.

struct reps {
    // positions will be stored with binary bits, in reverse order.
    // this is effecitvely a rather compact 16 x 16 matrix
    short int places[16]; 

    void init() {
        for (auto i = 0; i < 16; i++) {
            places[i] = 0 ;
        }
    }

// VERIFIED - DO NOT TOUCH
    void find_reps(std::string input) {
        char chars[16];
        int size = input.size();
        bool hit = false;

        // initialize char array

        for (auto i = 0; i < 16; i++) {
            chars[i] = ' ';
        }

        // Step 1 - build list of existent characters
        // We iterate through every character in input with i.
        // We iterate through every character in chars with j.
        // If a given chars[j] == input[i] then we have a match already.
        // Otherwise, if chars[j] == ' ' then we have not yet seen this
        //      character, and can add it to the current jth position.
        // We use hit to control the loop.
        for (auto i = 0; i < size; i++) {
            hit = false;
            for (auto j = 0; (j < 16) && !hit ; j++) {
                if (input[i] == chars[j]) {
                    hit = true;
                } else if (chars[j] == ' ') {
                    chars[j] = input[i];
                    hit = true;
                } else {
                    // do_mothing();
                }
            }
        // Step 2 - build repitition structure
        // We iterate through every character in input with i.
        // We iterate through every index in chars with j.
        // If input[i] == chars[j], then we can say that chars[j] maps to 
        //      places[j]. We can store the position information by using the
        //      bitwise << operator to shift 1 byte by i bits.
            for (auto j = 0; j < 16; j++) {
                if (input[i] == chars[j]) {
                    this->places[j] += (0b1 << i);
                } else {
                    // do_nothing();
                }
            }
        }
        return;
    }


    bool is_equal(const reps& item) {
        bool result = true;
        for (auto i = 0; i < 16 && result; i++) {
            if (this->places[i] == item.places[i]) {
                result = true;
            } else {
                result = false;
            }
        }
        return result;
    }
};

//      While bulding the struct we need to find the following data:
//          - The word's Rep matrix
//          - The word's length
//          - The number of unique characters in the sentence
//      We need a structure for the attempts that has the following data
//          - The word itself
//          - All words in dict with matching Rep Matrix's and len's
//          - A list of chars that 'belong' to it in the cipher

struct crypt {
    std::string encrypted; // encrypted word
    std::string decrypted; // attempted word
    std::string matching_dictionary[1000]; // all possible words
    int attempt; // index of current attempted solution
    bool test_solution;
    int size; // number of words in dictionary
    char solved[16]; // list of characters effected in codex

    void init() {
        test_solution = false;
        encrypted = "";
        decrypted = "";
        size = 0;
    }

    void init(std::string input) {
        encrypted = input;
        decrypted = input;
        attempt = 0;
        for (auto i = 0; i < 16; i++) {
            if (i < static_cast<int>(input.size())) {
                solved[i] = input[i];
            } else {
                solved[i] = ' ';
            }
        }
        test_solution = false;
        size = 0;
    }

    void add_to_dict(std::string input) {
        matching_dictionary[size] = input;
        size++;
    }
};

struct accel {
    // Dictionary of words
    std::string dictionary[1010];
    // metadata
    int lengths[1010]; // length of each word
    reps store[1010]; // repetition matrix of each word
    int word_count; // number of words in dictionary

    void init() {
        for (auto i = 0; i < 1010; i++) {
            this->dictionary[i] = "";
            this->lengths[i] = 0;
            this->store[i].init();
        }
        this->word_count = 0;
    }

    void add_to_dict(std::string input) {
        this->store[this->word_count].init();
        this->store[this->word_count].find_reps(input);
        this->lengths[this->word_count] = input.size();
        this->dictionary[this->word_count] = input;
        this->word_count++;
        return;
    }

    bool find_matching(reps *input_r, crypt *input_c) {
        bool found_match = false;
        for (auto i = 0; i < word_count; i++) {
            if (this->store[i].is_equal(*input_r)) {
                input_c->add_to_dict(this->dictionary[i]);
                found_match = true;
            } else {
                // do_nothing();
            }
        }
        return found_match;
    }

    bool test_word(std::map<char, char> *cipher, crypt *input) {
        bool is_collision = false;
        char enc = ' '; // character i of encrypted string
        char att = ' '; // character i of attempted string
        char temp = ' ';
        std::map<char, char> test_cipher; // temporary cipher
        std::map<char, char>::iterator it; // iterator for cipher

        int fallback_attempt = input->attempt;
        if ((fallback_attempt + 1) >= input->size) {
            fallback_attempt = 0;
        } else {
            fallback_attempt++;
        }
        input->attempt = 0;
        int count = 0;
        bool is_duplicate = false;
        bool fail_to_match = false;
        // Step 1: Check if any word fits
        for (auto i = 0; i < static_cast<int>(input->encrypted.size()) && !fail_to_match ; i++) {
            enc = input->encrypted[i];
            att = input->matching_dictionary[input->attempt][i];
            it = cipher->find(enc);
            for (auto f: *cipher){
                if ((f.first != enc) && (f.second == att)) {
                    count++;
                    // temp = f.first;
                    // cipher->erase(f.first);
                    // cipher->insert(std::pair<char, char>(f.first, ' '));
                }
                if (count > 0) {
                    is_duplicate = true;
                }
            }
            if (((it->second == ' ') || (it->second == att)) && !is_duplicate) {
                test_cipher.insert(std::pair<char, char>(enc, att));
            } else {
                input->attempt++;
                i = -1;
                count = 0;
                test_cipher.erase(test_cipher.begin(), test_cipher.end());
                is_duplicate = false;
            }
            if (input->attempt >= input->size) {
                input->attempt = 0;
                fail_to_match = true;
            }
        }

        input->decrypted = input->matching_dictionary[input->attempt];

        if (fail_to_match) {
            for (auto i = 0; i < static_cast<int>(input->encrypted.size()) ; i++) {
                enc = input->encrypted[i];
                att = input->matching_dictionary[fallback_attempt][i];
                test_cipher.insert(std::pair<char, char>(enc, att));
                for (auto f: *cipher){
                    if ((f.first != enc) && (f.second == att)) {
                        temp = f.first;
                        cipher->erase(f.first);
                        cipher->insert(std::pair<char, char>(f.first, ' '));
                    }
                }       
                is_collision = true;
                input->attempt = fallback_attempt;
                input->decrypted = input->matching_dictionary[fallback_attempt];
            }
        } else {
            // do_nothing
        }

        input->test_solution = true;
        // if we get here, then we can write/overwrite the cipher.
        
        for (auto it : test_cipher) {
            cipher->erase(it.first);
            cipher->insert(it);
        }

        return is_collision;
    }

// TODO: Remove tracking of size, rep matrix encodes size information for free

    std::string decrypt(std::string input) {
        std::string output = ""; // decrypted output
        std::map<char, char> cipher; // cipher enc->dec
        crypt itsdare[80]; // list of encrypted words
        reps check_reps; // used to calculate reps of word
        int count_words = 0;
        int solved_words = 0;
        int next_word = 0;
        bool skip = false;
        std::map<char, char>::iterator it; // used to get value from map

        // needed for spaces in output text
        cipher.insert(std::pair<char, char>(' ', ' '));

        check_reps.init();

        // init crypt blank entries...
        for (auto i = 0; i < 80; i++) {
            itsdare[i].init();
        }

        bool finished = false; // loop control


        // Step 1: Build seperate struct for each encrypted word
        //      To do this, compare rep matrix and length with that of every
        //      word in the dictionary. This will create a truncated list of
        //      words to test against.
        //      Store an array of dict lengths.
        //      If any dict has a length of zero, the problem is impossible.
        //      If unique chars in string > unique chars in dict, no solution.
        // STRING CUTTING VARS
        size_t loc = 0;
        size_t start = 0; // holds position of start of cut
        size_t len = 0; // holds how long we want to cut
        std::string temp = ""; // holds temporary substr
        // loop verified working
        for (auto i = 0; (loc != std::string::npos) && !skip ; i++){
            loc = input.find(' ', start);
            len = loc - start;
            temp = input.substr(start, len);
            start += (len + 1);
            finished = false;
            check_reps.init();
            // Check to see if word is already in itsdare
            for (auto j = 0; j < 80 && !finished; j++) {
                if (itsdare[j].encrypted == "") {
                    itsdare[j].init(temp);
                    check_reps.find_reps(temp);
                    skip = !this->find_matching(&check_reps, &(itsdare[j]));
                    count_words++;
                    finished = true;
                } else if (itsdare[j].encrypted == temp) {
                    finished = true;
                } else {
                    // do_nothing();
                }
            }
        }
        finished = false; // set to false to reuse


        // Step 2: Take the word with the smallest length, and pick a word.
        //      Add that word to the cipher.
        //      if a letter is already in the cipher, and the attempt changes
        //      it, then cycle through the other possible words and try again.
        //      if this does not work (e.g, we comb through all words in the
        //      dict), then we assume the cipher is wrong, and overwrite it.
        // Step 3: Check to see if the cipher has been changed 
        //      (track with bool- set in step 2)
        //      If cipher has been changed, then invalidate all word-solutions
        //      using the effected characters, save for the last solution.
        //      Go to step 2.

// START CHECKING...
        for (char j = 97; (j < 123 ) && !skip; j++) {
            cipher.insert(std::pair<char, char>(j, ' '));
            // std::cout << j << " = " << cipher[j] << std::endl;
        }
        int safe_limit = 80 * word_count;
        bool cypher_changed = true;
        bool word_changed = true;
        bool sentence_changed = true;
        bool cypher_dupe = false;
        int count = 0;
        while(!skip && !finished) {
            word_changed = false;
            safe_limit--;
            // output = "";
            // for (auto i = 0; i < static_cast<int>(input.size()); i++) {
            //     it = cipher.find(input[i]);
            //     output += it->second;
            // }
            // std::cout << safe_limit << " - " << next_word << " - " << output << " - " << itsdare[next_word].matching_dictionary[itsdare[next_word].attempt] << '\n' << std::flush;
            for (auto i = 0; i < static_cast<int>(itsdare[next_word].encrypted.size()); i++) {
                it = cipher.find(itsdare[next_word].encrypted[i]);
                if (itsdare[next_word].decrypted[i] != it->second || itsdare[next_word].decrypted[i] == ' ') {
                    word_changed = true;
                    sentence_changed = true;
                }
            }
            if (word_changed) {
                cypher_changed = this->test_word(&cipher, &(itsdare[next_word]));
            }
            next_word++;
            if (next_word == count_words) {
                if (cypher_changed || word_changed || sentence_changed) {
                    next_word = 0;
                    cypher_changed = false;
                    sentence_changed = false;
                } else {
                    next_word = 0;
                    count = 0;
                    finished = true;
                    cypher_dupe = false;
                    for (auto i = 97; i < 123; i++) {
                        count = 0;
                        for (auto j: cipher) {
                            if ((j.second == i) && (j.second != ' ')) {
                                count++;
                            }
                            if (count > 2) {
                                finished = false;
                            }
                        }
                    } 
                }
            }
            if (safe_limit == 0) {
                skip = true;
            }
            word_changed = false;
        }

        // Sanity check for cipher.

        for (auto i = 97; (i < 123) && !skip ; i++) {
            count = 0;
            for (auto j : cipher) {
                if ((j.second == i) && (j.second != ' ')) {
                    count++;
                }
                if (count > 1) {
                    skip = true;
                }
            }
            count = 0;
        }


        // for (char j = 97; (j < 123 ) && !skip; j++) {
        //     std::cout << j << " = " << cipher[j] << std::endl;
        // }
        

        // just throwing in spaces for output
        if (skip) {
            cipher.erase(cipher.begin(), cipher.end());
            cipher.insert(std::pair<char, char>(' ', ' '));
            for (auto i = 97; (i < 123); i++) {
                cipher.insert(std::pair<char, char>(i, '*'));
            }
        }

        for (auto i = 0; i < static_cast<int>(input.size()); i++) {
            it = cipher.find(input[i]);
            output += it->second;
        }

        // Step 0: extract data


        // We should track loops. If we find ourselves looping over more than
        // n times, we may be in an infinite loop, and there may simply be no
        // solution. Brainstorm loop detection later, if the judge fails.
        // n = 1,000 * 80 (size of dict * size of input string)
        return output;
    }

};

int main() {
    accel dothedew;

    dothedew.init();

    std::string input = "";
    std::getline(std::cin, input);

    int word_count = std::stoi(input);

    // Read in dictionary 

    for (auto i = 0; i < word_count; i++) {
        std::getline(std::cin, input);
        dothedew.add_to_dict(input);
    }

    while (input != "") {
        std::getline(std::cin, input);
        std::cout << dothedew.decrypt(input) << "\n";
    }
    return 0;
}


/* @END_OF_SOURCE_CODE */