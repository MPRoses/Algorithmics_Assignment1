// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <iomanip>  // setw
#include <fstream>   // file lezen
#include <iostream>
#include <climits> // int_max en int_min
#include <ctime>

TegelSpel::TegelSpel(){} 

// Geeft het aantal schalen in het spel terug
int TegelSpel::getSchalen() {
  return aantalSchalen;
}//getSchalen

// Geeft de inhoud van de pot terug
string TegelSpel::getPot() { 
  return huidigePot;
}//getPot

// Geeft een vector terug met inhoud van alle schalen
// De vector bevat paren van ints, waar de eerste het aantal gele
// en de tweede het aantal blauwe tegels in de schaal voorstelt
std::vector<std::pair<int, int>> TegelSpel::getInhoudSchalen() {
  std::vector<std::pair<int, int>> inhoudSchalen(aantalSchalen);

  for (int i = 0; i < aantalSchalen; i++) {
    int aantalG = 0;
    int aantalB = 0;
    for (char c : schalen[i]) {
      if (c == 'g') {
        aantalG++;
      } else if (c == 'b') {
        aantalB++;
      }
    }
    inhoudSchalen[i] = std::make_pair(aantalG, aantalB);
  }

  return inhoudSchalen;
}//getInhoudSchalen

// Geeft een vector terug met de inhoud van alle rijen voor de gegeven speler
// De vector bevat paren van integers, waar de eerste integer het aantal gele tegels
// en de tweede integer het aantal blauwe tegels in de rij voorstelt
std::vector< std::pair <int,int> > TegelSpel::getInhoudRijen(int speler) {
  std::vector<std::pair<int, int>> inhoud(aantalRijenOpBord); 
  std::vector<std::vector<int>>* spelerRijen;

  if (speler == 0) {
    spelerRijen = &speler1;
  } else if (speler == 1) {
    spelerRijen = &speler2;
  }

  for (int i = 0; i < aantalRijenOpBord; i++) {
    int aantalG = (*spelerRijen)[i][0];
    int aantalB = (*spelerRijen)[i][0];

    inhoud[i] = std::make_pair(aantalG, aantalB);
  }

  return inhoud;
}//getInhoudRijen

// Leest de inhoud van de pot in vanuit de gegeven inputstream
// Geeft true terug als de pot succesvol is ingelezen, false anders
bool TegelSpel::leesPot(std::ifstream& fin) {
  std::string regel;
  if (std::getline(fin, regel)) {
    for (char c : regel) {
      if (c != 'g' && c != 'b') {
        std::cout << "Ongeldige inhoud van de pot \n";
        return false;
      }
    }
    huidigePot = regel;
  }
  return true;
}//leesPot

// Leest het aantal schalen en het maximum aantal tegels per schaal
// in vanuit de gegeven inputstream
// Geeft true terug als de schalen en tegels succesvol zijn ingelezen, false anders
bool TegelSpel::leesSchalenTegels(std::ifstream& fin) {
  if (!(fin >> aantalSchalen >> maximumAantalTegels)) {
    std::cout << "Fout bij inlezen aantalSchalen en maximumAantalTegels \n";
    return false;
  }

  if (!integerInBereik(aantalSchalen, 1, 5) || !integerInBereik(maximumAantalTegels, 1, 5)) {
    std::cout << "Waarden buiten toegestane bereik \n";
    return false;
  }

  return true;
}//leesSchalenTegels

// Leest het aantal rijen op het bord en het aantal vakjes per rij
// in vanuit de gegeven inputstream
// Geeft true terug als de rijen en vakjes succesvol zijn in ingelezen, false anders
bool TegelSpel::leesRijenVakjes(std::ifstream& fin) {
  if (!(fin >> aantalRijenOpBord >> aantalVakjesPerRij)) {
    std::cout << "Fout bij inlezen aantalRijenOpBord en aantalVakjesPerRij \n";
    return false;
  }

  if (!integerInBereik(aantalRijenOpBord, 1, 10) || !integerInBereik(aantalVakjesPerRij, 1, 6)) {
    std::cout << "Waarden buiten toegestane bereik \n";
    return false;
  }

  return true;
}//leesRijenVakjes


// Leest de data van beide spelers in vanuit de gegeven inputstream
// Geeft true terug als de data van beide spelers succesvol is ingelezen, false anders
bool TegelSpel::leesSpelers(std::ifstream& fin) {
  speler1.resize(aantalRijenOpBord, std::vector<int>(2));
  speler2.resize(aantalRijenOpBord, std::vector<int>(2));

  for (int i = 0; i < aantalRijenOpBord; i++) {
    if (!(fin >> speler1[i][0] >> speler1[i][1])) {
      std::cout << "Fout bij inlezen data van speler1 \n";
      return false;
    }

    if ((speler1[i][0] != 0 && speler1[i][1] != 0)) {
      std::cout << "Ongeldige waarden voor speler1 \n";
      return false;
    }
  }

  for (int i = 0; i < aantalRijenOpBord; i++) {
    if (!(fin >> speler2[i][0] >> speler2[i][1])) {
      std::cout << "Fout bij inlezen data van speler2 \n";
      return false;
    }

    if ((speler2[i][0] != 0 && speler2[i][1] != 0)) {
      std::cout << "Ongeldige waarden voor speler2 \n";
      return false;
    }
  }
  return true;
}//leesSpelers

// Leest de beurt van de huidige speler in vanuit de gegeven inputstream
// Geeft true terug als de beurt succesvol is ingelezen, false anders
bool TegelSpel::leesBeurt(std::ifstream& fin) {
  if (!(fin >> huidigeBeurt) || (huidigeBeurt != 0 && huidigeBeurt != 1)) {
    std::cout << "Fout bij inlezen van de huidige beurt \n";
    return false;
  } 
  return true;
}//leesBeurt

// Bepaalt de inhoud van de schalen op basis van de pot en het
// maximum aantal tegels per schaal
bool TegelSpel::bepaalTegels() {
  schalen.resize(aantalSchalen, std::vector<char>(maximumAantalTegels));

  size_t pos = 0;
  for (int i = 0; i < aantalSchalen; i++) {
    for (int j = 0; j < maximumAantalTegels; j++) {
      if (pos < huidigePot.size()) {
        schalen[i][j] = huidigePot[pos];
        pos++;
      } else {
        schalen[i][j] = '\0';
      }

      if (j > aantalVakjesPerRij) {
        std::cout << "Ongeldige aantal tegels per rij \n";
        return false;
      }
    }
  }
  return true;
}//bepaalTegels

// Leest de data van het spel in vanuit de gegeven bestandsnaam
// Geeft true terug als de data van het spel succesvol is ingelezen, false anders
bool TegelSpel::leesInSpel(const char* invoernaam) {
  std::ifstream fin;   
  fin.open(invoernaam); 

  if (!fin) {  
    std::cout << "Ongeldige bestandsnaam";
    return false;
  } 

  if (!leesPot(fin)) return false;
  if (!leesSchalenTegels(fin)) return false;
  if (!leesRijenVakjes(fin)) return false;
  if (!leesSpelers(fin)) return false;
  if (!leesBeurt(fin)) return false;
  if (!bepaalTegels()) return false;

  std::cout << "Spel succesvol ingelezen! \n";

  fin.close();
  return true;
}//leesInSpel

// Bepaalt of het spel afgelopen is
// Geeft true terug als het spel afgelopen is, false anders
bool TegelSpel::eindstand() {
  // situatie 1: ofwel heeft een speler alle rijen gevuld
  for (auto* spelerRijen : {&speler1, &speler2}) {
    int count = 0;
    for (int i = 0; i < aantalRijenOpBord; i++) {
      if ((*spelerRijen)[i][0] == 5 || (*spelerRijen)[i][1] == 5) {
        count++;
      }
    }

    if (count == 5) {
      return true;
    }
  }

  // situatie 2: de huidige speler heeft geen geldige zet
  // controleert voor elke kleur, schaal, enz. of er een geldige zet is en zo ja, retourneert false
  std::vector<std::vector<int>>* spelerRijen = (huidigeBeurt == 0) ? &speler1 : &speler2;

  for (int schaal = 0; schaal < aantalSchalen; schaal++) {
    for (char kleur : {'g', 'b'}) {
      int aantal = 0;
      for (char c : schalen[schaal]) {
        if (c == kleur) {
          aantal++;
        }
      }
      if (aantal == 0) continue;

      if (valideZetten(schaal, kleur, aantal, spelerRijen)) {
        return false;
      }
    }
  }

  return true;
}//eindstand

// Druk de hele stand (pot, schalen met inhoud, rijen van de spelers met inhoud, speler-aan-beurt) af op het scherm
void TegelSpel::drukAf() {
  std::cout << "\nInhoud van de pot: " << huidigePot << "\n";

  std::cout << "Inhoud van de schalen: \n";
  for (int i = 0; i < aantalSchalen; i++) {
    std::cout << "Schaal " << i << ": ";
    for (int j = 0; j < maximumAantalTegels && schalen[i][j] != '\0'; j++) {
      std::cout << schalen[i][j] << " ";
    }
    std::cout << "\n";
  }

  // setw wordt hier gebruikt zodat ik geen whitespace hoef te tellen
  std::cout << std::setw(15) << "Speler1" << std::setw(13) << "Speler2\n";
  for (int i = 0; i < aantalRijenOpBord; i++) {
    std::cout << "Rij " << i+1 << " :" << std::setw(4) << speler1[i][0] << " " << speler1[i][1] << std::setw(10) << speler2[i][0] << " " << speler2[i][1] << "\n";
  }

  std::cout << "Speler aan beurt: " << (huidigeBeurt == 0 ? "Speler 1" : "Speler 2") << "\n";
}//drukAf

// Bepaalt alle verschillende zetten die de huidige speler kan doen
// Geeft een vector terug met paren van integers, waar de eerste integer de
// schaal en de tweede integer de kleur van de tegel voorstelt
vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten() { 
  vector< pair<int,char> > zetten;
  std::vector<std::vector<int>>* spelerRijen = (huidigeBeurt == 0) ? &speler1 : &speler2;

  for (size_t i = 0; i < schalen.size(); i++) {
    int aantalG = 0;
    int aantalB = 0;
    for (char c : schalen[i]) {
      if (c == 'g') {
        aantalG++;
      } else if (c == 'b') {
        aantalB++;
      }
    }

    if (aantalG > 0 && valideZetten(i, 'g', aantalG, spelerRijen)) {
      zetten.push_back(make_pair(i, 'g'));
    }

    if (aantalB > 0 && valideZetten(i, 'b', aantalB, spelerRijen)) {
      zetten.push_back(make_pair(i, 'b'));
    }
  }

  return zetten;
}//bepaalVerschillendeZetten

// Verwijdert de tegels van de gekozen schaal en kleur uit de pot
// en schuift de resterende tegels op
void TegelSpel::verwijderEnSchuifSchalen(int schaal, char kleur) { 
    int start = schaal * maximumAantalTegels;
    int end = start + maximumAantalTegels;

    for (int i = start; i < end; i++) {
        if (huidigePot[i] == kleur) {
            huidigePot[i] = '\0';
        }
    }

    std::string newPot;
    for (char c : huidigePot) {
      if (c != '\0') {
        newPot += c;
      }
    }
    huidigePot = newPot;

    bepaalTegels();
}//verwijderEnSchuifSchalen

// Controleert of de gegeven schaal, kleur en aantal tegels
// geldig zijn
bool TegelSpel::zetEisen(int schaal, char kleur, int aantal) {
  if (schaal < 0 || schaal > (aantalSchalen)) {
    return false;
  }

  if ((kleur != 'g' && kleur != 'b') || aantal <= 0 || aantal >= aantalVakjesPerRij) {
    return false;
  }

  return true;
}//zetEisen

// Bepaalt of de zet met de gegeven schaal, kleur en aantal tegels
// geldig is voor de huidige speler
bool TegelSpel::valideZetten(int schaal, char kleur, int aantal, std::vector<std::vector<int>>* spelerRijen) {

  int aantalFouteOpties = 0;
  int besteZet = 0;
  aantalGelijkeOpties = 0;
  actieveKleur = (kleur == 'g') ? 0 : 1;
  
  for (int i = 0; i < 20; i++) {
    mogelijkeZetten[i] = 0;
  }

  for (int i = 0; i < aantalRijenOpBord; i++) {
    if ((*spelerRijen)[i][((kleur == 'g') ? 1 : 0)] != 0) { 
      aantalFouteOpties++;
      continue;
    }

   if (((*spelerRijen)[i][actieveKleur] + aantal) <= aantalVakjesPerRij) {
    if ((((*spelerRijen)[i][actieveKleur]) + aantal) > besteZet) {
      mogelijkeZetten[0] = i + 1;
      besteZet = (((*spelerRijen)[i][actieveKleur]) + aantal);

    } else if ((((*spelerRijen)[i][actieveKleur]) + aantal) == besteZet) {
      aantalGelijkeOpties++;
      mogelijkeZetten[aantalGelijkeOpties] = i + 1;
    }
   } else {
    aantalFouteOpties++;
   }
  }

  if (aantalFouteOpties == aantalRijenOpBord) {
    return false;
  }

  return true;
}//valideZetten

// Doet een zet voor de huidige speler basis van de schaal en kleur
// Geeft true terug als de zet gelukt is anders false
bool TegelSpel::doeZet(int schaal, char kleur) {

  // bepaal aantal keer dat kleur voorkomt in gekozen schaal
  int aantal = 0; 
  
  for (char c : schalen[schaal]) {
    if (c == kleur) {
      aantal++;
    }
  }

  // bepaal juiste rijen i.v.t. speler
  std::vector<std::vector<int>>* spelerRijen = (huidigeBeurt == 0) ? &speler1 : &speler2;
  if (eindstand()) return false;
  if (!zetEisen(schaal, kleur, aantal)) return false; // IT CRASHES HERE

  // sla huidige positie op en voeg toe aan stack
  spelState huidigeState = {huidigePot, speler1, speler2, huidigeBeurt};
  spelGeschiedenis.push(huidigeState);
  //cout << "reached \n";

  if (!valideZetten(schaal, kleur, aantal, spelerRijen)) return false;

 // cout << "schalen size " << schalen.size() << '\n';
 // cout << "schalen 3 item 0 " << schalen[2][0] << '\n';
  //cout << "we gaan voor zet: ( " << schaal << "," << kleur << ") \n";
 
  verwijderEnSchuifSchalen(schaal, kleur);

  int gekozenRij = 0;
  if (aantalGelijkeOpties > 0) {
    gekozenRij = mogelijkeZetten[randomGetal(0, aantalGelijkeOpties)] - 1;
  } else {
    gekozenRij = mogelijkeZetten[0] - 1;
  }

  (*spelerRijen)[gekozenRij][actieveKleur] += aantal;
  huidigeBeurt = (huidigeBeurt == 0) ? 1 : 0;

  return true;
}//doeZet

// Doet een zet terug voor de huidige speler zolang er al een zet gedaan was
// Geeft true terug als de zet gelukt is anders false
bool TegelSpel::unDoeZet() {
  if (spelGeschiedenis.empty()) {
    return false; 
  }

  spelState vorigeState = spelGeschiedenis.top();
  spelGeschiedenis.pop();

  huidigePot = vorigeState.huidigePot;
  speler1 = vorigeState.speler1;
  speler2 = vorigeState.speler2;
  huidigeBeurt = vorigeState.huidigeBeurt;

  bepaalTegels();

  return true;
}//unDoeZet

// Doet een zet terug voor de huidige speler zolang er al een zet gedaan was
// Geeft true terug als de zet gelukt is anders false
int TegelSpel::besteScore(pair<int,char> &besteZet, long long &aantalStanden) {

  if (eindstand()) {
    int score = berekenScore(this->huidigeBeurt == 0 ? &speler1 : &speler2);
    return score;
  }
  int besteScore = INT_MAX;
  pair<int,char> zet;

  vector<pair<int,char>> mogelijkeZetten = this->bepaalVerschillendeZetten();

  for (auto zet : mogelijkeZetten) {
    //cout << "readed 1 \n";
    TegelSpel kopie = *this;
    kopie.doeZet(zet.first, zet.second);
    pair<int,char> volgendeZet;
    int score = -kopie.besteScore(volgendeZet, aantalStanden);
   // cout << "readed 2 \n";
    if (abs(score) < abs(besteScore)) {
      besteScore = score;
      besteZet = zet;
    }

    aantalStanden++;
  }

  return besteScore;
}//besteScore

// Berekend de score voor de speler die aan de beurt is
int TegelSpel::berekenScore(vector<vector<int>>* spelerRijen) {
  // Bepaal het aantal volle rijen voor beide spelers
  int volleRijenSpeler1 = 0;
  int volleRijenSpeler2 = 0;

  for (auto rij : *spelerRijen) {
    if (rij[0] == aantalVakjesPerRij || rij[1] == aantalVakjesPerRij) {
      volleRijenSpeler1++;
    }
  }

  // Bepaal de rijen van de andere speler
  vector<vector<int>>* rijenSpeler2 = (spelerRijen == &speler1) ? &speler2 : &speler1;

  for (auto rij : *rijenSpeler2) {
    if (rij[0] == aantalVakjesPerRij || rij[1] == aantalVakjesPerRij) {
      volleRijenSpeler2++;
    }
  }

  // Bereken de score
  int score = volleRijenSpeler1 - volleRijenSpeler2;
  return score;
}//berekenScore


// Bepaalt een "goede" zet voor de speler die aan de beurt is
// op basis van Monte Carlo
pair<int,char> TegelSpel::bepaalGoedeZet(int nrSimulaties) { 
  if (eindstand()) return make_pair(-1, ' ');

  vector<pair<int, char>> mogelijkeZetten = bepaalVerschillendeZetten();
  pair<int,char> goedeZet;
  double topScore = INT_MIN;

  for (auto zet : mogelijkeZetten) {
    double totaleScore = 0;

    for (int i = 0; i < nrSimulaties; i++ ) {
      TegelSpel kopie = *this;
      
      kopie.doeZet(zet.first, zet.second);

      while (!kopie.eindstand()) {
        vector<pair<int, char>> zetten = kopie.bepaalVerschillendeZetten();
        pair<int,char> randomZet = zetten[randomGetal(0, zetten.size() - 1)];
        kopie.doeZet(randomZet.first, randomZet.second);
      }

      totaleScore += kopie.berekenScore(kopie.huidigeBeurt == 0 ? &kopie.speler1 : &kopie.speler2);
    }

    double gemiddeldeScore = totaleScore / nrSimulaties;
    if (gemiddeldeScore > topScore) {
      topScore = gemiddeldeScore;
      goedeZet = zet;
    }
  }

  return goedeZet;
}//bepaalGoedeZet


// Vergelijkt spelers die "goede" (= op basis van bepaalGoedeZet) en "beste" (= op basis van besteScore) zetten doen en retourneert de score van de huidige speler, ofwel "goede" speler
int TegelSpel::bepaalGoedeScore() {
  TegelSpel kopie = *this;
  long long aantalStanden = 0;

  while (!kopie.eindstand()) {
    pair<int,char> zet;

    if (kopie.huidigeBeurt == 0) {
      zet = kopie.bepaalGoedeZet(NrSimulaties);
    } else {
      kopie.besteScore(zet, aantalStanden);
    }
    kopie.doeZet(zet.first, zet.second);
    kopie.drukAf();
  }

  return kopie.berekenScore(&kopie.speler1);
}//bepaalGoedeScore

// Loopt door naar eind op basis van zetten gemaakt door bepaalGoedeZet 
// en meet vervolgens achteruit de berekeningstijd van besteScore;
void TegelSpel::doeExperiment() {
  TegelSpel kopie = *this;
  kopie.spelGeschiedenis.empty();
  int aantalZetten = 0;


  while (!kopie.eindstand()) {
    pair<int,char> zet = kopie.bepaalGoedeZet(NrSimulaties);
    kopie.doeZet(zet.first, zet.second);
    aantalZetten++;
  } 

  while (!kopie.spelGeschiedenis.empty()) {
    if (aantalZetten == 1) return;
    clock_t start = clock();

    pair<int,char> besteZet;
    long long aantalStanden = 0;
    kopie.besteScore(besteZet, aantalStanden);
    clock_t eind = clock();
    double duration = static_cast<double>(eind - start) / CLOCKS_PER_SEC;

    std::cout << "De zet met behulp van besteScore duurde " << duration << "s om te berekenen\n";
    if (aantalZetten > 2) {
      std::cout << "gegeven dat het " << aantalZetten - 1 << " zetten vanaf de startpositie berekend is. \n";
    } else {
      std::cout << "gegeven dat het vanaf de startpositie berekend is. \n";
    }

    aantalZetten--;
    kopie.unDoeZet();
  }
  
}//doeExperiment
