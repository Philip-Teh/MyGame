#pragma once

//============================================================================
//=																			 =
//=						プリコンパイル済ヘッダーファイル					 =
//=																			 =
//============================================================================

#ifndef INCLUDEALL_H_
#define INCLUDEALL_H_

#include "main.h"

#include "include/assimp.h"

#include "include/renderer.h"
#include "include/WICTextureLoader.h"
#include "include/audio_clip.h"

#include "include/texture.h"
#include "include/input.h"
#include "include/mesh.h"
#include "include/model.h"
#include "include/modela.h"
#include "include/model_animation.h"
#include "include/collision.h"

#include "game_object/game_object.h"

#include "game_object/character/player.h"
#include "game_object/character/enemy.h"

#include "game_object/camera.h"
#include "game_object/bill_board.h"

#include "game_object/polygon.h"
#include "game_object/field.h"
#include "game_object/mesh_field.h"
#include "game_object/mesh_wall.h"
#include "game_object/skydome.h"
#include "game_object/bullet.h"
#include "game_object/ball.h"

#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "scene/title.h"
#include "scene/game.h"
#include "scene/result.h"

#include "map.h"

#endif // !INCLUDEALL_H_

