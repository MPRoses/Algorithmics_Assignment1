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

    // Loopt door naar eind op basis van zetten gemaakt door bepaalGoedeZet 
    // en meet vervolgens achteruit de berekeningstijd van besteScore;
    void doeExperiment ();

  private:
    // hulpfuncties voor leesInSpel
    bool leesPot(std::ifstream& fin);
    bool leesSchalenTegels(std::ifstream& fin);
    bool leesRijenVakjes(std::ifstream& fin);
    bool leesSpelers(std::ifstream& fin);
    bool leesBeurt(std::ifstream& fin);

    // bepaalt op basis van huidigePot de schalen
    bool bepaalTegels();

    // Update huidigePot en schalen na een zet
    void verwijderEnSchuifSchalen(int schaal, char kleur);

    // voldoet gegeven zet aan de zeteisen?
    bool zetEisen(int schaal, char kleur, int aantal);
    // kijkt of er voor meegegeven waarden een valide zet is
    bool valideZetten(int schaal, char kleur, int aantal, std::vector<std::vector<int>>* spelerRijen);

    // Telt aantal volle rijen en berekend score
    int berekenScore(vector<vector<int>>* spelerRijen);

    // startvariabelen
    string huidigePot = "";
    int aantalSchalen;
    int maximumAantalTegels;
    int aantalRijenOpBord;
    int aantalVakjesPerRij;
    // welke speler is aan zet
    int huidigeBeurt;
    int actieveKleur = 0;

    // houdt mogelijke zetten bij
    int mogelijkeZetten[20];
    int aantalGelijkeOpties = 0;

    // data voor rijen spelers en de schalen 
    std::vector<std::vector<char>> schalen;
    std::vector<std::vector<int>> speler1;
    std::vector<std::vector<int>> speler2;

    // stack voor bijhouden zetten
    stack<spelState> spelGeschiedenis;

};

#endif