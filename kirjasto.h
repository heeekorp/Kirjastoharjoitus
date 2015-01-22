#pragma once
class kirjasto
{
public:
	vector<kirja>kirjatVector;
	vector<asiakas>asiakkaatVector;
	vector<Tyontekija>tyontekijatvector;
	vector<Henkilo>henkilostovector;

	void LisaaKirja();
	void Poistakirja();
	void LainaaKirja();
	void PalautaKirja();
	void LisaaAsiakas();
	void NaytaKirjat();
	void NaytaTiettyKirja();
	void LisaaTyontekija();

	void PaivitaKirjatTiedosto();
	void PaivitaAsiakkaatTiedosto();

	void NaytaHenkilosto();
	  
	kirjasto();
	~kirjasto();
};

