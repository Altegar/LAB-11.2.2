// LAB-11.2.2.cpp
// Сушинський Ігор
// Лабораторія №11.2
// Послідовний пошук в масиві структур.
// Варіант 18
// 2 завдання

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

enum Specialnist { KOMPUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_TA_EKONOMIKA, FIZYKA_TA_INFORMATYKA, TRUDOVE_NAVCHANYA };

string specialnistStr[] = { "КН", "ІН", "МЕ", "ФІ", "ТН" };

struct Student
{
	string prizv;
	unsigned kurs;
	Specialnist specialnist;
	unsigned fizyka;
	unsigned matematika;
	union
	{
		unsigned programming;
		unsigned chiselni_metody;
		unsigned pedagogika;
	};
};

void CreateBIN(Student* p, const int N, char* fname);
void PrintBIN(Student* p, const int N, char* fname);
int OcinkaBIN(Student* p, const int N, char* fname);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	char fname[100];						// ім'я файлу
	cout << "Ввести ім'я файлу: "; cin >> fname;

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];

	int count;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід кількості оцінок «добре»" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			CreateBIN(p, N, fname);
			break;
		case 2:
			PrintBIN(p, N, fname);
			break;
		case 3:
			count = OcinkaBIN(p, N, fname);
			cout << "=============================================" << endl;
			cout << "| Якщо оцінка >= 8 або <= 10, то це «добре» |" << endl;
			cout << "---------------------------------------------" << endl;
			cout << "| Кількість оцінок «добре»: " << setw(15) << count << " |" << endl;
			cout << "=============================================" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void CreateBIN(Student* p, const int N, char* fname)
{
	ofstream fout(fname, ios::binary);				// відкрили файл для запису
	int specialnist;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;

		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv); fout << p[i].prizv << endl;
		cout << " курс: "; cin >> p[i].kurs; fout << p[i].kurs << endl;
		cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> specialnist; fout << specialnist << endl;
		p[i].specialnist = (Specialnist)specialnist;
		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << "фізика : "; cin >> p[i].fizyka; fout << p[i].fizyka << endl;
			cout << "математика : "; cin >> p[i].matematika; fout << p[i].matematika << endl;
			cout << "програмування : "; cin >> p[i].programming; fout << p[i].programming << endl;
			break;
		case INFORMATYKA:
			cout << "фізика : "; cin >> p[i].fizyka; fout << p[i].fizyka << endl;
			cout << "математика : "; cin >> p[i].matematika; fout << p[i].matematika << endl;
			cout << "чисельні методи : "; cin >> p[i].chiselni_metody; fout << p[i].chiselni_metody << endl;
			break;
		case MATEMATYKA_TA_EKONOMIKA:
		case FIZYKA_TA_INFORMATYKA:
		case TRUDOVE_NAVCHANYA:
			cout << "фізика : "; cin >> p[i].fizyka; fout << p[i].fizyka << endl;
			cout << "математика : "; cin >> p[i].matematika; fout << p[i].matematika << endl;
			cout << "педагогіка : "; cin >> p[i].pedagogika; fout << p[i].pedagogika << endl;
			break;
		}
		cout << endl;
	}
}

void PrintBIN(Student* p, const int N, char* fname)
{
	ifstream fin(fname, ios::binary);		// відкрили файл для зчитування
	cout << "=================================================================================================================="
		<< endl;
	cout << "|  №  |   Прізвище   | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(12) << right << p[i].prizv << " "
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(13) << right << specialnistStr[p[i].specialnist];

		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			cout << " |" << setw(7) << right
				<< p[i].fizyka << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(13) << right
				<< p[i].programming << " |" << right << endl;
			break;
		case INFORMATYKA:
			cout << " |" << setw(7) << right
				<< p[i].fizyka << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(15) << right << "|" << setw(16) << right
				<< p[i].chiselni_metody << " |" << right << endl;
			break;
		case MATEMATYKA_TA_EKONOMIKA:
		case FIZYKA_TA_INFORMATYKA:
		case TRUDOVE_NAVCHANYA:
			cout << " |" << setw(7) << right
				<< p[i].fizyka << right;
			cout << " | " << setw(10) << right
				<< p[i].matematika << right;
			cout << " | " << setw(15) << right << "|" << setw(18) << right << "|" << setw(11) << right
				<< p[i].pedagogika << " |" << right << endl;
			break;
		}
	}
	cout << "=================================================================================================================="
		<< endl;
	cout << endl;
}

int OcinkaBIN(Student* p, const int N, char* fname)
{
	int count = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		switch (p[i].specialnist)
		{
		case KOMPUTERNI_NAUKY:
			n++;
			if (p[i].fizyka >= 8 && p[i].fizyka <= 10)
			{
				count++;
			}
			if (p[i].matematika >= 8 && p[i].matematika <= 10)
			{
				count++;
			}
			if (p[i].programming >= 8 && p[i].programming <= 10)
			{
				count++;
			}
			break;
		case INFORMATYKA:
			n++;
			if (p[i].fizyka >= 8 && p[i].fizyka <= 10)
			{
				count++;
			}
			if (p[i].matematika >= 8 && p[i].matematika <= 10)
			{
				count++;
			}
			if (p[i].chiselni_metody >= 8 && p[i].chiselni_metody <= 10)
			{
				count++;
			}
			break;
		case MATEMATYKA_TA_EKONOMIKA:
		case FIZYKA_TA_INFORMATYKA:
		case TRUDOVE_NAVCHANYA:
			n++;
			if (p[i].fizyka >= 8 && p[i].fizyka <= 10)
			{
				count++;
			}
			if (p[i].matematika >= 8 && p[i].matematika <= 10)
			{
				count++;
			}
			if (p[i].pedagogika >= 8 && p[i].pedagogika <= 10)
			{
				count++;
			}
			break;
		}
	}

	return count;
}