/**
 *
 * @file   Puissance_4.cxx
 *
 * @author SCOUR Kilian Antoine MERINO Thomas BIANCHINI	
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

    void JeuNormal ()
    {
    	unsigned NbManche;
       	cout << "Saisir le nombre de manche(s) : ";
    	cin  >> NbManche ;
    	cin.ignore();
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
        for (i = 0; i < (NbManche * 49)*2 ; ++i)
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
            ClearScreen();
            AffichePuissance4 (Mat);
        	if    (Victoire ( Mat, NumLi, NumCol, CoupDuJoueur1))
        	{
        			if (CoupDuJoueur1)
        				CptVicJ1 += 1;
        			else 
        				CptVicJ2 += 1;
        			InitMat(Mat);
        			ClearScreen();
        			AffichePuissance4 (Mat);
        			
          	}
        	cout << setw (4) << NJoueur1 << ':' << CptVicJ1 << setw(16) << NJoueur2 << ':' << CptVicJ2 << endl << endl ;           
            CoupDuJoueur1 = !CoupDuJoueur1;

             if (NbManche == CptVicJ1) break;
            
        }
        if (i == (NbManche *49)*2 ) cout << "Match nul"  << endl;
        else if (NbManche == CptVicJ1) cout << "victoire de " << NJoueur1 << endl;
        else cout << "victoire de " << NJoueur2 << endl;
        cout << "Appuyez sur une entrée pour continuer...";
        cin.get();
    } // Jeu2Joueurs ()
    
    void EffacerColonneGagnante(CVMatrice & Mat, const unsigned NumLi, const unsigned NumCol)
    {
		
		for (unsigned i = NumLi; i < NumLi + 4; ++i)
		{
			
			if (NumLi <= Mat.size()-4)
				Mat[i][NumCol] = '.';
			else 
				Mat[i][NumCol] = Mat[i-4][NumCol];
			
		}
		
	}// EffacerColonneGagnante
    
    void JeuArcade () /* A TERMINER */
    /* Chacun commence avec 50 jetons. Lorsque qu'un joueur remplit une
     * ligne/colonne/diagonale, il gagne 1 point. et les jetons gagnants
     * sont effacés (ceux du dessus les remplacent). Si la grille est
     * saturée, la ligne du bas est effacée. Le joueur ayant le plus de 
     * points à la fin des stocks remporte la manche.
    */
    {
        CVLigne Li (7, '.');
        CVMatrice Mat (7, Li);
        InitMat (Mat);
        unsigned NombreDeJetons (100);
        char LettreCol;
        unsigned NumCol;
        unsigned NumLi;
        bool CoupDuJoueur1 = true;

		int ScoreJoueur1 (0);
		int ScoreJoueur2 (0);
        
        for (; NombreDeJetons > 0 ; --NombreDeJetons)
        {   

            ClearScreen();
            cout << "Nombre de jetons restants : " << NombreDeJetons / 2 << endl << endl; /* la moitié chacun */ 
            AffichePuissance4 (Mat);
            for (;;)
            {
				cout << endl << NJoueur1 << " : " << ScoreJoueur1 << '\t' << NJoueur2 << " : " << ScoreJoueur2 << endl << endl;
                    
				// Placement du jeton
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
            
           if (TestVictoireColonne (Mat, NumLi,NumCol, CoupDuJoueur1))
		   {
			if ((Mat[NumLi][NumCol] == Jeton1)) ScoreJoueur1++; else ScoreJoueur2++;
			EffacerColonneGagnante(Mat, NumLi,NumCol);
		   }
		   else if (TestVictoireLigne (Mat, NumLi,NumCol, CoupDuJoueur1))
		   {
			if (CoupDuJoueur1) ScoreJoueur1++; else ScoreJoueur2++;
		   }
		   else if (TestVictoireDiagonale (Mat, NumLi,NumCol, CoupDuJoueur1))
		   {
			if (CoupDuJoueur1) ScoreJoueur1++; else ScoreJoueur2++;
		   }
            CoupDuJoueur1 = !CoupDuJoueur1;
        }
        
    } // JeuArcade ()

/**************************************************************************/   
/************************MENU**********************************************/
void ParametreJeu ()
{
	cout << setw (4)<< "1) Jeu Normal" << endl;
	cout << setw(4) << "2) Jeu Arcade" << endl;
	cout << setw(4) << "3) Retour au menu " << endl;
	cout << "Que voulez-vous faire ?\n Saise : ";
	
	char ChoixJeu; 
	string Buffer;
	getline (cin, Buffer);
	ChoixJeu = Buffer [0];
	
	if (ChoixJeu == '3' )
		ClearScreen();
	if (ChoixJeu == '2')
	{
		ClearScreen ();
		//JeuArcade ();		
	}
	if (ChoixJeu == '1')
	{
		ClearScreen();
		JeuNormal ();
    } 
}// Menu dans Jeu

void Parametres (char & Jeton1, char & Jeton2, string & NJoueur1, string & NJoueur2, char & ChoixParam)
   {
   		Couleur (KCyan);
   		cout 	<< setw (4) << "1) Nom Joueur" << endl; 
   		Couleur (KVert);
   		cout	<< setw(4) << "2) Jeton" << endl;
   		Couleur (KRouge); 
   		cout << setw(4) << "3) Revenir au menu" << endl ;
   		Couleur (KReset);
   		cout << "Que voulez-vous faire ?\n Saise : ";		
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
			cout <<endl <<  " ____        _                                _  _   "<<
					endl << "|  _ \\ _   _(_)___ ___  __ _ _ __   ___ ___  | || |  "<<
					endl << "| |_) | | | | / __/ __|/ _` | _ \\ / __/ _ \\ | || |_ "<<
					endl << "|  __/| |_| | \\__ \\__ \\ (_| | | | | (_|  __/ |__   _|"<<
					endl << "|_|    \\__,_|_|___/___/\\__,_|_| |_|\\___\\___|    |_|  "<<
					  endl<< endl ;
			Couleur (KJaune);
			cout << setw (3) << "1) Jouer" << endl ;
			Couleur (KCyan);
			cout << setw (3) << "2) Préfèrences" << endl ;
			Couleur (KMagenta);
			cout << setw (3) << "3) Quitter" << endl;
			Couleur (KReset);
			cout << "Que voulez-vous faire ?\n Saise : ";					
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
				ParametreJeu ();// sélection dans menu principal
					
		}
	} //Menu () 

	


/***************************************************************************/

} // namespace

int main ()
{
    Menu ();
    return 0;
} // int main()
