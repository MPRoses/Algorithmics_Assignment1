// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <iomanip>  // setw
#include <fstream>   // file lezen
#include <algorithm> // count
#include <iostream>
#include <chrono>
#include <thread>
#include <climits>

//*************************************************************************

TegelSpel::TegelSpel ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

int TegelSpel::getSchalen () {
  return aantalSchalen;
}

string TegelSpel::getPot () { 
  return huidigePot;
}

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
}

std::vector< std::pair <int,int> > TegelSpel::getInhoudRijen (int speler) {
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
}

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
}

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
}

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
}

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
}

bool TegelSpel::leesBeurt(std::ifstream& fin) {
  if (!(fin >> huidigeBeurt) || (huidigeBeurt != 0 && huidigeBeurt != 1)) {
    std::cout << "Fout bij inlezen van de huidige beurt \n";
    return false;
  } 
  return true;
}

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
}

bool TegelSpel::leesInSpel (const char* invoernaam) {
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
}

bool TegelSpel::eindstand() {
  // check if game has ended, returns true if game is finished, otherwise false
  // case 1: either a player has all rows filled
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

  // case 2: current player has no valid move
  // checks for every kleur, schaal, etc. whether there is a valid move and if so, return false
  std::vector<std::vector<int>>* spelerRijen = (huidigeBeurt == 0) ? &speler1 : &speler2;

  for (int schaal = 0; schaal < 2; schaal++) {
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

// hi als je dit leest k ben t hier eig niet helemaal mee eens met een onderdeel
// als schaal 0 en schaal 1 equivalente kleuren hebben betekend niet dat de zetten hetzelfde
// zijn, aangezien je de verdere string huidigePot veranderd. Dat is aangezien er shift left is
// schaal 1 schuift op 0, maar schaal 2 schuift op 1, en zolang 2 niet gelijk is aan 1 en enz. voor de hele string ofwel alle schalen zullen de zetten de toekomstige schalen anders beinvloeden
// e.g. bgbgbgbgggbb, kies voor kleur = 'g' en schaal = 0 v 1
// schaal(0) -> bbbgbgggbb, en uit schaal(1) volgt: bgbgbbggbb, bgbgbbggbb is niet gelijk aan bbbgbgggbb

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


void TegelSpel::verwijderEnSchuifSchalen(int schaal, char kleur) { 
    int start = schaal * maximumAantalTegels;
    int end = start + maximumAantalTegels;

    for (int i = start; i < end; i++) {
        if (huidigePot[i] == kleur) {
            huidigePot[i] = '\0';
        }
    }

    huidigePot.erase(std::remove(huidigePot.begin(), huidigePot.end(), '\0'), huidigePot.end());

    bepaalTegels();
}//verwijderEnSchuifSchalen

bool TegelSpel::zetEisen(int schaal, char kleur, int aantal) {
  if (schaal < 0 || schaal > 1) {
    return false;
  }

  if ((kleur != 'g' && kleur != 'b') || aantal <= 0 || aantal >= aantalVakjesPerRij) {
    return false;
  }

  return true;
}//zetEisen

bool TegelSpel::valideZetten(int schaal, char kleur, int aantal, std::vector<std::vector<int>>* spelerRijen) {

  int aantalFouteOpties = 0;
  int besteZet = 0;
  aantalGelijkeOpties = 0;
  actieveKleur = (kleur == 'g') ? 0 : 1;
  
  for (int i = 0; i < 10; i++) {
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
   // cout << "geen opties in rij \n";
    return false;
  }

  return true;
}//valideZetten

bool TegelSpel::doeZet (int schaal, char kleur) {
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
  if (!zetEisen(schaal, kleur, aantal)) return false;
    
  // sla huidige positie op en voeg toe aan stack
  spelState huidigeState = {huidigePot, speler1, speler2, huidigeBeurt};
  spelGeschiedenis.push(huidigeState);

  if (!valideZetten(schaal, kleur, aantal, spelerRijen)) return false;
 
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
/*
int TegelSpel::besteScore(pair<int,char> &besteZet, long long &aantalStanden) {
  cout << "1 \n";
  TegelSpel kopie = *this;

  if (kopie.eindstand()) {
    return berekenScore(kopie.huidigeBeurt == 0 ? &speler1 : &speler2);
  }

  besteZet = kopie.bepaalGoedeZet(NrSimulaties);
  cout << "2 \n";

  kopie.doeZet(besteZet.first, besteZet.second);
  cout << "3 \n";
  pair<int,char> volgendeZet;
  //int score = -kopie.besteScore(volgendeZet, aantalStanden);
  cout << "4 \n";
  aantalStanden++;

  return 0;
}//besteScore */

int TegelSpel::besteScore(pair<int,char> &besteZet, long long &aantalStanden) {
  if (eindstand()) {
    int score = berekenScore(this->huidigeBeurt == 0 ? &speler1 : &speler2);
    return score;
  }

  int besteScore = INT_MAX;
  pair<int,char> zet;

  vector<pair<int,char>> mogelijkeZetten = this->bepaalVerschillendeZetten();

  for (auto zet : mogelijkeZetten) {
    TegelSpel kopie = *this;
    kopie.doeZet(zet.first, zet.second);

    pair<int,char> volgendeZet;
    int score = -kopie.besteScore(volgendeZet, aantalStanden);
    if (abs(score) < abs(besteScore)) {
      besteScore = score;
      besteZet = zet;
    }

    aantalStanden++;
  }

  return besteScore;
}



int TegelSpel::berekenScore(vector<vector<int>>* spelerRijen) {
  int volleRijenSpeler1 = 0;
  int volleRijenSpeler2 = 0;

  for (auto rij : *spelerRijen) {
    if (rij[0] == aantalVakjesPerRij || rij[1] == aantalVakjesPerRij) {
      volleRijenSpeler1++;
    }
  }

  vector<vector<int>>* rijenSpeler2 = (spelerRijen == &speler1) ? &speler2 : &speler1;

  for (auto rij : *rijenSpeler2) {
    if (rij[0] == aantalVakjesPerRij || rij[1] == aantalVakjesPerRij) {
      volleRijenSpeler2++;
    }
  }

  int score = volleRijenSpeler1 - volleRijenSpeler2;
  return score;
}//berekenScore
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
}

// Bugfix voor bug die ik niet begreep.
// als je bepaalGoedeScore() of doeExperiment() in een keer runned, zonder eerst bepaalGoedeZet of doeZet te runnen kom je in de derde iteratie van doeZet in een infinite loop.
void TegelSpel::initBord() {
  bepaalGoedeZet(NrSimulaties);
}

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

    // Ik neem aan dat het "niet" de bedoeling is deze library te gebruiken
    // ma het werkt heel eenvoudig en maakt het lekker mooi gelijk voor de gebruiker.
    std::this_thread::sleep_for(std::chrono::milliseconds(350));
    kopie.drukAf();
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  return kopie.berekenScore(&kopie.speler1);
}//bepaalGoedeScore

int aantalX = 0;

void TegelSpel::doeExperiment() {
  if (aantalX % 2 == 0) {
    initBord();
  }
  aantalX++;
  
  TegelSpel kopie = *this;
  int aantalZetten = 0;

  while (!kopie.eindstand()) {
    pair<int,char> zet = kopie.bepaalGoedeZet(NrSimulaties);
    kopie.doeZet(zet.first, zet.second);
    aantalZetten++;
  } 

  while (!kopie.spelGeschiedenis.empty()) {
    auto start = std::chrono::high_resolution_clock::now();
    pair<int,char> besteZet;
    long long aantalStanden = 0;
    kopie.besteScore(besteZet, aantalStanden); // GETS STUCK HERE ON RUN 2

    auto eind = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duur = eind - start;

    std::cout << "De zet met behulp van besteScore duurde " << duur.count() << " om te berekenen\n";
    if (aantalZetten > 2) {
      std::cout << "gegeven dat het " << aantalZetten - 1 << " zetten vanaf de startpositie berekend is. \n";
    } else {
      std::cout << "gegeven dat het vanaf de startpositie berekend is. \n";
    }

    aantalZetten--;
    kopie.unDoeZet();
  }
}//doeExperiment
