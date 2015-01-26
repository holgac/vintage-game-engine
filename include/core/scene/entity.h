#ifndef _VGE_ENTITY_H_

struct vge_component;
struct vge_entity
{
	struct vge_entity* next;
	struct vge_component* component;
};

// 
#endif /* _VGE_ENTITY_H_ */
