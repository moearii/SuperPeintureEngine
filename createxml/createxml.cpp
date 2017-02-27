#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

vector<string> split(const string &s, char delim);
void affichageDonnee(vector<string> vect);
vector<string> lectureDonnee(char * path);
vector<string> lectureDonneeLumiere(char * path);

/* Compil
 * g++ createxml.cpp -o createxml
 */
int main(int argc, char * argv[]){

    if(argc > 4 || argc < 3){
        cerr << "ERROR::syntax createxml absoption.cpp diffusion.cpp sortie.xml" << endl;
        cerr << "ERROR::syntax createxml lumiere.cpp sortie.xml" << endl;
        exit(1);
    }

    if(argc == 4){
        vector<string> absorption = lectureDonnee(argv[1]);
        vector<string> diffusion = lectureDonnee(argv[2]);

        // Verif donnees lues
        // affichageDonnee(absorption);

        // creation du fichier XML

        ofstream file (argv[3], ios::trunc);

        // check if file is opened
        if(!file.is_open()){
            cerr << "ERROR::Unable to creat file.xml" << endl;
            exit(2);
        }

        string pigmentName = argv[1];
        int iwaveLength = 380;



        pigmentName = pigmentName.substr(1,pigmentName.size() - 5);

        file << "<pigment>" << endl;
        file << "\t<label>" << pigmentName << "</label>" << endl;
        for(int i = 0; i < 101; i++){
            stringstream swaveLength;
            swaveLength << iwaveLength;
            file << "\t<amplitude wavelength = \"" << swaveLength.str() << "\">" << endl;
            file << "\t\t<absorption>" << absorption[i] << "</absorption>" << endl;
            file << "\t\t<diffusion>" << diffusion[i] << "</diffusion>" << endl;
            file << "\t</amplitude>" << endl;
            iwaveLength += 4;
        }
        file << "</pigment>";

        file.close();
    } else {
        vector<string> amplitude = lectureDonneeLumiere(argv[1]);
        ofstream file (argv[2], ios::trunc);
        // check if file is opened
        if(!file.is_open()){
            cerr << "ERROR::Unable to creat file.xml" << endl;
            exit(2);
        }

        string lumiereName = argv[1];
        int iwaveLength = 380;
        lumiereName = lumiereName.substr(11,lumiereName.size() - 15);

        file << "<lumiere>" << endl;
        file << "\t<label>" << lumiereName << "</label>" << endl;
        for(int i = 0; i < 101; i++){
            stringstream swaveLength;
            swaveLength << iwaveLength;
            file << "\t<amplitude wavelength = \"" << swaveLength.str() << "\">";
            file << amplitude[i];
            file << "</amplitude>" << endl;
            iwaveLength += 4;
        }
        file << "</lumiere>";

        file.close();
    }

    return 0;
}

// http://stackoverflow.com/questions/236129/split-a-string-in-c*/
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim))
    elems.push_back(item);

    return elems;
}

void affichageDonnee(vector<string> vect){
    for(int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
    }
}

vector<string> lectureDonnee(char * path){

    vector<string> donnees;
    ifstream file (path);

    // check if file is opened
    if(!file.is_open()){
        cerr << "ERROR::files is not open -> check files path" << endl;
        exit(2);
    }

    string line;
    vector<string> lineElements;

    // On lit les deux premieres lignes qui n'ont pas d'information utiles
    getline(file,line);
    getline(file,line);
    for(int i = 0; i < 101; i++){
        getline(file,line);
        lineElements = split(line, ' ');
        donnees.push_back(lineElements[4]);

    }

    file.close();

    return donnees;
}

vector<string> lectureDonneeLumiere(char * path){

    vector<string> donnees;
    ifstream file (path);

    // check if file is opened
    if(!file.is_open()){
        cerr << "ERROR::files is not open -> check files path" << endl;
        exit(2);
    }

    string line;
    vector<string> lineElements;

    // On lit les deux premieres lignes qui n'ont pas d'information utiles
    getline(file,line);
    getline(file,line);
    for(int i = 0; i < 101; i++){
        getline(file,line);
        lineElements = split(line, ' ');
        //cout << lineElements[1] << endl;
        donnees.push_back(lineElements[1]);

    }

    file.close();

    return donnees;
}
