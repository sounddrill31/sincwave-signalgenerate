/*
 * File: sinc.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 15-Sep-2026 23:18:06
 */

/* Include Files */
#include "sinc.h"
#include "genSincLogic_emxutil.h"
#include "genSincLogic_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void sinc(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int i;
  int i1;
  int k;
  x_data = x->data;
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  i1 = x->size[1];
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  for (k = 0; k < i1; k++) {
    double d;
    d = x_data[k];
    if (d == 0.0) {
      y_data[k] = 1.0;
    } else {
      double r;
      boolean_T negateSinpi;
      r = d;
      if (d < 0.0) {
        r = -d;
        negateSinpi = true;
      } else {
        negateSinpi = false;
      }
      if (r < 0.25) {
        r = sin(r * 3.141592653589793);
      } else {
        r -= 2.0 * floor(r / 2.0);
        if (r < 0.25) {
          r = sin(r * 3.141592653589793);
        } else if (r < 0.75) {
          r = 0.5 - r;
          r = cos(r * 3.141592653589793);
        } else if (r < 1.25) {
          r = 1.0 - r;
          r = sin(r * 3.141592653589793);
        } else if (r < 1.75) {
          r -= 1.5;
          r = -cos(r * 3.141592653589793);
        } else {
          r -= 2.0;
          r = sin(r * 3.141592653589793);
        }
      }
      if (negateSinpi) {
        r = -r;
      }
      y_data[k] = r / (3.141592653589793 * d);
    }
  }
}

/*
 * File trailer for sinc.c
 *
 * [EOF]
 */
