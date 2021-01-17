#pragma once
#define CRT_SECURE_NO_WARNIGS
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<sstream>
using namespace std;

class VerificareDate {

	vector<string>tipuriDate;
	vector<string> date;
	set<vector<string>> tabel;

public:

	VerificareDate()
	{
		for (std::vector<string>::iterator it = this->date.begin(); it != this->date.end(); ++it)
		{
			*it = " ";
		}

		for (std::vector<string>::iterator it = this->tipuriDate.begin(); it != this->tipuriDate.end(); ++it)
		{
			*it = " ";
		}

		for (std::set<vector<string>>::iterator it = this->tabel.begin(); it != this->tabel.end(); ++it)
		{
			vector<string> aux = *it;
			for (std::vector<string>::iterator jt = aux.begin(); jt != aux.end(); ++jt)
			{
				*jt = " ";
			}

			this->tabel.insert(aux);
		}
	}

	VerificareDate(vector<string> tipuri, vector<string> date, set<vector<string>> tabel)
	{
		this->tipuriDate = tipuri;
		this->date = date;
		this->tabel = tabel;
	}

	void setDate(vector<string> date)
	{
		if (date.size() > 0)
		{
			this->date = date;
		}
	}

	void setTipuri(vector<string> tipuri)
	{
		if (tipuri.size() > 0)
		{
			this->tipuriDate = tipuri;
		}
	}

	set<vector<string>> verificare()
	{
		if (date.size() == tipuriDate.size())
		{
			int index = 0;
			while (index < date.size())
			{
				if (tipuriDate[index] == "integer")
				{
					if (!(isInteger(date[index])))
					{
						break;
					}
				}
				else
				{
					if (tipuriDate[index] == "float")
					{
						if (!(isFloat(date[index])))
						{
							break;
						}
					}
					else
					{
						if (tipuriDate[index] == "text")
						{
							if (isInteger(date[index]) || isFloat(date[index]))
							{
								break;
							}
						}
					}
				}
				++index;
			}
			if (index < date.size())
			{
				cout << "Nu se respecta structura tabelului" << endl;
				cout << date[index] << " nu este de tip " << tipuriDate[index] << endl;
			}
			else
			{
				this->tabel.insert(date);
			}
		}
		else
		{
			cout << "Valorile nu respecta structura!" << endl;
		}

		return tabel;
	}

	inline bool isInteger(const std::string& s)
	{
		if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

		char* p;
		strtol(s.c_str(), &p, 10);

		return (*p == 0);
	}

	bool isFloat(string myString) {
		std::istringstream iss(myString);
		float f;
		iss >> noskipws >> f;
		return iss.eof() && !iss.fail();
	}

	bool verificareLaCreare()
	{
		if (date.size() == tipuriDate.size())
		{
			int index = 0;
			while (index < date.size())
			{
				if (tipuriDate[index] == "integer")
				{
					if (!(isInteger(date[index])))
					{
						break;
					}
				}
				else
				{
					if (tipuriDate[index] == "float")
					{
						if (!(isFloat(date[index])))
						{
							break;
						}
					}
					else
					{
						if (tipuriDate[index] == "text")
						{
							if (isInteger(date[index]) || isFloat(date[index]))
							{
								break;
							}
						}
					}
				}
				++index;
			}
			if (index < date.size())
			{
				cout << "Nu se respecta structura tabelului" << endl;
				cout << date[index] << " nu este de tip " << tipuriDate[index] << endl;
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			cout << "Valorile nu respecta structura!" << endl;
			return 0;
		}
	}
};