#include <iostream>
using namespace std;
const char *nombre_archivo = "archivo.dat";
struct Estudiante{
	int codigo;
	char nombres[50];
	char apellidos[50];
	int telefono;
};
void Leer();
void Crear();
void Actualizar();
void Borrar();
main(){
	Leer();
	Crear();
	Borrar();
	Actualizar();
	system("pause");
}
//funcion para leer los datos ingresados en el archivo//
void Leer(){
	system("cls");//funcion para limpiar la pantalla de los datos mostrados//
	FILE* archivo = fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo = fopen(nombre_archivo,"w+b");	
	}
	Estudiante estudiante;
	int id=0;//id: indica la posicion donde se encuentra el registro//
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"___________________"<<endl;
	cout<<"ID"<<" | "<<"Codigo"<<" | "<<" Nombres "<<" | "<<" Apellidos "<<" | "<<" Telefono "<<endl;
	do{
		cout<<id<<" | "<<estudiante.codigo<<" | "<<estudiante.nombres<<" | "<<estudiante.apellidos<<" | "<<estudiante.telefono<<endl;
		fread(&estudiante,sizeof(Estudiante),1,archivo);		
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}
//funcion para crear archivos y agregar datos. //
void Crear(){
	
	FILE* archivo = fopen(nombre_archivo,"a+b");
	char res;
	Estudiante estudiante;
	do{
		fflush(stdin);//sirve para limpiar el flujo del archivo. //
		cout<<"Ingrese codigo: ";
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"Ingrese nombres: ";
		cin.getline(estudiante.nombres,50);
		
		cout<<"Ingrese apellidos: ";
		cin.getline(estudiante.apellidos,50);
		
		cout<<"Ingrese telefono: ";
		cin>>estudiante.telefono;
		
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"Desea ingresar otro estudiante(s/n): "<<endl;
		cin>>res;
	}while(res=='s' || res=='S');
	fclose(archivo);//si el archivo se abre, se debe de cerrar con esta linea. //
	Leer();
}
void Actualizar(){
	
	FILE* archivo = fopen(nombre_archivo,"r+b");
	Estudiante estudiante;
	int id=0;
	cout<<"Ingrese el ID que desea modificar: ";
	cin>>id;
	fseek(archivo,id * sizeof(Estudiante),SEEK_SET);

		cout<<"Ingrese codigo: ";
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"Ingrese nombres: ";
		cin.getline(estudiante.nombres,50);
		
		cout<<"Ingrese apellidos: ";
		cin.getline(estudiante.apellidos,50);
		
		cout<<"Ingrese telefono: ";
		cin>>estudiante.telefono;
		
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);

	fclose(archivo);//si el archivo se abre, se debe de cerrar con esta linea. //
	Leer();	
}
void Borrar(){
	const char *nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b");
	FILE* archivo = fopen(nombre_archivo,"rb");
	Estudiante estudiante;
	int id=0,id_n=0;
	cout<<"Ingrese el ID a eliminar: ";
	cin>>id;
	while(fread(&estudiante,sizeof(Estudiante),1,archivo)){
		if(id_n !=id ){
			fwrite(&estudiante,sizeof(Estudiante),1,archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);
	
	archivo_temp = fopen(nombre_archivo_temp,"rb");
	archivo = fopen(nombre_archivo,"wb");
	while(fread(&estudiante,sizeof(Estudiante),1,archivo_temp)){
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	}
	fclose(archivo);
	fclose(archivo_temp);
	Leer();
}
