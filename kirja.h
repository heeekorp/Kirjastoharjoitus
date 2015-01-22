#pragma once
class kirja
{
public:
	string KirjanNimi; // Teoksen nimi
	string Tekija; // Kirjailija
	int udk; // UDK
	int LainaajaId;
	bool Lainassa; // Lainassa jees / nou
	static int Sarjanumero_alku;
	int sarjanumero;
	
	kirja();
	~kirja();
	
	static int kirja::HaeKirjanSarjanumero(int SuurinSarjanumero) {
		static int Sarjanumero_alku = 10000;
		Sarjanumero_alku = Sarjanumero_alku + SuurinSarjanumero;

		return Sarjanumero_alku++;
	}

private:
	
	//int kirjanyksilonro; // Kirjan yksilöivä sarjanumero
};

