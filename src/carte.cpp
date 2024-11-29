#include "Carte.h"
#include "point2D.hpp"
#include "polygone.hpp"
#include "ZN.hpp"
#include "ZA.hpp"
#include "ZAU.hpp"
#include "ZU.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Pour utiliser istringstream

using namespace std;

vector<Parcelle*> ListaParcelles;

string readFileIntoString(const string& path) {
  string  content;
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    content = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>())+string("\n");
    input_file.close();
  //cout << content<<endl;
  return content;
}


vector<string> extraireMots(const string& phrase) {
    vector<string> mots;
    istringstream flux(phrase); // Crée un flux à partir de la chaîne
    string mot;
    // Lire chaque mot séparé par un espace
    while (flux >> mot) {
        mots.push_back(mot);
    }
    return mots;
}


void ImporZU (string data){
  vector<string> mots = extraireMots(data);
  string Zone = "ZU" ;
  int Numéro = stoi(mots[1]);
  string Propriétaire = mots[2];
  int pConstructible = stoi(mots[3]);
  int surfaceConstruite = stoi(mots[4]);
  cout<<surfaceConstruite <<endl;
  cout<<stoi(mots[4]);
  vector<Point2D<int>> points ;
  for(int i=5;i<mots.size();i++){
    int x = 0; 
    int y = 0;
    mots[i] = mots[i].substr(1, mots[i].size() - 2); // Enlève '[' et ']'
  // Trouver la position du ';'
    size_t posPointVirgule = mots[i].find(';');
      // Extraire les parties avant et après le ';'
    string avantStr = mots[i].substr(0, posPointVirgule);
    string apresStr = mots[i].substr(posPointVirgule + 1);
      // Convertir les chaînes en entiers
    x = stoi(avantStr);
    y = stoi(apresStr);
    points.push_back(Point2D<int>(x,y)); 
  }
  Polygone<int> poly = Polygone<int>(points);
  ZU* parcelle = new ZU( Numéro, Propriétaire, poly , pConstructible, surfaceConstruite);
  ListaParcelles.push_back(parcelle);
}

void ImporZAU (string data){
  vector<string> mots = extraireMots(data);
  string Zone = "ZAU" ;
  int Numéro = stoi(mots[1]);
  string Propriétaire = mots[2];
  int pConstructible = stoi(mots[3]);
  vector<Point2D<int>> points ;
  for(int i=4;i<mots.size();i++){
    int x = 0; 
    int y = 0;
    mots[i] = mots[i].substr(1, mots[i].size() - 2); // Enlève '[' et ']'
  // Trouver la position du ';'
    size_t posPointVirgule = mots[i].find(';');
      // Extraire les parties avant et après le ';'
    string avantStr = mots[i].substr(0, posPointVirgule);
    string apresStr = mots[i].substr(posPointVirgule + 1);
      // Convertir les chaînes en entiers
    x = stoi(avantStr);
    y = stoi(apresStr);
    points.push_back(Point2D<int>(x,y)); 
  }
  Polygone<int> poly = Polygone<int>(points);
  ZAU* parcelle = new ZAU( Numéro, Propriétaire, poly , pConstructible);
  
  ListaParcelles.push_back(parcelle);

}

void ImporZA (string data){
  vector<string> mots = extraireMots(data);
  string Zone = "ZA" ;
  int Numéro = stoi(mots[1]);
  string Propriétaire = mots[2];
  string typeCulture = mots[3];
  vector<Point2D<int>> points ;
  for(int i=4;i<mots.size();i++){
    int x = 0; 
    int y = 0;
    mots[i] = mots[i].substr(1, mots[i].size() - 2); // Enlève '[' et ']'
  // Trouver la position du ';'
    size_t posPointVirgule = mots[i].find(';');
      // Extraire les parties avant et après le ';'
    string avantStr = mots[i].substr(0, posPointVirgule);
    string apresStr = mots[i].substr(posPointVirgule + 1);
      // Convertir les chaînes en entiers
    x = stoi(avantStr);
    y = stoi(apresStr);
    points.push_back(Point2D<int>(x,y)); 
  }
  Polygone<int> poly = Polygone<int>(points);
  ZA* parcelle = new ZA( Numéro, Propriétaire, poly , typeCulture);
  ListaParcelles.push_back(parcelle);
}

void ImporZN (string data){
  vector<string> mots = extraireMots(data);
  string Zone = "ZN" ;
  int Numéro = stoi(mots[1]);
  string Propriétaire = mots[2];
  vector<Point2D<int>> points ;
  for(int i=3;i<mots.size();i++){
    int x = 0; 
    int y = 0;
    mots[i] = mots[i].substr(1, mots[i].size() - 2); // Enlève '[' et ']'
  // Trouver la position du ';'
    size_t posPointVirgule = mots[i].find(';');
      // Extraire les parties avant et après le ';'
    string avantStr = mots[i].substr(0, posPointVirgule);
    string apresStr = mots[i].substr(posPointVirgule + 1);
      // Convertir les chaînes en entiers
    x = stoi(avantStr);
    y = stoi(apresStr);
    points.push_back(Point2D<int>(x,y)); 
  }
  Polygone<int> poly = Polygone<int>(points);
  ZN* parcelle = new ZN( Numéro, Propriétaire, poly,0);
  ListaParcelles.push_back(parcelle);  
}

void separateur(string data){
  int line = 0;
  string phrase = "";
  for (int i = 0 ; i <  data.size(); i++)
    {
      phrase += data[i];
        // check whether parsing character is punctuation or not
      if (data[i] =='\n')
        {
          if(line ==1){
            size_t espaceIndex = phrase.find(' ');
            string Zone = phrase.substr(0, espaceIndex);
            if(Zone =="ZU"){
              ImporZU(phrase);
            } else if (Zone =="ZAU"){
              ImporZAU(phrase);
            }else if (Zone == "ZA"){
              ImporZA(phrase);
            }else if (Zone=="ZN"){
              ImporZN(phrase);
            }
          cout << ""<<endl;
          line = 0 ;
          phrase = "";
          }
          else{
            line++;
          }
        }
    }
}

Carte::Carte(string path){
  string text= readFileIntoString(path);
  separateur(text);
}




void Carte::Export(){
   ofstream fichier("mon_fichier.txt");
    // Vérifier si le fichier est ouvert
    if (fichier.is_open()) {
     for(int i = 0 ; i<ListaParcelles.size(); i++){
        // Écrire dans le fichier
         fichier<< ListaParcelles[i]->getType()<<" ";
         fichier<< ListaParcelles[i]->getNumero()<<" ";
         fichier<< ListaParcelles[i]->getProprietaire()<<" ";


        if ((ListaParcelles[i]->getType())=="ZA"){
          auto za = dynamic_cast<ZA*>(ListaParcelles[i]) ;
          fichier << za->getCulture() << "\n";
          
        }else if((ListaParcelles[i]->getType())=="ZAU"){
          fichier<< ListaParcelles[i]->getPConstruct()<<"\n";

        }else if((ListaParcelles[i]->getType())=="ZN"){
          fichier<<"\n";
         
        }else if((ListaParcelles[i]->getType())=="ZU"){
          fichier<< ListaParcelles[i]->getPConstruct()<<" ";
          auto zu = dynamic_cast<ZU*>(ListaParcelles[i]) ;
          fichier << zu->getPContruite() << "\n";
         
        }
        fichier<< ListaParcelles[i]->getForme()<<"\n";
     }
        // Fermer le fichier
        fichier.close(); 
    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    
  

}



