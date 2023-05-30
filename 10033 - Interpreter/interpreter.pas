program interpreter (input, output);
uses sysUtils, math;

type
    ramArray = array [0..999] of NativeUInt;
    regArray = array [0..9] of NativeUInt; 

var
    ram : ramArray;
    reg : regArray;
    cont : boolean; // Exit control variable
    line : string; // Current user input
    runs : integer; // Number of test cases in input
    insc : NativeUInt; // Keeps track of cycle count

    {Reset the system}
    procedure clearSYS();
    var
        z : integer = 0;
    begin
        for z := 0 to 999 do
            ram[z] := 0;

        for z := 0 to 9 do
            reg[z] := 0;
    end;

    procedure readRAM();
    var
        loop : boolean;
        PC : integer;
    begin
        loop := true;
        PC := 0;

        // As long as we aren't empty, we're reading instructions
        while loop do
        begin
            readln(line);
            Trim(line);
            if Length(line) > 0 then
            begin
                ram[PC] := StrToInt(line);
            end
            else
                loop := false; 
            PC := PC + 1;
        end;
    end;

    function execPRG() : integer;
    var
        tick : NativeUInt;
        PC : integer;
        halt : boolean;
        a, b, c : integer;
        inst : integer; // value used for decoding register.
    begin
        PC := 0;
        tick := 0;
        halt := false;

        // How do we want to decode instructions?
        // 1 - Convert to string- *SLOW*, but works
        // 2 - bitwise math- How's that work with base10?
        // 3 - modulous operator- Duh.
        while not halt do
        begin
            tick := tick + 1;
            // Decode instruction, and execute
            inst := ram[PC];
            c := inst mod 10;
            inst := Floor(inst / 10);
            b := inst mod 10;
            inst := Floor(inst / 10);
            a := inst mod 10;

            PC := PC + 1;
            
            // HAHAHAHAHAHAHAHA
            // I cannot believe how obtuse my original implementation was
            case (a) of
            0 : if reg[c] <> 0 then PC := reg[b];
            1: halt := true;
            2: reg[b] := c;
            3: reg[b] := (reg[b] + c) mod 1000;
            4: reg[b] := (reg[b] * c) mod 1000;
            5: reg[b] := reg[c];
            6: reg[b] := (reg[b] + reg[c]) mod 1000;
            7: reg[b] := (reg[b] * reg[c]) mod 1000;
            8: reg[b] := ram[reg[c]];
            9: ram[reg[c]] := reg[b];
            end;
        end;
        execPRG := tick; // STUB
    end;

begin
    cont := true;

    // first line input holds run count
    readln(line);
    line := Trim(line);
    runs := StrToInt(line);

    // blank line follows
    readln(line);

    while cont do
    begin
        insc := 0;
        clearSYS(); // Reset system state

        readRAM();

        insc := execPRG();

        runs := runs - 1;

        if runs <= 0 then
        begin
            cont := false;
            writeln(insc);
        end
        else
        begin
            writeln(insc);
            writeln();
        end;
    end;


end.