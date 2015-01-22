// kirjastoharjoitus.cpp : Defines the entry point for the console application.
//

/* Ääkköset:
	\x86 = å
	\x84 = ä
	\x94 = ö
*/

#include "stdafx.h"

using namespace std;

void paivita_kirjat_tiedosto(kirjasto*);

int _tmain(int argc, _TCHAR* argv[])
{
	bool KirjastoAuki = true;
	int menusyotto = -1;

	kirjasto *Mykirjasto = new kirjasto; // Luodaan kirjasto

	// Tulosta ohjelman päävalikko
	do
	{
		system("CLS");
		cout << "Kirjasto" << endl;
		cout << endl;
		cout << "1 - Lis\x84\x84 kirja" << endl;
		cout << "2 - Poista kirja" << endl;
		cout << "3 - Lainaa kirja" << endl;
		cout << "4 - Palauta kirja" << endl;
		cout << "5 - N\x84yt\x84 kaikki kirjat" << endl;
		cout << "6 - N\x84yt\x84 tietty kirja" << endl;
		cout << "7 - Lis\x84\x84 asiakas" << endl;
		cout << "8 - Lis\x84\x84 ty\x94ntekij\x84" << endl;
		cout << "9 - N\x84yt\x84 henkil\x94st\x94" << endl;
		cout << "0 - Sulje kirjasto" << endl;

		cin >> menusyotto;

		// Päävalikon valinnat
		
		switch (menusyotto)
		{
		case 1:{
			Mykirjasto->LisaaKirja();
			thread myThread(&kirjasto::PaivitaKirjatTiedosto, Mykirjasto);
			cout << myThread.get_id();
			getchar(); getchar();
			myThread.join();
			break;
		}
		case 2:{
			Mykirjasto->Poistakirja();
			thread myThread(&kirjasto::PaivitaKirjatTiedosto, Mykirjasto);
			cout << myThread.get_id();
			getchar(); getchar();
			myThread.join();
			break;
		}
		case 3:{
			Mykirjasto->LainaaKirja();
			thread myThread(&kirjasto::PaivitaKirjatTiedosto, Mykirjasto);
			cout << myThread.get_id();
			getchar(); getchar();
			myThread.join();
			break;
		}
		case 4:{
	 		Mykirjasto->PalautaKirja();
			thread myThread(&kirjasto::PaivitaKirjatTiedosto, Mykirjasto);
			cout << myThread.get_id();
			getchar(); getchar();
			myThread.join();
			break;
		}
		case 5:
			Mykirjasto->NaytaKirjat();
			break;
		case 6:
			Mykirjasto->NaytaTiettyKirja();
			break;
		case 7:{
			Mykirjasto->LisaaAsiakas();
			thread myThread(&kirjasto::PaivitaAsiakkaatTiedosto, Mykirjasto);
			cout << myThread.get_id();
			getchar(); getchar();
			myThread.join();
			break;
		}
		case 8:
			Mykirjasto->LisaaTyontekija();
			break;
		case 9:
			Mykirjasto->NaytaHenkilosto();
			break;
		case 0:
			system("CLS");
			cout << "Kirjasto suljetaan. Paina Enter." << endl;
			KirjastoAuki = false;
			break;
		default:
			break;
		}

	} while (KirjastoAuki);

	delete Mykirjasto; // Tuhotaan kirjasto
	Mykirjasto = nullptr;

	system("PAUSE");

	return 0;
}

