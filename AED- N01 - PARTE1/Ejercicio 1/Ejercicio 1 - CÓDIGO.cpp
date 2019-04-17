#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

//Registro selección
struct seleccion{
	int bol; //Número de bolillero
	char nom[15]; //Nombre de la selección
	char conf[15];  //Confedereación a la que pertenece
};

//Prototipo de funciónes: Vectores
void llenaBolilleros(seleccion bolillero[]); //Llena bolilleros automáticamente
void llenaBolilleros_usuario(seleccion bolillero[]); // Llena los bolilleros manualmente
void leeBolilleros(seleccion bolillero[]); //Imprime en pantalla os bolilleros. 


//Prototipo de funciones: Archivos
FILE* creaArchivo(char nom[]); //Crea archivo con nombre nom
FILE* abreArchivo(char nom[]); //Abre archivo nom
void guardaArchivo(seleccion equipos[], FILE * f); //Guarda datos en el archivo
void leeArchivo(seleccion equipos[], FILE * f); //Lee los datos del archivo
void eliminaArchivo(FILE * f, char nom[]); //Elimina el archivo
int existe(char nom[], FILE * &f); //Comprueba si existe un archivo
void cerrarFlujo(FILE* f); //Se cierra el flujo.


//función principal
int main() {

	//Seteo de idioma al español. Permite impresión de caracteres con tilde.
	setlocale(LC_ALL, "spanish");

	//Declaración de vector, 32 posiciones para 32 selecciones
	seleccion bolillero[32];

	FILE * f = NULL;

	cout << "**********************************************************************************************************************" << endl;
	cout << "**********************************************************************************************************************" << endl;
	cout << "******************¡Bienvenido al Sistema de Bolilleros de Equipos Clasificados al Mundial de Futbol!******************" << endl;
	cout << "**********************************************************************************************************************" << endl;
	cout << "**********************************************************************************************************************" << endl;
	char itemseleccionado;

	int bandera = 0;
	while(!bandera){ //Ciclo While, se cierra cuando el usuario no desea seguir ejecutando el programa
	
	//En las condiciones planteadas para el While y el If, se tiene en cuenta que C++ interpreta el 0 como falso y el 1 como verdadero.

		if(!existe("Equipos.dat",f)){ //Si no existe Equipos.dat...
			cout << "El archivo de bolilleros no se ha encontrado" << endl;
			cout << "1. Generar archivo con valores por defecto" << endl;
			cout << "2. Generar archivo manualmente" << endl;
			cout << "3. Salir" << endl;
			cout << "Por favor ingrese una opción: ";
			cin >> itemseleccionado;

			if(itemseleccionado == '1'){ //Si el usuario ingresa la opción 1...

				llenaBolilleros(bolillero); //Se cargan los bolilleros automáticamente.
				f = creaArchivo("Equipos.dat"); //Se crea el archivo
				guardaArchivo(bolillero, f); //Se guardan los bolilleros en el archivo
				cout << "El archivo se ha generado satisfactoriamente." << endl << endl;

			} else if(itemseleccionado == '2'){ //Si el usuario ingresa la opción 2...
			
				llenaBolilleros_usuario(bolillero); //Se llenan los bolilleros manualmente
				f = creaArchivo("Equipos.dat"); //se crea el archivo
				guardaArchivo(bolillero, f); //se guardan los bolilleros en el archivo
				cout << "Bolilleros cargados satisfactoriamente." << endl;

			} else if(itemseleccionado == '3'){ //si el usuario ingresa la opción 3...
			
				cout << endl;
				cout << "¡Muchas gracias!, ¡Vuelva pronto!.";
				cout << "Grupo N01, AyED 2018, UTN FRBA." << endl;
				bandera = 1; //Se cierra el ciclo while.
				
			} else { //Si el usuario ingresa una opción incorrecta...
			
				cout << "Por favor ingrese una opción correcta." << endl;	
			}
			
		} else { //Si se encuentra el archivo Equipos.dat...
			
			cout << "Archivo encontrado" << endl;
			cout << "1. Leer bolilleros" << endl;
			cout << "2. Eliminar archivo" << endl;
			cout << "3. Salir" << endl;
			cout << "Por favor seleccione una opción: ";
			cin >> itemseleccionado;

			if(itemseleccionado == '1'){ //Si el usuario ingresa la opción 1...
			
				leeArchivo(bolillero, f); //se lee el archivo y se carga el vector de Bolilleros
				leeBolilleros(bolillero); //se imprimen en pantalla los bolilleros
				
			}else if(itemseleccionado == '2'){ //Si el usuario ingresa la opción 2...
			
				eliminaArchivo(f,"Equipos.dat"); //Se elimina Equipos.dat
				cout << "El archivo se ha eliminado satisfactoriamente" << endl << endl;
				
			} else if (itemseleccionado == '3'){ //Si el usuario ingresa la opción 3...
			
				cout << endl;
				cout << "¡Muchas gracias!, ¡Vuelva pronto!." << endl;
				cout << "Grupo N01, AyED 2018, UTN FRBA." << endl;
				bandera = 1; //Se cierra el ciclo while
				
			} else { //Si el usuario ingresa una opción incorrecta...
			
				cout << "Por favor ingrese una opción correcta." << endl;
				
			}
		}
		cerrarFlujo(f); //Se cierra el flujo.
	}
	
	system("pause");//Esta instrucción es para que cuando el programa es usado desde el Ejecutable (.exe) en lugar de ejecutarlo desde el compilador,
	                //la consola se cierre después de presionar una tecla, para que el usuairo termine de leer lo último que se ha impreso.
	return 0;
}

/////////////////////////////////////////////////////////VECTORES//////////////////////////////////////////////////////////////////////////////////////

//Función llenaBolilleros, a cada posición del vector asigna el nombre de un país junto con su confederación y número de bolillero
void llenaBolilleros(seleccion bolillero[]){

	bolillero[0].bol = 1;
	strcpy(bolillero[0].nom, "Rusia");
	strcpy(bolillero[0].conf, "UEFA");

	bolillero[1].bol = 1;
	strcpy(bolillero[1].nom,  "Alemania");
	strcpy(bolillero[1].conf, "UEFA");

	bolillero[2].bol = 1;
	strcpy(bolillero[2].nom, "Brasil");
	strcpy(bolillero[2].conf, "Conmebol");

	bolillero[3].bol = 1;
	strcpy(bolillero[3].nom, "Portugal");
	strcpy(bolillero[3].conf, "UEFA");

	bolillero[4].bol = 1;
	strcpy(bolillero[4].nom, "Argentina");
	strcpy(bolillero[4].conf, "Conmebol");

	bolillero[5].bol = 1;
	strcpy(bolillero[5].nom, "Bélgica");
	strcpy(bolillero[5].conf, "UEFA");

	bolillero[6].bol = 1;
	strcpy(bolillero[6].nom, "Polonia");
	strcpy(bolillero[6].conf, "UEFA");

	bolillero[7].bol = 1;
	strcpy(bolillero[7].nom, "Francia");
	strcpy(bolillero[7].conf, "UEFA");

	bolillero[8].bol = 2;
	strcpy(bolillero[8].nom, "España");
	strcpy(bolillero[8].conf, "UEFA");

	bolillero[9].bol = 2;
	strcpy(bolillero[9].nom, "Perú");
	strcpy(bolillero[9].conf, "Conmebol");

	bolillero[10].bol = 2;
	strcpy(bolillero[10].nom, "Suiza");
	strcpy(bolillero[10].conf, "UEFA");

	bolillero[11].bol = 2;
	strcpy(bolillero[11].nom, "Inglaterra");
	strcpy(bolillero[11].conf, "UEFA");

	bolillero[12].bol = 2;
	strcpy(bolillero[12].nom, "Colombia");
	strcpy(bolillero[12].conf, "Conmebol");

	bolillero[13].bol = 2;
	strcpy(bolillero[13].nom, "México");
	strcpy(bolillero[13].conf, "Concacaf");

	bolillero[14].bol = 2;
	strcpy(bolillero[14].nom, "Uruguay");
	strcpy(bolillero[14].conf, "Conmebol");

	bolillero[15].bol = 2;
	strcpy(bolillero[15].nom, "Croacia");
	strcpy(bolillero[15].conf, "UEFA");

	bolillero[16].bol = 3;
	strcpy(bolillero[16].nom, "Dinamarca");
	strcpy(bolillero[16].conf, "UEFA");

	bolillero[17].bol = 3;
	strcpy(bolillero[17].nom, "Islandia");
	strcpy(bolillero[17].conf, "UEFA");

	bolillero[18].bol = 3;
	strcpy(bolillero[18].nom, "Costa Rica");
	strcpy(bolillero[18].conf, "Concacaf");

	bolillero[19].bol = 3;
	strcpy(bolillero[19].nom, "Suecia");
	strcpy(bolillero[19].conf, "UEFA");

	bolillero[20].bol = 3;
	strcpy(bolillero[20].nom, "Túnez");
	strcpy(bolillero[20].conf, "CAF");

	bolillero[21].bol = 3;
	strcpy(bolillero[21].nom, "Egipto");
	strcpy(bolillero[21].conf, "CAF");

	bolillero[22].bol = 3;
	strcpy(bolillero[22].nom, "Senegal");
	strcpy(bolillero[22].conf, "CAF");

	bolillero[23].bol = 3;
	strcpy(bolillero[23].nom, "Irán");
	strcpy(bolillero[23].conf, "AFC");

	bolillero[24].bol = 4;
	strcpy(bolillero[24].nom, "Serbia");
	strcpy(bolillero[24].conf, "UEFA");

	bolillero[25].bol = 4;
	strcpy(bolillero[25].nom, "Nigeria");
	strcpy(bolillero[25].conf, "CAF");

	bolillero[26].bol = 4;
	strcpy(bolillero[26].nom, "Australia");
	strcpy(bolillero[26].conf, "AFC");

	bolillero[27].bol = 4;
	strcpy(bolillero[27].nom, "Japón");
	strcpy(bolillero[27].conf, "AFC");

	bolillero[28].bol = 4;
	strcpy(bolillero[28].nom, "Marruecos");
	strcpy(bolillero[28].conf, "CAF");

	bolillero[29].bol = 4;
	strcpy(bolillero[29].nom, "Panamá");
	strcpy(bolillero[29].conf, "Concacaf");

	bolillero[30].bol = 4;
	strcpy(bolillero[30].nom, "Corea del Sur");
	strcpy(bolillero[30].conf, "AFC");

	bolillero[31].bol = 4;
	strcpy(bolillero[31].nom, "Arabia Saudita");
	strcpy(bolillero[31].conf, "AFC");


	return;
}

//Funcion llenaBolilleros_usuario: Se solicita al usuario ingresar el país y la confederación al que pertenece, se asigna automáticamente el bolillero.
 void llenaBolilleros_usuario(seleccion bolillero[]){

	//Condiciones para la carga de equipos.
 	cout << endl;
 	cout << "Sistema de generación manual de equipos clasificados al mundial." << endl;
 	cout << endl;
 	cout << "Por favor ingrese los paises ordenados por bolillero, comenzando por el anfitrión." << endl;
 	cout << "Por favor ingrese las confederaciones tipeadas de la siguiente manera: " << endl;
 	cout << "1. UEFA" << endl;
 	cout << "2. CAF" << endl;
 	cout << "3. AFC" << endl;
 	cout << "4. OFC" << endl;
 	cout << "5. Conmebol" << endl;
 	cout << "6. Concacaf" << endl;
 	cout << "En caso contrario, no se ejecutará correctamente el programa." << endl;
 	cout << endl;

 	int i = 0;
 	for(i; i < 32; i++){ //For para ingresar 32 países
 		cout << "Por favor ingrese el país #" << (i+1) << ": ";

 		cin.ignore(); 
		 /*getline() requiere ser precedido de ignore (cin) para detenerse a la espera de una entrada por teclado cuando no se especifica
		 */
 		cin.getline (bolillero[i].nom,15);
 		
 		/*
		 En la función desarrollada, se pretende que el usuario ingrese nombres de países clasificados al mundial, como entre ellos hay nombres
		 compuestos por más de una palabra (ej: Costa Rica, Arabia Saudita, etc), por ser una limitación del cin, no se puede guardar más que la
		 primera palabra, por tal motivo se decide usar la función cin.getline() precedido por cin.ignore, para evitar problemas a la hora de cargar
		 los bolilleros manualmente. 
		 */

 		cout << "Por favor ingrese la confederación a la que pertenece " << bolillero[i].nom << ": ";
 		cin>> bolillero[i].conf;

 		if(i <= 7){ 
 			bolillero[i].bol = 1;       //Se pide al usuario que ingrese los equipos en el orden de los bolilleros, por lo tanto, por cada vuelta
		 } else if(i <= 15){            //de for, i se incrementa en 1, con eso se puede saber a qué bolillero pertenece el equipo ingresado,
		 	bolillero[i].bol = 2;		// entre 0 y 7 el bolillero 1; entre 8 y 15 el bolillero 2; entre 16 y 23 el bolillero 3; y entre 24 y 31 el bolillero 4.
		 } else if(i <= 23){
		 	bolillero[i].bol = 3;
		 } else if (i <= 31){
		 	bolillero[i].bol = 4;
		 }

		 cout << endl;
	 }
 }

 void leeBolilleros(seleccion bolillero[]){ //Impresión en pantalla de los bolilleros

	 int i = 0; //contador
	 for(i; i < 32; i++){
	 	if(i%8 == 0){ //si 'i' es divisible por 8, entonces es la primera posición de un bolillero
	 		cout << endl;
	 		cout << "Bolillero "<< bolillero[i].bol <<": "  << endl << endl; //Imprime el título de un bolillero
		 }
		 cout << bolillero[i].nom << " (" << bolillero[i].conf << ")"<< endl; //Impresión de la selección + confederación
	 }
	 cout << endl << endl;
	return;
 }
 
 /////////////////////////////////////////////////////////VECTORES//////////////////////////////////////////////////////////////////////////////////
 
 
 /////////////////////////////////////////////////////////ARCHIVOS//////////////////////////////////////////////////////////////////////////////////////


FILE* creaArchivo(char nom[]){
	return fopen(nom, "wb+");
}

FILE* abreArchivo(char nom[]){
	return fopen(nom, "rb");
}

void guardaArchivo(seleccion equipos[], FILE * f){
	fseek(f,0,SEEK_SET);//Puntero de archivo al inicio
	fwrite(equipos,sizeof(seleccion),32,f); //Guardar el vector de tamaño 32 en el archivo
	fflush(f); //Vaciar buffer
	return;
}
void leeArchivo(seleccion equipos[], FILE * f){
	fseek(f,0,SEEK_SET); //Puntero de archivo al inicio
	fread(equipos, sizeof(seleccion),32,f); //Leer el vector de tamaño 32 del archivo
	return;
}
void eliminaArchivo(FILE * f,char nom[]){
	fclose(f); //Cerrar el flujo
	remove(nom);

	return;
}

int existe(char nom[], FILE * &f){ //Comprueba si existe un archivo devuelve 0 si no existe, devuelve 1 si existe.
	f = abreArchivo(nom); //intenta abrir el archivo de nombre 'nom'
	if(f == NULL){ // si no pudo abrir el archivo entonces f es NULL.
		return 0;
	} else {
		return 1;
	}
}

void cerrarFlujo(FILE* f){
	fclose(f);
}

//////////////////////////////////////////////ARCHIVOS//////////////////////////////////////////////////////////////////////////////////////
