#include "struct.h" 
#include <iostream>
#include <fstream>
using namespace std;

//--------------------------------------------------

//���� ���������� �������� ������ �� �����
void game::InData(ifstream &ifst) {
	ifst  >> name >> director;
}

//����� ���������� �������� ������ � �����
void game::Out(ofstream &ofst) {
	ofst << "��� ������� �����. " << " �������� ������: " << name
		<< ", �������: " << director << endl;
}

//--------------------------------------------------

//���� ���������� ����������� �� ������
void cartoon::InData(ifstream &ifst) {
	ifst >>  name >> type;
}

//����� ���������� ����������� � �����
void cartoon::Out(ofstream &ofst) {
	ofst << "��� ���������. " << " �������� ������: " << name << ", ��� �����������: ";

	if (type == 1) {
		ofst << "����������" << endl;
	}
	if (type == 2) {
		ofst << "���������" << endl;
	}
}


//--------------------------------------------------

//���� ���������� ����������� ������ �� �����
film* film::In(ifstream &ifst)
{
	film *fm;
	int key;
	ifst >> key;
	switch (key)
	{
	case 1:
	{
		fm = new game;
	}break;
	case 2:
	{
		fm = new cartoon;
	}break;
	default:
	{
		return 0;
	}break;
	}

	fm->InData(ifst);
	return fm;
}

//������������� ����������
container::container()
{

	Top = nullptr;
	count = 0;
}

//������������� ������ ������
container::List::List()
{
	this->Next = nullptr;
	this->Priv = nullptr;
	this->data = nullptr;
}

//--------------------------------------------------



//���������� ����
int container::add(ifstream &ifst)
{
	//���� ��������� ������
	if (count == 0)
	{
		Top = new List;
		if ((Top->data = film::In(ifst)) != 0)
			return 1;
		else
			return 0;
	}
	//���� ��������� �� ������
	else
	{
		List *current = Top;
		for (int j = 0; j < count - 1; j++)
		{
			current = current->Next;
		}
		current->Next = new List;
		if ((current->Next->data = film::In(ifst)) != 0)
		{
			Top->Priv = current->Next;
			current->Next->Priv = current;
			current->Next->Next = Top;
			return 1;
		}
		else
		{
			delete current->Next;
			return 0;
		}
	}
	return 0;
}

//�������� ���� �������
void container::List::Del()
{
	List* current = this;
	while (current->Next != nullptr)
	{
		current = current->Next;
		delete current->Priv;
	}
	delete current;
}

//�������� ����������
void container::Clear()
{
	List* current = Top;
	for (int i = 1; i < count; i++)
	{
		current = current->Next;
		delete current->Priv;
	}
	delete current;
	count = 0;
}

// ���� ����������� ���������� �� ���������� ������
void container::In(ifstream &ifst)
{
	while (!ifst.eof()) {
		if (add(ifst) != 0)
			count++;
	}
}

// ����� ����������� ���������� � ��������� �����
void container::Out(ofstream & ofst)
{
	List* current = Top;
	ofst << "��������� �������� ���������� ��������� ������: " << count << endl;
	for (int j = 0; j < count; j++)
	{
		ofst << j + 1 << ": ";
		current->data->Out(ofst);
		current = current->Next;
	}
}
