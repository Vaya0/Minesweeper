/**
*
* Solution to course project # 05
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Vaya Yandina
* @idnumber 5MI0600284
* @compiler VC
*
* <minesweeper game>
*
*/

#include <iostream>

constexpr int N = 10;

void printDirections() {
	std::cout << "If You want to open a cell, please enter: @" << std::endl;
	std::cout << "If You want to mark a cell as a possible mine, please enter: #" << std::endl;
	std::cout << "If You want to unmark said cell, please enter: $" << std::endl;
}

void printField(char visibleValuesOfField[][N], int sizeOfField) {

	for (int row = 0; row < sizeOfField; row++) {
		for (int coll = 0; coll < sizeOfField; coll++) {
			std::cout << "{" << visibleValuesOfField[row][coll] << "}";
		}
	    std::cout << std::endl;
	}
	std::cout << std::endl;

}

void isValidSizeOfField(int& sizeOfField) {
	while (sizeOfField < 3 || sizeOfField>10) {
		std::cout << "Incorrect size (0 m 0)! Please enter a number that is between 3 and 10!: " << std::endl;
		std::cin >> sizeOfField;
	}
}

void isValidNumberOfMines(int& numberOfMines, int& sizeOfField) {
	while (numberOfMines < 1 || numberOfMines > 3 * sizeOfField) {
		std::cout << "Incorrect size (0 m 0)! Please enter a number that is between 1 and" << sizeOfField * 3 << "!: " << std::endl;
		std::cin >> numberOfMines;
	}
}

void fillPlayingFieldWithValues(char playingField[][N], char value) {

	for (int row = 0; row < N; row++) {
		for (int coll = 0; coll < N; coll++) {
			playingField[row][coll] = value;
		}
	}

}

void isValidCoordinatesForMine(int& row, int& coll, int sizeOfField) {

	while (row >= sizeOfField) {
		row = rand() % 10;
	}
	while (coll >= sizeOfField) {
		coll = rand() % 10;
	}

}

bool isAlreadyAssignedValue(char element) {
	return element == '*';//ako elementut veche e bomba
}

void placeMines(char playingField[][N], int sizeOfField, int numberOfMines) {

	srand(int(0));

	for (int i = 1; i <= numberOfMines; i++) {
		int row = rand() % 10;
		int coll = rand() % 10;// davame nqkakvi koordinati, no ne sme sigurnu che te shte popadnat v poleto

		isValidCoordinatesForMine(row, coll, sizeOfField);// ako sa tvurde golemi produljavame da priemame novi i novi

		if (isAlreadyAssignedValue(playingField[row][coll])) {// dali veche e slojena mina, zashtoto random chisla moche da se povtarqt
			i--;//podsigurqvame se che ako koordinatite sa bili ok, no veche e imalo, nqma da slojim vtora mina na sushtoto mqsto
		}
		else {
			playingField[row][coll] = '*';
		}
	}

}
char getCharFromInt(int ind) {
	return ind + '0';
}

void countMinesAroundEachElement(char playingField[][N], int sizeOfField, int row, int coll) {

	int count = 0;
	if (coll + 1 < sizeOfField) {
		if (playingField[row][coll + 1] == '*') {
			count++;
		}
	}
	if (coll + 1 < sizeOfField && row + 1 < sizeOfField) {
		if (playingField[row + 1][coll + 1] == '*') {
			count++;
		}
	}
	if (row + 1 < sizeOfField) {
		if (playingField[row + 1][coll] == '*') {
			count++;
		}
	}
	if (row + 1 < sizeOfField && coll - 1 >= 0) {
		if (playingField[row + 1][coll - 1] == '*') {
			count++;
		}
	}
	if (coll - 1 >= 0) {
		if (playingField[row][coll - 1] == '*') {
			count++;
		}
	}
	if (coll - 1 >= 0 && row - 1 >= 0) {
		if (playingField[row - 1][coll - 1] == '*') {
			count++;
		}
	}
	if (row - 1 >= 0) {
		if (playingField[row - 1][coll] == '*') {
			count++;
		}
	}
	if (coll + 1 < sizeOfField && row - 1 >= 0) {
		if (playingField[row - 1][coll + 1] == '*') {
			count++;
		}
	}
	playingField[row][coll] = getCharFromInt(count);
}

void countMines(char playingField[][N], int sizeOfField) {//minavame prez tsqlata matritsa
	for (int row = 0; row < sizeOfField; row++) {
		for (int coll = 0; coll < sizeOfField; coll++) {
			if (playingField[row][coll] != '*') {
				countMinesAroundEachElement(playingField, sizeOfField, row, coll);
			}
		}
	}
}

bool isValidUserInput(int row, int coll, char command, int sizeOfField){
	return (command == '@' || command == '#' || command == '$')
		&& row >= 0 && row < sizeOfField && coll >= 0 && coll < sizeOfField;
}


void mark(char visibleValuesOfField[][N], const char playingField[][N], int sizeOfField,
	int row, int coll, unsigned& numberOfFlagsLeft, int& numberOfMines) {

	if (visibleValuesOfField[row][coll] == '#') {
		std::cout << "You have already marked this cell! " << std::endl;
	}
	else if (visibleValuesOfField[row][coll] != ' ') {
		std::cout << "You have already opened this cell! " << std::endl;
	}
	else {
		visibleValuesOfField[row][coll] = '#';
		numberOfFlagsLeft--;
		if (playingField[row][coll] == '*') {
			numberOfMines--;
		}
	}
}


void unmark(char visibleValuesOfField[][N], const char playingField[][N], int sizeOfField,
	int row, int coll, unsigned numberOfFlagsLeft, int numberOfMines) {
	if (visibleValuesOfField[row][coll] == '#') {
		visibleValuesOfField[row][coll] = ' ';
		numberOfFlagsLeft += 1;
		if (visibleValuesOfField[row][coll] == ' ' && playingField[row][coll] == '*') {
			numberOfMines += 1;
		}
	}
	else {
		std::cout << "You cannot unmark a cell that has not been flagged as a possible mine yet! " << std::endl;
	}
}

void openAdjacent(char playingField[][N], char visibleValuesOfField[][N], int sizeOfField, int row, int coll, bool& gameLost, int& movesLeft) {
	if (row < 0 || row >= sizeOfField || coll < 0 || coll >= sizeOfField || visibleValuesOfField[row][coll] != ' ') {
		return;
	}
	visibleValuesOfField[row][coll] = playingField[row][coll];
	movesLeft--;

	if (playingField[row][coll] == '*') {
		return;
	}

	if (playingField[row][coll] == '0') {
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row - 1, coll, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row + 1, coll, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row, coll - 1, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row, coll + 1, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row - 1, coll - 1, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row - 1, coll + 1, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row + 1, coll - 1, gameLost, movesLeft);
		openAdjacent(playingField, visibleValuesOfField, sizeOfField, row + 1, coll + 1, gameLost, movesLeft);
	}

	gameLost = false;
}

void open(char playingField[][N], char visibleValuesOfField[][N], int sizeOfField, int row, int coll, bool& gameLost, int& movesLeft) {
	if (movesLeft == 0) {
		return;
	}

	if (visibleValuesOfField[row][coll] == '#') {
		std::cout << "Unable to open marked cell! (~~ o ~~)";
		return;
	}
	else if (visibleValuesOfField[row][coll] != ' ') {
		std::cout << "Cell is already opened! (`` ^ ``) " << std::endl;
		return;
	}

	openAdjacent(playingField, visibleValuesOfField, sizeOfField, row, coll, gameLost, movesLeft);

	if (playingField[row][coll] == '*') {
		for (int i = 0; i < sizeOfField; i++) {
			for (int j = 0; j < sizeOfField; j++) {
				if (playingField[i][j] == '*') {
					visibleValuesOfField[i][j] = playingField[i][j];
					gameLost = true;
					return;
				}
			}
		}
	}
	gameLost = false;
}


void createFunctionality(char visibleValuesOfField[][N], char playingField[][N], int sizeOfField, int numberOfMines) {
	bool gameLost = false;
	int movesLeft = sizeOfField * sizeOfField - numberOfMines;
	unsigned numberOfFlagsLeft = numberOfMines;
	char command;
	int row;
	int coll;

	do {//ako e s while ne mojem da ispolzvame promenlivite pri proverkata 
		std::cout << "Please enter the desired command {@, #, $} and the coordinates of the cell that You have chosen!: ";
		std::cin >> command;
		std::cin >> row;
		std::cin >> coll;
		if (isValidUserInput(row, coll, command, sizeOfField)) {
			if (command == '@') {
				open(playingField, visibleValuesOfField, sizeOfField, row, coll, gameLost, movesLeft);
				if (gameLost) {
					std::cout << "You have stepped on a mine! Game lost! (# o #)" << std::endl;
					break;
				}
			}
			else if (command == '#') {
				mark(visibleValuesOfField, playingField, sizeOfField, row, coll, numberOfFlagsLeft, numberOfMines);
			}
			else if (command == '$') {
				unmark(visibleValuesOfField, playingField, sizeOfField, row, coll, numberOfFlagsLeft, numberOfMines);
			}

			printField(visibleValuesOfField, sizeOfField);

			if (numberOfMines == 0 && movesLeft == 0) {
				std::cout << "Congratulations, You won !!! (^ o ^)" << std::endl;
				gameLost = true;
				break;
			}
		}
		if (!isValidUserInput(row, coll, command, sizeOfField)) {
			std::cout << "Incorrect input! (0 m 0)" << std::endl;
			return;
		}
	} while (!gameLost);
	return;
}

int main() {
	std::cout << "Please enter the desired size of the playing field {between 3 and 10}: " << std::endl;
	int sizeOfField;
	std::cin >> sizeOfField;
	isValidSizeOfField(sizeOfField);
	std::cout << "Please enter the desired number of mines {between 1 and " << 3 * sizeOfField << "}: " << std::endl;
	int numberOfMines;
	std::cin >> numberOfMines;
	isValidNumberOfMines(numberOfMines, sizeOfField);

	char playingField[N][N];
	char visibleValuesOfField[N][N];

	fillPlayingFieldWithValues(playingField, ' ');
	fillPlayingFieldWithValues(visibleValuesOfField, ' ');

	placeMines(playingField, sizeOfField, numberOfMines);
	countMines(playingField, sizeOfField);
	printField(visibleValuesOfField, sizeOfField);
	printDirections();
	createFunctionality(visibleValuesOfField, playingField, sizeOfField, numberOfMines);
}
