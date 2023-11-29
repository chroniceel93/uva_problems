program jollyjumper(input, output);
uses
    sysUtils, StrUtils; // This is mostly useful for string Ops.
type
    jumperArray = array[0..3001] of longInt;
var
    size : longInt;
    diff : longInt;
    counter : longInt; // Re-usable counter variable.
    isJumper : boolean;
    cont : boolean;
    space : sizeInt; // Holds location of the next space character.
    line : ansistring; // Holds a copy of our current line.
    jumpers : jumperArray;
    testers : jumperArray;

    function delim (str : string) : longInt;
    var
        result, counter : longInt;
    begin
        counter := 1;
        while counter < High(str) do
        begin
	    if str[counter] = ' ' then
            begin
                result := counter;
                counter := High(str);
            end;
	    counter := counter + 1;
        end;
        delim := result;
    end;


begin
    cont := true;
    isJumper := true;
    while cont = true do
    begin
        // Read stdin to a string.
        readln(line);
        // If input is empty, then exit out of main loop.
        if (line = '') then
	        cont := false
        else
        begin
            line := Trim(line);
            // First value is the number of inputs- Extract it, and continue
            //size := ExtractSubstr(line, space, ' ');
            space := delim(line);
            size := StrToInt(Copy(line, 0, space - 1));
	    Delete(line, 1, space);
            line := Trim(line);
        end;
        
        for counter := Low(testers) to High(testers) do
        begin
            testers[counter] := 0;
            jumpers[counter] := 0;
        end;
        // If string is non-empty, then we continue, otherwise, we exit.
        if (Length(line) > 0) and (cont = true) then
        begin
            isJumper := true;
            // This loop breaks the string down into an array of numbers
            counter := Low(jumpers);
            while Length(line) > 0 do
            begin
                // get next space
                space := delim(line);
                // Saves the contents of the string after the delimiter to
                //   second
                jumpers[counter] := StrToInt(LeftStr(line, space - 1));
                // Increase the counter, so next loop we save to a different
                //   index
                counter := counter + 1;
                // Deletes the contents of the string after, and including, the
                //   delimiter
                Delete(line, 1, space);
                // Trim whitespace, as needed
                line := Trim(line);
            end; // loop ends when line is empty.

        // This loop finds the difference of each successive pair of items in
        //   the array. The loop starts at index 0, and goes to size - 1 to
        //   avoid accessing out-of-bounds memory. For each loop, we set the
        //   value to one at a given index = diff.
        counter := Low(jumpers);
        while (counter < size - 1) and isJumper do
        begin
            diff := jumpers[counter] - jumpers[counter + 1];
            // abs
            if diff < 0 then
                diff := diff * -1;
            // else do_nothing;

            // If the value at testers[diff] is not zero, then the sqeuence has
            // a duplicate diff, and as it has n numbers, and must have one of
            // every number, then it is, by definition, not a jolly number.
            if testers[diff] = 0 then
                testers[diff] := 1
            else
            begin
                counter := size - 1; // effectively breaks loop
                isJumper := false;
            end;
	    counter := counter + 1; // increment every loop.
        end;

        // This loop determines if the sequence was a jolly number- Skipping
        //   zero, we check every item in the array up to the size of the
        //   sequence. If any value is zero, then it is not a jolly number.
        counter := 1;
        while (counter < size) and (isJumper) do
        begin
            if testers[counter] = 0 then
            begin
                isJumper := false;
                counter := size;
            end;
	    counter := counter + 1; // increment every loop.
        end;


        // Print result for this loop.
        if isJumper then
            writeln('Jolly')
        else
            writeln('Not jolly');

        // reset

        for counter:= Low(testers) to High(testers) do
        begin
            testers[counter] := 0;
            jumpers[counter] := 0;
        end;
    end;
end;
end.
