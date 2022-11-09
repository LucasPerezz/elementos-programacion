#include <stdio.h>
#include <string.h>

typedef struct
{
    char sucursal[16];
    int codigoProducto;
    int cantidad;
} T_SUCURSALES;

typedef struct
{
    int codigoProducto;
    char descripcion[21];
    float precio;
    int stock;
    int puntoPedido;
    int cantidadPedido;
} T_PRODUCTOS;

typedef struct
{
    int codigo;
    int cantidad;
} T_LLAMADAS;

int cantidadProductos(char[]);
void copiarArchivo(char[], T_PRODUCTOS[], int);
int busqueda(T_PRODUCTOS[], int, int);
void procesarDatos(char[], char[], char[], T_PRODUCTOS[], int);
void actualizarArchivo(char[], T_PRODUCTOS[], int);

int main()
{
    int cant;
    T_PRODUCTOS vProductos[200];
    cant = cantidadProductos("PRODUCTOS-11_2.dat");
    copiarArchivo("PRODUCTOS-11_2.dat", vProductos, cant);
    procesarDatos("PRODUCTOS-11_2.dat", "VENTAS-11_2.dat", "LLAMADAS-11_2.dat", vProductos, cant);
    actualizarArchivo("PRODUCTOS-11_2.dat", vProductos, cant);

    return 0;
}

int cantidadProductos(char nomArch[])
{
    T_PRODUCTOS prod;
    int i;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        i = 0;
        fread(&prod, sizeof(T_PRODUCTOS), 1, arch);
        while(!feof(arch))
        {
            i++;
            fread(&prod, sizeof(T_PRODUCTOS), 1, arch);
        }

        fclose(arch);
    }

    return i;
}

void copiarArchivo(char nomArch[], T_PRODUCTOS v[], int ce)
{
    T_PRODUCTOS prod;
    int i;
    FILE*arch;
    arch = fopen(nomArch, "rb");
    if(arch == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        i = 0;
        fread(&prod, sizeof(T_PRODUCTOS), 1, arch);
        while(!feof(arch) && i < ce)
        {
            v[i] = prod;
            i++;
            fread(&prod, sizeof(T_PRODUCTOS), 1, arch);
        }

        fclose(arch);
    }
}

int busqueda(T_PRODUCTOS v[], int ce, int bus)
{
    int i = 0, pos = -1;

    while(i < ce && pos == -1)
    {
        if(v[i].codigoProducto == bus)
        {
            pos = i;
        }
        i++;
    }

    return pos;
}



void procesarDatos(char archProductos[], char archSucursal[], char archLlamadas[], T_PRODUCTOS v[], int ce)
{
    float sucursalTotal, recaudacionTotal, maxTotal;
    int productos, band, pos;
    int cantPorSuc;
    char maxSucursal[16];
    char sucursalAnterior[16];
    T_PRODUCTOS prod;
    T_SUCURSALES suc;
    T_LLAMADAS llam;
    FILE*archivoProducto;
    FILE*archivoSucursal;
    FILE*archivoLlamadas;
    archivoProducto = fopen(archProductos, "wb");
    archivoSucursal = fopen(archSucursal, "rb");
    archivoLlamadas = fopen(archLlamadas, "ab");
    if(archivoProducto == NULL || archivoSucursal == NULL || archivoLlamadas == NULL)
    {
        printf("No se pudo abrir el archivo");
    }
    else
    {
        recaudacionTotal = 0;
        fread(&suc, sizeof(T_SUCURSALES), 1, archivoSucursal);
        while(!feof(archivoSucursal))
        {
            band = 0;
            sucursalTotal = 0;
            cantPorSuc = 0;
            strcpy(sucursalAnterior, suc.sucursal);
            while(strcmpi(sucursalAnterior, suc.sucursal) == 0 && !feof(archivoSucursal))
            {
                pos = busqueda(v, ce, suc.codigoProducto);
                sucursalTotal += v[pos].precio * suc.cantidad;
                recaudacionTotal += v[pos].precio * suc.cantidad;
                cantPorSuc += suc.cantidad;
                if(suc.cantidad > v[pos].stock)
                {
                    llam.codigo = suc.codigoProducto;
                    llam.cantidad = suc.cantidad;
                    fwrite(&llam, sizeof(T_LLAMADAS), 1, archivoLlamadas);
                }
                else
                {
                    v[pos].stock -= suc.cantidad;
                }

                if(band == 0 || sucursalTotal > maxTotal)
                {
                    strcpy(maxSucursal, suc.sucursal);
                    maxTotal = cantPorSuc;
                    band = 1;
                }
                fread(&suc, sizeof(T_SUCURSALES), 1, archivoSucursal);
            }


            printf("IMPORTE TOTAL DE SUCURSAL ");
            puts(suc.sucursal);
            printf("$%.2f\n\n\n\n", sucursalTotal);
        }
        printf("\nRECAUDACION TOTAL DE LA EMPRESA: $%.2f\n", recaudacionTotal);
        printf("SUCURSAL CON MAYOR CANTIDAD DE PRODUCTOS VENDIDOS: ");
        puts(maxSucursal);

        fclose(archivoLlamadas);
        fclose(archivoProducto);
        fclose(archivoSucursal);
    }
}

void actualizarArchivo(char nomArch[], T_PRODUCTOS v[], int ce)
{
    T_PRODUCTOS prod;
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
            fwrite(&v[i], sizeof(T_PRODUCTOS), 1, arch);
        }

        fclose(arch);
    }
}