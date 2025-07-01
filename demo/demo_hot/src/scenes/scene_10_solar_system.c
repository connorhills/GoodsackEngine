#include "demo_scenes.h"

#include "util/filesystem.h"

#include "entity/ecs.h"
#include "entity/modules/modules_systems.h"

#include "asset/asset.h"
#include "systems/ecs_systems.h"

#include "math.h"
#include "entity/__generated__/components_gen.h"

/*----------------------
 |  Scene 10
 |  Description: Solar System
 -----------------------*/
static gsk_Entity 
_create_planet_(gsk_ECS *p_ecs, gsk_Material *p_material, gsk_Model *planet_model,
                float planet_scale, float rotation_speed, float orbit_radius, float orbit_speed)
{
    gsk_Entity planet_entity = gsk_ecs_new(p_ecs);
    _gsk_ecs_add_internal(planet_entity, 
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {0.0f, 0.0f, 0.0f},
                            .scale    = {planet_scale, planet_scale, planet_scale},
                          }));
    _gsk_ecs_add_internal(planet_entity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = p_material,
                            .pModel   = planet_model,
                          }));
    _gsk_ecs_add_internal(planet_entity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = rotation_speed,
                            .orbit_radius   = orbit_radius,
                            .orbit_speed    = orbit_speed,
                            .orbit_position = 0.0f,
                          }));
    return planet_entity;
}
static void
_create_saturn_ring_(gsk_ECS *ecs, gsk_EntityId saturnId, gsk_Material *mat, gsk_Model *model)
{
    int rockAmount = 1000;

    float ringRadius = 2.0f;
    float offset     = 0.3f;

    for (int i = 0; i < rockAmount; i++)
    {
        float angle        = (2.0 * 3.14 * i) / rockAmount;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x            = sin(angle) * ringRadius + displacement;
        displacement       = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y            = displacement * 0.4f;
        displacement       = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z            = cos(angle) * ringRadius + displacement;

        float rot_x = ((float) rand() / RAND_MAX) * 20.0f * 3.14;
        float rot_y = ((float) rand() / RAND_MAX) * 20.0f * 3.14;
        float rot_z = ((float) rand() / RAND_MAX) * 20.0f * 3.14;

        float scale = 0.01f + ((float) rand() / RAND_MAX) * 0.05f;


        gsk_Entity rock = gsk_ecs_new(ecs);
        _gsk_ecs_add_internal(rock,
                              C_TRANSFORM,
                              (void *)(&(struct ComponentTransform) {
                                .position         = {x, y, z},
                                .scale            = {scale, scale, scale},
                                .orientation      = {rot_x, rot_y, rot_z},
                                .parent_entity_id = saturnId,
                              }));
        _gsk_ecs_add_internal(rock,
                              C_MODEL,
                              (void *)(&(struct ComponentModel) {
                                .material = mat,
                                .pModel   = model,
                              }));
    }
}

static gsk_Entity
_create_earth_moon_(gsk_ECS *ecs, gsk_EntityId earthId, gsk_Material *m_material, gsk_Model *m_model)
{
        gsk_Entity moon_entity = gsk_ecs_new(ecs);
        _gsk_ecs_add_internal(moon_entity,
                              C_TRANSFORM,
                              (void *)(&(struct ComponentTransform) {
                                .position         = {2.0f, 0.0f, 0.0f},
                                .scale            = {0.135f, 0.135f, 0.135f},
                                .parent_entity_id = earthId,
                              }));
        _gsk_ecs_add_internal(moon_entity,
                              C_MODEL,
                              (void *)(&(struct ComponentModel) {
                                .material = m_material,
                                .pModel   = m_model,
                              }));
}

 void _scene10(gsk_ECS *ecs, gsk_Renderer *renderer)
 {
    gsk_Texture *texDefNorm, *texPbrAo, *texMissing;
    gsk_Skybox *def_skybox;

    def_skybox = gsk_skybox_hdr_create(
        texture_create_hdr(GSK_PATH("gsk://textures/hdr/blue_galaxy_ref.hdr")));

    gsk_Texture *texDefSpec     = GSK_ASSET("gsk://textures/defaults/black.png");



    gsk_Model *model_planet = GSK_ASSET("gsk://models/sphere.obj");
    
    gsk_Model *model_rock   = GSK_ASSET("data://models/rock.obj");

    // Needed for ring to parent
    gsk_Entity saturn_entity;
    gsk_Material *mat_saturn;

    // Needed for moon to parent 
    gsk_Entity earth_entity;
    gsk_Material *mat_earth;

    gsk_Texture *rock_diffuse = GSK_ASSET("data://textures/rock/diffuse.png");
    gsk_Texture *rock_normal  = GSK_ASSET("data://textures/rock/normal.png");

    gsk_Texture *moon_diffuse = GSK_ASSET("data://textures/planets/earth/moon/diffuse.png");
    gsk_Texture *moon_normal  = GSK_ASSET("data://textures/planets/earth/moon/normal.png");

    gsk_Material *rock_material =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          rock_diffuse,
                          rock_normal,
                          texDefSpec);

    gsk_Material *mat_moon =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          moon_diffuse,
                          moon_normal,
                          texDefSpec);                     


    const char *planet_names[10] = {"sun", "mercury", "venus", "earth", "mars",
                                    "jupiter", "saturn", "uranus", "neptune", "pluto"};

    float planet_scales[10]      = {2.0f, 0.2f, 0.5f, 0.6f, 0.4f,
                                    1.2f, 1.0f, 0.8f, 0.7f, 0.2f};

    float rotation_speeds[10]    = {0.0f, 5.0f, 10.0f, 25.0f, 24.5f, 
                                    50.0f, 46.3f, 32.5, 34.5f, 15.0f};

    float orbit_radius[10]       = {0.0f, 4.5f, 7.5f, 10.5f, 13.5f,
                                    17.0f, 21.0f, 24.5, 28.0, 31.0f};

    float orbit_speeds[10]       = {0.0f, 1.0f, 0.7f, 0.6f, 0.5f, 
                                    0.25f, 0.2f, 0.14f, 0.11f, 0.09f};

    ecs = gsk_renderer_active_scene(renderer, 10);
    __set_active_scene_skybox(renderer, def_skybox);

    gsk_Entity *pCamera = malloc(sizeof(gsk_Entity));
    *pCamera            = gsk_ecs_new(ecs);

    gsk_Entity camera = *pCamera;
    _gsk_ecs_add_internal(
        camera,
        C_CAMERA,
        (void *)(&(struct ComponentCamera) {
            .axisUp      = {0.0f, 1.0f, 0.0f},
            .renderLayer = 0,
        }));
    _gsk_ecs_add_internal(camera,
                          C_CAMERALOOK,
                          (void *)(&(struct ComponentCameraLook) {
                            .sensitivity = 1.0f,
                          }));
    _gsk_ecs_add_internal(camera,
                          C_CAMERAMOVEMENT,
                          (void *)(&(struct ComponentCameraMovement) {
                            .speed = 5.0f,
                          }));
    _gsk_ecs_add_internal(camera,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {0.0f, 0.0f, 2.0f},
                          }));
                
    for (int i = 0; i < 10; i++)
    {
      char diffuse[128] = "";
      char normal[128]  = "";

      snprintf(diffuse, sizeof(diffuse), "data://textures/planets/%s/diffuse.png", planet_names[i]);
      snprintf(normal, sizeof(normal), "data://textures/planets/%s/normal.png", planet_names[i]);

      gsk_Texture *diff = GSK_ASSET(diffuse);
      gsk_Texture *norm = GSK_ASSET(normal);

      gsk_Material *p_mat =
       gsk_material_create(NULL,
                           GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                           3,
                           diff,
                           norm,
                           texDefSpec);

        gsk_Entity planet_entity = 
        _create_planet_(ecs, p_mat, model_planet, 
                        planet_scales[i], rotation_speeds[i], orbit_radius[i], orbit_speeds[i]);

        //Sets saturnEntity to proper EntityId
        if(strcmp(planet_names[i], "saturn") == 0) {
            saturn_entity = planet_entity;
            mat_saturn = p_mat;
        }

        if(strcmp(planet_names[i], "earth") == 0) {
            earth_entity  = planet_entity;
            mat_earth   = p_mat;
        }
    }

    _create_saturn_ring_(ecs, saturn_entity.id, rock_material, model_rock);

    _create_earth_moon_(ecs, earth_entity.id, mat_moon, model_planet);
}