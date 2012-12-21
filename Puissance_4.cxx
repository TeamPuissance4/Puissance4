/**
 *
 * @file   Puissance_4.cxx
 *
 * @authors Kilian SCOUR Antoine MERINO Thomas BIANCHINI Julie MIENVILLE
 *
 * @date   21/12/2012
 *
 * @brief  Projet puissance 4 en C++ sur console Linux
 * 
 * Veuillez lire le fichier README.txt
 *
**/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

namespace
{


    typedef vector <char> CVLigne;
    typedef vector <CVLigne> CVMatrice;
    
/*******************VARIABLES PAR DEFAUT ******************/
const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMagenta ("35");
const string KCyan    ("36");
char Jeton1 = 'X';
char Jeton2 = 'O';
string NJoueur1 = "Joueur1";
string NJoueur2 = "Joueur2";
char ChoixParam = '3';
string Cheat1 ("Casali"), Cheat2 ("Laporte");
 /**************************PARAMETRES JOUEURS *********************/
   void Couleur (const string & coul)
    {
        cout << "\033[" << coul.c_str () <<"m";
    }// Couleur ()
    	

    void SaisieJeton (char & Jeton1, char & Jeton2, string & NJoueur1, string & NJoueur2)
    {
        cout << "Saisissez le jeton de ";
        Couleur (KRouge); 
        cout << NJoueur1;
        Couleur (KReset);
        cout << " (Caractère éditable) :";
        string Buffer;
        getline(cin, Buffer);
        Jeton1 = Buffer[0];
        cout << endl;
        for (;;)
        {
            cout << "Saisissez le jeton de ";
            Couleur (KBleu);
            cout << NJoueur2;
            Couleur (KReset);
            cout << " (Caractère éditable) : ";
            string Buffer;
            getline(cin, Buffer);
            Jeton2 = Buffer[0];
            if (Jeton2 != Jeton1) break;
            cerr << "Choisissez un jeton différent de " << NJoueur1 << "." << endl;
        }
    } // SaisieJeton ()
    
    void SaisirNJoueur (string & NJoueur1, string & NJoueur2)
    {
		Couleur (KRouge);
        cout << "Nom du joueur 1 : ";
        Couleur (KReset);
        getline(cin, NJoueur1);
        for (;;)
        {
        	Couleur (KBleu);
            cout << "Nom du joueur 2 : ";
            Couleur (KReset);
            getline(cin, NJoueur2);
            
            if (NJoueur2 != NJoueur1) break;
            cerr << "Choisissez un pseudo différent de " << NJoueur1 << "!" << endl;
        }
        cout << "Le joueur 1 est : " << NJoueur1 << " ";
        if (NJoueur1 == Cheat1 || NJoueur1 == Cheat2)
        {
        	cout << "Correcteur Spotted" << endl;
		}
        cout << endl << "Le joueur 2 est : " << NJoueur2 << " ";
        if (NJoueur2 == Cheat1 || NJoueur2 == Cheat2)
        {
        		cout << "Correcteur Spotted" << endl;
        }
        cout << endl << "Appuyer sur entrée pour retourner dans le menu...";
        cin.get();
        
    }// SaisirNJoueur   
    
       /***********************************************************************    
    
    ***************************AFFICHAGE DE LA MATRICE*********************/    

	void ClearScreen ()
	{
        cout << "\033[H\033[2J";
    } // ClearScreen ()
    
    void AfficheLigne (const CVLigne & Li)
    {
        for (unsigned i (0); i < Li.size(); ++i)
        {
            cout << setw(3) << Li[i];
        }
        cout << endl;
    } // AfficheLigne()
    
    void AfficheMatrice (const CVMatrice & Mat)
    {
        for (unsigned i (0); i < Mat.size(); ++i)
        {
            AfficheLigne (Mat[i]);
        }
        
    } // AficheMatrice ()
    
    void AffichePuissance4 (const CVMatrice & Mat)
    {
    	
        AfficheMatrice (Mat);
        CVLigne Tirets (23, '-');
        for (unsigned i (0); i < Tirets.size(); ++i)
        {
            Couleur (KMagenta);
            cout << Tirets[i];
            Couleur (KReset);
        }
        cout << endl;
        char alpha[] = "ABCDEFG";
        CVLigne Lettres (alpha, alpha+sizeof(alpha)-1);
        AfficheLigne(Lettres);
    } // Affichepuissance4 ()
    
/*********************************************************************/

   
    void InitMat (CVMatrice & Mat)
    {
        CVLigne Li (7, '.');
        for (unsigned i (0); i < Mat.size(); ++i)
        {
            Mat[i] = Li;
        }
    } // InitMat()
    

    
    bool PositionneJeton (CVMatrice & Mat, const unsigned NumCol, unsigned & NumLi, const bool CoupDuJoueur1)
    {
        char Pion (CoupDuJoueur1 ? Jeton1 : Jeton2);
        
        for (NumLi = 6; NumLi != 0; --NumLi)
        {
            if (Mat[NumLi][NumCol] == '.') break;
        }
        if (NumLi >= 0 && Mat[NumLi][NumCol] == '.')
        {
            Mat[NumLi][NumCol] = Pion;
            return true;  
        }
        return false;
    } // PositionneJeton ()
    
/*********************************TEST DE VICTOIRE************************/  
  
    bool TestVictoireColonne (const CVMatrice & Mat, const unsigned NumLi, const unsigned NumCol, const bool CoupDuJoueur1)
    {
        if (NumLi >= 4) return false;
        unsigned i;
        for (i = NumLi; i < NumLi + 4; ++i)
        {
            if (Mat[i][NumCol] == (CoupDuJoueur1 ? Jeton1 : Jeton2)) continue;
            break;
        }
        if (i == NumLi + 4) return true;
        return false;
    } // TestVictoireColonne ()
    
    bool TestVictoireLigne (const CVMatrice & Mat, const unsigned NumLi, const unsigned NumCol, const bool CoupDuJoueur1)
    {
        char Pion = (CoupDuJoueur1 ? Jeton1 : Jeton2);

		const unsigned KNbPoss (NumCol < Mat.size () /2  ?  NumCol +1 : Mat.size () - NumCol);

		const int KPosDeb = max (0, int(NumCol - Mat.size () /2));

		for (unsigned NbInspections (0);  NbInspections < KNbPoss; ++NbInspections)
		{
			unsigned NbCorrespondances = 0;
			for (unsigned Pos (KPosDeb + NbInspections) ; (Pos < Mat.size ()) &&  (Pion == Mat [NumLi][Pos]) ; ++Pos)
			    ++ NbCorrespondances;

			if (4 == NbCorrespondances) return true;
		}
		return false;
    } // TestVictoireligne ()
    
    bool TestVictoireDiagonale (const CVMatrice & Mat, const unsigned NumLi, const unsigned NumCol, const bool CoupDuJoueur1)
    {
        char Pion = (CoupDuJoueur1 ? Jeton1 : Jeton2);
        const unsigned KNbPoss (NumCol < Mat.size () /2  ?  NumCol + 1 : Mat.size () - NumCol);
        /* Diagonale Sud-Ouest Nord-Est*/
        const int KPosDebCol1 = max (0, int(NumLi > Mat.size() / 2 ? NumCol - (Mat.size() - 1 - NumLi) : NumCol - Mat.size() / 2));
        const int KPosDebLi1 = min (6, int(NumLi > Mat.size() / 2 ? NumLi + (Mat.size() - 1 - NumLi) : NumLi + Mat.size() / 2));

        for (unsigned NbInspections (0);  NbInspections < KNbPoss; ++NbInspections)
		{
			unsigned NbCorrespondances = 0;
			for (unsigned PosCol (KPosDebCol1 + NbInspections), PosLi (KPosDebLi1 - NbInspections) ; 
				 (PosCol < Mat.size ()) && (PosLi < Mat.size()) &&  (Pion == Mat [PosLi][PosCol]) ; 
				 ++PosCol, --PosLi)

			    ++ NbCorrespondances;

			if (4 == NbCorrespondances) return true;
		}
        /* Diagonale Nord-Ouest Sud-Est */
        const int KPosDebCol2 = min (6, int(NumLi > Mat.size() / 2 ? NumCol + (Mat.size() - 1 - NumLi) : NumCol + Mat.size() / 2));
        const int KPosDebLi2 = min (6, int(NumLi > Mat.size() / 2 ? NumLi + (Mat.size() - 1 - NumLi) : NumLi + Mat.size() / 2));
        
	    for (unsigned NbInspections (0);  NbInspections < KNbPoss; ++NbInspections)
	    {
		    unsigned NbCorrespondances = 0;
		    for (unsigned PosCol (KPosDebCol2 - NbInspections), PosLi (KPosDebLi2 - NbInspections) ; 
		    	 (PosCol < Mat.size()) && (PosLi < Mat.size()) &&  (Pion == Mat [PosLi][PosCol]) ;
		    	   --PosLi, --PosCol)

		            ++ NbCorrespondances;


		    if (4 == NbCorrespondances) return true;
		}
		return false;
        
        
    } // TestVictoireDiagonale ()
        bool Victoire (const CVMatrice & Mat, const unsigned NumLi, const unsigned NumCol, const bool CoupDuJoueur1 )
    {
    		return (TestVictoireDiagonale (Mat, NumLi, NumCol, CoupDuJoueur1) ||
    		TestVictoireLigne (Mat, NumLi, NumCol, CoupDuJoueur1) ||
    		TestVictoireColonne (Mat, NumLi, NumCol, CoupDuJoueur1));
    }// Victoire ()
    
/**************************************************************************/

/*********************************MODE DE JEU ******************************/

    void JeuNormal ()
    /*L'utilisateur choisit le nombre de manche(s) à gagner afin qu'un vainqueur soit prononcé, 
    	chaque ligne/colonne/diagonale gagnante rappporte 1 point et réinitialise le jeu*/
    {
    	unsigned NbManche (13);
    	while (NbManche > 10 || NbManche < 0)
    	{
	    	cout << "Saisir le nombre de partie(s) gagnante(s) nécessaire(s) (Max : 9) : "; 
	    	char NbManchechar;
	        string Buffer;
	        cin >> Buffer;
	        cin.ignore();
	    	NbManchechar = Buffer[0];
	        NbManche = NbManchechar - '0';
    	}
        CVLigne Li (7, '.');
        CVMatrice Mat (7, Li);
        InitMat (Mat);
        ClearScreen();
        AffichePuissance4 (Mat);
        char LettreCol;
        unsigned NumCol;
        unsigned NumLi;
        bool CoupDuJoueur1 = true;
        unsigned i;
        unsigned CptVicJ1 (0), CptVicJ2 (0); 
        for (;;)
        {
	        for (i = 0; i < 50 ; ++i)
	        {   
	            if (i == 49)
                {
                    ClearScreen();
                    InitMat(Mat);
                    AffichePuissance4(Mat);
                    cout << "Match nul" << endl;
                    i = 0;
                }
	            for (;;)
	            {
	                for (;;)
	                {
	                	if (CoupDuJoueur1)
	                	{
	                		Couleur (KRouge);
	                    	cout << NJoueur1 ;
	                    	Couleur (KReset);
	                    }
	                    else 
	                    {
	                    	Couleur (KBleu);
	                    	cout << NJoueur2;
	                    	Couleur (KReset);
	                    }
	                    cout  << ": Choisissez la position (entre A et G) du pion à placer : ";
	                    string Buffer;
	                    getline (cin, Buffer);
	                    LettreCol = Buffer[0];
	                    LettreCol = toupper (LettreCol);
	                    if ( LettreCol < 'A' || LettreCol > 'G') continue;
	                    NumCol = LettreCol - 'A';
	                    break;
	                }                
	                if (PositionneJeton (Mat, NumCol, NumLi, CoupDuJoueur1)) break;
	            }
	            ClearScreen();
                AffichePuissance4 (Mat);
                if    (Victoire ( Mat, NumLi, NumCol, CoupDuJoueur1))
                {
                    ClearScreen();
        			if (CoupDuJoueur1)
        			{
        				CptVicJ1 += 1;
        				cout << "Victoire de " << NJoueur1 << endl;
        			}
        			else
        			{
        				CptVicJ2 += 1;
        				cout << "Victoire de " << NJoueur2 << endl;
        			}
        			InitMat(Mat);
                    AffichePuissance4(Mat);
                    
                }
                
                Couleur (KCyan);
                cout << setw (4) << NJoueur1 << ':' << CptVicJ1 << setw(16) << NJoueur2 << ':' << CptVicJ2 << endl << endl ;
                Couleur (KReset);
                CoupDuJoueur1 = !CoupDuJoueur1;
                
                if (NbManche == CptVicJ1 || NbManche == CptVicJ2)
                {
                	if (NbManche == CptVicJ1)
                	{
                				Couleur (KRouge);
                        		cout<< NJoueur1 << " remporte cette partie en " << NbManche << " manche(s). " << endl;
                        		break;
                        		Couleur (KReset);
                    }
                	else
                	{ 
                			Couleur (KBleu);
                			cout<< NJoueur2 << " remporte cette partie en " << NbManche << " manche(s). "<<  endl;
                			break;
                			Couleur (KReset);
                	}
                }
            }
            Couleur (KJaune);
            cout << "Résultat stocké dans Historique.txt" << endl;
            Couleur (KReset);
            ofstream os ("Historique.txt", ios::app);
            if (i == 49 )
            {
                cout << "Match nul"  << endl;
                os << "Match nul entre les joueurs " << NJoueur1 << " et " << NJoueur2;
            }
            else if (NbManche == CptVicJ1)
            {
                
                os << NJoueur1 << " a gagné contre " << NJoueur2 << ".\n";
                
                
            }
            else
            {
                os << NJoueur2 << " a gagné contre " << NJoueur1<<  ".\n";
            }
            cout << "Appuyez sur entrée pour retourner dans le menu...";
            cin.get();
            break;
        }
    } // JeuNormal ()
    
    
    

/**************************************************************************/   
/************************MENU**********************************************/


void Parametres (char & Jeton1, char & Jeton2, string & NJoueur1, string & NJoueur2, char & ChoixParam)
   {
   		Couleur (KCyan);
   		cout 	<< setw (4) << "1) Nom Joueur" << endl; 
   		Couleur (KVert);
   		cout	<< setw(4) << "2) Jeton" << endl;
   		Couleur (KRouge); 
   		cout << setw(4) << "3) Revenir au menu" << endl ;
   		Couleur (KReset);
   		cout << "Que voulez-vous faire ?\n Saisie : ";		
   		string Buffer;
   		getline (cin, Buffer);
   		ChoixParam = Buffer[0];
   		if (ChoixParam == '1')//Changer Pseudo
   		{
   			ClearScreen();
   			SaisirNJoueur (NJoueur1, NJoueur2);	
   		}
   		if (ChoixParam == '2')//Changer Jeton
   		{
   			ClearScreen();
   			SaisieJeton(Jeton1, Jeton2, NJoueur1, NJoueur2);
   		}
   		if (ChoixParam == '3')// Retour Menu
   		{
   			ClearScreen();
   		}
		// Choix des paramètres que l'on veut modifier

   	} //Menu des paramètres 

	void Menu ()
	{
		for (;;)
		{
			ClearScreen();
			Couleur (KRouge);
			cout <<endl << setw (12)<<  " ____        _                                _  _   "<<
    				endl << setw (12)<< "|  _ \\ _   _(_)___ ___  __ _ _ __   ___ ___  | || |  "<<
					endl << setw (12)<< "| |_) | | | | / __/ __|/ _` |  _ \\ / __/ _ \\ | || |_ "<<
					endl << setw (12)<< "|  __/| |_| | \\__ \\__ \\ (_| | | | | (_|  __/ |__   _|"<<
					endl << setw (12)<< "|_|    \\__,_|_|___/___/\\__,_|_| |_|\\___\\___|    |_|  "<<
					  endl<< endl ;
			Couleur (KJaune);
			cout << setw (3) << "1) Jouer" << endl ;
			Couleur (KCyan);
			cout << setw (3) << "2) Préfèrences" << endl ;
			Couleur (KVert);
            cout << setw (3) << "3) Historique" << endl; 
			Couleur (KMagenta);
			cout << setw (3) << "4) Quitter" << endl;
			Couleur (KReset);
			cout << "Que voulez-vous faire ?\n Saisie : ";					
			string Buffer;
			char Choix;
			getline (cin, Buffer);
			Choix=Buffer [0];
			if (Choix == '4') break;
            
            if (Choix == '3')
            {
                ifstream is ("Historique.txt");
                string Str;
                ClearScreen ();
                cout << "Historique des parties précédentes :" << endl;
                for (getline (is, Str); ! is.eof(); getline (is, Str))
                    cout << Str << endl;
                
                cout << "Appuyez sur entrée pour retourner dans le menu...";
                cin.get();
                
                        
    
            }
            
			if (Choix == '2')
			{
				ClearScreen();
				Parametres (Jeton1, Jeton2, NJoueur1,NJoueur2, ChoixParam);


			}
			if (Choix =='1')
			{
				ClearScreen ();
				JeuNormal ();// sélection dans menu principal

			}


		}
	} //Menu () 




/***************************************************************************/

} // namespace

int main ()
{
    Menu ();
    return 0;
} // int main()
