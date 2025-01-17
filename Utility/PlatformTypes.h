#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

typedef void (*pFunc_void_void)(void);
typedef void* (*pFunc_voidP_void)(void);   
typedef void (*pFunc_void_voidP)(void*);   
typedef void* (*pFunc_voidP_voidP)(void*);      



typedef unsigned char boolean;
typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed long sint32;
typedef unsigned long uint32;
typedef float float32;
typedef double float64;

#endif /* PLATFORM_TYPES_H */
