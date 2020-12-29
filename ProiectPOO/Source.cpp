#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<set>
#include "BazaDeDate.h"
using namespace std;


int menu();

int main()
{
	BazaDeDate bd;
	int op = 0;
	while (op != 8)
	{
		op = menu();
		switch (op)
		{
		case 1:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de creare: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.CreareTabel();
			break;
		}
		case 2:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de inserare: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.InserareTabel();
			break;
		}
		case 3:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de afisare: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.AfisareTabelV2();
			break;
		}

		case 4:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de stergere a tabelului: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.StergereTabel();
			break;
		}
		case 5:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de selectare: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.Selectare();
			break;
		}
		case 6:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de stergere linie: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.StergereDinTabel();
			break;
		}
		case 7:
		{
			system("cls");
			string comanda;
			cout << "Introduceti comanda de update: ";
			if (cin.peek() == '\n')
			{
				cin.ignore();
			}
			getline(cin, comanda);
			bd.setComanda(comanda);
			bd.UpdateTable();
			break;
		}
		case 8:
		{
			break;
		}
		default:
		{
			system("cls");
			cout << "Nr. invalid!" << endl;
			break;
		}
		}
	}
	
	
}

int menu()
{
	int optiune;
	cout << "Menu" << endl;
	cout << "1.Creare Tabel" << endl;
	cout << "2.Inserare in Tabel" << endl;
	cout << "3.Afisare Tabel" << endl;
	cout << "4.Stergere Tabel" << endl;
	cout << "5.Selectare in Tabel" << endl;
	cout << "6.Stergere linie din Tabela" << endl;
	cout << "7.Update valoare Tabel" << endl;
	cout << "8.Quit" << endl;
	cin >> optiune;
	return optiune;
}