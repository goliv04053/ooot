#define INTERNAL_SRC_OVERLAYS_ACTORS_OVL_EN_STREAM_Z_EN_STREAM_C
#include "actor_common.h"
/*
 * File: z_en_stream.c
 * Overlay: ovl_En_Stream
 * Description: Water Vortex
 */

#include "z_en_stream.h"
#include "objects/object_stream/object_stream.h"
#include "def/math_float.h"
#include "def/sys_matrix.h"
#include "def/z_actor.h"
#include "def/z_lib.h"
#include "def/z_rcp.h"

#define FLAGS ACTOR_FLAG_4

void EnStream_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Reset(Actor* pthisx, GlobalContext* globalCtx);
void EnStream_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnStream_WaitForPlayer(EnStream* pthis, GlobalContext* globalCtx);

ActorInit En_Stream_InitVars = {
    ACTOR_EN_STREAM,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_STREAM,
    sizeof(EnStream),
    (ActorFunc)EnStream_Init,
    (ActorFunc)EnStream_Destroy,
    (ActorFunc)EnStream_Update,
    (ActorFunc)EnStream_Draw,
    (ActorFunc)EnStream_Reset,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 20, ICHAIN_STOP),
};

void EnStream_SetupAction(EnStream* pthis, EnStreamActionFunc actionFunc) {
    pthis->actionFunc = actionFunc;
}

void EnStream_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnStream* pthis = (EnStream*)thisx;

    pthis->unk_150 = thisx->params & 0xFF;
    Actor_ProcessInitChain(thisx, sInitChain);
    if ((pthis->unk_150 != 0) && (pthis->unk_150 == 1)) {
        thisx->scale.y = 0.01f;
    }
    EnStream_SetupAction(pthis, EnStream_WaitForPlayer);
}

void EnStream_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// Checks if the player is in range of the vortex
s32 func_80B0B81C(Vec3f* vortexPosRot, Vec3f* playerPosRot, Vec3f* posDifference, f32 vortexYScale) {
    s32 ret = 0;
    f32 smallConstant = 28.0f;
    f32 upperBounds = 160 * vortexYScale * 50.0f;
    f32 lowerBounds = 0 * vortexYScale * 50.0f;
    f32 xzDist;
    f32 range;

    posDifference->x = playerPosRot->x - vortexPosRot->x;
    posDifference->y = playerPosRot->y - vortexPosRot->y;
    posDifference->z = playerPosRot->z - vortexPosRot->z;
    xzDist = sqrtf(SQ(posDifference->x) + SQ(posDifference->z));

    if (lowerBounds <= posDifference->y && posDifference->y <= upperBounds) {
        posDifference->y -= lowerBounds;

        range = ((75.0f - smallConstant) * (posDifference->y / (upperBounds - lowerBounds))) + 28.0f;
        if (xzDist <= range) {
            ret = 1;
        }
    }

    if ((posDifference->y <= lowerBounds) && (xzDist <= 28.0f)) {
        ret = 2;
    }

    return ret;
}

void EnStream_SuckPlayer(EnStream* pthis, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad48;
    Vec3f posDifference;
    f32 xzDist;
    f32 yDistWithOffset;
    s32 pad30;
    s32 pad2C;

    if (func_80B0B81C(&pthis->actor.world.pos, &player->actor.world.pos, &posDifference, pthis->actor.scale.y) != 0) {
        xzDist = sqrtf(SQ(posDifference.x) + SQ(posDifference.z));
        yDistWithOffset = player->actor.world.pos.y - (pthis->actor.world.pos.y - 90.0f);
        player->windDirection = Math_FAtan2F(-posDifference.x, -posDifference.z) * (0x8000 / M_PI);
        if (xzDist > 3.0f) {
            Math_SmoothStepToF(&player->windSpeed, 3.0f, 0.5f, xzDist, 0.0f);
        } else {
            player->windSpeed = 0.0f;
            Math_SmoothStepToF(&player->actor.world.pos.x, pthis->actor.world.pos.x, 0.5f, 3.0f, 0.0f);
            Math_SmoothStepToF(&player->actor.world.pos.z, pthis->actor.world.pos.z, 0.5f, 3.0f, 0.0f);
        }
        if (yDistWithOffset > 0.0f) {
            Math_SmoothStepToF(&player->actor.velocity.y, -3.0f, 0.7f, yDistWithOffset, 0.0f);
            if (posDifference.y < -70.0f) {
                player->stateFlags2 |= 0x80000000;
            }
        }
    } else {
        EnStream_SetupAction(pthis, EnStream_WaitForPlayer);
    }
}

void EnStream_WaitForPlayer(EnStream* pthis, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 pad;
    Vec3f temp;

    if (func_80B0B81C(&pthis->actor.world.pos, &player->actor.world.pos, &temp, pthis->actor.scale.y) != 0) {
        EnStream_SetupAction(pthis, EnStream_SuckPlayer);
    }
}

void EnStream_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnStream* pthis = (EnStream*)thisx;

    pthis->actionFunc(pthis, globalCtx);
    func_8002F948(thisx, NA_SE_EV_WHIRLPOOL - SFX_FLAG);
}

void EnStream_Draw(Actor* thisx, GlobalContext* globalCtx) {
    u32 multipliedFrames;
    u32 frames = globalCtx->gameplayFrames;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_stream.c", 295);
    func_80093D84(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_stream.c", 299),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    multipliedFrames = frames * 20;
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, frames * 30, -multipliedFrames, 0x40, 0x40, 1,
                                multipliedFrames, -multipliedFrames, 0x40, 0x40));
    gSPDisplayList(POLY_XLU_DISP++, object_stream_DL_000950);
    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_stream.c", 310);
}

void EnStream_Reset(Actor* pthisx, GlobalContext* globalCtx) {
    En_Stream_InitVars = {
        ACTOR_EN_STREAM,
        ACTORCAT_BG,
        FLAGS,
        OBJECT_STREAM,
        sizeof(EnStream),
        (ActorFunc)EnStream_Init,
        (ActorFunc)EnStream_Destroy,
        (ActorFunc)EnStream_Update,
        (ActorFunc)EnStream_Draw,
        (ActorFunc)EnStream_Reset,
    };

}
