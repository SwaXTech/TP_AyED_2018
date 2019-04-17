#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include<time.h>
using namespace std;

//Registro de selección
struct seleccion{
	int bol; //Número de bolillero
	char nom[15]; //Nombre de la selección
	char conf[15];  //Confedereación a la que pertenece
};

//Prototipo de función: Archivos
FILE* abreArchivo(char nom[]); //Abre archivo nom
void guardaArchivo(seleccion equipos[], FILE * f); //Guarda datos en el archivo
void leeArchivo(seleccion equipos[], FILE * f); //Lee los datos del archivo
void leeArchivo(seleccion equipos[], FILE * f, int grupo); //Lee los datos del archivo (GRUPOS)
FILE* creaArchivo(char nom[]); //Crea archivo con nombre nom
void eliminaArchivo(FILE * f, char nom[]); //Elimina el archivo
int compruebaExistencia(FILE * f); //Se comprueba la existencia de los archivos de grupos
void eliminaGrupos(FILE * f); //elimina los archivos de los grupos
void leeGrupos_Archivos(seleccion grupos[], FILE * f); //Lee los archivos de los grupos
int existe(char nom[], FILE * &f); //Se comprueba la existencia de un archivo
void cerrarFlujo(FILE* f); //Se cierra el flujo.

//Prototipo de función: Vectores
void leeBolilleros(seleccion bolillero[]); //imprime en pantalla los bolilleros
void rellenaConVacio(seleccion vector[]); //rellena los vectores con "" y 0
void leeGrupos(seleccion grupos[]); //imprime en pantalla los grupos


//Prototipo de funcion: Sorteo
void sorteo(seleccion bolillero[], seleccion grupos[]); //Pasos del sorteo
void pasoUno(seleccion bolillero[], seleccion grupos[]); //primer paso
void pasosSiguientes(seleccion bolillero[], seleccion grupos[], int paso); //pasos 2, 3 y 4
int validacion(seleccion grupos[]); //verifica si se cumple la condición


int main(){
	//Seteo de idioma al español. Permite impresión de caracteres con tilde.
	setlocale(LC_ALL, "spanish");
	
	//Semilla para la generación de números aleatorios
	srand(time(NULL));
	
	//Declaración de vector, 32 posiciones para 32 selecciones
	seleccion bolillero[32];
	seleccion grupos[32];
 		
	FILE * f;
	cout << "*********************************************************************************************************************" << endl;
	cout << "*********************************************************************************************************************" << endl;
	cout << "**********************¡Bienvenido al Sistema de Sorteo de Fase de Grupos del Mundial de Futbol!**********************" << endl;
	cout << "*********************************************************************************************************************" << endl;
	cout << "*********************************************************************************************************************" << endl;
	char itemseleccionado;
	
	int bandera = 0; //Esta variable cambiará a 1 cuando el usuario decida terminar con la ejecución del programa
	while(!bandera){ //Mientras que la variable bandera sea 0...
		
			if(compruebaExistencia(f) == 1){ //Si se encuentran todos los archivos de grupos...
				cout << "Los archivos de grupos ya se encuentran generados." <<endl;
				cout << "1. Leer grupos" << endl;
				cout << "2. Eliminar archivos" << endl;
				cout << "3. Salir" << endl;
				cout << "Por favor ingrese una opción: ";
				
				cin >> itemseleccionado;
				cout << endl;
				
				if(itemseleccionado == '1'){ //Si el usuario seleccionó la opción 1...
					
					leeGrupos_Archivos(grupos, f); //Lectura de los 8 archivos de grupos
					leeGrupos(grupos); //Impresión en pantalla de los 8 grupos
					
				} else if(itemseleccionado == '2'){ //Si el usuario seleccionó la opción 2...
					
						eliminaGrupos(f);	//Eliminación de los archivos de grupos existentes
				
			} else if(itemseleccionado == '3'){ //Si el usuario seleccionó la opción 3...
				bandera = 1; //Con bandera = 1 se termina la ejecución
				cout << "¡Muchas gracias!, ¡Vuelva pronto!." << endl;
				cout << "Grupo N01, AyED 2018, UTN FRBA." << endl;
				
			}else{ //si el usuario no seleccionó ni 1 ni 2 ni 3...
				cout << "Por favor ingrese una opción correcta" << endl;
				
			}
				
			} else if(compruebaExistencia(f) == 2){ //Si encuentra algunos archivos pero no todos...
	
						eliminaGrupos(f); //Eliminación de los archivos de grupos existentes
					
			} else if(compruebaExistencia(f) == 0){ //Si no hay ningun archivo de grupos...
		
				if(existe("Equipos.dat", f) == 0){ //Si NO existe el archivo Equipos.dat ...
					cout << "El archivo no se ha encontrado, por favor ejecute el generador de bolilleros y asegúrese de que el archivo 'Equipos.dat' haya sido copiado correctamente." << endl;
					cout << "Para más información lea el instructivo." << endl;
					bandera = 1; //No se puede continuar si el archivo con los bolilleros, se termina la ejecución
					
				} else { //Si existe el archivo Equipos.dat
			
					leeArchivo(bolillero, f); //Se lee el archivo y se almacena en el vector bolillero
			
					cout << "Archivo de bolilleros encontrado" << endl;
					cout << "1. Leer bolilleros" << endl;
					cout << "2. Sortear" << endl;
					cout << "3. Salir" << endl;
					cout << "Por favor ingrese una opción: ";
					
					cin >> itemseleccionado;
					cout << endl;
			
					if(itemseleccionado == '1'){ //Si el usuario seleccionó 1...
					
						leeBolilleros(bolillero); //Impresión en pantalla de bolilleros
						
					}else if(itemseleccionado == '2'){ //Si el usuario seleccionó 2...
							sorteo(bolillero, grupos); //Ejecución del sorteo
							leeGrupos(grupos); //Impresión en pantalla de los grupos
				
							cout << "¿Desea guardar los resultados del sorteo?" << endl;
							cout << "1. Si" << endl;
							cout << "2. No" << endl;
							cout << "Por favor ingrese una opción: ";
				
							int b = 0;
							while(!b){ //While para evitar que el usuario ingrese una opción incorrecta.
								
								cin >> itemseleccionado;
								cout << endl;
								if(itemseleccionado == '1'){ //Si el usuario seleccionó la opción 1...
								
								guardaArchivo(grupos, f); //se guardan los grupos en archivos
								b = 1;
								
								}else if(itemseleccionado == '2'){ //Si el usuario seleccionó la opción 2...
								
								 b = 1; //Vuelta al inicio
								 
								} else {
									
									cout << "Por favor ingrese una opción correcta: ";
									
								}
								
							}
							
							
					} else if (itemseleccionado == '3'){ //si el usuario seleccionó la opción 3...
							cout << "¡Muchas gracias!, ¡Vuelva pronto!." << endl;
							cout << "Grupo N01, AyED 2018, UTN FRBA." << endl;
							bandera = 1; //El usuario decidió terminar la ejecución
							
					} else { //Si el usuario no seleccionó ni 1, ni 2, ni 3...
						cout << "Por favor ingrese una opción correcta." << endl;
					}
				}	
			}
		cerrarFlujo(f);
	}
	
	system("pause"); //Esta instrucción es para que cuando el programa es usado desde el Ejecutable (.exe) en lugar de ejecutarlo desde el compilador,
	                //la consola se cierre después de presionar una tecla, para que el usuairo termine de leer lo último que se ha impreso.
	return 0; //Finalización de la ejecución
}

////////////////////////////////////////////////////////////////SORTEO///////////////////////////////////////////////////////////////////////////////////////
 
 void sorteo(seleccion bolillero[], seleccion grupos[]){ //Ejecución del sorteo paso a paso
 	
 	rellenaConVacio(grupos); //Los vectores se llenan con 0 y "" para evitar errores.
 	pasoUno(bolillero, grupos); //El primer paso sortea los equipos del primer bolillero. (0)
 	pasosSiguientes(bolillero, grupos, 1); //El segundo paso sortea los equipos del segundo bolillero (1)
 	pasosSiguientes(bolillero, grupos, 2); //El tercer paso sortea los equipos del tercer bolillero (2)
 	pasosSiguientes(bolillero, grupos, 3); //El cuarto paso sortea los equipos del cuarto bolillero (3)
 	
 	/*
	 A pesar de que en el enunciado separa en consigna al paso 2 y paso 3, en este caso se ejecutan de igual manera, ya que en el programa 
	 de generación de bolilleros, se da la opción al usuario de cargar los equipos manualmente (para futuros mundiales),
	 entonces puede haber variaciones que causen que  si se plantea un algoritmo diferente, no se pueda ejecutar correctamente.
	 */
 	
 	return; 
 }
 
 void pasoUno(seleccion bolillero[], seleccion grupos[]){
 	
 	grupos[0] = bolillero[0]; //El anfitrión, ubicado en la primera posición del vector, se ubicará como cabeza en el grupo A.
 	
 	int num_sorteado = 0; //Variable que almacena el número aleatorio generado por la función rand()
 	
 	int i = 1; //contador comenzando en 1, ya que el equipo N°0 ya está ubicado por ser el anfitrión
 	
 	while(i <= 7){ //Sorteo de los 7 equipos restantes del primer bolillero
 		
 		num_sorteado = rand()%8; //Número al azar de 0 a 7
 		
 		if(num_sorteado != 0){ //Porque el grupo A ya está ocupado
 			if(strcmp(grupos[(4*num_sorteado)].nom, "") == 0){ // 4*num_sorteado es la primera posición de cada grupo
 				grupos[(4*num_sorteado)] = bolillero[i]; 
 				i++;
 				
 				/*Los equipos restantes (del 1 al 7 inclusive), se sortean, cada grupo se identificará con un número del 0 al 7
 				siguiendo el orden del abcedario (0 para el grupo A, 1 para el grupo B, etc)
				Una vez que se obtiene el número aleatorio, se verifica si el grupo que tocó se encuentra disponible para el equipo
				
				Ej: Si el número aleatorio es 3, corresponde al grupo D. El grupo D tiene dominio en el vector 'grupos' desde
				la posición (3*4) = 12 hasta [(3*4)+4] = 16 (no inclusive). [12;16)
				
				En el caso del primer paso, se revisa que en la posición 4*num_sorteado, en el caso del ejemplo: 12
				no haya ningun equipo registrado. Se compara con la función strcmp. Si el campo 'nom' de la posición del vector
				a evaluar, se encuentra vacía, o sea que es igual a "", entonces se procede a almacenar el equipo que estamos evaluando en
				aquella posición. */
			}
		}
		 
	}
	
 return;
 }
 																			//paso = num de bolillero
 void pasosSiguientes(seleccion bolillero[], seleccion grupos[], int paso){ //'paso' varía entre 1 y 3, teniendo en cuenta que se comienza a contar desde el 0.
 																			//El número de paso corresponde al bolillero a sortear
 	
 	int num_sorteado = 0; //Variable que almacena el número aleatorio generado por la función rand()
 	int b = 0; //bandera
 	int i = 0; //contador
 	do{
 		i = (8*paso); //El puntero irá a la primera posición del bolillero a sortear.
 		/*El vector bolillero se encuentra ordenado por bolilleros, siendo un múltiplo de 8, los primeros equipos de cada bolillero.
 		
 		EJ: el tercer bolillero (que corresponde al bolillero n°2 comenzando a contar desde el 0) tiene dominio desde
 		(8*2) = 16 hasta [(8*2)+8] = 24 (no inclusive) [16;24)*/
 		
 		int j = 0;
 		for(j; j < 8; j++){
 			strcpy(grupos[(j*4)+ paso].nom, "");
 		/*	Este for limpia los campos nom de la posición de cada grupo que se está evaluando.
 			si al concluir con el sorteo, al realizar la validación resulta que no cumple con las reglas, el paso se debe volver a realizar
			por tal motivo y para el correcto funcionamiento del programa se procede a limpiar los campos que se desean evaluar 
			
			Los equipos del bolillero 'n', irán ubicados en la posición 'n' de cada grupo. 
			como cada bolillero corresponde al paso que se ejecuta, [(j*4)+ paso] es la posición en la que se guardarán los equipos del bolillero
			a evaluar.*/
		 }
 		
 		for(i; i < ((8*paso)+ 8); i++){ // 'i' corresponde a los equipos del bolillero que se está sorteando, cada bolillero tiene dominio desde 8*paso(i) hasta [(8*paso)+8]
 			b = 0; 
 			while(b == 0){ //El ciclo se ejecutará hasta que se sortee una posición válida para el equipo que se está evaluando.
 				num_sorteado = rand()%8; //Número al azar de 0 a 7
 			
 				if(strcmp(grupos[(4*num_sorteado)+ paso].nom, "") == 0){ 
 					grupos[(4*num_sorteado) + paso] = bolillero[i];
 					b++;
			 	}
			}
			
			/*[(4*num_sorteado) + paso] es la posición de cada grupo que se está sorteando.
			EJ: Si el número sorteado es 3, corresponde al grupo D.
			El grupo D tiene dominio en el vector 'grupos' desde (4*3) hasta [(4*3)+4] --> [12;16)
			Al multiplicar el número sorteado por 4, nos paramos en la primera posición del grupo que tocó; y al sumar el paso en el que estamos
			nos corremos hasta la posición que corresponde, si estamos sorteando el cuarto bolillero (N°3) el equipo que se sorteó se almacenará en [(4*3)+ 3] = 15
			que es la última posición del grupo D.
			  */
		 }
	 }while(validacion(grupos) != 0); //Mientras que se validen los resultados...
	 
	 return;
 }
 
 int validacion(seleccion grupos[]){ //Los grupos no pueden tener dos equipos de la misma confederación, excepto UEFA, con la posibilidad de tener 2 por grupo.
 	
 	int i = 0; //Contador
 	int validado = 0; //Variable a retornar. Se incrementará en 1 por cada grupo que no cumpla con la condición
	for(i; i < 8; i++){
		
		//Cupos de cada confederación
		int UEFA = 0;
		int Concacaf = 0;
		int Conmebol = 0;
		int AFC = 0;
		int CAF = 0;
		int OFC = 0;
	
		int j = (i*4); //j se inicializará en la primera posición de cada grupo, que son los múltiplos de 4.
		for(j; j < ((i*4)+4); j++){ //desde la primera posición de cada grupo, hasta la última [(i*4)+4] no inclusive 
			if(strcmp(grupos[j].conf, "UEFA") == 0){
				UEFA++;
			}
			if(strcmp(grupos[j].conf, "Conmebol") == 0){
				Conmebol++;
			}
			if(strcmp(grupos[j].conf, "Concacaf") == 0){
				Concacaf++;
			}
			if(strcmp(grupos[j].conf, "AFC") == 0){
				AFC++;
			}
			if(strcmp(grupos[j].conf, "CAF") == 0){
				CAF++;
			}
			if(strcmp(grupos[j].conf, "OFC") == 0){
				OFC++;
			}
			
			/* Se evalúa equipo por equipo de cada grupo (aunque algún campo esté vacío no afecta en el funcionamiento)
			Si el campo a evaluar tiene un equipo asignado, se revisa a qué confederación pertenece, y a esa variable se la incrementa en 1*/
		}
		
		if(UEFA > 2){ //Si UEFA tiene más de dos equipos en un mismo grupo
			validado++; //la variable se incrementa en 1
		}
		if(Conmebol > 1){ //Si Conmebol tiene más de un equipo en un mismo grupo
			validado++; //La variable se incrementa en uno
		}
		if(Concacaf > 1){//Si Concacaf tiene más de un equipo en un mismo grupo
			validado++;//La variable se incrementa en uno
		}
		if(AFC > 1){//Si AFC tiene más de un equipo en un mismo grupo
			validado++;//La variable se incrementa en uno
		}
		if(CAF > 1){ //Si CAF tiene más de un equipo en un mismo grupo
			validado++;//La variable se incrementa en uno
		}
		if(OFC > 1){ //Si OFC tiene más de un equipo en un mismo grupo
			validado++;//La variable se incrementa en uno
		}
		
	}	
 	return validado; //Si se valida el sorteo devuelve 0, cualquier otro valor en caso contrario, producto de la incrementación hecha recien
 }
 
 ////////////////////////////////////////////////////////////////SORTEO///////////////////////////////////////////////////////////////////////////////////////
 
 ////////////////////////////////////////////////////////////////VECTORES/////////////////////////////////////////////////////////////////////////////////////

 void leeBolilleros(seleccion bolillero[]){ //Impresión de bolilleros

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
	
		cout << "Grupo " << letraGrupo << ": " << endl;						//GRUPO A 0 - 3      	GRUPO E 16 - 19         
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
 
 void rellenaConVacio(seleccion vector[]){ //Esta funcion rellena los vectores con 0 y "", para evitar cualquier tipo de error durante la ejecución del programa
 	
 	int i = 0;
 	for(i; i < 32; i++){
 		strcpy(vector[i].nom,"");
 		strcpy(vector[i].conf, "");
 		vector[i].bol = 0;
	 }
 	
 	return;
 }
 
 ////////////////////////////////////////////////////////////////VECTORES/////////////////////////////////////////////////////////////////////////////////////
 
 ////////////////////////////////////////////////////////////////ARCHIVOS////////////////////////////////////////////////////////////////////////////////////

FILE* abreArchivo(char nom[]){ //Abre un archivo binario en modo lectura y escritura
	return fopen(nom, "rb+");
}

void guardaArchivo(seleccion equipos[], FILE * f){ //Guarda un archivo
	fclose(f); //Cerramos el flujo que ya no nos sirve, antes tenía a los bolilleros
	char nom[15] = ""; //nombre del grupo, será asignado como título del archivo
	int i = 0; //contador
	for(i; i < 8; i++){ //Se generan 8 archivos, cada uno con el nombre correspondiente para cada grupo
		if(i == 0){
			strcpy(nom,"Grupo A.dat");
		}
		if(i == 1){
			strcpy(nom,"Grupo B.dat");
		}
		if(i == 2){
			strcpy(nom,"Grupo C.dat");
		}
		if(i == 3){
			strcpy(nom,"Grupo D.dat");
		}
		if(i == 4){
			strcpy(nom,"Grupo E.dat");
		}
		if(i == 5){
			strcpy(nom,"Grupo F.dat");
		}
		if(i == 6){
			strcpy(nom,"Grupo G.dat");
		}
		if(i == 7){
			strcpy(nom,"Grupo H.dat");
		}
		f = creaArchivo(nom); //se crea un archivo de nombre 'nom'
		fseek(f,0,SEEK_SET); //se pone el puntero al inicio del archivo
		int j = (4*i); //la primera posición de cada grupo son los múltiplos de 4
		for(j; j < ((4*i)+ 4); j++){ // [(4*i)+4] es la primer posición del siguiente grupo
			seleccion s = equipos[j]; //variable auxiliar , se almacenará temporalmente el equipo que se guardará en el archivo  fwrite(equipos[j], sizeof(seleccion),1,f) no compila
			fwrite(&s,sizeof(seleccion),1,f); //se escribe a continuación de lo último, el equipo que se encuentra en 's'
		}
		fflush(f); //se vacía el buffer
		fclose(f); //se cierra el flujo
	}
	return;
}

void leeArchivo(seleccion equipos[], FILE * f){ //Lectura del archivo binario [corresponde usarlo con el archivo de bolilleros]
	fseek(f,0,SEEK_SET); //Puntero de archivo al inicio
	fread(equipos, sizeof(seleccion),32,f); //Leer el vector de tamaño 32 del archivo y guardarlo en 'equipos'
	return;
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

FILE* creaArchivo(char nom[]){ //se crea un archivo para escritura y lectura. Si existe otro antes, se borra.
	return fopen(nom, "wb+");
}

void eliminaArchivo(FILE * f,char nom[]){ //Se elimina el archivo de nombre 'nom'
	fclose(f); //Cerrar el flujo
	remove(nom); //remover archivo

	return;
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

void eliminaGrupos(FILE * f){ //Elimina los archivos de grupos preexistentes
	
	if(existe("Grupo A.dat", f)){ //Si existe el archivo Grupo A.dat...
		eliminaArchivo(f, "Grupo A.dat"); //Se elimina el archivo
		fclose(f); //se cierra el flujo
	}
	if(existe("Grupo B.dat", f)){ //Si existe el archivo Grupo B.dat...
		eliminaArchivo(f, "Grupo B.dat"); //Se elimina el archivo
		fclose(f); //se cierra el flujo
	}
	if(existe("Grupo C.dat", f)){ //Si existe el archivo Grupo C.dat...
		eliminaArchivo(f, "Grupo C.dat"); //Se elimina el archivo
		fclose(f); //se cierra el flujo
	}
	if(existe("Grupo D.dat", f)){ //Si existe el archivo Grupo D.dat...
		eliminaArchivo(f, "Grupo D.dat"); //Se elimina el archivo
		fclose(f); //se cierra el flujo
	}
	if(existe("Grupo E.dat", f)){ //Si existe el archivo Grupo E.dat...
		eliminaArchivo(f, "Grupo E.dat"); //Se elimina el archivo
		fclose(f); //se cierra el flujo
	}
	if(existe("Grupo F.dat", f)){ //Si existe el archivo Grupo F.dat...
		eliminaArchivo(f, "Grupo F.dat"); //Se elimina el archivo
		fclose(f); //se cierra el flujo
	}					
	if(existe("Grupo G.dat", f)){ //Si existe el archivo Grupo G.dat...
		eliminaArchivo(f, "Grupo G.dat"); //Se elimina el archivo
			fclose(f); //se cierra el flujo
	}						
	if(existe("Grupo H.dat", f)){ //Si existe el archivo Grupo H.dat...
		eliminaArchivo(f, "Grupo H.dat"); //Se elimina el archivo
		fclose(f);	//se cierra el flujo									
	}
	return;
}

void leeGrupos_Archivos(seleccion grupos[], FILE * f){ //Se leen los archivos de los grupos
	
	if(existe("Grupo A.dat", f)){ //Si existe el archivo Grupo A.dat...
		leeArchivo(grupos, f, 0);  //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo B.dat", f)){ //Si existe el archivo Grupo B.dat...
		leeArchivo(grupos, f, 1); //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo C.dat", f)){ //Si existe el archivo Grupo C.dat...
		leeArchivo(grupos, f, 2); //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo D.dat", f)){ //Si existe el archivo Grupo D.dat...
		leeArchivo(grupos, f, 3); //Se lee el archivo
		fclose(f);
	}	
	if(existe("Grupo E.dat", f)){ //Si existe el archivo Grupo E.dat...
		leeArchivo(grupos, f, 4); //Se lee el archivo
		fclose(f);
	}
	if(existe("Grupo F.dat", f)){ //Si existe el archivo Grupo F.dat...
		leeArchivo(grupos, f, 5); //Se lee el archivo
		fclose(f);
	}					
	if(existe("Grupo G.dat", f)){ //Si existe el archivo Grupo G.dat...
		leeArchivo(grupos, f, 6); //Se lee el archivo
	}						
	if(existe("Grupo H.dat", f)){ //Si existe el archivo Grupo H.dat...
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

void cerrarFlujo(FILE* f){
	fclose(f);
	return;	
}

 ////////////////////////////////////////////////////////////////ARCHIVOS////////////////////////////////////////////////////////////////////////////////////
