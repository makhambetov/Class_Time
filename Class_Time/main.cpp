#include <iostream>
using namespace std;

/*Создайте класс Время, в котором реализованы опера-
ции сложения, вычитания, сравнения, ввода и вывод
на экран. Возможность конвертации времени из аме-
риканского формата am (pm): 10:00 pm = 22:00, 12:00
pm =00:00*/

class CTime
{
	int m_nHour;	//часы
	int m_nMinute;	//минуты
public:
	//конструктор, данные по умолчанию равны нулю
	CTime(int h = 0, int m = 0)
	{
		SetTime(h, m);
	}
	
	//Set метод ввода времени
	void SetTime(int h, int m)
	{
		if(h >= 0 && h <= 23) m_nHour = h;
		else m_nHour = 0;
		if(m >= 0 && m <= 59) m_nMinute = m;
		else m_nMinute = 0;
	}

	//метод вывода на экран
	void Display(){
		cout << endl << m_nHour << ":" << m_nMinute << endl;
	}

	//перегрузка оператора присваивания
	CTime & operator=(const CTime & t){
		this->m_nHour = t.m_nHour;
		this->m_nMinute = t.m_nMinute;
		return *this;
	}

	/*перегрузка оператора сложения
	  при сложении показывает новое время, напр.:
	  10:55 + 00:10 = 11:05, т.е.,
	  10 часов 55 минут -> через 10 минут будет -> 11 часов 05 минут*/
	CTime operator+(CTime & t){
		CTime temp = *this;
		temp.m_nHour   += t.m_nHour;
		temp.m_nMinute += t.m_nMinute;
		if (temp.m_nHour > 23) temp.m_nHour -= 24;
		if (temp.m_nMinute > 59){
			temp.m_nHour++;
			temp.m_nMinute -= 60;
		}
		return temp;
	}

	//перегрузка оператора вычитания
	//аналогично, как со сложением
	CTime operator-(CTime & t){
		CTime temp = *this;
		temp.m_nHour   -= t.m_nHour;
		temp.m_nMinute -= t.m_nMinute;
		if (temp.m_nMinute < 0){
			temp.m_nHour--;
			temp.m_nMinute += 60;
		}
		if (temp.m_nHour < 0) temp.m_nHour += 24;
		return temp;
	}


	/*Логические операторы равнения*/

	//перегрузка оператора ==
	bool operator == (CTime & t){
		return (this->m_nHour == t.m_nHour && this->m_nMinute == t.m_nMinute);
	}

	//перегрузка оператора <
	bool operator < (CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute < t.m_nMinute);
		else return (this->m_nHour < t.m_nHour);
	}

	//перегрузка оператора >
	bool operator > (CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute > t.m_nMinute);
		else return (this->m_nHour > t.m_nHour);
	}

	//перегрузка оператора <=
	bool operator <=(CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute <= t.m_nMinute);
		else return (this->m_nHour < t.m_nHour);
	}

	//перегрузка оператора >=
	bool operator >=(CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute >= t.m_nMinute);
		else return (this->m_nHour > t.m_nHour);
	}

	//метод для конвертации из американского формата (передаем в качестве аргументов)
	// 10:45 pm -> time.Convert(10, 45, "pm"); -> 22:45
	void Convert(int h, int m, char * t = "am"){

		if(m >= 0 && m <= 59) m_nMinute = m;		//проверка корректности ввода минут
		else m_nMinute = 0;

		if (t == "am" || t == "a"){					//проверка корректности ввода am
			if (h >= 0 && h <= 12) m_nHour = h;		//проверка корректности ввода часов
			else m_nHour = 0;
		}
		else if(t == "pm" || t == "p"){				//проверка корректности ввода pm
			if (h >= 0 && h <= 24) m_nHour = h + 12;//проверка корректности ввода часов
			else m_nHour = 0;
		}
		else {
			m_nHour   = 0;							//обнуляем в случае некорректного ввода
			m_nMinute = 0;
			cout << "Error! Enter correct format.\n";
		}
	}

	//объявляем дружественные функции ввода-вывода
	friend ostream & operator<<(ostream & os, const CTime & t);
	friend istream & operator>>(istream & is, CTime & t);
};

//перегрузка оператора вывода <<
//добавляем ноль перед одноразрядными числами, напр., 15:5 -> 15:05
ostream & operator<<(ostream & os, const CTime & t){
	char h,m;
	if(t.m_nHour < 10 && t.m_nMinute < 10)
		os << "0" << t.m_nHour << ":" << "0" << t.m_nMinute << endl;
	else if(t.m_nHour < 10)
		os << "0" << t.m_nHour << ":" << t.m_nMinute << endl;
	else if(t.m_nMinute < 10)
		os << t.m_nHour << ":" << "0" << t.m_nMinute << endl;
	else
		os << t.m_nHour << ":" << t.m_nMinute << endl;
	return os;
}
//перегрузка оператора ввода
istream & operator>>(istream & is, CTime & t)
{
	int h, m;
	cout << "Введите время (часы [пробел] минуты):\n";
	is >> h >> m;
	t.SetTime(h, m);
	return is;
}


void main()
{
	setlocale(LC_ALL, "RUSSIAN");

	CTime t1;
	cout << "t1 = " << t1;
	CTime t2(14, 4);
	cout << "t2 = " << t2;
	cin >> t2;
	cout << "t2 = " << t2;

	CTime t3 = t2;
	cout << "t3 = " << t3;
	CTime t4(23, 55);
	CTime t5(13, 20);
	CTime t6;
	cout << "t4 = " << t4;
	cout << "t5 = " << t5;
	cout << "t6 = t4+t5 = " << t4+t5;


	cout << "-------------" <<endl;
{
	CTime t1(14, 50);
	CTime t2(14, 50);
	CTime t3(14, 55);
	cout << "t1 = "<< t1;
	cout << "t2 = "<< t2;
	cout << "t3 = "<< t3;
	if (t1 >= t3) cout << "true\n";
	else cout << "false\n";
	
	CTime t4;
	t4.Convert(9, 8, "p");
	cout << t4;
}

	cin.get();
	cin.get();
}