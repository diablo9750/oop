#ifndef _struct
#define _struct
#include <fstream>
using namespace std;

//���������� �����
class film {
public:
	static film* In(ifstream &ifst);
	virtual void InData(ifstream &ifst) = 0;//���� ������ � ������
	virtual void Out(ofstream &ofst) = 0;//����� ������ � ������
};
//���������
class container
{
private:
	class List {
	public:
		List();//������������� ������
		void Del();//������� �������� ������ �� ������
		List* Next;//��������� �� ��������� ������
		List* Priv;//��������� �� ���������� ������
		film* data;//��������� �� ������ � ������
	};
public:
	int add(ifstream &ifst);//������� ���������� ������ ������ � ���������
	void In(ifstream &ifst);//���� ������ � ���������
	void Out(ofstream &ofst);//����� ������ �� ����������
	void Clear();//�������� ������ �� ���������
	container();//������������� ����������
				//~container() { Clear(); } // ���������� ����������-�������� ������
	List* Top;//��������� �� ��������� ������ � ����������
	int count;//����� ������� � ����������
};

//������� �����
class game : public film {
	char country[100];//������
	char name[100];//�������� ������
	char director[100];//��� ��������
public:
	void InData(ifstream &ifst);//���� ������ � ������
	void Out(ofstream &ofst);//����� ������ � ������
	game() {}//�������� ��� �������������.
};
//����������
class cartoon : public film {
	char country[100];//������
	char name[100];//�������� ������
	int type;//��� �����������
public:
	void InData(ifstream &ifst);//���� ������ � ������
	void Out(ofstream &ofst);//����� ������ � ������
	cartoon() {}//�������� ��� �������������.
};
#endif 