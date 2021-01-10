/**
 * @file IO_definitions.h
 * @author Rafal Rogalski
 * @brief Command IO definition file.
 * 
 */
#ifndef IO_DEFINITIONS_H_
#define IO_DEFINITIONS_H_

#define GET_COUNT       _IOR('a', 'a', uint64_t*)
#define RESET_COUNT     _IO('a', 'b')
#define GET_COUT_TIME   _IOR('a', 'c', uint32_t*)

#endif //!IO_DEFINITIONS_H_