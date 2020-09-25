# Two Pass Assembler
* Basic two pass assembler written in C++ for CEC18: Compiler Construction coursework

## Installing 2PA:
1. Run:
```
$ git clone https://github.com/Nipunnyka/Compilers.git
```
2. Run 
```
cd 2P_assembler && g++ tpa.cpp && ./a.out
```
3. Enter 8085 assembler code in `input.txt` and expect machine code in `otput.txt`

## Two Pass Assemblers
* Assembler have been famously used to convert source program to executable machine code
* Low Level Assembly code can be directly converted to machine code without many intermediate steps so we will be usin 8085 assembly code in this program to understand the functioning of assemblers
![Image of pipeline of compiler]()</br>
The pipeline of our 2PA is as follows:
![Image of 2PA pipeline]()</br>
* In the Analysis pass, we identify labels and literals and store them along with theit locations in the symbol and literal table
    * The psuedo-algo for pass 1 is as follow:
    ```
    Pass1(){
        for(line: program)
            for(word: line)
                if(word==label)
                    store (label, location) in SYMBOL_TABLE
        location++  
    }
    ```
* In the Synthesis pass, we will go through the code word by word and converting source code keyword to machine code and identified symbols and literals from Symbol Table to machine code
    * The psude-algo for pass 2 is as follows:
    ```
    Pass2(){
        for(word: program){
            if(word==label)
                skip
            identify format of given word
                input other required words 
                for(word: required in format)
                    if(word==label)
                        search for location in symbol table 
                        convert location to binary number and insert into machine code file
                    else{
                        find its machine code and insert into output file
                    }
        }
    }
    ```

Note: 8085 assembly code is very close to machine code so the object code and linker phases in the image above have been entirely skipped

## Notes for Nerds
### Checked Errors
* Source/Target File couldnt be opened
* Desired Label not found
* Invalid instruction whose opcode isnt identified

### Unchecked Errors
The program relies on the input to be of valid syntax and no checks are made, the program will behave unpredictably in case of violation.
* Format
    * Labels must be immediately followed by `:` like `label:` 
    * If the opcode is documented to be followed x regiter and y numbers then it must follow that
    * A new operation must be requested in a new line bc I am tracking location counter wrt line number
* Resource Limitations
    * I have only added a few instruction of 8085 ISA so add as required in future
    * Only Register from R0-R7 have been coded, the `getRegCode()` returns an erroroneous value of `11111` which isnt checked further so maybe accomodate that in future

Disclaimer: not tested thoroughly, may generate undocumented errors

