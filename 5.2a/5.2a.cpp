
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <Windows.h> 

using namespace std;

enum Specialty { KN, INF, ME, PI, TD };

string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Матема. та екн.", " Фізика та інфорю", "Трудове навчання" };

struct Student {
	char prizv[64];
	unsigned cours;
	Specialty spec;
	unsigned physic, math, informatic;
};

void Create(const char* fName);
void Print(const char* fName);
double Excellent(const char* fName);
void Count(const char* fName);


int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fname[100];
	cout << "Введіть назву файлу: ";
	cin >> fname;

	int menuItem;

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - Обчислити процент студентів,  " << endl;
		cout << " у яких середній бал більший за 4,5" << endl;
		cout << " [4] - Вивести прізвища студентів, які вчаться на “відмінно”" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;


		switch (menuItem)
		{
		case 1:
			Create(fname);
			break;
		case 2:
			Print(fname);
			break;
		case 3:
			cout << "Процент студентів що має середній бал >4.5 ="
				<< Excellent(fname) << " % " << endl;
			break;
		case 4:
			Count(fname);
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

void Create(const char* fName)
{
	ofstream f(fName, ios::binary);
	Student s;
	char ch;
	int spec;
	int i = 0;
	do {
		cin.get(); 
		cin.sync(); 

		cout << " Прізвище: "; cin >> s.prizv;
		cout << " Курс: "; cin >> s.cours;

		cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та екноміка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> spec;
		s.spec = (Specialty)spec;
		cout << " Оцінка з фізики: "; cin >> s.physic;
		cout << " Оцінка з математики: "; cin >> s.math;
		cout << " Оцінка з інформатики: "; cin >> s.informatic;
		cout << endl;
		if (!f.write((char*)&s, sizeof(Student))) {
			cerr << "Error writing file." << endl;
		}
		cout << "Continue?(Y/N)"; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}
void Print(const char* fName)
{
	ifstream f(fName, ios::binary);
	Student s;
	int i = 0;

	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика | "
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	while (f.read((char*)&s, sizeof(Student))) 
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s.prizv
			<< "| " << setw(4) << right << s.cours << " "
			<< "| " << setw(11) << left << specialtyStr[s.spec] << " "
			<< "| " << setw(6) << right << s.physic << " "
			<< "| " << setw(6) << left << s.math << " "
			<< "| " << setw(7) << right << s.informatic << endl;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}

double Excellent(const char* fName)
{
	ifstream f(fName, ios::binary);
	Student s;
	int count = 0;
	int all = 0;
	while (f.read((char*)&s, sizeof(Student))) 
	{
		if (((double)(s.informatic + s.math + s.physic) / 3) >= (double)4.5)
			count++;
		all++;
	}
	if (count != (int)0)
		return (double)(all * count) / 100;
	else
		return 0;
}

void Count(const char* fName)
{
	ifstream f(fName, ios::binary);
	Student s;
	while (f.read((char*)&s, sizeof(Student))) 
	{
		if ((s.informatic == 5) && (s.math == 5) && (s.physic == 5))
		{
			cout << "# " << s.prizv << endl;
		}
	}
}