#include <iostream>
using namespace std;

struct equipo{              //El registro de equipos es para el ordenamiento en el arbol segun el criterio
    int cod_equipo;
    int goles;
};
struct nodo{                //El registro nodo tiene la información, un puntero al hijo izquierdo y un puntero al hijo derecho
    equipo info;
    nodo* izq;
    nodo* der;
};

////////////////////////////////////////////////////////////////////////////////
///////////////////Funciones características del arbol/////////////////////////
///////////////////////////////////////////////////////////////////////////////

void inOrden(nodo*, char[32][20]);

void insertaNodo(nodo* &, equipo);

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/////////////////////Funciones características del ejercicio//////////////////
//////////////////////////////////////////////////////////////////////////////

int cargaEquipos(equipo[32]);

void cargaVector(char [32][20]);

//////////////////////////////////////////////////////////////////////////////

int main() {
	
	setlocale(LC_ALL, "");
	
	cout << "******************************************************************************" << endl;
	cout << "**********Bienvenido al sistema de impresión de equipos del mundial***********" << endl;
	cout << "*******************************************************************************"<< endl;
	
	cout << "A continuación se prodecerá a mostrar los equipos ordenados por cantidad de goles: " << endl;
	

    equipo equipos[32];                     //En equipos se guardan los datos de las selecciones

    if(cargaEquipos(equipos)){              //Si logra cargar los equipos desde el archivo...

        nodo * raiz = NULL;                 //Puntero a la raiz del arbol
        int i = 0;
        for(i; i < 32; i++){
            insertaNodo(raiz, equipos[i]);  //Se inserta la selección en el arbol
        }

        char nombres[32][20];               //Nombres de las selecciones
        cargaVector(nombres);               //se carga el vector con los nombres
        inOrden(raiz, nombres);             //Se imprime inOrden


    } else {                                //Si no se pudo abrir el archivo...

        cout << "El archivo de equipos no existe, por favor consulte el instructivo para más información" << endl;
    }

	system("pause");
    return 0;
}

//Esta función carga los equipos desde el archivo al vector
int cargaEquipos(equipo equipos[32]){
    int V[32] {0};
    FILE* f = NULL;

    if(f = fopen("Goles por equipo.dat", "rb")){
        fseek(f, 0, SEEK_SET);
        fread(&V, sizeof(int), 32, f);

        int i = 0;
        for(i; i < 32; i++){
            equipos[i].goles = V[i];
            equipos[i].cod_equipo = i;
        }
        return 1;
    } else {
        return 0;
    }
}

//Esta función inserta los equipos en el arbol
void insertaNodo(nodo* &arbol, equipo x){

    if(arbol == NULL){
        nodo* aux = new nodo();
        aux -> info = x;
        aux -> izq = NULL;
        aux -> der = NULL;

        arbol = aux;
    } else {
        if(x.goles < arbol -> info.goles){
            insertaNodo(arbol -> izq, x);
        } else if(x.goles >= arbol -> info.goles){
            insertaNodo(arbol -> der, x);
        }
    }
    return;
}

//Esta función imprime inOrden
void inOrden(nodo* arbol, char v[32][20]){
    if(arbol != NULL){
        inOrden(arbol -> izq, v);
        cout << "La selección de " << v[arbol -> info.cod_equipo] << " ha convertido " << arbol -> info.goles << " goles " <<endl;
        inOrden(arbol -> der,v);
    }
    return;
}

//Esta función carga el vector de nombres...
void cargaVector(char V[32][20]) {
    char V1[32][20] = {
            {"Rusia"},
            {"Alemania"},
            {"Brasil"},
            {"Portugal"},
            {"Argentina"},
            {"Bélgica"},
            {"Polonia"},
            {"Francia"},
            {"España"},
            {"Perú"},
            {"Suiza"},
            {"Inglaterra"},
            {"Colombia"},
            {"Croacia"},
            {"México"},
            {"Uruguay"},
            {"Dinamarca"},
            {"Suecia"},
            {"Islandia"},
            {"Costa Rica"},
            {"Túnez"},
            {"Egipto"},
            {"Senegal"},
            {"Iran"},
            {"Serbia"},
            {"Nigeria"},
            {"Japón"},
            {"Marruecos"},
            {"Panamá"},
            {"Corea del Sur"},
            {"Arabia Saudí"},
            {"Australia"}};

    memcpy(V, V1, sizeof(V1));

}
