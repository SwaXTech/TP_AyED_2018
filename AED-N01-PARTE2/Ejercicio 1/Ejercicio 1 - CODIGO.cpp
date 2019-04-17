#include <iostream>
#include <cstring>

using namespace std;

struct gol {                //El struct gol, es un registro que tiene los campos necesarios para identificar un gol
    int id_gol;             //Identificador único de gol
    int cod_equipo;         //Identificador único de equipo 0-31
    int fecha;              //Fecha del partido en aaaammdd
    char nombre_jugador[40];//Aunque el enunciado dice que el nombre del jugador debe contener 20 caracteres, se decide extender el límite a 40 para que entren los nombres reales de los jugadores
    int id_partido;         //Identificador único de partido
};

struct nodo {               //El struct nodo es un registro para el uso de listas.
    gol info;               //En el campo info se guarda toda la información que compete al gol
    nodo *sgte;             //En el campo sgte se guarda el puntero al siguiente nodo
};

///////////////////////////////////////////////////////////////////////
/////////////Funciones características del ejercicio//////////////////
/////////////////////////////////////////////////////////////////////

void cargarGol(FILE *, nodo *[]);

void cargaVector(char[32][20]);

void cargarGolesPorDefecto(FILE* f);

void ordenarVector(gol V[], int n);
///////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/////////////Funciones características de las listas/////////////////
////////////////////////////////////////////////////////////////////

nodo *insertaOrdenado(nodo *&, gol);

gol pop(nodo *&);

void imprimeLista(nodo* &);

///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
///////////Funciones características de los archivos/////////////
////////////////////////////////////////////////////////////////

int existe(char[], FILE *&);

FILE *abrirArchivo(char []);

FILE *crearArchivo(char []);

void grabarGol(FILE *, gol &);

void leerArchivo(FILE *, char[32][20]);

void vaciarBuffer(FILE *);

void punteroAlInicio(FILE *);

void cerrarArchivo(FILE *);

void borrarArchivo(FILE *, char[]);
/////////////////////////////////////////////////////////////////


int main() {
    setlocale(LC_ALL, "");              //Función para poder imprimir tildes en consola

    FILE *f = NULL;                     //Puntero al archivo en memoria

    char V[32][20];                     //El vector V, tendrá en su interior los nombres de los equipos, siendo el índice, el identificador único de equipo
    cargaVector(V);                     //Se carga el vector V

    nodo *goles[32] = {NULL};           //Un vector de listas, que sirve para ordenar los goles por equipo

    cout << "**************************************************************************************" << endl;
    cout << "****************Bienvenido al sistema de goles del mundial****************************" << endl;
    cout << "**************************************************************************************" << endl << endl;
    int bandera = 0;                    //Variable para el control del while
    while (!bandera) {

        char itemSeleccionado[10];      //Aquí se almacenará el item seleccionado por el usuario

        if (existe("goles.dat", f)) {   //Si existe el archivo...

            cout << "Se ha encontrado un archivo de goles:" << endl;
            cout << "1. Leer archivo" << endl;
            cout << "2. Borrar archivo" << endl;
            cout << "3. Salir" << endl;
            cout << "Por favor seleccióne una opción: ";

            cin >> itemSeleccionado;

            if (!strcmp(itemSeleccionado, "1")) {               //Si el usuario selecciona la opción 1...
                f = abrirArchivo("goles.dat");
                leerArchivo(f, V);
            } else if (!strcmp(itemSeleccionado, "2")) {        //Si el usuario selecciona la opción 2...
                borrarArchivo(f, "goles.dat");
                cout << "El archivo se ha borrado satisfactoriamente." << endl;
            } else if (!strcmp(itemSeleccionado, "3")) {        //Si el usuario selecciona la opción 3...
                bandera = 1;
            } else {                                            //Si el usuario no seleccionó ninguna de las opciones disponibles
                cout << "Por favor ingrese un valor válido" << endl;
            }

        } else {                                                //Si el archivo no se encuentra...

            cout << "El archivo no se ha encontrado: " << endl;
            cout << "1. Crear archivo manualmente" << endl;
            cout << "2. Crear archivo con valores por defecto [MUNDIAL 2018]" << endl;
            cout << "3. Salir" << endl << endl;

            cout << "Por favor seleccióne una opción: ";
            cin >> itemSeleccionado;

            if (!strcmp(itemSeleccionado, "1")) {               //Si el usuario selecciona la opción 1...
                f = crearArchivo("goles.dat");
                cargarGol(f, goles);
            } else if (!strcmp(itemSeleccionado, "2")) {        //Si el usuario selecciona la opción 2...
                f = crearArchivo("goles.dat");
                cargarGolesPorDefecto(f);

            } else if (!strcmp(itemSeleccionado, "3")) {        //Si el usuario selecciona la opción 3...
                bandera = 1;
            } else {                                            //Si el usuario no selecciona ninguna opción...
                cout << "Por favor ingrese un valor válido" << endl;
            }

        }
    }

    cerrarArchivo(f);
    return 0;
}

//La siguiente función carga gol por gol, manualmente...
void cargarGol(FILE *f, nodo *goles[]) {

    gol x;
    int valor = 0;
    char cadena[10];
    int bandera = 0;
    char seguir;
    int contador = 0;

    do {
        cout << "Por favor, ingrese el código del equipo: ";
        do {
            cin >> valor;
            //Se ingresa el código de equipo y se comprueba que sea válido

            if (valor >= 0 && valor < 31) {
                x.cod_equipo = valor;
                bandera = 1;
            } else {
                cout << "Por favor ingrese un valor válido: ";
            }

        } while (bandera == 0);

        cout << "Por favor, ingrese el código del partido: ";
        do {
            bandera = 0;
            cin >> valor;
            //Se ingresa el código de partido y se comprueba que sea válido

            if (valor >= 0 && valor < 64) {
                x.id_partido = valor;
                bandera = 1;
            } else {
                cout << "Por favor ingrese un valor válido: ";
            }

        } while (bandera == 0);

        cout << "Por favor, ingrese la fecha con el formato (DD/MM/AAAA):  ";

        do {
            bandera = 0;
            cin >> cadena; //Se ingresa la fecha DD/MM/AAAA

            if (cadena[2] == '/' && cadena[5] == '/') { //Se comprueba que el formato sea correcto
                int dia;
                int mes;
                int agno;

                dia = ((cadena[0] - '0') * 10 + (cadena[1] - '0'));
                mes = ((cadena[3] - '0') * 10 + (cadena[4] - '0'));
                agno = ((cadena[6] - '0') * 1000 + (cadena[7] - '0') * 100 + (cadena[8] - '0') * 10 +
                        (cadena[9] - '0'));

                /*
                 * El procedimiento anterior lo que hace es tomar cada uno de los caracteres en ASCII
                 * que ingresó el usuario y le resta el '0' en ASCII, que lo convierte en un entero
                 * si es el primer dígito de DD o MM se multiplica por 10 y se suma el segundo dígito
                 * en el caso del año, al primer dígito se lo multiplica por 1000, se le suma el segundo dígito
                 * multiplicado por 100, que se le suma el tercer dígito multiplicado por 10 y por ultimo
                 * se adiciona el último dígito.
                 *
                 * EJ: 12/07/2018
                 *
                 * día: 1*10 + 2 = 12
                 * mes: 0*10 + 7 = 7
                 * año: 2*1000 + 0 * 100 + 1 * 10 + 8 = 2018
                 * */

                if (dia > 0 && dia <= 31) { //Si el día es correcto...
                    if (mes > 0 && mes <= 12) { //Si el mes es correcto...
                        if ((agno - 30) % 4 == 0) { //Si el año corresponde con un año válido de mundial...
                            //Para esta condición se tiene en cuenta que el primer mundial se realizó en 1930
                            //Y se hace cada 4 años, por lo tanto si a cada año se le resta 30, debe ser múltiplo de 4

                            //Para convertirlo a aaaammdd:
                            agno *= 10000;
                            x.fecha = (dia + mes * 100 + agno);
                            bandera = 1;
                        }
                    }
                }
            }

            if (!bandera) {
                cout << "Por favor ingrese un valor válido: ";
            }

        } while (!bandera);

        cout << "Por favor, ingrese el nombre del jugador: ";
        //cin >> x.nombre_jugador; //Ingreso del nombre del jugador
        cin.ignore(); 				
        cin.getline (x.nombre_jugador,40);
        /*
		
		Se decide utilizar cin.ignore() y cin.getline() ya que sino no se pueden ingresar los nombres completos de los jugadores
		*/
        

        x.id_gol = contador;     //Al id_gol se le asigna el número segun orden
        contador++;

        insertaOrdenado(goles[x.cod_equipo], x); //Se inserta en la lista, ordenado según criterio solicitado

        cout << "¿Desea seguir agregando goles? (Y/N): ";
        cin >> seguir;

    } while (seguir == 'y' || seguir == 'Y');

/*  int j = 0;
    for(j;j < 32; j++){
        if(goles[j] != NULL){
            imprimeLista(goles[j]);
        }
    }
*/ //El bloque de código anterior se deja comentado para realizar algún control sobre el procesamiento de las listas

    punteroAlInicio(f);
    int i = 0;
    for (i; i < 32; i++) {
        if (goles[i] != NULL) {
            while (goles[i] != NULL) {
                gol z = pop(goles[i]);          //Se extrae de la lista el gol correspondiente al primer nodo de cada lista, asociada a cada equipo
                grabarGol(f, z);                //Se graba el gol en el archivo
            }
        }
    }
    vaciarBuffer(f);
}

//La siguiente función comprueba si existe un archivo, devuelve 1 en el caso de que si, 0 en el caso de que no
int existe(char nom[], FILE *&f) {
    f = abrirArchivo(nom);
    if (f == NULL) {
        return 0;
    } else {
        return 1;
    }
}

//La siguiente función abre un archivo para lectura y escritura
FILE *abrirArchivo(char nom[]) {
    return fopen(nom, "rb+");
}

//La siguiente función crea un archivo para escritura
FILE *crearArchivo(char nom[]) {
    return fopen(nom, "wb+");
}

//La siguiente función vacía el buffer
void vaciarBuffer(FILE *f) {
    fflush(f);
}

//La siguiente función cierra el flujo
void cerrarArchivo(FILE *f) {
    fclose(f);
}

//La siguiente función borra el archivo
void borrarArchivo(FILE *f, char nom[]) {

    if (f != NULL) {
        vaciarBuffer(f);
        cerrarArchivo(f);
        f = NULL;
    }
    remove(nom);
}

//La siguiente función pone el puntero al inicio del archivo
void punteroAlInicio(FILE *f) {
    fseek(f, 0, SEEK_SET);
}

//La siguiente función graba un registro en el archivo
void grabarGol(FILE *f, gol &x) {
    fwrite(&x, sizeof(gol), 1, f);
}

//La siguiente función lee los registros de un archivo
void leerArchivo(FILE *f, char V[32][20]) {
    punteroAlInicio(f);
    gol x;
    fread(&x, sizeof(gol), 1, f);
    while (!feof(f)) {

        cout << "El jugador: " << x.nombre_jugador << " de la selección " << V[x.cod_equipo] << " " << "(cod: " << x.cod_equipo << ")" << " metió el gol #" << x.id_gol
             << " en el partido #" << x.id_partido << " en " << x.fecha << endl;
        fread(&x, sizeof(gol), 1, f);
    };

}

//La siguiente función carga el vector de nombres de equipos
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

//La siguiente función extrae la info del primer nodo de la lista
gol pop(nodo *&lista) {

    gol valor;
    nodo *pro = lista;
    valor = pro->info;
    lista = pro->sgte;
    delete pro;

    return valor;
}

//La siguiente funcion busca un valor en la lista
nodo *buscar(nodo *lista, gol valor) {
    nodo *p = lista;

    while (p != NULL && p->info.fecha < valor.fecha) {
        while (p != NULL && p->info.id_gol < valor.id_gol) {
            p = p->sgte;
        }

        if (p != NULL && p->info.fecha < valor.fecha) {
            if (p != NULL && p->info.id_gol < valor.id_gol) {
                return p;
            }

        } else {

            return NULL;

        }
    }
}


//Función para insertar un valor en la lista
nodo *insertaOrdenado(nodo *&lista, gol x) {    //Recibe como parámetros el inicio de la lista y el valor a ingresar

    nodo *q = NULL;                             //Declaro un nodo auxiliar
    nodo *p = new nodo();                       //Creo una instancia del nodo que voy a ingresar a la cola
    p->info = x;                                //A p le asigno el valor que quiero ingresar


    if (lista == NULL || x.fecha < lista->info.fecha) {
        if (lista == NULL || x.id_gol < lista->info.id_gol) {
            p->sgte = lista;                    //Pongo el nodo al principio y le digo que el siguiente es que antes estaba en lista
            lista = p;                          //Actualizo el inicio de la lista
        }

    } else {
        q = lista;                              //A q le doy el valor del inicio de la lista

        while (q->sgte != NULL && x.fecha > q->sgte->info.fecha) {
            while (q->sgte != NULL && x.id_gol > q->sgte->info.id_gol) {
                q = q->sgte; //Paso al siguiente nodo
            }
        }

        //Una vez que llegué al lugar donde tengo que meter mi nuevo nodo
        p->sgte = q->sgte;                      //Al nodo que va a ingresar le pongo como siguiente el nodo que viene despues al que acabo de encontrar
        q->sgte = p;                            //AL nodo que acabo de encontrar le asigno como siguiente el nodo nuevo

    }
    return p;                                   //Por si lo llego a necesitar, retorno el nodo recién creado
}


//La siguiente función imprime la lista sin eliminar nodos
void imprimeLista(nodo* &lista){

    nodo* x = lista;
    int i = 0;

    while(x != NULL){

        cout << "El jugador: " << x -> info.nombre_jugador << " del equipo #" << x -> info.cod_equipo << " metió el gol #" << x -> info.id_gol
             << " en el partido #" << x -> info.id_partido << "en " << x -> info.fecha << endl;
        x = x -> sgte;
        i++;
    }

}

//La siguiente funcion carga los goles por defecto
void cargarGolesPorDefecto(FILE* f){
    gol V[169];

    V[0].cod_equipo = 0;
    V[0].fecha = 20180614;
    strcpy(V[0].nombre_jugador, "Yuri Gazinski");
    V[0].id_partido = 0;

    V[1].cod_equipo = 0;
    V[1].fecha = 20180614;
    strcpy(V[1].nombre_jugador, "Denís Chéryshev");
    V[1].id_partido = 0;

    V[2].cod_equipo = 0;
    V[2].fecha = 20180614;
    strcpy(V[2].nombre_jugador, "Dzyuba");
    V[2].id_partido = 0;

    V[3].cod_equipo = 0;
    V[3].fecha = 20180614;
    strcpy(V[3].nombre_jugador, "Denís Chéryshev");
    V[3].id_partido = 0;

    V[4].cod_equipo = 0;
    V[4].fecha = 20180614;
    strcpy(V[4].nombre_jugador, "Golovin");
    V[4].id_partido = 0;

    V[5].cod_equipo = 15;
    V[5].fecha = 20180615;
    strcpy(V[5].nombre_jugador, "José Maria Gimenez");
    V[5].id_partido = 1;

    V[6].cod_equipo = 0;
    V[6].fecha = 20180619;
    strcpy(V[6].nombre_jugador, "Ahmed Fathy");
    V[6].id_partido = 2;

    V[7].cod_equipo = 0;
    V[7].fecha = 20180619;
    strcpy(V[7].nombre_jugador, "Denís Chéryshev");
    V[7].id_partido = 2;

    V[8].cod_equipo = 0;
    V[8].fecha = 20180619;
    strcpy(V[8].nombre_jugador, "Artem Dzyuba");
    V[8].id_partido = 2;

    V[9].cod_equipo = 21;
    V[9].fecha = 20180619;
    strcpy(V[9].nombre_jugador, "Mohamed Salah");
    V[9].id_partido = 2;

    V[10].cod_equipo = 15;
    V[10].fecha = 20180620;
    strcpy(V[10].nombre_jugador, "Luis Alberto Suarez");
    V[10].id_partido = 3;

    V[11].cod_equipo = 15;
    V[11].fecha = 20180625;
    strcpy(V[11].nombre_jugador, "Luis Alberto Suarez");
    V[11].id_partido = 4;

    V[12].cod_equipo = 15;
    V[12].fecha = 20180625;
    strcpy(V[12].nombre_jugador, "Denís Chéryshev(GEC)");
    V[12].id_partido = 4;

    V[13].cod_equipo = 15;
    V[13].fecha = 20180625;
    strcpy(V[13].nombre_jugador, "Edinson Cavani");
    V[13].id_partido = 4;

    V[14].cod_equipo = 30;
    V[14].fecha = 20180625;
    strcpy(V[14].nombre_jugador, "Salman Al-Faraj");
    V[14].id_partido = 5;

    V[15].cod_equipo = 30;
    V[15].fecha = 20180625;
    strcpy(V[15].nombre_jugador, "Salman AL-Dawsari");
    V[15].id_partido = 5;

    V[16].cod_equipo = 21;
    V[16].fecha = 20180625;
    strcpy(V[16].nombre_jugador, "Mohamed Salah");
    V[16].id_partido = 5;

    V[17].cod_equipo = 23;
    V[17].fecha = 20180615;
    strcpy(V[17].nombre_jugador, "Aziz Boulhaddouz(GEC)");
    V[17].id_partido = 6;

    V[18].cod_equipo = 3;
    V[18].fecha = 20180615;
    strcpy(V[18].nombre_jugador, "Cristiano Ronaldo");
    V[18].id_partido = 7;

    V[19].cod_equipo = 3;
    V[19].fecha = 20180615;
    strcpy(V[19].nombre_jugador, "Cristiano Ronaldo");
    V[19].id_partido = 7;

    V[20].cod_equipo = 3;
    V[20].fecha = 20180615;
    strcpy(V[20].nombre_jugador, "Cristiano Ronaldo");
    V[20].id_partido = 7;

    V[21].cod_equipo = 8;
    V[21].fecha = 20180615;
    strcpy(V[21].nombre_jugador, "Diego Costa");
    V[21].id_partido = 7;

    V[22].cod_equipo = 8;
    V[22].fecha = 20180615;
    strcpy(V[22].nombre_jugador, "Diego Costa");
    V[22].id_partido = 7;

    V[23].cod_equipo = 8;
    V[23].fecha = 20180615;
    strcpy(V[23].nombre_jugador, "Nacho Fernandez Iglesias");
    V[23].id_partido = 7;

    V[24].cod_equipo = 3;
    V[24].fecha = 20180620;
    strcpy(V[24].nombre_jugador, "Cristiano Ronaldo");
    V[24].id_partido = 8;

    V[25].cod_equipo = 8;
    V[25].fecha = 20180620;
    strcpy(V[25].nombre_jugador, "Diego Costa");
    V[25].id_partido = 9;

    V[26].cod_equipo = 23;
    V[26].fecha = 20180625;
    strcpy(V[26].nombre_jugador, "Karim Ansarifard");
    V[26].id_partido = 10;

    V[27].cod_equipo = 3;
    V[27].fecha = 20180625;
    strcpy(V[27].nombre_jugador, "Ricardo Quaresma");
    V[27].id_partido = 10;

    V[28].cod_equipo = 8;
    V[28].fecha = 20180625;
    strcpy(V[28].nombre_jugador, "Isco");
    V[28].id_partido = 11;

    V[29].cod_equipo = 8;
    V[29].fecha = 20180625;
    strcpy(V[29].nombre_jugador, "Iago Aspas");
    V[29].id_partido = 11;

    V[30].cod_equipo = 27;
    V[30].fecha = 20180625;
    strcpy(V[30].nombre_jugador, "Khalid Boutaïb");
    V[30].id_partido = 11;

    V[31].cod_equipo = 27;
    V[31].fecha = 20180625;
    strcpy(V[31].nombre_jugador, "Youseff En-Nesyri");
    V[31].id_partido = 11;

    V[32].cod_equipo = 7;
    V[32].fecha = 20180616;
    strcpy(V[32].nombre_jugador, "Antonie Griezmann");
    V[32].id_partido = 12;

    V[33].cod_equipo = 7;
    V[33].fecha = 20180616;
    strcpy(V[33].nombre_jugador, "Aziz Behich(GEC)");
    V[33].id_partido = 12;

    V[34].cod_equipo = 31;
    V[34].fecha = 20180616;
    strcpy(V[34].nombre_jugador, "Mile Jedinak");
    V[34].id_partido = 12;

    V[35].cod_equipo = 16;
    V[35].fecha = 20180616;
    strcpy(V[35].nombre_jugador, "Yusuff Poulsen");
    V[35].id_partido = 13;

    V[36].cod_equipo = 16;
    V[36].fecha = 20180621;
    strcpy(V[36].nombre_jugador, "Yusuff Poulsen");
    V[36].id_partido = 14;

    V[37].cod_equipo = 31;
    V[37].fecha = 20180621;
    strcpy(V[37].nombre_jugador, "Mile Jedinak");
    V[37].id_partido = 14;

    V[38].cod_equipo = 7;
    V[38].fecha = 20180621;
    strcpy(V[38].nombre_jugador, "Kylian Mbappé");
    V[38].id_partido = 15;

    V[39].cod_equipo = 9;
    V[39].fecha = 20180626;
    strcpy(V[39].nombre_jugador, "André Carrillo");
    V[39].id_partido = 17;

    V[40].cod_equipo = 9;
    V[40].fecha = 20180626;
    strcpy(V[40].nombre_jugador, "Paolo Guerrero");
    V[40].id_partido = 17;

    V[41].cod_equipo = 4;
    V[41].fecha = 20180616;
    strcpy(V[41].nombre_jugador, "Sergio Agüero");
    V[41].id_partido = 18;

    V[42].cod_equipo = 18;
    V[42].fecha = 20180616;
    strcpy(V[42].nombre_jugador, "Alfreó Finnbogason");
    V[42].id_partido = 18;

    V[43].cod_equipo = 13;
    V[43].fecha = 20180616;
    strcpy(V[43].nombre_jugador, "Oghenekaro Etebo");
    V[43].id_partido = 19;

    V[44].cod_equipo = 13;
    V[44].fecha = 20180616;
    strcpy(V[44].nombre_jugador, "Luka Modric");
    V[44].id_partido = 19;

    V[45].cod_equipo = 13;
    V[45].fecha = 20180621;
    strcpy(V[45].nombre_jugador, "Ante Rebic");
    V[45].id_partido = 20;

    V[46].cod_equipo = 13;
    V[46].fecha = 20180621;
    strcpy(V[46].nombre_jugador, "Luka Modric");
    V[46].id_partido = 20;

    V[47].cod_equipo = 13;
    V[47].fecha = 20180621;
    strcpy(V[47].nombre_jugador, "Ivan Rakitic");
    V[47].id_partido = 20;

    V[48].cod_equipo = 25;
    V[48].fecha = 20180622;
    strcpy(V[48].nombre_jugador, "Ahmed Musa");
    V[48].id_partido = 21;

    V[49].cod_equipo = 25;
    V[49].fecha = 20180622;
    strcpy(V[49].nombre_jugador, "Ahmed Musa");
    V[49].id_partido = 21;

    V[50].cod_equipo = 25;
    V[50].fecha = 20180626;
    strcpy(V[50].nombre_jugador, "Victor Moses");
    V[50].id_partido = 22;

    V[51].cod_equipo = 4;
    V[51].fecha = 20180626;
    strcpy(V[51].nombre_jugador, "Lionel Messi");
    V[51].id_partido = 22;

    V[52].cod_equipo = 4;
    V[52].fecha = 20180626;
    strcpy(V[52].nombre_jugador, "Marcos Rojo");
    V[52].id_partido = 22;

    V[53].cod_equipo = 19;
    V[53].fecha = 20180626;
    strcpy(V[53].nombre_jugador, "Gylfi Sigurosson");
    V[53].id_partido = 23;

    V[54].cod_equipo = 13;
    V[54].fecha = 20180626;
    strcpy(V[54].nombre_jugador, "Milan Badelj");
    V[54].id_partido = 23;

    V[55].cod_equipo = 13;
    V[55].fecha = 20180626;
    strcpy(V[55].nombre_jugador, "Ivan Perisic");
    V[55].id_partido = 23;

    V[56].cod_equipo = 24;
    V[56].fecha = 20180617;
    strcpy(V[56].nombre_jugador, "Aleksandar Kolarov");
    V[56].id_partido = 24;

    V[57].cod_equipo = 2;
    V[57].fecha = 20180617;
    strcpy(V[57].nombre_jugador, "Pheilippe Coutinho");
    V[57].id_partido = 25;

    V[58].cod_equipo = 10;
    V[58].fecha = 20180617;
    strcpy(V[58].nombre_jugador, "Steven Zuber");
    V[58].id_partido = 25;

    V[59].cod_equipo = 2;
    V[59].fecha = 20180622;
    strcpy(V[59].nombre_jugador, "Pheilippe Coutinho");
    V[59].id_partido = 26;

    V[60].cod_equipo = 2;
    V[60].fecha = 20180622;
    strcpy(V[60].nombre_jugador, "Neymar");
    V[60].id_partido = 26;

    V[61].cod_equipo = 24;
    V[61].fecha = 20180622;
    strcpy(V[61].nombre_jugador, "Aleksandar Mitrovic");
    V[61].id_partido = 27;

    V[62].cod_equipo = 10;
    V[62].fecha = 20180622;
    strcpy(V[62].nombre_jugador, "Granit Xhaka");
    V[62].id_partido = 27;

    V[63].cod_equipo = 10;
    V[63].fecha = 20180622;
    strcpy(V[63].nombre_jugador, "Xherdan Shaqiri");
    V[63].id_partido = 27;

    V[64].cod_equipo = 2;
    V[64].fecha = 20180627;
    strcpy(V[64].nombre_jugador, "Paulinho");
    V[64].id_partido = 28;

    V[65].cod_equipo = 2;
    V[65].fecha = 20180627;
    strcpy(V[65].nombre_jugador, "Thiago Silva");
    V[65].id_partido = 28;

    V[66].cod_equipo = 10;
    V[66].fecha = 20180627;
    strcpy(V[66].nombre_jugador, "Blerim Dzemaili");
    V[66].id_partido = 29;

    V[67].cod_equipo = 10;
    V[67].fecha = 20180627;
    strcpy(V[67].nombre_jugador, "Josip Drmic");
    V[67].id_partido = 29;

    V[68].cod_equipo = 19;
    V[68].fecha = 20180627;
    strcpy(V[68].nombre_jugador, "Kendall Watson");
    V[68].id_partido = 29;

    V[69].cod_equipo = 19;
    V[69].fecha = 20180627;
    strcpy(V[69].nombre_jugador, "Yann Sommer");
    V[69].id_partido = 29;

    V[70].cod_equipo = 14;
    V[70].fecha = 20180618;
    strcpy(V[70].nombre_jugador, "Hirving Lozano");
    V[70].id_partido = 30;

    V[71].cod_equipo = 17;
    V[71].fecha = 20180618;
    strcpy(V[71].nombre_jugador, "Andreas Granqvist");
    V[71].id_partido = 31;

    V[72].cod_equipo = 29;
    V[72].fecha = 20180623;
    strcpy(V[72].nombre_jugador, "Son Heung-min");
    V[72].id_partido = 32;

    V[73].cod_equipo = 14;
    V[73].fecha = 20180623;
    strcpy(V[73].nombre_jugador, "Carlos Vela");
    V[73].id_partido = 32;

    V[74].cod_equipo = 14;
    V[74].fecha = 20180623;
    strcpy(V[74].nombre_jugador, "Javier Hernandez");
    V[74].id_partido = 32;

    V[75].cod_equipo = 1;
    V[75].fecha = 20180618;
    strcpy(V[75].nombre_jugador, "Marco Reus");
    V[75].id_partido = 33;

    V[76].cod_equipo = 1;
    V[76].fecha = 20180618;
    strcpy(V[76].nombre_jugador, "Toni Kroos");
    V[76].id_partido = 33;

    V[77].cod_equipo = 17;
    V[77].fecha = 20180618;
    strcpy(V[77].nombre_jugador, "Ola Toivonen");
    V[77].id_partido = 33;

    V[78].cod_equipo = 29;
    V[78].fecha = 20180627;
    strcpy(V[78].nombre_jugador, "Kim Young Gwon");
    V[78].id_partido = 34;

    V[79].cod_equipo = 29;
    V[79].fecha = 20180627;
    strcpy(V[79].nombre_jugador, "Son Heung-min");
    V[79].id_partido = 34;

    V[80].cod_equipo = 17;
    V[80].fecha = 20180627;
    strcpy(V[80].nombre_jugador, "Ludwig Augustinsson");
    V[80].id_partido = 35;

    V[81].cod_equipo = 17;
    V[81].fecha = 20180627;
    strcpy(V[81].nombre_jugador, "Andreas Granqvist");
    V[81].id_partido = 35;

    V[82].cod_equipo = 17;
    V[82].fecha = 20180627;
    strcpy(V[82].nombre_jugador, "Edson Álvarez");
    V[82].id_partido = 35;

    V[83].cod_equipo = 5;
    V[83].fecha = 20180618;
    strcpy(V[83].nombre_jugador, "Dries Mertens");
    V[83].id_partido = 36;

    V[84].cod_equipo = 5;
    V[84].fecha = 20180618;
    strcpy(V[84].nombre_jugador, "Romelu Lukaku");
    V[84].id_partido = 36;

    V[85].cod_equipo = 5;
    V[85].fecha = 20180618;
    strcpy(V[85].nombre_jugador, "Romelu Lukaku");
    V[85].id_partido = 36;

    V[86].cod_equipo = 20;
    V[86].fecha = 20180618;
    strcpy(V[86].nombre_jugador, "Ferjani Sassi");
    V[86].id_partido = 37;

    V[87].cod_equipo = 11;
    V[87].fecha = 20180618;
    strcpy(V[87].nombre_jugador, "Harry Kane");
    V[87].id_partido = 37;

    V[88].cod_equipo = 11;
    V[88].fecha = 20180618;
    strcpy(V[88].nombre_jugador, "Harry Kane");
    V[88].id_partido = 37;

    V[89].cod_equipo = 5;
    V[89].fecha = 20180623;
    strcpy(V[89].nombre_jugador, "Eden Hazard");
    V[89].id_partido = 38;

    V[90].cod_equipo = 5;
    V[90].fecha = 20180623;
    strcpy(V[90].nombre_jugador, "Romelu Lukaku");
    V[90].id_partido = 38;

    V[91].cod_equipo = 5;
    V[91].fecha = 20180623;
    strcpy(V[91].nombre_jugador, "Michy Batshuayi");
    V[91].id_partido = 38;

    V[92].cod_equipo = 5;
    V[92].fecha = 20180623;
    strcpy(V[92].nombre_jugador, "Romelu Lukaku");
    V[92].id_partido = 38;

    V[93].cod_equipo = 5;
    V[93].fecha = 20180623;
    strcpy(V[93].nombre_jugador, "Eden Hazard");
    V[93].id_partido = 38;

    V[94].cod_equipo = 20;
    V[94].fecha = 20180623;
    strcpy(V[94].nombre_jugador, "Dylan Bronn");
    V[94].id_partido = 38;

    V[95].cod_equipo = 20;
    V[95].fecha = 20180623;
    strcpy(V[95].nombre_jugador, "Wahbi Khazri");
    V[95].id_partido = 38;

    V[96].cod_equipo = 11;
    V[96].fecha = 20180624;
    strcpy(V[96].nombre_jugador, "Jhon Stones");
    V[96].id_partido = 39;

    V[97].cod_equipo = 11;
    V[97].fecha = 20180624;
    strcpy(V[97].nombre_jugador, "Jhon Stones");
    V[97].id_partido = 39;

    V[98].cod_equipo = 11;
    V[98].fecha = 20180624;
    strcpy(V[98].nombre_jugador, "Harry Kane");
    V[98].id_partido = 39;

    V[99].cod_equipo = 1;
    V[99].fecha = 20180624;
    strcpy(V[99].nombre_jugador, "Harry Kane");
    V[99].id_partido = 39;

    V[100].cod_equipo = 11;
    V[100].fecha = 20180624;
    strcpy(V[100].nombre_jugador, "Harry Kane");
    V[100].id_partido = 39;

    V[101].cod_equipo = 11;
    V[101].fecha = 20180624;
    strcpy(V[101].nombre_jugador, "Jesse Lingard");
    V[101].id_partido = 39;

    V[102].cod_equipo = 28;
    V[102].fecha = 20180624;
    strcpy(V[102].nombre_jugador, "Felipe Baloy");
    V[102].id_partido = 39;

    V[103].cod_equipo = 25;
    V[103].fecha = 20180628;
    strcpy(V[103].nombre_jugador, "Adnan Januzaj");
    V[103].id_partido = 40;

    V[104].cod_equipo = 28;
    V[104].fecha = 20180628;
    strcpy(V[104].nombre_jugador, "Yassine Meriah[GEC]");
    V[104].id_partido = 41;

    V[105].cod_equipo = 20;
    V[105].fecha = 20180628;
    strcpy(V[105].nombre_jugador, "Fakhreddine Ben Youssef");
    V[105].id_partido = 41;

    V[106].cod_equipo = 20;
    V[106].fecha = 20180628;
    strcpy(V[106].nombre_jugador, "Wahbi Khazri");
    V[106].id_partido = 41;

    V[107].cod_equipo = 12;
    V[107].fecha = 20180619;
    strcpy(V[107].nombre_jugador, "Juan Fernando Quintero");
    V[107].id_partido = 42;

    V[108].cod_equipo = 26;
    V[108].fecha = 20180619;
    strcpy(V[108].nombre_jugador, "Shiniji Kagawa");
    V[108].id_partido = 42;

    V[109].cod_equipo = 26;
    V[109].fecha = 20180619;
    strcpy(V[109].nombre_jugador, "Yuya Osako");
    V[109].id_partido = 42;

    V[110].cod_equipo = 6;
    V[110].fecha = 20180619;
    strcpy(V[110].nombre_jugador, "Grezegorz Krychowiak");
    V[110].id_partido = 43;

    V[111].cod_equipo = 22;
    V[111].fecha = 20180619;
    strcpy(V[111].nombre_jugador, "Thiago Rangel Cionek");
    V[111].id_partido = 43;

    V[112].cod_equipo = 22;
    V[112].fecha = 20180619;
    strcpy(V[112].nombre_jugador, "M'Baye Niang");
    V[112].id_partido = 43;

    V[113].cod_equipo = 26;
    V[113].fecha = 20180624;
    strcpy(V[113].nombre_jugador, "Takashi Inui");
    V[113].id_partido = 44;

    V[114].cod_equipo = 26;
    V[114].fecha = 20180624;
    strcpy(V[114].nombre_jugador, "Keisuke Honda");
    V[114].id_partido = 44;

    V[115].cod_equipo = 22;
    V[115].fecha = 20180624;
    strcpy(V[115].nombre_jugador, "Sadio Mané");
    V[115].id_partido = 44;

    V[116].cod_equipo = 22;
    V[116].fecha = 20180624;
    strcpy(V[116].nombre_jugador, "Moussa Wagué");
    V[116].id_partido = 44;

    V[117].cod_equipo = 12;
    V[117].fecha = 20180624;
    strcpy(V[117].nombre_jugador, "Yerry Mina");
    V[117].id_partido = 45;

    V[118].cod_equipo = 12;
    V[118].fecha = 20180624;
    strcpy(V[118].nombre_jugador, "Radamel Falcao");
    V[118].id_partido = 45;

    V[119].cod_equipo = 12;
    V[119].fecha = 20180624;
    strcpy(V[119].nombre_jugador, "Juan Guillermo Cuadrado");
    V[119].id_partido = 45;

    V[120].cod_equipo = 12;
    V[120].fecha = 20180624;
    strcpy(V[120].nombre_jugador, "Jan Bednarek");
    V[120].id_partido = 46;

    V[121].cod_equipo = 12;
    V[121].fecha = 20180628;
    strcpy(V[121].nombre_jugador, "Yerry Mina");
    V[121].id_partido = 47;

    V[122].cod_equipo = 15;
    V[122].fecha = 20180630;
    strcpy(V[122].nombre_jugador, "Edinson Cavani");
    V[122].id_partido = 48;

    V[123].cod_equipo = 15;
    V[123].fecha = 20180630;
    strcpy(V[123].nombre_jugador, "Edinson Cavani");
    V[123].id_partido = 48;

    V[124].cod_equipo = 3;
    V[124].fecha = 20180630;
    strcpy(V[124].nombre_jugador, "Pepe");
    V[124].id_partido = 48;

    V[125].cod_equipo = 7;
    V[125].fecha = 20180630;
    strcpy(V[125].nombre_jugador, "Antonie Griezmann");
    V[125].id_partido = 49;

    V[126].cod_equipo = 7;
    V[126].fecha = 20180630;
    strcpy(V[126].nombre_jugador, "Benjamin Pavard");
    V[126].id_partido = 49;

    V[127].cod_equipo = 7;
    V[127].fecha = 20180630;
    strcpy(V[127].nombre_jugador, "Kylian Mbappé");
    V[127].id_partido = 49;

    V[128].cod_equipo = 7;
    V[128].fecha = 20180630;
    strcpy(V[128].nombre_jugador, "Kylian Mbappé");
    V[128].id_partido = 49;

    V[129].cod_equipo = 4;
    V[129].fecha = 20180630;
    strcpy(V[129].nombre_jugador, "Ángel Di María");
    V[129].id_partido = 49;

    V[130].cod_equipo = 4;
    V[130].fecha = 20180630;
    strcpy(V[130].nombre_jugador, "Gabriel Mercado");
    V[130].id_partido = 49;

    V[131].cod_equipo = 4;
    V[131].fecha = 20180630;
    strcpy(V[131].nombre_jugador, "Sergio Agüero");
    V[131].id_partido = 49;

    V[132].cod_equipo = 2;
    V[132].fecha = 20180702;
    strcpy(V[132].nombre_jugador, "Neymar");
    V[132].id_partido = 50;

    V[133].cod_equipo = 2;
    V[133].fecha = 20180702;
    strcpy(V[133].nombre_jugador, "Roberto Firmino");
    V[133].id_partido = 50;

    V[134].cod_equipo = 5;
    V[134].fecha = 20180702;
    strcpy(V[134].nombre_jugador, "Jan Vertoghen");
    V[134].id_partido = 51;

    V[135].cod_equipo = 5;
    V[135].fecha = 20180702;
    strcpy(V[135].nombre_jugador, "Marouane Fellaini");
    V[135].id_partido = 51;

    V[136].cod_equipo = 5;
    V[136].fecha = 20180702;
    strcpy(V[136].nombre_jugador, "Nacer Chadili");
    V[136].id_partido = 51;

    V[137].cod_equipo = 26;
    V[137].fecha = 20180702;
    strcpy(V[137].nombre_jugador, "Genki Haraguchi");
    V[137].id_partido = 51;

    V[138].cod_equipo = 26;
    V[138].fecha = 20180702;
    strcpy(V[138].nombre_jugador, "Takashi Inui");
    V[138].id_partido = 51;

    V[139].cod_equipo = 8;
    V[139].fecha = 20180701;
    strcpy(V[139].nombre_jugador, "Serguei Ignashevich[GEC]");
    V[139].id_partido = 52;

    V[140].cod_equipo = 0;
    V[140].fecha = 20180701;
    strcpy(V[140].nombre_jugador, "Artiom Dziuba");
    V[140].id_partido = 52;

    V[141].cod_equipo = 13;
    V[141].fecha = 20180701;
    strcpy(V[141].nombre_jugador, "Mario Mandzukic");
    V[141].id_partido = 53;

    V[142].cod_equipo = 16;
    V[142].fecha = 20180701;
    strcpy(V[142].nombre_jugador, "Mathias Jorgensen");
    V[142].id_partido = 53;

    V[143].cod_equipo = 17;
    V[143].fecha = 20180703;
    strcpy(V[143].nombre_jugador, "Emil Forsberg");
    V[143].id_partido = 54;

    V[144].cod_equipo = 13;
    V[144].fecha = 20180703;
    strcpy(V[144].nombre_jugador, "Yerry Mina");
    V[144].id_partido = 55;

    V[145].cod_equipo = 11;
    V[145].fecha = 20180703;
    strcpy(V[145].nombre_jugador, "Harry Kane");
    V[145].id_partido = 55;

    V[146].cod_equipo = 7;
    V[146].fecha = 20180706;
    strcpy(V[146].nombre_jugador, "Raphael Varane");
    V[146].id_partido = 56;

    V[147].cod_equipo = 7;
    V[147].fecha = 20180706;
    strcpy(V[147].nombre_jugador, "Antonie Griezmann");
    V[147].id_partido = 56;

    V[148].cod_equipo = 2;
    V[148].fecha = 20180706;
    strcpy(V[148].nombre_jugador, "Renato Augusto");
    V[148].id_partido = 57;

    V[149].cod_equipo = 5;
    V[149].fecha = 20180706;
    strcpy(V[149].nombre_jugador, "Fernandinho");
    V[149].id_partido = 57;

    V[150].cod_equipo = 5;
    V[150].fecha = 20180706;
    strcpy(V[150].nombre_jugador, "Kevin De Bruyne");
    V[150].id_partido = 57;

    V[151].cod_equipo = 0;
    V[151].fecha = 20180707;
    strcpy(V[151].nombre_jugador, "Denis Cheryshev");
    V[151].id_partido = 58;

    V[152].cod_equipo = 0;
    V[152].fecha = 20180707;
    strcpy(V[152].nombre_jugador, "Mario Figueira");
    V[152].id_partido = 58;

    V[153].cod_equipo = 13;
    V[153].fecha = 20180707;
    strcpy(V[153].nombre_jugador, "Andrej Kramaric");
    V[153].id_partido = 58;

    V[154].cod_equipo = 13;
    V[154].fecha = 20180707;
    strcpy(V[154].nombre_jugador, "Domagoj Vida");
    V[154].id_partido = 58;

    V[155].cod_equipo = 11;
    V[155].fecha = 20180707;
    strcpy(V[155].nombre_jugador, "Harry Maguire");
    V[155].id_partido = 59;

    V[156].cod_equipo = 11;
    V[156].fecha = 20180707;
    strcpy(V[156].nombre_jugador, "Bamidele Alli");
    V[156].id_partido = 59;

    V[157].cod_equipo = 7;
    V[157].fecha = 20180710;
    strcpy(V[157].nombre_jugador, "Samuel Umtiti");
    V[157].id_partido = 60;


    V[158].cod_equipo = 13;
    V[158].fecha = 20180711;
    strcpy(V[158].nombre_jugador, "Ivan Perisic");
    V[158].id_partido = 61;

    V[159].cod_equipo = 13;
    V[159].fecha = 20180711;
    strcpy(V[159].nombre_jugador, "Mario Mandzukic");
    V[159].id_partido = 61;

    V[160].cod_equipo = 11;
    V[160].fecha = 20180711;
    strcpy(V[160].nombre_jugador, "Kieran Trippier");
    V[160].id_partido = 61;

    V[161].cod_equipo = 5;
    V[161].fecha = 20180714;
    strcpy(V[161].nombre_jugador, "Thomas Meunier");
    V[161].id_partido = 62;

    V[162].cod_equipo = 5;
    V[162].fecha = 20180714;
    strcpy(V[162].nombre_jugador, "Eden Hazard");
    V[162].id_partido = 62;


    V[163].cod_equipo = 7;
    V[163].fecha = 20180715;
    strcpy(V[163].nombre_jugador, "Mario Mandzukic[GEC]");
    V[163].id_partido = 63;


    V[164].cod_equipo = 7;
    V[164].fecha = 20180715;
    strcpy(V[164].nombre_jugador, "Antonie Griezmann");
    V[164].id_partido = 63;


    V[165].cod_equipo = 7;
    V[165].fecha = 20180715;
    strcpy(V[165].nombre_jugador, "Paul Pogba");
    V[165].id_partido = 63;


    V[166].cod_equipo = 7;
    V[166].fecha = 20180715;
    strcpy(V[166].nombre_jugador, "Kylian Mbappé");
    V[166].id_partido = 63;


    V[167].cod_equipo = 13;
    V[167].fecha = 20180715;
    strcpy(V[167].nombre_jugador, "Ivan Perisic");
    V[167].id_partido = 63;

    V[168].cod_equipo = 13;
    V[168].fecha = 20180715;
    strcpy(V[168].nombre_jugador, "Mario Mandzukic");
    V[168].id_partido = 63;

    int i = 0;
    for(i; i < 169; i++){
        V[i].id_gol = i;
    }

    ordenarVector(V, 169); //Se ordena el vector
    punteroAlInicio(f);
    int j = 0;
    for (j; j < 169; j++) {
        grabarGol(f, V[j]);
    }
    vaciarBuffer(f);
}

//La siguiente función ordena el vector por el método de la burbuja
void ordenarVector(gol V[], int n){

    int t = 0;                      //Variable bandera, indica que terminó el ordenamiento
    int i = 0;                      //Contador i
    int j;                          //Contador j
    gol aux;                        //Variable auxiliar

    //Bucle while, cerrará el ciclo cuando no haya más que ordenar
    while(i <= n && t == 0){        //Pasos de ordenamiento
        t = 1;
        for(j = 1; j<n-i; j++){     //Comparaciones

            if(V[j-1].cod_equipo > V[j].cod_equipo){ //Ordenamiento por código de equipo
                t = 0;
                aux = V[j];
                V[j] = V[j-1];
                V[j-1] = aux;
            } else if(V[j-1].cod_equipo == V[j].cod_equipo){ //Si es igual...

                if(V[j-1].fecha > V[j].fecha){               //Se ordena por fecha
                    t = 0;
                    aux = V[j];
                    V[j] = V[j-1];
                    V[j-1] = aux;
                } else if(V[j-1].fecha == V[j].fecha){       //Si la fecha es igual...
                    if(V[j-1].id_gol > V[j].id_gol){         //se ordena por id de gol
                        t = 0;
                        aux = V[j];
                        V[j] = V[j-1];
                        V[j-1] = aux;
                    }
                }
            }
        }
        i++;
    }
}


