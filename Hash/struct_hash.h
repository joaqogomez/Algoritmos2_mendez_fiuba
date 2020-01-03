#ifndef __STRUCT_HASH_H__
#define __STRUCT_HASH_H__

struct hash{
	abb_t** tabla_hash;
	hash_destruir_dato_t destructor;
	size_t capacidad;
	size_t cantidad_claves;
};


#endif /*__STRUCT_HASH_H__ */
