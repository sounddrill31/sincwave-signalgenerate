/*
 * File: genSincLogic.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 15-Sep-2026 23:18:06
 */

#ifndef GENSINCLOGIC_H
#define GENSINCLOGIC_H

/* Include Files */
#include "genSincLogic_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void genSincLogic(double A, double f, double duration, double Fs,
                         emxArray_real_T *t, emxArray_real_T *x,
                         double *samples, double *cycles);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for genSincLogic.h
 *
 * [EOF]
 */
