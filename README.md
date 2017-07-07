# UTBM_IA41_Pogo

## Information

### School project

- University: [UTBM](http://www.utbm.fr/)
- Unit value: IA41 (Artificial Intelligence: Fundamental Concepts and Dedicated Languages)
- Semester: Spring 2017

### Authors / students

- [Julien Barbier](https://github.com/beta-ray70)
- [Kadir Ercin](https://github.com/Ridakz)
- [Maxime Pinard](https://github.com/pinam45)

### Subject

The goal is to make a program to play the Pogo game and an A.I. able to play the game. The user should be able to play against the A.I., make the A.I. play against itself and choose which play first.

### Realisation

2 versions of the A.I. are implemented, the first uses the [MinMax algorithm](report-fr/algorithms/MinMax.algo) and the second uses the [AlphaBeta algorithm](report-fr/algorithms/AlphaBeta.algo). As both A.I. make the same choices, only the AlphaBeta A.I., the most efficient, is used.

3 game modes available:
- Human vs Human
- Human vs A.I.
- A.I. vs A.I.

For each game, the user must choose who plays first and the depth of each A.I., the depth of the A.I. is the exploration depth of the tree in the MinMax / AlphaBeta algorithm.

The console UI was made with [ConsoleControl](https://github.com/pinam45/ConsoleControl).

For more information about the realisation, see the French report (made with LaTeX) in the [report-fr](report-fr) folder.

## Content

- **cmake/**: CMake related files
- **ConsoleControl/**: ConsoleControl library submodule
- **Pogo/**: Project sources
- **report-fr/**: French report sources

## Compilation

### CMake

For more information about CMake see [the CMake website](https://cmake.org/). Common CMake use:

	$ mkdir build
	$ cd build
	$ cmake ..
	$ make

### Make

For more information about Make see [the GNU website](https://www.gnu.org/software/make/). To compile, use the default target with:

	$ make

For information about the other targets, use:

	$ make help

## Copyright

This work is under the MIT License

[Read the license file](LICENSE)
