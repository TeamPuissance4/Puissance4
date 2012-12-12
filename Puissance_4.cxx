/**
 *
 * @file   Puissance_4.cxx
 *
 * @author SCOUR Kilian <-- Trololol COUCOUCOUCOU
 *
 * @date   6/12/2012
 *
 * @brief  Puissance 4
 *
**/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


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
 /**************************PARAMETRES JOUEURS *********************/
    void SaisieJeton (char & Jeton1, char & Jeton2, string & NJoueur1, string & NJoueur2)
    {
        cout << "Saisissez le jeton de " << NJoueur1 << " (Caractère éditable) :";
        string Buffer;
        getline(cin, Buffer);
        Jeton1 = Buffer[0];
        cout << endl;
        for (;;)
        {
            cout << "Saisissez le jeton de " << NJoueur2 << " (Caractère éditable) : ";
            string Buffer;
            getline(cin, Buffer);
            Jeton2 = Buffer[0];
            if (Jeton2 != Jeton1) break;
            cerr << "Choisissez un jeton différent de " << NJoueur1 << "." << endl;
        }
        Jeton1 = 'X';
        Jeton2 = 'O';
    } // SaisieJeton ()
    
      void SaisirNJoueur (string & NJoueur1, string & NJoueur2)
    {
            cout << "Nom du joueur 1 : "; 
            getline(cin, NJoueur1);
            for (;;)
            {
                cout << "Nom du joueur 2 : ";
                getline(cin, NJoueur2);
                if (NJoueur2 != NJoueur1) break;
                cerr << "Choisissez un pseudo différent de " << NJoueur1 << "!" << endl;
            }
            
    }// SaisirNJoueur   
    
        void Couleur (const string & coul)
    {
        cout << "\033[" << coul.c_str () <<"m";
    }// Couleur ()
    
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
        ClearScreen ();
        Couleur (KReset);
        for (unsigned i (0); i < Mat.size(); ++i)
        {
            AfficheLigne (Mat[i]);
        }
    } // AficheMatrice ()
    
    void AffichePuissance4 (const CVMatrice & Mat)
    {
        AfficheMatrice (Mat);
        CVLigne Tirets (21, '-');
        for (unsigned i (0); i < Tirets.size(); ++i)
        {
            cout << Tirets[i];
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
    

    
    void PositionneJeton (CVMatrice & Mat, const unsigned NumCol, unsigned & NumLi, const bool CoupDuJoueur1)
    {
        char Pion (CoupDuJoueur1 ? Jeton1 : Jeton2);
        for (NumLi = 6; NumLi != 0; --NumLi)
        {
            if (Mat[NumLi][NumCol] == '.') break;
        }
        if (NumLi >= 0 && Mat[NumLi][NumCol] == '.')
        {
            Mat[NumLi][NumCol] = Pion;
        }
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
	    const int KPosDebCol1 = max (0, int(NumLi > Mat.size() / 2 ? NumCol - (Mat.size() - 1 - NumLi) : NumCol - Mat.size() / 2));
        const int KPosDebLi1 = min (6, int(NumLi > Mat.size() / 2 ? NumLi + (Mat.size() - 1 - NumLi) : NumLi + Mat.size() / 2));
        const int KPosDebCol2 = min (6, int(NumLi > Mat.size() / 2 ? NumCol + (Mat.size() - 1 - NumLi) : NumCol + Mat.size() / 2));
        const int KPosDebLi2 = min (6, int(NumLi > Mat.size() / 2 ? NumLi + (Mat.size() - 1 - NumLi) : NumLi + Mat.size() / 2));
	    
        for (unsigned NbInspections (0);  NbInspections < KNbPoss; ++NbInspections)
		{
			unsigned NbCorrespondances = 0;
			for (unsigned PosCol (KPosDebCol1 + NbInspections), PosLi (KPosDebLi1 - NbInspections) ; (PosCol < Mat.size ()) && (PosLi < Mat.size()) &&  (Pion == Mat [PosLi][PosCol]) ; ++PosCol, --PosLi)
			    ++ NbCorrespondances;

			if (4 == NbCorrespondances) return true;
		}
		
	    for (unsigned NbInspections (0);  NbInspections < KNbPoss; ++NbInspections)
	    {
		    unsigned NbCorrespondances = 0;
		    for (unsigned PosCol (KPosDebCol2 - NbInspections), PosLi (KPosDebLi2 - NbInspections) ; (PosCol < Mat.size()) && (PosLi < Mat.size()) &&  (Pion == Mat [PosLi][PosCol]) ; --PosLi, --PosCol)
		            ++ NbCorrespondances;

		    if (4 == NbCorrespondances) return true;
		}
		return false;
        
        
    } // TestVictoireDiagonale ()
    
    bool Victoire (const CVMatrice & Mat, const unsigned NumLi, const unsigned NumCol, const bool CoupDuJoueur1)
    {
    		return (TestVictoireDiagonale (Mat, NumLi, NumCol, CoupDuJoueur1) ||
    		TestVictoireLigne (Mat, NumLi, NumCol, CoupDuJoueur1) ||
    		TestVictoireColonne (Mat, NumLi, NumCol, CoupDuJoueur1)) ;
    }// Victoire ()
    
/**************************************************************************/
    
/*********************************MODE DE JEU ******************************/

    int Jeu2Joueurs ()
    {
        CVLigne Li (7, '.');
        CVMatrice Mat (7, Li);
        InitMat (Mat);
        AffichePuissance4 (Mat);
        char LettreCol;
        unsigned NumCol;
        unsigned NumLi;
        bool CoupDuJoueur1 = true;
        unsigned i;
        
        for (i = 0; i < 49 ; ++i)
        {   
            
            for (;;)
            {
                for (;;)
                {
                    cout << (CoupDuJoueur1 ? NJoueur1 : NJoueur2) << ": Choisissez la position (entre A et G) du pion à placer : ";
                    string Buffer;
                    getline (cin, Buffer);
                    LettreCol = Buffer[0];
                    LettreCol = toupper (LettreCol);
                    if ( LettreCol < 'A' || LettreCol > 'G') continue;
                    NumCol = LettreCol - 'A';
                    break;
                }                
                PositionneJeton (Mat, NumCol, NumLi, CoupDuJoueur1);
                if (Mat[NumLi][NumCol] == (CoupDuJoueur1 ? Jeton1 : Jeton2)) break;
            }
            AffichePuissance4 (Mat);
           if (Victoire (Mat, NumLi,NumCol, CoupDuJoueur1)) break;
            CoupDuJoueur1 = !CoupDuJoueur1;
        }
        if (i == 49) cout << "Match nul"  << endl;
        else if (CoupDuJoueur1) cout << "victoire de " << NJoueur1 << endl;
        else cout << "victoire de " << NJoueur2 << endl;
    } // Jeu2Joueurs ()

/**************************************************************************/   
/************************MENU**********************************************/

void Parametres (char & Jeton1, char & Jeton2, string & NJoueur1, string & NJoueur2, char & ChoixParam)
   {
   		cout 	<< setw (4) << "1) Nom Joueur" << endl 
   				<< setw(4) << "2) Jeton" << endl 
   				<< setw(4) << "3) Revenir au menu" << endl ;
   				
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
			Couleur (KRouge);
			cout <<endl <<  "PUISSANCE 4 " <<endl << endl ;
			Couleur (KJaune);
			cout << setw (3) << "1) Jouer" << endl ;
			Couleur (KCyan);
			cout << setw (3) << "2) Préfèrences" << endl ;
			Couleur (KMagenta);
			cout << setw (3) << "3) Quitter" << endl;
			Couleur (KReset);
								
			string Buffer;
			char Choix;
			getline (cin, Buffer);
			Choix=Buffer [0];
			if (Choix == '3') break;
			if (Choix == '2')
			{
				ClearScreen();
				Parametres (Jeton1, Jeton2, NJoueur1,NJoueur2, ChoixParam);
				
				
			}
			if (Choix =='1')
				Jeu2Joueurs();// sélection dans menu principal
					
		}
	} //Menu () 

	


/***************************************************************************/

} // namespace

int main ()
{
    Menu ();
    return 0;
} // int main()
