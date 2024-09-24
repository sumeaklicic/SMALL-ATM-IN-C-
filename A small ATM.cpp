#include <iostream>
#include <fstream>
using namespace std;
/*Osmisliti projekat bankomata. Program treba nuditi korisniku da sam bira da li zeli vidjeti broj svog  računa, stanje na računu, podići novac, uplatiti sebi novac,
uplatiti nekom novac.Te 4 opcije se pokreću svaki put nakon sto korisnik odradi neku stavr. Da bi se izbacila kartica van potrebno je da korisnik unese broj -1 i bankomat se tad gasi.*/
/*OBJASNJENJE: Podaci o svim ljudima u banci se nalaze u jednom teksualnom dokumentu, tu mozemo vidjeti ime, prezime, broj racuna i iznos koji ima. Iznos mozemo vijdeti u KM i u eurima. Takode u datoteci se 
cuva sifra svake osobe. Prilikom izbora sta osobi treba ona mora unijeti svoju sifru. Ako je sifra netacna nije moguce odraditi nista. Nakon uplate ili isplate bankomat se
automatski gasi. Takode osoba moze odredeni novac prenijeti drugom racunu. Zadnja opcija koja se nudi je da osoba sebe prijavi na bankomat. Pri uclanjenju treba unijeti ime, prezime
broj racuna koji dobije u banci i sifru. Na pocetku ima 0KM na bankomatu. Ako zeli nesto dodati treba nakon uclanjenja kliknuti opciju 3 */


struct clanovi{
	string ime;
	string prezime;
	int broj_racuna;
	float iznos;
	int sifra;
	
};


const int maxbroj = 10;
clanovi korisnik[maxbroj];


fstream datoteka;


int povlacenjeizdatoteke();
void stanjenaracunu(int ukupno);
void provjerabrojaracuna(int ukupno);
int podizanjenovca(int ukupno);
int uplatanovca(int ukupno);
int uplatanadrugiracun(int ukupno);
void uclanjivanje(int ukupno);


int main(){
	
	int ukupno; //Uzimamo broj clanova u datoteci da bismo mogli pristupiti ostalim funkcijama
	ukupno = povlacenjeizdatoteke();
	int opcija;
	do
	{
		cout<<endl<<endl<<"Dobrodosli na bankomat. Ispod se nalazi spisak stvari koje Vam nudi nas bankomat. Da biste pristupili nekoj od operacija obavezno je unijeti sifru"<<endl;
		cout<<"1. Saznajte broj Vaseg racuna"<<endl;
		cout<<"2. Pogledajte stanje na racunu"<<endl;
		cout<<"3. Podizanje novca"<<endl;
		cout<<"4. Uplata novca na racun"<<endl;
		cout<<"5. Uplata novca na drugi racun"<<endl;
		cout<<"6. Prijavite se na nas bankomat"<<endl;
		cin>>opcija;
		
		switch(opcija)
		{
			case 1:
				{
					provjerabrojaracuna(ukupno);	
					break;
				}
				
			case 2:
				{
					stanjenaracunu(ukupno);
					break;					
				}
				
			case 3:
				{
					int rezultat;
					rezultat= podizanjenovca(ukupno);
					if(rezultat==1)
					{
						return 0;
					}
					if(rezultat==2)
					{
						cout<<"Pokusajte sve birati ispocetka"<<endl;
						break;
					}
				}
				
			case 4:
				{
					int rezultat;
					rezultat= uplatanovca(ukupno);
					if(rezultat==1)
					{
					return 0;
					}
					if(rezultat==2)
					{
						cout<<"Pokusajte sve birati ispocetka"<<endl;
						break;	
					}
				}
			
			case 5:
				{
					int rezultat;
					rezultat= uplatanadrugiracun(ukupno);
					if(rezultat==1)
					{
						cout<<endl<<"Nakon uplate na drugi racun moramo izbaciti Vasu karticu. "<<endl<<"Hvala Vam na povjerenju"<<endl;
						return 0;
					}
					if(rezultat==2)
					{
						cout<<"Pokusajte sve birati ispocetka"<<endl;
						break;
					}
					if(rezultat==3)
					{
						cout<<"Zbog nemogucnosti da pronademo racun koji ste trazili nudimo Vam da ponovo sve ispocetka birate"<<endl;
						break;
					}
				}
				
			case 6:
				{
					uclanjivanje(ukupno);
					return 0;
				}
		}
		
	}
	while (opcija!=-1);
	
	return 0;
}


int povlacenjeizdatoteke() {
	
    datoteka.open("clanovi.txt", ios::in);
    
    if (!datoteka.is_open()) {
        cout << "Ne mogu da otvorim datoteku!" << endl;   //Funkcija provjerava da li je datoteka otvorena, ako nije odmah se izlazi iz cijele ove funkcije
        return -1; 
    }
    
    int brojac = 0;

    while (brojac < maxbroj && datoteka >> korisnik[brojac].ime >> korisnik[brojac].prezime >> korisnik[brojac].broj_racuna >> korisnik[brojac].iznos >> korisnik[brojac].sifra) { //Povlacenje podataka iz datoteke
        brojac++;
    }

    datoteka.close(); 
    return brojac;
}

void provjerabrojaracuna(int ukupno)
{
		int broj;	
		cout<<endl<<"Unesite sifru"<<endl;
		cin>>broj;
		int br=0;
					
		for(int i=0; i<=ukupno; i++)
		{
						
			if(korisnik[i].sifra ==broj) //Provjera imamo li u datoteci unesenu sifru
				{
					cout<<endl<<"Postovani/a "<<korisnik[i].ime<<" broj Vaseg racuna je: "<<korisnik[i].broj_racuna<<endl;
					br++;  //Ako se br poveca znaci da je korisnik pronades i iduci if uslov nije ispunjen
				}
						
				if(korisnik[i].sifra!=broj && i==ukupno && br==0)   //Za slucaj da nije pronadena sifra ispisuje se poruka
				{
					cout<<"Vasa sifra nije pronadena "<<endl;
				}
						
		}
}

void stanjenaracunu(int ukupno)
{
	int broj;			
	int br=0;
	cout<<endl<<"Unesite sifru"<<endl;
	cin>>broj;
					
	for(int i=0; i<=ukupno; i++)
	{		
		if(korisnik[i].sifra ==broj) //Provjera imamo li u datoteci unesenu sifru
		{
							
			int valuta;
			cout<<endl<<"Postovani/a "<<korisnik[i].ime<<" u kojoj valuti zelite vidjeti iznos? Ako zelite vidjeti u KM unesite 1, a ako zelite u eurima unesite 2"<<endl;
			cin>>valuta;
							
			if(valuta ==1)
			{
				cout<<"Na Vasem racunu se nalazi "<<korisnik[i].iznos<<" KM"<<endl;
			}
							
			if(valuta==2)
			{
				float euri = korisnik[i].iznos /2;
				cout<<"Na Vasem racunu se nalazi "<<euri<<" eura";
			}
			
			br++;
		}
						
		if(korisnik[i].sifra!=broj && i==ukupno && br==0)   //Za slucaj da nije pronadena sifra ispisuje se poruka ispod
		{
			cout<<"Vasa sifra nije pronadena samim tim ne mozemo naci broj Vaseg racuna"<<endl;
		}
	}
}


int podizanjenovca (int ukupno) {
	int rez;
	int br=0;
	int broj,ostatak, novac,pare;
	cout<<endl<<"Unesite Vasu sifru"<<endl;
	cin>>broj;
	
	for(int i=0; i<=ukupno; i++)
	{
		
		if(korisnik[i].sifra== broj)
		{
			rez=1;
			cout<<endl<<"Postovani/a "<<korisnik[i].ime<<" Vase stanje na racunu je "<<korisnik[i].iznos;
			cout<<" Unesite zeljeni iznos koji mora biti manji ili jednak Vasem iznosu i djeljiv sa 10"<<endl;
			cin>>novac;
			
			while(novac%10!=0)
			{
				cout<<"Uneseni iznos nije djeljiv za 10. "<<endl<<"Pokusajte ponovo"<<endl;
				cin>>novac;
			}
			
			pare=novac; //Da bi sacuvala uneseni iznos jer se novac poslije kroz zadatak mijenja
			cout<<"Isplacujemo Vam Vas iznos"<<endl;
			
			while(novac>=100 && novac%10==0)
			{
				cout<<"Novcanica od 100 KM"<<endl;
				novac=novac-100;
			}
			
			while(novac>=50 && novac%10==0)
			{
				cout<<"Novcanica od 50KM"<<endl;
				novac=novac-50;
			}
			
			while(novac>=20 && novac%10==0)
			{
				cout<<"Novcanica od 20KM"<<endl;
				novac=novac-20;
			}
			
			while(novac>=10 && novac %10==0)
			{
				cout<<"Novcanica od 10KM"<<endl;
				novac=novac-10;
			}
			
			int pozicija =i;
			
			cout<<endl<<"Isplata je zavrsena."<<" Uspjeli smo Vam isplatiti "<<pare<<" KM."<<endl;
			ostatak=korisnik[i].iznos-pare;
			cout<<endl<<"U banci Vam je ostalo jos "<<ostatak<<" KM"<<endl;
			cout<<endl<<"Nakon isplate potrebno je ugasiti bankomat. Hvala Vam na povjerenju"<<endl;
			
			datoteka.open("clanovi.txt", ios::out);
			if(datoteka.is_open())
			{
				for(int k=0; k<=ukupno; k++)
				{
					
					if(k==pozicija) //Kad naidemo na naseg koji je dizao novac prekucamo novi iznos
					{
						datoteka<<endl<<korisnik[k].ime<<" "<<korisnik[k].prezime<<" "<<korisnik[k].broj_racuna<<" "<<ostatak<<" "<<korisnik[k].sifra<<endl;
					}
					
					if(k!=pozicija) //Ako ta osoba nije podizala novac stanje treba biti isto
					{
						datoteka<<korisnik[k].ime<<" "<<korisnik[k].prezime<<" "<<korisnik[k].broj_racuna<<" "<<korisnik[k].iznos<<" "<<korisnik[k].sifra<<endl;
					}
					
					}
			}
			datoteka.close();
			br++;	
		}
		
		if(korisnik[i].sifra!=broj && i==ukupno && br==0)
		{
			cout<<"Nismo Vas pronasli u nasem sistemu"<<endl;
			rez =2;
		}
	}	
	return rez;
}


int uplatanovca(int ukupno)
{
	int rez;
	int broj;
	int brojac =0;
	cout<<endl<<"Unesite sifru"<<endl;
	cin>>broj;
	
	for(int i=0; i<=ukupno; i++)
	{
		
		if(korisnik[i].sifra==broj)
		{
			rez=1;
			int pare;
			cout<<endl<<"Hvala Vam sto ste izabrali bas nas. Novcanice poredajte tako da budu sve okrenute na istu stranu te zatim unesite tacno koliko ste novcanica dodali u KM"<<endl;
			cin>>pare;
			
			while(pare&10 !=0 )
			{
				cout<<"Uneseni iznos nije djeljiv sa 10. Pokusajte ponovo"<<endl;
				cin>>pare;
			}
			
			int iznos2;
			iznos2=pare+korisnik[i].iznos;
			cout<<endl<<"Novac smo spremili u Vasu kasu "<<korisnik[i].ime<<" sad na Vasem racunu imate "<<iznos2<<" KM";
			cout<<endl<<"Nakon uplate novca bankomat se mora ugasiti i izbaciti kartica"<<endl<<"Hvala Vam na povjerenju"<<endl;
			
			datoteka.open("clanovi.txt", ios::out);
			
			if(datoteka.is_open())
			{
				for(int k=0; k<ukupno; k++)
				{
					
					if(k==i) //Kad naidemo na naseg koji je uplatio novac prekucamo novi iznos
					{
						datoteka<<endl<<korisnik[k].ime<<" "<<korisnik[k].prezime<<" "<<korisnik[k].broj_racuna<<" "<<iznos2<<" "<<korisnik[k].sifra<<endl;
					}
					
					if(k!=i) //Ako ta osoba nije podizala novac stanje treba biti isto
					{
						datoteka<<korisnik[k].ime<<" "<<korisnik[k].prezime<<" "<<korisnik[k].broj_racuna<<" "<<korisnik[k].iznos<<" "<<korisnik[k].sifra<<endl;
					}
					
					}
			}
			datoteka.close();
			brojac++;	
		}
		if(korisnik[i].sifra!=broj && i==ukupno && brojac==0)
		{
			rez=2;
			cout<<"Nismo pronasli Vasu sifru"<<endl;
		}
		}
		return rez;
	}
	

int uplatanadrugiracun(int ukupno)
{
	int rez;
	int broj;
	int br1=0;
	cout<<endl<<"Unesite sifru"<<endl;
	cin>>broj;
	for(int i=0; i<ukupno; i++)
	{
		
		if(korisnik[i].sifra == broj)
		{
		
			rez=1;
			int pozicijaosobekojauplacuje = i;
			int opcija;
			cout<<"Unesite racun na koji zelite uplatit novac. Nudimo Vam dvije opcije"<<endl;
			cout<<"1.Prenos odredenog dijela Vaseg novca na drugi racun"<<endl;
			cout<<"2.Uplata novcanica direktno na racun "<<endl;
			cout<<"Izaberite nacin prenosa"<<endl;
			cin>>opcija;
			
			if(opcija==1)
			{
				int racun, uplata;
				int vasnovac;
				vasnovac=korisnik[i].iznos;
				cout<<endl<<"Unesite racun na koji trebamo prenijeti novac"<<endl;
				cin>>racun;
				cout<<"Unesite kolicinu novca koju prenosimo na drugi racun: "<<endl;
				cin>>uplata;
				
				while(uplata % 10 !=0)
				{
					cout<<"Unesena cifra nije djeljiva sa 10. Pokusajte ponovo "<<endl;
					cin>>uplata;
				}
				
				for(int k=0; k<ukupno; k++)
				{
					
					int brojac=0;
					if(korisnik[k].broj_racuna == racun)
					{
						int pozicija =k;
						int pare= korisnik[k].iznos + uplata;
						vasnovac=vasnovac-uplata;
						cout<<endl<<"Na racun "<<korisnik[pozicija].ime<<" ste uplatili "<<uplata<<endl;
						
						datoteka.open("clanovi.txt", ios::out);
						
						if(datoteka.is_open())
						{
							
							for(int z=0; z<ukupno; z++)
							{
								
								if(z==pozicija)
								{
									datoteka<<korisnik[z].ime<<" "<<korisnik[z].prezime<<" "<<korisnik[z].broj_racuna<<" "<<pare<<" "<<korisnik[z].sifra<<endl;
								}
								
								if(z!=pozicija && z!=pozicijaosobekojauplacuje)
								{
									datoteka<<korisnik[z].ime<<" "<<korisnik[z].prezime<<" "<<korisnik[z].broj_racuna<<" "<<korisnik[z].iznos<<" "<<korisnik[z].sifra<<endl;
								}
								
								if(z==pozicijaosobekojauplacuje)
								{
									datoteka<<korisnik[z].ime<<" "<<korisnik[z].prezime<<" "<<korisnik[z].broj_racuna<<" "<<vasnovac<<" "<<korisnik[z].sifra<<endl;
								}
								
							}
						}
						datoteka.close();
						brojac++;
						
					}
					
				if(brojac==0 && korisnik[k].broj_racuna!= racun && k==ukupno-1)
				{
					cout<<endl<<"Nismo pronasli broj racuna koji ste unijeli"<<endl;
					rez=3;
				}
				
				}
			}
			
			br1++;
			
			if(opcija==2)
			{
				
				int iznos, racun;
				cout<<endl<<"Unesite racun na koji zelite prenijeti novac"<<endl;
				cin>>racun;
				cout<<"Ubacite novac koji zelite poslati"<<endl;
				cin>>iznos;
				
				if(iznos % 10 !=0)
				{
					cout<<"Uneseni iznos nije djeljiv sa 10. Pokusajte ponovo"<<endl;
					cin>>iznos;
				}
				
				for(int o=0; o<ukupno; o++)
				{
					int brooo=0;
					
					if(korisnik[o].broj_racuna==racun)
					{
						cout<<"Na racun "<<korisnik[o].ime<<" ste uplatili "<<iznos<<endl;
						int poz=o;
						datoteka.open("clanovi.txt", ios::out);
						
						if(datoteka.is_open())
						{
							for(int p=0; p<ukupno; p++)
							{
								if(p==poz)
								{
									datoteka<<korisnik[p].ime<<" "<<korisnik[p].prezime<<" "<<korisnik[p].broj_racuna<<" "<<korisnik[p].iznos + iznos<<" "<<korisnik[p].sifra<<endl;
								}
								if(p!=poz)
								{
									datoteka<<korisnik[p].ime<<" "<<korisnik[p].prezime<<" "<<korisnik[p].broj_racuna<<" "<<korisnik[p].iznos<<" "<<korisnik[p].sifra<<endl;
								}
							}
						}
						
						brooo++;
					}
					
					if(brooo==0 && korisnik[o].broj_racuna!=racun && o==ukupno-1)
					{
						cout<<"Nismo pronasli trazeni racun"<<endl;
						rez=3;
					}
				}
				
			}
			br1++;
		}
		
		if(br1==0 && korisnik[i].sifra!=broj && i==ukupno-1)
		{
			rez=2;
			cout<<"Nismo pronasli Vasu sifru"<<endl;
		}
		
	}
	return rez;
}


void uclanjivanje(int ukupno)
{
	cout<<endl<<"Hvala Vam na ukazanom povjerenju. U banci ste dobili sve potrebne informacije(broj racuna i sfiru)."<<endl;
	cout<<"Unesite sve potrebne stvari navedenim redom"<<endl;
	
	datoteka.open("clanovi.txt", ios::out);
	
	if(datoteka.is_open())
	{
		string ime, prezime;
		int sifra, racun;
		cout<<endl<<"Unesite Vase ime: ";
		cin>>ime;
		cout<<endl<<"Unesite Vase prezime: ";
		cin>>prezime;
		cout<<endl<<"Unesite dodijeljeni broj racuna: ";
		cin>>racun;
		cout<<endl<<"Unesite Vasu sifru: ";
		cin>>sifra;
		
		for(int i=0; i<=ukupno; i++)
		{
			
			if(i==ukupno)
			{
				datoteka<<ime<<" "<<prezime<<" "<<racun<<" "<<" 0" <<" "<<sifra<<endl;
			}
			
			if(i!=ukupno)
			{
				datoteka<<korisnik[i].ime<<" "<<korisnik[i].prezime<<" "<<korisnik[i].broj_racuna<<" "<<korisnik[i].iznos<<" "<<korisnik[i].sifra<<endl;
			}
			
		}
			
	}
	datoteka.close();
	cout<<"Hvala jos jednom, trenutno ste clan banke. Stanje Vseg racuna je 0KM. Da biste to promijenili stavite ponovo karticu i dodajte novac."<<endl<<"Sretno!"<<endl;
}