#include <iostream>
#include <cstring>

using namespace std;

struct gol {                    //El registro gol, contiene los datos que comprenden cada uno de los goles, se usa para la extracción del archivo
    int id_gol;                 //Identificador único de gol
    int cod_equipo;             //Código unico de equipo
    int fecha;                  //Fecha del partido aaaammdd
    char nombre_jugador[40];    //Nombre del jugador
    int id_partido;             //Identificador único del partido
};

struct jugador {                //El registro jugador se utiliza para cargar la matriz con los datos solicitados
    char nombre_jugador[40];    //Nombre del jugador
    int fecha;                  //Fecha del partido
    int goles;                  //Cantidad de goles por jugador
};

struct nodo {                   //Nodo para la matriz y ordenamientos solicitados
    jugador info;
    nodo *sgte;
};

struct goleador {               //El registro goleador es utilizado para organizar los goleadores del mundial
    char nom[40];
    int cod_equipo;
    int goles;
    goleador *sgte;
};

struct nodo1 {                  //El nodo1 se utiliza para las listas de ordenamiento por fechas

    int fecha;
    goleador *goleadores;
    nodo1 *sgte;
};

struct jugador1{                //El registro jugador1 se utiliza para el ordenamiento de los goleadores por mundial

    char nom[40];
    int goles;
    int equipo;
};


/////////////////////////////////////////////////////
///////Funciones características del ejercicio//////
///////////////////////////////////////////////////

void cargaVector(char[32][20]);

int cargarMatriz(nodo *[32][64]);

void cantGolesPorEquipo(nodo *[32][64], char[32][20]);

void goleadoresMundial(nodo *[32][64], char[32][20]);

void goleadoresPorFecha(nodo *[32][64], char [32][20]);

void ordenarVector(jugador1 [], int);

//////////////////////////////////////////////////

////////////////////////////////////////////////////
//////Funciones características de las listas//////
//////////////////////////////////////////////////
nodo *insertaOrdenado(nodo *&, jugador);

nodo1 *insertaOrdenado(nodo1 *&, int);

goleador *insertaOrdenado(goleador *&, char[]);

nodo *buscar(nodo *, jugador);

nodo1 *buscar(nodo1 *, int);

goleador *buscar(goleador *, char[]);

nodo *buscar_o_insertar(nodo *&, jugador);

nodo1 *buscar_o_insertar(nodo1 *&, int);

goleador *buscar_o_insertar(goleador *&, char[]);

int retornaCantidad(goleador* &);

/////////////////////////////////////////////////

//////////////////////////////////////////////////
////Funciones características de los archivos////
////////////////////////////////////////////////
int existe(char[], FILE *&);

FILE *abrirArchivo(char []);

void punteroAlInicio(FILE *);

//////////////////////////////////////////////

int main() {
    setlocale(LC_ALL, "");

    cout << "*******************************************************************************" << endl;
    cout << "*******************Bienvenido al sistema de impresión ordenada*****************" << endl;
    cout << "*******************************************************************************" << endl;

    nodo *goles[32][64] = {NULL};           //Matriz de punteros
    int bandera = 0;                        //Variable para controlar do-while
    char V[32][20];                         //Vector de nombres de equipos
    cargaVector(V);                         //Carga de vector

    int existencia = cargarMatriz(goles);

    do {
        char itemseleccionado[10];
        if (existencia) { //Si se pudo cargar la matriz con el archivo...
            cout << "Se ha encontrado un archivo de goles." << endl;

            cout << "1. Mostrar cantidad de goles por equipo" << endl;
            cout << "2. Mostrar goleadores por fecha" << endl;
            cout << "3. Mostrar goleadores del mundial" << endl;
            cout << "4. Salir" << endl;
            cout << "Por favor seleccione una opción: ";
            cin >> itemseleccionado;

            if (!strcmp(itemseleccionado, "1")) {           //Si el usuario seleccionó la opción 1...
                cantGolesPorEquipo(goles, V);
            } else if (!strcmp(itemseleccionado, "2")) {    //Si el usuario seleccionó la opción 2...
                goleadoresPorFecha(goles, V);
            } else if (!strcmp(itemseleccionado, "3")) {    //Si el usuario seleccionó la opción 3...
                goleadoresMundial(goles, V);
            } else if (!strcmp(itemseleccionado, "4")){     //Si el usuario seleccionó la opción 4...
                bandera = 1;
            }
        } else {
            cout << "El archivo de goles no se ha encontrado, por favor, ejecute Ejercicio 1.exe y revise el instructivo para más información..." << endl;
            system("pause");
            bandera = 1;
        }

    } while (!bandera);


    return 0;
}

//La siguiente función carga la matriz con la información solicitada
int cargarMatriz(nodo *M[32][64]) {
    FILE *f = NULL;
    gol x;
    jugador z;
    nodo *w;

    if (!existe("goles.dat", f)) {
        return 0;
    } else {
        punteroAlInicio(f);
        while (!feof(f)) {
            fread(&x, sizeof(gol), 1, f);

            strcpy(z.nombre_jugador, x.nombre_jugador);
            z.fecha = x.fecha;

            w = buscar_o_insertar(M[x.cod_equipo][x.id_partido], z);
            w->info.goles++;
        }
        return 1;
    }
}

//La siguiente función imprime la cantidad de goles por equipo
void cantGolesPorEquipo(nodo *M[32][64], char equipos[32][20]) { //Recibe la matriz y tambien los nombres de los equipos

    int i = 0;
    int j = 0;
    int v[32] = {0};                        //En v se guardan los goles del equipo i


    for (i; i < 32; i++) {
        for (j = 0; j < 64; j++) {
            nodo *p = M[i][j];
            //nodo *q = NULL;

            while (p != NULL) {
                v[i] += p->info.goles;      //Se incrementa por cada gol
                p = p->sgte;

            }

        }
    }

    for(i = 0; i < 32; i++){
        cout << "La selección de  " << equipos[i] << " ha convertido " << v[i] << " goles" << endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //////////El siguiente bloque genera un archivo que usará el siguiente ejercicio/////
    /////////////////////////////////////////////////////////////////////////////////////
    FILE* f = fopen("Goles por equipo.dat", "wb");
    fwrite(&v, sizeof(int), 32, f);
    fflush(f);
    fclose(f);
    /////////////////////////////////////////////////////////////////////////////////////
}

//La siguiente función imprime los goleadores por fecha
void goleadoresPorFecha(nodo *M[32][64], char V[32][20]) {  //Recibe la matriz y el vector de nombres
    nodo1 *lista = NULL;
    nodo1 *p = NULL;
    goleador* q = NULL;
    int fe;                 //En fe se guardará la fecha para operar con ella

    int i = 0;
    int j = 0;

    for (i; i < 32; i++) {
        for (j = 0; j < 64; j++) {
            if (M[i][j] != NULL) {
                fe = M[i][j]->info.fecha;           //En fe se guarda la fecha
                nodo *t = M[i][j];
                while (t != NULL) {
                    p = buscar_o_insertar(lista, fe);   //Se busca en la lista si la fecha ya tiene goleadores registrados

                    q = insertaOrdenado(p -> goleadores, t -> info.nombre_jugador); //Se inserta el jugador en la fecha
                    q->goles = t ->info.goles;                                      //Se actualiza la cantidad de goles
                    q->cod_equipo = i;                                              //Se registra el equipo de donde proviene el gol
                    t = t->sgte;
                }
            }
        }
    }

        nodo1* z = lista;
        nodo1* w = NULL;

        goleador* y = NULL;
        goleador* r = NULL;

        while(z != NULL){
            w = z;
            z = z -> sgte;

            fe = w ->fecha;                 //En fe se guarda la fecha actual para despues imprimir
            y = w->goleadores;              //Se trae la información de los goleadores de una fecha
            cout << "El día " << fe << " se han registrado los siguientes goleadores: " << endl << endl;

            while(y != NULL){
                r = y;
                y = y -> sgte;

                cout << "El jugador " << r -> nom << " ha convertido " << r->goles << " goles, para la selección de " << V[r->cod_equipo] << endl;
            }
            cout << endl << endl;
        }
    }


//La siguiente función imprime los goleadores del mundial
    void goleadoresMundial(nodo *M[32][64], char equipos[32][20]){  //Recibe la matriz y el vector de nombres

        goleador* lista = NULL;
        goleador* g = NULL;
        char nom[40];

        int i = 0;
        int j = 0;

        for (i; i < 32; i++) {
            for (j = 0; j < 64; j++) {

                if(M[i][j] != NULL){
                    g = buscar_o_insertar(lista, M[i][j] ->info.nombre_jugador);    //Se busca el jugador
                    g->goles += M[i][j] ->info.goles;                               //se incrementa la cantidad de goles
                    g ->cod_equipo = i;                                             //Se indica el código de equipo
                }
            }
        }

        int cant = retornaCantidad(lista);  //Para la creación del vector, necesito la cantidad de goleadores
        jugador1 V[cant] = {NULL};          //Creo un vector de tal cantidad
        goleador* p = NULL;

        i = 0;
        while(lista != NULL){               //Carga del vector
            p = lista;
            strcpy(V[i].nom, p -> nom);
            V[i].goles = p -> goles;
            V[i].equipo = p -> cod_equipo;
            lista = lista -> sgte;
            delete p;
            i++;
        }

        ordenarVector(V, cant);             //Se ordena el vector

        for(i = 0; i < cant; i++){
            if(V[i].goles == 1){
                cout << "#" << i+1 << " el jugador " << V[i].nom << " convirtió " << V[i].goles << " gol para la selección de " << equipos[V[i].equipo] << endl;

            } else {
                cout << "#" << i+1 << " el jugador " << V[i].nom << " convirtió " << V[i].goles << " goles para la selección de  " << equipos[V[i].equipo] << endl;

            }
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Esta función busca y retorna un nodo en la lista
    nodo *buscar(nodo *lista, gol valor) {
        nodo *p = lista;

        while (p != NULL && p->info.fecha < valor.fecha) {
            while (p != NULL && p->info.goles < valor.id_gol) {
                p = p->sgte;
            }

            if (p != NULL && p->info.fecha < valor.fecha) {
                if (p != NULL && p->info.goles < valor.id_gol) {
                    return p;
                }

            } else {

                return NULL;

            }
        }
    }


//Esta función inserta un valor en la lista
    nodo *insertaOrdenado(nodo *&lista, jugador x) { //Eecibe como parámetros el inicio de la lista y el valor a ingresar

        nodo *q = NULL;                         //Declaro un nodo auxiliar
        nodo *p = new nodo();                   //Creo una instancia del nodo que voy a ingresar a la cola
        p->info = x;                            //A p le asigno el valor que quiero ingresar
        p -> info.goles = 0;
        if (lista == NULL || strcmp(x.nombre_jugador, lista->info.nombre_jugador) < 0) {
            p->sgte = lista;                    //Pongo el nodo al principio y le digo que el siguiente es que antes estaba en lista
            lista = p;                          //Actualizo el inicio de la lista

        } else {
            q = lista;                          //A q le doy el valor del inicio de la lista

            while (q->sgte != NULL && strcmp(x.nombre_jugador, q-> sgte ->info.nombre_jugador) > 0) {
                q = q->sgte;                    //Paso al siguiente nodo
            }
            //Una vez que llegué al lugar donde tengo que meter mi nuevo nodo
            p->sgte = q->sgte;                  //Al nodo que va a ingresar le pongo como siguiente el nodo que viene despues al que acabo de encontrar
            q->sgte = p;                        //AL nodo que acabo de encontrar le asigno como siguiente el nodo nuevo

        }

        return p;                               //Por si lo llego a necesitar, retorno el nodo recién creado
    }

//Busca y devuelve un nodo en la lista
    nodo *buscar(nodo *lista, jugador valor) {
        nodo *p = lista;

        while (p != NULL && strcmp(p->info.nombre_jugador, valor.nombre_jugador) < 0) {
            p = p->sgte;
        }

        if (p != NULL && strcmp(p->info.nombre_jugador, valor.nombre_jugador) == 0) {

            return p;

        } else {

            return NULL;

        }

    }

//Busca el nodo en la lista y si no está, lo inserta
    nodo *buscar_o_insertar(nodo *&lista, jugador valor) {

        nodo *p = buscar(lista, valor);

        if (p == NULL) {
            p = insertaOrdenado(lista, valor);
        }

        return p;
    }

    gol leerArchivo(FILE *f) {
        // punteroAlInicio(f);
        gol x;
        fread(&x, sizeof(gol), 1, f);
        return x;
    }

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

    void punteroAlInicio(FILE *f) {
        fseek(f, 0, SEEK_SET);
    }

    void cerrarArchivo(FILE *f) {
        fclose(f);
    }

    FILE *abrirArchivo(char nom[]) {
        return fopen(nom, "rb+");
    }

    int existe(char nom[], FILE *&f) {
        f = abrirArchivo(nom);
        if (f == NULL) {
            return 0;
        } else {
            return 1;
        }
    }

    nodo1 *insertaOrdenado(nodo1 *&lista, int x) {
        nodo1 *q = NULL;
        nodo1 *p = new nodo1();
        p->fecha = x;

        if (lista == NULL || x < lista->fecha) {

            p->sgte = lista;
            lista = p;

        } else {
            q = lista;


            while (q->sgte != NULL && x > q->sgte->fecha) {

                q = q->sgte;
            }

            p->sgte = q->sgte;
            q->sgte = p;
        }

        return p;
    }

//Busca y devuelve un nodo en la lista
    nodo1 *buscar(nodo1 *lista, int valor) {
        nodo1 *p = lista;

        while (p != NULL && p->fecha < valor) {
            p = p->sgte;
        }

        if (p != NULL && p->fecha == valor) {

            return p;

        } else {

            return NULL;

        }

    }

//Busca el nodo en la lista y si no está, lo inserta
    nodo1 *buscar_o_insertar(nodo1 *&lista, int valor) {

        nodo1 *p = buscar(lista, valor);

        if (p == NULL) {
            p = insertaOrdenado(lista, valor);
        }

        return p;
    }

    goleador * insertaOrdenado(goleador *&lista, char x[]) {

        goleador *q = NULL;
        goleador *p = new goleador();
        strcpy(p->nom, x);

        if (lista == NULL ||
            strcmp(x, lista->nom) < 0) {

            p->sgte = lista;
            lista = p;

        } else {
            q = lista;


            while (q->sgte != NULL && strcmp(x, q->sgte->nom) > 0) {
                q = q->sgte;
            }
            p->sgte = q->sgte;
            q->sgte = p;

        }
        return p;
    }

//Busca y devuelve un nodo en la lista
    goleador *buscar(goleador *lista, char valor[]) {
        goleador *p = lista;

        while (p != NULL && strcmp(p->nom, valor) < 0) {
            p = p->sgte;
        }

        if (p != NULL && strcmp(p->nom, valor) == 0) {

            return p;

        } else {
            return NULL;
        }

    }

//Busca el nodo en la lista y si no está, lo inserta
    goleador *buscar_o_insertar(goleador *&lista, char valor[]) {

        goleador *p = buscar(lista, valor);

        if (p == NULL) {
            p = insertaOrdenado(lista, valor);
        }

        return p;
    }

//La siguiente función retorna la cantidad de nodos de una lista
    int retornaCantidad(goleador* &lista){
        goleador* p = lista;
        goleador* q = NULL;
        int i = 0;

        while(p != NULL){ //Voy pasando nodo a nodo hasta llegar al último y voy incrementando un contador
            q = p;
            p = p -> sgte;
            i++;
        }

        return i;
    }

    void ordenarVector(jugador1 V[], int n){

        int t = 0;                  //Variable bandera, indica que terminó el ordenamiento
        int i = 0;                  //Contador i
        int j;                      //Contador j
        jugador1 aux;               //Variable auxiliar

        //Bucle while, cerrará el ciclo cuando no haya más que ordenar
        while(i <= n && t == 0){    //Pasos de ordenamiento
            t = 1;
            for(j = 1; j < n-i; j++){ //Comparaciones

                if(V[j-1].goles < V[j].goles){

                    t = 0;
                    aux = V[j];
                    V[j] = V[j-1];
                    V[j-1] = aux;
                }
            }
            i++;
        }
    }
