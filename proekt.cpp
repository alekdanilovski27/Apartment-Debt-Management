#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//struktura za zacuvuvanje na vlezni podatoci
struct apartment{
    char Ime[15];
    char Prezime[15];
    int apartNum;
    float quadrature;
    float mRata;
    float Dolg;
    int Rok[3];
};

//struktura za zacuvuvanje na sopstvenicite na stanovite.
struct owner{
    char Ime[15];
    char Prezime[15];
    int apartment_count;
    float Dolg;
	float mRata;
    int Rok[3];
};

//funkcija za presmetuvanje na mesecna rata
float presmetajRata(float quadrature){
    return 0.1 * quadrature * 61.5+100;
}

// Ovaa funkcija pominuva niz niza sopstvenici i gi sortira spored dospeaniot dolg.
void bubbleSortDesc(owner arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].Dolg < arr[j + 1].Dolg){
                owner temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main(){
    const int MAKS_APARTMANI = 60;
    int n;
    fstream podatoci;
    podatoci.open("vlez.dat", ios::out);
    if(!podatoci.is_open()){	//tuka proveruvame dali ke mozi da se otvori fajlot "vlez.dat".
        cout<<"Fajlot ne moze da se otvori!";	//dokolku ne mozi ovaa poraka ke se ispecati na ekranot.   
        return 0;
    }
    cout<<"Vnesete go brojot na kolku stanovi sakate da vnesete (maksumum e 60) "<<endl;;
    cin>>n;
    if(n > MAKS_APARTMANI){      //tuka proveruvame dali vneseniot broj e pogolem od maksimalniot broj na stanovi sto mozat da postojat.
        cout<<"Maksimalniot broj na stanovi e 60. "<<endl; 	//dokolku n e pogolem od 60 ovaa poraka ke se ispecati na ekranot.
        return 0;
    }
    
	for (int i=0; i<n; i++) {	//ovoj for ciklus sluzi za vnesuvanje na vleznite podatoci zavisno od brojot n.
		apartment Apartments;	//na primer ako n=3 togas ke treba da vneseme podatoci za 3 stanovi.
		
    	cout<<"Vnesi ime: ";
    	cin>>Apartments.Ime;
    	
    	cout<<"Vnesi prezime: ";
    	cin>>Apartments.Prezime;
    	
    	cout<<"Vnesi broj na stan: ";
    	cin>>Apartments.apartNum;
    	
    	cout<<"Vnesi kvadratura: ";
    	cin>>Apartments.quadrature;
    	
    	Apartments.mRata = presmetajRata(Apartments.quadrature);	//tuka ja koristime funkcijata za presmetuvanje na rati.
    	cout<< "Mesecna rata: " << Apartments.mRata << endl;
    	
    	cout<<"Vnesete go dolgot: ";
    	cin>>Apartments.Dolg;
    
    	cout<<"Vnesete den: ";
    	cin>>Apartments.Rok[0];
    	cout<<"Vnesete mesec: ";
    	cin>>Apartments.Rok[1];
    	cout<<"Vnesete godina: ";
    	cin>>Apartments.Rok[2];
    	
    	podatoci << Apartments.Ime << endl;
    	podatoci << Apartments.Prezime << endl;
    	podatoci << Apartments.apartNum << endl;
    	podatoci << Apartments.quadrature << endl;
    	podatoci << Apartments.mRata << endl;
    	podatoci << Apartments.Dolg << endl;
    	podatoci << Apartments.Rok[0] << endl;
    	podatoci << Apartments.Rok[1] << endl;
    	podatoci << Apartments.Rok[2] << endl;
	}
	podatoci.close();
	
	owner owners[60];
	int curr_owner = 0;
	
	podatoci.open("vlez.dat", ios::in);
	for (int i=0; i<n; i++){
		apartment Apartments;
		
		podatoci >> Apartments.Ime;
    	podatoci >> Apartments.Prezime;
		podatoci >> Apartments.apartNum;
		podatoci >> Apartments.quadrature;
		podatoci >> Apartments.mRata;
		podatoci >> Apartments.Dolg;
		podatoci >> Apartments.Rok[0];
		podatoci >> Apartments.Rok[1];
		podatoci >> Apartments.Rok[2];
		
		bool owner_exists_already = false;
		for( int y = 0; y < curr_owner; y++ ){
			
			if( strcmp(owners[y].Ime, Apartments.Ime) == 0	//ovoj IF proveruva dali imeto i prezimeto na sopstvenikot se vneseni
			&& strcmp(owners[y].Prezime, Apartments.Prezime) == 0 )
			{
				owners[y].Dolg += Apartments.Dolg;
				owners[y].mRata += Apartments.mRata;
				owners[y].apartment_count++;
				owner_exists_already = true;
				break;
			}
		}
				
		if( owner_exists_already )
			continue;
		
		strcpy( owners[curr_owner].Ime, Apartments.Ime );
		strcpy( owners[curr_owner].Prezime, Apartments.Prezime );
		owners[curr_owner].Dolg = Apartments.Dolg;
		owners[curr_owner].mRata = Apartments.mRata;
		owners[curr_owner].apartment_count = 1;
		owners[curr_owner].Rok[0] = Apartments.Rok[0];
		owners[curr_owner].Rok[1] = Apartments.Rok[1];
		owners[curr_owner].Rok[2] = Apartments.Rok[2];
		curr_owner++;
	}
	podatoci.close();
	
	bubbleSortDesc(owners, curr_owner);
	
	for( int i = 0; i < curr_owner; i++ ){
		cout << owners[i].Ime << "\t" << owners[i].apartment_count << "\t" << owners[i].Dolg;
		
		if( owners[i].Dolg == 0 )
			continue;
			
		if( owners[i].Dolg / owners[i].mRata < 4.0f ){
			cout << "\tOPOMENA DA SE PLATI DO: " << owners[i].Rok[0]<< "/" << owners[i].Rok[1] << "/" << owners[i].Rok[2] << endl;
		}
		else
			cout << "\tPREDADEN NA IZVRSITEL." << endl;
	}
	return 0;
}
