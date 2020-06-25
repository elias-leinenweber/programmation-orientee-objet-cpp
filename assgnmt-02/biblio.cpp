#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur {
public:
  Auteur(string, bool);
  Auteur(const Auteur &) = delete;
  string getNom() const;
  bool getPrix() const;

private:
  string nom;
  bool prix;
};

Auteur::Auteur(string nom, bool prix = false)
: nom(nom), prix(prix)
{}

string
Auteur::getNom() const
{
  return nom;
}

bool
Auteur::getPrix() const
{
  return prix;
}

class Oeuvre {
public:
  Oeuvre(string, Auteur &, string);
  Oeuvre(const Oeuvre &) = delete;
  string getTitre() const;
  const Auteur &getAuteur() const;
  string getLangue() const;
  void affiche() const;
  ~Oeuvre();

private:
  string titre;
  const Auteur &auteur;
  string langue;
};

Oeuvre::Oeuvre(string titre, Auteur &auteur, string langue)
: titre(titre), auteur(auteur), langue(langue)
{}

string
Oeuvre::getTitre() const
{
  return titre;
}

Auteur const &
Oeuvre::getAuteur() const
{
  return auteur;
}

string
Oeuvre::getLangue() const
{
  return langue;
}

void
Oeuvre::affiche() const
{
  cout << titre << ", " << auteur.getNom() << ", en " << langue;
}

Oeuvre::~Oeuvre()
{
  cout << "L'oeuvre \"";
  affiche();
  cout << "\" n'est plus disponible." << endl;
}

class Exemplaire {
public:
  Exemplaire(Oeuvre &);
  Exemplaire(const Exemplaire &);
  const Oeuvre &getOeuvre() const;
  void affiche();
  ~Exemplaire();

private:
  Oeuvre &oeuvre;
};

Exemplaire::Exemplaire(Oeuvre &oeuvre)
: oeuvre(oeuvre)
{
  cout << "Nouvel exemplaire de : ";
  oeuvre.affiche();
  cout << endl;
}

Exemplaire::Exemplaire(const Exemplaire &autre)
: oeuvre(autre.oeuvre)
{
  cout << "Copie d'un exemplaire de ";
  autre.getOeuvre().affiche();
  cout << endl;
}

Oeuvre const &
Exemplaire::getOeuvre() const
{
  return oeuvre;
}

void
Exemplaire::affiche()
{
  cout << "Exemplaire de : ";
  oeuvre.affiche();
}

Exemplaire::~Exemplaire()
{
  cout << "Un exemplaire de \"";
  oeuvre.affiche();
  cout << "\" a été jeté !" << endl;
}

class Bibliotheque {
public:
  Bibliotheque(string);
  string getNom() const;
  void stocker(Oeuvre &, unsigned int);
  void lister_exemplaires(string) const;
  unsigned int compter_exemplaires(const Oeuvre &) const;
  void afficher_auteurs(bool) const;
  ~Bibliotheque();

private:
  string nom;
  vector<Exemplaire *> exemplaires;
};

Bibliotheque::Bibliotheque(string nom)
: nom(nom)
{
  cout << "La bibliothèque " << nom << " est ouverte !" << endl;
}

string
Bibliotheque::getNom() const
{
  return nom;
}

void
Bibliotheque::stocker(Oeuvre &oeuvre, unsigned int n = 1)
{
  for (unsigned int i = 0; i < n; ++i)
    exemplaires.push_back(new Exemplaire(oeuvre));
}

void
Bibliotheque::lister_exemplaires(string langue = "") const
{
  for (Exemplaire* const exemplaire : exemplaires)
    if (langue == "" || exemplaire->getOeuvre().getLangue() == langue) {
      exemplaire->affiche();
      cout << endl;
    }
}

unsigned int
Bibliotheque::compter_exemplaires(const Oeuvre &oeuvre) const
{
  unsigned int n = 0;
  for (Exemplaire* const exemplaire : exemplaires)
    if (exemplaire->getOeuvre().getTitre() == oeuvre.getTitre() &&
        exemplaire->getOeuvre().getAuteur().getNom() == oeuvre.getAuteur().getNom() &&
        exemplaire->getOeuvre().getAuteur().getPrix() == oeuvre.getAuteur().getPrix() &&
        exemplaire->getOeuvre().getLangue() == oeuvre.getLangue())
      ++n;
  return n;
}

void
Bibliotheque::afficher_auteurs(bool prix = false) const
{
  for (Exemplaire* const exemplaire : exemplaires)
    if (!prix || exemplaire->getOeuvre().getAuteur().getPrix())
      cout << exemplaire->getOeuvre().getAuteur().getNom() << endl;
}

Bibliotheque::~Bibliotheque()
{
  cout << "La bibliothèque " << nom << " ferme ses portes," << endl << "et détruit ses exemplaires :" << endl;
  for (Exemplaire *exemplaire : exemplaires)
    delete exemplaire;
}
/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
