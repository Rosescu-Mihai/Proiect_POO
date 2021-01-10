#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<set>
#include "BazaDeDate.h"
#include <fstream>
using namespace std;

class PreluaredateTXT
{

	string numeFisier;
public:

	PreluaredateTXT()
	{
		numeFisier = " ";
	}

	void setNumeFisier(string nf)
	{
		if (nf.length() > 0 && (nf == "CREATE" || nf == "INSERT"))
		{
			this->numeFisier = nf;
		}
	}

	string getNumeFisier()
	{
		return this->numeFisier;
	}
};