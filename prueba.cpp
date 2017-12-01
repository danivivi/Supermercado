#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Comentario
Programa de simula un supermercado
Fecha:30-Noviembre-2017
Elaborado por: Viviana Rojas Ruiz, Alejandro Gonzalez y Leyder Mejia*/

struct Clientes{
	char nombre[30];
	char apellido[30];
	char cedula[15];
}clientesitos;

typedef struct{// asignar nombre alternativo a tipos asistentes
	char *NombreProducto;
	int codigo;
	int precio;
	int puntos;
}trabajadores;

trabajadores *trab;

FILE *super;
FILE *Usuarios;

void listaProductos();
void MostrarProductos();
void Menu();
void datosCliente();
void MostrarClientes();
void Compra(Clientes v[]);
void PasarDatos();
void AnadirProductos();
void CambiarPuntos(int totalPrecio);

void vaciar(char temp[]);
void copiar(char temp[],int i);

int tam;
Clientes v[100];
char temp[4];

int main() {	
	Menu();
	return 0;
}	
void Menu(){
	int opcion;
	do{
		printf("<<<<<<Bienvenidos>>>>>>>>\n");
		printf("----Supermercado EL FRESA-----\n\n");
		printf("<<<<<<MENU>>>>>>\n");		
		printf("Ingrese una opcion:\n");
		printf("1.Lista de Productos\n");
		printf("2.Comprar Productos\n");
		printf("3.Añadir Productos\n");		
		printf("4.Lista de Clientes\n");		
		printf("0.Salir\n");
		scanf("%d",&opcion);
		switch(opcion)
		{
		case 0:
			printf("Gracias por Elegir nuestro Supermercado EL FRESA\n");
			exit(0);			
		case 1:
			MostrarProductos();
			break;
		case 2:
			datosCliente();
			Compra(v);
			break;
		case 3:
			AnadirProductos();
			break;
		case 4:
			MostrarClientes();
			break;			
		default:
			printf("La opcion Ingresada No es Válida\n");
			break;
		}		
	}while(opcion!=0);
}

void MostrarProductos()
{
	int letra;
	char ruta[] = "Super.txt"; 
	super = fopen(ruta, "rt");
	if(super == NULL){
		printf("Error al abrir el archivo \n");
	}else{
		while((letra = fgetc(super)) != EOF){
			if(letra == '\n'){
				printf("\n");
			}else{
				putchar(letra);//visualiza los caracteres
			}
		}
		fclose(super);
	}
	PasarDatos();
}
void PasarDatos(){

	char temp[50];
	int cont=0;
	int j;
	int i;
	char aux;
	
	FILE *f;
	f= fopen("Super.txt", "r");
	if (f== NULL){
		printf("No se ha podido abrir el archivo \n");
		exit(1);
	}
	while(!feof(f)){//mientras llegue al final del archivo 
		fgets(temp,50,f);
		cont++;
	}
	rewind(f);//pone el cursor al comienzo del archivo
	trab=(trabajadores*)malloc(cont*sizeof(trabajadores));//reserva la memoria 
	if(trab==NULL){
		printf("No se a podido reservar la memoria\n");
		exit(1);
	}
	
	for(i=0;!feof(f);i++){
		vaciar(temp);
		aux='0';
		for(j=0;aux!='-';j++){
			aux=fgetc(f);
			if(aux!='-'){
				temp[j]=aux;
			}
		}copiar(temp,i);
		
		fgets(temp,4,f);
		trab[i].codigo=atoi(temp);//char a int 
		
		printf("Producto: %s  Codigo: %i \n",trab[i].NombreProducto,trab[i].codigo);
	}
	//return 0;
}

void vaciar(char temp[]){
	for(int i=0;i<50;i++){
		temp[i]='\0';		
	}
}
void copiar(char temp[],int i){
	int N=strlen(temp)+1;//contar letra por letra
	trab[i].NombreProducto=(char*)malloc(N*sizeof(char));
	if(trab[i].NombreProducto==NULL){
		printf("No se ha podido reservar memoria \n");
		exit(1);
	}
	strcpy(trab[i].NombreProducto,temp);//copiando el archivo en nombre producto
}
void listaProductos(){
	int letra;
	char direccion[]="Super.txt";
	super = fopen(direccion, "wt");
	if(super == NULL){
		printf("Error al abrir el archivo \n");
	}else{
		while((letra = getchar()) != EOF){
			fputc(letra, super);
		}
		fclose(super);
	}
}

void AnadirProductos(){
	int letra;
	char ruta[] = "super.txt"; 
	super = fopen(ruta, "at");
	if(super == NULL){
		printf("Error al abrir el archivo \n");
	}else{
		while((letra = getchar()) != EOF){
			fputc(letra, super);
		}
		fclose(super);
	}
}

void datosCliente()
{
	char ruta[]="Usuarios.txt";
	Usuarios = fopen(ruta, "at");
	if(Usuarios == NULL){
		printf("Error al abrir el archivo \n");
	}else{
		printf("Ingrese Datos del Cliente");
		fflush(stdin);
		printf("\nNombre: ");fgets(clientesitos.nombre, 30, stdin);
		printf("\nApellido: ");fgets(clientesitos.apellido, 30, stdin);
		printf("\nCedula: ");fgets(clientesitos.cedula, 30, stdin);
		fprintf(Usuarios,"\nNombre: ");
		fwrite(clientesitos.nombre,1,strlen(clientesitos.nombre),Usuarios);
		fprintf(Usuarios,"\nApellido: ");
		fwrite(clientesitos.apellido,1,strlen(clientesitos.apellido),Usuarios);
		fprintf(Usuarios,"\nCedula: ");
		fwrite(clientesitos.cedula,1,strlen(clientesitos.cedula),Usuarios);		
		fclose(Usuarios);
	}
}

void MostrarClientes()
{
	int letra;
	char ruta[] = "Usuarios.txt"; 
	Usuarios = fopen(ruta, "rt");
	if(super == NULL){
		printf("Error al abrir el archivo \n");
	}else{
		while((letra = fgetc(Usuarios)) != EOF){
			if(letra == '\n'){
				printf("\n");
			}else{
				putchar(letra);
			}
		}
		fclose(Usuarios);
	}
}

void Compra(Clientes v[])
{
	int codigo;
	int precio[10],totalPrecio=0;
	int efectivo,cambio;
	
	printf("Ingrese Cantidad de Productos a Comprar:\n");
	scanf("%d",&tam);
	int pos=0;
	for(int i=0;i<tam;i++){
		printf("Codigo: ");
		scanf("%d",&codigo);
		for(int i=1;i<=100;i++){
			if (codigo==trab[i].codigo){
				pos=i;
				printf("\nCodigo: %d  Producto: %s",trab[pos].codigo,trab[pos].NombreProducto);
				printf("   Valor $");
				scanf("%d",&trab[pos].precio);
				precio[i]=trab[pos].precio;
			}
		}
	}
	for(int i=0;i<tam;i++){
		totalPrecio=totalPrecio+precio[i];		
	}
	printf("Total Compra: $%d\n ",totalPrecio);
	printf("\nIngrese Efectivo:  ");
	scanf("%d",&efectivo);
	cambio = efectivo-totalPrecio;
	printf("\nEl cambio es de $%d",cambio);
	
	CambiarPuntos(totalPrecio);
}

void CambiarPuntos(int totalPrecio){
	int opcion;
	if (totalPrecio>=20000 and totalPrecio<40000){		
		printf("\nAcaba de Ganar 30 Puntos por su Compra!!\n ");
		printf("Puede escoger entre:\n");
		printf("1.Vajilla de 4 Puestos\n");
		printf("2.Juego de Cucharones\n");
		printf("3.Olla a Presion 4L\n");
		printf("Ingrese una Opcion:\n");
		scanf("%d",&opcion);
		switch(opcion){
		case 1:
			printf("<<<Felicidades se lleva una Vajilla de 4 Puestos>>>\n");
			break;
		case 2:
			printf("<<<Felicidades se lleva un Juego de Cucharones>>>\n");
			break;
		case 3:
			printf("<<<Felicidades se lleva una Olla a Presion de 4L>>>\n");
			break;			
		}
	}else if(totalPrecio>40000){
		printf("Acaba de Ganar 60 Puntos por su Compra!!\n ");
		printf("Puede escoger entre:\n");
		printf("1.Bicicleta Todoterreno\n");
		printf("2.Sanduchera\n");
		printf("3.Cafetera\n");
		printf("Ingrese una Opcion:\n");
		scanf("%d",&opcion);
		switch(opcion){
		case 1:
			printf("<<<Felicidades se lleva una Bicicleta Todoterreno>>>\n");
			break;
		case 2:
			printf("<<<Felicidades se lleva una Sanduchera>>>\n");
			break;
		case 3:
			printf("<<<Felicidades se lleva una Cafetera>>>\n");
			break;			
		}
	}else{
		printf("Gracias por su Compra.\n");
	}
}
	
	


