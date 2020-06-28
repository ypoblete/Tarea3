#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <vector>

using namespace std;

class TablaHash{
private:
    static const int hashN = 21089; //N° de registros de tweeter
    int cant = 0;
    list <pair<string,double>> tabla[hashN]; //Armamos una tabla con: Lista 1 al indice 0, Lista 2 al indice 1... y así sucesivamente
    
public:
    bool isEmpty() const; //Para hacer la consulta si lista está vacía
    unsigned long funcHash(string clave); //Función hash con la que se almacenarán los datos
    void insertValor(string clave,double valor); //función insertar datos
    void removeValor(int clave); //Si queremos eliminar
    int buscarValor(string clave); //Si queremos buscar
    void printTabla();
    int getCant();
    int contarList();
};

bool TablaHash::isEmpty() const{
    return cant == 0;
}

unsigned long TablaHash::funcHash(string clave){
    unsigned long hash = 5381;
    int c;
    for(int i=0;i<8 && i<clave.size();i++){ //Lee hasta 8 caracteres del string
        c = clave[i];
        hash = ((hash<<5)+ hash)+c;
    }
    return hash % hashN;
}


void TablaHash::insertValor(string clave,double valor){
    unsigned long valorHash = funcHash(clave); //Definiendo la entrada a la tabla hash con la clave
    auto& celda = tabla[valorHash]; //Dependiendo del valor, dice a que lista le corresponderá el par clave-valor
    auto Iter = begin(celda); //Definimos un iterador para el comienzo de la lista
    bool existeClave = false; //Preguntamos si la clave existe o no para asegurarnos. En caso de que exista lo que haremos será reemplazar el valor con el valor nuevo a insertar.
    for(;Iter != end(celda);Iter++){ //Recorremos las listas para verificar que la clave exista o no
        if(Iter->first == clave){
            existeClave = true; //Si existe clave...
            Iter->second = valor; //El valor será reemplazado
            break;
        }
    }
    if(!existeClave){
        celda.emplace_back(clave,valor); //Creamos la celda e insertamos la clave,valor
        cant++;
    }
    return;
}

int TablaHash::buscarValor(string clave){
    int pos = funcHash(clave);
    int inicial = pos;
    auto &celda = tabla[inicial];
    auto Iter = begin(celda);
    for(;Iter != end(celda);Iter++){
            if(Iter->first==clave) return pos;
    }
    return -1;
}

void TablaHash::printTabla(){ //Impresión de la tabla hash
    for(int i{};i<hashN;i++){ //Ciclo for para recorrer las claves insertadas hasta el número máximo de claves
        if(tabla[i].size() == 0) continue; //Para que continue en caso que no tenga tamaño
        auto Iter = tabla[i].begin(); //creamos iterador para recorrer la tabla desde el comienzo
        for(;Iter != tabla[i].end();Iter++){ //Hacemos el ciclo for para recorrer la tabla hasta el final
            cout << "Clave: " << i << " " << Iter->first << " Valor: " << Iter->second << endl; //Imprimiendo las claves con valores respectivos
        }
    }
}

int TablaHash::getCant(){
    return cant;
}

int TablaHash::contarList(){
    int conta = 0;
    for(int i{};i<hashN;i++){
        if(tabla[i].size() != 0) conta++;
    }
    cout << conta << endl;
    return 0;
}

struct misDatos
{
    string univ;
    double id;
    string name;
    int tweets;
    int friends;
    int followers;
    string date;
};

int main(){
    TablaHash TH;
    misDatos followers;
    int contador =0;
    string dato;
    int n=20000;
    vector<pair<string,double>> vectordatos;
    vector<string> random;
    
    for(int i=0;i<n;i++){
        random.push_back("abcdefghi");
    }

    ifstream archivo;

    archivo.open("/Users/ypoblete/Desktop/CPP/Datosbasicos/LaboratorioEDA/TareaEDA/Tarea3/universities_followers.txt",ios::in);
    
    
    //auto startInsert = std::chrono::system_clock::now();
    //{

    string linea;
    int cantLineasLeer = 20000; //21071 es el total
    for(int i=0; i<cantLineasLeer; i++){
                getline(archivo,linea);
        stringstream registro(linea);
        if(contador == 0){
            contador++; //Contador +=1;
            continue; //equivalente al break pero no rompe el ciclo, solo cambia la iteración y se salta la línea.
                
        }
        
        double id = 0;
        string name;
        
        for (int columna = 0; getline(registro, dato, ',');columna++){
                switch (columna){
                    case 0: // Universidad
                        followers.univ = dato;
                    break;
                    case 1: // ID
                        followers.id = stod(dato);
                        id = stod(dato);
                    break;
                    case 2: // Usuario
                        followers.name = dato;
                        name = dato;
                    break;
                    case 3: // Tweets
                        followers.tweets = stoi(dato);
                    break;
                    case 4: // Friends
                        followers.friends = stoi(dato);
                    break;
                    case 5: // Followers
                        followers.followers = stoi(dato);
                    break;
                    case 6: //fecha
                        followers.date = dato;
                    break;
            }
        }
        TH.insertValor(name,id);
        vectordatos.push_back(make_pair(name,id));
        }
    
    TH.contarList();
    
    //}
    //auto endInsert = std::chrono::system_clock::now();
    
    //std::chrono::duration<double> elapsedInsert = endInsert - startInsert;
    //std::cout << "Elapsed time: " << elapsedInsert.count() << "s" << endl;
    
    //TH.printTabla();
    
    //Buscando valores que si están
    auto startSearch = std::chrono::system_clock::now();
    {
    for(int i=0;i<n;i++){
        string busca = vectordatos[rand()%vectordatos.size()].first;
        TH.buscarValor(busca);
        /*if(TH.buscarValor(busca) == -1){
            cout <<"No : " << busca << endl;
        }
        else{
            cout << "Si : " << busca << endl;
        }*/
    }
    }
    auto endSearch = std::chrono::system_clock::now();
    
    //Para búsqueda de datos NO que están
    auto startSearch2 = std::chrono::system_clock::now();
    {
    for(int i=0;i<n;i++){
        string busca = random[rand()%random.size()];
        TH.buscarValor(busca);
        /*if(TH.buscarValor(busca) == -1){
            cout << "No : " << busca << endl;
        }
        else{
            cout << "Si : " << busca << endl;
        }*/
    }
    }
    auto endSearch2 = std::chrono::system_clock::now();
    
    
    std::chrono::duration<double> elapsedSearch = endSearch - startSearch;
    std::cout << "Tiempo búsqueda si están: " << elapsedSearch.count() << " s";
    
    cout << "\n" << endl;
    
    std::chrono::duration<double> elapsedSearch2 = endSearch2 - startSearch2;
    std::cout << "Tiempo búsqueda no están: " << elapsedSearch2.count() << " s";
    
    cout << endl;
    return 0;
}
