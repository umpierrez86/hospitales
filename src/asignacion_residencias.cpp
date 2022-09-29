/*5083168*/
/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include "../include/pila.h"
#include <cstddef>

Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs)
{
    //hospitales con cupos libres
    Pila libres = crear_pila();
    for(nat i = 0; i < m; i++){
      apilar(i,libres);
    }

    //hospitales donde se encuentran los estudiantes
    int *current = new int[n];
    for(nat i = 0; i < n; i++){
      current[i] = -1;
    }

    //ranking de preferencias de estudiantes
    nat **ranking = new nat*[n];
    for(nat i = 0; i < n; i++){
      ranking[i] = new nat[m];
    }
    for(nat i = 0; i < n; i++){
      for(nat j = 0; j < m; j++){
        nat pref = ePrefs[i][j];
        ranking[i][pref] = j;
      }
    }

    //proximo estudiante en la lista de preferncias del hospital al cual no se propuso
    nat *next = new nat[m];
    for(nat i = 0; i < n; i++){
      next[i] = 0;
    }
    
    //lista de parejas
    Asignacion parejas = crear_asignacion();

    //suma de cupos
    nat *cupos = new nat[m];
    for(nat i = 0; i < m; i++){
      cupos[i] = C[i];
    }

    //emparejamiento
    while(es_vacia_pila(libres)){
        nat h = cima(libres);
        nat estudiante = hPrefs[h][next[h]];
        if(current[estudiante] == -1){
          //Par p = { .eid = estudiante, .hid = h };
          //insertar_par(p,parejas);
          current[estudiante] = h;
          //next[h] = next[h] + 1;
          cupos[h] = cupos[h] - 1;
          if(cupos[h] == 0){
            desapilar(libres);
          }
        }else{
          nat actual = current[estudiante];
          if(ranking[estudiante][actual] > ranking[estudiante][h]){
            current[estudiante] = h;
            cupos[actual] = cupos[actual] + 1;
            cupos[h] = cupos[h] - 1;
            if(cupos[h] == 0){
              desapilar(libres);
            }
            if(cupos[actual] > 0){
              apilar(actual,libres);
            }
          }
        }
        next[h] = next[h] + 1;
    }

    //asigno las parejas en la lista
    for(nat i = 0; i < n; i++){
      par p;
      p.eid = 0;
      p.hid = 0;
      insertar_par(p,parejas);
    }

    //liberar memoria
    destruir_pila(libres);
    delete [] current;
    delete [] next;
    delete [] cupos;
    for(nat i = 0; i < n; i++)
      delete [] ranking[i];
    delete [] ranking;
    
    return NULL; // se debe retornar algo de tipo asignacion
}
