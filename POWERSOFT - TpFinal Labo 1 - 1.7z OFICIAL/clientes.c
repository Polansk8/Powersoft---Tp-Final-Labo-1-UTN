#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>


#include "Menu.h"
#include "clientes.h"
#include "centrarTitulos.h"


#define DIM 100





CLI loadOneClient (CLI c)
{
    system("cls");
    printf(">>>Ingrese el apellido....: ");
    fflush(stdin);
    gets(c.apellido);
    system("cls");

    printf(">>>Ingrese el nombre......: ");
    fflush(stdin);
    gets(c.name);
    system("cls");

    printf(">>>Ingrese el genero(M o F): ");
    fflush(stdin);
    scanf("%c", &c.sexo);
    system("cls");

    printf(">>>Ingrese el celular.....: ");
    fflush(stdin);
    gets(c.celular);
    system("cls");

    printf(">>>Ingrese el eMail.......: ");
    fflush(stdin);
    gets(c.email);

    return c;
}



void printOneClient (CLI c)
{
    printf("\n                    Id: %d", c.id);
    printf("\n     Apellido y nombre: %s %s", c.apellido, c.name);
    printf("\n                D.N.I.: %s", c.dni);
if (c.sexo == 'm' || c.sexo == 'M')
    {
    printf("\n                Genero: Masculino");
    }
else
    {
    printf("\n                Genero: Femenino");
    }
    printf("\n               Celular: %s", c.celular);
    printf("\n                 eMail: %s", c.email);
if (!c.baja)
    {
    printf("\n                Estado: ALTA");
    }
else
    {
    printf("\n                Estado: BAJA");
    }
}





