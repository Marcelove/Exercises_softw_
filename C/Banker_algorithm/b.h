int errorr;

FILE *commands;
FILE *customer;
FILE *resultado;

void updateneed(int **maximum, int **allocation, int **need, int clientes, int limite);

int isDigit(char a);//indentificar digitos

void pegadigitos(FILE *fp, int **matriz, int clientes, int limite);//extrair digitos

void printaMatriz(int **maximum, int **allocation, int **need, int clientes, int limite);//printa as matrizes

int lines (FILE *fp);//retornar o número de clientes

void updateavailable(int **allocation, int *resources, int clientes, int limite);//atualizar recursos

void verifyavailable(int **allocation, int *resources, int clientes, int limite);//atualizar recursos

int takeRequest(FILE *fp, int **allocation, int clientes, int limite, int *duplicatas);//realizar request

int takeRelease(FILE *fp, int **allocation, int clientes, int limite, int *duplicatas);//realizar release

void verifysafety (int **need, int *resources, int clientes, int limite);

void verifymaximum(int **allocation, int **maximum, int clientes, int limite);
