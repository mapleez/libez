#ifndef _EZ_HASH_H_
#	define _EZ_HASH_H_

typedef unsigned int (*hash_function)
	(char*, unsigned int);

/* 
 * Common hash functions
 */

extern int ez_horner_hash (char*, int);
extern int ez_simple_hash (int, int);
extern int ez_ascii_hash (char*, int);

/*
 * Other hash functions
 */

extern unsigned int RSHash  (char*, unsigned int);
extern unsigned int JSHash  (char*, unsigned int);
extern unsigned int PJWHash (char*, unsigned int);
extern unsigned int ELFHash (char*, unsigned int);
extern unsigned int BKDRHash(char*, unsigned int);
extern unsigned int SDBMHash(char*, unsigned int);
extern unsigned int DJBHash (char*, unsigned int);
extern unsigned int DEKHash (char*, unsigned int);
extern unsigned int BPHash  (char*, unsigned int);
extern unsigned int FNVHash (char*, unsigned int);
extern unsigned int APHash  (char*, unsigned int);

#endif // ~ _EZ_HASH_H_

