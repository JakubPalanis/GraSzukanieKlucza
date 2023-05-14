#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
const int N=5;									//wysokoœæ planszy
const int M=6;									//szerokoœæ planszy
const int K=3;									//iloœæ potworów
void pustaTablica(char T[][M], char hT[][M]);
int gra(char T[][M], char hT[][M]);


int main()
{
	char T[N][M];								
	char hT[N][M];
	int end = 0;
	
	pustaTablica(hT, T);						//wczytuje dwie tablice
	
	while(end == 0){							//dopóki gra zwraca wartoœæ 0 to dalej trwa,jeœli nie, gra siê koñczy
		end = gra(hT, T);
	}

	system("CLS");								//ostatnie wyœwietlenie planszy
	for( int i = 0; i < N; i++ )
    {
        for( int j = 0; j < M; j++ )
        {
    
			cout << T[ i ][ j ];
        }
        cout << endl;
    }
    cout << endl;
    if (end == 2) cout << "Wygrales";			//gdy gra zwróci wartoœæ 2 to wyœwietla,¿e wygra³eœ
    else cout << "Przegrales";					//gdy gra zwróci wartoœæ 1 to wyœwietla,¿e przegra³eœ

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
    	
	//losujemy pozycjê gracza
	while(zmiana!=1)						
    {										
		losN=(rand()%(N-1))+0;				//pierwsza wspó³rzêdna	
		losM=(rand()%(M-1))+0;				//druga wspó³rzêdna
		hT[losN][losM]='a';					//nadpisujemy pozycje gracza jako 'a'
		zmiana++;
	}
	zmiana = 0;
	
	//losujemy pozycjê potworów
	while(zmiana!=K)								
    {	
		losN=(rand()%(N-1))+0;
		losM=(rand()%(M-1))+0;
		if (T[losN][losM]=='.'){			//jeœli obecna wspó³rzêdna jest oznaczona jako kropka nadpisujemy pozycje potwora jako '!' (tworzymy to, aby  nie powtórzy³y siê wspó³rzêdne z innymi rzeczami)
			T[losN][losM]='!';
			zmiana++;
		}
	}
	zmiana = 0;
	
	//losujemy pozycjê klucza
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
	
	//losujemy pozycjê drzwi
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
	
	int zycie = 3;					//tu ustalamy ile mamy ¿yæ
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
			if (T[i][j] == 'k' && hT[i][j] == 'a')	//jeœli znajdziemy siê na polu klucz to 'a' zamieni siê na '@', ale tylko na tym polu (aby od razu jak wejdzie siê na klucz siê zamieni³y)
			cout << '@';				
			else cout << hT[i][j];
        }
        cout << endl;
    }
      
   
    
    cout << endl;
    if(T[n][m] == 'k'){							//jesli wejdziemy na pole klucz
		cout << "znalazles klucz ";			
		gracz = '@';								//'a' zamienia siê na '@' i ustawia wartosc klucza na 1	
		klucz = 1;
	}
    else if(T[n][m] == '!'){
    	cout << "znalazles potwora ";
		zycie -= 1;								//za ka¿dym razem jak wejdziemy na potwora to zmniejsza nam siê ¿ycie o jeden
		if (zycie == 0) {						//jeœli nie mamy ju¿ ¿yæ to gra zwraca wartoœæ jeden i koñczy grê
			if(klucz == 1) T[n][m] = '@';		//jeœli mieliœmy klucz to gra na koniec wyœwietla nasz¹ pozycjê jako '@', jeœli nie to jako 'a'
			else T[n][m] = 'a';
		return 1;
		}
	}
	else if(T[n][m] == '$'){
    	cout << "znalazles drzwi ";
		if (klucz == 1) {						//jeœli znajdujemy siêna drzwiach i mamy klucz to zwraca wartoœæ 2 i koñczy grê
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
			else hT[n][m] = '.';		// jezeli nie to daje kropkê
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


