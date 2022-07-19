#define ESC 27
#define DIM 50
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "stEmpleados.h"
#include "centrarTitulos.h"

stEmpleado cargarUnEmpleado()
{
    stEmpleado e;
    printf("\n Ingrese apellido del empleado: ");
    fflush(stdin);
    gets(e.apellido);
    printf("\n Ingrese nombre del empleado: ");
    fflush(stdin);
    gets(e.nombre);
    printf("\n Ingrese el dni del empleado: ");
    fflush(stdin);
    gets(e.dni);
    printf("\n Ingrese el telefono del empleado: ");
    fflush(stdin);
    gets(e.telefono);
    printf("\n Ingrese el mail del empleado: ");
    fflush(stdin);
    gets(e.mail);
    printf("\n Ingrese el estado del empleado: ");
    fflush(stdin);
    scanf("%i", &e.estado);

    return e;
}

int cargarEmpleados (stEmpleado e[], int dim)
{
    int opcion = 0;
    int i = 0;
    while(opcion != ESC && i < dim )
    {
        e[i] = cargarUnEmpleado();
        i++;
        printf("Seguir cargando empleados? CUALQ.TECLA: SI / ESC: NO");
        opcion = getch();
        system("cls");
    }
    return i;
}

void mostrarUnEmpleado(stEmpleado e)
{
    printf("\n id: %i", e.id);
    printf("\n Apellido: %s", e.apellido);
    printf("\n Nombre: %s", e.nombre);
    printf("\n DNI: %s", e.dni);
    printf("\n Telefono: %s", e.telefono);
    printf("\n Email: %s", e.mail);
    if (e.estado == 0)
    {
        printf("\n Estado: ALTA");
    }
    else
    {
        printf("\nEstado: BAJA");
    }

    printf("\n------------------------");
}

void mostrarEmpleados(stEmpleado e[], int v)
{
    for(int i = 0; i < v; i ++)
    {
        mostrarUnEmpleado(e[i]);
    }
}

void cargarArchivoEmpleado(char nombreArchivo[])
{
    FILE *archiEMpleados = fopen(nombreArchivo, "ab");
    stEmpleado e;
    char opcion;
    int id = 0;

    if(archiEMpleados)
    {
        if(ftell(archiEMpleados)>sizeof(stEmpleado))
        {
            id = incrementarIdEmpleado(nombreArchivo);
        }
        do
        {
            id ++;
            e = cargarUnEmpleado();
            e.id = id;
            fwrite(&e,sizeof(stEmpleado), 1, archiEMpleados);
            contarTitulo("SEGUIR CARGANDO EMPLEADOS?");
            contarTitulo("ESC PARA SALIR O CUALQ. TECLA PARA CONTINUAR");
            printf("\n\t\t\t\t\t\t\t\t");
            opcion = getch();
            system("cls");
        }
        while(opcion!=ESC);
        fclose(archiEMpleados);
    }

}

void mostrarArchivoEmpleado(char nombreArchivo[])
{
    FILE *cargarArchivoEmpleado = fopen(nombreArchivo, "rb");
    stEmpleado e;

    if(cargarArchivoEmpleado)
    {
        while(fread(&e,sizeof(stEmpleado), 1, cargarArchivoEmpleado)> 0)
        {
            mostrarUnEmpleado(e);
        }
    }
    fclose(cargarArchivoEmpleado);
}


void buscarporDatoInt(char nombreArchivo[], int dato)
{
    FILE *cargarArchivoEmpleado = fopen(nombreArchivo,"rb");
    int flag = 0;
    stEmpleado e;

    if (cargarArchivoEmpleado)
    {
        while(fread(&e,sizeof(stEmpleado), 1, cargarArchivoEmpleado) > 0 && flag == 0)
        {
            if(e.id == dato)
            {
                mostrarUnEmpleado(e);
                printf("\n");
                flag = 1;
            }
        }
        fclose(cargarArchivoEmpleado);
    }

}

void buscarPorEstado(char nombreArchivo[], int dato)
{
    FILE *cargarArchivoEmpleado = fopen(nombreArchivo,"rb");
    stEmpleado e;

    if (cargarArchivoEmpleado)
    {
        while(fread(&e,sizeof(stEmpleado), 1, cargarArchivoEmpleado) > 0)
        {
            if(e.estado == dato)
            {
                mostrarUnEmpleado(e);
                printf("\n");
            }
        }
    }
    fclose(cargarArchivoEmpleado);
}

int incrementarIdEmpleado (char nombreArchivo[])
{
    int id = 0;

    stEmpleado e;

    FILE *archiEmpleados = fopen(nombreArchivo, "rb");

    if(archiEmpleados)
    {
        fseek(archiEmpleados, -1 * sizeof(archiEmpleados),SEEK_END);
        if(fread(&e, sizeof(stEmpleado),1, archiEmpleados) > 0)
        {
            id = e.id;
        }
        fclose(archiEmpleados);
    }

    return id;
}

void buscarPorDni (char nombreArchivo[], char dni[])
{
    int flag = 0;
    stEmpleado e;

    FILE *cargarArchivoEmpleado = fopen(nombreArchivo, "rb");

    if (cargarArchivoEmpleado)
    {
        while(fread(&e,sizeof(stEmpleado), 1, cargarArchivoEmpleado) > 0 && flag == 0)
        {
            if (strcmp(dni, e.dni) == 0)
            {
                mostrarUnEmpleado(e);
                printf("\n");
                flag = 1;
            }
        }
    }
    fclose(cargarArchivoEmpleado);
}

void buscarPorApellido (char nombreArchivo[], char apellido[])
{
    stEmpleado e;
    FILE *archiEmpleado = fopen(nombreArchivo, "rb");

    if(archiEmpleado)
    {
        while(fread(&e, sizeof(stEmpleado),1,archiEmpleado) > 0)
        {
            if (strcmpi(apellido, e.apellido) == 0)
            {
                mostrarUnEmpleado(e);
                printf("\n");
            }
        }
    }
    fclose(archiEmpleado);
}

void modificarApellido(char nombreArchivo[], char apellido[])
{
    int flag = 0;
    char nuevoApellido[DIM];
    stEmpleado e;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {
        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0)
        {
            if(strcmpi(e.apellido, apellido) == 0)
            {
                flag = 1;
            }
        }
        if(flag)
        {
            printf("\n INGRESE NUEVO APELLIDO DEL CLIENTE: ");
            fflush(stdin);
            gets(nuevoApellido);
            strcpy(e.apellido,nuevoApellido);
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }
        else
        {
            printf("APELLIDO NO ENCONTRADO.");
        }
        fclose(archiEmpleado);
    }
}

void modificarDni(char nombreArchivo[], char dni[])
{
    int flag = 0;
    char nuevoDni[DIM];
    stEmpleado e;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {
        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0)
        {
            if(strcmp(e.dni, dni) == 0)
            {
                flag = 1;
            }
        }
        if(flag)
        {
            printf("\n INGRESE NUEVO DNI DEL CLIENTE: ");
            fflush(stdin);
            gets(nuevoDni);
            strcpy(e.dni,nuevoDni);
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }
        else
        {
            printf("DNI NO ENCONTRADO.");
        }
        fclose(archiEmpleado);
    }
}

void modificarNombre(char nombreArchivo[], char nombre[])
{
    int flag = 0;
    char nuevoNombre[DIM];
    stEmpleado e;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {
        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0)
        {
            if(strcmpi(e.nombre, nombre) == 0)
            {
                flag = 1;
            }
        }
        if(flag)
        {
            printf("\n INGRESE NUEVO NOMBRE DEL CLIENTE: ");
            fflush(stdin);
            gets(nuevoNombre);
            strcpy(e.nombre,nuevoNombre);
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }
        else
        {
            printf("NOMBRE NO ENCONTRADO.");
        }
        fclose(archiEmpleado);
    }
}

void modificarTelefono(char nombreArchivo[], char telefono[])
{
    int flag = 0;
    char nuevoTelefono[DIM];
    stEmpleado e;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {
        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0)
        {
            if(strcmp(e.telefono, telefono) == 0)
            {
                flag = 1;
            }
        }
        if(flag)
        {
            printf("\n INGRESE NUEVO TELEFONO DEL CLIENTE: ");
            fflush(stdin);
            gets(nuevoTelefono);
            strcpy(e.telefono,nuevoTelefono);
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }
        else
        {
            printf("TELEFONO NO ENCONTRADO.");
        }
        fclose(archiEmpleado);
    }
}

void modificarMail(char nombreArchivo[], char mail[])
{
    int flag = 0;
    char nuevoMail [DIM];
    stEmpleado e;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {
        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0)
        {
            if(strcmpi(e.mail, mail) == 0)
            {
                flag = 1;
            }
        }
        if(flag)
        {
            printf("\n INGRESE NUEVO MAIL DEL CLIENTE: ");
            fflush(stdin);
            gets(nuevoMail);
            strcpy(e.mail,nuevoMail);
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }
        else
        {
            printf("MAIL NO ENCONTRADO.");
        }
        fclose(archiEmpleado);
    }
}

void modificarEstadoxId(char nombreArchivo[], int id)
{
    stEmpleado e;
    int flag = 0;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {

        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0 )
        {
            if(e.id == id)
            {
                flag =1;
            }
        }

        if(flag)
        {
            if(e.estado == 0)
            {
                e.estado = 1;
            }
            else
            {
                e.estado = 0;
            }
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }


    }
    fclose(archiEmpleado);
}

void modificarEstadoxDni(char nombreArchivo[], char dni[])
{
    stEmpleado e;
    int flag = 0;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {

        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0 )
        {
            if(strcmp(e.dni,dni)== 0)
            {
                flag =1;
            }
        }

        if(flag)
        {
            if(e.estado == 0)
            {
                e.estado = 1;
            }
            else
            {
                e.estado = 0;
            }
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }


    }
    fclose(archiEmpleado);
}

void modificarEstadoxApellido(char nombreArchivo[], char apellido[])
{
    stEmpleado e;
    int flag = 0;

    FILE *archiEmpleado = fopen(nombreArchivo, "r+b");
    if(archiEmpleado)
    {

        while(flag == 0 && fread(&e,sizeof(stEmpleado),1,archiEmpleado) > 0 )
        {
            if(strcmpi(e.apellido, apellido)== 0)
            {
                flag =1;
            }
        }

        if(flag)
        {
            if(e.estado == 0)
            {
                e.estado = 1;
            }
            else
            {
                e.estado = 0;
            }
            fseek(archiEmpleado, -1 * sizeof(stEmpleado), SEEK_CUR);
            fwrite(&e,sizeof(stEmpleado),1,archiEmpleado);
            mostrarUnEmpleado(e);
        }


    }
    fclose(archiEmpleado);
}



