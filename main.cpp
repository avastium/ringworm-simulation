#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class TRingworm {
public:
	int size;
	int** area;
	int** timings;
	void createArea() {
		area = new int* [size];
		timings = new int* [size];
		for (int i = 0; i < size; ++i) area[i] = new int[size];
		for (int i = 0; i < size; ++i) timings[i] = new int[size];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				area[i][j] = 0;
				timings[i][j] = 0;
			}
		}
		area[size / 2][size / 2] = 1;
		timings[size / 2][size / 2] = 1;
	}
	void outputArea() {
		system("cls");
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				switch (area[i][j]) {
				case 0:
					SetConsoleTextAttribute(hConsole, 0xF | 0xA0);
					break;
				case 1:
					SetConsoleTextAttribute(hConsole, 0xF | 0xC0);
					break;
				case 2:
					SetConsoleTextAttribute(hConsole, 0xF | 0xE0);
					break;
				}
				cout << " " << " ";
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hConsole, 0xF | 0xF);
	}
	void nextStep() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (area[i][j] == 1) {
					if (i != 0) {
						int rnd = rand() % 2;
						if (rnd == 1 && area[i - 1][j] == 0) area[i - 1][j] = 9;
					}
					if (i != size - 1) {
						int rnd = rand() % 2;
						if (rnd == 1 && area[i + 1][j] == 0) area[i + 1][j] = 9;
					}
					if (j != 0) {
						int rnd = rand() % 2;
						if (rnd == 1 && area[i][j - 1] == 0) area[i][j - 1] = 9;
					}
					if (j != size - 1) {
						int rnd = rand() % 2;
						if (rnd == 1 && area[i][j + 1] == 0) area[i][j + 1] = 9;
					}
				}
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (area[i][j] == 9) area[i][j] = 1;
				if (area[i][j] == 1 || area[i][j] == 2) timings[i][j]++;
				if (timings[i][j] == 6) area[i][j] = 2;
				if (timings[i][j] == 10) {
					area[i][j] = 0;
					timings[i][j] = 0;
				}
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));
	TRingworm model{};
	do {
		cout << "Enter the size of the skin area (odd number): ";
		cin >> model.size;
	} while (model.size % 2 == 0);
	model.createArea();
	model.outputArea();
	while (true) {
		cout << "Use ENTER to continue simulation." << endl;
		cin.get();
		model.nextStep();
		model.outputArea();
	}
	system("pause");
	return 0;
}