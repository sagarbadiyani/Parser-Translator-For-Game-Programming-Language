# Parser-Translator-For-Game-Programming-Language

## Compilation
Run Makefile by entering the command `make`

## Execution
This will generate an executable file - **test**
Run the command `./test`

## Files
- scanner.l : This is the flex file
- parser.y : This is the Bison file
- driver.c : This is the main C code

## Assumtions
- For a row `4 2 2 4`, the instruction `SUBTRACT LEFT.` will give `4 0 4 0`.
- The start state has 1 random tile placed on the grid.
- `ADD LEFT..` or `ADD LEFT.abc` (and such commands where there are characters after the fullstop) will give an Error. 
