#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

/* Constantes */
#define MAX_USUARIOS 1
#define MAX_INTENTOS 3
#define MAX_PRODUCTOS 60
#define MAX_CLIENTES 10
#define MAX_LONG 50

/* Estructuras */
struct Producto {
    char nombre[MAX_LONG];
    int codigo;
    float precio;
    int cantidad;
    char fecha_vencimiento[MAX_LONG];
    char unidad_medida[MAX_LONG];
    char descripcion[MAX_LONG];
};

struct Cliente {
    char nombre[MAX_LONG];
    int codigo;
    char celular[MAX_LONG];
    char direccion[MAX_LONG];
    float credito;
};

struct Usuario {
    char nombre[MAX_LONG];
    char clave[MAX_LONG];
};

/* Variables globales */
struct Producto inventario[MAX_PRODUCTOS];
int num_productos = 0;

struct Cliente clientes[MAX_CLIENTES];
int num_clientes = 0;

/* Prototipos */
void mostrarMenu();
void opcionInventario();
void opcionCliente();
void salir();
int iniciarSesion(struct Usuario usuarios[], int max_intentos);
void agregarProducto();
void eliminarProducto();
void buscarProducto();
void actualizarProducto();
void verInventario();
void venderProducto();
void agregarCliente();
void eliminarCliente();
void buscarCliente();
void actualizarCliente();
void verClientes();
int validarCelular(const char* celular);

/* Funcion para mostrar la presentacion grafica */
void mostrarPresentacion() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(227, 269, "Cargando...");
	setfillstyle(XHATCH_FILL, 1);
    bar(80, 307, 185, 347);
    rectangle(79, 305, 553, 347);
    delay(1000);
    bar(179, 308, 302, 346);
    delay(1000);
    bar(302, 308, 453, 346);
    delay(1000);
    bar(452, 308, 550, 346);
    delay(1000);
    setfillstyle(SOLID_FILL, 0);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(182, 360, "Pulsa cualquier tecla para continuar :D");
    bar(196, 214, 482, 294);
    getch();
    bar(2,1,639,478);
	setfillstyle(SOLID_FILL,1);
	bar(157,72,207,204);
	setlinestyle(SOLID_LINE,0,3);
	delay(1000);
	setfillstyle(SOLID_FILL,1);
	bar(157,204,321,248);
	delay(1000);
	setfillstyle(SOLID_FILL,1);
	bar(277,131,321,246);
	delay(1000);
	setfillstyle(SOLID_FILL,1);
	bar(222,75,262,189);
	delay(1000);
	bar(222,75,374,115);
	setfillstyle(SOLID_FILL,1);
	bar(336,114,374,242);
	delay(1000);
	bar(336,206,437,248);
	delay(1000);
	setfillstyle(SOLID_FILL,1);
	bar(394,132,442,248);
	delay(1000);
	setfillstyle(SOLID_FILL,2);	/*cruz*/
	bar(465,207,486,229);
	bar(407,74,433,128);
	rectangle(408,75,434,129);
	setfillstyle(SOLID_FILL,2);
	rectangle(435,89,449,115);
	rectangle(391,89,408,115); /*nuevo*/
	bar(393,91,447,113); /*relleno horiz*/
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(465,178,487,193);
	bar(459,197,493,244);
	rectangle(459,197,493,244);
	setfillstyle(SOLID_FILL,WHITE);
	rectangle(466,207,486,236);
	bar(466,206,486,236);
	setlinestyle(SOLID_LINE,0,9);
	setcolor(BLUE);
	line(475,211,475,228);
	line(467,218,484,218);
	delay(1000);
	setcolor(WHITE);
	outtextxy(270,259, "Farmacia UniMedic");
	outtextxy(166,289, "-Proyecto de curso de Ing. en computacion-");
	outtextxy(304,310, "1M4-CO");
	getch();
	outtextxy(146,409, "Alex Rodrigo Acosta Salinas");
	outtextxy(146,429, "Steven Alexander Reyes Sandino");
	outtextxy(146,449, "Horacio Munoz Sanchez");
	outtextxy(190,389, "--INTEGRANTES--");
	outtextxy(420,389, "--CARNET--");
	outtextxy(420,409, "2024-1847U");
	outtextxy(420,429, "2024-1882U");
	outtextxy(420,449, "2024-1816U");
	getch();
    closegraph();
}

/* Funcion principal */
int main() {
    struct Usuario usuarios[MAX_USUARIOS] = {{"admin", "1234"}};  /* Usuario predeterminado */
    int intentos = MAX_INTENTOS;

	mostrarPresentacion();  /*Mostrar la presentacion grafica*/

    if (iniciarSesion(usuarios, intentos)) {
        int opcion;
        do {
            mostrarMenu();
		gotoxy(32,15);	printf("\033[1;37mElija una opcion: \033[0m\n");
		gotoxy(32,16);	scanf("%d", &opcion);

            switch (opcion) {
                case 1:
                    opcionInventario();
                    break;
                case 2:
                    opcionCliente();
                    break;
                case 3:
                    salir();
                    break;
                default:
					printf("Opcion invalida. Por favor, intente de nuevo.\n");
					getch();
            }
        } while (opcion != 3);  /* Repetir hasta que se elija la opcion de salir */
    }

    return 0;
}

/* Funcion para iniciar sesion con 3 intentos */
int iniciarSesion(struct Usuario usuarios[], int max_intentos) {
    char nombreIngresado[MAX_LONG], claveIngresada[MAX_LONG];
    int intentos = 0;
    int i;
	 clrscr();
	while (intentos < max_intentos) {
	/*adornos*/
	gotoxy(15,4);  printf("\033[3;36m :   :    :    :    :   :   :   :   :   :   :   :  :      \033[0m\n");
	gotoxy(15,21); printf("\033[3;36m :   :    :    :    :   :   :   :   :   :   :   :  :      \033[0m\n");
	gotoxy(15,5);  printf("\033[3;36m : \033[0m\n");
	gotoxy(15,7);  printf("\033[3;31m : \033[0m\n");
	gotoxy(15,9);  printf("\033[3;36m : \033[0m\n");
	gotoxy(15,11); printf("\033[3;31m : \033[0m\n");
	gotoxy(15,13); printf("\033[3;36m : \033[0m\n");
	gotoxy(15,15); printf("\033[3;31m : \033[0m\n");
	gotoxy(15,17); printf("\033[3;36m : \033[0m\n");
	gotoxy(15,19); printf("\033[3;31m : \033[0m\n");
	gotoxy(65,5);  printf("\033[3;36m : \033[0m\n");
	gotoxy(65,7);  printf("\033[3;31m : \033[0m\n");
	gotoxy(65,9);  printf("\033[3;36m : \033[0m\n");
	gotoxy(65,11); printf("\033[3;31m : \033[0m\n");
	gotoxy(65,13); printf("\033[3;36m : \033[0m\n");
	gotoxy(65,15); printf("\033[3;31m : \033[0m\n");
	gotoxy(65,17); printf("\033[3;36m : \033[0m\n");
	gotoxy(65,19); printf("\033[3;31m : \033[0m\n");

	/*fin adornos*/
	gotoxy(20,5); printf("\033[5;1;37m         === Inicio de sesion === \033[0m\n");
	gotoxy(20,7);	printf("\033[1;33mUsuario: \033[0m\n");
	gotoxy(20,9);	scanf("%s", nombreIngresado);
	gotoxy(20,12);	printf("\033[2;36mClave: \033[0m\n");
	gotoxy(20,14);scanf("%s", claveIngresada);

        for (i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarios[i].nombre, nombreIngresado) == 0 && strcmp(usuarios[i].clave, claveIngresada) == 0) {
		gotoxy(27,19);printf("\033[0;32mInicio de sesion exitoso :D\033[0m\n");
				getch();
                return 1;  /* Usuario autenticado */
            }
        }
	gotoxy(20,20);printf("\033[0;31mUsuario o clave incorrectos. Le quedan %d intentos.\033[0m\n", max_intentos - (++intentos));

    }

gotoxy(20,24);	printf("\033[1;37mDemasiados intentos fallidos. Saliendo del programa...\033[0m\n");
	getch();
    return 0;
}

/* Funcion para mostrar el menu principal */
void mostrarMenu() {
clrscr();
	/*inicio*/
	gotoxy(20,2);  printf("\033[1;32m      =   =   =   =   =   =   =   =          \033[0m\n");
	gotoxy(23,3); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,5); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,7); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,9); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,11); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,13); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,15); printf("\033[2;36m = \033[0m\n");
	gotoxy(23,17); printf("\033[2;36m = \033[0m\n");
	/*derecha*/
	gotoxy(56,3);  printf("\033[2;36m = \033[0m\n");
	gotoxy(56,5);  printf("\033[2;36m = \033[0m\n");
	gotoxy(56,7);  printf("\033[2;36m = \033[0m\n");
	gotoxy(56,9);  printf("\033[2;36m = \033[0m\n");
	gotoxy(56,11); printf("\033[2;36m = \033[0m\n");
	gotoxy(56,13); printf("\033[2;36m = \033[0m\n");
	gotoxy(56,15); printf("\033[2;36m = \033[0m\n");
	gotoxy(56,17); printf("\033[2;36m =  \033[0m\n");
	gotoxy(23,18); printf("\033[1;32m   =   =   =   =   =   =   =   =          \033[0m\n");

	gotoxy(30,4); printf("\033[1;32m  ===Menu Principal===\033[0m\n");
	gotoxy(28,6); printf("\033[0;32m 1.\033[0m\n");
	gotoxy(32,6); printf("\033[1;37mInventario\033[0m\n");
	gotoxy(28,8); printf("\033[0;32m 2.\033[0m\n");
	gotoxy(32,8); printf("\033[1;37mClientes\033[0m\n");
	gotoxy(28,10); printf("\033[0;32m 3.\033[0m\n");
	gotoxy(32,10);printf("\033[1;37mSalir\033[0m\n");
}

/* Menu de Inventario */
void opcionInventario() {
	int opcion;
clrscr();
	do {
	/*aqui inician los adornos*/
	gotoxy(22,3);   printf("\033[1;37m|\033[0m\n");
	gotoxy(22,4);   printf("\033[1;37m|\033[0m\n");
	gotoxy(22,5);   printf("\033[1;37m|\033[0m\n");
	gotoxy(22,6);   printf("\033[2;32m|\033[0m\n");  /*032 verde*/ /*37blanc*/
	gotoxy(22,7);   printf("\033[1;37m|\033[0m\n");
	gotoxy(22,8);  printf("\033[1;32m|\033[0m\n");
	gotoxy(22,9);  printf("\033[1;37m|\033[0m\n");
	gotoxy(22,10);  printf("\033[1;32m|\033[0m\n");
	gotoxy(22,11);  printf("\033[1;37m|\033[0m\n");
	gotoxy(22,12);  printf("\033[1;32m|\033[0m\n");
	gotoxy(22,13);  printf("\033[1;37m|\033[0m\n");
	gotoxy(22,14);  printf("\033[1;32m|\033[0m\n");
	gotoxy(22,15);  printf("\033[1;37m|\033[0m\n");
	gotoxy(22,16);  printf("\033[1;32m|\033[0m\n");
	gotoxy(22,17);  printf("\033[1;37m|\033[0m\n");    /***/

	gotoxy(60,3);   printf("\033[1;37m|\033[0m\n");
	gotoxy(60,4);   printf("\033[1;32m|\033[0m\n");
	gotoxy(60,5);   printf("\033[1;37m|\033[0m\n");
	gotoxy(60,6);   printf("\033[0;32m|\033[0m\n");
	gotoxy(60,7);   printf("\033[1;37m|\033[0m\n");
	gotoxy(60,8);  printf("\033[0;32m|\033[0m\n");
	gotoxy(60,9);  printf("\033[1;37m|\033[0m\n");
	gotoxy(60,10);  printf("\033[1;32m|\033[0m\n");
	gotoxy(60,11);  printf("\033[1;37m|\033[0m\n");
	gotoxy(60,12);  printf("\033[1;32m|\033[0m\n");
	gotoxy(60,13);  printf("\033[1;37m|\033[0m\n");
	gotoxy(60,14);  printf("\033[1;32m|\033[0m\n");
	gotoxy(60,15);  printf("\033[1;37m|\033[0m\n");
	gotoxy(60,16);  printf("\033[1;37m|\033[0m\n");
	gotoxy(60,17);  printf("\033[1;32m|\033[0m\n");     /*j*/

	/*horizontales*/
	gotoxy(23,2);  printf("\033[1;38m- - - - - - - - - - - - - - - - - - -\033[0m\n");
	gotoxy(23,18);   printf("\033[1;32m- - - - - - - - - - - - - - - - - - -\033[0m\n");
	/*aca terminan*/

	gotoxy(29,4);	printf("\033[1;32m === Menu Inventario ===\033[0m\n");
	gotoxy(27,6);   printf("\033[1;37m1. Agregar Producto\033[0m\n");
	gotoxy(27,7);	printf("\033[1;37m2. Eliminar Producto\033[0m\n");
	gotoxy(27,8);	printf("\033[1;37m3. Buscar Producto\033[0m\n");
	gotoxy(27,9);	printf("\033[1;37m4. Actualizar Producto\033[0m\n");
	gotoxy(27,10);	printf("\033[1;37m5. Ver Inventario\033[0m\n");
	gotoxy(27,11);	printf("\033[1;37m6. Vender Producto\033[0m\n");
	gotoxy(27,12);	printf("\033[1;37m7. Volver\033[0m\n");
	gotoxy(27,15);	printf("\033[1;34mElija una opcion: \033[0m\n");
	gotoxy(27,16);	scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                eliminarProducto();
                break;
            case 3:
                buscarProducto();
                break;
            case 4:
                actualizarProducto();
                break;
            case 5:
				verInventario();
                break;
            case 6:
                venderProducto();
                break;
			case 7:
				gotoxy(25,19);
				printf("\033[1;32mVolviendo al menu principal...\033[0m\n");
				getch();
				clrscr();
                break;
			default:
				gotoxy(25,20);
				printf("Opcion invalida. Intente de nuevo.\n");
				getch();
        }
    } while (opcion != 7);
}

/* Funcion para agregar un producto al inventario */
void agregarProducto() {
clrscr();
    if (num_productos < MAX_PRODUCTOS) {
        struct Producto p;
        printf("Ingrese el nombre del producto: ");
        scanf("%s", p.nombre);
        printf("Ingrese el codigo del producto: ");
        scanf("%d", &p.codigo);
        printf("Ingrese el precio del producto: ");
        scanf("%f", &p.precio);
        printf("Ingrese la cantidad: ");
        scanf("%d", &p.cantidad);
        printf("Ingrese la fecha de vencimiento (dd/mm/aaaa): ");
        scanf("%s", p.fecha_vencimiento);
        printf("Ingrese la unidad de medida: ");
        scanf("%s", p.unidad_medida);
		printf("Especificacion (menor/Adulto): ");
        scanf("%s", p.descripcion);

        inventario[num_productos++] = p;
		printf("Producto agregado exitosamente.\n");
		getch();
		clrscr();
    } else {
		printf("El inventario esta lleno.\n");
		getch();
		clrscr();
    }
}

/* Funcion para eliminar un producto (manteniendo registro) */

void eliminarProducto() {
    int codigo;
	int i;
	clrscr();
    printf("Ingrese el codigo del producto a eliminar: ");
    scanf("%d", &codigo);

    for (i = 0; i < num_productos; i++) {
        if (inventario[i].codigo == codigo) {
			printf("Producto %s eliminado (manteniendo registro).\n", inventario[i].nombre);
			getch();
            inventario[i].cantidad = 0;  /* Marcado como sin stock */
            return;
        }
    }
	printf("Producto no encontrado.\n");
	getch();
	clrscr();
}
clcsr();

/* Funcion para buscar un producto por codigo o nombre */
void buscarProducto() {
    int codigo;
    int opcion;
	int i;

	char nombre[MAX_LONG];
	clrscr();
    printf("Buscar por codigo (1) o nombre (2): ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        printf("Ingrese el codigo del producto: ");
        scanf("%d", &codigo);
        for ( i = 0; i < num_productos; i++) {
            if (inventario[i].codigo == codigo) {
                printf("Producto encontrado: %s, Cantidad: %d, Precio: %.2f, Unidad: %s\n",
					   inventario[i].nombre, inventario[i].cantidad, inventario[i].precio, inventario[i].unidad_medida);

				return;

            }
        }
    } else if (opcion == 2) {
        printf("Ingrese el nombre del producto: ");
        scanf("%s", nombre);
        for ( i = 0; i < num_productos; i++) {
            if (strcmp(inventario[i].nombre, nombre) == 0) {
                printf("Producto encontrado: Codigo: %d, Cantidad: %d, Precio: %.2f, Unidad: %s\n",
                       inventario[i].codigo, inventario[i].cantidad, inventario[i].precio, inventario[i].unidad_medida);
				return;
				getch();

            }
        }
    }

	printf("Producto no encontrado.\n");
	getch();
	clrscr();

}


/* Funcion para actualizar un producto en el inventario */
void actualizarProducto() {
    int codigo;
	int i;
	clrscr();
    printf("Ingrese el codigo del producto a actualizar: ");
    scanf("%d", &codigo);

    for (i = 0; i < num_productos; i++) {
        if (inventario[i].codigo == codigo) {
			printf("Actualizando producto %s...\n", inventario[i].nombre);
			getch();
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &inventario[i].precio);
            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &inventario[i].cantidad);
			printf("Actualizacion completada.\n");
			return;
			getch();
        }
    }
	printf("Producto no encontrado.\n");
	getch();
	clrscr();
}

/* Funcion para ver todo el inventario */      /*5*/

void verInventario() {
  int i;
  clrscr();
	gotoxy(29,4);
	clrscr();
	printf("\033[5;1;31m=== Inventario ===\033[0m\n");
    for (i = 0; i < num_productos; i++) {
	gotoxy(29,12);
	clrscr();
	printf("Codigo: %d, Producto: %s, Precio: %.2f, Cantidad: %d, Vence: %s, Unidad: %s\n",
               inventario[i].codigo, inventario[i].nombre, inventario[i].precio, inventario[i].cantidad,
			   inventario[i].fecha_vencimiento, inventario[i].unidad_medida);
			   getch();
			   clrscr();


	}
}

/* Funcion para vender un producto */
void venderProducto() {
    int codigo;
    int i;
	int cantidad_vender;
	clrscr();
    printf("Ingrese el codigo del producto a vender: ");
    scanf("%d", &codigo);

    for (i = 0; i < num_productos; i++) {
        if (inventario[i].codigo == codigo) {
            printf("Producto encontrado: %s, Precio: %.2f, Cantidad disponible: %d\n",
                   inventario[i].nombre, inventario[i].precio, inventario[i].cantidad);
            printf("Ingrese la cantidad a vender: ");
            scanf("%d", &cantidad_vender);

            if (inventario[i].cantidad >= cantidad_vender) {
                inventario[i].cantidad -= cantidad_vender;
				printf("Venta realizada. Producto restante: %d\n", inventario[i].cantidad);
				getch();
				clrscr();
            } else {
				printf("Cantidad insuficiente para la venta.\n");
				getch();
				clrscr();
            }
			return;
        }
    }
	printf("Producto no encontrado.\n");
	getch();
	clrscr();
}

/* Menu de Clientes */
void opcionCliente() {
	int opcion;
	clrscr();
	do {
	gotoxy(24,4);  printf("\033[1;36m |\033[0m\n");
	gotoxy(24,6);   printf("\033[1;33m |\033[0m\n");
	gotoxy(24,9);  printf("\033[1;31m |\033[0m\n");
	gotoxy(24,11); printf("\033[1;33m |\033[0m\n");
	gotoxy(24,13); printf("\033[1;31m |\033[0m\n");
	gotoxy(26,14); printf("\033[1;33m- - - - - - - - - - - - - - -\033[0m\n");
	gotoxy(26,3);  printf("\033[1;37m- - - - - - - - - - - - - - -\033[0m\n");
	gotoxy(54,4);  printf("\033[1;36m |\033[0m\n");
	gotoxy(54,6);  printf("\033[1;33m |\033[0m\n");
	gotoxy(54,9);  printf("\033[1;31m |\033[0m\n");
	gotoxy(54,11); printf("\033[1;33m |\033[0m\n");
	gotoxy(54,13); printf("\033[1;36m |\033[0m\n");

	gotoxy(29,4);	printf("\033[1;36m === Menu Clientes ===\033[0m\n");
	gotoxy(29,5);	printf("\033[1;37m1. Agregar Cliente\033[0m\n");
	gotoxy(29,6);	printf("\033[1;37m2. Eliminar Cliente\033[0m\n");
	gotoxy(29,7);	printf("\033[1;37m3. Buscar Cliente\033[0m\n");
	gotoxy(29,8);	printf("\033[1;37m4. Actualizar Cliente\033[0m\n");
	gotoxy(29,9);	printf("\033[1;37m5. Ver Clientes\033[0m\n");
	gotoxy(29,10);	printf("\033[1;37m6. Volver\033[0m\n");
	gotoxy(29,13);	printf("\033[1;38mElija una opcion: \033[0m\n");
	gotoxy(48,13);	scanf("%d", &opcion);


        switch (opcion) {
            case 1:
                agregarCliente();
                break;
            case 2:
                eliminarCliente();
                break;
            case 3:
                buscarCliente();
                break;
            case 4:
                actualizarCliente();
                break;
            case 5:
                verClientes();
                break;
			case 6:
                printf("Volviendo al menu principal...\n");
                break;
			default:
				gotoxy(30,14);
				printf("Opcion invalida. Intente de nuevo.\n");
				getch();
        }
    } while (opcion != 6);
}
clscr();
/* Funcion para validar que el celular tenga 8 digitos */
int validarCelular(const char* celular) {
  int i;
  clrscr();
    if (strlen(celular) != 8) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (celular[i] < '0' || celular[i] > '9') {
            return 0;
        }
    }
    return 1;
}
  clscr();
/* Funcion para agregar un cliente */
void agregarCliente() {
clrscr();
    if (num_clientes < MAX_CLIENTES) {
		struct Cliente c;
		clrscr();
        printf("Ingrese el nombre del cliente: ");
        scanf("%s", c.nombre);
        printf("Ingrese el codigo del cliente: ");
        scanf("%d", &c.codigo);

        do {
			printf("Ingrese el celular del cliente (8 digitos): ");
            scanf("%s", c.celular);
            if (!validarCelular(c.celular)) {
				printf("Numero de celular invalido. Debe tener exactamente 8 digitos y ser numerico.\n");
				getch();
            }
		} while (!validarCelular(c.celular));  /* Repite hasta que el numero sea valido  */

        printf("Ingrese la direccion del cliente: ");
        scanf("%s", c.direccion);
        printf("Ingrese el credito del cliente: ");
        scanf("%f", &c.credito);

        clientes[num_clientes++] = c;
		printf("Cliente agregado exitosamente.\n");
		getch();
		clrscr();
    } else {
		printf("La lista de clientes esta llena.\n");
		clrscr();
    }
}

/* Funcion para eliminar un cliente (no borrar, solo marcar) */
void eliminarCliente() {
    int codigo;
	int i;
	clrscr();
    printf("Ingrese el codigo del cliente a eliminar: ");
    scanf("%d", &codigo);

    for (i = 0; i < num_clientes; i++) {
        if (clientes[i].codigo == codigo) {
			printf("Cliente %s eliminado (manteniendo registro).\n", clientes[i].nombre);
			getch();
			clrscr();
            clientes[i].credito = 0;  /* Marcado como inactivo */
            return;
        }
    }
	printf("Cliente no encontrado.\n");
	getch();
	clrscr();
}
clscr();
/* Funcion para buscar un cliente por codigo o nombre */
void buscarCliente() {
    int codigo;
    int opcion;
	int i;
	char nombre[MAX_LONG];
	clrscr();
    printf("Buscar por codigo (1) o nombre (2): ");
    scanf("%d", &opcion);

	if (opcion == 1) {
		clrscr();
        printf("Ingrese el codigo del cliente: ");
        scanf("%d", &codigo);
        for (i = 0; i < num_clientes; i++) {
            if (clientes[i].codigo == codigo) {
                printf("Cliente encontrado: %s, Celular: %s, Direccion: %s, Credito: %.2f\n",
					   clientes[i].nombre, clientes[i].celular, clientes[i].direccion, clientes[i].credito);
				getch();
				clrscr();
				return;

            }
        }
	} else if (opcion == 2) {
	clrscr();
        printf("Ingrese el nombre del cliente: ");
		scanf("%s", nombre);
        for (i = 0; i < num_clientes; i++) {
            if (strcmp(clientes[i].nombre, nombre) == 0) {
                printf("Cliente encontrado: Codigo: %d, Celular: %s, Direccion: %s, Credito: %.2f\n",
					   clientes[i].codigo, clientes[i].celular, clientes[i].direccion, clientes[i].credito);
					   getch();
                return;
            }
        }
    }

	printf("Cliente no encontrado.\n");
	getch();
	clrscr();
}
clscr();
/* Funcion para actualizar un cliente */
void actualizarCliente() {
    int codigo;
	int i;
	clrscr();
    printf("Ingrese el codigo del cliente a actualizar: ");
    scanf("%d", &codigo);

    for (i = 0; i < num_clientes; i++) {
        if (clientes[i].codigo == codigo) {
            printf("Actualizando cliente %s...\n", clientes[i].nombre);
            printf("Ingrese el nuevo credito: ");
            scanf("%f", &clientes[i].credito);
			printf("Actualizacion completada.\n");
			getch();
			clrscr();
            return;
        }
    }
	printf("Cliente no encontrado.\n");
	getch();
	clrscr();
}
clscr();
/* Funcion para ver todos los clientes */
void verClientes() {
  int i;
  clrscr();
    printf("\n=== Lista de Clientes ===\n");
    for ( i = 0; i < num_clientes; i++) {
        printf("Codigo: %d, Nombre: %s, Celular: %s, Direccion: %s, Credito: %.2f\n",
			   clientes[i].codigo, clientes[i].nombre, clientes[i].celular, clientes[i].direccion, clientes[i].credito);
			   printf("\n");
			   getch();
			   clrscr();
    }
}
clscr();
/* Funcion para salir del programa */
void salir() {
clrscr();
gotoxy(29,5);
	printf("\033[1;34mSaliendo del programa...\033[0m\n");
	getch();
}
