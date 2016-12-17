/*
 * OWL - an OCaml numerical library for scientific computing
 * Copyright (c) 2016 Liang Wang <liang.wang@cl.cam.ac.uk>
 */

#include "owl_macros.h"

#ifndef NAME
#define NAME _uninit_vec_cmp_function
#endif /* NAME */

#ifndef NUMBER
#define NUMBER double
#endif /* NUMBER */

#ifndef STOPFN
#define STOPFN(X, Y) (X < Y)
#endif /* NUMBER */


CAMLprim value NAME(value vN, value vX, value vY)
{
  CAMLparam2(vX, vY);
  int N = Long_val(vN);

  struct caml_ba_array *big_X = Caml_ba_array_val(vX);
  CAMLunused int dim_X = *big_X->dim;
  NUMBER *X_data = ((NUMBER *) big_X->data);

  struct caml_ba_array *big_Y = Caml_ba_array_val(vY);
  CAMLunused int dim_Y = *big_Y->dim;
  NUMBER *Y_data = ((NUMBER *) big_Y->data);

  NUMBER *start_x, *stop_x, *start_y;

  caml_enter_blocking_section();  /* Allow other threads */

  start_x = X_data;
  stop_x = start_x + N;
  start_y = Y_data;

  int r = 1;

  while (start_x != stop_x) {
    NUMBER x = *start_x;
    NUMBER y = *start_y;

    if (STOPFN(x, y)) {
      r = 0;
      break;
    }

    start_x += 1;
    start_y += 1;
  };

  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(r));
}


#undef STOPFN
#undef NUMBER
#undef NAME
