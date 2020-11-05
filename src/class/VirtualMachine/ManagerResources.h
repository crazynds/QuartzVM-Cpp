/*
 * ManagerResorces.h
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */

#ifndef SRC_CLASS_VIRTUALMACHINE_MANAGERRESORCES_H_
#define SRC_CLASS_VIRTUALMACHINE_MANAGERRESORCES_H_

#include "../../lib/Types.h"

class ManagerResources {
private:


	struct{
		void* address;
		uint32 tag;
	}addres_tag;

	struct{
		struct addres_tag *arr;
		uint64 size;
	}thread_map;

	//struct thread_map *tagMap;


	bool check_tag(uint32 tag);

public:
	ManagerResources();
	virtual ~ManagerResources();

	void* alloc(uint64 x);
	void* alloc_tag(uint64 x,uint32 tag);

	void* realloc(void*,uint64 x);
	void free(void*);
	void free(uint32 tag);

	uint32 genereteUniqueTag();


};

#endif /* SRC_CLASS_VIRTUALMACHINE_MANAGERRESORCES_H_ */
