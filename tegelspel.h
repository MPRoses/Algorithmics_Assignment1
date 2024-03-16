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
    // Retourneerd het aantal schalen van het huidige spel
    int getSchalen ();
    // Retourneerd de inhoud van de pot
    string getPot ();

    // Retourneerd vector,[schaal][Paar[aantalG, anatalB]]
    vector< pair <int,int> > getInhoudSchalen ();

    // Getter voor inhoud rijen van een speler
    // Retourneer:
    // * een vector met voor elke rij (in een of andere volgorde) van speler
    //   `speler' een tweetal (aantalG,aantalB): het aantal gele,
    //   respectievelijk blauwe tegels in die rij
    vector< pair <int,int> > getInhoudRijen (int speler);

    // Lees een spel in vanuit tekstbestand invoernaam, mogelijk al (deels)
    // gevuld met tegels.
    // Controleer daarbij
    // * of het bestand wel te openen is,
    // * of de pot wel allemaal tegels (letters) 'g' en 'b' bevat
    // * of de parameters M, N, K en L uit de opdracht binnen
    //   de grenzen van de opdracht vallen
    // * of de inhoud van elke rij van de spelers klopt met de regels van
    //   het spel:
    //   - OF 0 tegels, OF alleen gele tegels OF alleen blauwe tegels
    //   - het aantal tegels in de rij past ook echt in de rij (is <= L)
    // Retourneer:
    // * true, als aan alle voorwaarden is voldaan
    // * false, als niet aan alle voorwaarden is voldaan
    // Post:
    // * Als aan alle voorwaarden is voldaan, is het spel met de tegels
    //   opgeslagen in membervariabelen, en staat speler-aan-beurt goed.
    bool leesInSpel (const char* invoernaam);

    // Controleer of we een eindstand hebben bereikt, dat wil zeggen:
    // of een speler alle rijen vol heeft, of dat er geen enkele geldige zet
    // is voor de speler die aan de beurt is.
    // Retourneer:
    // * true, als we een eindstand hebben bereikt
    // * false, als we geen eindstand hebben bereikt
    bool eindstand ();

    // Druk de hele stand (pot, schalen met inhoud, rijen van de spelers
    // met inhoud, speler-aan-beurt) af op het scherm.
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

    // Doe een zet voor de speler die aan de beurt is:
    // tegels kiezen van schaal `schaal' van kleur `kleur', en die in
    // de bijpassende rij leggen.
    // Controleer eerst of het wel een geldige zet is, dat wil zeggen,
    // - of het geen eindstand is
    // - of `schaal' een geldige nummer is voor de schaal
    // - of `kleur' een geldige kleur is, die ook voorkomt in schaal `schaal'
    // - of de speler aan beurt al deze tegels ook echt kwijt kan in een rij
    // Retourneer:
    // * true, als dit een geldige zet is
    // * false, als dit geen geldige zet is.
    // Post:
    // * als het een geldige zet is, is de zet uitgevoerd:
    //   - de tegels van de gekozen kleur zijn van de gekozen schaal
    //     verwijderd, en in de bijpassende rij van de speler aan beurt gelegd
    //   - de schaal is voor zover mogelijk aangevuld met tegels
    //     uit de pot
    //   - de speler aan beurt is gewisseld
    //   - de zet is toegevoegd aan de lijst met gedane zetten
    // * als het geen geldige zet is, is de stand niet veranderd.
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
    void bepaalTegels();

    string huidigePot = "";
    int aantalSchalen;
    int maximumAantalTegels;
    int aantalRijenOpBord;
    int aantalVakjesPerRij;
    int huidigeBeurt;

    // speler1, speler2 en schalen zijn vectors i.p.v. arrays
    // zodat er dan gedeclareerd kan worden met een 
    // niet constante waarde; ofwel met maximumAantalTegels, aantalSchalen en aantalRijenOpBord

    std::vector<std::vector<char>> schalen;
    std::vector<std::vector<int>> speler1;
    std::vector<std::vector<int>> speler2;


};

#endif

