#pragma once
class Henkilo
{
public:
	string Nimi;
	string Osoite;
	string Hetu;
	int Henkilonumero;

	//vector<kirja>Lainaukset;


	bool OnkoTyontekija;

	static int Henkilo::HaeHenkilonumero(int SuurinHenkilonumero) {
		static int Henkilonumero_alku = 1000;
		Henkilonumero_alku = Henkilonumero_alku + SuurinHenkilonumero;
		return Henkilonumero_alku++;
	}

	Henkilo();
	~Henkilo();
};

