#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<set>
#include "CREATEandINSERT.h"
#include <fstream>
#include <sstream>
#include "VerificareDate.h"
#include "ScriereBinara.h"
using namespace std;
class BazaDeDate
{
	string nume_tabel;
	string comanda;
	vector<string> coloane_tabel;
	vector<string> valori_coloane;
	set<vector<string>> linii_tabel;
	map<string, set<vector<string>>> Tabele;
	PreluaredateTXT n;
	int nrFisiserAfisare = 1;
	int nrFisierSelect = 1;
	VerificareDate vfCreare;

public:

	BazaDeDate()
	{
		comanda = " ";
	}

	BazaDeDate(string comanda)
	{
		this->comanda = comanda;
	}

	void setComanda(string linie)
	{
		if (linie.length() > 0)
		{
			comanda = linie;
		}
	}
	void CreareTabel()
	{
		string verif1 = comanda.substr(0, 12);
		if (verif1 == "CREATE TABLE")
		{
			int poz1 = 13;
			int poz2 = 0;
			poz2 = comanda.find('(', sizeof('('));

			string nume_tabel = comanda.substr(poz1, poz2 - poz1);
			int ok = 1;

			for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
			{
				if (nume_tabel == it->first)
					ok = 0;
			}
			if (ok == 1)
			{
				int inceput_coloana = poz2 + 1;
				int final_coloana = 0;

				while (inceput_coloana < comanda.size() - 2)
				{
					for (std::string::size_type index = inceput_coloana; index < comanda.size(); ++index)
					{
						if (comanda[index] == ')')
						{
							final_coloana = index;
							break;
						}
					}
					string coloana = comanda.substr(inceput_coloana + 1, final_coloana - 1 - inceput_coloana);
					int nr = 0;
					for (std::string::size_type i = coloana.size(); i >= 1; --i)
					{
						if (coloana[i] == ',')
						{
							nr++;
						}
					}
					if (nr != 3)
					{
						cout << "Coloana nu respecta nr de atribute" << endl;
						break;
					}
					else
					{
						int pozitie_valoare_implicita = 0;
						for (std::string::size_type i = coloana.size(); i >= 1; --i)
						{
							if (coloana[i] == ' ')
							{
								pozitie_valoare_implicita = i;
								break;
							}
						}

						if (coloana[pozitie_valoare_implicita - 1] != ',')
						{
							cout << "Coloana nu respecta structura!" << endl;
							break;
						}
						else
						{
							coloane_tabel.push_back(coloana);
							inceput_coloana = final_coloana + 3;
						}
					}
				}

				if (inceput_coloana < comanda.size() - 2)
				{
					cout << "Coloana incorect initializata" << endl;
				}
				else
				{
					vector<string> tipuri;
					vector<string> valori_implicite;
					for (std::vector<string>::iterator x = coloane_tabel.begin(); x != coloane_tabel.end(); ++x)
					{
						int pozTip1 = x->find(',', 0);
						int pozTip2 = x->find(',', pozTip1 + 1);
						string tipdata = x->substr(pozTip1 + 2, pozTip2 - pozTip1 - 2);
						if (tipdata == "integer" || tipdata == "float" || tipdata == "text")
						{
							tipuri.push_back(tipdata);
						}
						else
						{
							cout << "Tipurile de coloana sunt stabilite corect!" << endl;
							break;
						}

						string valoare = *x;
						int pozitie_valoare_implicita = 0;
						for (std::string::size_type i = valoare.size(); i >= 1; --i)
						{
							if (valoare[i] == ',')
							{
								pozitie_valoare_implicita = i;
								break;
							}
						}
						string valoare_implicita = x->substr(pozitie_valoare_implicita + 2, x->size());
						valori_implicite.push_back(valoare_implicita);


					}
					vfCreare.setTipuri(tipuri);
					vfCreare.setDate(valori_implicite);
					if (vfCreare.verificareLaCreare())
					{
						linii_tabel.insert(coloane_tabel);
						coloane_tabel.clear();
						Tabele.insert(std::pair< string, set<vector<string>>>(nume_tabel, linii_tabel));
						valori_coloane.clear();
						linii_tabel.clear();
						cout << "Creare cu succes a tabelului!" << endl;
					}
					else
					{
						coloane_tabel.clear();
						linii_tabel.clear();
						valori_coloane.clear();
						cout << "Tabelul nu a putut fi creat!" << endl;
					}
				}

			}
			else
			{
				cout << "Exista deja un tabel cu acest nume!" << endl;
			}
		}
		else
		{
			cout << "Comanda incorecta!!" << endl;
		}
	}
	void InserareTabel()
	{
		string verificare = comanda.substr(0, 11);
		if (verificare == "INSERT INTO")
		{
			int poz1 = 12;
			int poz2 = 0;

			poz2 = comanda.find(' ', 12);

			string nume_tabel = comanda.substr(poz1, poz2 - poz1);
			int ok = 0;
			set<vector<string>> comp1;
			for (map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
			{
				if (it->first == nume_tabel)
				{
					comp1 = it->second;
					ok = 1;
				}
			}
			if (ok == 1)
			{
				string verificare2 = comanda.substr(poz2 + 1, 6);
				if (verificare2 == "VALUES")
				{
					int inceput_valoare_coloana = poz2 + 7;
					int final_valoare_coloana = 0;

					while (inceput_valoare_coloana < comanda.size() - 2)
					{
						for (std::string::size_type index = inceput_valoare_coloana; index < comanda.size(); ++index)
						{
							if (comanda[index] == ',' || comanda[index] == ')')
							{
								final_valoare_coloana = index;
								break;
							}
						}

						string valoare_coloana = comanda.substr(inceput_valoare_coloana + 1, final_valoare_coloana - 1 - inceput_valoare_coloana);
						valori_coloane.push_back(valoare_coloana);

						inceput_valoare_coloana = final_valoare_coloana + 1;
					}


					set<vector<string>> comp2;
					for (map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
					{
						if (it->first == nume_tabel)
						{
							vector<string>inf_coloane = *it->second.rbegin();
							vector<string> tipuri;
							for (std::vector<string>::iterator xt = inf_coloane.begin(); xt != inf_coloane.end(); ++xt)
							{
								int pozTip1 = xt->find(',', 0);
								int pozTip2 = xt->find(',', pozTip1 + 1);
								string tipdata = xt->substr(pozTip1 + 2, pozTip2 - pozTip1 - 2);
								tipuri.push_back(tipdata);
							}
							VerificareDate vf1(tipuri, valori_coloane, it->second);
							it->second = vf1.verificare();
							comp2 = it->second;
							valori_coloane.clear();
							ScriereFisier scb(it->second, it->first);
							scb.serializare();
							break;
						}
					}
					if (comp1 == comp2)
					{
						cout << "valorile nu au fost inserate!" << endl;
					}
					else
					{
						cout << "Valori inserate cu succes!" << endl;
					}

				}
				else
				{
					cout << "Comanda incorecta!!" << endl;
				}
			}
			else
			{
				cout << "Tabelul nu exista!" << endl;
			}

		}
		else
		{
			cout << "Comanda incorecta!!" << endl;
		}
	}

	void AfisareTabel(set<vector<string>> sv)
	{
		vector<string> v = *sv.rbegin();
		string linie_nume_coloana;
		string linie_val_imp;

		ofstream file_Afisare;
		file_Afisare.open("DISPLAY_TABLE_" + std::to_string(nrFisiserAfisare) + ".txt");
		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it)
		{
			int pozitie_nume_coloana = it->find(',', 0);
			string nume_coloana = it->substr(0, pozitie_nume_coloana);
			cout << nume_coloana << " || ";
			linie_nume_coloana.append(nume_coloana + " || ");
		}
		file_Afisare << linie_nume_coloana << endl;
		cout << endl;

		for (std::vector<string>::iterator it = v.begin(); it != v.end(); ++it)
		{
			string valoare = *it;
			int pozitie_valoare_implicita = 0;
			for (std::string::size_type i = valoare.size(); i >= 1; --i)
			{
				if (valoare[i] == ',')
				{
					pozitie_valoare_implicita = i;
					break;
				}
			}

			string valoare_implicita = it->substr(pozitie_valoare_implicita + 1, it->size());
			cout << valoare_implicita << " || ";
			linie_val_imp.append(valoare_implicita + " || ");
		}
		file_Afisare << linie_val_imp << endl;
		cout << endl;

		for (std::set<vector<string>>::iterator it = sv.begin(); it != std::prev(sv.end()); ++it)
		{
			string linie_valoare = " ";
			vector<string> aux = *it;
			for (std::vector<string>::iterator jt = aux.begin(); jt != aux.end(); ++jt)
			{
				cout << *jt << " || ";
				linie_valoare.append(*jt + " || ");
			}
			file_Afisare << linie_valoare << endl;
			cout << endl;
		}
		file_Afisare.close();
		nrFisiserAfisare++;
	}

	void AfisareTabelV2()
	{
		string verificare = comanda.substr(0, 13);
		if (verificare == "DISPLAY TABLE")
		{
			int poz_nume_tabel = 14;

			string nume_T = comanda.substr(poz_nume_tabel, comanda.size() - poz_nume_tabel);
			int ok = 0;

			for (map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
			{
				if (it->first == nume_T)
				{
					cout << "Nume Tabel: " << it->first << endl;
					AfisareTabel(it->second);
					ok = 1;
					break;
				}
			}

			if (ok == 0)
			{
				cout << "Tabelul nu exista!" << endl;
			}

		}
		else
		{
			cout << "Comanda incorecta!!" << endl;
		}
	}

	void StergereTabel()
	{
		string verificare = comanda.substr(0, 10);
		if (verificare == "DROP TABLE")
		{
			string nume_tabel = comanda.substr(11, comanda.size() - 11);
			int ok = 1;
			for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
			{
				if (nume_tabel == it->first)
				{
					Tabele.erase(it);
					cout << "Tabelul a fost eliminat!" << endl;
					ok = 0;
					break;
				}
			}

			if (ok == 1)
			{
				cout << "Tabelul nu exista!" << endl;
			}
		}
		else
		{
			cout << "Comanda incorecta!!" << endl;
		}
	}

	void Selectare()
	{
		string verificare = comanda.substr(0, 6);
		if (verificare == "SELECT")
		{
			int poz1 = 7;
			int poz2 = comanda.find('F', poz1);

			string cerere = comanda.substr(poz1, poz2 - poz1 - 1);

			poz1 = poz2;

			poz2 = comanda.find(' ', poz1 + 1);
			string verficare2 = comanda.substr(poz1, poz2 - poz1);

			if (verficare2 == "FROM")
			{
				if (cerere == "ALL")
				{
					string nume_tabel = comanda.substr(poz2 + 1, comanda.size() - poz2 - 1);
					int ok = 1;
					for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
					{
						if (nume_tabel == it->first)
						{
							cout << "Nume Tabel: " << it->first << endl;
							AfisareTabel(it->second);
							ok = 0;
							break;
						}
					}

					if (ok == 1)
					{
						cout << "Tabelul nu exista!" << endl;
					}

				}
				else
				{
					vector<string> coloane_selectate;
					int inceput_denumire_coloana = 0;
					int final_denumire_coloana = 0;
					string linie_nume_coloana;
					string linie_val_imp;

					ofstream file_SELECT;
					file_SELECT.open("SELECT_" + std::to_string(nrFisierSelect) + ".txt");

					while (inceput_denumire_coloana < cerere.size() - 1)
					{
						for (std::string::size_type index = inceput_denumire_coloana; index < cerere.size(); ++index)
						{
							if (cerere[index] == ',' || index == cerere.size() - 1)
							{
								final_denumire_coloana = index;
								break;
							}
						}

						string denumire_coloana = cerere.substr(inceput_denumire_coloana, final_denumire_coloana - inceput_denumire_coloana + 1);
						coloane_selectate.push_back(denumire_coloana);
						inceput_denumire_coloana = final_denumire_coloana + 2;
					}

					string nume_tabel = comanda.substr(poz2 + 1, comanda.size() - poz2 - 1);

					for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
					{
						if (nume_tabel == it->first)
						{
							linii_tabel = it->second;
							coloane_tabel = *linii_tabel.rbegin();
							vector <int> poziti_coloane_selectate;
							for (std::vector<string>::iterator xt = coloane_selectate.begin(); xt != coloane_selectate.end(); ++xt)
							{
								string aux = *xt;
								for (std::vector<string>::iterator jt = coloane_tabel.begin(); jt != coloane_tabel.end(); ++jt)
								{
									string nume_coloana;
									int pozitie_nume_coloana = jt->find(',', 0);
									if (aux[aux.size() - 1] == ',')
									{
										nume_coloana = jt->substr(0, pozitie_nume_coloana + 1);
									}
									else
									{
										nume_coloana = jt->substr(0, pozitie_nume_coloana);
									}
									if (nume_coloana == aux)
									{
										cout << nume_coloana << "||";
										int index1 = jt - coloane_tabel.begin();
										poziti_coloane_selectate.push_back(index1);
										linie_nume_coloana.append(nume_coloana + " || ");
									}
								}
							}
							file_SELECT << linie_nume_coloana << endl;
							cout << endl;
							for (std::vector<string>::iterator yt = coloane_selectate.begin(); yt != coloane_selectate.end(); ++yt)
							{
								string aux = *yt;
								for (std::vector<string>::iterator jt = coloane_tabel.begin(); jt != coloane_tabel.end(); ++jt)
								{
									string nume_coloana;
									int pozitie_nume_coloana = jt->find(',', 0);
									if (aux[aux.size() - 1] == ',')
									{
										nume_coloana = jt->substr(0, pozitie_nume_coloana + 1);
									}
									else
									{
										nume_coloana = jt->substr(0, pozitie_nume_coloana);
									}
									if (nume_coloana == aux)
									{
										string valoare = *jt;
										int pozitie_valoare_implicita = 0;
										for (std::string::size_type i = valoare.size(); i >= 1; --i)
										{
											if (valoare[i] == ',')
											{
												pozitie_valoare_implicita = i;
												break;
											}
										}

										string valoare_implicita = jt->substr(pozitie_valoare_implicita + 1, jt->size());
										cout << valoare_implicita << " || ";
										linie_val_imp.append(valoare_implicita + " || ");

									}
								}
							}
							file_SELECT << linie_val_imp << endl;
							cout << endl;

							for (std::set<vector<string>>::reverse_iterator kt = std::next(it->second.rbegin(), 1); kt != it->second.rend(); ++kt)
							{
								vector<string> aux_valori = *kt;
								string linie_valoare = " ";
								for (int i = 0; i < poziti_coloane_selectate.size(); ++i)
								{
									for (std::vector<string>::iterator mt = aux_valori.begin(); mt != aux_valori.end(); ++mt)
									{
										int compara = mt - aux_valori.begin();
										if (poziti_coloane_selectate[i] == compara)
										{
											cout << *mt << " || ";
											linie_valoare.append(*mt + " || ");
										}

									}
								}
								file_SELECT << linie_valoare << endl;
								cout << endl;
								
							}
							break;
						}
						else
						{
							cout << "Tabelul nu exista!" << endl;
						}
					}

					file_SELECT.close();
					nrFisierSelect++;
				}
			}
			else
			{
				cout << "Comanda incorecta!!" << endl;
			}

		}
		else
		{
			cout << "Comanda incorecta!!" << endl;
		}
	}
	string removeWord(string str, string word)
	{
		if (str.find(word) != string::npos)
		{
			size_t p = -1;

			string tempWord = word + " ";
			while ((p = str.find(word)) != string::npos)
			{
				str.replace(p, tempWord.length(), "");
			}

			tempWord = " " + word;
			while ((p = str.find(word)) != string::npos)
			{
				str.replace(p, tempWord.length(), "");
			}

		}

		return str;
	}

	void StergereDinTabel()
	{
		string verificare = comanda.substr(0, 11);
		if (verificare == "DELETE FROM")
		{
			int poz1 = 12;
			int poz2 = comanda.find('W', poz1);

			string numeT = comanda.substr(poz1, poz2 - poz1 - 1);
			int ok = 0;

			poz1 = poz2;
			string verificare2 = comanda.substr(poz1, 5);
			if (verificare2 == "WHERE")
			{
				for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
				{
					if (numeT == it->first)
					{
						ok = 1;
						poz1 = poz1 + 5;
						poz2 = comanda.find('=', poz1);
						string numeC = comanda.substr(poz1 + 1, poz2 - poz1 - 1);
						string valoareC = comanda.substr(poz2 + 1, comanda.size() - poz2);
						vector<string> coloane_tabel = *it->second.rbegin();
						int ok2 = 0;
						int ok3 = 0;
						for (std::vector<string>::iterator j = coloane_tabel.begin(); j != coloane_tabel.end(); ++j)
						{
							int pozitie_nume_coloana = j->find(',', 0);
							string nume_coloana = j->substr(0, pozitie_nume_coloana);

							string valoare = *j;
							int pozitie_valoare_implicita = 0;
							for (std::string::size_type i = valoare.size(); i >= 1; --i)
							{
								if (valoare[i] == ',')
								{
									pozitie_valoare_implicita = i;
									break;
								}
							}


							string valoare_implicita = j->substr(pozitie_valoare_implicita + 2, j->size());

							if (numeC == nume_coloana && valoare_implicita == valoareC)
							{
								ok2 = 1;
							}
							if (numeC == nume_coloana)
							{
								ok3 = 1;
							}

						}
						if (ok2 == 1)
						{
							vector<string> coloane_noi;
							for (std::vector<string>::iterator it = coloane_tabel.begin(); it != coloane_tabel.end(); ++it)
							{
								string valoare = *it;
								int pozitie_valoare_implicita = 0;
								for (std::string::size_type i = valoare.size(); i >= 1; --i)
								{
									if (valoare[i] == ',')
									{
										pozitie_valoare_implicita = i;
										break;
									}
								}

								BazaDeDate bd;
								string valoare_implicita = it->substr(pozitie_valoare_implicita + 1, it->size());
								valoare = bd.removeWord(valoare, valoare_implicita);
								coloane_noi.push_back(valoare);
							}

							set<vector<string>> set_aux = it->second;
							set_aux.erase(*set_aux.rbegin());
							set_aux.insert(coloane_noi);
							it->second = set_aux;
							cout << "OK" << endl;
						}

						if (ok3 == 1)
						{
							set<vector<string>> set_aux = it->second;
							for (std::set<vector<string>>::reverse_iterator xt = std::next(it->second.rbegin(), 1); xt != it->second.rend(); ++xt)
							{
								int contine = 0;
								vector<string> aux = *xt;
								for (std::vector<string>::iterator jt = aux.begin(); jt != aux.end(); ++jt)
								{
									string aux_val = *jt;
									if (aux_val[aux_val.size() - 1] == ',')
									{
										string valoareC_aux = valoareC + ",";

										if (valoareC_aux == aux_val)
										{
											contine = 1;
											break;
										}
									}
									else
									{
										if (valoareC == aux_val)
										{
											contine = 1;
											break;
										}
									}

								}
								if (contine == 1)
								{
									set_aux.erase(aux);
								}
							}
							it->second = set_aux;
						}
						if (ok3 == 0)
						{
							cout << "Coloana nu exista!" << endl;
						}
					}
				}
				if (ok == 0)
				{
					cout << "Tabelul nu exista!" << endl;
				}

			}
			else
			{
				cout << "Comanda incorecta!!" << endl;
			}

		}
		else
		{
			cout << "Comanda incorecta!!" << endl;
		}
	}

	void UpdateTable()
	{
		string verificare = comanda.substr(0, 6);
		if (verificare == "UPDATE")
		{
			int poz1 = 7;
			int poz2 = comanda.find(' ', poz1 + 1);

			string nume_Tabel = comanda.substr(poz1, poz2 - poz1);

			poz1 = poz2 + 1;
			poz2 = comanda.find(' ', poz1);
			string verificare2 = comanda.substr(poz1, poz2 - poz1);
			if (verificare2 == "SET")
			{
				poz1 = poz2 + 1;
				poz2 = comanda.find('=', poz1);
				string nume_set = comanda.substr(poz1, poz2 - poz1);
				poz1 = poz2 + 1;
				poz2 = comanda.find(' ', poz1);
				string valoare_set = comanda.substr(poz1, poz2 - poz1);

				poz1 = poz2 + 1;
				poz2 = comanda.find(' ', poz1);
				string verificare3 = comanda.substr(poz1, poz2 - poz1);
				if (verificare3 == "WHERE")
				{
					poz1 = poz2 + 1;
					poz2 = comanda.find('=', poz1);
					string nume_where = comanda.substr(poz1, poz2 - poz1);
					poz1 = poz2 + 1;
					poz2 = comanda.find(' ', poz1);
					string valoare_where = comanda.substr(poz1, poz2 - poz1);
					int ok = 0;
					for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
					{
						if (nume_Tabel == it->first)
						{
							vector<string> coloane_tabel = *it->second.rbegin();
							int ok2 = 0;
							int ok3 = 0;
							int index_set = 0;
							int index_where = 0;
							for (std::vector<string>::iterator j = coloane_tabel.begin(); j != coloane_tabel.end(); ++j)
							{
								int pozitie_nume_coloana = j->find(',', 0);
								string nume_coloana = j->substr(0, pozitie_nume_coloana);

								string valoare = *j;
								int pozitie_valoare_implicita = 0;
								for (std::string::size_type i = valoare.size(); i >= 1; --i)
								{
									if (valoare[i] == ',')
									{
										pozitie_valoare_implicita = i;
										break;
									}
								}


								string valoare_implicita = j->substr(pozitie_valoare_implicita + 2, j->size());

								if (nume_where == nume_coloana && valoare_implicita == valoare_where)
								{
									ok2 = 1;
								}
								if (nume_where == nume_coloana)
								{
									index_where = j - coloane_tabel.begin();
									ok3 = 1;
								}
								if (nume_coloana == nume_set)
								{
									index_set = j - coloane_tabel.begin();
								}

							}

							if (ok2 == 1)
							{
								for (std::vector<string>::iterator j = coloane_tabel.begin(); j != coloane_tabel.end(); ++j)
								{
									int pozitie_nume_coloana = j->find(',', 0);
									string nume_coloana = j->substr(0, pozitie_nume_coloana);

									if (nume_set == nume_coloana)
									{
										string valoare = *j;
										int pozitie_valoare_implicita = 0;
										for (std::string::size_type i = valoare.size(); i >= 1; --i)
										{
											if (valoare[i] == ',')
											{
												pozitie_valoare_implicita = i;
												break;
											}
										}

										j->replace(pozitie_valoare_implicita + 2, j->size() - pozitie_valoare_implicita, valoare_set);
									}

								}
								set<vector<string>> set_aux = it->second;
								set_aux.erase(*set_aux.rbegin());
								set_aux.insert(coloane_tabel);
								it->second = set_aux;
								cout << "OK2" << endl;
							}
							if (ok3 == 1)
							{
								vector<int> index_vector;
								for (std::set<vector<string>>::reverse_iterator x = std::next(it->second.rbegin(), 1); x != it->second.rend(); ++x)
								{
									vector<string> date = *x;
									for (std::vector<string>::iterator vt = date.begin(); vt != date.end(); ++vt)
									{
										string data = *vt;
										if (data[data.size() - 1] == ',')
										{
											string valoareC_aux = valoare_where + ",";

											if (valoareC_aux == data)
											{
												int index = std::distance(std::next(it->second.rbegin(), 1), x);
												index_vector.push_back(index);
											}
										}
										else
										{
											if (valoare_where == data)
											{
												int index = std::distance(std::next(it->second.rbegin(), 1), x);
												index_vector.push_back(index);
											}
										}
									}
								}

								set<vector<string>> set_aux = it->second;
								for (std::vector<int>::iterator nt = index_vector.begin(); nt != index_vector.end(); ++nt)
								{
									int index = *nt;
									for (std::set<vector<string>>::reverse_iterator x = std::next(it->second.rbegin(), 1); x != it->second.rend(); ++x)
									{
										if (index == std::distance(std::next(it->second.rbegin(), 1), x))
										{
											vector<string> date = *x;
											set_aux.erase(date);
											for (std::vector<string>::iterator it = date.begin(); it != date.end(); ++it)
											{
												if (index_set == it - date.begin())
												{
													it->replace(0, it->size(), valoare_set);
												}
											}
											set_aux.insert(date);
										}

									}
								}
								it->second = set_aux;
							}
						}
					}
				}
			}
		}
	}

	void preluare()
	{
		n.setNumeFisier("CREATE");
		ifstream file_CREATE(n.getNumeFisier() + ".txt");
		if (file_CREATE.is_open())
		{
			while (getline(file_CREATE, comanda))
			{
				CreareTabel();
			}
			file_CREATE.close();
		}
		else
		{
			cout << "Fisierul nu exista!" << endl;
		}

		n.setNumeFisier("INSERT");
		ifstream file_INSERT(n.getNumeFisier() + ".txt");
		if (file_INSERT.is_open())
		{
			while (getline(file_INSERT, comanda))
			{
				InserareTabel();
			}
			file_INSERT.close();
		}
		else
		{
			cout << "Fisierul nu exista!" << endl;
		}
	}

	void exportTabelCSV()
	{
		string verificare = comanda.substr(0, 6);
		if (verificare == "EXPORT")
		{
			int poz1 = comanda.find(' ', 0);
			int poz2 = comanda.find(' ', poz1 + 1);

			string nume_tabel = comanda.substr(poz1 + 1, poz2 - poz1 - 1);
			int ok = 0;
			for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
			{
				if (nume_tabel == it->first)
				{
					ok = 1;
					poz1 = poz2;
					poz2 = comanda.length();
					string nume_fisier = comanda.substr(poz1 + 1, poz2 - poz1);
					if (nume_fisier.length() > 0)
					{
						ofstream file_CSV;
						file_CSV.open(nume_fisier);
						for (std::set<vector<string>>::reverse_iterator r_it = std::next(it->second.rbegin()); r_it != it->second.rend(); ++r_it)
						{
							vector<string> aux = *r_it;
							for (std::vector<string>::iterator vt = aux.begin(); vt != aux.end(); ++vt)
							{
								file_CSV << *vt << ",";
							}
							file_CSV << endl;
						}
						file_CSV.close();
						cout << "Fiser creat cu succes!" << endl;
					}
					else
					{
						cout << "Fisierul nu este specificat!" << endl;
					}
					break;
				}
			}
			if (ok == 0)
			{
				cout << "Tabelul nu exista" << endl;
			}
		}
		else
		{
			cout << "Comanda este incorecta!" << endl;
		}
	}


	void importTabel()
	{
		string verificare = comanda.substr(0, 6);
		if (verificare == "IMPORT")
		{
			int poz1 = comanda.find(' ', 0);
			int poz2 = comanda.find(' ', poz1 + 1);

			string nume_tabel = comanda.substr(poz1 + 1, poz2 - poz1 - 1);
			int ok = 0;
			for (std::map<string, set<vector<string>>>::iterator it = Tabele.begin(); it != Tabele.end(); ++it)
			{
				if (nume_tabel == it->first)
				{
					ok = 1;
					poz1 = poz2;
					poz2 = comanda.length();
					string nume_fisier = comanda.substr(poz1 + 1, poz2 - poz1);
					if (nume_fisier.length() > 0)
					{
						if (nume_fisier == nume_tabel + ".bin")
						{
							set<vector<string>> set_aux;
							ScriereFisier scfb(it->second, it->first);
							set_aux = scfb.deserializare();
							for (std::set<vector<string>>::const_iterator xit = set_aux.begin(); xit != set_aux.end(); ++xit)
							{
								vector<string> vec_aux = *xit;
								it->second.insert(vec_aux);
							}
						}
						else
						{
							ifstream file_CSV;
							file_CSV.open(nume_fisier);
							if (file_CSV.is_open())
							{
								vector<string>inf_coloane = *it->second.rbegin();
								vector<string> tipuri;
								for (std::vector<string>::iterator xt = inf_coloane.begin(); xt != inf_coloane.end(); ++xt)
								{
									int pozTip1 = xt->find(',', 0);
									int pozTip2 = xt->find(',', pozTip1 + 1);
									string tipdata = xt->substr(pozTip1 + 2, pozTip2 - pozTip1 - 2);
									tipuri.push_back(tipdata);
								}

								vector<string> date;
								while (file_CSV.good())
								{
									string element;
									getline(file_CSV, element, '\n');

									if (element.size() > 0)
									{
										int inceput_valoare_coloana = 0;
										int final_valoare_coloana = 0;

										while (inceput_valoare_coloana < element.size() - 2)
										{
											int pozindex = 0;
											for (std::string::size_type index = inceput_valoare_coloana; index < element.size(); ++index)
											{
												pozindex = index;
												if (element[index] == ',')
												{
													final_valoare_coloana = index;
													break;
												}
											}

											if (pozindex == element.size() - 1)
											{
												string valoare_coloana = element.substr(inceput_valoare_coloana, final_valoare_coloana - inceput_valoare_coloana);
												date.push_back(valoare_coloana);
												break;
											}
											else
											{
												string valoare_coloana = element.substr(inceput_valoare_coloana, final_valoare_coloana - inceput_valoare_coloana);
												date.push_back(valoare_coloana);

												inceput_valoare_coloana = final_valoare_coloana + 1;
											}
										}

										VerificareDate vf(tipuri, date, it->second);
										it->second = vf.verificare();
										date.clear();
									}

								}
								file_CSV.close();
							}
							else
							{
								cout << "Fisierul nu exista!" << endl;
							}
						}

					}
					else
					{
						cout << "Fisierul nu este specificat!" << endl;
					}
					break;
				}
			}
			if (ok == 0)
			{
				cout << "Tabelul nu exista" << endl;
			}
		}
		else
		{
			cout << "Comanda este incorecta!" << endl;
		}
	}
};