// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <iomanip>  // voor leuker afdrukken
#include <fstream>   // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen ()
{
  // TODO: implementeer deze memberfunctie
  return 0;

}  // getSchalen

//*************************************************************************

string TegelSpel::getPot () { 

  return huidigePot;

  // TODO: implementeer deze memberfunctie

}  // getPot

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudSchalen ()
{ vector< pair <int,int> > inhoudSchalen;

  // TODO: implementeer deze memberfunctie

  return inhoudSchalen;

}  // getInhoudSchalen

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudRijen (int speler)
{ vector< pair <int,int> > inhoudRijen;

  // TODO: implementeer deze memberfunctie

  return inhoudRijen;

}  // getInhoudRijen

//*************************************************************************

bool TegelSpel::leesInSpel (const char* invoernaam) {
  std::ifstream fin;   
  fin.open(invoernaam); 

  if (!fin) {  
    std::cout << "Ongeldige bestandsnaam";
    return false;
  } 

  std::string regel;

  // case 1 : inhoud van de pot
  if (std::getline(fin, regel)) {
    for (char c : regel) {
      if (c != 'g' && c != 'b') {
        std::cout << "Ongeldige inhoud van de pot \n";
        return false;
      }
    }
    huidigePot = regel;
  }

  // case 2 : aantalSchalen en maximumAantalTegels
  if (!(fin >> aantalSchalen >> maximumAantalTegels)) {
    std::cout << "Fout bij inlezen aantalSchalen en maximumAantalTegels \n";
    return false;
  }

  // case 3 : aantalRijenOpBord en aantalVakjesPerRij
  if (!(fin >> aantalRijenOpBord >> aantalVakjesPerRij)) {
    std::cout << "Fout bij inlezen aantalRijenOpBord en aantalVakjesPerRij \n";
    return false;
  }

  // case 4 : speler1 en speler2
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

  // case 5 : huidigeBeurt
  if (!(fin >> huidigeBeurt) || (huidigeBeurt != 0 && huidigeBeurt != 1)) {
    std::cout << "Fout bij inlezen van de huidige beurt \n";
    return false;
  } 

  // bepaling van tegels t.o.v. schalen
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

  std::cout << "Spel succesvol ingelezen! \n";

  fin.close();
  return true;
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

