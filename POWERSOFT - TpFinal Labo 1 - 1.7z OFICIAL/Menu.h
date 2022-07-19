#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


///Pone un recuadro a un texto
void recuadro(char cabecera[]);


///Menu principal
void mainMenu();
///Menu de clientes
void clientMenu ();
///Menu de muestra de clientes
void printClientsMenu ();
///Menu de busqueda de clientes
void searchClientMenu ();
///Menu de alta o baja de clientes
void regDeregMenu ();
///Menu de modificacion de clientes
void customClientsMenu ();


///Menu de consumos
void consumMenu ();
///Menu de muestra de consumos
void printConMenu ();


#endif // MENU_H_INCLUDED
