#define INTERNAL_SRC_CODE_Z_GAME_DLFTBLS_C
#include "global.h"
#include "z64game.h"
#include "z64global.h"
#include "title_setup.h"
#include "segment_symbols.h"
#include "z_select.h"
#include "z_title.h"
#include "z_opening.h"
#include "z_file_choose.h"
#include "def/z_game_dlftbls.h"
#include "def/z_play.h" // FORCE

#define GAMESTATE_OVERLAY(name, init, destroy, size)                                                         \
    {                                                                                                        \
        NULL, (uintptr_t)_ovl_##name##SegmentRomStart, (uintptr_t)_ovl_##name##SegmentRomEnd, _ovl_##name##SegmentStart, \
            _ovl_##name##SegmentEnd, 0, init, destroy, 0, 0, 0, size                                         \
    }
#define GAMESTATE_OVERLAY_INTERNAL(init, destroy, size) \
    { NULL, 0, 0, NULL, NULL, 0, init, destroy, 0, 0, 0, size }

GameStateOverlay gGameStateOverlayTable[] = {
    GAMESTATE_OVERLAY_INTERNAL(TitleSetup_Init, TitleSetup_Destroy, sizeof(GameState)),
    GAMESTATE_OVERLAY(select, Select_Init, Select_Destroy, sizeof(SelectContext)),
    GAMESTATE_OVERLAY(title, Title_Init, Title_Destroy, sizeof(TitleContext)),
    GAMESTATE_OVERLAY_INTERNAL(Gameplay_Init, Gameplay_Destroy, sizeof(GlobalContext)),
    GAMESTATE_OVERLAY(opening, Opening_Init, Opening_Destroy, sizeof(OpeningContext)),
    GAMESTATE_OVERLAY(file_choose, FileChoose_Init, FileChoose_Destroy, sizeof(FileChooseContext)),
};
