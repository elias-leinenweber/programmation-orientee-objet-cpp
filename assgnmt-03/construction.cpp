#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Brique(Forme, Couleur);
  ostream &afficher(ostream &) const;
};

ostream &operator<<(ostream &, const Brique &);

Brique::Brique(Forme forme, Couleur couleur)
: forme(forme), couleur(couleur)
{}

ostream &
Brique::afficher(ostream &sortie) const
{
  if (couleur != "")
    sortie << "(" << forme << ", " << couleur << ")";
  else
    sortie << forme;
  return sortie;
}

ostream &
operator<<(ostream &sortie, const Brique &brique)
{
  return brique.afficher(sortie);
}

class Construction {
  friend class Grader;

public:
  Construction(Brique);
  ostream &afficher(ostream &) const;
  Construction &operator^=(const Construction &);
  Construction &operator-=(const Construction &);
  Construction &operator+=(const Construction &);

private:
  vector<vector<vector<Brique>>> contenu;
};

Construction::Construction(Brique brique)
: contenu(1, vector<vector<Brique>>(1, vector<Brique>()))
{
  contenu[0][0].push_back(brique);
}

ostream &
Construction::afficher(ostream &sortie) const
{
  for (int i = contenu.size() - 1; i >= 0; --i) {
    sortie << "Couche " << i << " :" << endl;
    for (const vector<Brique> &rangee : contenu[i]) {
      for (const Brique &brique : rangee)
        sortie << brique << " ";
      sortie << endl;
    }
  }
  return sortie;
}

ostream &
operator<<(ostream &sortie, const Construction &construction)
{
  return construction.afficher(sortie);
}

Construction &
Construction::operator^=(const Construction &autre)
{
  for (const vector<vector<Brique>> &couche : autre.contenu)
    this->contenu.push_back(couche);
  return *this;
}

const Construction
operator^(Construction a, const Construction &b)
{
  return a ^= b;
}

Construction &
Construction::operator-=(const Construction &autre)
{
  if (autre.contenu.size() >= this->contenu.size())
    for (unsigned int i = 0; i < this->contenu.size(); ++i)
      for (const vector<Brique> &rangee : autre.contenu[i])
        this->contenu[i].push_back(rangee);
  return *this;
}

const Construction
operator-(Construction a, const Construction &b)
{
  return a -= b;
}

Construction &
Construction::operator+=(const Construction &autre)
{
  if (autre.contenu.size() >= this->contenu.size())
    for (unsigned int i = 0; i < this->contenu.size(); ++i)
      if (autre.contenu[i].size() >= this->contenu[i].size())
        for (unsigned int j = 0; j < this->contenu[i].size(); ++j)
          for (const Brique &brique : autre.contenu[i][j])
            this->contenu[i][j].push_back(brique);
  return *this;
}

const Construction
operator+(Construction a, const Construction &b)
{
  return a += b;
}

const Construction
operator*(unsigned int n, const Construction &a)
{
  Construction res = a;

  for (unsigned int i = 1; i < n; ++i)
    res += a;
  return res;
}

const Construction
operator/(unsigned int n, const Construction &a)
{
  Construction res = a;

  for (unsigned int i = 1; i < n; ++i)
    res ^= a;
  return res;
}

const Construction
operator%(unsigned int n, const Construction &a)
{
  Construction res = a;

  for (unsigned int i = 1; i < n; ++i)
    res -= a;
  return res;
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
