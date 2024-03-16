// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <iomanip>  // setw
#include <fstream>   // file lezen
#include <algorithm> // count
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen () {
  return aantalSchalen;
}  // getSchalen

//*************************************************************************

string TegelSpel::getPot () { 
  return huidigePot;
}  // getPot

//*************************************************************************
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

//*************************************************************************

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

//*************************************************************************

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
  bepaalTegels();

  std::cout << "Spel succesvol ingelezen! \n";

  fin.close();
  return true;
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
  return true;
}

bool TegelSpel::leesRijenVakjes(std::ifstream& fin) {
  if (!(fin >> aantalRijenOpBord >> aantalVakjesPerRij)) {
    std::cout << "Fout bij inlezen aantalRijenOpBord en aantalVakjesPerRij \n";
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
  }
  for (int i = 0; i < aantalRijenOpBord; i++) {
    if (!(fin >> speler2[i][0] >> speler2[i][1])) {
      std::cout << "Fout bij inlezen data van speler2 \n";
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

void TegelSpel::bepaalTegels() {
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
    }
  }
}

//*************************************************************************

bool TegelSpel::eindstand ()
{
  // TODO: implementeer deze memberfunctie

  return false;

} // eindstand

//*************************************************************************

void TegelSpel::drukAf () {
  std::cout << "\nInhoud van de pot: " << huidigePot << "\n";

  std::cout << "Inhoud van de schalen: \n";
for (int i = 0; i < aantalSchalen; i++) {
  std::cout << "Schaal " << i+1 << ": ";
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

  std::cout << "Speler-aan-beurt: " << (huidigeBeurt == 0 ? "Speler 1" : "Speler 2") << "\n";
}


//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () { 
  vector< pair<int,char> > zetten;

  // TODO: implementeer deze memberfunctie

  return zetten;

}  // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet ()
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // unDoeZet

//*************************************************************************

int TegelSpel::besteScore (pair<int,char> &besteZet,
                             long long &aantalStanden)
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // besteScore

//*************************************************************************

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties)
{ pair<int,char> goedeZet;

  // TODO: implementeer deze memberfunctie

  return goedeZet;

}  // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore ()
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore

//*************************************************************************

void TegelSpel::doeExperiment ()
{
  // TODO: implementeer deze memberfunctie

}  // doeExperiment

