/*
 * File: genSincLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 15-Sep-2026 23:18:06
 */

/* Include Files */
#include "genSincLogic.h"
#include "abs.h"
#include "colon.h"
#include "genSincLogic_emxutil.h"
#include "genSincLogic_types.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sinc.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>

/* Function Definitions */
/*
 * hack to allow memory size of t and x to grow
 *
 * Arguments    : double A
 *                double f
 *                double duration
 *                double Fs
 *                emxArray_real_T *t
 *                emxArray_real_T *x
 *                double *samples
 *                double *cycles
 * Return Type  : void
 */
void genSincLogic(double A, double f, double duration, double Fs,
                  emxArray_real_T *t, emxArray_real_T *x, double *samples,
                  double *cycles)
{
  __m128d r;
  emxArray_real_T *b_t;
  double dv[2];
  double a;
  double b;
  double d;
  double *a_data;
  double *b_t_data;
  double *t_data;
  int i;
  int loop_ub;
  int scalarLB;
  int vectorUB;
  /*  Simple matlab function to generate Sinc Wave */
  /*  Create a time vector centered around zero so that the main lobe */
  /*  of the sinc function appears near the middle of the plot. */
  a = -duration / 2.0;
  d = 1.0 / Fs;
  b = duration / 2.0;
  emxInit_real_T(&b_t, 2);
  t_data = b_t->data;
  if (rtIsNaN(a) || rtIsNaN(d) || rtIsNaN(b)) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    t_data = b_t->data;
    t_data[0] = rtNaN;
  } else if ((d == 0.0) || ((a < b) && (d < 0.0)) || ((b < a) && (d > 0.0))) {
    b_t->size[0] = 1;
    b_t->size[1] = 0;
  } else if ((rtIsInf(a) || rtIsInf(b)) && (rtIsInf(d) || (a == b))) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    t_data = b_t->data;
    t_data[0] = rtNaN;
  } else if (rtIsInf(d)) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    t_data = b_t->data;
    t_data[0] = a;
  } else if ((floor(a) == a) && (floor(d) == d)) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    loop_ub = (int)((b - a) / d);
    b_t->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    t_data = b_t->data;
    scalarLB = ((loop_ub + 1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
      dv[0] = i;
      dv[1] = i + 1;
      r = _mm_loadu_pd(&dv[0]);
      _mm_storeu_pd(&t_data[i],
                    _mm_add_pd(_mm_set1_pd(a), _mm_mul_pd(_mm_set1_pd(d), r)));
    }
    for (i = scalarLB; i <= loop_ub; i++) {
      t_data[i] = a + d * (double)i;
    }
  } else {
    eml_float_colon(a, d, b, b_t);
    t_data = b_t->data;
  }
  if (b_t->size[1] - 1 < 1) {
    loop_ub = 0;
  } else {
    loop_ub = b_t->size[1] - 1;
  }
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = loop_ub;
  emxEnsureCapacity_real_T(t, scalarLB);
  b_t_data = t->data;
  /*  MATLAB sinc(z) = sin(pi*z)/(pi*z). */
  /*  The factor 2*f controls the spacing of the zero crossings. */
  a = 2.0 * f;
  emxInit_real_T(&t, 2);
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = loop_ub;
  emxEnsureCapacity_real_T(t, scalarLB);
  a_data = t->data;
  scalarLB = (loop_ub / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&t_data[i]);
    _mm_storeu_pd(&b_t_data[i], r);
    _mm_storeu_pd(&a_data[i], _mm_mul_pd(_mm_set1_pd(a), r));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    d = t_data[i];
    b_t_data[i] = d;
    a_data[i] = a * d;
  }
  sinc(t, b_t);
  t_data = b_t->data;
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  loop_ub = b_t->size[1];
  t->size[1] = b_t->size[1];
  emxEnsureCapacity_real_T(t, scalarLB);
  a_data = t->data;
  scalarLB = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = b_t->size[1];
  emxEnsureCapacity_real_T(x, scalarLB);
  b_t_data = x->data;
  scalarLB = (b_t->size[1] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_mul_pd(_mm_set1_pd(A), _mm_loadu_pd(&t_data[i]));
    _mm_storeu_pd(&a_data[i], r);
    _mm_storeu_pd(&b_t_data[i], r);
  }
  for (i = scalarLB; i < loop_ub; i++) {
    a = A * t_data[i];
    a_data[i] = a;
    b_t_data[i] = a;
  }
  /*  Normalize the wave to ensure it fits within the amplitude range */
  b_abs(t, b_t);
  a = maximum(b_t);
  emxFree_real_T(&b_t);
  if (a > 0.0) {
    scalarLB = x->size[0] * x->size[1];
    x->size[0] = 1;
    loop_ub = t->size[1];
    x->size[1] = t->size[1];
    emxEnsureCapacity_real_T(x, scalarLB);
    b_t_data = x->data;
    scalarLB = (t->size[1] / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
      _mm_storeu_pd(
          &b_t_data[i],
          _mm_mul_pd(_mm_set1_pd(A),
                     _mm_div_pd(_mm_loadu_pd(&a_data[i]), _mm_set1_pd(a))));
    }
    for (i = scalarLB; i < loop_ub; i++) {
      b_t_data[i] = A * (a_data[i] / a);
    }
  }
  emxFree_real_T(&t);
  /*  "cycles" is not physically meaningful for a sinc wave because */
  /*  sinc is not periodic. Keep it as 2 for compatibility with the */
  /*  other generator interfaces. */
  a = 0.8 * (double)x->size[1];
  if (a >= 0.5) {
    scalarLB = (int)floor(a + 0.5);
  } else {
    scalarLB = 0;
  }
  scalarLB = (int)fmin(x->size[1], scalarLB);
  *samples = scalarLB;
  *cycles = 2.0;
}

/*
 * File trailer for genSincLogic.c
 *
 * [EOF]
 */
