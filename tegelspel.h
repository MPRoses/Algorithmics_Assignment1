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

    // Bepaal met behulp van brute force en recursie de eindscore voor
    // de speler die in de huidige stand (= de stand van de huidige
    // recursieve aanroep) aan de beurt is, wanneer beide spelers vanaf
    // dit punt optimaal verder spelen.
    // De score is gelijk aan het aantal volle rijen van de speler min
    // het aantal volle rijen van de andere speler.
    // Post:
    // * als de huidige stand geen eindstand was, bevat parameter
    //   besteZet een paar (schaal,kleur) dat de huidige speler
    //   in de eerstvolgende zet moet kiezen, om de beste score te bereiken
    // * anders bevat parameter besteZet een passende default waarde
    // * aantalStanden is gelijk aan het aantal standen dat we hebben
    //   bekeken bij het bepalen van de beste eindscore
    // * de stand in het spel is nog onveranderd
    int besteScore (pair<int,char> &besteZet, long long &aantalStanden);

    // Retourneerd de gevonden zet(rij, kolom) zolang het spel spel nog bezig is, anders zet(-1, '')
    pair<int,char> bepaalGoedeZet (int nrSimulaties);

    // Speel het spel uit vanaf de huidige stand. Laat hierbij de speler
    // die in de huidige stand aan de beurt is, steeds een `goede zet'
    // (gevonden met bepaalGoedeZet) doen, terwijl de andere speler steeds
    // een beste zet (gevonden met besteScore) doet.
    // Retourneer:
    // * de score aan het eind van het spel voor de speler die steeds
    //   een `goede zet' gedaan heeft
    // Post:
    // * de huidige stand is weer hetzelfde als aan het begin van de functie
    //   (zetten zijn dus weer ongedaan gemaakt)
    int bepaalGoedeScore ();

    // Doe het experiment met de tijd van besteScore:
    // * speel het spel uit vanaf de huidige stand met goedeZetten
    // * maak vanaf die eindstand steeds een zet extra ongedaan, en kijk
    //   hoe lang een aanroep van besteScore dan duurt
    // * totdat de eerste goedeZet die in deze functie gedaan is, ook
    //   ongedaan is gemaakt, of het wachten op de uitkomst van besteScore
    //   te lang duurt
    // Post:
    // * de huidige stand is weer hetzelfde als aan het begin van de functie
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

