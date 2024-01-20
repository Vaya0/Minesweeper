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
* <предназначение на файла>
*
*/


#include <iostream>

constexpr int N = 10;

void printField(char visibleValuesOfField[][N], int sizeOfField) {

	for (int i = 0; i < sizeOfField; i++)
	{
		for (int j = 0; j < sizeOfField; j++)
		{
			std::cout << "{" << visibleValuesOfField[i][j] << "}";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

void isValidSizeOfField(int& sizeOfField) {
	while (sizeOfField < 3 || sizeOfField>10) {
		std::cout << "Incorrect size! Please enter a number that is between 3 and 10!: ";
		std::cin >> sizeOfField;
	}
}

void isValidNumberOfMines(int& numberOfMines, int& sizeOfField) {
	while (numberOfMines < 1 || numberOfMines > 3 * sizeOfField) {
		std::cout << "Incorrect size! Please enter a number that is between 1 and" << sizeOfField * 3 << "!: ";
		std::cin >> numberOfMines;
	}
}

void fillPlayingFieldWithValues(char playingField[][N], char value) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			playingField[i][j] = value;
		}
	}

}

void isValidCoordinatesForMine(int& row, int& coll, int sizeOfField) {

	while (row >= sizeOfField)
	{
		row = rand() % 10;
	}
	while (coll >= sizeOfField)
	{
		coll = rand() % 10;
	}

}

bool isAlreadyAssignedValue(char element)
{
	return element == '*';//ako elementut veche e bomba
}

void placeMines(char playingField[][N], int sizeOfField, int numberOfMines) {

	srand(time(0));

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

void countMinesAroundEachElement(char playingField[][N], int sizeOfField, int i, int j) {

	int count = 0;
	if (j + 1 < sizeOfField) {
		if (playingField[i][j + 1] == '*') {
			count++;
		}
	}
	if (j + 1 < sizeOfField && i + 1 < sizeOfField) {
		if (playingField[i + 1][j + 1] == '*') {
			count++;
		}
	}
	if (i + 1 < sizeOfField) {
		if (playingField[i + 1][j] == '*') {
			count++;
		}
	}
	if (i + 1 < sizeOfField && j - 1 >= 0) {
		if (playingField[i + 1][j - 1] == '*') {
			count++;
		}
	}
	if (j - 1 >= 0) {
		if (playingField[i][j - 1] == '*') {
			count++;
		}
	}
	if (j - 1 >= 0 && i - 1 >= 0) {
		if (playingField[i - 1][j - 1] == '*') {
			count++;
		}
	}
	if (i - 1 >= 0) {
		if (playingField[i - 1][j] == '*') {
			count++;
		}
	}
	if (j + 1 < sizeOfField && i - 1 >= 0) {
		if (playingField[i - 1][j + 1] == '*') {
			count++;
		}
	}
	playingField[i][j] = count;

}

void countMines(char playingField[][N], int sizeOfField) {//minavame prez tsqlata matritsa
	for (int i = 0; i < sizeOfField; i++) {
		for (int j = 0; j < sizeOfField; j++) {
			if (playingField[i][j] != '*') {
				countMinesAroundEachElement(playingField, sizeOfField, i, j);
			}
		}
	}
}

bool isValidUserInput(int row, int coll, char command, int sizeOfField)
{
	return (command == '@' || command == '#' || command == '$')
		&& row >= 0 && row < sizeOfField && coll >= 0 && coll < sizeOfField;
}


void open(char visibleValuesOfField[][N], const char playingField[][N], int sizeOfField,
			unsigned& movesLeft, int row, int coll, bool& gameOver) {


}

void mark(char visibleValuesOfField[][N], const char playingField[][N], int sizeOfField,
			int row, int coll, unsigned numberOfFlagsLeft, int numberOfMines) {

	if (visibleValuesOfField[row][coll] == '%') {//if marked
		std::cout << "You have already marked this cell! ";
	}
	else if (visibleValuesOfField[row][coll] != ' ') {//has the number of mines near it
		std::cout << "You have already opened this cell! ";
	}
	else {
		visibleValuesOfField[row][coll] = '%';//mark it
		numberOfFlagsLeft--;
		if (playingField[row][coll] == '*') {
			numberOfMines--;
		}
	}
}


void unmark(char visibleValuesOfField[][N], const char playingField[][N], int sizeOfField,
			int row, int coll, unsigned numberOfFlagsLeft, int numberOfMines) {
	if (visibleValuesOfField[row][coll]  == '%') {
		visibleValuesOfField[row][coll] = ' ';
		numberOfFlagsLeft += 1;
		if (visibleValuesOfField[row][coll] == ' ' && playingField[row][coll] == '*')
			numberOfMines += 1;
	}
	else {
		std::cout << "You cannot unmark a cell that has not been flagged as a possible mine yet!";
	}
}


void createFunctionality(char visibleValuesOfField[][N], char playingField[][N], int sizeOfField, int numberOfMines) {
	bool gameLost = false;
	unsigned movesLeft = sizeOfField * sizeOfField - numberOfMines;
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
				open(visibleValuesOfField, playingField, sizeOfField, movesLeft, row, coll, gameLost);
			}
			else if (command == '#') {
				mark(visibleValuesOfField, playingField, sizeOfField, row, coll, numberOfFlagsLeft, numberOfMines);
			}
			else if (command == '$') {
				unmark(visibleValuesOfField, playingField, sizeOfField, row, coll, numberOfFlagsLeft, numberOfMines);
			}
			printField(visibleValuesOfField, sizeOfField);
			if (!gameLost && !movesLeft)
			{
				std::cout << "Congratulations, You won !!! (^o^)";
				gameLost = true;
			}
		}
		if (!isValidUserInput(row, coll, command, sizeOfField)) {
			std::cout << "Incorrect input!";
		}
	} while (!gameLost);
	return;
}

int main() {
	std::cout << "Please enter the desired size of the playing field {between 3 and 10}: ";
	int sizeOfField;
	std::cin >> sizeOfField;
	isValidSizeOfField(sizeOfField);
	std::cout << "Please enter the desired number of mines {between 1 and " << 3 * sizeOfField << "}: ";
	int numberOfMines;
	std::cin >> numberOfMines;
	isValidNumberOfMines(numberOfMines, sizeOfField);

	char playingField[N][N];
	char visibleValuesOfField[N][N];

	fillPlayingFieldWithValues(playingField, ' ');
	fillPlayingFieldWithValues(visibleValuesOfField, '?');

	placeMines(playingField, sizeOfField, numberOfMines);
	countMines(playingField, sizeOfField);
	printField(visibleValuesOfField, sizeOfField);
	std::cout << "If You want to open a cell, please enter: @." << std::endl;
	std::cout << "If You want to mark a cell as a possible mine, please enter: #" << std::endl;
	std::cout << "If You want to unmark said cell, please enter: $" << std::endl;
	createFunctionality(visibleValuesOfField, playingField, sizeOfField, numberOfMines);
}