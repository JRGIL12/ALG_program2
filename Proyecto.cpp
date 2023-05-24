/*
	Nombre:
		MINI PROYECTO 1	
	Objetivo:
		Se desea crear un programa que maneje el control de estudios de un centro educativo.
	Descripcion:
		`En la institución se dictan clases semestralmente, se tienen tres lapsos (1,2,3) anuales, el período corresponde al curso de verano anual.
		`Las materias a dictar están guardadas en el sistema. Se pueden modificar, consultar o eliminar materias. 
		`Cuando se elimina una materia se deben borrar del sistema todos los cursos con esa materia como contenido. 
		`El código de materia es único y no se puede modificar una vez creado.
		`Para registrar un curso deben preexistir la materia (código) y los alumnos (cédula).
		`Un alumno puede solo puede tener aprobada una materia una vez, luego de ello no puede reinscribirla.
		`Puede haber reprobado la materia un máximo de 4 (cuatro) veces. En caso de reprobar ya no puede volver a inscribirse en el instituto.
		`Puede haber retirado la materia infinita cantidad de veces. 
		`El código del curso es único y no puede ser modificado una vez creado.
			-Cuando se elimina un curso, deben borrarse todas sus referencias en el sistema
			-Cuando se elimina un alumno deben borrarse todas sus referencias en el sistema.
			-El sistema debe manejarse en listas dinámicas en memoria principal y almacenarse en memoria secundaria.

		Se tienen tres listas principales:
			*Materias:
				 código dela materia (entero),
				 nombre (hasta 30 caracteres),
				 descripción(máximo 100 caracteres),
				 semestre al que pertenece (I,II, …, X),
				 numero de créditos ( 2 a 5 ).
			*Cursos:
				Código del curso ( entero ),
				código materia, año ( XXXX), 
				Lapso (1..3: indica primer semestre, segundo o verano).
			*Personas:
				Cédula de identidad ( entero largo ),
				nombres y apellidos,
				fecha de nacimiento,
				dirección.
				La cedula es única y no puede ser modificada. 
				Si se elimina una persona en el sistema deben eliminarse todas sus referencias en el sistema.
				Igual mente cada estudiante tiene una lista de los cursos en que ha participado.
				Allí se almacenan: código de curso y la nota correspondiente.

	Características del sistema:
		El sistema tiene un menú principal que tiene tres (03) opciones principales

		+Mantenimiento: (tablas base del sistema)
			-Materias:
				*agregar
				*modificar
				*consultar 
				*eliminar.
			-Cursos:
				*agregar, 
				*modificar
				*consultar 
				*eliminar.
			-Personas:
				*agregar
				*modificar
				*consultar 
				*eliminar personas (sin datos de cursos)

		+Control de estudios
			-Alumnos:
				*Agregar 
				*modificar 
				*eliminar alumnos en cursos con sus notas correspondientes.
			-Una persona solo se puede inscribir una vez en cada Curso.
			-No se puede inscribir a un alumno en una materia que ya tenga aprobada. 
            -Se puede modificar la nota en un curso y alumnos dados
		+Consultas:
			- Dado un nombre de curso buscar su código.
			- Dado un nombre de alumno buscar su(s) cédula(s) asociada(s) y demás datos (sinónimos para ubicar la cédula que nos interesa).
			- Dado un año y un lapso ubicar todos los cursos dictados ( nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
			- Dado un código de materia mostrar todos los cursos que la han dictado (nombre de curso, materia, cantidad de alumnos aprobados y reprobados)
			-Dado un código de curso mostrar todos los datos del mismo con la materia y los alumnos con sus notas
			-Dada una materia ( código ) mostrar los alumnos que la han aprobado (cedula, apellido y nombre con su nota )
			-Todos los cursos (con sus alumnos y notas) dictados en un periodo dado.
			-Dada una cedula mostrar todos los cursos con sus notas tomadas por esapersona

*/
/*
	Entrega inicial: 01 de junio 2023 vía módulo 7 (archivo comprimido con todos los fuentesy archivos de datos).
	Grupos de un máximo de 04 (cuatro) personas. (misma sección).
	
	Contenido de la entrega: 
	todo el mantenimiento del sistema (tablas):
		-materias
		-cursos 
		-personas 
		(agregar, modificar y eliminar, así como el almacenamiento y recuperación de la información con archivos).
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

const int maxEntero=32767; // maximo numero para un ENTERO

struct fecha
{
	int year;
	int month;
	int day;
} Fecha;

struct materias
{
	int codigoMat;
	char nombreMat[30];
	char descripcion[100];
	char semestre[3]; //DEL 1 AL 10 EN NUMEROS ROMANOS
	int creditos; //DE 2 A 5
	materias *prx;
} Materias;

struct cursos
{
	int codigocurso;
	materias codigoMat;
	fecha year; 
	int lapso; // DE 1 A 3
	cursos *prx;
} Cursos;

struct personas
{
	long int cedula;	// NO SE PUEDE MODIFICAR
	char nombre_apellido[30];
	fecha fecha;
	char direccion[40];
	materias *prx;
	cursos *aba;
	personas *sig;
} Personas;

//DECLARACION DE FUNCIONES

void introduciropcion(int *opcion);
int validar_num (char numero[]);
void AgregaMateria (materias **p);
void ingcodigo(int *codigo);
void ingnombre(char *Matnombre);
void ingDescripcion(char *Matdescripcion);
materias *buscarMateria(materias *mat, int codigo, char nombre[]);
void  BloqMayus ( char s[] );
void ingCredito(int *credito);

int main (){
	materias *mat = NULL;
	cursos *cur = NULL;
	personas *per = NULL;

	int op, aux, aux2;
	do 
	{
		printf("\t MENU\n\n");

		printf(" 1- MANTENIMIENTO\n 2- CONTROL DE ESTUDIOS\n 3- CONSULTAS\n\n 0- SALIR\n\n ");

		fflush(stdin);
		introduciropcion(&op);

		system("cls");
		switch (op) 
		{
			//MENU MANTENIMIENTO
			case 1:
				do 
				{
					printf("\n\tMANTENIMIENTO\n\n");
					printf(" 1- MATERIAS\n 2- CURSOS\n 3- PERSONAS\n\n 0- VOLVER\n\n ");
					fflush(stdin);
					introduciropcion(&aux);
					system("cls");
					switch (aux)
					{
						case 0:
							break;
						
						case 1://MENU MATERIAS
							do 
							{
								printf("\n\tMATERIAS \n\n");
								printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
								fflush(stdin);
								introduciropcion(&aux2);
								system("cls");
								switch (aux2)
								{
									case 0:
										break;
								
									case 1: //Agregar Materia
										printf("\n\tAGREGAR\n\n");
										AgregaMateria(&mat);
										fflush(stdin);

										printf("\n\n\tMATERIA AGREGADA CON EXITO!!!\n\n");
										system("cls");
										break;
									
									case 2 : //Modificar Materia
										printf("\n\tMODIFICAR\n\n");
										break;
									
									case 3: //Consultar Materia
										printf("\n\tCONSULTAR\n\n");
										/*
										if (materias) 
											printf("\ntHOLA");
										else 
											printf(" NO EXISTE NINGUNA MATERIA EN EL SISTEMA \n\n");
										*/
										break;
									
									case 4: //Eliminar Materia
										printf("\n\tELIMINAR\n\n");
										/*
										if (materias)
											printf("\ntHOLA");
										else 
											printf(" NO EXISTE NINGUNA MATERIA EN EL SISTEMA\n\n");
										*/
										break;

									default:
										printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										Sleep(1000);
								}
							}while(aux2!=0);
							break;

						case 2 ://MENU CURSOS
							do 
							{
								printf("\n\tCURSOS \n\n");
								printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
								fflush(stdin);
								introduciropcion(&aux2);
								system("cls");
								switch (aux2)
								{
									case 0:
										break;
									
									case 1://Agregar Curso
										printf("\n\tAGREGAR\n\n");
										break;
									
									case 2 : //Modificar Curso
										printf("\n\tMODIFICAR\n\n");
										break;
									
									case 3: //Consultar Curso
										printf("\n\tCONSULTAR\n\n");
										/*
										if (cursos) 
										{
										
										} 
										else 
											printf(" NO EXISTE NINGUN CURSO EN EL SISTEMA \n\n");
										*/
										break;
									
									case 4: //Eliminar Curso
										printf("\n\tELIMINAR\n\n");
										/*
										if (cursos)
										{
											
										} 
										else 
											printf(" NO EXISTE NINGUN CURSO EN EL SISTEMA\n\n");
										*/
										break;

									default:
										printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										Sleep(1000);
								}
							}while(aux2!=0);
							break;
						
						case 3: //MENU PERSONAS
							do 
							{
								printf("\n\tPERSONAS \n\n");
								printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
								fflush(stdin);
								introduciropcion(&aux2);
								system("cls");
								switch (aux2)
								{
									case 0:
										break;
									
									case 1: //Agregar Persona
										printf("\n\tAGREGAR\n\n");
										break;
									
									case 2: //Modificar Persona
										printf("\n\tMODIFICAR\n\n");
										break;
									
									case 3: //Consultar Persona
										printf("\n\tCONSULTAR\n\n");
										/*
										if (personas)
										{
										} 
										else 
											printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");
											*/
										break;
									
									case 4: //Eliminar Materia
										printf("\n\tELIMINAR\n\n");
										/*
										if (personas)
										{
										
										} 
										else 
											printf(" NO EXISTE NINGUNA PERSONAS EN EL SISTEMA\n\n");
											*/
										break;

									default:
										printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										Sleep(1000);
								}
							}while(aux2!=0);		
							break;
						
						default:
							printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
					// Fin del Switch del menu de MANTENIMIENTO
					}    
					if (aux !=0)
					{
						system("pause");
		    			system("cls");
					}
				}while(aux !=0);
				break;

				case 2:/*MENU CONTROL DE ESTUDIOS*/
					do 
					{
						printf("\n\tCONTROL DE ESTUDIOS \n\n");
						printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
						fflush(stdin);
						introduciropcion(&aux2);
						system("cls");
						switch (aux2)
						{
							case 0:
								break;
							
							case 1: //Agregar Persona
								printf("\n\tAGREGAR\n\n");
								break;
							
							case 2 : //Modificar Persona
								printf("\n\tMODIFICAR\n\n");
								break;
							
							case 3://Consultar Persona
								printf("\n\tCONSULTAR\n\n");
								/*
								if (personas) 
								{
								
								} 
								else 
									printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");
								*/
								break;
							//Eliminar Persona
							case 4: 
								printf("\n\tELIMINAR\n\n");									
								/*
								if (personas)
								{
									;
								} 
								else 
									printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA\n\n");
								*/
								break;

							default:
								printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
								system("pause");
								break;
						}
					}while(aux2!=0);	
					break;
				
				case 3://MENU CONSULTA
					do 
					{
						printf("\n\t\t MENU DE CONSULTA \n\n");
						printf("\t 1- DADO UN NOMBRE DE CURSO, BUSCA SU CODIGO\n");
						printf("\t 2- DADO UN NOMBRE DE ALUMNO, BUSCAR SU CEDULA ASOCIADA Y DATOS\n");
						printf("\t 3- DADO UN ANIO Y UN LAPSO, UBICAR TODOS LOS CURSOS DICTADOS \n");
						printf("\t 4- DADO UN CODIGO DE MATERIA, MOSTRAR TODOS LOS CURSOS QUE LA HAN DICTADO\n");
						printf("\t 5- DADO UN CODIGO DE CUROS, MOSTRAR TODOS LOS DATOS DEL MISMO\n");
						printf("\t 6- DADA UNA MATERIA, MOSTRAR TODOS LOS ALUMNOS QUE HAN APROBADO\n");
						printf("\t 7- TODOS LOS CURSOS DICTADOS EN UN PERIODO DADO\n");
						printf("\t 8- DADA UNA CEDULA, MOSTRAR TODOS LOS CURSOS CON SUS NOTAS TOMADAS POR ESA PERSONA\n");
						fflush(stdin);
						introduciropcion(&aux2);
						system("cls");
						switch (aux2)
						{
							case 0:
								break;
							
							case 1://Agregar Persona 
								printf("\n\tAGREGAR\n\n");
								break;
							
							case 2 ://Modificar Persona 
								printf("\n\tMODIFICAR\n\n");
								break;
							//Consultar Persona
							case 3: 
								printf("\n\tCONSULTAR\n\n");
								/*
								if (personas) 
								{
								
								} 
								else 
									printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");
								*/
								break;
							
							case 4: //Eliminar Materia
								printf("\n\tELIMINAR\n\n");
								/*
								if (personas)
								{
									
								} 
								else 
								printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA\n\n")
								;*/
								break;

							default:
								printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
								system("pause");
								break;
						}
					}while(aux2!=0);	
					break;
				
					default:
						if (op != 0)
						{
							printf(" DEBE ELEGIR UNA OPCION VALIDA ");
							Sleep(100);
						}
					}
					system("cls");
				}while(op !=0); /* FIN DEL SWITCH DEL MENU PRINCIPAL*/
				printf("\n HASTA PRONTO!!!\n");
				Sleep(1000);
				return 0;

}

/* FUNCIONES Y PROCEDIMIENTOS*/

void introduciropcion(int *opcion) 
{/*Funcion para validar que la opcion ingresada por el usuario es mayor que 1 y no contiene letras*/
	char copia[20];
	int valn;
	fflush(stdin);
	do
	{
		printf("\n INTRODUZCA NUMERO DE OPCION -> ");
		scanf_s  ("%s",&copia);
		valn=validar_num(copia);
		if ((strlen(copia)>1)||(valn!=0))
			printf("\n DEBE INGRESAR UN NUMERO QUE SE ENCUENTRE ENTRE LAS OPCIONES \n ");
	} while ((strlen(copia)>1)||(valn!=0));
	*opcion=atoi(copia);
	fflush(stdin);
}


int validar_num (char numero[])	
{/*Funcion que nos permite validar dado un string, saber si tiene solo numeros o contiene letras*/
	int i=0, sw=0,j;
	j=strlen(numero);
	while((i<j)&&(sw==0))
	{
		if(isdigit(numero[i])!=0)
		{
			i++;
		}
		else
			sw=1;
		
	}
	return sw;
}

void AgregaMateria (materias **mat)
{
	materias *ax;
	ax = new materias;
	fflush(stdin);
	do
	{
		printf(" INTRODUZCA EL CODIGO DE LA MATERIA : ");
		ingcodigo(&ax->codigoMat);
		if (buscarMateria(*mat, ax->codigoMat, ax->nombreMat) != NULL) 
		{//Se valida que el codigo de la Materia sea unico
			printf("\n EL CODIGO INTRODUCIDO YA SE ENCUENTRA EN EL SISTEMA \n");
			Sleep(1); 
			printf("\n\n");
		}
	}while (buscarMateria(*mat, ax->codigoMat, ax->nombreMat) != NULL);
	printf("\n");
	printf (" INTRODUZCA EL NOMBRE DE LA MATERIA [30 CARACTERES]: ");
	ingnombre(ax->nombreMat);
	printf (" INTRODUZCA UNA BREVE DESCRIPCION DE LA MATERIA [100 CARACTERES]: ");
	ingDescripcion(ax->descripcion);
	fflush(stdin);
	printf (" INTRODUZCA LAS UNIDADES CREDITO [2-5]: ");
	ingCredito(&ax->creditos);

	ax->prx = NULL;
	printf(" %i -- %s -- %s -- %i\n\n", ax->codigoMat , ax->nombreMat, ax->descripcion, ax->creditos);
	system("pause");
	if (mat==NULL) 
	{
		*mat = ax;
	}
	else 
	{
		ax->prx = *mat;
		*mat = ax;
	}
}


void ingcodigo(int *codigo)
{
	char copia[5];
	int valn;
	do
	{
		scanf_s("%s",&copia);
		valn=validar_num(copia);
		*codigo=atoi(copia);
		if((*codigo>=maxEntero)||(*codigo==0)||(valn!=0))
		{
			printf("\n EL NUMERO INGRESADO NO ES VALIDO (INGRESE OTRO): ");
		}
	}while ((*codigo>=maxEntero)||(*codigo==0)||(valn!=0));
	fflush(stdin);
	*codigo=atoi(copia);
}


void ingnombre(char *Matnombre) 
{/*funcion para validar que el nombre no excede la cantidad de 30 caracteres*/
	do
	{
		fflush(stdin);
		scanf_s (" %[^\n]s",&*Matnombre);
		if (!(strlen(Matnombre)<=30))
			printf(" LA CADENA DEBE SER MENOR A 30 CARACTERES: ");
	} while (!(strlen(Matnombre)<=30));
	BloqMayus(Matnombre);
	printf  (" \n");
	fflush(stdin);
}

void ingDescripcion(char *Matdescripcion) 
{/*funcion para validar que la descripcion no excede la cantidad de 100 caracteres*/
	do
	{
		fflush(stdin);
		scanf_s (" %[^\n]s",&*Matdescripcion);
		if (!(strlen(Matdescripcion)<=100))
			printf(" LA CADENA DEBE SER MENOR A 100 CARACTERES: ");
	} while (!(strlen(Matdescripcion)<=100));
	BloqMayus(Matdescripcion);
	printf  (" \n");
	fflush(stdin);
}

materias *buscarMateria(materias *mat, int codigo, char nombre[])
{
	materias *temp = mat;
	for ( ; temp ; temp=temp->prx) 
	{
		if (codigo == 0) 
		{
			if (strcmp(temp->nombreMat, nombre)==0) 
				return temp; //Se encontro una materia con el mismo nombre
		} 
		else 
		{
			if (temp->codigoMat == codigo)  
				return temp;	//Se encontro una materia con el mismo codigo
		}		      
	}
	return NULL;
}

void  BloqMayus ( char s[] )
{/*Rutina que convierte todas las letras de un string en mayusculas*/
	int i;
	for (i = 0; s[i]!='\0'; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
			{
				s[i] = s[i] - 32;
			}
	}
}

void ingCredito(int *credito)
{/*funcion para validar las unidades credito de la materia*/
	char copiacredito[5];
	int valn;
	bool ver = false;
	do 
	{
		fflush(stdin);
		scanf_s ("%s",&copiacredito);
		valn=validar_num(copiacredito);
		if ((strlen(copiacredito)<1)||(valn!=0))
		{
		
		}	
		else 
			if ((atoi(copiacredito)>1) && (atoi(copiacredito)<6))
			{
				*credito=atoi(copiacredito);
				ver = true;
			}
			if (ver==false)
				printf(" \n OPCION INVALIDA, INGRESE DE NUEVO -> ");
	} while (ver == false);
	fflush(stdin);
}
