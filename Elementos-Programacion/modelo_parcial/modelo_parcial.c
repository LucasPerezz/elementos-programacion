/* Una empresa, que ofrece servicio de delivery a los comercios de la ciudad, quiere implementar una
aplicación para obtener datos estadísticos sobre sus servicios.
Se tiene un archivo con los, como máximo, 120 empleados que se encargan de las entregas. Este
archivo se llama “Repartidores.dat”, con un registro por empleado, sin orden, con el siguiente
diseño de registro:
Número de legajo (int, 4 dígitos)
Apellido y nombre (alfanumérico, 30 caracteres)
Cantidad de entregas acumuladas hasta el mes de mayo (int)
Se cuenta también con el archivo “PedidosJunio.dat” con los pedidos entregados en el mes de junio,
ordenado alfabéticamente por nombre del comercio, con el siguiente diseño de registro:
Nombre del comercio (alfanumérico, 20 caracteres)
Día del pedido (int, 1 a 30)
Legajo del empleado que realizó la entrega (int, 4 dígitos)
Importe del pedido (float)
Si el número de legajo no se encuentra no procesar el pedido.
Realizar un programa en lenguaje C, para:
1) Actualizar el archivo “Repartidores.dat” incrementando la cantidad de entregas con las del
mes de junio.
2) Informar el importe recaudado en cada día del mes de junio.
3) Generar el archivo “ComerciosJunio.dat”, ordenado alfabéticamente, con un registro por
cada comercio que recibió pedidos en junio, con el siguiente formato:
Nombre del comercio (alfanumérico, 20 caracteres)
Cantidad de pedidos de junio (int)
Importe total de las entregas de junio (float)
Realizar como mínimo funciones para:
a) Almacenar los datos del archivo en memoria.
b) Realizar búsqueda en un vector. */

#include <stdio.h>
#include <string.h>

typedef struct
{
    int nroLegajo;
    char nomApe[31];
    int cantEntregas;
}T_REPARTIDORES;

typedef struct
{
    char nomComercio[21];
    int diaPedido;
    int nroLegajo;
    float importePedido;
}T_PEDIDOS;

typedef struct
{
    char nomComercio[21];
    int cantPedidos;
    float importeTotal;
}T_REGISTRO;

int contadorRepartidores(char[], T_REPARTIDORES[], int);
int busqueda(T_REPARTIDORES[], int, int);
void actualizarInfoRepartidores(char[], T_REPARTIDORES[], int);
void actualizarArchivo(char[], T_REPARTIDORES[], int);
void generarArchivo(char[], char[], float[]);
void mostrarDias(float[], int);
void mostrarArchivo(char[]);

int main()
{
    T_REPARTIDORES vRepartidores[120];
    float vRecaudacionDia[30] = {0};
    int cant;
    cant = contadorRepartidores("repartidores.dat", vRepartidores, 120);
    actualizarInfoRepartidores("pedidosjunio.dat", vRepartidores, cant);
    actualizarArchivo("repartidores.dat", vRepartidores, cant);
    generarArchivo("pedidosJunio.dat", "comerciosJunio.dat", vRecaudacionDia);
    mostrarDias(vRecaudacionDia, 30);
    mostrarArchivo("pedidosJunio.dat");

    return 0;

}

int contadorRepartidores(char nomArch[], T_REPARTIDORES v[], int ce)
{
    int i;
    T_REPARTIDORES rep;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&rep, sizeof(T_REPARTIDORES), 1, arch);
        while(!feof(arch))
        {
            i++;
            fread(&rep, sizeof(T_REPARTIDORES), 1, arch);
        }
        fclose(arch);
    }

    return i;
}

int busqueda(T_REPARTIDORES v[], int ce, int bus)
{
    int i, pos;
    i = 0;
    pos = -1;
    while(i < ce && pos == -1)
    {
        if(v[pos].nroLegajo == bus)
        {
            pos = i;
        }
        i++;
    }

    return pos;
}

void actualizarInfoRepartidores(char nomArch[], T_REPARTIDORES v[], int ce)
{
    int pos;
    T_PEDIDOS ped;
    FILE*arch;
    arch = fopen(nomArch ,"rb");
    if(arch == NULL)
    {
        printf("No se puede abrir el archivo");
    }
    else
    {
        fread(&ped, sizeof(T_PEDIDOS), 1, arch);
        while(!feof(arch))
        {
            pos = busqueda(v, ce, ped.nroLegajo);
            v[pos].cantEntregas++;
            fread(&ped, sizeof(T_PEDIDOS), 1, arch);
        }

        fclose(arch);
    }
}

void actualizarArchivo(char nomArch[], T_REPARTIDORES v[], int ce)
{
    T_REPARTIDORES rep;
    int i;
    FILE*arch;
    arch = fopen(nomArch, "wb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        for(i = 0; i < ce; i++)
        {
            fwrite(&v[i], sizeof(T_REPARTIDORES), 1, arch);
        }

        fclose(arch);
    }
}

void generarArchivo(char nomArch[], char nomArch2[], float v[])
{
    T_REGISTRO reg;
    T_PEDIDOS ped;
    char comercioAnterior[21];
    float impxComercio;
    int cantxComercio;
    FILE*arch;
    FILE*arch2;
    arch = fopen(nomArch, "rb");
    arch2 = fopen(nomArch2, "wb");
    if(arch == NULL || arch2 == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        fread(&ped, sizeof(T_PEDIDOS), 1, arch);
        while(!feof(arch))
        {
            strcpy(comercioAnterior, ped.nomComercio);
            impxComercio = 0;
            cantxComercio = 0;
            while(strcmpi(comercioAnterior, ped.nomComercio) == 0 && !feof(arch))
            {
                impxComercio += ped.importePedido;
                cantxComercio++;
                v[ped.diaPedido - 1] += ped.importePedido;
                fread(&ped, sizeof(T_PEDIDOS), 1, arch);
            }
            reg.cantPedidos = cantxComercio;
            reg.importeTotal = impxComercio;
            strcpy(reg.nomComercio, comercioAnterior);
            fwrite(&reg, sizeof(T_REGISTRO), 1, arch2);
        }

        fclose(arch);
        fclose(arch2);
    }

}

void mostrarDias(float v[], int ce)
{
    int i;

    for(i = 0; i < ce; i++)
    {
        printf("DIA %d \t DINERO RECAUDADO: %.2f\n\n\n", i + 1, v[i]);
    }
}

void mostrarArchivo(char nomArch[])
{
    T_REGISTRO reg;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        printf("*********INFORMACION COMERCIOS***********\n\n");
        fread(&reg, sizeof(T_REGISTRO), 1, arch);
        while(!feof(arch))
        {
            puts(reg.nomComercio);
            printf("PEDIDOS: %d\n", reg.cantPedidos);
            printf("IMPORTE: %.2f\n\n\n", reg.importeTotal);
        }
    }
}

