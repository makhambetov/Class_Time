#include <iostream>
using namespace std;

/*�������� ����� �����, � ������� ����������� �����-
��� ��������, ���������, ���������, ����� � �����
�� �����. ����������� ����������� ������� �� ���-
���������� ������� am (pm): 10:00 pm = 22:00, 12:00
pm =00:00*/

class CTime
{
	int m_nHour;	//����
	int m_nMinute;	//������
public:
	//�����������, ������ �� ��������� ����� ����
	CTime(int h = 0, int m = 0)
	{
		SetTime(h, m);
	}
	
	//Set ����� ����� �������
	void SetTime(int h, int m)
	{
		if(h >= 0 && h <= 23) m_nHour = h;
		else m_nHour = 0;
		if(m >= 0 && m <= 59) m_nMinute = m;
		else m_nMinute = 0;
	}

	//����� ������ �� �����
	void Display(){
		cout << endl << m_nHour << ":" << m_nMinute << endl;
	}

	//���������� ��������� ������������
	CTime & operator=(const CTime & t){
		this->m_nHour = t.m_nHour;
		this->m_nMinute = t.m_nMinute;
		return *this;
	}

	/*���������� ��������� ��������
	  ��� �������� ���������� ����� �����, ����.:
	  10:55 + 00:10 = 11:05, �.�.,
	  10 ����� 55 ����� -> ����� 10 ����� ����� -> 11 ����� 05 �����*/
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

	//���������� ��������� ���������
	//����������, ��� �� ���������
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


	/*���������� ��������� ��������*/

	//���������� ��������� ==
	bool operator == (CTime & t){
		return (this->m_nHour == t.m_nHour && this->m_nMinute == t.m_nMinute);
	}

	//���������� ��������� <
	bool operator < (CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute < t.m_nMinute);
		else return (this->m_nHour < t.m_nHour);
	}

	//���������� ��������� >
	bool operator > (CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute > t.m_nMinute);
		else return (this->m_nHour > t.m_nHour);
	}

	//���������� ��������� <=
	bool operator <=(CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute <= t.m_nMinute);
		else return (this->m_nHour < t.m_nHour);
	}

	//���������� ��������� >=
	bool operator >=(CTime & t){
		if(this->m_nHour == t.m_nHour) 
			return (this->m_nMinute >= t.m_nMinute);
		else return (this->m_nHour > t.m_nHour);
	}

	//����� ��� ����������� �� ������������� ������� (�������� � �������� ����������)
	// 10:45 pm -> time.Convert(10, 45, "pm"); -> 22:45
	void Convert(int h, int m, char * t = "am"){

		if(m >= 0 && m <= 59) m_nMinute = m;		//�������� ������������ ����� �����
		else m_nMinute = 0;

		if (t == "am" || t == "a"){					//�������� ������������ ����� am
			if (h >= 0 && h <= 12) m_nHour = h;		//�������� ������������ ����� �����
			else m_nHour = 0;
		}
		else if(t == "pm" || t == "p"){				//�������� ������������ ����� pm
			if (h >= 0 && h <= 24) m_nHour = h + 12;//�������� ������������ ����� �����
			else m_nHour = 0;
		}
		else {
			m_nHour   = 0;							//�������� � ������ ������������� �����
			m_nMinute = 0;
			cout << "Error! Enter correct format.\n";
		}
	}

	//��������� ������������� ������� �����-������
	friend ostream & operator<<(ostream & os, const CTime & t);
	friend istream & operator>>(istream & is, CTime & t);
};

//���������� ��������� ������ <<
//��������� ���� ����� �������������� �������, ����., 15:5 -> 15:05
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
//���������� ��������� �����
istream & operator>>(istream & is, CTime & t)
{
	int h, m;
	cout << "������� ����� (���� [������] ������):\n";
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