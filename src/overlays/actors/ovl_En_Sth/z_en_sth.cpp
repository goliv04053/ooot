#define INTERNAL_SRC_OVERLAYS_ACTORS_OVL_EN_STH_Z_EN_STH_C
#include "actor_common.h"
/*
 * File: z_en_sth.c
 * Overlay: ovl_En_Sth
 * Description: Uncursed House of Skulltula People
 */

#include "vt.h"
#include "z_en_sth.h"
#include "objects/object_ahg/object_ahg.h"
#include "objects/object_boj/object_boj.h"
#include "def/graph.h"
#include "def/sys_matrix.h"
#include "def/z_actor.h"
#include "def/z_collision_check.h"
#include "def/z_common_data.h"
#include "def/z_lib.h"
#include "def/z_message_PAL.h"
#include "def/z_rcp.h"
#include "def/z_scene.h"
#include "def/z_skelanime.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_3 | ACTOR_FLAG_4)

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Reset(Actor* pthisx, GlobalContext* globalCtx);
void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Update2(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnSth_WaitForObjectLoaded(EnSth* pthis, GlobalContext* globalCtx);
void EnSth_ParentRewardObtainedWait(EnSth* pthis, GlobalContext* globalCtx);
void EnSth_RewardUnobtainedWait(EnSth* pthis, GlobalContext* globalCtx);
void EnSth_ChildRewardObtainedWait(EnSth* pthis, GlobalContext* globalCtx);

ActorInit En_Sth_InitVars = {
    ACTOR_EN_STH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnSth),
    (ActorFunc)EnSth_Init,
    (ActorFunc)EnSth_Destroy,
    (ActorFunc)EnSth_Update,
    NULL,
    (ActorFunc)EnSth_Reset,
};

#include "overlays/ovl_En_Sth/ovl_En_Sth.cpp"

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

static s16 sObjectIds[6] = {
    OBJECT_AHG, OBJECT_BOJ, OBJECT_BOJ, OBJECT_BOJ, OBJECT_BOJ, OBJECT_BOJ,
};

static FlexSkeletonHeader* sSkeletons[6] = {
    &object_ahg_Skel_0000F0,
    &object_boj_Skel_0000F0,
    &object_boj_Skel_0000F0,
    &object_boj_Skel_0000F0,
    &object_boj_Skel_0000F0,
    &object_boj_Skel_0000F0,
};

static AnimationHeader* sAnimations[6] = {
    &sParentDanceAnim, &sChildDanceAnim, &sChildDanceAnim, &sChildDanceAnim, &sChildDanceAnim, &sChildDanceAnim,
};

static EnSthActionFunc sRewardObtainedWaitActions[6] = {
    EnSth_ParentRewardObtainedWait, EnSth_ChildRewardObtainedWait, EnSth_ChildRewardObtainedWait,
    EnSth_ChildRewardObtainedWait,  EnSth_ChildRewardObtainedWait, EnSth_ChildRewardObtainedWait,
};

static u16 sEventFlags[6] = {
    0x0000, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000,
};

static s16 sGetItemIds[6] = {
    GI_RUPEE_GOLD, GI_WALLET_ADULT, GI_STONE_OF_AGONY, GI_WALLET_GIANT, GI_BOMBCHUS_10, GI_HEART_PIECE,
};

static Vec3f D_80B0B49C = { 700.0f, 400.0f, 0.0f };

static Color_RGB8 sTunicColors[6] = {
    { 190, 110, 0 }, { 0, 180, 110 }, { 0, 255, 80 }, { 255, 160, 60 }, { 190, 230, 250 }, { 240, 230, 120 },
};

void EnSth_SetupAction(EnSth* pthis, EnSthActionFunc actionFunc) {
    pthis->actionFunc = actionFunc;
}

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* pthis = (EnSth*)thisx;

    s16 objectId;
    s32 params = pthis->actor.params;
    s32 objectBankIdx;

    osSyncPrintf(VT_FGCOL(BLUE) "金スタル屋 no = %d\n" VT_RST, params); // "Gold Skulltula Shop"
    if (pthis->actor.params == 0) {
        if (gSaveContext.inventory.gsTokens < 100) {
            Actor_Kill(&pthis->actor);
            // "Gold Skulltula Shop I still can't be a human"
            osSyncPrintf("金スタル屋 まだ 人間に戻れない \n");
            return;
        }
    } else if (gSaveContext.inventory.gsTokens < (pthis->actor.params * 10)) {
        Actor_Kill(&pthis->actor);
        // "Gold Skulltula Shop I still can't be a human"
        osSyncPrintf(VT_FGCOL(BLUE) "金スタル屋 まだ 人間に戻れない \n" VT_RST);
        return;
    }

    objectId = sObjectIds[params];
    if (objectId != 1) {
        objectBankIdx = Object_GetIndex(&globalCtx->objectCtx, objectId);
    } else {
        objectBankIdx = 0;
    }

    osSyncPrintf("bank_ID = %d\n", objectBankIdx);
    if (objectBankIdx < 0) {
        ASSERT(0, "0", "../z_en_sth.c", 1564);
    }
    pthis->objectBankIdx = objectBankIdx;
    pthis->drawFunc = EnSth_Draw;
    Actor_SetScale(&pthis->actor, 0.01f);
    EnSth_SetupAction(pthis, EnSth_WaitForObjectLoaded);
    pthis->actor.draw = NULL;
    pthis->unk_2B2 = 0;
    pthis->actor.targetMode = 6;
}

void EnSth_SetupShapeColliderUpdate2AndDraw(EnSth* pthis, GlobalContext* globalCtx) {
    s32 pad;

    ActorShape_Init(&pthis->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    Collider_InitCylinder(globalCtx, &pthis->collider);
    Collider_SetCylinder(globalCtx, &pthis->collider, &pthis->actor, &sCylinderInit);
    pthis->actor.colChkInfo.mass = MASS_IMMOVABLE;
    pthis->actor.update = EnSth_Update2;
    pthis->actor.draw = pthis->drawFunc;
}

void EnSth_SetupAfterObjectLoaded(EnSth* pthis, GlobalContext* globalCtx) {
    s32 pad;
    s16* params;

    EnSth_SetupShapeColliderUpdate2AndDraw(pthis, globalCtx);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(gObjectTable[pthis->objectBankIdx].vromStart.get());
    SkelAnime_InitFlex(globalCtx, &pthis->skelAnime, sSkeletons[pthis->actor.params], NULL, pthis->jointTable,
                       pthis->morphTable, 16);
    Animation_PlayLoop(&pthis->skelAnime, sAnimations[pthis->actor.params]);

    pthis->eventFlag = sEventFlags[pthis->actor.params];
    params = &pthis->actor.params;
    if (gSaveContext.eventChkInf[13] & pthis->eventFlag) {
        EnSth_SetupAction(pthis, sRewardObtainedWaitActions[*params]);
    } else {
        EnSth_SetupAction(pthis, EnSth_RewardUnobtainedWait);
    }
}

void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* pthis = (EnSth*)thisx;

    Collider_DestroyCylinder(globalCtx, &pthis->collider);
}

void EnSth_WaitForObjectLoaded(EnSth* pthis, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, pthis->objectBankIdx)) {
        pthis->actor.objBankIndex = pthis->objectBankIdx;
        pthis->actionFunc = EnSth_SetupAfterObjectLoaded;
    }
}

void EnSth_FacePlayer(EnSth* pthis, GlobalContext* globalCtx) {
    s32 pad;
    s16 diffRot = pthis->actor.yawTowardsPlayer - pthis->actor.shape.rot.y;

    if (ABS(diffRot) <= 0x4000) {
        Math_SmoothStepToS(&pthis->actor.shape.rot.y, pthis->actor.yawTowardsPlayer, 6, 0xFA0, 0x64);
        pthis->actor.world.rot.y = pthis->actor.shape.rot.y;
        func_80038290(globalCtx, &pthis->actor, &pthis->headRot, &pthis->unk_2AC, pthis->actor.focus.pos);
    } else {
        if (diffRot < 0) {
            Math_SmoothStepToS(&pthis->headRot.y, -0x2000, 6, 0x1838, 0x100);
        } else {
            Math_SmoothStepToS(&pthis->headRot.y, 0x2000, 6, 0x1838, 0x100);
        }
        Math_SmoothStepToS(&pthis->actor.shape.rot.y, pthis->actor.yawTowardsPlayer, 0xC, 0x3E8, 0x64);
        pthis->actor.world.rot.y = pthis->actor.shape.rot.y;
    }
}

void EnSth_LookAtPlayer(EnSth* pthis, GlobalContext* globalCtx) {
    s16 diffRot = pthis->actor.yawTowardsPlayer - pthis->actor.shape.rot.y;

    if ((ABS(diffRot) <= 0x4300) && (pthis->actor.xzDistToPlayer < 100.0f)) {
        func_80038290(globalCtx, &pthis->actor, &pthis->headRot, &pthis->unk_2AC, pthis->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&pthis->headRot.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&pthis->headRot.y, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&pthis->unk_2AC.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&pthis->unk_2AC.y, 0, 6, 0x1838, 0x64);
    }
}

void EnSth_RewardObtainedTalk(EnSth* pthis, GlobalContext* globalCtx) {
    if (Actor_TextboxIsClosing(&pthis->actor, globalCtx)) {
        if (pthis->actor.params == 0) {
            EnSth_SetupAction(pthis, EnSth_ParentRewardObtainedWait);
        } else {
            EnSth_SetupAction(pthis, EnSth_ChildRewardObtainedWait);
        }
    }
    EnSth_FacePlayer(pthis, globalCtx);
}

void EnSth_ParentRewardObtainedWait(EnSth* pthis, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&pthis->actor, globalCtx)) {
        EnSth_SetupAction(pthis, EnSth_RewardObtainedTalk);
    } else {
        pthis->actor.textId = 0x23;
        if (pthis->actor.xzDistToPlayer < 100.0f) {
            func_8002F2CC(&pthis->actor, globalCtx, 100.0f);
        }
    }
    EnSth_LookAtPlayer(pthis, globalCtx);
}

void EnSth_GivePlayerItem(EnSth* pthis, GlobalContext* globalCtx) {
    u16 getItemId = sGetItemIds[pthis->actor.params];

    switch (pthis->actor.params) {
        case 1:
        case 3:
            switch (CUR_UPG_VALUE(UPG_WALLET)) {
                case 0:
                    getItemId = GI_WALLET_ADULT;
                    break;

                case 1:
                    getItemId = GI_WALLET_GIANT;
                    break;
            }
            break;
    }

    func_8002F434(&pthis->actor, globalCtx, getItemId, 10000.0f, 50.0f);
}

void EnSth_GiveReward(EnSth* pthis, GlobalContext* globalCtx) {
    if (Actor_HasParent(&pthis->actor, globalCtx)) {
        pthis->actor.parent = NULL;
        EnSth_SetupAction(pthis, EnSth_RewardObtainedTalk);
        gSaveContext.eventChkInf[13] |= pthis->eventFlag;
    } else {
        EnSth_GivePlayerItem(pthis, globalCtx);
    }
    EnSth_FacePlayer(pthis, globalCtx);
}

void EnSth_RewardUnobtainedTalk(EnSth* pthis, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(globalCtx)) {
        Message_CloseTextbox(globalCtx);
        EnSth_SetupAction(pthis, EnSth_GiveReward);
        EnSth_GivePlayerItem(pthis, globalCtx);
    }
    EnSth_FacePlayer(pthis, globalCtx);
}

void EnSth_RewardUnobtainedWait(EnSth* pthis, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&pthis->actor, globalCtx)) {
        EnSth_SetupAction(pthis, EnSth_RewardUnobtainedTalk);
    } else {
        if (pthis->actor.params == 0) {
            pthis->actor.textId = 0x28;
        } else {
            pthis->actor.textId = 0x21;
        }
        if (pthis->actor.xzDistToPlayer < 100.0f) {
            func_8002F2CC(&pthis->actor, globalCtx, 100.0f);
        }
    }
    EnSth_LookAtPlayer(pthis, globalCtx);
}

void EnSth_ChildRewardObtainedWait(EnSth* pthis, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&pthis->actor, globalCtx)) {
        EnSth_SetupAction(pthis, EnSth_RewardObtainedTalk);
    } else {
        if (gSaveContext.inventory.gsTokens < 50) {
            pthis->actor.textId = 0x20;
        } else {
            pthis->actor.textId = 0x1F;
        }
        if (pthis->actor.xzDistToPlayer < 100.0f) {
            func_8002F2CC(&pthis->actor, globalCtx, 100.0f);
        }
    }
    EnSth_LookAtPlayer(pthis, globalCtx);
}

void EnSth_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* pthis = (EnSth*)thisx;

    pthis->actionFunc(pthis, globalCtx);
}

void EnSth_Update2(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* pthis = (EnSth*)thisx;
    s32 pad;

    Collider_UpdateCylinder(&pthis->actor, &pthis->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &pthis->collider.base);
    Actor_MoveForward(&pthis->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &pthis->actor, 0.0f, 0.0f, 0.0f, 4);
    if (SkelAnime_Update(&pthis->skelAnime)) {
        pthis->skelAnime.curFrame = 0.0f;
    }
    pthis->actionFunc(pthis, globalCtx);

    // Likely an unused blink timer and eye index
    if (DECR(pthis->unk_2B6) == 0) {
        pthis->unk_2B6 = Rand_S16Offset(0x3C, 0x3C);
    }
    pthis->unk_2B4 = pthis->unk_2B6;
    if (pthis->unk_2B4 >= 3) {
        pthis->unk_2B4 = 0;
    }
}

s32 EnSth_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    EnSth* pthis = (EnSth*)thisx;

    s32 temp_v1;

    if (limbIndex == 15) {
        rot->x += pthis->headRot.y;
        rot->z += pthis->headRot.x;
        *dList = D_80B0A050;
    }

    if (pthis->unk_2B2 & 2) {
        pthis->unk_2B2 &= ~2;
        return 0;
    }

    if ((limbIndex == 8) || (limbIndex == 10) || (limbIndex == 13)) {
        temp_v1 = limbIndex * 0x32;
        rot->y += (Math_SinS((globalCtx->state.frames * (temp_v1 + 0x814)).toS16()) * 200.0f);
        rot->z += (Math_CosS((globalCtx->state.frames * (temp_v1 + 0x940)).toS16()) * 200.0f);
    }
    return 0;
}

void EnSth_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    EnSth* pthis = (EnSth*)thisx;

    if (limbIndex == 15) {
        Matrix_MultVec3f(&D_80B0B49C, &pthis->actor.focus.pos);
        if (pthis->actor.params != 0) { // Children
            OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_sth.c", 2079);

            gSPDisplayList(POLY_OPA_DISP++, D_80B0A3C0);

            CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_sth.c", 2081);
        }
    }
}

Gfx* EnSth_AllocColorDList(GraphicsContext* globalCtx, u8 envR, u8 envG, u8 envB, u8 envA) {
    Gfx* dList;

    dList = (Gfx*)Graph_Alloc(globalCtx, 2 * sizeof(Gfx));
    gDPSetEnvColor(dList, envR, envG, envB, envA);
    gSPEndDisplayList(dList + 1);

    return dList;
}

void EnSth_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSth* pthis = (EnSth*)thisx;
    Color_RGB8* envColor1;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_sth.c", 2133);

    gSegments[6] = PHYSICAL_TO_VIRTUAL(gObjectTable[pthis->objectBankIdx].vromStart.get());
    func_800943C8(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               EnSth_AllocColorDList(globalCtx->state.gfxCtx, sTunicColors[pthis->actor.params].r,
                                     sTunicColors[pthis->actor.params].g, sTunicColors[pthis->actor.params].b, 255));

    if (pthis->actor.params == 0) {
        gSPSegment(POLY_OPA_DISP++, 0x09, EnSth_AllocColorDList(globalCtx->state.gfxCtx, 190, 110, 0, 255));
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x09, EnSth_AllocColorDList(globalCtx->state.gfxCtx, 90, 110, 130, 255));
    }
    SkelAnime_DrawFlexOpa(globalCtx, pthis->skelAnime.skeleton, pthis->skelAnime.jointTable, pthis->skelAnime.dListCount,
                          EnSth_OverrideLimbDraw, EnSth_PostLimbDraw, &pthis->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_sth.c", 2176);
}

void EnSth_Reset(Actor* pthisx, GlobalContext* globalCtx) {
    En_Sth_InitVars = {
        ACTOR_EN_STH,
        ACTORCAT_NPC,
        FLAGS,
        OBJECT_GAMEPLAY_KEEP,
        sizeof(EnSth),
        (ActorFunc)EnSth_Init,
        (ActorFunc)EnSth_Destroy,
        (ActorFunc)EnSth_Update,
        NULL,
        (ActorFunc)EnSth_Reset,
    };

    sCylinderInit = {
        {
            COLTYPE_NONE,
            AT_NONE,
            AC_ON | AC_TYPE_ENEMY,
            OC1_ON | OC1_TYPE_ALL,
            OC2_TYPE_1,
            COLSHAPE_CYLINDER,
        },
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            TOUCH_NONE,
            BUMP_ON,
            OCELEM_ON,
        },
        { 30, 40, 0, { 0, 0, 0 } },
    };

    D_80B0B49C = { 700.0f, 400.0f, 0.0f };

}
