/*******************************************************************************/
/* Header File Name: dapdsStruct64_t.h                                         */  
/*                                                                             */
/* Descriptive-name: Definitions for Tivoli Storage Manager external           */
/*                    dsStruct64_t routines                                    */ 
/*******************************************************************************/
#define DS_EQUAL         0
#define DS_GREATERTHAN   1
#define DS_LESSTHAN     -1

#define dCmp64(x,y) \
  ((x)->hi > (y)->hi ? DS_GREATERTHAN : \
       ((x)->hi < (y)->hi ? DS_LESSTHAN : \
               ((x)->lo > (y)->lo ? DS_GREATERTHAN : \
                          ((x)->lo < (y)->lo ? DS_LESSTHAN : DS_EQUAL))))

extern dsStruct64_t dMake64( dsUint32_t n );
extern dsStruct64_t dIncr64( dsStruct64_t *x, dsUint32_t n );
extern dsStruct64_t dDecr64( dsStruct64_t *x, dsUint32_t n );
extern dsStruct64_t dAdd64( dsStruct64_t *x, dsStruct64_t *y );
extern dsStruct64_t dSub64( dsStruct64_t *x, dsStruct64_t *y );

extern void  dShiftR64( dsStruct64_t *x, unsigned int b );
extern void  dShiftL64( dsStruct64_t *x, unsigned int b );

extern dsStruct64_t dMul64( dsStruct64_t *x, dsStruct64_t *y, int *overflow );
extern dsStruct64_t dDiv64( dsStruct64_t *x, dsStruct64_t *y, dsStruct64_t *rmdrP );
extern char  *dI64toCh( dsStruct64_t *value, char *string, int radix );
extern dsStruct64_t dChtoI64( char *str, int radix );
