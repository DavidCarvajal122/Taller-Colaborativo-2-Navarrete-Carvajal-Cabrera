#include <stdio.h>
#include <string.h>


#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100

// Funcion clientes empieza
// Función para ingresar un cliente
void ingresarCliente(FILE *archivo, char nombres[][50], char cedulas[][11], int *numClientes) {
    if (*numClientes < MAX_CLIENTES) {
        char nuevaCedula[11];
        int cedulaExistente = 0;

        do {
            printf("Ingrese la cédula del cliente (10 dígitos): ");
            scanf("%s", nuevaCedula);

            // Validar la cédula según el formato de cédula ecuatoriana
            if (strlen(nuevaCedula) == 10) {
                cedulaExistente = 0;

                // Verificar si la cédula ya existe en el archivo
                fseek(archivo, 0, SEEK_SET);
                while (!feof(archivo)) {
                    char cedulaArchivo[11];
                    fscanf(archivo, "%s", cedulaArchivo);

                    if (strcmp(cedulaArchivo, nuevaCedula) == 0) {
                        printf("Ya existe un cliente con esta cédula. Ingrese una cédula diferente.\n");
                        cedulaExistente = 1;
                        break;
                    }
                }
            } else {
                printf("La cédula debe tener 10 dígitos. Ingrese una cédula válida.\n");
            }

        } while (strlen(nuevaCedula) != 10 || cedulaExistente);

        strcpy(cedulas[*numClientes], nuevaCedula);

        printf("Ingrese el nombre del cliente: ");
        scanf("%s", nombres[*numClientes]);

        // Guardar los datos en el archivo
        fprintf(archivo, "%s %s\n", cedulas[*numClientes], nombres[*numClientes]);

        (*numClientes)++;
        printf("Cliente ingresado correctamente.\n");
    } else {
        printf("No se pueden ingresar más clientes. Límite alcanzado.\n");
    }
}

// Función para modificar un cliente
void modificarCliente(FILE *archivo, char nombres[][50], char cedulas[][11], int numClientes) {
    char cedula[11];
    int cedulaExistente = 0;

    printf("Ingrese la cédula del cliente que desea modificar: ");
    scanf("%s", cedula);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(cedulas[i], cedula) == 0) {
            printf("Ingrese el nuevo nombre del cliente: ");
            scanf("%s", nombres[i]);

            // Actualizar los datos en el archivo
            fseek(archivo, 0, SEEK_SET);
            FILE *temp = fopen("temp.txt", "w");

            while (!feof(archivo)) {
                char cedulaArchivo[11];
                fscanf(archivo, "%s", cedulaArchivo);

                if (!feof(archivo)) {
                    if (strcmp(cedulaArchivo, cedula) == 0) {
                        fprintf(temp, "%s %s\n", cedula, nombres[i]);
                    } else {
                        char nombreArchivo[50];
                        fscanf(archivo, "%s", nombreArchivo);
                        fprintf(temp, "%s %s\n", cedulaArchivo, nombreArchivo);
                    }
                }
            }

            fclose(archivo);
            fclose(temp);

            remove("clientes.txt");
            rename("temp.txt", "clientes.txt");

            printf("Cliente modificado correctamente.\n");
            return;
        }
    }

    printf("Cliente no encontrado.\n");
}

// Función para consultar un cliente
void consultarCliente(char nombres[][50], char cedulas[][11], int numClientes) {
    char cedula[11];

    printf("Ingrese la cédula del cliente que desea consultar: ");
    scanf("%s", cedula);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(cedulas[i], cedula) == 0) {
            printf("Nombre: %s, Cédula: %s\n", nombres[i], cedulas[i]);
            return;
        }
    }

    printf("Cliente no encontrado.\n");
}

// Función para ver el listado de clientes
void verListadoClientes(char nombres[][50], char cedulas[][11], int numClientes) {
    printf("Listado de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Nombre: %s, Cédula: %s\n", nombres[i], cedulas[i]);
    }
}
// funciones de clientes finaliza
//Funcion de productos empieza
// Función para ingresar un producto
void ingresarProducto(char nombres[][50], int codigos[], float precios[], int cantidades[], int *numProductos) {
    if (*numProductos < MAX_PRODUCTOS) {
        printf("Ingrese el nombre del producto: ");
        scanf("%s", nombres[*numProductos]);

        printf("Ingrese el código del producto: ");
        scanf("%d", &codigos[*numProductos]);

        printf("Ingrese el precio del producto: ");
        scanf("%f", &precios[*numProductos]);

        printf("Ingrese la cantidad del producto: ");
        scanf("%d", &cantidades[*numProductos]);

        (*numProductos)++;
        printf("Producto ingresado correctamente.\n");
    } else {
        printf("No se pueden ingresar más productos. Límite alcanzado.\n");
    }
}

// Función para editar un producto
void editarProducto(char nombres[][50], int codigos[], float precios[], int cantidades[], int numProductos) {
    int codigo;
    printf("Ingrese el código del producto que desea editar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < numProductos; i++) {
        if (codigos[i] == codigo) {
            printf("Ingrese el nuevo nombre del producto: ");
            scanf("%s", nombres[i]);

            printf("Ingrese el nuevo precio del producto: ");
            scanf("%f", &precios[i]);

            printf("Ingrese la nueva cantidad del producto: ");
            scanf("%d", &cantidades[i]);

            printf("Producto editado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

// Función para eliminar un producto
void eliminarProducto(char nombres[][50], int codigos[], float precios[], int cantidades[], int *numProductos) {
    int codigo;
    printf("Ingrese el código del producto que desea eliminar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *numProductos; i++) {
        if (codigos[i] == codigo) {
            // Eliminar el producto moviendo los elementos siguientes hacia atrás
            for (int j = i; j < (*numProductos - 1); j++) {
                strcpy(nombres[j], nombres[j + 1]);
                codigos[j] = codigos[j + 1];
                precios[j] = precios[j + 1];
                cantidades[j] = cantidades[j + 1];
            }
            (*numProductos)--;
            printf("Producto eliminado correctamente.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

// Función para listar todos los productos
void listarProductos(char nombres[][50], int codigos[], float precios[], int cantidades[], int numProductos) {
    printf("Lista de productos:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Nombre: %s, Código: %d, Precio: %.2f, Cantidad: %d\n",
               nombres[i], codigos[i], precios[i], cantidades[i]);
    }
}

// Función para guardar los datos en un archivo
void guardarDatosEnArchivo(char nombres[][50], int codigos[], float precios[], int cantidades[], int numProductos) {
    FILE *archivo = fopen("inventario.txt", "w");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s %d %.2f %d\n", nombres[i], codigos[i], precios[i], cantidades[i]);
    }

    fclose(archivo);
    printf("Datos guardados en el archivo correctamente.\n");
}
//Funcion de productos finaliza

//funcion facturas empieza
// Función para ingresar una factura
void facturar(
    char fechas[][20], char cedulasFactura[][11], char nombresFactura[][50],
    float valoresPagados[], int cantidadesProductos[], int *numFacturas,
    char nombres[][50], char cedulas[][11], int numClientes,
    int codigos[], float precios[], int cantidades[], int numProductos
) {
    if (*numFacturas < MAX_FACTURAS) {
        char fecha[20];
        char cedula[11];
        char nombre[50];
        float valorPagado = 0;
        int cantidadProductos = 0;

        int clienteExistente = 0;

        // Ingresar información de la factura
        printf("Ingrese la fecha de la factura: ");
        scanf("%s", fecha);

        do {
            printf("Ingrese la cédula del cliente: ");
            scanf("%s", cedula);

            // Verificar si la cédula del cliente existe
            for (int i = 0; i < numClientes; i++) {
                if (strcmp(cedulas[i], cedula) == 0) {
                    clienteExistente = 1;
                    break;
                }
            }

            if (!clienteExistente) {
                printf("No existe un cliente con esta cédula. Ingrese una cédula válida.\n");
            }

        } while (!clienteExistente);

        // Obtener el nombre del cliente
        for (int i = 0; i < numClientes; i++) {
            if (strcmp(cedulas[i], cedula) == 0) {
                strcpy(nombre, nombres[i]);
                break;
            }
        }

        // Ingresar detalles de los productos comprados
        int seguirComprando;
        do {
            int codigoProducto;
            printf("Ingrese el código del producto: ");
            scanf("%d", &codigoProducto);

            // Buscar el producto en el inventario
            int indiceProducto = -1;
            for (int i = 0; i < numProductos; i++) {
                if (codigos[i] == codigoProducto) {
                    indiceProducto = i;
                    break;
                }
            }

            if (indiceProducto != -1) {
                // El producto existe, actualizar la factura
                valorPagado += precios[indiceProducto];
                cantidadProductos++;
            } else {
                printf("Producto no encontrado en el inventario. Ingrese un código válido.\n");
            }

            printf("¿Desea agregar otro producto? (1: Sí, 0: No): ");
            scanf("%d", &seguirComprando);

        } while (seguirComprando);

        // Guardar la factura en los arreglos correspondientes
        strcpy(fechas[*numFacturas], fecha);
        strcpy(cedulasFactura[*numFacturas], cedula);
        strcpy(nombresFactura[*numFacturas], nombre);
        valoresPagados[*numFacturas] = valorPagado;
        cantidadesProductos[*numFacturas] = cantidadProductos;

        (*numFacturas)++;

        printf("Factura generada correctamente.\n");
    } else {
        printf("No se pueden generar más facturas. Límite alcanzado.\n");
    }
}

// Función para buscar una factura por cédula del cliente
void buscarFactura(
    char fechas[][20], char cedulasFactura[][11], char nombresFactura[][50],
    float valoresPagados[], int cantidadesProductos[], int numFacturas
) {
    char cedulaBusqueda[11];
    printf("Ingrese la cédula del cliente para buscar la factura: ");
    scanf("%s", cedulaBusqueda);

    for (int i = 0; i < numFacturas; i++) {
        if (strcmp(cedulasFactura[i], cedulaBusqueda) == 0) {
            printf("Factura encontrada:\n");
            printf("Fecha: %s\n", fechas[i]);
            printf("Cédula: %s\n", cedulasFactura[i]);
            printf("Nombre: %s\n", nombresFactura[i]);
            printf("Valor Pagado: %.2f\n", valoresPagados[i]);
            printf("Cantidad de Productos: %d\n", cantidadesProductos[i]);
            return;
        }
    }

    printf("No se encontró ninguna factura para la cédula proporcionada.\n");
}

// Función para ver el listado de facturas
void verListadoFacturas(
    char fechas[][20], char cedulasFactura[][11], char nombresFactura[][50],
    float valoresPagados[], int cantidadesProductos[], int numFacturas
) {
    printf("Listado de Facturas:\n");
    for (int i = 0; i < numFacturas; i++) {
        printf("Factura %d:\n", i + 1);
        printf("Fecha: %s\n", fechas[i]);
        printf("Cédula: %s\n", cedulasFactura[i]);
        printf("Nombre: %s\n", nombresFactura[i]);
        printf("Valor Pagado: %.2f\n", valoresPagados[i]);
        printf("Cantidad de Productos: %d\n", cantidadesProductos[i]);
        printf("------------------------\n");
    }
}


int main(){
  int opcprincipal;
  int opccliente;
  int opcproducto;
  char nombres[MAX_PRODUCTOS][50];
  int codigos[MAX_PRODUCTOS];
  float precios[MAX_PRODUCTOS];
  int cantidades[MAX_PRODUCTOS];
  int numProductos = 0;
  char nombresC[MAX_CLIENTES][50];
  char cedulas[MAX_CLIENTES][11];
  int numClientes = 0;
  char fechas[MAX_FACTURAS][20];
  char cedulasFactura[MAX_FACTURAS][11];
  char nombresFactura[MAX_FACTURAS][50];
  float valoresPagados[MAX_FACTURAS];
  int cantidadesProductos[MAX_FACTURAS];
  int numFacturas = 0;
  FILE *archivo = fopen("clientes.txt", "a+");

  if (archivo == NULL) {
      printf("No se pudo abrir el archivo para leer/escribir.\n");
      return 1;
  }
  // Leer los datos del archivo al inicio del programa
  while (!feof(archivo)) {
      fscanf(archivo, "%s %s", cedulas[numClientes], nombres[numClientes]);
      numClientes++;
  }
  do {
    printf("1: Ingresar datos del Cliente\n");
    printf("2: Ingresar datos de los Productos\n");
    printf("3: Facturar\n");
    printf("4: Buscar Factura\n");
    printf("5: Ver listado de Facturas\n");
    printf("6: Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcprincipal);
    switch(opcprincipal){
      case 1:
        printf("\nIngresos del cliente\n");
        do {
          printf("\n1. Datos del cliente\n");
          printf("2. Modificar cliente\n");
          printf("3. Consultar cliente\n");
          printf("4. Ver listado de clientes\n");
          printf("5. Salir\n");
          printf("Seleccione una opción: ");
          scanf("%d", &opccliente);

          switch (opccliente) {
              case 1:
                  ingresarCliente(archivo, nombres, cedulas, &numClientes);
                  break;
              case 2:
                  modificarCliente(archivo, nombres, cedulas, numClientes);
                  break;
              case 3:
                  consultarCliente(nombres, cedulas, numClientes);
                  break;
              case 4:
                  verListadoClientes(nombres, cedulas, numClientes);
                  break;
              case 5:
                  printf("Saliendo de la seccion de clientes...\n");
                  break;
              default:
                  printf("Opción no válida. Intente de nuevo.\n");
          }
        }while(opccliente != 5);

      break;
      case 2:
        printf("Ingresos de los productos\n");
        do {
            printf("\n1. Ingresar producto\n");
            printf("2. Editar producto\n");
            printf("3. Eliminar producto\n");
            printf("4. Listar productos\n");
            printf("5. Salir\n");
            printf("Seleccione una opción: ");
            scanf("%d", &opcproducto);

            switch (opcproducto) {
                case 1:
                    ingresarProducto(nombres, codigos, precios, cantidades, &numProductos);
                  guardarDatosEnArchivo(nombres, codigos, precios, cantidades, numProductos);
                    break;
                case 2:
                    editarProducto(nombres, codigos, precios, cantidades, numProductos);
                  guardarDatosEnArchivo(nombres, codigos, precios, cantidades, numProductos);
                    break;
                case 3:
                    eliminarProducto(nombres, codigos, precios, cantidades, &numProductos);
                  guardarDatosEnArchivo(nombres, codigos, precios, cantidades, numProductos);
                    break;
                case 4:
                    listarProductos(nombres, codigos, precios, cantidades, numProductos);
                    break;
                case 5:
                    printf("Saliendo de la seccion de productos...\n");
                    break;
                default:
                    printf("Opción no válida. Intente de nuevo.\n");
            }
        } while (opcproducto != 5);

      break;
      case 3:
          facturar(
              fechas, cedulasFactura, nombresFactura,
              valoresPagados, cantidadesProductos, &numFacturas,
              nombres, cedulas, numClientes, codigos, precios, cantidades, numProductos
          );
          break;
      case 4:
          buscarFactura(
              fechas, cedulasFactura, nombresFactura,
              valoresPagados, cantidadesProductos, numFacturas
          );
          break;
      case 5:
          verListadoFacturas(
              fechas, cedulasFactura, nombresFactura,
              valoresPagados, cantidadesProductos, numFacturas
          );
          break;
      case 6:
        printf("Saliendo del programa...\n");
      break;
      default:
      printf("Opción no válida. Intente de nuevo.\n");
    }
  }while(opcprincipal!=6);

  fclose(archivo);
  return 0;
}

