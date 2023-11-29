program stackemup(input, output);
uses
    sysUtils;
type
    deckArray = array[0..51] of char;
    // Could technically have made this an object, or a class, but it did 
    //   not want to cooperate- I had issues initializing an array of objects.
    //   Thankfully, records behave better, even if I need to explicitly initia-
    //   ize them in main. It does not seem to hurt performance any- The same
    //   work would be done either way.
    Shuffle = record
        order : deckArray;
    end; 
    ShuffleArr = array of Shuffle;

var
    space : sizeInt;
    line : ansistring; // Holds a copy of our current input line.
    alpha_deck : deckArray;
    swap_deck : deckArray;
    shuffling : boolean;
    shuffles : ShuffleArr;
    test_cases : longInt; // Number of test cases.
    shuffle_count : longInt; // Number of shuffles in the test case.
    set_shuffle : ShortInt;
    i, j, l : longInt; // Counter Variables

    function delim (var str : ansistring) : sizeInt;
    var
        result, counter, size : sizeInt;
    begin 
        size := Length(str);
        counter := 1;
        result := size + 1;
        while counter < size do
        begin
            if Copy(str,counter,1) = ' ' then
            begin
                result := counter;
                counter := size;
            end;
        counter := counter + 1;
        end;
        delim := result;
    end;

    function cardName (value : char) : ansistring;
    var
        result : ansistring;
        card : longInt;
    begin
        card := longInt(value) mod 13;

        case (card) of
            0 : result := '2';
            1 : result := '3';
            2 : result := '4';
            3 : result := '5';
            4 : result := '6';
            5 : result := '7';
            6 : result := '8';
            7 : result := '9';
            8 : result := '10';
            9 : result := 'Jack';
            10 : result := 'Queen';
            11 : result := 'King';
            12 : result := 'Ace';
        else
            result := 'Oh, dear!';
        end;

        result := result + ' of ';

        if value <= char(12) then
            result := result + 'Clubs'
        else if (value > char(12)) and (value <= char(25)) then
            result := result + 'Diamonds'
        else if (value > char(25)) and (value <= char(38)) then
            result := result + 'Hearts'
        else if value > char(38) then
            result := result + 'Spades';

        cardName := result;
    end;
begin
    // Get first line of input, test case count.
    readln(line);
    test_cases := StrToInt(line);
    // Main for loop- Originally from i = 0 to (i < test_cases)
    for l := 0 to test_cases - 1 do
    begin
        // re-initialize deck for every test case
        for i := 0 to 51 do 
        begin
            alpha_deck[i] := char(i);
            swap_deck[i] := char(i);
        end;

        // Get first line of test case, number of shuffles.
        repeat readln(line) until not (line = '');

        shuffle_count := StrToInt(line);
        setlength(shuffles, shuffle_count);
        for i := Low(shuffles) to High(shuffles) do
            for j := Low(shuffles[i].order) to High(shuffles[i].order) do
                shuffles[i].order[j] := char(0);

        // read in shuffles

        for i := 0 to shuffle_count - 1 do
        begin
            readln(line);
            for j := 0 to 51 do 
            begin
                if (line = '') then readln(line);
                space := delim(line);
                shuffles[i].order[j] := char(StrToInt(Copy(line, 0, space - 1)) - 1);
                Delete(line, 1, space);
            end;
        end;

        // read out order
        shuffling := true;
        set_shuffle := 0;

        readln(line);
        set_shuffle := StrToInt(line) - 1;
        repeat
            for i := 0 to 51 do
                swap_deck[i] := alpha_deck[ShortInt(shuffles[set_shuffle].order[i])];
            
            for i := 0 to 51 do
                alpha_deck[i] := swap_deck[i];
            
            readln(line);
            if line = '' then shuffling := false 
                else set_shuffle := StrToInt(line) - 1;

        until not shuffling;

        // output final order
        for i := Low(alpha_deck) to High(alpha_deck) do
            writeln(cardName(alpha_deck[i]));
        
        if l < (test_cases) - 1 then
            writeln('');
        
    end;
end.