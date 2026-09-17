/*
 * File: genSincLogic_types.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 15-Sep-2026 23:18:06
 */

#ifndef GENSINCLOGIC_TYPES_H
#define GENSINCLOGIC_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#endif
/*
 * File trailer for genSincLogic_types.h
 *
 * [EOF]
 */
