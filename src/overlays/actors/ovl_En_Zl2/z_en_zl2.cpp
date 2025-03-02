#define INTERNAL_SRC_OVERLAYS_ACTORS_OVL_EN_ZL2_Z_EN_ZL2_C
#include "actor_common.h"
/*
 * File: z_en_zl2.c
 * Overlay: ovl_En_Zl2
 * Description: Adult Zelda (Cutscenes)
 */

#include "z_en_zl2.h"
#include "vt.h"

#include "overlays/actors/ovl_Door_Warp1/z_door_warp1.h"
#include "objects/object_zl2/object_zl2.h"
#include "objects/object_zl2_anime1/object_zl2_anime1.h"
#include "def/audio_bank.h"
#include "def/math_float.h"
#include "def/graph.h"
#include "def/sys_matrix.h"
#include "def/z_actor.h"
#include "def/z_bgcheck.h"
#include "def/z_common_data.h"
#include "def/z_kankyo.h"
#include "def/z_lib.h"
#include "def/z_parameter.h"
#include "def/z_play.h"
#include "def/z_rcp.h"
#include "def/z_scene.h"
#include "def/z_skelanime.h"

#define FLAGS ACTOR_FLAG_4

void EnZl2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZl2_Reset(Actor* pthisx, GlobalContext* globalCtx);
void EnZl2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZl2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZl2_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80B4F45C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx, Gfx** gfx);

void func_80B50BBC(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50BEC(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50C40(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50CA8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50CFC(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50D50(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50D94(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50DE8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50E3C(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50E90(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50EE4(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50F38(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50F8C(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B50FE8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51034(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51080(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B510CC(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51118(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51164(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B511B0(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B511FC(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51250(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B512B8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51310(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51A5C(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51A8C(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51AE4(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51B44(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51BA8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51C0C(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51C64(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B51CA8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B52068(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B52098(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B52108(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B521A0(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B523BC(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B523C8(EnZl2* pthis, GlobalContext* globalCtx);
void func_80B525D4(EnZl2* pthis, GlobalContext* globalCtx);

static void* sEyeTextures[] = { gZelda2EyeOpenTex, gZelda2EyeHalfTex, gZelda2EyeShutTex,
                                gZelda2Eye03Tex,   gZelda2Eye04Tex,   gZelda2Eye05Tex,
                                gZelda2Eye06Tex,   gZelda2Eye07Tex,   gZelda2Eye08Tex };

static void* sMouthTextures[] = { gZelda2MouthSeriousTex, gZelda2MouthHappyTex, gZelda2MouthOpenTex };

static EnZl2ActionFunc sActionFuncs[] = {
    func_80B521A0, func_80B50BBC, func_80B50BEC, func_80B50C40, func_80B50CA8, func_80B50CFC,
    func_80B50D50, func_80B50D94, func_80B50DE8, func_80B50E3C, func_80B50E90, func_80B50EE4,
    func_80B50F38, func_80B50F8C, func_80B50FE8, func_80B51034, func_80B51080, func_80B510CC,
    func_80B51118, func_80B51164, func_80B511B0, func_80B511FC, func_80B51250, func_80B512B8,
    func_80B51310, func_80B51A5C, func_80B51A8C, func_80B51AE4, func_80B51B44, func_80B51BA8,
    func_80B51C0C, func_80B51C64, func_80B51CA8, func_80B52068, func_80B52098, func_80B52108,
};

static OverrideLimbDraw sOverrideLimbDrawFuncs[] = {
    func_80B4F45C,
};

static EnZl2DrawFunc sDrawFuncs[] = {
    func_80B523BC,
    func_80B523C8,
    func_80B525D4,
};

ActorInit En_Zl2_InitVars = {
    ACTOR_EN_ZL2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZL2,
    sizeof(EnZl2),
    (ActorFunc)EnZl2_Init,
    (ActorFunc)EnZl2_Destroy,
    (ActorFunc)EnZl2_Update,
    (ActorFunc)EnZl2_Draw,
    (ActorFunc)EnZl2_Reset,
};

void EnZl2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZl2* pthis = (EnZl2*)thisx;

    SkelAnime_Free(&pthis->skelAnime, globalCtx);
}

void EnZl2_UpdateEyes(EnZl2* pthis) {
    s32 pad[4];
    s16* eyeTexIndex2 = &pthis->eyeTexIndex2;
    s16* blinkTimer = &pthis->blinkTimer;
    s16* eyeTexIndex = &pthis->eyeTexIndex;

    if (DECR(*blinkTimer) == 0) {
        *blinkTimer = Rand_S16Offset(60, 60);
    }
    *eyeTexIndex = *blinkTimer;
    if (*eyeTexIndex >= 3) {
        *eyeTexIndex = 0;
    }
    *eyeTexIndex2 = *eyeTexIndex;
}

void func_80B4EA40(EnZl2* pthis) {
    s16* eyeTexIndex = &pthis->eyeTexIndex;
    f32* unk_27C = &pthis->unk_27C;

    if (*unk_27C < 3.0f) {
        *eyeTexIndex = 0;
    } else if (*unk_27C < 6.0f) {
        *eyeTexIndex = 1;
    } else if (*unk_27C < 9.0f) {
        *eyeTexIndex = 2;
    } else {
        *eyeTexIndex = 5;
        pthis->eyeTexIndex2 = *eyeTexIndex;
        return;
    }
    *unk_27C += 1.0f;
    pthis->eyeTexIndex2 = *eyeTexIndex;
}

void func_80B4EAF4(EnZl2* pthis) {
    s16* eyeTexIndex = &pthis->eyeTexIndex;
    f32* unk_27C = &pthis->unk_27C;

    if (*unk_27C < 2.0f) {
        *eyeTexIndex = 5;
    } else if (*unk_27C < 4.0f) {
        *eyeTexIndex = 2;
    } else if (*unk_27C < 6.0f) {
        *eyeTexIndex = 1;
    } else {
        EnZl2_UpdateEyes(pthis);
        return;
    }
    *unk_27C += 1.0f;
    pthis->eyeTexIndex2 = *eyeTexIndex;
}

void func_80B4EBB8(EnZl2* pthis) {
    s16* eyeTexIndex = &pthis->eyeTexIndex;
    f32* unk_27C = &pthis->unk_27C;

    if (*unk_27C < 2.0f) {
        *eyeTexIndex = 0;
    } else if (*unk_27C < 4.0f) {
        *eyeTexIndex = 1;
    } else {
        *eyeTexIndex = 2;
        pthis->eyeTexIndex2 = *eyeTexIndex;
        return;
    }
    *unk_27C += 1.0f;
    pthis->eyeTexIndex2 = *eyeTexIndex;
}

void func_80B4EC48(EnZl2* pthis) {
    s16* eyeTexIndex = &pthis->eyeTexIndex;
    f32* unk_27C = &pthis->unk_27C;

    if (*unk_27C < 2.0f) {
        *eyeTexIndex = 2;
    } else if (*unk_27C < 4.0f) {
        *eyeTexIndex = 1;
    } else {
        EnZl2_UpdateEyes(pthis);
        return;
    }
    *unk_27C += 1.0f;
    pthis->eyeTexIndex2 = *eyeTexIndex;
}

void EnZl2_setEyesIndex(EnZl2* pthis, s16 index) {
    pthis->eyeTexIndex = index;
    pthis->eyeTexIndex2 = pthis->eyeTexIndex;
}

void EnZl2_setEyeIndex2(EnZl2* pthis, s16 index) {
    pthis->eyeTexIndex2 = index;
}

void EnZl2_setMouthIndex(EnZl2* pthis, s16 index) {
    pthis->mouthTexIndex = index;
}

void func_80B4ED2C(EnZl2* pthis, GlobalContext* globalCtx) {
    Actor_UpdateBgCheckInfo(globalCtx, &pthis->actor, 75.0f, 30.0f, 30.0f, 5);
}

s32 EnZl2_UpdateSkelAnime(EnZl2* pthis) {
    return SkelAnime_Update(&pthis->skelAnime);
}

CsCmdActorAction* EnZl2_GetNpcAction(GlobalContext* globalCtx, s32 idx) {
    if (globalCtx->csCtx.state != CS_STATE_IDLE) {
        return globalCtx->csCtx.npcActions[idx];
    }
    return NULL;
}

void func_80B4EDB8(EnZl2* pthis, GlobalContext* globalCtx, s32 arg2) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, arg2);

    if (npcAction != NULL) {
        pthis->actor.world.pos.x = npcAction->startPos.x;
        pthis->actor.world.pos.y = npcAction->startPos.y;
        pthis->actor.world.pos.z = npcAction->startPos.z;
        pthis->actor.world.rot.y = pthis->actor.shape.rot.y = npcAction->rot.y;
    }
}

void func_80B4EE38(EnZl2* pthis, s16 arg1, s32 arg2) {
    s32 phi_a3;
    s32 temp_v1;
    s32 phi_v0 = arg2;

    if (pthis->unk_24C != 0) {
        temp_v1 = (s16)(arg1 + pthis->unk_1DC[phi_v0]);
        phi_a3 = arg1 - pthis->unk_20C[phi_v0];
        phi_v0 = pthis->unk_1AC[phi_v0];

        if ((s32)fabsf((f32)phi_a3) > 0x8000) {
            if (arg1 > 0) {
                phi_a3 -= 0x10000;
            } else {
                phi_a3 += 0x10000;
            }
        }
        if (phi_a3 != 0) {
            phi_v0 += (phi_a3 - phi_v0) / 16;
        }
        if (phi_v0 != 0) {
            phi_v0 -= (phi_v0 / 10);
        }
        if ((s16)(temp_v1 - arg1) != 0) {
            phi_v0 -= ((s16)(temp_v1 - arg1) / 50);
        }
        temp_v1 += phi_v0;
        if (((pthis->unk_1AC[arg2] * phi_v0) <= 0) && ((s16)(temp_v1 - arg1) > -0x64) &&
            ((s16)(temp_v1 - arg1) < 0x64)) {
            temp_v1 = arg1;
            phi_v0 = 0;
        }
        pthis->unk_1AC[arg2] = phi_v0;
        pthis->unk_1DC[arg2] = temp_v1 - arg1;
    }
    pthis->unk_20C[arg2] = arg1;
}

void func_80B4EF64(EnZl2* pthis, s16 arg1, s32 arg2) {
    s32 temp_t0 = arg2;
    s32 temp_t2;
    s32 temp_v1;
    s32 phi_t1;
    s32 phi_v0;
    s32 phi_a0;
    f32 curFrame;
    f32 unk_278;

    if (temp_t0 == 2) {
        phi_a0 = 0x3A98;
        phi_t1 = 0;
    } else if (temp_t0 == 5) {
        phi_a0 = 0x32C8;
        phi_t1 = 3;
    } else if (temp_t0 == 8) {
        phi_a0 = 0x2EE0;
        phi_t1 = 6;
    } else if (temp_t0 == 11) {
        phi_a0 = 0x4000;
        phi_t1 = 9;
    } else if (temp_t0 == 14) {
        phi_a0 = 0x4000;
        phi_t1 = 12;
    } else if (temp_t0 == 17) {
        phi_a0 = 0x4000;
        phi_t1 = 15;
    } else {
        phi_a0 = 0x4000;
        phi_t1 = 18;
    }

    if (pthis->unk_24C != 0) {
        phi_v0 = pthis->unk_1DC[temp_t0] + arg1;
        temp_v1 = (s16)(phi_v0 & 0xFFFF);
        temp_t2 = arg1 - pthis->unk_20C[temp_t0];
        phi_v0 = pthis->unk_1AC[temp_t0];

        if ((s32)fabsf((f32)temp_t2) > 0x8000) {
            if (arg1 > 0) {
                temp_t2 -= 0x10000;
            } else {
                temp_t2 += 0x10000;
            }
        }
        if (phi_t1 >= 0) {
            temp_t2 += (ABS(pthis->unk_1AC[phi_t1]) / 3);
        }
        if (temp_t2 != 0) {
            phi_v0 += ((temp_t2 - phi_v0) / 16);
        }
        if (phi_v0 != 0) {
            phi_v0 -= phi_v0 / 10;
        }
        if ((s16)(temp_v1 - phi_a0) != 0) {
            phi_v0 -= (s16)(temp_v1 - phi_a0) / 50;
        }
        temp_v1 += phi_v0;

        if (((pthis->unk_1AC[arg2] * phi_v0) <= 0) && ((s16)(temp_v1 - phi_a0) > -0x64) &&
            ((s16)(temp_v1 - phi_a0) < 0x64)) {
            temp_v1 = phi_a0;
            phi_v0 = 0;
        }

        if (arg2 == 2) {
            if ((pthis->action == 5) || (pthis->action == 30)) {
                curFrame = pthis->skelAnime.curFrame;
                unk_278 = pthis->unk_278;
                temp_t0 = (s32)((3500.0f * curFrame) / unk_278) + phi_a0;
                if (temp_t0 >= temp_v1) {
                    temp_v1 = temp_t0;
                    phi_v0 /= -2;
                }
            } else if ((pthis->action == 6) || (pthis->action == 31)) {
                temp_t0 = phi_a0 + 0xDAC;
                if (temp_t0 >= temp_v1) {
                    temp_v1 = temp_t0;
                    phi_v0 /= -2;
                }
            } else if (pthis->action == 20) {
                temp_t0 = phi_a0 - 0x3E8;
                if (temp_t0 >= temp_v1) {
                    temp_v1 = temp_t0;
                    phi_v0 /= -2;
                }
            }
        }
        pthis->unk_1AC[arg2] = phi_v0;
        pthis->unk_1DC[arg2] = temp_v1 - arg1;
    }
    pthis->unk_20C[arg2] = arg1;
}

void func_80B4F230(EnZl2* pthis, s16 arg1, s32 arg2) {
    s32 temp_v1;
    s16 temp_t0;
    s32 temp_t2;
    s32 temp_t3;
    s32 phi_v0;
    s32 index1AC;
    s32 phi_t5;

    if (pthis->unk_24C != 0) {
        temp_v1 = pthis->unk_1DC[arg2] - arg1;
        temp_t0 = temp_v1;
        temp_t2 = temp_t0;
        temp_t3 = pthis->unk_1AC[arg2];
        phi_v0 = temp_t3;
        temp_t3 = arg1 - pthis->unk_20C[arg2];

        if (arg2 == 1) {
            index1AC = 0;
            phi_t5 = pthis->unk_1AC[index1AC];
        } else if (arg2 == 4) {
            index1AC = 3;
            phi_t5 = pthis->unk_1AC[index1AC];
        } else if (arg2 == 7) {
            index1AC = 6;
            phi_t5 = pthis->unk_1AC[index1AC];
        } else if (arg2 == 10) {
            index1AC = 9;
            phi_t5 = ABS(pthis->unk_1AC[index1AC]);
        } else if (arg2 == 13) {
            index1AC = 12;
            phi_t5 = ABS(pthis->unk_1AC[index1AC]);
        } else if (arg2 == 16) {
            index1AC = 15;
            phi_t5 = -ABS(pthis->unk_1AC[index1AC]);
        } else {
            index1AC = 18;
            phi_t5 = -ABS(pthis->unk_1AC[index1AC]);
        }

        if ((s32)fabsf(temp_t3) > 0x8000) {
            if (arg1 > 0) {
                temp_t3 -= 0x10000;
            } else {
                temp_t3 += 0x10000;
            }
        }
        if (index1AC >= 0) {
            temp_t3 += phi_t5 / 3;
        }

        if (temp_t3 != 0) {
            phi_v0 += (temp_t3 - phi_v0) / 16;
        }
        if (phi_v0 != 0) {
            phi_v0 -= phi_v0 / 10;
        }
        if (temp_t0 != 0) {
            phi_v0 -= temp_t0 / 50;
        }
        temp_v1 += phi_v0;
        if (((pthis->unk_1AC[arg2] * phi_v0) <= 0) && (temp_t2 > -0x64) && (temp_t2 < 0x64)) {
            temp_v1 = 0;
            phi_v0 = 0;
        }
        pthis->unk_1AC[arg2] = phi_v0;
        pthis->unk_1DC[arg2] = arg1 + temp_v1;
    }
    pthis->unk_20C[arg2] = arg1;
}

s32 func_80B4F45C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                  Gfx** gfx) {
    s32 pad;
    EnZl2* pthis = (EnZl2*)thisx;
    Mtx* sp74;
    MtxF sp34;
    Vec3s sp2C;
    s16 pad2;
    s16* unk_1DC = pthis->unk_1DC;

    if (limbIndex == 14) {
        sp74 = (Mtx*)Graph_Alloc(globalCtx->state.gfxCtx, sizeof(Mtx) * 7);
        gSPSegment((*gfx)++, 0x0C, sp74);

        Matrix_Push();
        Matrix_Translate(pos->x, pos->y, pos->z, MTXMODE_APPLY);
        Matrix_RotateZYX(rot->x, rot->y, rot->z, MTXMODE_APPLY);
        Matrix_Push();
        Matrix_Translate(362.0f, -133.0f, 0.0f, MTXMODE_APPLY);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 0);
            func_80B4F230(pthis, sp2C.x, 1);
            func_80B4EF64(pthis, sp2C.z, 2);
        }
        Matrix_RotateZYX(unk_1DC[0] + kREG(31), unk_1DC[1] + kREG(32), unk_1DC[2] + kREG(33), MTXMODE_APPLY);
        Matrix_Translate(-188.0f, -184.0f, 0.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[0], "../z_en_zl2.c", 1056);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 3);
            func_80B4F230(pthis, sp2C.x, 4);
        }
        Matrix_RotateZYX(unk_1DC[3] + kREG(34), unk_1DC[4] + kREG(35), unk_1DC[5] + kREG(36), MTXMODE_APPLY);
        Matrix_Translate(-410.0f, -184.0f, 0.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[1], "../z_en_zl2.c", 1100);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 6);
            func_80B4F230(pthis, sp2C.x, 7);
        }
        Matrix_RotateZYX(unk_1DC[6] + kREG(37), unk_1DC[7] + kREG(38), unk_1DC[8] + kREG(39), MTXMODE_APPLY);
        Matrix_Translate(-1019.0f, -26.0f, 0.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[2], "../z_en_zl2.c", 1120);
        Matrix_Pop();
        Matrix_Push();
        Matrix_Translate(467.0f, 265.0f, 389.0f, MTXMODE_APPLY);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 9);
            func_80B4F230(pthis, sp2C.x, 10);
            func_80B4EF64(pthis, sp2C.z, 11);
        }
        Matrix_RotateZYX(unk_1DC[9] + kREG(40), unk_1DC[10] + kREG(41), unk_1DC[11] + kREG(42), MTXMODE_APPLY);
        Matrix_Translate(-427.0f, -1.0f, -3.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[3], "../z_en_zl2.c", 1145);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 12);
            func_80B4F230(pthis, sp2C.x, 13);
            func_80B4EF64(pthis, sp2C.z, 14);
        }
        Matrix_RotateZYX(unk_1DC[12] + kREG(43), unk_1DC[13] + kREG(44), unk_1DC[14] + kREG(45), MTXMODE_APPLY);
        Matrix_Translate(-446.0f, -52.0f, 84.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[4], "../z_en_zl2.c", 1164);
        Matrix_Pop();
        Matrix_Push();
        Matrix_Translate(467.0f, 265.0f, -389.0f, MTXMODE_APPLY);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 15);
            func_80B4F230(pthis, sp2C.x, 16);
            func_80B4EF64(pthis, sp2C.z, 17);
        }
        Matrix_RotateZYX(unk_1DC[15] + kREG(46), unk_1DC[16] + kREG(47), unk_1DC[17] + kREG(48), MTXMODE_APPLY);
        Matrix_Translate(-427.0f, -1.0f, 3.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[5], "../z_en_zl2.c", 1189);
        Matrix_Get(&sp34);
        Matrix_MtxFToYXZRotS(&sp34, &sp2C, 0);
        if (!FrameAdvance_IsEnabled(globalCtx)) {
            func_80B4EE38(pthis, sp2C.y, 18);
            func_80B4F230(pthis, sp2C.x, 19);
            func_80B4EF64(pthis, sp2C.z, 20);
        }
        Matrix_RotateZYX(unk_1DC[18] + kREG(49), unk_1DC[19] + kREG(50), unk_1DC[20] + kREG(51), MTXMODE_APPLY);
        Matrix_Translate(-446.0f, -52.0f, -84.0f, MTXMODE_APPLY);
        Matrix_ToMtx(&sp74[6], "../z_en_zl2.c", 1208);
        Matrix_Pop();
        Matrix_Pop();
        pthis->unk_24C = 1;
    }
    return false;
}

void EnZl2_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    EnZl2* pthis = (EnZl2*)thisx;
    s32 pad[2];

    if (limbIndex == 10) {
        if ((pthis->unk_254 != 0) && (globalCtx->csCtx.frames >= 900)) {
            gSPDisplayList((*gfx)++, gZelda2OcarinaDL);
        }

        {
            Player* player = GET_PLAYER(globalCtx);
            Matrix_Push();
            if (player->rightHandType == 0xFF) {
                Matrix_Put(&player->shieldMf);
                Matrix_Translate(180.0f, 979.0f, -375.0f, MTXMODE_APPLY);
                Matrix_RotateZYX(-0x5DE7, -0x53E9, 0x3333, MTXMODE_APPLY);
                Matrix_Scale(1.2f, 1.2f, 1.2f, MTXMODE_APPLY);
                gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_zl2.c", 1253),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList((*gfx)++, gZelda2OcarinaDL);
            }
            Matrix_Pop();
        }
    }
}

void func_80B4FCCC(EnZl2* pthis, GlobalContext* globalCtx) {
    s32 unk_274 = pthis->unk_274;

    gSegments[6] = VIRTUAL_TO_PHYSICAL(gObjectTable[unk_274].vromStart.get());
}

void func_80B4FD00(EnZl2* pthis, AnimationHeader* animation, u8 arg2, f32 transitionRate, s32 arg4) {
    f32 frameCount = Animation_GetLastFrame(animation);
    f32 playbackSpeed;
    f32 unk0;
    f32 fc;

    if (arg4 == 0) {
        unk0 = 0.0f;
        fc = frameCount;
        playbackSpeed = 1.0f;
    } else {
        fc = 0.0f;
        unk0 = frameCount;
        playbackSpeed = -1.0f;
    }

    Animation_Change(&pthis->skelAnime, animation, playbackSpeed, unk0, fc, arg2, transitionRate);
}

void func_80B4FD90(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00B5FC, 0, 0.0f, 0);
    pthis->action = 1;
}

void func_80B4FDD4(EnZl2* pthis) {
    if (Animation_OnFrame(&pthis->skelAnime, 14.0f)) {
        Common_PlaySfxAtPos(&pthis->actor.projectedPos, NA_SE_PL_WALK_CONCRETE);
    }
}

void func_80B4FE10(GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.frames >= 830) && (globalCtx->csCtx.frames < 1081)) {
        Common_PlaySfx2(NA_SE_EV_EARTHQUAKE - SFX_FLAG);
    }
}

void func_80B4FE48(EnZl2* pthis) {
    Common_PlaySfxAtPos(&pthis->actor.projectedPos, NA_SE_EV_GOTO_HEAVEN - SFX_FLAG);
}

void func_80B4FE6C(EnZl2* pthis) {
    Common_PlaySfxAtPos(&pthis->actor.projectedPos, NA_SE_EN_GANON_LAUGH);
}

void func_80B4FE90(EnZl2* pthis) {
    Common_PlaySfxAtPos(&pthis->actor.projectedPos, NA_SE_VO_Z1_SURPRISE);
}

void func_80B4FEB4(EnZl2* pthis) {
    Common_PlaySfxAtPos(&pthis->actor.projectedPos, NA_SE_VO_Z1_PAIN);
}

void func_80B4FED8(EnZl2* pthis) {
    Common_PlaySfxAtPos(&pthis->actor.projectedPos, NA_SE_VO_Z1_CRY_0);
}

void EnZl2_GiveLightArrows(EnZl2* pthis, GlobalContext* globalCtx) {
    Player* player;
    f32 posX;
    f32 posY;
    f32 posZ;

    if (pthis->unk_244 == 0) {
        player = GET_PLAYER(globalCtx);
        posX = player->actor.world.pos.x;
        posY = player->actor.world.pos.y + 80.0f;
        posZ = player->actor.world.pos.z;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_DEMO_EFFECT, posX, posY, posZ, 0, 0, 0, 0x17);
        Item_Give(globalCtx, ITEM_ARROW_LIGHT);
        pthis->unk_244 = 1;
    }
}

void func_80B4FF84(EnZl2* pthis, GlobalContext* globalCtx) {
    f32 posX;
    f32 posY;
    f32 posZ;

    if (pthis->unk_250 == 0) {
        posX = pthis->actor.world.pos.x;
        posY = pthis->actor.world.pos.y;
        posZ = pthis->actor.world.pos.z;

        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_DOOR_WARP1, posX, posY, posZ, 0, 0, 0, WARP_YELLOW);
        pthis->unk_250 = 1;
    }
}

void func_80B4FFF0(EnZl2* pthis, GlobalContext* globalCtx) {
    f32 posX;
    f32 posY;
    f32 posZ;

    if (pthis->unk_248 == 0) {
        posX = pthis->actor.world.pos.x;
        posY = pthis->actor.world.pos.y + (kREG(5) + -26.0f);
        posZ = pthis->actor.world.pos.z;

        Actor_SpawnAsChild(&globalCtx->actorCtx, &pthis->actor, globalCtx, ACTOR_DOOR_WARP1, posX, posY, posZ, 0, 0x4000,
                           0, WARP_PURPLE_CRYSTAL);
        pthis->unk_248 = 1;
    }
}

void func_80B5008C(EnZl2* pthis) {
    Actor* child = pthis->actor.child;

    if (child != NULL) {
        child->world.pos.x = pthis->actor.world.pos.x;
        child->world.pos.y = pthis->actor.world.pos.y + (kREG(5) + -26.0f);
        child->world.pos.z = pthis->actor.world.pos.z;
    }
}

void func_80B500E0(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    Vec3f* thisPos = &pthis->actor.world.pos;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 someFloat;

    if (npcAction != NULL) {
	    someFloat  = Environment_LerpWeightAccelDecel(npcAction->endFrame, npcAction->startFrame, globalCtx->csCtx.frames, 8, 8);
        startX = npcAction->startPos.x;
        startY = npcAction->startPos.y;
        startZ = npcAction->startPos.z;
        endX = npcAction->endPos.x;
        endY = npcAction->endPos.y;
        endZ = npcAction->endPos.z;
        thisPos->x = ((endX - startX) * someFloat) + startX;
        thisPos->y = ((endY - startY) * someFloat) + startY;
        thisPos->z = ((endZ - startZ) * someFloat) + startZ;
    }
}

void func_80B501C4(EnZl2* pthis, s32 alpha) {
    if (pthis->actor.child != NULL) {
        ((DoorWarp1*)pthis->actor.child)->crystalAlpha = alpha;
    }
}

void func_80B501E8(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);

    if (npcAction != NULL) {
	    pthis->actor.shape.shadowAlpha = pthis->alpha = (1.0f - Environment_LerpWeight(npcAction->endFrame, npcAction->startFrame, globalCtx->csCtx.frames)) *
            255.0f;
        func_80B501C4(pthis, pthis->alpha);
    }
}

void func_80B50260(EnZl2* pthis, GlobalContext* globalCtx) {
    pthis->action = 1;
    pthis->drawConfig = 0;
    pthis->actor.shape.shadowAlpha = 0;
}

void func_80B50278(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);

    pthis->actor.world.pos.x = npcAction->startPos.x;
    pthis->actor.world.pos.y = npcAction->startPos.y;
    pthis->actor.world.pos.z = npcAction->startPos.z;
    pthis->actor.world.rot.y = pthis->actor.shape.rot.y = npcAction->rot.y;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->action = 2;
    pthis->drawConfig = 1;
}

void func_80B50304(EnZl2* pthis, GlobalContext* globalCtx) {
    s32 pad[2];
    ActorShape* shape = &pthis->actor.shape;
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    f32 actionXDelta;
    f32 actionZDelta;

    actionXDelta = npcAction->endPos.x - npcAction->startPos.x;
    actionZDelta = npcAction->endPos.z - npcAction->startPos.z;
    func_80B4FD00(pthis, &gZelda2Anime1Anim_0003BC, 0, -12.0f, 0);
    pthis->action = 3;
    pthis->drawConfig = 1;
    pthis->unk_23C = 0.0f;
    shape->shadowAlpha = 255;
    pthis->actor.world.rot.y = shape->rot.y = Math_FAtan2F(actionXDelta, actionZDelta) * (0x8000 / M_PI);
}

void func_80B503DC(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);

    if ((npcAction != NULL) && (globalCtx->csCtx.frames >= npcAction->endFrame)) {
        pthis->action = 4;
    }
}

void func_80B5042C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_0022D0, 2, -8.0f, 0);
    pthis->action = 5;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->unk_27C = 0.0f;
}

void func_80B50488(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_002750, 0, 0.0f, 0);
        pthis->action = 6;
        pthis->drawConfig = 1;
    }
}

void func_80B504D4(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00325C, 2, -8.0f, 0);
    pthis->action = 7;
    pthis->drawConfig = 1;
    pthis->unk_27C = 0.0f;
    EnZl2_setMouthIndex(pthis, 1);
    pthis->actor.shape.shadowAlpha = 0xFF;
}

void func_80B5053C(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_003538, 0, 0.0f, 0);
        pthis->action = 8;
    }
}

void func_80B50580(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_000A50, 2, -8.0f, 0);
    pthis->action = 9;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
}

void func_80B505D4(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_000EB0, 0, 0.0f, 0);
        pthis->action = 10;
    }
}

void func_80B50618(EnZl2* pthis, GlobalContext* globalCtx) {
    EnZl2_GiveLightArrows(pthis, globalCtx);
    pthis->action = 11;
}

void func_80B50644(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FF84(pthis, globalCtx);
    pthis->action = 12;
}

void func_80B50670(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00B5FC, 0, -8.0f, 0);
    pthis->action = 13;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
}

void func_80B506C4(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00AAD4, 2, -8.0f, 0);
    pthis->action = 14;
    pthis->drawConfig = 1;
    EnZl2_setEyesIndex(pthis, 4);
    EnZl2_setMouthIndex(pthis, 2);
    pthis->actor.shape.shadowAlpha = 0xFF;
    func_80B4FE90(pthis);
}

void func_80B5073C(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_00AFE0, 0, 0.0f, 0);
        pthis->action = 15;
    }
}

void func_80B50780(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_001670, 2, -8.0f, 0);
    pthis->action = 16;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    func_80B4FFF0(pthis, globalCtx);
    EnZl2_setEyesIndex(pthis, 3);
}

void func_80B507E8(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_001B48, 0, 0.0f, 0);
        pthis->action = 17;
    }
}

void func_80B5082C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_002B14, 2, -8.0f, 0);
    pthis->action = 18;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
}

void func_80B50880(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_002F30, 0, 0.0f, 0);
        pthis->action = 19;
        func_80B4FEB4(pthis);
    }
}

void func_80B508C8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_001010, 2, -8.0f, 0);
    pthis->action = 20;
    pthis->drawConfig = 1;
    EnZl2_setEyesIndex(pthis, 6);
    pthis->actor.shape.shadowAlpha = 0xFF;
}

void func_80B50928(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_0013A0, 0, 0.0f, 0);
        pthis->action = 21;
        func_80B4FED8(pthis);
    }
}

void func_80B50970(EnZl2* pthis, GlobalContext* globalCtx) {
    pthis->action = 22;
}

void func_80B50980(EnZl2* pthis, GlobalContext* globalCtx) {
    pthis->action = 23;
    pthis->drawConfig = 2;
    pthis->alpha = 255;
}

void func_80B509A0(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);

    if (npcAction != NULL) {
        if (globalCtx->csCtx.frames >= npcAction->endFrame) {
            pthis->action = 24;
            pthis->drawConfig = 0;
            func_80B4FE6C(pthis);
        }
    }
}

void func_80B50A04(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    s32 newAction;
    s32 unk_240;

    if (npcAction != NULL) {
        newAction = npcAction->action;
        unk_240 = pthis->unk_240;
        if (newAction != unk_240) {
            switch (newAction) {
                case 1:
                    func_80B50260(pthis, globalCtx);
                    break;
                case 2:
                    func_80B50278(pthis, globalCtx);
                    break;
                case 3:
                    func_80B50304(pthis, globalCtx);
                    break;
                case 4:
                    func_80B5042C(pthis, globalCtx);
                    break;
                case 5:
                    func_80B504D4(pthis, globalCtx);
                    break;
                case 6:
                    func_80B50580(pthis, globalCtx);
                    break;
                case 7:
                    func_80B50618(pthis, globalCtx);
                    break;
                case 8:
                    func_80B50670(pthis, globalCtx);
                    break;
                case 9:
                    func_80B506C4(pthis, globalCtx);
                    break;
                case 10:
                    func_80B50780(pthis, globalCtx);
                    break;
                case 11:
                    func_80B5082C(pthis, globalCtx);
                    break;
                case 12:
                    func_80B508C8(pthis, globalCtx);
                    break;
                case 13:
                    func_80B50970(pthis, globalCtx);
                    break;
                case 14:
                    func_80B50980(pthis, globalCtx);
                    break;
                case 15:
                    func_80B50644(pthis, globalCtx);
                    break;
                default:
                    osSyncPrintf("En_Zl2_inAgain_Check_DemoMode:そんな動作は無い!!!!!!!!\n");
            }
            pthis->unk_240 = newAction;
        }
    }
}

void func_80B50BBC(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50BEC(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50C40(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FDD4(pthis);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B500E0(pthis, globalCtx);
    func_80B503DC(pthis, globalCtx);
}

void func_80B50CA8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50CFC(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B4EA40(pthis);
    func_80B50488(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B50D50(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50D94(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B4EAF4(pthis);
    func_80B5053C(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B50DE8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50E3C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    func_80B505D4(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B50E90(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50EE4(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50F38(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50F8C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B50FE8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B5073C(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B51034(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B51080(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B507E8(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B510CC(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B51118(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B50880(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B51164(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B511B0(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE10(globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B50928(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B511FC(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B5008C(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B51250(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4FE48(pthis);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B500E0(pthis, globalCtx);
    func_80B5008C(pthis);
    func_80B50A04(pthis, globalCtx);
}

void func_80B512B8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B501E8(pthis, globalCtx);
    func_80B509A0(pthis, globalCtx);
}

void func_80B51310(EnZl2* pthis, GlobalContext* globalCtx) {
    Actor* child;

    if (EnZl2_GetNpcAction(globalCtx, 0) == NULL) {
        child = pthis->actor.child;
        if (child != NULL) {
            Actor_Kill(child);
        }
        Actor_Kill(&pthis->actor);
    }
}

void func_80B5135C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00A15C, 0, 0.0f, 0);
    pthis->action = 25;
    pthis->unk_254 = 1;
}

void func_80B513A8(EnZl2* pthis, GlobalContext* globalCtx) {
    Player* player;
    f32 posX;
    f32 posY;
    f32 posZ;

    if (pthis->unk_250 == 0) {
        player = GET_PLAYER(globalCtx);
        posX = player->actor.world.pos.x;
        posY = player->actor.world.pos.y;
        posZ = player->actor.world.pos.z;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_DOOR_WARP1, posX, posY, posZ, 0, 0, 0, WARP_UNK_7);
        pthis->unk_250 = 1;
    }
}

void func_80B51418(EnZl2* pthis, GlobalContext* globalCtx) {
    EnZl2_UpdateEyes(pthis);
    if (globalCtx->csCtx.frames < 431) {
        EnZl2_setMouthIndex(pthis, 1);
    } else {
        EnZl2_setMouthIndex(pthis, 0);
    }
}

void func_80B5146C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4EA40(pthis);
    EnZl2_setMouthIndex(pthis, 0);
}

void func_80B5149C(EnZl2* pthis, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames < 988) {
        EnZl2_setEyesIndex(pthis, 7);
        EnZl2_setEyeIndex2(pthis, 8);
    } else {
        EnZl2_UpdateEyes(pthis);
    }
    EnZl2_setMouthIndex(pthis, 0);
}

void func_80B514F8(EnZl2* pthis, GlobalContext* globalCtx) {
    EnZl2_UpdateEyes(pthis);
    if (globalCtx->csCtx.frames < 1190) {
        EnZl2_setMouthIndex(pthis, 1);
    } else {
        EnZl2_setMouthIndex(pthis, 0);
    }
}

void func_80B5154C(EnZl2* pthis, GlobalContext* globalCtx) {
    CutsceneContext* csCtx;

    if (pthis->skelAnime.mode != 0) {
        EnZl2_UpdateEyes(pthis);
    } else {
        csCtx = &globalCtx->csCtx;
        if (csCtx->frames < 0x5F0) {
            func_80B4EBB8(pthis);
        } else if (csCtx->frames == 0x5F0) {
            pthis->unk_27C = 0.0f;
        } else {
            func_80B4EC48(pthis);
        }
    }
}

void func_80B515C4(EnZl2* pthis) {
    pthis->action = 25;
    pthis->drawConfig = 0;
    pthis->actor.shape.shadowAlpha = 0;
}

void func_80B515D8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00A15C, 0, -8.0f, 0);
    func_80B4EDB8(pthis, globalCtx, 0);
    pthis->action = 26;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->unk_27C = 0.0f;
}

void func_80B51644(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_0087B8, 0, -8.0f, 0);
    }
}

void func_80B51678(EnZl2* pthis) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_007D0C, 2, -8.0f, 0);
    pthis->action = 27;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->unk_27C = 0.0f;
}

void func_80B516D0(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_009AD4, 0, -8.0f, 0);
    }
}

void func_80B51704(EnZl2* pthis) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_0090D8, 2, -8.0f, 0);
    pthis->action = 28;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->unk_27C = 0.0f;
}

void func_80B5175C(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_006778, 0, -8.0f, 0);
    }
}

void func_80B51790(EnZl2* pthis) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_005F40, 2, -8.0f, 0);
    pthis->action = 29;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
}

void func_80B517E0(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_002750, 0, -8.0f, 0);
        pthis->action = 31;
    }
}

void func_80B51824(EnZl2* pthis) {
    func_80B4FD00(pthis, &gZelda2Anime1Anim_0022D0, 2, -8.0f, 0);
    pthis->action = 30;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->unk_27C = 0.0f;
}

void func_80B5187C(EnZl2* pthis, s32 arg1) {
    if (arg1 != 0) {
        func_80B4FD00(pthis, &gZelda2Anime1Anim_00A79C, 0, -8.0f, 0);
        pthis->unk_27C = 0.0f;
    }
}

void func_80B518C0(EnZl2* pthis) {
    func_80B4FD00(pthis, SEGMENTED_TO_VIRTUAL(&gZelda2Anime1Anim_004900), 2, -8.0f, 0);
    pthis->action = 32;
    pthis->drawConfig = 1;
    pthis->actor.shape.shadowAlpha = 0xFF;
    pthis->unk_27C = 0.0f;
}

void func_80B51948(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    s32 newAction;
    s32 unk_240;

    if (npcAction != NULL) {
        newAction = npcAction->action;
        unk_240 = pthis->unk_240;
        if (newAction != unk_240) {
            switch (newAction) {
                case 1:
                    func_80B515C4(pthis);
                    break;
                case 2:
                    func_80B515D8(pthis, globalCtx);
                    break;
                case 16:
                    func_80B51678(pthis);
                    break;
                case 17:
                    func_80B51704(pthis);
                    break;
                case 18:
                    func_80B51790(pthis);
                    break;
                case 4:
                    func_80B51824(pthis);
                    break;
                case 20:
                    func_80B518C0(pthis);
                    break;
                case 21:
                    func_80B513A8(pthis, globalCtx);
                    break;
                default:
                    osSyncPrintf("En_Zl2_inEnding_Check_DemoMode:そんな動作は無い!!!!!!!!\n");
            }
            pthis->unk_240 = newAction;
        }
    }
}

void func_80B51A5C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B51948(pthis, globalCtx);
}

void func_80B51A8C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B51418(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B51948(pthis, globalCtx);
}

void func_80B51AE4(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    func_80B51644(pthis, EnZl2_UpdateSkelAnime(pthis));
    func_80B51948(pthis, globalCtx);
}

void func_80B51B44(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B5149C(pthis, globalCtx);
    func_80B516D0(pthis, EnZl2_UpdateSkelAnime(pthis));
    func_80B51948(pthis, globalCtx);
}

void func_80B51BA8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B514F8(pthis, globalCtx);
    func_80B5175C(pthis, EnZl2_UpdateSkelAnime(pthis));
    func_80B51948(pthis, globalCtx);
}

void func_80B51C0C(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B5146C(pthis, globalCtx);
    func_80B517E0(pthis, EnZl2_UpdateSkelAnime(pthis));
}

void func_80B51C64(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B51948(pthis, globalCtx);
}

void func_80B51CA8(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    func_80B5154C(pthis, globalCtx);
    func_80B5187C(pthis, EnZl2_UpdateSkelAnime(pthis));
    func_80B51948(pthis, globalCtx);
}

void func_80B51D0C(EnZl2* pthis, GlobalContext* globalCtx) {
    pthis->action = 33;
    pthis->drawConfig = 0;
    pthis->actor.shape.shadowAlpha = 0;
}

void func_80B51D24(EnZl2* pthis, GlobalContext* globalCtx) {
    s32 pad[2];
    u32 sfxId;
    SkelAnime* skelAnime = &pthis->skelAnime;

    if (Animation_OnFrame(skelAnime, 6.0f) || Animation_OnFrame(skelAnime, 0.0f)) {
        if (pthis->actor.bgCheckFlags & 1) {
            sfxId = SFX_FLAG;
            sfxId += SurfaceType_GetSfx(&globalCtx->colCtx, pthis->actor.floorPoly, pthis->actor.floorBgId);
            Common_PlaySfxAtPos(&pthis->actor.projectedPos, sfxId);
        }
    }
}

void func_80B51DA4(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    Vec3f* thisPos = &pthis->actor.world.pos;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 someFloat;

    if (npcAction != NULL) {
	    someFloat  = Environment_LerpWeightAccelDecel(npcAction->endFrame, npcAction->startFrame, globalCtx->csCtx.frames, 0, 8);
        startX = npcAction->startPos.x;
        startY = npcAction->startPos.y;
        startZ = npcAction->startPos.z;
        endX = npcAction->endPos.x;
        endY = npcAction->endPos.y;
        endZ = npcAction->endPos.z;
        thisPos->x = ((endX - startX) * someFloat) + startX;
        thisPos->y = ((endY - startY) * someFloat) + startY;
        thisPos->z = ((endZ - startZ) * someFloat) + startZ;
        if (globalCtx->csCtx.frames > npcAction->endFrame) {
            Actor_Kill(&pthis->actor);
        }
    }
}

void func_80B51EA8(EnZl2* pthis) {
    pthis->action = 33;
    pthis->drawConfig = 0;
    pthis->actor.shape.shadowAlpha = 0;
}

void func_80B51EBC(EnZl2* pthis, GlobalContext* globalCtx) {
    ActorShape* shape = &pthis->actor.shape;
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    s32 pad[2];

    pthis->actor.world.rot.y = shape->rot.y = npcAction->rot.y;
    func_80B4FD00(pthis, &gZelda2Anime1Anim_00B224, 0, 0.0f, 0);
    pthis->action = 34;
    pthis->drawConfig = 1;
    shape->shadowAlpha = 255;
}

void func_80B51F38(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);

    if (npcAction != NULL) {
        if (globalCtx->csCtx.frames - 8 >= npcAction->endFrame) {
            func_80B4FD00(pthis, &gZelda2Anime1Anim_00B5FC, 0, -8.0f, 0);
            pthis->action = 35;
        }
    }
}

void func_80B51FA8(EnZl2* pthis, GlobalContext* globalCtx) {
    CsCmdActorAction* npcAction = EnZl2_GetNpcAction(globalCtx, 0);
    s32 action;
    s32 unk_240;

    if (npcAction != NULL) {
        action = npcAction->action;
        unk_240 = pthis->unk_240;
        if (action != unk_240) {
            switch (action) {
                case 1:
                    func_80B51EA8(pthis);
                    break;
                case 2:
                    func_80B51EBC(pthis, globalCtx);
                    break;
                case 14:
                    Actor_Kill(&pthis->actor);
                    break;
                default:
                    osSyncPrintf("En_Zl2_inRunning_Check_DemoMode:そんな動作は無い!!!!!!!!\n");
                    break;
            }
            pthis->unk_240 = action;
        }
    }
}

void func_80B52068(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B51FA8(pthis, globalCtx);
}

void func_80B52098(EnZl2* pthis, GlobalContext* globalCtx) {
    func_80B4FCCC(pthis, globalCtx);
    func_80B4ED2C(pthis, globalCtx);
    EnZl2_UpdateEyes(pthis);
    EnZl2_UpdateSkelAnime(pthis);
    func_80B51D24(pthis, globalCtx);
    func_80B51F38(pthis, globalCtx);
    func_80B51DA4(pthis, globalCtx);
}

void func_80B52108(EnZl2* pthis, GlobalContext* globalCtx) {
}

void func_80B52114(EnZl2* pthis, GlobalContext* globalCtx) {
    switch (pthis->actor.params) {
        case 1:
            func_80B5135C(pthis, globalCtx);
            break;
        case 4:
            func_80B51D0C(pthis, globalCtx);
            break;
        case 0:
            func_80B4FD90(pthis, globalCtx);
            break;
        default:
            osSyncPrintf(VT_FGCOL(RED) " En_Oa2 の arg_data がおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
            func_80B4FD90(pthis, globalCtx);
    }
}

void func_80B521A0(EnZl2* pthis, GlobalContext* globalCtx) {
    s32 pad;
    ObjectContext* objectCtx = &globalCtx->objectCtx;
    s32 bankIndex = Object_GetIndex(objectCtx, OBJECT_ZL2_ANIME1);
    s32 pad2;

    if (bankIndex < 0) {
        osSyncPrintf(VT_FGCOL(RED) "En_Zl2_main_bankアニメーションのバンクを読めない!!!!!!!!!!!!\n" VT_RST);
        return;
    }

    if (Object_IsLoaded(objectCtx, bankIndex)) {
        pthis->unk_274 = bankIndex;
        func_80B4FCCC(pthis, globalCtx);
        pthis->unk_278 = Animation_GetLastFrame(&gZelda2Anime1Anim_0022D0);
        func_80B52114(pthis, globalCtx);
    }
}

void EnZl2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnZl2* pthis = (EnZl2*)thisx;

    if (pthis->action < 0 || pthis->action >= 0x24 || sActionFuncs[pthis->action] == NULL) {
        osSyncPrintf(VT_FGCOL(RED) "メインモードがおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
        return;
    }
    sActionFuncs[pthis->action](pthis, globalCtx);
}

void EnZl2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnZl2* pthis = (EnZl2*)thisx;
    ActorShape* shape = &thisx->shape;
    s32 pad;

    ActorShape_Init(shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    shape->shadowAlpha = 0;
    SkelAnime_InitFlex(globalCtx, &pthis->skelAnime, &gZelda2Skel, NULL, NULL, NULL, 0);

    switch (thisx->params) {
        case 1:
            Audio_SetSoundBanksMute(0x6F);
            break;
        case 4:
            gSaveContext.timer2State = 0;
            break;
    }
}

s32 EnZl2_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                           Gfx** gfx) {
    EnZl2* pthis = (EnZl2*)thisx;

    if (pthis->overrideLimbDrawConfig < 0 || pthis->overrideLimbDrawConfig > 0 ||
        sOverrideLimbDrawFuncs[pthis->overrideLimbDrawConfig] == NULL) {
        osSyncPrintf(VT_FGCOL(RED) "描画前処理モードがおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
        return 0;
    }
    return sOverrideLimbDrawFuncs[pthis->overrideLimbDrawConfig](globalCtx, limbIndex, dList, pos, rot, thisx, gfx);
}

void func_80B523BC(EnZl2* pthis, GlobalContext* globalCtx) {
}

void func_80B523C8(EnZl2* pthis, GlobalContext* globalCtx) {
    s32 pad[3];
    s16 eyeTexIndex = pthis->eyeTexIndex;
    s16 eyeTexIndex2 = pthis->eyeTexIndex2;
    void* eyeTex = sEyeTextures[eyeTexIndex];
    void* eyeTex2 = sEyeTextures[eyeTexIndex2];
    SkelAnime* skelAnime = &pthis->skelAnime;
    s16 mouthTexIndex = pthis->mouthTexIndex;
    void* mouthTex = sMouthTextures[mouthTexIndex];
    s32 pad1;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_zl2.c", 1623);

    func_80093D18(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(eyeTex2));
    gSPSegment(POLY_OPA_DISP++, 0x0A, SEGMENTED_TO_VIRTUAL(mouthTex));
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x0B, &D_80116280[2]);

    POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                       EnZl2_OverrideLimbDraw, EnZl2_PostLimbDraw, pthis, POLY_OPA_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_zl2.c", 1648);
}

void func_80B525D4(EnZl2* pthis, GlobalContext* globalCtx) {
    s32 pad[2];
    s16 eyeTexIndex = pthis->eyeTexIndex;
    void* eyeTex = sEyeTextures[eyeTexIndex];
    s16 mouthTexIndex = pthis->mouthTexIndex;
    SkelAnime* skelAnime = &pthis->skelAnime;
    void* mouthTex = sMouthTextures[mouthTexIndex];
    s32 pad1;

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_zl2.c", 1663);

    func_80093D84(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_XLU_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_XLU_DISP++, 0x0A, SEGMENTED_TO_VIRTUAL(mouthTex));
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, pthis->alpha);
    gSPSegment(POLY_XLU_DISP++, 0x0B, &D_80116280[0]);

    POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                       EnZl2_OverrideLimbDraw, NULL, pthis, POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_zl2.c", 1692);
}

void EnZl2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnZl2* pthis = (EnZl2*)thisx;

    if ((pthis->drawConfig < 0) || (pthis->drawConfig >= 3) || (sDrawFuncs[pthis->drawConfig] == NULL)) {
        osSyncPrintf(VT_FGCOL(RED) "描画モードがおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
        return;
    }
    sDrawFuncs[pthis->drawConfig](pthis, globalCtx);
}

void EnZl2_Reset(Actor* pthisx, GlobalContext* globalCtx) {
    En_Zl2_InitVars = {
        ACTOR_EN_ZL2,
        ACTORCAT_NPC,
        FLAGS,
        OBJECT_ZL2,
        sizeof(EnZl2),
        (ActorFunc)EnZl2_Init,
        (ActorFunc)EnZl2_Destroy,
        (ActorFunc)EnZl2_Update,
        (ActorFunc)EnZl2_Draw,
        (ActorFunc)EnZl2_Reset,
    };

}
