#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Flacon(string, double, double);
  ostream &etiquette(ostream &) const;
  const Flacon operator+(const Flacon &) const;
  #define BONUS
  Flacon &operator+=(const Flacon &);
};

ostream &operator<<(ostream &, const Flacon &);

Flacon::Flacon(string nom, double volume, double pH)
: nom(nom), volume(volume), pH(pH)
{}

ostream &
Flacon::etiquette(ostream &sortie) const
{
  return sortie << nom << " : " << volume << " mL, pH " << pH;
}

ostream &
operator<<(ostream &sortie, const Flacon &flacon)
{
  return flacon.etiquette(sortie);
}

const Flacon
Flacon::operator+(const Flacon &autre) const
{
  double nouveau_pH = -log10((volume * pow(10.0, -pH) + autre.volume * pow(10.0, -autre.pH)) / (volume + autre.volume));
  return Flacon(nom + " + " + autre.nom, volume + autre.volume, nouveau_pH);
}

Flacon &
Flacon::operator+=(const Flacon &autre)
{
  return *this = *this + autre;
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
