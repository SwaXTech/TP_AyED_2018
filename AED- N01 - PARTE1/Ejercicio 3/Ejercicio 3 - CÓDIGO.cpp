#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
using namespace std;

//Registros de selección
struct seleccion{ //Este registro es con el que se trabajó en el ejercicio 1 y 2
	int bol; //Número de bolillero
	char nom[15]; //Nombre de la selección
	char conf[15];  //Confedereación a la que pertenece
};

struct seleccion2{ //Con este registro se va a trabajar en el ejercicio 3
	char letra; //Letra de grupo 					
	char nom[15]; //Nombre de la selección
	char conf[15];  //Confedereación a la que pertenece
};

//Prototipo de función: Vectores
void leeGrupos(seleccion grupos[]); //imprime en pantalla los grupos
void imprimeOrdenado(seleccion2 v[]);
void conversion(seleccion grupos[], seleccion2 grupos2[]);


//Prototipo de función: Ordenamiento
void orden1(seleccion2 grupos[]);
void orden2(seleccion2 grupos[]);
void orden3(seleccion2 grupos[]);
void orden4(seleccion2 grupos[]);
void orden5(seleccion2 grupos[]);
	
//Prototipo de función: Archivos
FILE* abreArchivo(char nom[]); //Abre archivo nom
void leeArchivo(seleccion equipos[], FILE * f, int grupo); //Lee los datos del archivo (GRUPOS)
void leeGrupos_Archivos(seleccion grupos[], FILE * f); //Lee los archivos de los grupos
int existe(char nom[], FILE * &f); //Se comprueba la existencia de un archivo (nom)
int compruebaExistencia(FILE * f); //Se comprueba la existencia de los archivos de grupos


int main() {
	
	//Seteo de idioma al español. Permite impresión de caracteres con tilde.
	setlocale(LC_ALL, "spanish");
	
	//Declaración de vector, 32 posiciones para 32 selecciones
	seleccion grupos[32];
	seleccion2 grupos2[32]; //En este vector se almacenarán los equipos con la nueva estructura de registro
	seleccion2 ordenado[32]; //En este vector se almacenarán los equipos ordenados según el criterio elegido
	
	FILE * f = NULL;
	
	cout << "*********************************************************************************************************************" << endl;
	cout << "*********************************************************************************************************************" << endl;
	cout << "********Bienvenido al Sistema de Ordenamiento e Impresión de Equipos de Fase de Grupos del Mundial de Futbol*********" << endl;
	cout << "*********************************************************************************************************************" << endl;
	cout << "*********************************************************************************************************************" << endl;
	char itemseleccionado;
	
	int bandera = 0; //Esta variable cambiará a 1 cuando el usuario decida terminar con la ejecución del programa
	while(!bandera){ //Mientras que la variable bandera sea 0...
		
		if(compruebaExistencia(f) == 1){ //Si existen todos los archivos de equipos...
			leeGrupos_Archivos(grupos, f);
			conversion(grupos, grupos2);
			
			cout << endl;
			cout << "1. Imprimir grupos ordenados por LETRA DE GRUPO" << endl;
			cout << "2. Imprimir grupos ordenados por NOMBRE DE EQUIPO" << endl;
			cout << "3. Imprimir grupos ordenados por CONFEDERACIÓN" << endl;
			cout << "4. Imprimir grupos ordenados por LETRA DE GRUPO y CONFEDERACIÓN" << endl;
			cout << "5. Imprimir grupos ordenados por LETRA DE GRUPO, CONFEDERACIÓN y NOMBRE DE EQUIPO" << endl;
			cout << "6. Salir" << endl;
			
			cout << "Por favor ingrese una opción: ";
			cin >> itemseleccionado;
			
			if(itemseleccionado == '1'){
				
				orden1(grupos2);
				
				
			} else if(itemseleccionado == '2'){
				
				orden2(grupos2);
				
				
			} else if(itemseleccionado == '3'){
				
				orden3(grupos2);
				
				
			} else if(itemseleccionado == '4'){
				
				orden4(grupos2);
				
				
			} else if(itemseleccionado == '5'){
				
				orden5(grupos2);
				
				
			} else if(itemseleccionado == '6'){
				
				bandera = 1;
				cout << endl;
				cout << "¡Muchas gracias!, ¡Vuelva pronto!." << endl;
				cout << "Grupo N01, AyED 2018, UTN FRBA." << endl;
				
				
			} else {
				
				cout << "Por favor ingrese una opción correcta" << endl;
			}
			
		} else {
			cout << "Los archivos de equipos no existen o son erróneos. Por favor ejecute el sistema de sorteo de fase de grupos." << endl;
			bandera = 1;
		}
	
	}

	system("pause");//Esta instrucción es para que cuando el programa es usado desde el Ejecutable (.exe) en lugar de ejecutarlo desde el compilador,
	                //la consola se cierre después de presionar una tecla, para que el usuairo termine de leer lo último que se ha impreso.
	return 0;
}

////////////////////////////////////////////////////////////////VECTORES/////////////////////////////////////////////////////////////////////////////////////

 void leeGrupos(seleccion grupos[]){ //impresión en pantalla de grupos
 	int i = 0; //Contador
	char letraGrupo; //variable para identificar al grupo
	
 	int j = 0;
 	for(i; i < 8; i++){
 		if(i == 0){
 			letraGrupo = 'A';
		 } else if(i == 1){
 			letraGrupo = 'B';
		 } else if(i == 2){
 			letraGrupo = 'C';
		 } else if(i == 3){
 			letraGrupo = 'D';
		 } else if(i == 4){
 			letraGrupo = 'E';
		 } else if(i == 5){
 			letraGrupo = 'F';
		 } else if(i == 6){
 			letraGrupo = 'G';
		 } else if(i == 7){
 			letraGrupo = 'H';
		 }	
	
		cout << "Grupo " << letraGrupo << "(" << i << ")" << ": " << endl;	//GRUPO A 0 - 3      	GRUPO E 16 - 19         
 		for(j; j < (4*i + 4); j++){                                         //GRUPO B 4 - 7 		GRUPO F 20 - 23
 			cout << grupos[j].nom <<"(" <<grupos[j].conf << ")" << endl;	//GRUPO C 8 - 11        GRUPO G 24- 27
	 	}         															//GRUPO D 12 - 15       GRUPO H 28 - 31
	 	//Luego de imprimir cada grupo, la variable 'j' mantiene su valor
	 	//siendo la primera posición de cada grupo
	 	//i es el grupo, [(4*i)+4] es la primer posición del siguiente grupo
	 	cout << endl;
	 }
 	return;
 }
 
 void imprimeOrdenado(seleccion2 v[]){
 	int i = 0;
 	for(i; i < 32; i++){
 		cout << endl;
 		cout << (i+1) << ". "<< v[i].nom << " (" << v[i].conf << ") " << " [Grupo " << v[i].letra << "]"<< endl;
	 }
 	return;
 }

void conversion(seleccion grupos[], seleccion2 grupos2[]){
	
	int i = 0;
	for(i; i < 32; i++){
		strcpy(grupos2[i].nom, grupos[i].nom); //Se almacena el nombre del equipo en la posición i
		strcpy(grupos2[i].conf, grupos[i].conf); //Se almacena la confederación del equipo en la posición i
		
		if(i < 4){ 						//Del 0 al 3 inclusive se encuentra el grupo A
			grupos2[i].letra = 'A';
		} else if(i < 8){ 				//Del 4 al 7 inclusive se encuentra el grupo B
			grupos2[i].letra = 'B';
		} else if(i < 12){				//Del 8 al 11 inclusive se encuentra el grupo C
			grupos2[i].letra = 'C';
		} else if(i < 16){				//Del 12 al 15 inclusive se encuentra el grupo D
			grupos2[i].letra = 'D';
		} else if(i < 20){				//Del 16 al 19 inclusive se encuentra el grupo E
			grupos2[i].letra = 'E';
		} else if(i < 24){			 	//Del 20 al 23 inclusive se encuentra el grupo F
			grupos2[i].letra = 'F';
		} else if(i < 28){				//Del 24 al 27 inclusive se encuentra el grupo G
			grupos2[i].letra = 'G';
		} else if(i < 32){ 				//Del 28 al 31 inclusive se encuentra el grupo H
			grupos2[i].letra = 'H';
		}
		
	}

	return;
}
 
 ////////////////////////////////////////////////////////////////VECTORES/////////////////////////////////////////////////////////////////////////////////////
 
 
////////////////////////////////////////////////////////////////ORDENAMIENTO//////////////////////////////////////////////////////////////////////////////////

void orden1(seleccion2 grupos[]){
	
	int t = 0; //Variable bandera, indica que terminó el ordenamiento
	int i = 0; //Contador i
	int j; //Contador j
	seleccion2 aux; //Variable auxiliar
	
	//Bucle while, cerrará el ciclo cuando no haya más que ordenar
	while(i <= 32 && t == 0){ //Pasos de ordenamiento
		t = 1; 
		for(j = 1; j < (32-i); j++){ //Comparaciones
			
			if(grupos[j-1].letra > grupos[j].letra){
				
				t = 0;
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
			}
			
		}
		i++;
	}
	
	imprimeOrdenado(grupos);
	return;
}

void orden2(seleccion2 grupos[]){ //Ordenamiento por el método de la burbuja mejorado
	
	int t = 0; //Variable bandera, indica que terminó el ordenamiento
	int i = 0; //Contador i
	int j; //Contador j
	seleccion2 aux; //Variable auxiliar
	
	//Bucle while, cerrará el ciclo cuando no haya más que ordenar
	while(i <= 32 && t == 0){ //Pasos de ordenamiento
		t = 1; 
		for(j = 1; j < (32-i); j++){ //Comparaciones
			
			if(strcmp(grupos[j-1].nom, grupos[j].nom) > 0 ){
				
				t = 0;
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
			}
			
		}
		i++;
	}
	
	imprimeOrdenado(grupos);
	return;
}

void orden3(seleccion2 grupos[]){ //Ordenamiento por el método de la burbuja mejorado
	
	int t = 0; //Variable bandera, indica que terminó el ordenamiento
	int i = 0; //Contador i
	int j; //Contador j
	seleccion2 aux; //Variable auxiliar
	
	//Bucle while, cerrará el ciclo cuando no haya más que ordenar
	while(i <= 32 && t == 0){ //Pasos de ordenamiento
		t = 1; 
		for(j = 1; j < (32-i); j++){ //Comparaciones
			
			if(strcmp(grupos[j-1].conf, grupos[j].conf) > 0 ){
				
				t = 0;
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
			}
			
		}
		i++;
	}
	imprimeOrdenado(grupos);
	return;
}

void orden4(seleccion2 grupos[]){
	
	int t = 0; //Variable bandera, indica que terminó el ordenamiento
	int i = 0; //Contador i
	int j; //Contador j
	seleccion2 aux; //Variable auxiliar
	
	//Bucle while, cerrará el ciclo cuando no haya más que ordenar
	while(i <= 32 && t == 0){ //Pasos de ordenamiento
		t = 1; 
		for(j = 1; j < (32-i); j++){ //Comparaciones
			
			if(grupos[j-1].letra > grupos[j].letra){
				t = 0;
			
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
				
			} else if(grupos[j-1].letra == grupos[j].letra){
				
				if(strcmp(grupos[j-1].conf, grupos[j].conf) > 0 ){
				
				t = 0;
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
				
				}
			}
			
		}
		i++;
	}
	imprimeOrdenado(grupos);
	return;
}

void orden5(seleccion2 grupos[]){
	
	int t = 0; //Variable bandera, indica que terminó el ordenamiento
	int i = 0; //Contador i
	int j; //Contador j
	seleccion2 aux; //Variable auxiliar
	
	//Bucle while, cerrará el ciclo cuando no haya más que ordenar
	while(i <= 32 && t == 0){ //Pasos de ordenamiento
		t = 1; 
		for(j = 1; j < (32-i); j++){ //Comparaciones
			
			if(grupos[j-1].letra > grupos[j].letra){
				t = 0;
			
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
			} else if(grupos[j-1].letra == grupos[j].letra){
				
				if(strcmp(grupos[j-1].conf, grupos[j].conf) > 0 ){
				
				t = 0;
				aux = grupos[j];
				grupos[j] = grupos[j-1];
				grupos[j-1] = aux;
				
				} else if(strcmp(grupos[j-1].conf, grupos[j].conf) == 0){
					
					if(strcmp(grupos[j-1].nom, grupos[j].nom) > 0 ){
				
						t = 0;
						aux = grupos[j];
						grupos[j] = grupos[j-1];
						grupos[j-1] = aux;
					}
				}
			}	
		}
		i++;
	}
	imprimeOrdenado(grupos);
	return;
}
////////////////////////////////////////////////////////////////ORDENAMIENTO///////////////////////////////////////////////////////////////////////////////////
 
 ////////////////////////////////////////////////////////////////ARCHIVOS////////////////////////////////////////////////////////////////////////////////////

FILE* abreArchivo(char nom[]){ //Abre un archivo binario en modo lectura y escritura
	return fopen(nom, "rb+");
}

void leeArchivo(seleccion equipos[], FILE * f, int grupo){ //Lectura de los archivos binarios [corresponde usarlo con los archivos de grupos]
	fseek(f,0,SEEK_SET); //puntero al inicio
	seleccion s; //variable auxiliar
	
	int i = grupo*4; //i inicializada en la primera posición de cada grupo.(los múltiplos de 4)
	for(i; i < (grupo*4)+4; i++){ //se almacenan los equipos de un grupo en su correspondiente posición, [(grupo*4)+4] es la primera posición del grupo siguiente
		fread(&s,sizeof(seleccion),1,f); //se lee y almacena en 's', el equipo del archivo
		equipos[i] = s; //se almacena en el vector el equipo almacenado en 's'
	}
	return;
}

void leeGrupos_Archivos(seleccion grupos[], FILE * f){ //Se leen los archivos de los grupos
	
	if(existe("Grupo A.dat", f) == 1){ //Si existe el archivo Grupo A.dat...
		leeArchivo(grupos, f, 0);  //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo B.dat", f) == 1){ //Si existe el archivo Grupo B.dat...
		leeArchivo(grupos, f, 1); //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo C.dat", f) == 1){ //Si existe el archivo Grupo C.dat...
		leeArchivo(grupos, f, 2); //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo D.dat", f) == 1){ //Si existe el archivo Grupo D.dat...
		leeArchivo(grupos, f, 3); //Se lee el archivo
		fclose(f);
	}	
	if(existe("Grupo E.dat", f) == 1){ //Si existe el archivo Grupo E.dat...
		leeArchivo(grupos, f, 4); //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo F.dat", f) == 1){ //Si existe el archivo Grupo F.dat...
		leeArchivo(grupos, f, 5); //Se lee el archivo
		fclose(f);
	}					
	if(existe("Grupo G.dat", f) == 1){ //Si existe el archivo Grupo G.dat...
		leeArchivo(grupos, f, 6); //Se lee el archivo
	}						
	if(existe("Grupo H.dat", f) == 1){ //Si existe el archivo Grupo H.dat...
		leeArchivo(grupos, f, 7); //Se lee el archivo
		fclose(f);										
	}
	
	return;
}

int existe(char nom[], FILE * &f){ //Comprueba si existe un archivo devuelve 0 si no existe, devuelve 1 si existe.
	f = abreArchivo(nom);
	if(f == NULL){
		return 0;
	} else {
		return 1;
	}
}


int compruebaExistencia(FILE * f){ //Se comprueba la existencia de los archivos de grupos
	int cant = 0; //variable auxiliar, se incrementará por cada archivo encontrado. Si están y son correctos, deberían ser 8.
	
		if(existe("Grupo A.dat", f) == 1){ //Si el archivo Grupo A.dat se logra abrir...
			cant++; //Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo B.dat", f) == 1){ //Si el archivo Grupo B.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo C.dat", f) == 1){ //Si el archivo Grupo C.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo D.dat", f) == 1){ //Si el archivo Grupo D.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo E.dat", f) == 1){ //Si el archivo Grupo E.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo F.dat", f) == 1){ //Si el archivo Grupo F.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo G.dat", f) == 1){ //Si el archivo Grupo G.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		if(existe("Grupo H.dat", f) == 1){ //Si el archivo Grupo H.dat se logra abrir...
			cant++;//Se incrementa la variable 'cant'.
			fclose(f); //se cierra el flujo
		}
		
		if(cant == 0){ //Si no existe ningun archivo...
			return 0;
		} else if(cant == 8){ //Si están todos los archivos
			return 1;
		} else { //Si hay algunos, pero no todos.
			return 2;
		}
}

////////////////////////////////////////////////////////////////ARCHIVOS////////////////////////////////////////////////////////////////////////////////////
