#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
const int N=5;									//wysoko�� planszy
const int M=6;									//szeroko�� planszy
const int K=3;									//ilo�� potwor�w
void pustaTablica(char T[][M], char hT[][M]);
int gra(char T[][M], char hT[][M]);


int main()
{
	char T[N][M];								
	char hT[N][M];
	int end = 0;
	
	pustaTablica(hT, T);						//wczytuje dwie tablice
	
	while(end == 0){							//dop�ki gra zwraca warto�� 0 to dalej trwa,je�li nie, gra si� ko�czy
		end = gra(hT, T);
	}

	system("CLS");								//ostatnie wy�wietlenie planszy
	for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
    
			cout << T[ i ][ j ];
        }
        cout << endl;
    }
    cout << endl;
    if (end == 2) cout << "Wygrales";			//gdy gra zwr�ci warto�� 2 to wy�wietla,�e wygra�e�
    else cout << "Przegrales";					//gdy gra zwr�ci warto�� 1 to wy�wietla,�e przegra�e�

	return 0;
}

void pustaTablica(char hT[][M], char T[][M])
{	
	srand(time(NULL));
	int losN;
	int losM;
	int zmiana=0;
	// zapelnianie hash i kropkami
	for( int i = 0; i < N; i++ )				
    {
        for( int j = 0; j < M; j++ )
        {
            T[ i ][ j ] = '.';
            hT[ i ][ j ] ='#';
        }
    }
    	
	//losujemy pozycj� gracza
	while(zmiana!=1)						
    {										
		losN=(rand()%(N-1))+0;				//pierwsza wsp�rz�dna	
		losM=(rand()%(M-1))+0;				//druga wsp�rz�dna
		hT[losN][losM]='a';					//nadpisujemy pozycje gracza jako 'a'
		zmiana++;
	}
	zmiana = 0;
	
	//losujemy pozycj� potwor�w
	while(zmiana!=K)								
    {	
		losN=(rand()%(N-1))+0;
		losM=(rand()%(M-1))+0;
		if (T[losN][losM]=='.'){			//je�li obecna wsp�rz�dna jest oznaczona jako kropka nadpisujemy pozycje potwora jako '!' (tworzymy to, aby  nie powt�rzy�y si� wsp�rz�dne z innymi rzeczami)
			T[losN][losM]='!';
			zmiana++;
		}
	}
	zmiana = 0;
	
	//losujemy pozycj� klucza
    while(zmiana!=1)							
    {	
		losN=(rand()%(N-1))+0;
		losM=(rand()%(M-1))+0;
		if (T[losN][losM]=='.'){
			T[losN][losM]='k';
			zmiana++;
		}
	}
	zmiana = 0;
	
	//losujemy pozycj� drzwi
    while(zmiana!=1)
    {	
		losN=(rand()%(N-1))+0;
		losM=(rand()%(M-1))+0;
		if (T[losN][losM]=='.'){
			T[losN][losM]='$';
			zmiana++;
		}
	}
	zmiana = 0;	

}	

int gra(char hT[][M], char T[][M]){
	
	int zycie = 3;					//tu ustalamy ile mamy �y�
	int klucz = 0;
	char gracz = 'a';			
	
	while (true){
	int n, m;
	char ruch; 
	// print
	system("cls");
	
	for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
            if (hT[i][j] == gracz){
				n = i;
            	m = j;
			}
			if (T[i][j] == 'k' && hT[i][j] == 'a')	//je�li znajdziemy si� na polu klucz to 'a' zamieni si� na '@', ale tylko na tym polu (aby od razu jak wejdzie si� na klucz si� zamieni�y)
			cout << '@';				
			else cout << hT[i][j];
        }
        cout << endl;
    }
      
   
    
    cout << endl;
    if(T[n][m] == 'k'){							//jesli wejdziemy na pole klucz
		cout << "znalazles klucz ";			
		gracz = '@';								//'a' zamienia si� na '@' i ustawia wartosc klucza na 1	
		klucz = 1;
	}
    else if(T[n][m] == '!'){
    	cout << "znalazles potwora ";
		zycie -= 1;								//za ka�dym razem jak wejdziemy na potwora to zmniejsza nam si� �ycie o jeden
		if (zycie == 0) {						//je�li nie mamy ju� �y� to gra zwraca warto�� jeden i ko�czy gr�
			if(klucz == 1) T[n][m] = '@';		//je�li mieli�my klucz to gra na koniec wy�wietla nasz� pozycj� jako '@', je�li nie to jako 'a'
			else T[n][m] = 'a';
		return 1;
		}
	}
	else if(T[n][m] == '$'){
    	cout << "znalazles drzwi ";
		if (klucz == 1) {						//je�li znajdujemy si�na drzwiach i mamy klucz to zwraca warto�� 2 i ko�czy gr�
		T[n][m] = '@';
		return 2;
		}
	}
	else cout << "nic nie znalazles ";
 	
	// poruszanie   
    cin >> ruch;
    switch(ruch)
	{

	case 'w':
		if(n-1 >= 0){
			// sprawdza czy na polu ktorym stalismy bylo cos innego niz . jezeli tak to odstawia to
			if(T[n][m] != '.'){
				hT[n][m] = T[n][m];		
			}
			else hT[n][m] = '.';		// jezeli nie to daje kropk�
				hT[n-1][m] = gracz;		
		}
    break;
	
	case 'a':
		if(m-1 >= 0){
			if(T[n][m] != '.'){
				hT[n][m] = T[n][m];
			}
			else hT[n][m] = '.';
				hT[n][m-1] = gracz;
		}
    break;  
     
	case 's':
		if(n+1 < N){
			cout << n+1 << endl;
			if(T[n][m] != '.'){
				hT[n][m] = T[n][m];
			}
			else hT[n][m] = '.'; 
			hT[n+1][m] = gracz; 
		}
    break;
   
	case 'd':
		if(m+1 < M){
			if(T[n][m] != '.'){
				hT[n][m] = T[n][m];
			}
			else hT[n][m] = '.';
				hT[n][m+1] = gracz;
		}
		    break;  
	}
}
}


