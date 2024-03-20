// Hoofdprogramma voor oplossing voor eerste programmeeropdracht Algoritmiek,
// voorjaar 2024: TegelSpel
//
// Biedt de gebruiker een menustructuur om
// * het spel te spelen
//   - vanaf een in te lezen, en mogelijk (deels) gevulde stand
//   waarbij de gebruiker steeds
//   - de verschillende zetten voor de huidige speler kan bepalen
//   - een zet kan uitvoeren (tegels van een schaal kiezen en laten neerleggen)
//   - de laatste zet ongedaan kan maken
//   - kan vragen om de score voor de speler die aan de beurt is, als beide
//     spelers vanaf dit moment optimaal verder spelen
//   - kan vragen om een `goede zet' voor de speler die aan de beurt is
//   - kan vragen om de eindscore voor de speler die aan de beurt is,
//     als hij vanaf nu een `goede zet' doet, terwijl de andere speler
//     steeds een beste zet doet
//   - een experiment kan doen met de tijd van besteScore
//
// Namen studenten, datum

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "tegelspel.h"
using namespace std;
const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

// Schrijf het menu op het scherm en vraag een keuze van de gebruiker.
// Retourneer: de keuze van de gebruiker
int keuzeUitMenu ()
{ int keuze;

  cout << endl;
  cout << "1. Verschillende zetten voor huidige speler bepalen" << endl;
  cout << "2. Een zet uitvoeren" << endl;
  cout << "3. Laatste zet ongedaan maken" << endl;
  cout << "4. Beste score (met beste zet) bepalen" << endl;
  cout << "5. Een goede zet bepalen" << endl;
  cout << "6. Score goed tegen best bepalen" << endl;
  cout << "7. Experiment doen met tijd besteScore" << endl;
  cout << "8. Stoppen met dit spel" << endl;
  cout << endl;
  cout << "Maak een keuze: ";
  cin >> keuze;

  return keuze;

}  // keuzeUitMenu

//*************************************************************************

// Roep s1->besteScore aan, meet de benodigde tijd, en zet de relevante
// data op het scherm.
void roepBesteScoreAan (TegelSpel *s1) { 
  pair<int,char> besteZet;
  long long aantalStanden = 0;  // aantal bekeken standen bij aanroep besteScore

  clock_t start = clock();
  int score = s1 -> besteScore(besteZet, aantalStanden);
  clock_t eind = clock();

  double duration = static_cast<double>(eind - start) / CLOCKS_PER_SEC;

  cout << endl;
  cout << "Beste score is: " << score << endl;
  cout << "Een beste zet is: (" << besteZet.first << "," << besteZet.second
<< ")" << endl;
  cout << "We hebben hiervoor " << aantalStanden
       << " standen bekeken." << endl;
  cout << "Dit kostte " << (eind-start) << " clock ticks, ofwel "
       << duration << " seconden." << endl;

}  // roepBesteScoreAan

//*************************************************************************

// Speel het spel aangewezen door pointer s1.
// Hierbij krijgt de gebruiker herhaaldelijk de keuze om
// * de verschillende zetten voor de huidige speler te bepalen
// * een zet uit te voeren (tegels van een schaal kiezen en laten neerleggen)
// * de laatste zet ongedaan te maken
// * te vragen om de eindscore voor de speler die aan de beurt is, als beide
//   spelers vanaf dit moment optimaal verder spelen
// * te vragen om een `goede zet' voor de speler die aan de beurt is
// * te vragen om de eindscore voor de speler die aan de beurt is,
//   als hij vanaf nu een `goede zet' doet, terwijl de andere speler
//   steeds een beste zet doet
// * een experiment te doen met tijd voor aanroep besteScore
//
// Voor elke iteratie van het menu wordt de stand afgedrukt.
//
// Dit alles gaat door, totdat de gebruiker aangeeft dat hij wil stoppen
// met het spel
void doeSpel (TegelSpel *s1)
{ int aantalZetten, // aantal mogelijke zetten
      schalen,
      keuze,
      schaal,
      score;
  char kleur;
  pair<int,char> zet;
  vector < pair <int,char> > zetten;  // de mogelijke zetten
  long long aantalStanden;  // aantal bekeken standen bij aanroep besteScore

  schalen = s1->getSchalen();

  keuze = 0;
  while (keuze!=8)
  {
    s1 -> drukAf ();

    keuze = keuzeUitMenu ();

    switch (keuze)
    { case 1: cout << endl;
              zetten = s1->bepaalVerschillendeZetten ();
              aantalZetten = zetten.size ();
              cout << "Mogelijke zetten:";
              for (int i=0;i<aantalZetten;i++)
                cout << " ("
                   << zetten[i].first << "," << zetten[i].second << ")";
              cout << endl;
              break;
      case 2: cout << endl;
              cout << "Geef het nummer van de schaal (0.." << schalen-1 << "): ";
              cin >> schaal;
              cout << "Geef de kleur van de tegels (g,b): ";
              cin >> kleur;
              if (!(s1->doeZet (schaal, kleur)))
              { cout << endl;
                cout << "Er is geen zet gedaan." << endl;
              }
              break;
      case 3: if (!(s1->unDoeZet ()))
              { cout << endl;
                cout << "Er is geen zet ongedaan gemaakt." << endl;
              }
              break;
      case 4: roepBesteScoreAan (s1);
              break;
      case 5: zet = s1 -> bepaalGoedeZet (NrSimulaties);
              cout << endl;
              cout << "Een goede zet is: (" << zet.first << ","
                   << zet.second << ")" << endl;
              break;
      case 6: score = s1 -> bepaalGoedeScore ();
              cout << endl;
              cout << "Score goed tegen best is: " << score << endl;
              break;
      case 7: s1 -> doeExperiment ();
              break;
      case 8: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

  if (s1->eindstand())
  { s1 -> drukAf ();
    cout << endl;
    cout << "De huidige stand is een eindstand.\n";
    cout << "De score voor de speler die aan de beurt zou zijn is: "
         << s1->besteScore (zet, aantalStanden) << endl;
  }

}  // doeSpel

//*************************************************************************

void hoofdmenu ()
{ TegelSpel *s1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
                      // en weer weg te gooien
  int keuze;
  char invoernaam[MaxBestandsNaamLengte+1];

  do
  {
    cout << endl;
    cout << "1. Een spel inlezen" << endl;
    cout << "2. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1: s1 = new TegelSpel ();
//              s1 -> drukAf ();  // er is nog geen geldig spel,
//                                // niet crashen...
              cout << "Geef de naam van het tekstbestand met het spel (E.g. spel.txt)): ";
              cin >> invoernaam;
              if (s1 -> leesInSpel (invoernaam))
                doeSpel (s1);
              delete s1;  // netjes opruimen
              break;
      case 2: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=2);

}  // hoofdmenu

//*************************************************************************
  
int main ()
{
  hoofdmenu ();

  return 0;

}
