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

/*
 for (int i = 0; i < aantalRijenOpBord; i++) {
    int aantalVol = 0; 
    int aantalLeeg = 0;
    char actieveKleur;

    if (!(spelerData[i][0] == 0 && spelerData[i][1] == 0)) {
      actieveKleur = spelerData[i][0] == 0 ? 'b' : 'g';
    }

    if (actieveKleur == 'g') {
      aantalVol = spelerData[i][0];
    } else if (actieveKleur == 'b') {
      aantalVol = spelerData[i][1];
    }
    */

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur) {
  std::vector<std::vector<int>>* spelerRijen;
  int aantal = 0;

  // if game is finished return

  if (schaal < 0 || schaal >= aantalSchalen) {
    return false;
  }

  for (char c : schalen[schaal]) {
    if (c == kleur) {
      aantal++;
    }
  }

  if ((kleur != 'g' && kleur != 'b') || aantal <= 0 || aantal >= aantalVakjesPerRij) {
    return false;
  }

  if (kleur == 'g') {
    spelerRijen = &speler1;
  } else if (kleur == 'b') {
    spelerRijen = &speler2;
  }

  int actieveKleur = (kleur == 'g') ? 0 : 1;
  int mogelijkeZetten[10][1]; // best row of possibility followed by 0 = g || 1 = b

  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 1; j++) {
        mogelijkeZetten[i][j] = 0;
    }
  }

  int aantalGelijkeOpties = 1;
  int besteZet = 0;   
  // kleur = yellow, Y B B Y
  for (int i = 0; i < aantalRijenOpBord; i++) {

    if ((*spelerRijen)[i][((kleur == 'g') ? 1 : 0)] != 0) {
      continue;
    }

   if (((*spelerRijen)[i][actieveKleur] + aantal) <= 5) {

    if ((((*spelerRijen)[i][actieveKleur]) + aantal) > besteZet) {

      mogelijkeZetten[0][0] = actieveKleur;
      besteZet = (((*spelerRijen)[i][actieveKleur]) + aantal);

    } else if ((((*spelerRijen)[i][actieveKleur]) + aantal - 5) == besteZet) {

      mogelijkeZetten[i][0] = actieveKleur;
      aantalGelijkeOpties++;
    }
   } 
  } 

  for (int i = 0; i < 10; i++) {
    if (mogelijkeZetten[i][0] != 0) {
      cout << "Mogelijke zet in rij: " << i << ' ' << mogelijkeZetten[i][0];
    }
  }

  return true;

}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet () {
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

