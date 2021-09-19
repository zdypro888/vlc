/*****************************************************************************
 * vlc.h: global header for libvlc
 *****************************************************************************
 * Copyright (C) 1998-2008 VLC authors and VideoLAN
 *
 * Authors: Vincent Seguin <seguin@via.ecp.fr>
 *          Samuel Hocevar <sam@zoy.org>
 *          Gildas Bazin <gbazin@netcourrier.com>
 *          Derk-Jan Hartman <hartman at videolan dot org>
 *          Pierre d'Herbemont <pdherbemont@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef VLC_VLC_H
#define VLC_VLC_H 1

/**
 * \file
 * This file defines libvlc new external API
 */

# ifdef __cplusplus
extern "C" {
# endif

#include <vlc/libvlc.h>
#include <vlc/libvlc_renderer_discoverer.h>
#include <vlc/libvlc_picture.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>
#include <vlc/libvlc_media_list.h>
#include <vlc/libvlc_media_list_player.h>
#include <vlc/libvlc_media_discoverer.h>
#include <vlc/libvlc_events.h>
#include <vlc/libvlc_dialog.h>
#include <vlc/deprecated.h>

typedef void (*p_libvlc_media_parse)( libvlc_media_t *p_md );
typedef void (*p_libvlc_media_parse_async)( libvlc_media_t *p_md );
typedef bool (*p_libvlc_media_is_parsed)( libvlc_media_t *p_md );
typedef void (*p_libvlc_track_description_list_release)( libvlc_track_description_t *p_track_description );
typedef int (*p_libvlc_video_get_track_count)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_video_get_track)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_video_set_track)( libvlc_media_player_t *p_mi, int i_track );
typedef int (*p_libvlc_video_get_spu)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_video_get_spu_count)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_video_set_spu)( libvlc_media_player_t *p_mi, int i_spu );
typedef int (*p_libvlc_audio_get_track_count)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_audio_get_track)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_audio_set_track)( libvlc_media_player_t *p_mi, int i_track );
typedef void (*p_libvlc_playlist_play)( libvlc_instance_t *p_instance );
typedef void (*p_libvlc_clearerr )(void);
typedef void (*p_libvlc_release)( libvlc_instance_t *p_instance );
typedef void (*p_libvlc_retain)( libvlc_instance_t *p_instance );
typedef int (*p_libvlc_add_intf)( libvlc_instance_t *p_instance, const char *name );
typedef void (*p_libvlc_free)( void *ptr );
typedef void (*p_libvlc_log_unset)( libvlc_instance_t *p_instance );
typedef void (*p_libvlc_log_set_file)( libvlc_instance_t *p_instance, FILE *stream );
typedef void (*p_libvlc_module_description_list_release)( libvlc_module_description_t *p_list );
typedef int64_t (*p_libvlc_clock)(void);
typedef void (*p_libvlc_dialog_set_context)(libvlc_dialog_id *p_id, void *p_context);
typedef int (*p_libvlc_dialog_post_action)(libvlc_dialog_id *p_id, int i_action);
typedef int (*p_libvlc_dialog_dismiss)(libvlc_dialog_id *p_id);
typedef void (*p_libvlc_media_retain)( libvlc_media_t *p_md );
typedef void (*p_libvlc_media_release)( libvlc_media_t *p_md );
typedef int (*p_libvlc_media_save_meta)( libvlc_media_t *p_md );
typedef libvlc_time_t (*p_libvlc_media_get_duration)( libvlc_media_t *p_md );
typedef void (*p_libvlc_media_parse_stop)( libvlc_media_t *p_md );
typedef libvlc_media_parsed_status_t (*p_libvlc_media_get_parsed_status)( libvlc_media_t *p_md );
typedef void (*p_libvlc_media_set_user_data)( libvlc_media_t *p_md, void *p_new_user_data );
typedef libvlc_media_type_t (*p_libvlc_media_get_type)( libvlc_media_t *p_md );
typedef void (*p_libvlc_media_thumbnail_request_cancel)( libvlc_media_thumbnail_request_t *p_req );
typedef void (*p_libvlc_media_thumbnail_request_destroy)( libvlc_media_thumbnail_request_t *p_req );
typedef void (*p_libvlc_media_slaves_clear)( libvlc_media_t *p_md );
typedef int (*p_libvlc_media_discoverer_start)( libvlc_media_discoverer_t * p_mdis );
typedef void (*p_libvlc_media_discoverer_stop)( libvlc_media_discoverer_t * p_mdis );
typedef void (*p_libvlc_media_discoverer_release)( libvlc_media_discoverer_t * p_mdis );
typedef bool (*p_libvlc_media_discoverer_is_running)(libvlc_media_discoverer_t *p_mdis);
typedef void (*p_libvlc_media_list_release)( libvlc_media_list_t *p_ml );
typedef void (*p_libvlc_media_list_retain)( libvlc_media_list_t *p_ml );
typedef void (*p_libvlc_media_list_set_media)( libvlc_media_list_t *p_ml, libvlc_media_t *p_md );
typedef int (*p_libvlc_media_list_add_media)( libvlc_media_list_t *p_ml, libvlc_media_t *p_md );
typedef int (*p_libvlc_media_list_remove_index)( libvlc_media_list_t *p_ml, int i_pos );
typedef int (*p_libvlc_media_list_count)( libvlc_media_list_t *p_ml );
typedef bool (*p_libvlc_media_list_is_readonly)(libvlc_media_list_t *p_ml);
typedef void (*p_libvlc_media_list_lock)( libvlc_media_list_t *p_ml );
typedef void (*p_libvlc_media_list_unlock)( libvlc_media_list_t *p_ml );
typedef void (*p_libvlc_media_list_player_release)( libvlc_media_list_player_t * p_mlp );
typedef void (*p_libvlc_media_list_player_retain)( libvlc_media_list_player_t *p_mlp );
typedef void (*p_libvlc_media_list_player_play)(libvlc_media_list_player_t * p_mlp);
typedef void (*p_libvlc_media_list_player_pause)(libvlc_media_list_player_t * p_mlp);
typedef bool (*p_libvlc_media_list_player_is_playing)(libvlc_media_list_player_t * p_mlp);
typedef libvlc_state_t (*p_libvlc_media_list_player_get_state)( libvlc_media_list_player_t * p_mlp );
typedef void (*p_libvlc_media_list_player_stop_async)( libvlc_media_list_player_t * p_mlp);
typedef int (*p_libvlc_media_list_player_next)(libvlc_media_list_player_t * p_mlp);
typedef int (*p_libvlc_media_list_player_previous)(libvlc_media_list_player_t * p_mlp);
typedef void (*p_libvlc_media_player_release)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_retain)( libvlc_media_player_t *p_mi );
typedef bool (*p_libvlc_media_player_is_playing)(libvlc_media_player_t *p_mi);
typedef int (*p_libvlc_media_player_play )( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_pause )( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_media_player_stop_async )( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_set_nsobject )( libvlc_media_player_t *p_mi, void * drawable );
typedef uint32_t (*p_libvlc_media_player_get_xwindow )( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_set_hwnd )( libvlc_media_player_t *p_mi, void *drawable );
typedef libvlc_time_t (*p_libvlc_media_player_get_length)( libvlc_media_player_t *p_mi );
typedef libvlc_time_t (*p_libvlc_media_player_get_time)( libvlc_media_player_t *p_mi );
typedef float (*p_libvlc_media_player_get_position)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_set_chapter)( libvlc_media_player_t *p_mi, int i_chapter );
typedef int (*p_libvlc_media_player_get_chapter)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_media_player_get_chapter_count)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_set_title)( libvlc_media_player_t *p_mi, int i_title );
typedef int (*p_libvlc_media_player_get_title)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_media_player_get_title_count)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_previous_chapter)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_next_chapter)( libvlc_media_player_t *p_mi );
typedef float (*p_libvlc_media_player_get_rate)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_media_player_set_rate)( libvlc_media_player_t *p_mi, float rate );
typedef libvlc_state_t (*p_libvlc_media_player_get_state)( libvlc_media_player_t *p_mi );
typedef unsigned (*p_libvlc_media_player_has_vout)( libvlc_media_player_t *p_mi );
typedef bool (*p_libvlc_media_player_is_seekable)(libvlc_media_player_t *p_mi);
typedef bool (*p_libvlc_media_player_can_pause)(libvlc_media_player_t *p_mi);
typedef bool (*p_libvlc_media_player_program_scrambled)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_next_frame)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_media_player_set_video_title_display)( libvlc_media_player_t *p_mi, libvlc_position_t position, unsigned int timeout );
typedef void (*p_libvlc_player_program_delete)( libvlc_player_program_t *program );
typedef size_t (*p_libvlc_player_programlist_count)( const libvlc_player_programlist_t *list );
typedef void (*p_libvlc_player_programlist_delete)( libvlc_player_programlist_t *list );
typedef void (*p_libvlc_media_player_select_program_id)( libvlc_media_player_t *p_mi, int program_id);
typedef void (*p_libvlc_toggle_fullscreen)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_set_fullscreen)(libvlc_media_player_t *p_mi, bool b_fullscreen);
typedef bool (*p_libvlc_get_fullscreen)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_video_set_key_input)( libvlc_media_player_t *p_mi, unsigned on );
typedef void (*p_libvlc_video_set_mouse_input)( libvlc_media_player_t *p_mi, unsigned on );
typedef float (*p_libvlc_video_get_scale)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_video_set_scale)( libvlc_media_player_t *p_mi, float f_factor );
typedef void (*p_libvlc_video_set_aspect_ratio)( libvlc_media_player_t *p_mi, const char *psz_aspect );
typedef int64_t (*p_libvlc_video_get_spu_delay)( libvlc_media_player_t *p_mi );
typedef float (*p_libvlc_video_get_spu_text_scale)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_video_set_spu_text_scale)( libvlc_media_player_t *p_mi, float f_scale );
typedef int (*p_libvlc_video_set_spu_delay)( libvlc_media_player_t *p_mi, int64_t i_delay );
typedef int (*p_libvlc_video_get_teletext)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_video_set_teletext)( libvlc_media_player_t *p_mi, int i_page );
typedef void (*p_libvlc_audio_output_list_release)( libvlc_audio_output_t *p_list );
typedef void (*p_libvlc_audio_toggle_mute)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_audio_get_mute)( libvlc_media_player_t *p_mi );
typedef void (*p_libvlc_audio_set_mute)( libvlc_media_player_t *p_mi, int status );
typedef int (*p_libvlc_audio_get_volume)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_audio_set_volume)( libvlc_media_player_t *p_mi, int i_volume );
typedef int (*p_libvlc_audio_get_channel)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_audio_set_channel)( libvlc_media_player_t *p_mi, int channel );
typedef int64_t (*p_libvlc_audio_get_delay)( libvlc_media_player_t *p_mi );
typedef int (*p_libvlc_audio_set_delay)( libvlc_media_player_t *p_mi, int64_t i_delay );
typedef unsigned (*p_libvlc_audio_equalizer_get_preset_count)( void );
typedef unsigned (*p_libvlc_audio_equalizer_get_band_count)( void );
typedef float (*p_libvlc_audio_equalizer_get_band_frequency)( unsigned u_index );
typedef void (*p_libvlc_audio_equalizer_release)( libvlc_equalizer_t *p_equalizer );
typedef int (*p_libvlc_audio_equalizer_set_preamp)( libvlc_equalizer_t *p_equalizer, float f_preamp );
typedef float (*p_libvlc_audio_equalizer_get_preamp)( libvlc_equalizer_t *p_equalizer );
typedef int (*p_libvlc_audio_equalizer_set_amp_at_index)( libvlc_equalizer_t *p_equalizer, float f_amp, unsigned u_band );
typedef float (*p_libvlc_audio_equalizer_get_amp_at_index)( libvlc_equalizer_t *p_equalizer, unsigned u_band );
typedef int (*p_libvlc_media_player_set_equalizer)( libvlc_media_player_t *p_mi, libvlc_equalizer_t *p_equalizer );
typedef int (*p_libvlc_media_player_get_role)(libvlc_media_player_t *p_mi);
typedef size_t (*p_libvlc_media_tracklist_count)( const libvlc_media_tracklist_t *list );
typedef void (*p_libvlc_media_tracklist_delete)( libvlc_media_tracklist_t *list );
typedef void (*p_libvlc_media_track_release)( libvlc_media_track_t *track );
typedef void (*p_libvlc_picture_retain)( libvlc_picture_t* pic );
typedef void (*p_libvlc_picture_release)( libvlc_picture_t* pic );
typedef int (*p_libvlc_picture_save)( const libvlc_picture_t* pic, const char* path );
typedef libvlc_picture_type_t (*p_libvlc_picture_type)( const libvlc_picture_t* pic );
typedef libvlc_time_t (*p_libvlc_picture_get_time)( const libvlc_picture_t* pic );
typedef size_t (*p_libvlc_picture_list_count)( const libvlc_picture_list_t* list );
typedef void (*p_libvlc_picture_list_destroy)( libvlc_picture_list_t* list );
typedef void (*p_libvlc_renderer_item_release)(libvlc_renderer_item_t *p_item);
typedef int (*p_libvlc_renderer_item_flags)(const libvlc_renderer_item_t *p_item);
typedef void (*p_libvlc_renderer_discoverer_release)( libvlc_renderer_discoverer_t *p_rd );
typedef int (*p_libvlc_renderer_discoverer_start)( libvlc_renderer_discoverer_t *p_rd );
typedef void (*p_libvlc_renderer_discoverer_stop)( libvlc_renderer_discoverer_t *p_rd );

# ifdef __cplusplus
}
# endif

#endif /* _VLC_VLC_H */
