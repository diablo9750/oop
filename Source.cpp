#include "struct.h" 
#include <iostream>
#include <fstream>
using namespace std;
//--------------------------------------------------

//Дополнительные функции
int game::Vowel() {
	int count = 0;
	char mass[] = { "аеоуияэыёАЁОУИЯЭЫЁ" };
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
	char mass[] = { "аеоуияэыёАЁОУИЯЭЫЁ" };
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
	char mass[] = { "аеоуияэыёАЁОУИЯЭЫЁ" };
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

// Вывод содержимого контейнера
void container::Vowel(ifstream& ifst, ofstream& ofst)
{
	ofst << "Контейнер содержит количество элементов равное: " << count << endl;
	List* current = Top;
	Sort();
	film* fm;
	for (int j = 0; j < count; j++)
	{

		ofst << j + 1 << ": ";
		current->data->Out(ofst);
		ofst << "Количество гласных в названии: " << current->data->Vowel() << endl;
		current = current->Next;
	}
}

//--------------------------------------------------

//Ввод параметров игрового фильма из файла
void game::InData(ifstream& ifst) {
	ifst >> country >> name >> director;
}

//Вывод параметров игрового фильма в поток
void game::Out(ofstream& ofst) {
	ofst << "Это игровой фильм. Страна, где произведён фильм: " << country << ", Название фильма: " << name
		<< ", Режиссёр: " << director << endl;
}

//--------------------------------------------------

//Ввод параметров мультфильма из потока
void cartoon::InData(ifstream& ifst) {
	ifst >> country >> name >> type;
}

//Вывод параметров мультфильма в поток
void cartoon::Out(ofstream& ofst) {
	ofst << "Это мультильм. Страна, где произведён фильм: " << country << ", Название фильма: " << name << ", вид мультфильма: ";

	if (type == 1) {
		ofst << "рисованный" << endl;
	}
	if (type == 2) {
		ofst << "кукольный" << endl;
	}
}

//--------------------------------------------------

//Ввод параметров мультфильма из потока
void doc::InData(ifstream& ifst) {
	ifst >> name >> date;
}

//Вывод параметров мультфильма в поток
void doc::Out(ofstream& ofst) {
	ofst << "Это доументальный фильм: " << ", Название фильма: " << name << ", Год выпуска: " << date << endl;
}
//--------------------------------------------------

//Ввод параметров обобщенного фильма из файла
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

//Инициализация контейнера
container::container()
{
	Top = nullptr;
	count = 0;
}

//Инициализация нового списка
container::List::List()
{
	this->Next = nullptr;
	this->Priv = nullptr;
	this->data = nullptr;
}

//--------------------------------------------------

//Добавление узла
int container::add(ifstream& ifst)
{
	//Если контейнер пустой
	if (count == 0)
	{
		Top = new List;
		if ((Top->data = film::In(ifst)) != 0)
			return 1;
		else
			return 0;
	}
	//Если контейнер не пустой
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

//Удаление всех списков
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

//Отчистка контейнера
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

// Ввод содержимого контейнера из указанного потока
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

// Сортировка содержимого контейнера
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

// Вывод содержимого контейнера в указанный поток
void container::Out(ofstream& ofst)
{
	List* current = Top;
	Sort();
	ofst << "Контейнер содержит количество элементов равное: " << count << endl;
	for (int j = 0; j < count; j++)
	{
		ofst << j + 1 << ": ";
		current->data->Out(ofst);
		ofst << "Количество гласных в названии: " << current->data->Vowel() << endl;
		current = current->Next;
	}
}
//----------------------------------------------------

//Вывод только игровых
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
	ofst << "Только игровые фильмы." << endl;
	for (int i = 0; i < count; i++) {

		current->data->OutGame(ofst);
		current = current->Next;
	}
}
//----------------------------------------------------
