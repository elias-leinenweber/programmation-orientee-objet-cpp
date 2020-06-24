#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

class Patient {
  public:
    void init(double, double);
    void afficher();
    double poids();
    double taille();
    double imc();

  private:
    double masse;
    double hauteur;
};

void
Patient::init(double poids, double taille)
{
  if (poids > 0.0 && taille > 0.0) {
    masse = poids;
    hauteur = taille;
  } else {
    masse = 0.0;
    hauteur = 0.0;
  }
}

void
Patient::afficher()
{
  cout << "Patient : " << masse << " kg pour " << hauteur << " m" << endl;
}

double
Patient::poids()
{
  return masse;
}

double
Patient::taille()
{
  return hauteur;
}

double
Patient::imc()
{
  return hauteur != 0.0 ? masse / (hauteur * hauteur) : 0.0;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Patient quidam;
  double poids, taille;
  do {
    cout << "Entrez un poids (kg) et une taille (m) : ";
    cin >> poids >> taille;
    quidam.init(poids, taille);
    quidam.afficher();
    cout << "IMC : " << quidam.imc() << endl;
  } while (poids * taille != 0.0);
  return 0;
}
