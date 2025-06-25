#include "demo_scenes.h"

#include "util/filesystem.h"

#include "entity/ecs.h"
#include "entity/modules/modules_systems.h"

#include "asset/asset.h"
#include "systems/ecs_systems.h"

#include "entity/__generated__/components_gen.h"

/*----------------------
 |  Scene 10
 |  Description: Solar System
 -----------------------*/

 void _scene10(gsk_ECS *ecs, gsk_Renderer *renderer)
 {
    gsk_Texture *texDefNorm, *texPbrAo, *texMissing;
    gsk_Skybox *def_skybox;

    def_skybox = gsk_skybox_hdr_create(
        texture_create_hdr(GSK_PATH("gsk://textures/hdr/blue_galaxy_ref.hdr")));

    gsk_Texture *texDefSpec     = GSK_ASSET("gsk://textures/defaults/black.png");

    gsk_Texture *texEarthDiff   = GSK_ASSET("data://textures/planets/earth/diffuse.png");
    gsk_Texture *texEarthNorm   = GSK_ASSET("data://textures/planets/earth/normal.png");

    gsk_Texture *texSunDiff     = GSK_ASSET("data://textures/planets/sun/diffuse.png");
    gsk_Texture *texSunNorm     = GSK_ASSET("data://textures/planets/sun/normal.png");

    gsk_Texture *texMercuryDiff = GSK_ASSET("data://textures/planets/mercury/diffuse.png");
    gsk_Texture *texMercuryNorm = GSK_ASSET("data://textures/planets/mercury/normal.png");

    gsk_Texture *texVenusDiff   = GSK_ASSET("data://textures/planets/venus/diffuse.png");
    gsk_Texture *texVenusNorm   = GSK_ASSET("data://textures/planets/venus/normal.png");

    gsk_Texture *texMarsDiff    = GSK_ASSET("data://textures/planets/mars/diffuse.png");
    gsk_Texture *texMarsNorm    = GSK_ASSET("data://textures/planets/mars/normal.png");

    gsk_Texture *texJupiterDiff = GSK_ASSET("data://textures/planets/jupiter/diffuse.png");
    gsk_Texture *texJupiterNorm = GSK_ASSET("data://textures/planets/jupiter/normal.png");

    gsk_Texture *texSaturnDiff  = GSK_ASSET("data://textures/planets/saturn/diffuse.png");
    gsk_Texture *texSaturnNorm  = GSK_ASSET("data://textures/planets/saturn/normal.png");

    gsk_Texture *texUranusDiff  = GSK_ASSET("data://textures/planets/uranus/diffuse.png");
    gsk_Texture *texUranusNorm  = GSK_ASSET("data://textures/planets/uranus/normal.png");

    gsk_Texture *texNeptuneDiff = GSK_ASSET("data://textures/planets/neptune/diffuse.png");
    gsk_Texture *texNeptuneNorm = GSK_ASSET("data://textures/planets/neptune/normal.png");

    gsk_Texture *texPlutoDiff   = GSK_ASSET("data://textures/planets/pluto/diffuse.png");
    gsk_Texture *texPlutoNorm   = GSK_ASSET("data://textures/planets/pluto/normal.png");

    gsk_Model *model_planet = GSK_ASSET("gsk://models/sphere.obj");

    gsk_Material *matSun = 
       gsk_material_create(NULL,
                           GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                           3,
                           texSunDiff,
                           texSunNorm,
                           texDefSpec);

    gsk_Material *matMercury =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texMercuryDiff,
                          texMercuryNorm,
                          texDefSpec);

    gsk_Material *matVenus =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texVenusDiff,
                          texVenusNorm,
                          texDefSpec);

    gsk_Material *matEarth = 
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texEarthDiff,
                          texEarthNorm,
                          texDefSpec);

    gsk_Material *matMars =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texMarsDiff,
                          texMarsNorm,
                          texDefSpec);

    gsk_Material *matJupiter =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texJupiterDiff,
                          texJupiterNorm,
                          texDefSpec);

    gsk_Material *matSaturn =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texSaturnDiff,
                          texSaturnNorm,
                          texDefSpec);

    gsk_Material *matUranus =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texUranusDiff,
                          texUranusNorm,
                          texDefSpec);

    gsk_Material *matNeptune =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texNeptuneDiff,
                          texNeptuneNorm,
                          texDefSpec);

    gsk_Material *matPluto =
      gsk_material_create(NULL,
                          GSK_PATH("gsk://shaders/lit-diffuse.shader"),
                          3,
                          texPlutoDiff,
                          texPlutoNorm,
                          texDefSpec);

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

    gsk_Entity sunEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(sunEntity, 
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {0.0f, 0.0f, 0.0f},
                            .scale    = {2.0f, 2.0f, 2.0f},
                          }));
    _gsk_ecs_add_internal(sunEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matSun,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(sunEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 1.0f,
                            .orbit_radius   = 0.0f,
                            .orbit_speed    = 0.0f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity mercuryEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(mercuryEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {4.5f, 0.0f, 0.0f},
                            .scale    = {0.2f, 0.2f, 0.2f},
                          }));
    _gsk_ecs_add_internal(mercuryEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matMercury,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(mercuryEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 5.0f,
                            .orbit_radius   = 4.5f,
                            .orbit_speed    = 1.0f,
                            .orbit_position = 0.0f,
                          }));
    
    gsk_Entity venusEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(venusEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {7.5f, 0.0f, 0.0f},
                            .scale    = {0.5f, 0.5f, 0.5f},
                          }));
    _gsk_ecs_add_internal(venusEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matVenus,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(venusEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 10.0f,
                            .orbit_radius   = 7.5f,
                            .orbit_speed    = 0.7f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity earthEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(earthEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {10.5f, 0.0f, 0.0f},
                            .scale    = {0.6f, 0.6f, 0.6f},
                          }));
    _gsk_ecs_add_internal(earthEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matEarth,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(earthEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 15.0f,
                            .orbit_radius   = 10.5f,
                            .orbit_speed    = 0.6f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity marsEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(marsEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {13.5f, 0.0f, 0.0f},
                            .scale    = {0.4f, 0.4f, 0.4f},
                          }));
    _gsk_ecs_add_internal(marsEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matMars,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(marsEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 20.0f,
                            .orbit_radius   = 13.5f,
                            .orbit_speed    = 0.5f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity jupiterEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(jupiterEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {17.0f, 0.0f, 0.0f},
                            .scale    = {1.2f, 1.2f, 1.2f},
                          }));
    _gsk_ecs_add_internal(jupiterEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matJupiter,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(jupiterEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 25.0f,
                            .orbit_radius   = 17.0f,
                            .orbit_speed    = 0.25f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity saturnEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(saturnEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {21.0f, 0.0f, 0.0f},
                            .scale    = {1.0f, 1.0f, 1.0f},
                          }));
    _gsk_ecs_add_internal(saturnEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matSaturn,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(saturnEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 30.0f,
                            .orbit_radius   = 21.0f,
                            .orbit_speed    = 0.2f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity uranusEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(uranusEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {24.5f, 0.0f, 0.0f},
                            .scale    = {0.8f, 0.8f, 0.8f},
                          }));
    _gsk_ecs_add_internal(uranusEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matUranus,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(uranusEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 35.0f,
                            .orbit_radius   = 24.5f,
                            .orbit_speed    = 0.14f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity neptuneEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(neptuneEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {28.0f, 0.0f, 0.0f},
                            .scale    = {0.7f, 0.7f, 0.7f},
                          }));
    _gsk_ecs_add_internal(neptuneEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matNeptune,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(neptuneEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 40.0f,
                            .orbit_radius   = 28.0f,
                            .orbit_speed    = 0.11f,
                            .orbit_position = 0.0f,
                          }));

    gsk_Entity plutoEntity = gsk_ecs_new(ecs);
    _gsk_ecs_add_internal(plutoEntity,
                          C_TRANSFORM,
                          (void *)(&(struct ComponentTransform) {
                            .position = {31.0f, 0.0f, 0.0f},
                            .scale    = {0.2f, 0.2f, 0.2f},
                          }));
    _gsk_ecs_add_internal(plutoEntity,
                          C_MODEL,
                          (void *)(&(struct ComponentModel) {
                            .material = matPluto,
                            .pModel   = model_planet,
                          }));
    _gsk_ecs_add_internal(plutoEntity,
                          C_PLANET,
                          (void *)(&(struct ComponentPlanet) {
                            .rotation_speed = 45.0f,
                            .orbit_radius   = 31.0f,
                            .orbit_speed    = 0.09f,
                            .orbit_position = 0.0f,
                          }));
}