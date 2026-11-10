# Apartment Debt Management

A C++ console application for managing debts of apartment owners in a residential building. It calculates the monthly fee for each apartment, groups apartments by owner, and shows who needs a payment reminder and who has been handed over to a bailiff.

## Features

- Enter data for up to **60 apartments** (name, surname, apartment number, area, debt and payment deadline)
- Automatic **monthly fee calculation** based on the apartment area
- Saves the input to a file (`vlez.dat`) and reads it back
- **Groups apartments by owner**: if one person owns several apartments, their debts and fees are summed and the number of apartments is counted
- **Sorts owners by debt** (from highest to lowest)
- Prints a status for every owner with a debt:
  - debt below 4 monthly fees: **payment reminder** with a deadline date
  - debt of 4 or more monthly fees: **handed over to a bailiff**

## Monthly fee formula

```
monthly fee = 0.1 * area (m²) * 61.5 + 100
```

## Tech and concepts

- **Language:** C++
- Structs, functions and arrays
- File handling (`fstream`)
- String functions (`strcmp`, `strcpy`)
- Bubble sort

## How to compile and run

With g++:

```
g++ main.cpp -o apartments
./apartments
```

On Windows (PowerShell or CMD):

```
g++ main.cpp -o apartments.exe
apartments.exe
```

You can also open the file in Code::Blocks, Dev-C++ or Visual Studio and run it from there.

## Example

Input for 3 apartments (name, surname, apartment number, area, debt, day, month, year):

| Owner | Apartment | Area (m²) | Debt | Deadline |
|-------|-----------|-----------|------|----------|
| Petar Petrovski | 1 | 50 | 1000 | 15/12/2026 |
| Marija Ilieva | 2 | 80 | 3000 | 1/12/2026 |
| Ana Stojanova | 3 | 60 | 0 | 1/1/2027 |

Output (name, number of apartments, debt, status):

```
Marija  1   3000   PREDADEN NA IZVRSITEL.
Petar   1   1000   OPOMENA DA SE PLATI DO: 15/12/2026
Ana     1   0
```

## Notes

- The program creates the file `vlez.dat` in the same folder when it runs.
- The text in the program (prompts and messages) is in Macedonian written in Latin letters.
