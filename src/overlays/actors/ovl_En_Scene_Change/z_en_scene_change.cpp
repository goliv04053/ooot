#define INTERNAL_SRC_OVERLAYS_ACTORS_OVL_EN_SCENE_CHANGE_Z_EN_SCENE_CHANGE_C
#include "actor_common.h"
/*
 * File: z_en_scene_change.c
 * Overlay: ovl_En_Scene_Change
 * Description: Unknown (Broken Actor)
 */

#include "z_en_scene_change.h"
#include "def/graph.h"
#include "def/z_rcp.h"

#define FLAGS 0

void EnSceneChange_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSceneChange_Reset(Actor* pthisx, GlobalContext* globalCtx);
void EnSceneChange_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSceneChange_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSceneChange_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnSceneChange_DoNothing(EnSceneChange* pthis, GlobalContext* globalCtx);

ActorInit En_Scene_Change_InitVars = {
    ACTOR_EN_SCENE_CHANGE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_JJ,
    sizeof(EnSceneChange),
    (ActorFunc)EnSceneChange_Init,
    (ActorFunc)EnSceneChange_Destroy,
    (ActorFunc)EnSceneChange_Update,
    (ActorFunc)EnSceneChange_Draw,
    (ActorFunc)EnSceneChange_Reset,
};

void EnSceneChange_SetupAction(EnSceneChange* pthis, EnSceneChangeActionFunc actionFunc) {
    pthis->actionFunc = actionFunc;
}

void EnSceneChange_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSceneChange* pthis = (EnSceneChange*)thisx;

    EnSceneChange_SetupAction(pthis, EnSceneChange_DoNothing);
}

void EnSceneChange_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnSceneChange_DoNothing(EnSceneChange* pthis, GlobalContext* globalCtx) {
}

void EnSceneChange_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSceneChange* pthis = (EnSceneChange*)thisx;

    pthis->actionFunc(pthis, globalCtx);
}

void EnSceneChange_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    Gfx* displayList;
    s32 pad2[2];
    Gfx* displayListHead;

    displayList = (Gfx*)Graph_Alloc(globalCtx->state.gfxCtx, 0x3C0);

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_scene_change.c", 290);

    displayListHead = displayList;
    gSPSegment(POLY_OPA_DISP++, 0x0C, displayListHead);

    func_80093D18(globalCtx->state.gfxCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_scene_change.c", 386);
}

void EnSceneChange_Reset(Actor* pthisx, GlobalContext* globalCtx) {
    En_Scene_Change_InitVars = {
        ACTOR_EN_SCENE_CHANGE,
        ACTORCAT_PROP,
        FLAGS,
        OBJECT_JJ,
        sizeof(EnSceneChange),
        (ActorFunc)EnSceneChange_Init,
        (ActorFunc)EnSceneChange_Destroy,
        (ActorFunc)EnSceneChange_Update,
        (ActorFunc)EnSceneChange_Draw,
        (ActorFunc)EnSceneChange_Reset,
    };

}
