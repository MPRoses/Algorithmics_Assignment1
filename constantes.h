// Enkele constantes voor implementatie TegelSpel

#ifndef ConstantesHVar  // voorkom dat dit bestand meerdere keren
#define ConstantesHVar  // ge-include wordt

using namespace std;

const int MaxSchalen = 5;    // maximaal aantal schalen
const int MaxPerSchaal = 5;  // maximaal aantal tegels op een schaal
const int MaxRijen = 10;      // maximaal aantal rijen om tegels in te leggen
const int MaxPerRij = 6;     // maximaal aantal stenen per rij
const int NrSimulaties = 100;  // bij bepalen van `goede' zet
const pair<int,char> GeenZet = make_pair (-1,'\0');  // ongeldige zet

#endif

