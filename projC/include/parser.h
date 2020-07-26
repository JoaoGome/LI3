#ifndef PARSER_H
#define PARSER_H

int isLetra (char* line, int size);
int isNumero (char* line, int size);
int testaP (char* line);
int testaC (char* line);
int testaV (char* line);
char* parseVendas (char* line, int position);

#endif
