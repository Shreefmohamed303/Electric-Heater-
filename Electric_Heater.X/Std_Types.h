#ifndef STD_TYPES_H
#define STD_TYPES_H


typedef unsigned char   uint8_t ;
typedef signed 			int8_t ;

typedef unsigned short 	uint16_t ;
typedef signed 	short	int16_t;

typedef unsigned long  	uint32_t ;
typedef signed 	long	int32_t ;

typedef unsigned long long   	uint64_t ;
typedef signed 	long  long 		int64_t ;

typedef float  float32_t ;
typedef double float64_t ;

typedef uint8_t Std_ReturnType;

typedef enum
{
    OFF=0, 
    ON=1
}tState;

typedef enum
{
    FALSE=0, 
    TRUE=1
}tbool;

#define E_OK        (Std_ReturnType)(0x00u)
#define E_NOT_OK    (Std_ReturnType)(0x01u)

#define ENABLE       1
#define DISABLE      0

#endif