#pragma once
#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<fstream>
#include "VerificareDate.h"
using namespace std;

class ScriereFisier {

	set<vector<string>> continut_tabel;
	string nume_tabel;

public:

	ScriereFisier()
	{

	}

	ScriereFisier(set<vector<string>> tabel, string nume)
	{
		this->continut_tabel = tabel;
		nume_tabel = nume;
	}

	void serializare()
	{
		ofstream g(nume_tabel + ".bin", ios::binary);
		for (std::set<vector<string>>::const_reverse_iterator crit = std::next(continut_tabel.rbegin()); crit != continut_tabel.rend(); ++crit)
		{
			vector<string> aux = *crit;
			for (std::vector<string>::iterator it = aux.begin(); it != aux.end(); ++it)
			{
				int dimensiune = it->length();
				g.write((char*)&dimensiune, sizeof(dimensiune));
				g.write(it->c_str(), dimensiune + 1);
			}
		}
		g.close();
	}

	set<vector<string>> deserializare()
	{
		ifstream f(nume_tabel + ".bin", ios::binary);
		int lenght = 0;
		set<vector<string>> continut_nou;
		vector<string> vector_nou;
		vector<string>inf_coloane = *continut_tabel.rbegin();
		vector<string> tipuri;
		for (std::vector<string>::iterator xt = inf_coloane.begin(); xt != inf_coloane.end(); ++xt)
		{
			int pozTip1 = xt->find(',', 0);
			int pozTip2 = xt->find(',', pozTip1 + 1);
			string tipdata = xt->substr(pozTip1 + 2, pozTip2 - pozTip1 - 2);
			tipuri.push_back(tipdata);
		}

		VerificareDate vf;
		vf.setTipuri(tipuri);
		int nr = 0;
		if (f.is_open())
		{
			while (f.good())
			{
				f.read((char*)&lenght, sizeof(lenght));
				char* buffer = new char[lenght + 1];
				f.read(buffer, lenght + 1);
				vector_nou.push_back(buffer);
				nr++;
				if (nr == 3)
				{
					nr = 0;
					vf.setDate(vector_nou);
					if (vf.verificareLaCreare())
					{
						continut_nou.insert(vector_nou);
					}
					vector_nou.clear();
				}
			}
		}

		f.close();

		return continut_nou;

	}
};