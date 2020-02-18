#pragma once

//============================================================================
//=																			 =
//=						プリコンパイル済ヘッダーファイル					 =
//=																			 =
//============================================================================

#ifndef INCLUDEALL_H_
#define INCLUDEALL_H_

#include "main.h"

#include "lib/assimp.h"
#include "lib/WICTextureLoader.h"

#include "include/renderer.h"
#include "include/shader.h"
#include "include/audio_clip.h"

#include "include/texture.h"
#include "include/input.h"
#include "include/mesh.h"
#include "include/model.h"
#include "include/modela.h"
#include "include/model_animation.h"
#include "game_object/polygon.h"
#include "ui/number.h"
#include "ui/num_draw.h"

#include "game_status.h"

#include "game_object/game_object.h"
#include "game_object/camera.h"
#include "game_object/bill_board.h"
#include "game_object/field.h"
#include "game_object/effect.h"

#include "game_object/character/enemy.h"
#include "game_object/character/e_troop.h"
#include "game_object//character/enemy_state.h"
#include "game_object/character/enemy_state_move.h"
#include "game_object/character/enemy_state_idle.h"
#include "game_object/character/player.h"
#include "game_object/character/benemy.h"
#include "game_object/character/allies.h"

#include "game_object/mesh_field.h"
#include "game_object/skydome.h"

#include "game_object/floor.h"
#include "game_object/wall.h"
#include "game_object/goal.h"
#include "game_object/box.h"

#include "load_map.h"
#include "map.h"

#include "ui/menu.h"
#include "ui/score.h"
#include "ui/step.h"
#include "ui/num_enemy.h"
#include "ui/pull.h"
#include "ui/stage_num.h"
#include "ui/stage_clear.h"
#include "ui/help.h"
#include "ui/key_info.h"
#include "ui/return_stage_select.h"
#include "ui/return_title.h"
#include "ui/reset.h"
#include "ui/exit.h"
#include "ui/replay.h"
#include "ui/pause.h"
#include "ui/ui_manager.h"

#include "stage_manager.h"
#include "select_button.h"

#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "scene/title.h"
#include "scene/loading.h"
#include "scene/tutorial.h"
#include "scene/stage_select.h"
#include "scene/game_over.h"
#include "scene/game_clear.h"
#include "scene/game.h"
#include "scene/result.h"


#endif // !INCLUDEALL_H_

