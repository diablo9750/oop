// ConsoleApplication1.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include <clocale>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "struct.h"
#include "Source.cpp"

using namespace std;
void main(int argc, char* argv[])
{
	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������ 
	setlocale(LC_ALL, "Russian"); // ����� ������� ��������� ������

	ifstream ifst("in.txt");
	ofstream ofst("out.txt", ios::trunc);
	/*if (argc != 3) {
		cout << "incorrect command line! "
			"Waited: command in_file out_file"
			<< endl;
		system("pause");
		exit(1);
	}
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);*/
	cout << "�����!" << endl;
	container c;
	c.In(ifst);
	ofst << "��������� �����." << endl;
	c.Out(ofst);
	c.Clear();
	ofst << "��������� ����." << endl;
	c.Out(ofst);
	cout << "����!" << endl;
	system("pause");
}

