// Definitie van klasse TegelSpel

#ifndef TegelSpelHVar  // voorkom dat dit bestand meerdere keren
#define TegelSpelHVar  // ge-include wordt

#include <vector>
#include <string>
#include "constantes.h"
using namespace std;

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

    // retourneerd true als een eindstand bereikt is
    bool eindstand ();

    // Druk de hele stand (pot, schalen met inhoud, rijen van de spelers met inhoud, speler-aan-beurt) af op het scherm.
    void drukAf ();

    // Bepaal alle verschillende, geldige zetten (schaal,kleur) in de huidige
    // stand. Twee zetten zijn verschillend als
    // * ze schalen betreffen met verschillende inhoud (qua aantal gele tegels
    //   en aantal blauwe tegels)
    // * of verschillende kleuren betreffen
    // (of beide).
    // Een zet met een kleur die niet voorkomt op de schaal is niet geldig.
    // Een zet met een kleur die vaker voorkomt op de schaal dan de speler
    // in een rij kwijt kan, is niet geldig.
    // Retourneer:
    // * Een vector met alle verschillende geldige zetten (schaal,kleur);
    //   de volgorde van de zetten maakt niet uit.
    vector< pair<int,char> > bepaalVerschillendeZetten ();

    // Maakt op basis van gekozen schaal, kleur en huidige speler
    // de best mogelijke zet.
    bool doeZet (int schaal, char kleur);

    // Maak de laatst gedane zet ongedaan.
    // Controleer eerst of er wel een zet is om ongedaan te maken,
    // opgeslagen in de lijst met zetten.
    // Retourneer:
    // * true, als er een zet was om ongedaan te maken
    // * false, anders
    // Post:
    // * als returnwaarde true is, is de zet ongedaan gemaakt:
    //   - de speler aan beurt is teruggewisseld,
    //   - tegels zijn terug van schaal naar pot
    //   - uit schaal gehaalde tegels zijn terug van rij naar schaal
    //   - de zet is van de lijst met uitgevoerde zetten gehaald
    // * als returnwaarde false is, is de stand niet veranderd
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

    // Bepaal een `goede zet' voor de speler die in de huidige stand aan
    // aan de beurt is: een zet die ertoe leidt dat hij (na deze ene zet)
    // met nrSimulaties keer random uitspelen een zo hoog mogelijke
    // gemiddelde score haalt.
    // Controleer eerst of de huidige stand geen eindstand is.
    // Retourneer:
    // * de gevonden zet (rij,kolom), als het geen eindstand is
    // * een passende default waarde, als het al wel een eindstand is
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

};

#endif

