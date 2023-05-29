program threenone(input, output);
uses
    sysUtils;
var
    i : longInt; // Control variable, controls loops
    first, second, temp, max : longInt;
    cont, lineEmpty : boolean; // Control variable, exits program
    space : SizeInt;
    line : string;

    function recurse (num : longInt) : longInt;
    var
        res : longInt = 0;
        tick : longInt = 0;
    begin
        if (num mod 2) > 0 then
            res := (3 * num) + 1
        else
            res := round(num / 2);

        if res = 1 then
            tick := 1
        else
            tick := recurse(res);
        
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
    cont := true;
    lineEmpty := true;

    while cont = true do
    begin
        // line := '';qu
        readln(line);
        line := Trim(line);
        if Length(line) > 0 then
        begin
            while Length(line) > 0 do
            begin
                space := LastDelimiter(' ', line);
                second := StrToInt(RightStr(line, (Length(line)-space)));
                Delete(line, space, (Length(line)-space)+1);
                line := Trim(line);
                space := LastDelimiter(' ', line);
                if space > 0 then
                begin
                    first := StrToInt(RightStr(line, (Length(line)-space)));
                    Delete(line, space, (Length(line)-space)+1);
                    line := Trim(line);
                end
                else
                begin
                    first := StrToInt(line);
                    line := '';
                end;
                temp := 0;
                max := test(first, second);
                writeln(IntToStr(first) + ' ' + IntToStr(second) + ' ' + IntToStr(max))
            end;
        end
        else
            cont := false;
    end;
end.