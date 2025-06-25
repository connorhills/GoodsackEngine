#include "ecs_systems.h"
#include "entity/ecs.h"
#include "core/device/device.h"

static void
init(gsk_Entity entity)
{
    if(gsk_ecs_has(entity, C_CAMERA)) { return; }
    
    struct ComponentTransform *transform = gsk_ecs_get(entity, C_TRANSFORM);
}

static void
update(gsk_Entity entity)
{
    if (gsk_ecs_has(entity, C_CAMERA)) { return; }

    struct ComponentTransform *transform = gsk_ecs_get(entity, C_TRANSFORM);
    struct ComponentPlanet    *planet = gsk_ecs_get(entity, C_PLANET);

    transform->orientation[1] += planet->rotation_speed * gsk_device_getTime().delta_time;

    planet->orbit_position += planet->orbit_speed * gsk_device_getTime().delta_time;

    transform->position[0] = planet->orbit_radius * cosf(planet->orbit_position);
    transform->position[2] = planet->orbit_radius * sinf(planet->orbit_position);
}

void
rotate_planet_system_init(gsk_ECS *ecs)
{
    gsk_ecs_system_register(ecs,
                            ((gsk_ECSSystem) {
                                .init   = (gsk_ECSSubscriber)init,
                                .update = (gsk_ECSSubscriber)update,
                            }));
}