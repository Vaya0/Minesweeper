#include<iostream>

constexpr int N = 10;

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
	return element == '*';
}

void placeMines(char playingField[][N], int sizeOfField, int numberOfMines) {

	srand(time(0));

	for (int i = numberOfMines; i > 0; i--) {
		int row = rand() % 10;
		int coll = rand() % 10;

		isValidCoordinatesForMine(row, coll, sizeOfField);

		if (isAlreadyAssignedValue(playingField[row][coll])) {
			i++;
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

void countMines(char playingField[][N], int sizeOfField) {
	for (int i = 0; i < sizeOfField; i++) {
		for (int j = 0; j < sizeOfField; j++) {
			if (playingField[i][j] != '*') {
				countMinesAroundEachElement(playingField, sizeOfField, i, j);
			}
		}
	}
}

bool isValidUserInput(int x, int y, char command, int sizeOfField)
{
	return (command == '@' || command == '#' || command == '$')
		&& x >= 0 && x < sizeOfField && y >= 0 && y < sizeOfField;
}

//void createFunctionality(char visibleValuesOfField[][N], char playingField[][N], int sizeOfField, int numberOfMines) {

//}

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
	printField(visibleValuesOfField, sizeOfField);
	countMines(playingField, sizeOfField);
	std::cout << "If You want to open a cell, please enter: @." << std::endl;
	std::cout << "If You want to mark a cell as a possible mine, please enter: #" << std::endl;
	std::cout << "If You want to unmark said cell, please enter: $" << std::endl;
	//createFunctionality(visibleValuesOfField, playingField, sizeOfField, numberOfMines);
}