#ifndef __ECS_SYSTEMS_H__
#define __ECS_SYSTEMS_H__

#include "entity/ecs.h"

#ifdef __cplusplus
extern "C" {
#endif

void
rotate_planet_system_init(gsk_ECS *ecs);

#ifdef __cplusplus
}
#endif

#endif // __ECS_SYSTEMS_H__