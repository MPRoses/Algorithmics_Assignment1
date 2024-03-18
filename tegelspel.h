// Definitie van klasse TegelSpel

#ifndef TegelSpelHVar  // voorkom dat dit bestand meerdere keren
#define TegelSpelHVar  // ge-include wordt

#include <vector>
#include <string>
#include <stack>
#include "constantes.h"
using namespace std;

// stack voor bijhouden van zetten 
struct spelState {
  string huidigePot;
  vector<vector<int>> speler1;
  vector<vector<int>> speler2;
  int huidigeBeurt;
};


class TegelSpel { 
  public:
    //default constructor
    TegelSpel ();

    // Retourneerd het aantal schalen
    int getSchalen ();

    // Retourneerd de inhoud van de pot
    string getPot ();

    // Retourneerd vector,[schaal][Paar[aantalG, anatalB]]
    vector< pair <int,int> > getInhoudSchalen ();

    // Retourneerd vector,[schaal][Paar[aantalG, anatalB]] voor speler x
    vector< pair <int,int> > getInhoudRijen (int speler);

    // Leest file en checkt of het voldoet aan de speleisen
    bool leesInSpel (const char* invoernaam);

    // Retourneerd true als een eindstand bereikt is
    bool eindstand ();

    // Druk de hele stand (pot, schalen met inhoud, rijen van de spelers met inhoud, speler-aan-beurt) af op het scherm.
    void drukAf ();

    // Retourneerd vector,Paar[int (schaal), char (kleur)]
    vector< pair<int,char> > bepaalVerschillendeZetten ();

    // Maakt op basis van gekozen schaal en kleur "best" mogelijke zet voor de huidige speler.
    bool doeZet (int schaal, char kleur);

    // Retourneerd true als er een zet is ongedaan anders false
    bool unDoeZet ();

    // Retourneerd eindscore voor huidige speler gegeven dat beide spelers optimaal doorspelen
    int besteScore (pair<int,char> &besteZet, long long &aantalStanden);

    // Retourneerd de gevonden beste zet(schaal, kleur) op basis van de methode Monte Carlo zolang het spel spel nog bezig is, anders zet(-1, '')
    pair<int,char> bepaalGoedeZet (int nrSimulaties);

    // Vergelijkt spelers die "goede" (= op basis van bepaalGoedeZet) en "beste" (= op basis van besteScore) zetten doen en retourneert de score van de huidige speler, ofwel "goede" speler
    int bepaalGoedeScore ();

    // werkt
    void doeExperiment ();

  private:
    // TODO: uw eigen private memberfuncties en -variabelen
    bool leesPot(std::ifstream& fin);
    bool leesSchalenTegels(std::ifstream& fin);
    bool leesRijenVakjes(std::ifstream& fin);
    bool leesSpelers(std::ifstream& fin);
    bool leesBeurt(std::ifstream& fin);
    void verwijderEnSchuifSchalen(int schaal, char kleur);
    bool bepaalTegels();
    bool zetEisen(int schaal, char kleur, int aantal);
    bool valideZetten(int schaal, char kleur, int aantal, std::vector<std::vector<int>>* spelerRijen);
    int berekenScore(vector<vector<int>>* spelerRijen);
    void initBord();

    string huidigePot = "";
    int aantalSchalen;
    int maximumAantalTegels;
    int aantalRijenOpBord;
    int aantalVakjesPerRij;
    int huidigeBeurt;

    int mogelijkeZetten[11];
    int aantalGelijkeOpties = 0;
    int actieveKleur = 0;
    std::vector<std::vector<char>> schalen;
    std::vector<std::vector<int>> speler1;
    std::vector<std::vector<int>> speler2;

    stack<spelState> spelGeschiedenis;

};

#endif

