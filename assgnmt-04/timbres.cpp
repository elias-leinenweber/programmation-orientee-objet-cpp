#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
  string nom;
  unsigned int annee;
  string pays;
  double valeur_faciale;

public:
  Timbre(string, unsigned int, string, double);
  double vente() const;
  unsigned int age() const;
  ostream &afficher(ostream &) const;
};

ostream &operator<<(ostream &, const Timbre &);

Timbre::Timbre(string nom, unsigned int annee, string pays = "Suisse",
    double valeur_faciale = 1.0)
: nom(nom), annee(annee), pays(pays), valeur_faciale(valeur_faciale)
{}

double
Timbre::vente() const
{
  double prix = valeur_faciale;
  unsigned int age_timbre = age();

  if (age_timbre >= 5)
    prix *= 2.5 * age_timbre;
  return prix;
}

unsigned int
Timbre::age() const
{
  return ANNEE_COURANTE - annee;
}

ostream &
Timbre::afficher(ostream &sortie) const
{
  return sortie << "de nom " << nom << " datant de " << annee <<
      " (provenance " << pays << ") ayant pour valeur faciale " <<
      valeur_faciale << " francs";
}

ostream &
operator<<(ostream &sortie, const Timbre &timbre)
{
  sortie << "Timbre ";
  return timbre.afficher(sortie);
}

class Rare : public Timbre {
private:
  static constexpr double PRIX_BASE_TRES_RARE = 600.0;
  static constexpr double PRIX_BASE_RARE = 400.0;
  static constexpr double PRIX_BASE_PEU_RARE = 50.0;
  unsigned int exemplaires;

public:
  Rare(string, unsigned int, string, double, unsigned int);
  unsigned int nb_exemplaires() const;
  double vente() const;
};

ostream &operator<<(ostream &, const Rare &);

Rare::Rare(string nom, unsigned int annee, string pays, double valeur_faciale,
    unsigned int exemplaires)
: Timbre(nom, annee, pays, valeur_faciale), exemplaires(exemplaires)
{}

unsigned int
Rare::nb_exemplaires() const
{
  return exemplaires;
}

double
Rare::vente() const
{
  return (exemplaires < 100 ? PRIX_BASE_TRES_RARE : (exemplaires < 1000 ?
      PRIX_BASE_RARE : PRIX_BASE_PEU_RARE)) * (age() / 10.0);
}

ostream &
operator<<(ostream &sortie, const Rare &rare)
{
  sortie << "Timbre rare (" << rare.nb_exemplaires() << " ex.) ";
  return rare.afficher(sortie);
}

class Commemoratif : public Timbre {
public:
  Commemoratif(string, unsigned int, string, double);
  double vente() const;
};

ostream &operator<<(ostream &, const Commemoratif &);

Commemoratif::Commemoratif(string nom, unsigned int annee, string pays,
    double valeur_faciale)
: Timbre(nom, annee, pays, valeur_faciale)
{}

double
Commemoratif::vente() const
{
  return 2 * Timbre::vente();
}

ostream &
operator<<(ostream &sortie, const Commemoratif &commemoratif)
{
  sortie << "Timbre commémoratif ";
  return commemoratif.afficher(sortie);
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
