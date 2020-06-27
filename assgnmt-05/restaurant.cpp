#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit {
public:
  Produit(string, string);
  string getNom() const;
  string getUnite() const;
  virtual string toString() const;
  virtual const Produit *adapter(double) const;
  double quantiteTotale(const string &) const;

private:
  string nom;
  string unite;
};

class Ingredient {
public:
  Ingredient(const Produit &, double);
  const Produit &getProduit() const;
  double getQuantite() const;
  string descriptionAdaptee() const;
  string toString() const;
  double quantiteTotale(const string &) const;

private:
  const Produit &produit;
  double quantite;
};

class Recette {
public:
  Recette(string, double);
  void ajouter(const Produit &, double);
  Recette adapter(double) const;
  string toString() const;
  double quantiteTotale(const string &) const;

private:
  vector<Ingredient *> ingredients;
  string nom;
  double nbFois_;
};

class ProduitCuisine : public Produit {
public:
  ProduitCuisine(string);
  void ajouterARecette(const Produit &, double);
  const ProduitCuisine *adapter(double) const override;
  string toString() const override;
  double quantiteTotale(const string &) const;

private:
  Recette recette;
};

Produit::Produit(string nom, string unite = "")
: nom(nom), unite(unite)
{}

string
Produit::getNom() const
{
  return nom;
}

string
Produit::getUnite() const
{
  return unite;
}

string
Produit::toString() const
{
  return nom;
}

const Produit *
Produit::adapter(double n) const
{
  return this;
}

double
Produit::quantiteTotale(const string &nomProduit) const
{
  return nom == nomProduit ? 1. : 0.;
}

Ingredient::Ingredient(const Produit &produit, double quantite)
: produit(produit), quantite(quantite)
{}

const Produit &
Ingredient::getProduit() const
{
  return produit;
}

double
Ingredient::getQuantite() const
{
  return quantite;
}

string
Ingredient::descriptionAdaptee() const
{
  ostringstream ss;

  ss << fixed << quantite << " " << produit.getUnite() << " de " << produit.toString();
  return ss.str();
}

string
Ingredient::toString() const
{
  return descriptionAdaptee();
}

double
Ingredient::quantiteTotale(const string &nomProduit) const
{
  return quantite * produit.quantiteTotale(nomProduit);
}

Recette::Recette(string nom, double nbFois = 1.)
: nom(nom), nbFois_(nbFois)
{}

void
Recette::ajouter(const Produit &p, double quantite)
{
  ingredients.push_back(new Ingredient(p, nbFois_ * quantite));
}

Recette
Recette::adapter(double n) const
{
  Recette nouvelle(nom, nbFois_ * n);

  for (const Ingredient *ingredient : ingredients)
    nouvelle.ajouter(ingredient->getProduit(), ingredient->getQuantite() * n);
  return nouvelle;
}

string
Recette::toString() const
{
  ostringstream ss;
  unsigned int i = 1;

  ss << "  Recette \"" << nom << "\" x " << nbFois_ << ":";
  for (const Ingredient *ingredient : ingredients)
    ss << endl << "  " << i++ << ". " << ingredient->toString();
  return ss.str();
}

double
Recette::quantiteTotale(const string &nomProduit) const
{
  double somme = 0.;

  for (const Ingredient *ingredient : ingredients)
    somme += ingredient->quantiteTotale(nomProduit);
  return somme;
}

ProduitCuisine::ProduitCuisine(string nom)
: Produit(nom, "portion(s)"), recette(nom)
{}

void
ProduitCuisine::ajouterARecette(const Produit &produit, double quantite)
{
  recette.ajouter(produit, quantite);
}

const ProduitCuisine *
ProduitCuisine::adapter(double n) const
{
  ProduitCuisine *nouveau;

  nouveau = new ProduitCuisine(*this);
  nouveau->recette.adapter(n);
  return nouveau;
}

string
ProduitCuisine::toString() const
{
  return Produit::toString() + "\n" + recette.toString();
}

double
ProduitCuisine::quantiteTotale(const string &nomProduit) const
{
  return getNom() == nomProduit ? 1. : recette.quantiteTotale(nomProduit);
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
