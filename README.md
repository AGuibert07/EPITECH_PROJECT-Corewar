# Epitech Project : Corewar

### Description
The goal of the **Corewar** project was to recode in C the corewar video game. I had to create a virtual memory in which at most four programs 
(called 'champions') fight to be the last survivor : each program, coded in redcode assembly and compiled to a binary file, has to execute the
'live' instruction regularly to indicate to the game that it is still alive. When a champion does not execute the 'live' instruction during a given
laps of time, it is considered as dead and is no longer executed. The last champion alive is declarated winner.
This project follows up on the previous project, **robot-factory**, which consisted to create the redcode assembly compiler.

### Contributors
- Alexis Guibert {[LinkedIn](https://www.linkedin.com/in/alexis-guibert-it/) / [Github](https://github.com/AGuibert07)}

### Installation
First, clone this repository using
```
git clone git@github.com:AGuibert07/EPITECH_PROJECT-Corewar.git
```
Then, compile the C code using the `make` command. To compile the program with the Terminal User Interface, use `make bonus`.

### Usage
```
$> ./corewar -h
USAGE
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...
DESCRIPTION
-dump nbr_cycle dumps the state of the virtual machine after the nbr_cycle execution
-n prog_number sets the next program’s number. By default, the first free number in the parameter
order
-a load_address sets the next program’s loading address. When no address is specified, optimize the
addresses so that the processes are as far away from each other as possible. The addresses are
MEM_SIZE modulo.
```

### Technologies Used
- **Coding language** C
- **Terminal User Interface (TUI)** ncurses
