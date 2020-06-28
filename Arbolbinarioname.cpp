#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <chrono>

using namespace std;

struct Nodo{
    string dato;
    Nodo *der;
    Nodo *izq;
};

//prototipos de las funciones
void menu();
Nodo *crearNodo(string);
void insertNodo(Nodo *&,string); //Le pasamos uno de tipo nodo y por ref
Nodo *arbol = NULL;
void mostrarArbol(Nodo *arbol,int contador); //En este caso "arbol" no va por referencia (&) porque no cambiaremos ningún valor, solo mostraremos sus valores. El contador ayudará para ordenar de manera correcta y separará los nodos de otros en el momento de la impresión. Contador va a empezar valiendo 0 e irá subiendo. Imprimiremos primero lo de la derecha.
bool busqueda(Nodo *,string);
int altura(Nodo *arbol);

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
    ifstream archivo;
    archivo.open("/Users/ypoblete/Desktop/CPP/Datosbasicos/LaboratorioEDA/TareaEDA/Tarea3/universities_followers.txt",ios::in);
    //"/Users/ypoblete/Desktop/CPP/Datosbasicos/LaboratorioEDA/TareaEDA/Tarea3/universities_followers.txt"
    
    misDatos followers;
    vector <misDatos> datos;
    vector <string> vectordatos;
    int contador = 0;
    string dato;
    int n=20000;
    vector <string> random;
    
    for(int i=0;i<n;i++){
        random.push_back("1 + rand() % 1000");
    }
    
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
                    break;
                    case 2: // Usuario
                        followers.name = dato;
                        insertNodo(arbol,dato);
                        vectordatos.push_back(dato);
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
    //mostrarArbol(arbol, contador); //Para mostrar mi arbol
        
    //}
    //auto endInsert = std::chrono::system_clock::now();
    
    //std::chrono::duration<double> elapsedInsert = endInsert - startInsert;
    //std::cout << "Tiempo inserción: " << elapsedInsert.count() << " s";
    
    cout << "\n" << endl;
    
    //Para búsqueda de elementos que si están
    auto startSearch = std::chrono::system_clock::now();
    {
    for(int i=0;i<n;i++){
        string clave = vectordatos[rand()%vectordatos.size()];
        busqueda(arbol,clave);
     /*if(busqueda(arbol,clave)){
        cout << "Si" << endl;
        }
        else{
            cout << "No" << endl;
        }*/
    }
    }
    auto endSearch = std::chrono::system_clock::now();
    
    //Para búsqueda de datos NO que están
    auto startSearch2 = std::chrono::system_clock::now();
    {
    for(int i=0;i<n;i++){
        string clave = random[rand()%random.size()];
        busqueda(arbol,clave);
        /*if(busqueda(arbol,clave)){
        cout << "Si" << endl;
        }
        else{
            cout << "No" << endl;
        }*/
    }
    }
    auto endSearch2 = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsedSearch = endSearch - startSearch;
    std::cout << "Tiempo búsqueda si están: " << elapsedSearch.count() << " s";
    
    cout << "\n" << endl;
    
    std::chrono::duration<double> elapsedSearch2 = endSearch2 - startSearch2;
    std::cout << "Tiempo búsqueda no están: " << elapsedSearch2.count() << " s";

    cout << "\n" << endl;
    
    cout << sizeof(dato) << endl;
    
    cout << sizeof(followers.name) << endl;
    
    cout << "la altura del arbol es: " << altura(arbol) << endl;

    return 0;
}

Nodo *crearNodo(string n){
    Nodo *nuevo_nodo = new Nodo(); //creamos el nuevo nodo y le reservamos memoria de tipo Nodo();
    
    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    
    return nuevo_nodo;
}

void insertNodo(Nodo *&arbol, string n){
    if(arbol == NULL){ //Si arbol está vacío, crea un nuevo nodo
        Nodo *nuevo_nodo = crearNodo(n); //Llamamos a nuestra función crear nodo con dato n
        arbol = nuevo_nodo;
    }
    else{ //Si el arbol tiene 1 o mas nodos. Necesitamos primer tener el valor de la raiz para ver a que lado lo enviamos
        string valorRaiz = arbol->dato; //Obtenemos valor raiz
        if(n < valorRaiz){
            insertNodo(arbol->izq,n); //Con esto nos vamos hacia el lado izquierdo e insertamos el n
        }
        else{ //Con esto nos iríamos al lado derecho
            insertNodo(arbol->der,n);
        }
    }
    
}
//Función para mostrar árbol completo
void mostrarArbol(Nodo *arbol,int cont){
    if(arbol == NULL) return; //Vemos si es que el arbol no esta vacío primero. Solo retornamos porque no voy a mostrar nada
    else{
        mostrarArbol(arbol->der,cont+1); //Esto hace que sea recursivo
        for(int i=0;i<cont;i++){ //Aqui usamos el contador para ir iterando sobre el contador y mostrar los elementos de la derecha. Dará el espacio entre un nodo y otro
            cout <<"     "; //Dejamos 3 espacios por si los números son muy grandes para que se vea bien
        }
        cout<<arbol->dato<<endl; //Con esto se muestra la rama
        mostrarArbol(arbol->izq,cont+1);
    }
}

bool busqueda(Nodo *arbol,string n){ //Para buscar es True o False en caso que esté o no.
    if(arbol == NULL) return false; //Para revisar si el árbol está vacío
    else if(arbol->dato == n) return true;
    else if(n<arbol->dato) return busqueda(arbol->izq,n);
    else return busqueda(arbol->der,n);
}

int altura(Nodo *arbol){
    if(arbol == NULL) return -1;
    
    int izq = altura(arbol->izq);
    int der = altura(arbol->der);
    return izq > der? izq + 1 : der + 1;
}
