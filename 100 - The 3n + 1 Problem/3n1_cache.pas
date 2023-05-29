
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

// NOTE: Program appaears to complete in roughly half the time compared to the C++
// version, as per the onlinejudge's timer.

program threenone(input, output);
uses
    sysUtils; // This is mostly useful for stringOps
type
    cacheArray = array [0..100000] of longInt; // we define our array type here
var
    i : longInt; // Control variable, controls loops
    first, second, max : longInt;
    cont : boolean; // Control variable, exits program
    space : SizeInt; // Holds location of the next space character
    line : string; // our input line
    cache : cacheArray; // Our cache, as in the c++ solution

    function recurse (num : longInt) : longInt;
    var
        res : longInt = 0;
        tick : longInt = 0;
    begin
        if (num mod 2) > 0 then
            res := (3 * num) + 1
        else 
            res := round(num / 2);

        if res > 100000 then
            tick := recurse(res)
        else if (cache[res] = 0) and (res <> 1) then
        begin
            tick := recurse(res);
            cache[res] := tick;
        end
        else if res = 1 then
            tick := 1
        else
            tick := cache[res];
        
        recurse := tick + 1;
    end;

    function test (low : longInt; high : longInt) : longInt;
    var
        testVar : longInt = 0;
        max : longInt = 0;
    begin
        if low > high then
        begin
            testVar := low;
            low := high;
            high := testVar;
        end;

        for i := low to high do
        begin
            if i = 1 then
                testVar := 1
            else
                testVar := recurse(i);
            
            if testVar > max then
                max := testVar;
        end;

        test := max;
    end;

begin
    for i := 0 to 100000 do
        cache[i] := 0;

    cont := true;

    while cont = true do
    begin
    // The biggest change in this port is in how the input is parsed- Instead of
    // We read stdin to a string like before, but the array of functions we have
    // are rather a bit different- In this case, leadning me to take a 
    // right-to-left approach to breaking up the string into ints.
        readln(line);
        line := Trim(line);
        if Length(line) > 0 then
        begin
        // Here, Is fixed a small little issue, that UVA evidently does not
        // care too much about, but throws a flag in the debug-checker,
        // where you have multiple inputs on one line. It'll set things to loop
        // while the string isn't empty
            while Length(line) > 0 do
            begin
                // get last space
                space := LastDelimiter(' ', line);
                // Saves the contents of the string after the delimiter to 
                //  second
                second := StrToInt(RightStr(line, (Length(line)-space)));
                // Deletes the contents of the string after, and including, the 
                //  delimiter
                Delete(line, space, (Length(line)-space)+1);
                // Trims whitespace, in case of excess whitespace
                line := Trim(line);
                // Check for another delimiter. If it exists, then we have 
                //  multiple inputs on this line.
                space := LastDelimiter(' ', line);
                if space > 0 then
                begin // Case multiple inputs
                    // Copy right of string to delimiter, as earlier.
                    first := StrToInt(RightStr(line, (Length(line)-space)));
                    // Delete that run of the string, as earlier.
                    Delete(line, space, (Length(line)-space)+1);
                    // Trim whitespace, as needed.
                    line := Trim(line);
                end
                else
                begin // Case no more inputs
                    // convert string to int, and clear the line
                    first := StrToInt(line);
                    line := '';
                end;
                
                max := test(first, second);
                writeln(IntToStr(first) + ' ' + IntToStr(second) + ' ' + IntToStr(max))
            end;
        end
        else
            cont := false;
    end;
end.