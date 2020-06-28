#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <string>
#include <iterator>
#include <math.h>
#include <vector>

using namespace std;

//Usaremos un arreglo porque me interesa un contenedor con posición. Otra alternativa podría ser un arreglo de pares o punteros e ir trabajando con nodos.
class Hash{
private:
    long double *tabla = new long double[30403]; //voy a tener palabras en mi tabla. Tamaño 57 que lo decido yo. La hago como puntero
    long double disponible = NULL; //Solo para estética de poder saber si una de mis casillas en la tabla está disponible o vacía
    long double vacio = NULL;
    long int tam;  //Hace referencia a la cantidad de objetos insertados
    long int cap; //La capacidad será de 21070 ya que definí que mi tabla iba a ser de 21070 elementos
public:
    
    Hash(){ //Mi constructor, no recibe nada y solo inicializa los valores de mis variables.
        this->tam = 0;
        this->cap = 30403;
    }
    void expandir(){ //No es tan sencillo agrandar el arreglo como en un arraylist ya que las inserciones se hicieron en base a la capacidad. Por lo tanto si la expando debo modificar las inserciones
        long int aux[cap];
        long int capaux = cap;
        for(int i=0;i<cap;i++) aux[i]=tabla[i]; //voy a iterar y tener todos los elementos que tenia en mi tabla inicialmente
        this->tabla = new long double[cap*2]; //En este caso creamos una tabla auxiliar de tamaño doble del anterior.
        cap*=2;
        for(int i=0;i<capaux;i++){ //ahora realizo la inserción
            insert(aux[i]);
        }
    }
    //Definiendo métodos que necesito principalmente: función hash, insertar, saber tamaño y obtener posición (at).
    long int fhash(double s){
        long int aux = (long int)round(abs(s)) % this->cap;
        return aux;
    }
    
    void insert(double s){
        if(tam==cap*2) expandir(); //Si tamaño = capacidad, entonces llamo a mi función expandir. Esto también es el factor de carga alpha con valor 1, esto quiere decir que cuando tenga mi tabla llena, recien voy a expandir aunque muchas veces se usan factores de carga menores. Podría usar el ideal que es 0,5 o 0,7 donde mi tabla esté llena hasta la mitad y ahí realizar la expansión. //Menos menor factor de carga la complejidad temporal es menor ya que no tengo que recorrer tanto para buscar un espacio vacío.
        long int pos = fhash(s);
        
        while(true){
            if(tabla[pos]==disponible || tabla[pos] == vacio){ //Comprobar si posicion está disponible o vacia
                break; //En caso que esté disponible rompo el ciclo
            }
            else{
                if(tabla[pos] == s){
                    return;
                }
                pos = (pos+1)%this->cap; //En caso que no esté disponible le sumo 1 a la posición. Siempre le hago módulo para asegurarme que nunca me exceda del límite de mi capacidad. Esto actualiza la posición. Esta estrategia es bastante básica, si encuentra la posición ocupada entonces busco la siguiente. Esto considera la LINEAL PROBING, ya que si mi posición donde quiero insertar ya está ocupada, entonces pruebo las posiciones siguientes
            }
        }
        tabla[pos] = s; //Luego que encuentro la posición disponible, rompo el ciclo y realizo la inserción en mi tabla hash con esta línea de código. En caso que mi capacidad sea llenada, debo volver a crear mi tabla
        tam++;
    }
    long int size(){ //solo retorno el tamaño
        return tam;
    }
    long int at(double s){ //Dada una palabra, retornar la posición en la que está insertada. Esto sirve para comprobar si el elemento está insertado en la tabla ya que sinó regresará invalido.
        long int pos = fhash(s);
        for(int i=0;i<cap;i++){
            if(tabla[pos] == s) return pos;
            pos = (pos+1)%this->cap; //Aumenta el número si no lo encuentra
        }
        return -1; //En caso que no se encuentre la palabra
    }

    void mostrarTabla(){
        if(tam == 0) return;
        int cont = 0;
        for(int i=0;i<cap;i++){
            if(tabla[i] != vacio && tabla[i] != disponible){
                cout << tabla[i] << endl;
                cont++;
            }
        }
        cout << "Total: " << cont << endl;
    }
    long int getTam(){
        return tam;
    }
};

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
    Hash h;
    misDatos followers;
    vector <double> vectordatos;
    int contador =0;
    string dato;
    int n = 20000;
    vector <double> random;
    
    for(int i=0;i<n;i++){
        random.push_back(1 + rand()%1000);
    }
    
    ifstream archivo;
    
    archivo.open("/Users/ypoblete/Desktop/CPP/Datosbasicos/LaboratorioEDA/TareaEDA/Tarea3/universities_followers.txt",ios::in);
    

    //auto startInsert = std::chrono::system_clock::now();
    //{
    
    string linea;
    int cantLineasLeer = 21000; //21071 es el total
    for(int i=0; i<cantLineasLeer; i++){
                getline(archivo,linea);
        stringstream registro(linea);
        if(contador == 0){
            contador++; //Contador +=1;
            continue; //equivalente al break pero no rompe el ciclo, solo cambia la iteración y se salta la línea.
        }
        
        for (int columna = 0; getline(registro, dato, ',');columna++){
                switch (columna){
                    case 0: // Universidad
                        followers.univ = dato;
                    break;
                    case 1: // ID
                        followers.id = stod(dato);
                        h.insert(stod(dato));
                        vectordatos.push_back(stod(dato));
                    break;
                    case 2: // Usuario
                        followers.name = dato;
                        //cout<< name << endl;
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
    }
    
    //}
    //auto endInsert = std::chrono::system_clock::now();
    
    //std::chrono::duration<double> elapsedInsert = endInsert - startInsert;
    //std::cout << "Elapsed time: " << elapsedInsert.count() << "s" << endl;

    //h.mostrarTabla();
    //cout << "Total insertos: " << h.getTam() << endl;

    //Para búsqueda de elementos que si están
    auto startSearch = std::chrono::system_clock::now();
    {
    for(int i=0;i<n;i++){
        double clave = vectordatos[rand()%vectordatos.size()];
        h.at(clave);
        /*if(h.at(clave) == -1){
            cout << "No" << endl;
        }
        else{
            cout << "Si" << endl;
        }*/
    }
    }
    auto endSearch = std::chrono::system_clock::now();
    
    //Para búsqueda de datos NO que están
    auto startSearch2 = std::chrono::system_clock::now();
    {
    for(int i=0;i<n;i++){
        double clave = random[rand()%random.size()];
        h.at(clave);
        /*if(h.at(clave) == -1){
            cout << "No" << endl;
        }
        else{
            cout << "Si" << endl;
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

