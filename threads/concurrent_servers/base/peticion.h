#ifndef PETICION_H
#define PETICION_H

struct peticion {
  long id;
  /* Resto de campos necesarios */
  int tipo;
  char url[80];
  /* ... */
};

typedef struct peticion peticion_t;

void recibir_peticion(peticion_t *p);
void responder_peticion(peticion_t *p);

#endif
