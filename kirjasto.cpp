#include "stdafx.h"
#include "kirjasto.h"


kirjasto::kirjasto()
{
	// Kirjasto luokan constructorissa käydään läpi kirjat.txt ja asiakkaat.txt,
	// ja lisätään näiden sisältö asiakkaat ja kirjat -vektoreihin.

	string puskuri = "";
	string elemetti = "";
	int NumeroTemp = 0;
	int SuurinKirjanSarjanumero = 10000;
	int SuurinHenkilonumero = 1000;
	size_t erotin_paikka;

	// Avataan kirjat.txt lukemista varten.
	fstream tiedosto;
	tiedosto.open("kirjat.txt");

	// Luetaan tiedostoa rivi kerraallaan kirjaolioon, ja lisätään luokat kirjatvektoriin;
	// Muuttujien erottimena tiedostossa käytetään ":" -merkkiä.
	while (getline(tiedosto, puskuri)) {
		kirja k;

		// Haetaan ensimmäisen erottimen paikka riviltä.
		erotin_paikka = puskuri.find(":");
		// Erotetaan elementti.
		elemetti = puskuri.substr(0, erotin_paikka);
		// Sijoitetaan elementti kirja luokkaan.
		k.KirjanNimi = elemetti;
		// Poistetaan elementti ja erotin puskurista.
		puskuri.erase(0, erotin_paikka + 1);

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		k.Tekija = elemetti;
		puskuri.erase(0, erotin_paikka + 1);

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		NumeroTemp = atoi(puskuri.c_str());	// atoi() -> string tyyppi integeriksi.
		k.udk = NumeroTemp;
		puskuri.erase(0, erotin_paikka + 1);

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		NumeroTemp = atoi(puskuri.c_str());
		k.sarjanumero = NumeroTemp;
		puskuri.erase(0, erotin_paikka + 1);

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		if (elemetti == "1"){ k.Lainassa = true; }
		if (elemetti == "0"){ k.Lainassa = false; }
		puskuri.erase(0, erotin_paikka + 1);

		k.LainaajaId = atoi(elemetti.c_str());

		// Kirjaolio vektoriin.
		this->kirjatVector.push_back(k);

		// Selvitetään suurin kirjan sarjanumero tiedostossa.
		if (k.sarjanumero > SuurinKirjanSarjanumero){ SuurinKirjanSarjanumero = k.sarjanumero; }

	}
	tiedosto.close();

	// Asetetaan sarjanumeron alkuarvo.
	kirja::HaeKirjanSarjanumero(SuurinKirjanSarjanumero - 10000);

	/////////////////////////////////////////////
	/////////////////////////////////////////////

	puskuri = "";
	elemetti = "";
	NumeroTemp = 0;

	// Avataan asiakkaat.txt lukemista varten.
	tiedosto.open("asiakkaat.txt");

	// Luetaan tiedostoa rivi kerraallaan asiakkaatolioon, ja lisätään luokat asiakkaatvektoriin;
	// Muuttujien erottimena tiedostossa käytetään ":" -merkkiä.
	while (getline(tiedosto, puskuri)) {
		asiakas a;

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		a.Nimi = elemetti;
		puskuri.erase(0, erotin_paikka + 1);

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		a.Osoite = elemetti;
		puskuri.erase(0, erotin_paikka + 1);

		erotin_paikka = puskuri.find(":");
		elemetti = puskuri.substr(0, erotin_paikka);
		a.Hetu = elemetti;
		puskuri.erase(0, erotin_paikka + 1);


		NumeroTemp = atoi(puskuri.c_str());
		a.Henkilonumero = NumeroTemp;

		this->asiakkaatVector.push_back(a);
		this->henkilostovector.push_back(a);

		if (SuurinHenkilonumero < a.Henkilonumero) { SuurinHenkilonumero = a.Henkilonumero; }

	}
	tiedosto.close();

	// Asetetaan henkilönumeron alkuarvo.
	Henkilo::HaeHenkilonumero(SuurinHenkilonumero - 1000);
}

void kirjasto::LisaaKirja()
{
	kirja Uusikirja;
	string syotto = " "; // Tähän syötetään tekstit
	int syottoint = 0; // lukujen syöttö

	// Kirjan nimen kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 kirja" << endl;
		cout << "Kirjan nimi: ";
		getline(cin, syotto);
		Uusikirja.KirjanNimi = syotto;
	} while (syotto == " " || syotto == "");

	syotto = ""; // Nollataan syöttö.

	// Tekijän kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 kirja" << endl;
		cout << "Kirjan nimi: " << Uusikirja.KirjanNimi << endl;
		cout << "Kirjan tekij\x84: ";
		getline(cin, syotto);
		Uusikirja.Tekija = syotto;
	} while (syotto == " " || syotto == "");

	syotto = ""; // Nollataan syöttö.

	// UDK kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 kirja" << endl;
		cout << "Kirjan nimi: " << Uusikirja.KirjanNimi << endl;
		cout << "Kirjan tekij\x84: " << Uusikirja.Tekija << endl;
		cout << "Kirjan UDK: ";
		cin >> syottoint;
		Uusikirja.udk = syottoint;
	} while (syottoint <= 0);

	syottoint = 0; // syötön nollaus

	Uusikirja.Lainassa = false;
	Uusikirja.sarjanumero = kirja::HaeKirjanSarjanumero(0);

	// Lisättävä kirjaolio kirjatvektoriin.
	this->kirjatVector.push_back(Uusikirja);
}

void kirjasto::LisaaAsiakas()
{
	string syotto = " "; // Tähän syötetään tekstit
	int syottoint = 0; // lukujen syöttö

	asiakas UusiAsiakas;

	// Asiakkaan nimen kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 asiakas" << endl;
		cout << "Asiakkaan nimi: ";
		getline(cin, syotto);
		UusiAsiakas.Nimi = syotto;
	} while (syotto == " " || syotto == "");


	syotto = ""; // Syötön nollaus.

	// Asiakkaan hetun kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 asiakas" << endl;
		cout << "Asiakkaan nimi: ";
		cout << UusiAsiakas.Nimi << endl;
		cout << "Hetu: ";
		getline(cin, syotto);
		UusiAsiakas.Hetu = syotto;
	} while (syotto == " " || syotto == "");

	syotto = ""; // Syötön nollaus.

	// Asiakkaan osoitteen kysely.
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 asiakas" << endl;
		cout << "Asiakkaan nimi: ";
		cout << UusiAsiakas.Nimi << endl;

		cout << "Hetu: ";
		cout << UusiAsiakas.Hetu << endl;

		cout << "Osoite: ";
		getline(cin, syotto);
		UusiAsiakas.Osoite = syotto;
	} while (syotto == " " || syotto == "");

	syotto = ""; // Syötön nollaus.

	UusiAsiakas.Henkilonumero = Henkilo::HaeHenkilonumero(0);

	this->asiakkaatVector.push_back(UusiAsiakas); //Uusi asiakas asiakasluetteloon.
	this->henkilostovector.push_back(UusiAsiakas);
	cout << "Asiakas lis\x84tty. Asiakasnumero: " << UusiAsiakas.Henkilonumero << endl;
	
	ofstream tiedosto_input;
	tiedosto_input.open("asiakkaat.txt", ios_base::app); // ios_base::app -> lisää tiedoston loppuun.
	string AsiakasTemp;

	AsiakasTemp = UusiAsiakas.Nimi + ":" + UusiAsiakas.Osoite + ":" + UusiAsiakas.Hetu + ":" + to_string(UusiAsiakas.Henkilonumero) + "\n";
	tiedosto_input << AsiakasTemp;
	tiedosto_input.close();
	
	
	getchar(); getchar();

}

void kirjasto::NaytaKirjat()
{
	system("CLS");
	cout << "Kirjaston kaikki kirjat: " << endl;
	cout << "\nNimi:\t\tTekij\x84:\t\tUDK:\tsarjanumero:" << endl;
	for each (kirja MyElement in this->kirjatVector)
	{
		//Tulostetaan kirjaston kaikkien kirjojen tiedot.
		cout << MyElement.KirjanNimi << ", \t";
		cout << MyElement.Tekija << ", \t" << MyElement.udk << ", \t" << MyElement.sarjanumero << ", \t";;
		if (MyElement.Lainassa == true)
		{
			cout << " LAINASSA!";
		}
		cout << endl;
	}
	getchar(); getchar();
}

void kirjasto::LainaaKirja()
{
	// tempit arvoja varten
	int temphenkilonumero = 0; 
	int tempsarjanumero = 0;
	int kirjatemp = 0;

	// asiakkaan ja kirjan tietojen kysely
	system("CLS");
	cout << "Kirjan lainaus" << endl;
	cout << "Anna asiakkaan asiakasnumero:";
	cin >> temphenkilonumero;
	cout << "Anna kirjan sarjanumero: ";
	cin >> tempsarjanumero; 

	// Käydään läpi kirjat ja asetetaan lainattava kirja lainatuksi.
	// Tallennetaan Lainaajan henkilönumero kirjan tietoihin.
	for (unsigned int i = 0; i < this->kirjatVector.size(); i++)
	{
		if (this->kirjatVector.at(i).sarjanumero == tempsarjanumero)
		{
			if (this->kirjatVector.at(i).Lainassa == true){
				cout << "Kirja on jo lainassa!" << endl;
				getchar();
				break;
			}
			else{
				this->kirjatVector.at(i).Lainassa = true;
				this->kirjatVector.at(i).LainaajaId = temphenkilonumero;
				cout << "Lainaus suoritettu onnistuneesti!" << endl;
				getchar();
				kirjatemp = i;
				break;
			}
		}
	}
}

void kirjasto::PalautaKirja()
{
	int tempasiakasnumero = 0;
	int tempkirjanro = 0;
	int tempasiakasiterator = 0;

	system("CLS");
	cout << "Palauta kirja" << endl;
	cout << "Anna asiakasnumero: ";
	cin >> tempasiakasnumero; // asiakasnumeron kysely

	// tulosta asiakkaan nimi ja muut oleelliset tiedot
	for (unsigned int i = 0; i < this->asiakkaatVector.size(); i++)
	{
		if (this->asiakkaatVector.at(i).Henkilonumero == tempasiakasnumero)
		{
			cout << "Asiakkaan nimi: " << this->asiakkaatVector.at(i).Nimi << "\n"<< endl;

			// Tulostetaan kirjat, jotka ovat asiakkaalla lainassa
			for (unsigned int j = 0; j < this->kirjatVector.size(); j++)
			{
				if (this->kirjatVector.at(j).LainaajaId == tempasiakasnumero){
					cout << this->kirjatVector.at(j).KirjanNimi + ", " + this->kirjatVector.at(j).Tekija + ", ";
					cout << this->kirjatVector.at(j).sarjanumero << endl;
					cout << "-----------------------" << endl;
				}
			}
		
			tempasiakasiterator = i; // tallennetaan asiakkaan paikka asiakkaatVectorissa
			break;
		}
	}

	cout << "Anna palautettavan kirjan sarjanumero: ";
	cin >> tempkirjanro; // kirjan sarjanumeron kysely

	// Käydään läpi kirjatVectoria ja asetetaan palautettu kirja palautetuksi
	// Asetetaan palautetun kirjan LainaajaId 0:ksi.
	for (unsigned int i = 0; i < this->kirjatVector.size(); i++)
	{
		if (this->kirjatVector.at(i).sarjanumero == tempkirjanro)
		{
			this->kirjatVector.at(i).Lainassa = false;
			this->kirjatVector.at(i).LainaajaId = 0;
			break;
		}
	}
	getchar();
}

void kirjasto::Poistakirja()
{
	int tempsarjanumero = 0;

	system("CLS");
	cout << "Poista kirja" << endl;
	cout << "Kirjan sarjanumero: ";
	cin >> tempsarjanumero;

	// Käydään läpi kirjatVectoria ja poistetaan sarjanumeron mukainen kirja
	for (unsigned int i = 0; i < this->kirjatVector.size(); i++)
	{
		if (this->kirjatVector.at(i).sarjanumero == tempsarjanumero)
		{
			this->kirjatVector.erase(this->kirjatVector.begin() + i);
			cout << "Kirja poistettu onnistuneesti!" << endl;
			getchar();
			break;
		}
	}

}

void kirjasto::NaytaTiettyKirja()
{
	int syotto = 0;
	string hakusana = "";

	system("CLS");
	cout << "Hae kirjoja:" << endl;
	cout << "Valitse haun tyyppi" << endl;
	cout << "(1) Kirjan nimi" << endl;
	cout << "(2) Kirjan tekij\x84" << endl;
	cin >> syotto;

	switch (syotto)
	{
	case 1:
		cout << "Anna hakusana:";
		cin.ignore();
		getline(cin, hakusana);

		for (unsigned int i = 0; i < this->kirjatVector.size(); i++){
			if (this->kirjatVector.at(i).KirjanNimi == hakusana){
				cout << this->kirjatVector.at(i).KirjanNimi << ", ";
				cout << this->kirjatVector.at(i).Tekija << ", ";
				cout << this->kirjatVector.at(i).sarjanumero << ", ";
				if (this->kirjatVector[i].Lainassa == true)
				{
					cout << "Kirja on LAINASSA." << endl;
				}
				else
				{
					cout << "Kirja on KIRJASTOSSA." << endl;
				}
				cout << endl;
			}
		}
		break;
	case 2:
		cout << "Anna hakusana:";
		cin.ignore();
		getline(cin, hakusana);

		for (unsigned int i = 0; i < this->kirjatVector.size(); i++){
			if (this->kirjatVector.at(i).Tekija == hakusana){
				cout << this->kirjatVector.at(i).KirjanNimi << ", ";
				cout << this->kirjatVector.at(i).Tekija << ", ";
				cout << this->kirjatVector.at(i).sarjanumero << ", ";
				if (this->kirjatVector[i].Lainassa == true)
				{
					cout << "Kirja on LAINASSA." << endl;
				}
				else
				{
					cout << "Kirja on KIRJASTOSSA." << endl;
				}
				cout << endl;
			}
		}
		break;
	default:
		break;
	}
	cout << "Paina enter jatkaaksesi!" << endl;
	getchar();
}

void kirjasto::LisaaTyontekija()
{
	string syotto = " "; // Tähän syötetään tekstit
	int syottoint = 0; // lukujen syöttö

	Tyontekija UusiTyontekija;

	// Asiakkaan nimen kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 ty\x94ntekij\x84" << endl;
		cout << "Nimi: ";
		getline(cin, syotto);
		UusiTyontekija.Nimi = syotto;
	} while (syotto == " " || syotto == "");


	syotto = ""; // Syötön nollaus.

	// Asiakkaan hetun kysely
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 ty\x94ntekij\x84" << endl;
		cout << "Nimi: ";
		cout << UusiTyontekija.Nimi << endl;
		cout << "Hetu: ";
		getline(cin, syotto);
		UusiTyontekija.Hetu = syotto;
	} while (syotto == " " || syotto == "");

	syotto = ""; // Syötön nollaus.

	// Asiakkaan osoitteen kysely.
	do
	{
		system("CLS");
		cout << "Lis\x84\x84 ty\x94ntekij\x84" << endl;
		cout << "Nimi: ";
		cout << UusiTyontekija.Nimi << endl;

		cout << "Hetu: ";
		cout << UusiTyontekija.Hetu << endl;

		cout << "Osoite: ";
		getline(cin, syotto);
		UusiTyontekija.Osoite = syotto;
	} while (syotto == " " || syotto == "");

	syotto = ""; // Syötön nollaus.

	UusiTyontekija.Henkilonumero = Henkilo::HaeHenkilonumero(0);

	this->tyontekijatvector.push_back(UusiTyontekija); //Uusi työntekijä työntekijäluetteloon.
	this->henkilostovector.push_back(UusiTyontekija);
	cout << "Ty\x94ntekij\x84 lis\x84tty. Numero: " << UusiTyontekija.Henkilonumero << endl;
	getchar(); getchar();

}

void kirjasto::NaytaHenkilosto()
{
	system("CLS");
	cout << "Koko henkil\x94st\x94: " << endl;

	for (unsigned int i = 0; i < this->henkilostovector.size(); i++)
	{
		
			cout << this->henkilostovector.at(i).Nimi << ", ";
			cout << this->henkilostovector.at(i).Hetu << ", ";
			cout << this->henkilostovector.at(i).Osoite << ", ";
			cout << this->henkilostovector.at(i).Henkilonumero << ", ";
			if (this->henkilostovector[i].OnkoTyontekija == true)
			{
				cout << "Ty\x94ntekij\x84" << endl;
				cout << "----------------" << endl;
			}
			else
			{
				cout << "Asiakas" << endl;
				cout << "----------------" << endl;
			}
			cout << endl;
		}
	getchar(); getchar();
}

void kirjasto::PaivitaKirjatTiedosto(){
	// Päivittää kirjaVektorin sisällön kirjat.txt tiedostoon.

	// Ylikirjoitetaan tiedosto.
	ofstream tiedosto_input;
	tiedosto_input.open("kirjat.txt", ofstream::out | ofstream::trunc);
	
	string KirjaTemp = "";
	string Lainassa = "";

	// Lisätään kirjatvektorin kirjaoliot tiedostoon jokainen omalle rivilleen.
	// Muuttujien erottimena ":" -merkki.
	for each (kirja MyElement in this->kirjatVector){
		if (MyElement.Lainassa == true){ Lainassa = "1"; }
		if (MyElement.Lainassa == false){ Lainassa = "0"; }

		KirjaTemp = MyElement.KirjanNimi + ":" + MyElement.Tekija + ":" + to_string(MyElement.udk) + ":" + to_string(MyElement.sarjanumero) + ":" + Lainassa + ":" + to_string(MyElement.LainaajaId) + "\n";

		tiedosto_input << KirjaTemp;

	}
	tiedosto_input.close();

}

void kirjasto::PaivitaAsiakkaatTiedosto(){
	// Päivittää asiakkaatVektorin sisällön asiakkaat.txt tiedostoon.

	//  Ylikirjoitetaan tiedosto.
	ofstream tiedosto_input;
	tiedosto_input.open("asiakkaat.txt", ofstream::out | ofstream::trunc);
	
	string AsiakasTemp;
	
	// Lisätään asiakkaatvektorin asiakasoliot tiedostoon jokainen omalle rivilleen.
	// Muuttujien erottimena ":" -merkki.
	for each (asiakas MyElement in this->asiakkaatVector){

		AsiakasTemp = MyElement.Nimi + ":" + MyElement.Osoite + ":" + MyElement.Hetu + ":" + to_string(MyElement.Henkilonumero) + "\n";

		tiedosto_input << AsiakasTemp;

	}

	tiedosto_input.close();

}

kirjasto::~kirjasto()
{
}
