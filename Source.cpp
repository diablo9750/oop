#include "struct.h" 
#include <iostream>
#include <fstream>
using namespace std;
//--------------------------------------------------

//�������������� �������
int game::Vowel() {
	int count = 0;
	char mass[] = { "����������������ۨ" };
	for (int i = 0; i < strlen(name); i++)
	{
		for (int j = 0; j < strlen(mass); j++)
		{
			if (name[i] == mass[j])
			{
				count++;
			}
		}
	}
	return count;
}

int cartoon::Vowel() {
	int count = 0;
	char mass[] = { "����������������ۨ" };
	for (int i = 0; i < strlen(name); i++)
	{
		for (int j = 0; j < strlen(mass); j++)
		{
			if (name[i] == mass[j])
			{
				count++;
			}
		}
	}
	return count;
}

int doc::Vowel() {
	int count = 0;
	char mass[] = { "����������������ۨ" };
	for (int i = 0; i < strlen(name); i++)
	{
		for (int j = 0; j < strlen(mass); j++)
		{
			if (name[i] == mass[j])
			{
				count++;
			}
		}
	}
	return count;
}

// ����� ����������� ����������
void container::Vowel(ifstream& ifst, ofstream& ofst)
{
	ofst << "��������� �������� ���������� ��������� ������: " << count << endl;
	List* current = Top;
	Sort();
	film* fm;
	for (int j = 0; j < count; j++)
	{

		ofst << j + 1 << ": ";
		current->data->Out(ofst);
		ofst << "���������� ������� � ��������: " << current->data->Vowel() << endl;
		current = current->Next;
	}
}

//--------------------------------------------------

//���� ���������� �������� ������ �� �����
void game::InData(ifstream& ifst) {
	ifst >> country >> name >> director;
}

//����� ���������� �������� ������ � �����
void game::Out(ofstream& ofst) {
	ofst << "��� ������� �����. ������, ��� ��������� �����: " << country << ", �������� ������: " << name
		<< ", �������: " << director << endl;
}

//--------------------------------------------------

//���� ���������� ����������� �� ������
void cartoon::InData(ifstream& ifst) {
	ifst >> country >> name >> type;
}

//����� ���������� ����������� � �����
void cartoon::Out(ofstream& ofst) {
	ofst << "��� ���������. ������, ��� ��������� �����: " << country << ", �������� ������: " << name << ", ��� �����������: ";

	if (type == 1) {
		ofst << "����������" << endl;
	}
	if (type == 2) {
		ofst << "���������" << endl;
	}
}

//--------------------------------------------------

//���� ���������� ����������� �� ������
void doc::InData(ifstream& ifst) {
	ifst >> name >> date;
}

//����� ���������� ����������� � �����
void doc::Out(ofstream& ofst) {
	ofst << "��� ������������� �����: " << ", �������� ������: " << name << ", ��� �������: " << date << endl;
}
//--------------------------------------------------

//���� ���������� ����������� ������ �� �����
film* film::In(ifstream& ifst)
{
	film* fm;
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
	case 3:
	{
		fm = new doc;
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
int container::add(ifstream& ifst)
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
		List* current = Top;
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
void container::In(ifstream& ifst)
{
	while (!ifst.eof()) {
		if (add(ifst) != 0)
			count++;
	}
}

bool film::Compare(film& other) {
	return Vowel() > other.Vowel();
}

// ���������� ����������� ����������
void container::Sort()
{
	List* current = Top;
	for (int i = 0; i < count; i++)
	{
		if (current->data->Compare(*current->Next->data))
		{
			List p;
			p.data = current->data;
			current->data = current->Next->data;
			current->Next->data = p.data;
			i = 0;
			current = Top;
		}
		else
		{
			current = current->Next;
		}
	}
}

// ����� ����������� ���������� � ��������� �����
void container::Out(ofstream& ofst)
{
	List* current = Top;
	Sort();
	ofst << "��������� �������� ���������� ��������� ������: " << count << endl;
	for (int j = 0; j < count; j++)
	{
		ofst << j + 1 << ": ";
		current->data->Out(ofst);
		ofst << "���������� ������� � ��������: " << current->data->Vowel() << endl;
		current = current->Next;
	}
}
//----------------------------------------------------

//����� ������ �������
void film::OutGame(ofstream& ofst) {
}
void game::OutGame(ofstream& ofst) {
	Out(ofst);
}
void cartoon::OutGame(ofstream& ofst) {
}
void doc::OutGame(ofstream& ofst) {
}
void container::OutGame(ofstream& ofst) {
	List* current = Top;
	ofst << "������ ������� ������." << endl;
	for (int i = 0; i < count; i++) {

		current->data->OutGame(ofst);
		current = current->Next;
	}
}
//----------------------------------------------------
