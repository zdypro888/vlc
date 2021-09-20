#include "dynamic.h"
#include <dlfcn.h>

typedef void (*p_libvlc_video_set_crop_window)(libvlc_media_player_t *, unsigned, unsigned, unsigned, unsigned);
typedef void (*p_libvlc_media_list_retain)(libvlc_media_list_t *);
typedef void (*p_libvlc_audio_set_volume_callback)(libvlc_media_player_t *, libvlc_audio_set_volume_cb);
typedef char *(*p_libvlc_audio_equalizer_get_preset_name)(unsigned);
typedef int (*p_libvlc_media_player_set_position)(libvlc_media_player_t *, float, bool);
typedef int (*p_libvlc_media_player_get_chapter)(libvlc_media_player_t *);
typedef void (*p_libvlc_audio_toggle_mute)(libvlc_media_player_t *);
typedef libvlc_media_track_t *(*p_libvlc_media_track_hold)(libvlc_media_track_t *);
typedef void (*p_libvlc_picture_release)(libvlc_picture_t *);
typedef void (*p_libvlc_video_set_crop_ratio)(libvlc_media_player_t *, unsigned, unsigned);
typedef void (*p_libvlc_media_player_select_tracks)(libvlc_media_player_t *, libvlc_track_type_t, libvlc_media_track_t **, size_t);
typedef void (*p_libvlc_video_set_aspect_ratio)(libvlc_media_player_t *, char *);
typedef void (*p_libvlc_media_list_release)(libvlc_media_list_t *);
typedef libvlc_time_t (*p_libvlc_media_get_duration)(libvlc_media_t *);
typedef libvlc_media_t *(*p_libvlc_media_list_item_at_index)(libvlc_media_list_t *, int);
typedef void (*p_libvlc_set_exit_handler)(libvlc_instance_t *, void (*cb)(void *), void *);
typedef void (*p_libvlc_free)(void *);
typedef void (*p_libvlc_media_player_set_hwnd)(libvlc_media_player_t *, void *);
typedef void (*p_libvlc_media_parse_stop)(libvlc_media_t *);
typedef int (*p_libvlc_media_player_set_renderer)(libvlc_media_player_t *, libvlc_renderer_item_t *);
typedef int (*p_libvlc_media_list_player_play_item)(libvlc_media_list_player_t *, libvlc_media_t *);
typedef int (*p_libvlc_dialog_post_action)(libvlc_dialog_id *, int);
typedef int (*p_libvlc_media_player_get_full_title_descriptions)(libvlc_media_player_t *, libvlc_title_description_t ***);
typedef int (*p_libvlc_media_player_stop_async)(libvlc_media_player_t *);
typedef void (*p_libvlc_player_programlist_delete)(libvlc_player_programlist_t *);
typedef unsigned (*p_libvlc_audio_equalizer_get_band_count)(void);
typedef void (*p_libvlc_video_set_adjust_int)(libvlc_media_player_t *, unsigned, int);
typedef int (*p_libvlc_audio_get_track)(libvlc_media_player_t *);
typedef unsigned (*p_libvlc_audio_equalizer_get_preset_count)(void);
typedef bool (*p_libvlc_media_get_stats)(libvlc_media_t *, libvlc_media_stats_t *);
typedef void (*p_libvlc_media_set_user_data)(libvlc_media_t *, void *);
typedef void (*p_libvlc_media_player_unselect_track_type)(libvlc_media_player_t *, libvlc_track_type_t);
typedef void (*p_libvlc_media_list_player_set_playback_mode)(libvlc_media_list_player_t *, libvlc_playback_mode_t);
typedef int (*p_libvlc_audio_get_channel)(libvlc_media_player_t *);
typedef bool (*p_libvlc_media_player_can_pause)(libvlc_media_player_t *);
typedef libvlc_module_description_t *(*p_libvlc_audio_filter_list_get)(libvlc_instance_t *);
typedef char *(*p_libvlc_renderer_item_name)(libvlc_renderer_item_t *);
typedef int (*p_libvlc_audio_set_volume)(libvlc_media_player_t *, int);
typedef libvlc_time_t (*p_libvlc_media_player_get_length)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_list_player_set_media_list)(libvlc_media_list_player_t *, libvlc_media_list_t *);
typedef long (*p_libvlc_media_player_get_xwindow)(libvlc_media_player_t *);
typedef float (*p_libvlc_audio_equalizer_get_preamp)(libvlc_equalizer_t *);
typedef bool (*p_libvlc_media_is_parsed)(libvlc_media_t *);
typedef float (*p_libvlc_video_get_adjust_float)(libvlc_media_player_t *, unsigned);
typedef size_t (*p_libvlc_player_programlist_count)(libvlc_player_programlist_t *);
typedef void (*p_libvlc_media_thumbnail_request_destroy)(libvlc_media_thumbnail_request_t *);
typedef void (*p_libvlc_media_player_select_track)(libvlc_media_player_t *, libvlc_media_track_t *);
typedef int (*p_libvlc_video_set_spu_delay)(libvlc_media_player_t *, int64_t);
typedef void (*p_libvlc_media_add_option)(libvlc_media_t *, char *);
typedef char *(*p_libvlc_get_compiler)(void);
typedef libvlc_media_t *(*p_libvlc_media_duplicate)(libvlc_media_t *);
typedef void (*p_libvlc_video_set_adjust_float)(libvlc_media_player_t *, unsigned, float);
typedef int (*p_libvlc_media_player_get_title_count)(libvlc_media_player_t *);
typedef libvlc_media_t *(*p_libvlc_media_new_fd)(libvlc_instance_t *, int);
typedef char *(*p_libvlc_renderer_item_type)(libvlc_renderer_item_t *);
typedef libvlc_player_programlist_t *(*p_libvlc_media_player_get_programlist)(libvlc_media_player_t *);
typedef int (*p_libvlc_media_list_count)(libvlc_media_list_t *);
typedef size_t (*p_libvlc_media_discoverer_list_get)(libvlc_instance_t *, libvlc_media_discoverer_category_t, libvlc_media_discoverer_description_t ***);
typedef int (*p_libvlc_media_player_set_role)(libvlc_media_player_t *, unsigned);
typedef int (*p_libvlc_media_discoverer_start)(libvlc_media_discoverer_t *);
typedef int64_t (*p_libvlc_video_get_spu_delay)(libvlc_media_player_t *);
typedef void *(*p_libvlc_media_get_user_data)(libvlc_media_t *);
typedef int64_t (*p_libvlc_audio_get_delay)(libvlc_media_player_t *);
typedef void (*p_libvlc_module_description_list_release)(libvlc_module_description_t *);
typedef int (*p_libvlc_video_update_viewpoint)(libvlc_media_player_t *, libvlc_video_viewpoint_t *, bool);
typedef libvlc_track_description_t *(*p_libvlc_video_get_spu_description)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_player_set_title)(libvlc_media_player_t *, int);
typedef int (*p_libvlc_video_set_spu)(libvlc_media_player_t *, int);
typedef libvlc_picture_type_t (*p_libvlc_picture_type)(libvlc_picture_t *);
typedef int (*p_libvlc_audio_output_set)(libvlc_media_player_t *, char *);
typedef libvlc_equalizer_t *(*p_libvlc_audio_equalizer_new_from_preset)(unsigned);
typedef int (*p_libvlc_audio_set_track)(libvlc_media_player_t *, int);
typedef unsigned (*p_libvlc_media_player_has_vout)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_release)(libvlc_media_t *);
typedef void (*p_libvlc_player_program_delete)(libvlc_player_program_t *);
typedef void (*p_libvlc_audio_set_callbacks)(libvlc_media_player_t *, libvlc_audio_play_cb, libvlc_audio_pause_cb, libvlc_audio_resume_cb, libvlc_audio_flush_cb, libvlc_audio_drain_cb, void *);
typedef void (*p_libvlc_audio_set_format)(libvlc_media_player_t *, char *, unsigned, unsigned);
typedef void (*p_libvlc_media_player_select_program_id)(libvlc_media_player_t *, int);
typedef void (*p_libvlc_media_tracks_release)(libvlc_media_track_t **, unsigned);
typedef float (*p_libvlc_audio_equalizer_get_amp_at_index)(libvlc_equalizer_t *, unsigned);
typedef void (*p_libvlc_media_track_release)(libvlc_media_track_t *);
typedef bool (*p_libvlc_media_player_is_playing)(libvlc_media_player_t *);
typedef void (*p_libvlc_title_descriptions_release)(libvlc_title_description_t **, unsigned);
typedef bool (*p_libvlc_media_list_is_readonly)(libvlc_media_list_t *);
typedef void (*p_libvlc_video_set_spu_text_scale)(libvlc_media_player_t *, float);
typedef int (*p_libvlc_media_player_add_slave)(libvlc_media_player_t *, libvlc_media_slave_type_t, char *, bool);
typedef void (*p_libvlc_log_get_context)(libvlc_log_t *, char **, char **, unsigned *);
typedef void (*p_libvlc_media_player_release)(libvlc_media_player_t *);
typedef void (*p_libvlc_video_set_logo_string)(libvlc_media_player_t *, unsigned, char *);
typedef float (*p_libvlc_video_get_spu_text_scale)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_list_player_retain)(libvlc_media_list_player_t *);
typedef void (*p_libvlc_playlist_play)(libvlc_instance_t *);
typedef void (*p_libvlc_media_list_player_pause)(libvlc_media_list_player_t *);
typedef int (*p_libvlc_media_player_set_equalizer)(libvlc_media_player_t *, libvlc_equalizer_t *);
typedef int (*p_libvlc_media_list_player_play_item_at_index)(libvlc_media_list_player_t *, int);
typedef size_t (*p_libvlc_media_tracklist_count)(libvlc_media_tracklist_t *);
typedef void (*p_libvlc_video_set_callbacks)(libvlc_media_player_t *, libvlc_video_lock_cb, libvlc_video_unlock_cb, libvlc_video_display_cb, void *);
typedef int (*p_libvlc_video_get_teletext)(libvlc_media_player_t *);
typedef int (*p_libvlc_event_attach)(libvlc_event_manager_t *, libvlc_event_type_t, libvlc_callback_t, void *);
typedef size_t (*p_libvlc_renderer_discoverer_list_get)(libvlc_instance_t *, libvlc_rd_description_t ***);
typedef void (*p_libvlc_media_player_set_pause)(libvlc_media_player_t *, int);
typedef void (*p_libvlc_media_list_player_stop_async)(libvlc_media_list_player_t *);
typedef libvlc_video_viewpoint_t *(*p_libvlc_video_new_viewpoint)(void);
typedef bool (*p_libvlc_video_set_output_callbacks)(libvlc_media_player_t *, libvlc_video_engine_t, libvlc_video_output_setup_cb, libvlc_video_output_cleanup_cb, libvlc_video_output_set_resize_cb, libvlc_video_update_output_cb, libvlc_video_swap_cb, libvlc_video_makeCurrent_cb, libvlc_video_getProcAddress_cb, libvlc_video_frameMetadata_cb, libvlc_video_output_select_plane_cb, void *);
typedef libvlc_media_t *(*p_libvlc_media_new_path)(libvlc_instance_t *, char *);
typedef void (*p_libvlc_media_player_select_tracks_by_ids)(libvlc_media_player_t *, libvlc_track_type_t, char *);
typedef void (*p_libvlc_media_add_option_flag)(libvlc_media_t *, char *, unsigned);
typedef void (*p_libvlc_media_player_set_xwindow)(libvlc_media_player_t *, long);
typedef int (*p_libvlc_audio_set_channel)(libvlc_media_player_t *, int);
typedef int (*p_libvlc_media_player_get_role)(libvlc_media_player_t *);
typedef int (*p_libvlc_media_list_add_media)(libvlc_media_list_t *, libvlc_media_t *);
typedef void (*p_libvlc_media_list_lock)(libvlc_media_list_t *);
typedef void (*p_libvlc_media_slaves_clear)(libvlc_media_t *);
typedef int (*p_libvlc_media_player_get_chapter_count_for_title)(libvlc_media_player_t *, int);
typedef void (*p_libvlc_log_unset)(libvlc_instance_t *);
typedef int (*p_libvlc_video_get_track)(libvlc_media_player_t *);
typedef int64_t (*p_libvlc_clock)(void);
typedef int (*p_libvlc_renderer_discoverer_start)(libvlc_renderer_discoverer_t *);
typedef int (*p_libvlc_video_get_spu)(libvlc_media_player_t *);
typedef void (*p_libvlc_set_user_agent)(libvlc_instance_t *, char *, char *);
typedef void (*p_libvlc_log_set_file)(libvlc_instance_t *, FILE *);
typedef void (*p_libvlc_media_tracklist_delete)(libvlc_media_tracklist_t *);
typedef void (*p_libvlc_media_discoverer_stop)(libvlc_media_discoverer_t *);
typedef void (*p_libvlc_video_set_mouse_input)(libvlc_media_player_t *, unsigned);
typedef libvlc_event_manager_t *(*p_libvlc_media_list_event_manager)(libvlc_media_list_t *);
typedef void (*p_libvlc_log_get_object)(libvlc_log_t *, char **, char **, uintptr_t *);
typedef libvlc_event_manager_t *(*p_libvlc_media_event_manager)(libvlc_media_t *);
typedef libvlc_media_parsed_status_t (*p_libvlc_media_get_parsed_status)(libvlc_media_t *);
typedef int (*p_libvlc_video_get_cursor)(libvlc_media_player_t *, unsigned, int *, int *);
typedef char *(*p_libvlc_video_get_aspect_ratio)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_set_meta)(libvlc_media_t *, libvlc_meta_t, char *);
typedef float (*p_libvlc_media_player_get_position)(libvlc_media_player_t *);
typedef libvlc_media_list_t *(*p_libvlc_media_list_new)(void);
typedef void (*p_libvlc_toggle_fullscreen)(libvlc_media_player_t *);
typedef libvlc_module_description_t *(*p_libvlc_video_filter_list_get)(libvlc_instance_t *);
typedef char *(*p_libvlc_vprinterr)(char *, void *);
typedef void (*p_libvlc_media_player_navigate)(libvlc_media_player_t *, unsigned);
typedef int (*p_libvlc_dialog_post_login)(libvlc_dialog_id *, char *, char *, bool);
typedef void (*p_libvlc_audio_equalizer_release)(libvlc_equalizer_t *);
typedef void (*p_libvlc_video_set_key_input)(libvlc_media_player_t *, unsigned);
typedef void (*p_libvlc_video_set_scale)(libvlc_media_player_t *, float);
typedef void (*p_libvlc_set_fullscreen)(libvlc_media_player_t *, bool);
typedef float (*p_libvlc_video_get_scale)(libvlc_media_player_t *);
typedef libvlc_event_manager_t *(*p_libvlc_media_list_player_event_manager)(libvlc_media_list_player_t *);
typedef bool (*p_libvlc_media_list_player_is_playing)(libvlc_media_list_player_t *);
typedef bool (*p_libvlc_media_player_program_scrambled)(libvlc_media_player_t *);
typedef libvlc_audio_output_device_t *(*p_libvlc_audio_output_device_list_get)(libvlc_instance_t *, char *);
typedef float (*p_libvlc_media_player_get_rate)(libvlc_media_player_t *);
typedef int (*p_libvlc_video_take_snapshot)(libvlc_media_player_t *, unsigned, char *, unsigned, unsigned);
typedef int (*p_libvlc_media_list_index_of_item)(libvlc_media_list_t *, libvlc_media_t *);
typedef int (*p_libvlc_video_set_track)(libvlc_media_player_t *, int);
typedef char *(*p_libvlc_renderer_item_icon_uri)(libvlc_renderer_item_t *);
typedef size_t (*p_libvlc_picture_list_count)(libvlc_picture_list_t *);
typedef int (*p_libvlc_media_player_set_time)(libvlc_media_player_t *, libvlc_time_t, bool);
typedef void (*p_libvlc_audio_output_device_list_release)(libvlc_audio_output_device_t *);
typedef void *(*p_libvlc_media_player_get_hwnd)(libvlc_media_player_t *);
typedef bool (*p_libvlc_media_player_is_seekable)(libvlc_media_player_t *);
typedef void (*p_libvlc_video_set_teletext)(libvlc_media_player_t *, int);
typedef void (*p_libvlc_video_set_marquee_int)(libvlc_media_player_t *, unsigned, int);
typedef char *(*p_libvlc_audio_output_device_get)(libvlc_media_player_t *);
typedef libvlc_media_player_t *(*p_libvlc_media_list_player_get_media_player)(libvlc_media_list_player_t *);
typedef int (*p_libvlc_video_get_adjust_int)(libvlc_media_player_t *, unsigned);
typedef libvlc_media_track_t *(*p_libvlc_media_player_get_track_from_id)(libvlc_media_player_t *, char *);
typedef int (*p_libvlc_audio_equalizer_set_preamp)(libvlc_equalizer_t *, float);
typedef void (*p_libvlc_retain)(libvlc_instance_t *);
typedef libvlc_media_tracklist_t *(*p_libvlc_media_get_tracklist)(libvlc_media_t *, libvlc_track_type_t);
typedef void (*p_libvlc_chapter_descriptions_release)(libvlc_chapter_description_t **, unsigned);
typedef int (*p_libvlc_video_get_spu_count)(libvlc_media_player_t *);
typedef libvlc_equalizer_t *(*p_libvlc_audio_equalizer_new)(void);
typedef void (*p_libvlc_picture_list_destroy)(libvlc_picture_list_t *);
typedef libvlc_media_list_t *(*p_libvlc_media_discoverer_media_list)(libvlc_media_discoverer_t *);
typedef void (*p_libvlc_media_discoverer_list_release)(libvlc_media_discoverer_description_t **, size_t);
typedef void (*p_libvlc_audio_set_mute)(libvlc_media_player_t *, int);
typedef int (*p_libvlc_audio_equalizer_set_amp_at_index)(libvlc_equalizer_t *, float, unsigned);
typedef libvlc_state_t (*p_libvlc_media_player_get_state)(libvlc_media_player_t *);
typedef int (*p_libvlc_audio_get_track_count)(libvlc_media_player_t *);
typedef void *(*p_libvlc_media_player_get_nsobject)(libvlc_media_player_t *);
typedef libvlc_media_track_t *(*p_libvlc_media_player_get_selected_track)(libvlc_media_player_t *, libvlc_track_type_t);
typedef libvlc_media_tracklist_t *(*p_libvlc_media_player_get_tracklist)(libvlc_media_player_t *, libvlc_track_type_t);
typedef void (*p_libvlc_video_set_logo_int)(libvlc_media_player_t *, unsigned, int);
typedef void (*p_libvlc_renderer_discoverer_stop)(libvlc_renderer_discoverer_t *);
typedef void (*p_libvlc_media_parse)(libvlc_media_t *);
typedef libvlc_instance_t *(*p_libvlc_new)(int, char **);
typedef libvlc_state_t (*p_libvlc_media_list_player_get_state)(libvlc_media_list_player_t *);
typedef libvlc_event_manager_t *(*p_libvlc_media_player_event_manager)(libvlc_media_player_t *);
typedef float (*p_libvlc_audio_equalizer_get_band_frequency)(unsigned);
typedef char *(*p_libvlc_media_get_mrl)(libvlc_media_t *);
typedef int (*p_libvlc_video_get_marquee_int)(libvlc_media_player_t *, unsigned);
typedef void (*p_libvlc_track_description_list_release)(libvlc_track_description_t *);
typedef libvlc_media_track_t *(*p_libvlc_media_tracklist_at)(libvlc_media_tracklist_t *, size_t);
typedef void (*p_libvlc_clearerr)(void);
typedef void (*p_libvlc_audio_output_list_release)(libvlc_audio_output_t *);
typedef unsigned (*p_libvlc_picture_get_stride)(libvlc_picture_t *);
typedef void (*p_libvlc_release)(libvlc_instance_t *);
typedef libvlc_media_thumbnail_request_t *(*p_libvlc_media_thumbnail_request_by_time)(libvlc_media_t *, libvlc_time_t, libvlc_thumbnailer_seek_speed_t, unsigned, unsigned, bool, libvlc_picture_type_t, libvlc_time_t);
typedef libvlc_track_description_t *(*p_libvlc_video_get_track_description)(libvlc_media_player_t *);
typedef int (*p_libvlc_media_list_insert_media)(libvlc_media_list_t *, libvlc_media_t *, int);
typedef void (*p_libvlc_dialog_set_context)(libvlc_dialog_id *, void *);
typedef void (*p_libvlc_log_set)(libvlc_instance_t *, libvlc_log_cb, void *);
typedef void (*p_libvlc_video_set_format)(libvlc_media_player_t *, char *, unsigned, unsigned, unsigned);
typedef int (*p_libvlc_add_intf)(libvlc_instance_t *, char *);
typedef libvlc_media_t *(*p_libvlc_media_new_callbacks)(libvlc_instance_t *, libvlc_media_open_cb, libvlc_media_read_cb, libvlc_media_seek_cb, libvlc_media_close_cb, void *);
typedef void (*p_libvlc_media_list_unlock)(libvlc_media_list_t *);
typedef int (*p_libvlc_media_player_get_full_chapter_descriptions)(libvlc_media_player_t *, int, libvlc_chapter_description_t ***);
typedef int (*p_libvlc_audio_get_mute)(libvlc_media_player_t *);
typedef char *(*p_libvlc_printerr)(char *);
typedef libvlc_media_player_t *(*p_libvlc_media_player_new)(libvlc_instance_t *);
typedef void (*p_libvlc_media_player_set_video_title_display)(libvlc_media_player_t *, libvlc_position_t, unsigned);
typedef char *(*p_libvlc_media_get_codec_description)(libvlc_track_type_t, long);
typedef int (*p_libvlc_media_player_set_rate)(libvlc_media_player_t *, float);
typedef void (*p_libvlc_video_set_deinterlace)(libvlc_media_player_t *, int, char *);
typedef void (*p_libvlc_media_player_pause)(libvlc_media_player_t *);
typedef libvlc_audio_output_t *(*p_libvlc_audio_output_list_get)(libvlc_instance_t *);
typedef libvlc_state_t (*p_libvlc_media_get_state)(libvlc_media_t *);
typedef void (*p_libvlc_audio_set_format_callbacks)(libvlc_media_player_t *, libvlc_audio_setup_cb, libvlc_audio_cleanup_cb);
typedef libvlc_media_discoverer_t *(*p_libvlc_media_discoverer_new)(libvlc_instance_t *, char *);
typedef libvlc_event_manager_t *(*p_libvlc_renderer_discoverer_event_manager)(libvlc_renderer_discoverer_t *);
typedef void (*p_libvlc_media_slaves_release)(libvlc_media_slave_t **, unsigned);
typedef libvlc_media_t *(*p_libvlc_media_new_location)(libvlc_instance_t *, char *);
typedef void (*p_libvlc_media_list_set_media)(libvlc_media_list_t *, libvlc_media_t *);
typedef libvlc_media_t *(*p_libvlc_media_list_media)(libvlc_media_list_t *);
typedef unsigned (*p_libvlc_media_tracks_get)(libvlc_media_t *, libvlc_media_track_t ***);
typedef void (*p_libvlc_media_parse_async)(libvlc_media_t *);
typedef void (*p_libvlc_event_detach)(libvlc_event_manager_t *, libvlc_event_type_t, libvlc_callback_t, void *);
typedef int (*p_libvlc_video_get_size)(libvlc_media_player_t *, unsigned, unsigned *, unsigned *);
typedef bool (*p_libvlc_media_discoverer_is_running)(libvlc_media_discoverer_t *);
typedef void (*p_libvlc_renderer_item_release)(libvlc_renderer_item_t *);
typedef libvlc_player_program_t *(*p_libvlc_player_programlist_at)(libvlc_player_programlist_t *, size_t);
typedef int (*p_libvlc_dialog_dismiss)(libvlc_dialog_id *);
typedef int64_t (*p_libvlc_delay)(int64_t);
typedef libvlc_picture_t *(*p_libvlc_picture_list_at)(libvlc_picture_list_t *, size_t);
typedef void (*p_libvlc_media_retain)(libvlc_media_t *);
typedef int (*p_libvlc_media_player_get_title)(libvlc_media_player_t *);
typedef char *(*p_libvlc_media_get_meta)(libvlc_media_t *, libvlc_meta_t);
typedef int (*p_libvlc_media_list_player_next)(libvlc_media_list_player_t *);
typedef libvlc_media_t *(*p_libvlc_media_new_as_node)(libvlc_instance_t *, char *);
typedef void (*p_libvlc_media_list_player_release)(libvlc_media_list_player_t *);
typedef void (*p_libvlc_media_list_player_play)(libvlc_media_list_player_t *);
typedef void (*p_libvlc_media_player_next_frame)(libvlc_media_player_t *);
typedef unsigned (*p_libvlc_picture_get_width)(libvlc_picture_t *);
typedef libvlc_media_thumbnail_request_t *(*p_libvlc_media_thumbnail_request_by_pos)(libvlc_media_t *, float, libvlc_thumbnailer_seek_speed_t, unsigned, unsigned, bool, libvlc_picture_type_t, libvlc_time_t);
typedef libvlc_player_program_t *(*p_libvlc_media_player_get_selected_program)(libvlc_media_player_t *);
typedef int (*p_libvlc_media_list_player_previous)(libvlc_media_list_player_t *);
typedef void (*p_libvlc_media_player_set_nsobject)(libvlc_media_player_t *, void *);
typedef int (*p_libvlc_media_save_meta)(libvlc_media_t *);
typedef libvlc_media_player_t *(*p_libvlc_media_player_new_from_media)(libvlc_media_t *);
typedef int (*p_libvlc_media_player_get_chapter_count)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_player_next_chapter)(libvlc_media_player_t *);
typedef libvlc_track_description_t *(*p_libvlc_audio_get_track_description)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_list_player_set_pause)(libvlc_media_list_player_t *, int);
typedef void (*p_libvlc_dialog_set_callbacks)(libvlc_instance_t *, libvlc_dialog_cbs *, void *);
typedef void (*p_libvlc_media_player_set_media)(libvlc_media_player_t *, libvlc_media_t *);
typedef void *(*p_libvlc_dialog_get_context)(libvlc_dialog_id *);
typedef char *(*p_libvlc_get_version)(void);
typedef int (*p_libvlc_media_slaves_add)(libvlc_media_t *, libvlc_media_slave_type_t, unsigned, char *);
typedef char *(*p_libvlc_errmsg)(void);
typedef int (*p_libvlc_audio_get_volume)(libvlc_media_player_t *);
typedef void (*p_libvlc_renderer_discoverer_list_release)(libvlc_rd_description_t **, size_t);
typedef libvlc_media_t *(*p_libvlc_media_player_get_media)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_player_set_android_context)(libvlc_media_player_t *, void *);
typedef void (*p_libvlc_media_player_set_chapter)(libvlc_media_player_t *, int);
typedef int (*p_libvlc_media_list_remove_index)(libvlc_media_list_t *, int);
typedef libvlc_player_program_t *(*p_libvlc_media_player_get_program_from_id)(libvlc_media_player_t *, int);
typedef unsigned (*p_libvlc_picture_get_height)(libvlc_picture_t *);
typedef void (*p_libvlc_video_set_crop_border)(libvlc_media_player_t *, unsigned, unsigned, unsigned, unsigned);
typedef int (*p_libvlc_media_parse_with_options)(libvlc_media_t *, libvlc_media_parse_flag_t, int);
typedef void (*p_libvlc_media_player_retain)(libvlc_media_player_t *);
typedef int (*p_libvlc_video_get_track_count)(libvlc_media_player_t *);
typedef libvlc_media_type_t (*p_libvlc_media_get_type)(libvlc_media_t *);
typedef libvlc_audio_output_device_t *(*p_libvlc_audio_output_device_enum)(libvlc_media_player_t *);
typedef void (*p_libvlc_video_set_marquee_string)(libvlc_media_player_t *, unsigned, char *);
typedef void (*p_libvlc_audio_output_device_set)(libvlc_media_player_t *, char *, char *);
typedef int (*p_libvlc_picture_save)(libvlc_picture_t *, char *);
typedef void (*p_libvlc_set_app_id)(libvlc_instance_t *, char *, char *, char *);
typedef int (*p_libvlc_renderer_item_flags)(libvlc_renderer_item_t *);
typedef libvlc_renderer_discoverer_t *(*p_libvlc_renderer_discoverer_new)(libvlc_instance_t *, char *);
typedef void (*p_libvlc_picture_retain)(libvlc_picture_t *);
typedef libvlc_renderer_item_t *(*p_libvlc_renderer_item_hold)(libvlc_renderer_item_t *);
typedef int (*p_libvlc_video_get_logo_int)(libvlc_media_player_t *, unsigned);
typedef void (*p_libvlc_video_set_format_callbacks)(libvlc_media_player_t *, libvlc_video_format_cb, libvlc_video_cleanup_cb);
typedef void (*p_libvlc_media_player_previous_chapter)(libvlc_media_player_t *);
typedef bool (*p_libvlc_get_fullscreen)(libvlc_media_player_t *);
typedef libvlc_time_t (*p_libvlc_picture_get_time)(libvlc_picture_t *);
typedef int (*p_libvlc_media_player_play)(libvlc_media_player_t *);
typedef void (*p_libvlc_media_discoverer_release)(libvlc_media_discoverer_t *);
typedef int (*p_libvlc_audio_set_delay)(libvlc_media_player_t *, int64_t);
typedef void (*p_libvlc_media_thumbnail_request_cancel)(libvlc_media_thumbnail_request_t *);
typedef struct libvlc_media_list_t *(*p_libvlc_media_subitems)(libvlc_media_t *);
typedef libvlc_time_t (*p_libvlc_media_player_get_time)(libvlc_media_player_t *);
typedef unsigned (*p_libvlc_media_slaves_get)(libvlc_media_t *, libvlc_media_slave_t ***);
typedef libvlc_media_list_player_t *(*p_libvlc_media_list_player_new)(libvlc_instance_t *);
typedef void (*p_libvlc_media_list_player_set_media_player)(libvlc_media_list_player_t *, libvlc_media_player_t *);
typedef char *(*p_libvlc_get_changeset)(void);
typedef unsigned char *(*p_libvlc_picture_get_buffer)(libvlc_picture_t *, size_t *);
typedef void (*p_libvlc_renderer_discoverer_release)(libvlc_renderer_discoverer_t *);

p_libvlc_video_set_crop_border _libvlc_video_set_crop_border;
void dynamic_libvlc_video_set_crop_border(libvlc_media_player_t *mp, unsigned left, unsigned right, unsigned top, unsigned bottom)
{
    return _libvlc_video_set_crop_border(mp, left, right, top, bottom);
}
p_libvlc_media_player_new _libvlc_media_player_new;
libvlc_media_player_t *dynamic_libvlc_media_player_new(libvlc_instance_t *p_libvlc_instance)
{
    return _libvlc_media_player_new(p_libvlc_instance);
}
p_libvlc_dialog_set_callbacks _libvlc_dialog_set_callbacks;
void dynamic_libvlc_dialog_set_callbacks(libvlc_instance_t *p_instance, libvlc_dialog_cbs *p_cbs, void *p_data)
{
    return _libvlc_dialog_set_callbacks(p_instance, p_cbs, p_data);
}
p_libvlc_media_list_set_media _libvlc_media_list_set_media;
void dynamic_libvlc_media_list_set_media(libvlc_media_list_t *p_ml, libvlc_media_t *p_md)
{
    return _libvlc_media_list_set_media(p_ml, p_md);
}
p_libvlc_media_player_select_tracks_by_ids _libvlc_media_player_select_tracks_by_ids;
void dynamic_libvlc_media_player_select_tracks_by_ids(libvlc_media_player_t *p_mi, libvlc_track_type_t type, char *psz_ids)
{
    return _libvlc_media_player_select_tracks_by_ids(p_mi, type, psz_ids);
}
p_libvlc_video_set_marquee_int _libvlc_video_set_marquee_int;
void dynamic_libvlc_video_set_marquee_int(libvlc_media_player_t *p_mi, unsigned option, int i_val)
{
    return _libvlc_video_set_marquee_int(p_mi, option, i_val);
}
p_libvlc_video_set_adjust_float _libvlc_video_set_adjust_float;
void dynamic_libvlc_video_set_adjust_float(libvlc_media_player_t *p_mi, unsigned option, float value)
{
    return _libvlc_video_set_adjust_float(p_mi, option, value);
}
p_libvlc_video_filter_list_get _libvlc_video_filter_list_get;
libvlc_module_description_t *dynamic_libvlc_video_filter_list_get(libvlc_instance_t *p_instance)
{
    return _libvlc_video_filter_list_get(p_instance);
}
p_libvlc_media_player_set_role _libvlc_media_player_set_role;
int dynamic_libvlc_media_player_set_role(libvlc_media_player_t *p_mi, unsigned role)
{
    return _libvlc_media_player_set_role(p_mi, role);
}
p_libvlc_media_list_retain _libvlc_media_list_retain;
void dynamic_libvlc_media_list_retain(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_retain(p_ml);
}
p_libvlc_media_player_unselect_track_type _libvlc_media_player_unselect_track_type;
void dynamic_libvlc_media_player_unselect_track_type(libvlc_media_player_t *p_mi, libvlc_track_type_t type)
{
    return _libvlc_media_player_unselect_track_type(p_mi, type);
}
p_libvlc_video_set_teletext _libvlc_video_set_teletext;
void dynamic_libvlc_video_set_teletext(libvlc_media_player_t *p_mi, int i_page)
{
    return _libvlc_video_set_teletext(p_mi, i_page);
}
p_libvlc_video_set_logo_int _libvlc_video_set_logo_int;
void dynamic_libvlc_video_set_logo_int(libvlc_media_player_t *p_mi, unsigned option, int value)
{
    return _libvlc_video_set_logo_int(p_mi, option, value);
}
p_libvlc_audio_get_delay _libvlc_audio_get_delay;
int64_t dynamic_libvlc_audio_get_delay(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_delay(p_mi);
}
p_libvlc_media_get_codec_description _libvlc_media_get_codec_description;
char *dynamic_libvlc_media_get_codec_description(libvlc_track_type_t i_type, long i_codec)
{
    return _libvlc_media_get_codec_description(i_type, i_codec);
}
p_libvlc_media_player_set_video_title_display _libvlc_media_player_set_video_title_display;
void dynamic_libvlc_media_player_set_video_title_display(libvlc_media_player_t *p_mi, libvlc_position_t position, unsigned timeout)
{
    return _libvlc_media_player_set_video_title_display(p_mi, position, timeout);
}
p_libvlc_audio_set_mute _libvlc_audio_set_mute;
void dynamic_libvlc_audio_set_mute(libvlc_media_player_t *p_mi, int status)
{
    return _libvlc_audio_set_mute(p_mi, status);
}
p_libvlc_media_player_get_full_chapter_descriptions _libvlc_media_player_get_full_chapter_descriptions;
int dynamic_libvlc_media_player_get_full_chapter_descriptions(libvlc_media_player_t *p_mi, int i_chapters_of_title, libvlc_chapter_description_t ***pp_chapters)
{
    return _libvlc_media_player_get_full_chapter_descriptions(p_mi, i_chapters_of_title, pp_chapters);
}
p_libvlc_video_get_spu_text_scale _libvlc_video_get_spu_text_scale;
float dynamic_libvlc_video_get_spu_text_scale(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_spu_text_scale(p_mi);
}
p_libvlc_media_player_set_xwindow _libvlc_media_player_set_xwindow;
void dynamic_libvlc_media_player_set_xwindow(libvlc_media_player_t *p_mi, long drawable)
{
    return _libvlc_media_player_set_xwindow(p_mi, drawable);
}
p_libvlc_video_set_key_input _libvlc_video_set_key_input;
void dynamic_libvlc_video_set_key_input(libvlc_media_player_t *p_mi, unsigned on)
{
    return _libvlc_video_set_key_input(p_mi, on);
}
p_libvlc_log_set _libvlc_log_set;
void dynamic_libvlc_log_set(libvlc_instance_t *p_instance, libvlc_log_cb cb, void *data)
{
    return _libvlc_log_set(p_instance, cb, data);
}
p_libvlc_media_get_mrl _libvlc_media_get_mrl;
char *dynamic_libvlc_media_get_mrl(libvlc_media_t *p_md)
{
    return _libvlc_media_get_mrl(p_md);
}
p_libvlc_media_player_next_chapter _libvlc_media_player_next_chapter;
void dynamic_libvlc_media_player_next_chapter(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_next_chapter(p_mi);
}
p_libvlc_media_list_player_set_media_player _libvlc_media_list_player_set_media_player;
void dynamic_libvlc_media_list_player_set_media_player(libvlc_media_list_player_t *p_mlp, libvlc_media_player_t *p_mi)
{
    return _libvlc_media_list_player_set_media_player(p_mlp, p_mi);
}
p_libvlc_toggle_fullscreen _libvlc_toggle_fullscreen;
void dynamic_libvlc_toggle_fullscreen(libvlc_media_player_t *p_mi)
{
    return _libvlc_toggle_fullscreen(p_mi);
}
p_libvlc_video_set_aspect_ratio _libvlc_video_set_aspect_ratio;
void dynamic_libvlc_video_set_aspect_ratio(libvlc_media_player_t *p_mi, char *psz_aspect)
{
    return _libvlc_video_set_aspect_ratio(p_mi, psz_aspect);
}
p_libvlc_media_player_set_media _libvlc_media_player_set_media;
void dynamic_libvlc_media_player_set_media(libvlc_media_player_t *p_mi, libvlc_media_t *p_md)
{
    return _libvlc_media_player_set_media(p_mi, p_md);
}
p_libvlc_media_player_program_scrambled _libvlc_media_player_program_scrambled;
bool dynamic_libvlc_media_player_program_scrambled(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_program_scrambled(p_mi);
}
p_libvlc_media_player_get_title_count _libvlc_media_player_get_title_count;
int dynamic_libvlc_media_player_get_title_count(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_title_count(p_mi);
}
p_libvlc_media_player_play _libvlc_media_player_play;
int dynamic_libvlc_media_player_play(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_play(p_mi);
}
p_libvlc_media_player_next_frame _libvlc_media_player_next_frame;
void dynamic_libvlc_media_player_next_frame(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_next_frame(p_mi);
}
p_libvlc_media_player_navigate _libvlc_media_player_navigate;
void dynamic_libvlc_media_player_navigate(libvlc_media_player_t *p_mi, unsigned navigate)
{
    return _libvlc_media_player_navigate(p_mi, navigate);
}
p_libvlc_media_player_get_media _libvlc_media_player_get_media;
libvlc_media_t *dynamic_libvlc_media_player_get_media(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_media(p_mi);
}
p_libvlc_chapter_descriptions_release _libvlc_chapter_descriptions_release;
void dynamic_libvlc_chapter_descriptions_release(libvlc_chapter_description_t **p_chapters, unsigned i_count)
{
    return _libvlc_chapter_descriptions_release(p_chapters, i_count);
}
p_libvlc_media_player_get_rate _libvlc_media_player_get_rate;
float dynamic_libvlc_media_player_get_rate(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_rate(p_mi);
}
p_libvlc_video_set_scale _libvlc_video_set_scale;
void dynamic_libvlc_video_set_scale(libvlc_media_player_t *p_mi, float f_factor)
{
    return _libvlc_video_set_scale(p_mi, f_factor);
}
p_libvlc_audio_set_channel _libvlc_audio_set_channel;
int dynamic_libvlc_audio_set_channel(libvlc_media_player_t *p_mi, int channel)
{
    return _libvlc_audio_set_channel(p_mi, channel);
}
p_libvlc_media_list_player_set_media_list _libvlc_media_list_player_set_media_list;
void dynamic_libvlc_media_list_player_set_media_list(libvlc_media_list_player_t *p_mlp, libvlc_media_list_t *p_mlist)
{
    return _libvlc_media_list_player_set_media_list(p_mlp, p_mlist);
}
p_libvlc_media_player_select_program_id _libvlc_media_player_select_program_id;
void dynamic_libvlc_media_player_select_program_id(libvlc_media_player_t *p_mi, int program_id)
{
    return _libvlc_media_player_select_program_id(p_mi, program_id);
}
p_libvlc_audio_get_mute _libvlc_audio_get_mute;
int dynamic_libvlc_audio_get_mute(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_mute(p_mi);
}
p_libvlc_media_is_parsed _libvlc_media_is_parsed;
bool dynamic_libvlc_media_is_parsed(libvlc_media_t *p_md)
{
    return _libvlc_media_is_parsed(p_md);
}
p_libvlc_audio_equalizer_get_preamp _libvlc_audio_equalizer_get_preamp;
float dynamic_libvlc_audio_equalizer_get_preamp(libvlc_equalizer_t *p_equalizer)
{
    return _libvlc_audio_equalizer_get_preamp(p_equalizer);
}
p_libvlc_video_get_marquee_int _libvlc_video_get_marquee_int;
int dynamic_libvlc_video_get_marquee_int(libvlc_media_player_t *p_mi, unsigned option)
{
    return _libvlc_video_get_marquee_int(p_mi, option);
}
p_libvlc_audio_get_track _libvlc_audio_get_track;
int dynamic_libvlc_audio_get_track(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_track(p_mi);
}
p_libvlc_media_tracklist_delete _libvlc_media_tracklist_delete;
void dynamic_libvlc_media_tracklist_delete(libvlc_media_tracklist_t *list)
{
    return _libvlc_media_tracklist_delete(list);
}
p_libvlc_media_player_set_pause _libvlc_media_player_set_pause;
void dynamic_libvlc_media_player_set_pause(libvlc_media_player_t *mp, int do_pause)
{
    return _libvlc_media_player_set_pause(mp, do_pause);
}
p_libvlc_module_description_list_release _libvlc_module_description_list_release;
void dynamic_libvlc_module_description_list_release(libvlc_module_description_t *p_list)
{
    return _libvlc_module_description_list_release(p_list);
}
p_libvlc_retain _libvlc_retain;
void dynamic_libvlc_retain(libvlc_instance_t *p_instance)
{
    return _libvlc_retain(p_instance);
}
p_libvlc_media_player_new_from_media _libvlc_media_player_new_from_media;
libvlc_media_player_t *dynamic_libvlc_media_player_new_from_media(libvlc_media_t *p_md)
{
    return _libvlc_media_player_new_from_media(p_md);
}
p_libvlc_video_get_aspect_ratio _libvlc_video_get_aspect_ratio;
char *dynamic_libvlc_video_get_aspect_ratio(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_aspect_ratio(p_mi);
}
p_libvlc_media_tracklist_count _libvlc_media_tracklist_count;
size_t dynamic_libvlc_media_tracklist_count(libvlc_media_tracklist_t *list)
{
    return _libvlc_media_tracklist_count(list);
}
p_libvlc_event_detach _libvlc_event_detach;
void dynamic_libvlc_event_detach(libvlc_event_manager_t *p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void *p_user_data)
{
    return _libvlc_event_detach(p_event_manager, i_event_type, f_callback, p_user_data);
}
p_libvlc_clearerr _libvlc_clearerr;
void dynamic_libvlc_clearerr(void)
{
    return _libvlc_clearerr();
}
p_libvlc_renderer_item_release _libvlc_renderer_item_release;
void dynamic_libvlc_renderer_item_release(libvlc_renderer_item_t *p_item)
{
    return _libvlc_renderer_item_release(p_item);
}
p_libvlc_media_list_add_media _libvlc_media_list_add_media;
int dynamic_libvlc_media_list_add_media(libvlc_media_list_t *p_ml, libvlc_media_t *p_md)
{
    return _libvlc_media_list_add_media(p_ml, p_md);
}
p_libvlc_set_fullscreen _libvlc_set_fullscreen;
void dynamic_libvlc_set_fullscreen(libvlc_media_player_t *p_mi, bool b_fullscreen)
{
    return _libvlc_set_fullscreen(p_mi, b_fullscreen);
}
p_libvlc_media_thumbnail_request_cancel _libvlc_media_thumbnail_request_cancel;
void dynamic_libvlc_media_thumbnail_request_cancel(libvlc_media_thumbnail_request_t *p_req)
{
    return _libvlc_media_thumbnail_request_cancel(p_req);
}
p_libvlc_renderer_discoverer_event_manager _libvlc_renderer_discoverer_event_manager;
libvlc_event_manager_t *dynamic_libvlc_renderer_discoverer_event_manager(libvlc_renderer_discoverer_t *p_rd)
{
    return _libvlc_renderer_discoverer_event_manager(p_rd);
}
p_libvlc_audio_equalizer_new_from_preset _libvlc_audio_equalizer_new_from_preset;
libvlc_equalizer_t *dynamic_libvlc_audio_equalizer_new_from_preset(unsigned u_index)
{
    return _libvlc_audio_equalizer_new_from_preset(u_index);
}
p_libvlc_media_player_get_title _libvlc_media_player_get_title;
int dynamic_libvlc_media_player_get_title(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_title(p_mi);
}
p_libvlc_player_programlist_at _libvlc_player_programlist_at;
libvlc_player_program_t *dynamic_libvlc_player_programlist_at(libvlc_player_programlist_t *list, size_t index)
{
    return _libvlc_player_programlist_at(list, index);
}
p_libvlc_media_retain _libvlc_media_retain;
void dynamic_libvlc_media_retain(libvlc_media_t *p_md)
{
    return _libvlc_media_retain(p_md);
}
p_libvlc_media_player_get_state _libvlc_media_player_get_state;
libvlc_state_t dynamic_libvlc_media_player_get_state(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_state(p_mi);
}
p_libvlc_printerr _libvlc_printerr;
char *dynamic_libvlc_printerr(char *fmt)
{
    return _libvlc_printerr(fmt);
}
p_libvlc_media_discoverer_media_list _libvlc_media_discoverer_media_list;
libvlc_media_list_t *dynamic_libvlc_media_discoverer_media_list(libvlc_media_discoverer_t *p_mdis)
{
    return _libvlc_media_discoverer_media_list(p_mdis);
}
p_libvlc_log_get_object _libvlc_log_get_object;
void dynamic_libvlc_log_get_object(libvlc_log_t *ctx, char **name, char **header, uintptr_t *id)
{
    return _libvlc_log_get_object(ctx, name, header, id);
}
p_libvlc_video_set_logo_string _libvlc_video_set_logo_string;
void dynamic_libvlc_video_set_logo_string(libvlc_media_player_t *p_mi, unsigned option, char *psz_value)
{
    return _libvlc_video_set_logo_string(p_mi, option, psz_value);
}
p_libvlc_media_parse _libvlc_media_parse;
void dynamic_libvlc_media_parse(libvlc_media_t *p_md)
{
    return _libvlc_media_parse(p_md);
}
p_libvlc_audio_equalizer_get_preset_name _libvlc_audio_equalizer_get_preset_name;
char *dynamic_libvlc_audio_equalizer_get_preset_name(unsigned u_index)
{
    return _libvlc_audio_equalizer_get_preset_name(u_index);
}
p_libvlc_media_new_path _libvlc_media_new_path;
libvlc_media_t *dynamic_libvlc_media_new_path(libvlc_instance_t *p_instance, char *path)
{
    return _libvlc_media_new_path(p_instance, path);
}
p_libvlc_audio_equalizer_get_band_count _libvlc_audio_equalizer_get_band_count;
unsigned dynamic_libvlc_audio_equalizer_get_band_count(void)
{
    return _libvlc_audio_equalizer_get_band_count();
}
p_libvlc_media_player_get_chapter_count _libvlc_media_player_get_chapter_count;
int dynamic_libvlc_media_player_get_chapter_count(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_chapter_count(p_mi);
}
p_libvlc_media_add_option _libvlc_media_add_option;
void dynamic_libvlc_media_add_option(libvlc_media_t *p_md, char *psz_options)
{
    return _libvlc_media_add_option(p_md, psz_options);
}
p_libvlc_video_take_snapshot _libvlc_video_take_snapshot;
int dynamic_libvlc_video_take_snapshot(libvlc_media_player_t *p_mi, unsigned num, char *psz_filepath, unsigned i_width, unsigned i_height)
{
    return _libvlc_video_take_snapshot(p_mi, num, psz_filepath, i_width, i_height);
}
p_libvlc_media_list_event_manager _libvlc_media_list_event_manager;
libvlc_event_manager_t *dynamic_libvlc_media_list_event_manager(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_event_manager(p_ml);
}
p_libvlc_media_get_state _libvlc_media_get_state;
libvlc_state_t dynamic_libvlc_media_get_state(libvlc_media_t *p_md)
{
    return _libvlc_media_get_state(p_md);
}
p_libvlc_media_discoverer_list_release _libvlc_media_discoverer_list_release;
void dynamic_libvlc_media_discoverer_list_release(libvlc_media_discoverer_description_t **pp_services, size_t i_count)
{
    return _libvlc_media_discoverer_list_release(pp_services, i_count);
}
p_libvlc_dialog_get_context _libvlc_dialog_get_context;
void *dynamic_libvlc_dialog_get_context(libvlc_dialog_id *p_id)
{
    return _libvlc_dialog_get_context(p_id);
}
p_libvlc_audio_get_channel _libvlc_audio_get_channel;
int dynamic_libvlc_audio_get_channel(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_channel(p_mi);
}
p_libvlc_renderer_item_icon_uri _libvlc_renderer_item_icon_uri;
char *dynamic_libvlc_renderer_item_icon_uri(libvlc_renderer_item_t *p_item)
{
    return _libvlc_renderer_item_icon_uri(p_item);
}
p_libvlc_video_get_adjust_float _libvlc_video_get_adjust_float;
float dynamic_libvlc_video_get_adjust_float(libvlc_media_player_t *p_mi, unsigned option)
{
    return _libvlc_video_get_adjust_float(p_mi, option);
}
p_libvlc_media_list_player_next _libvlc_media_list_player_next;
int dynamic_libvlc_media_list_player_next(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_next(p_mlp);
}
p_libvlc_media_list_player_play_item _libvlc_media_list_player_play_item;
int dynamic_libvlc_media_list_player_play_item(libvlc_media_list_player_t *p_mlp, libvlc_media_t *p_md)
{
    return _libvlc_media_list_player_play_item(p_mlp, p_md);
}
p_libvlc_media_discoverer_list_get _libvlc_media_discoverer_list_get;
size_t dynamic_libvlc_media_discoverer_list_get(libvlc_instance_t *p_inst, libvlc_media_discoverer_category_t i_cat, libvlc_media_discoverer_description_t ***ppp_services)
{
    return _libvlc_media_discoverer_list_get(p_inst, i_cat, ppp_services);
}
p_libvlc_log_set_file _libvlc_log_set_file;
void dynamic_libvlc_log_set_file(libvlc_instance_t *p_instance, FILE *stream)
{
    return _libvlc_log_set_file(p_instance, stream);
}
p_libvlc_picture_release _libvlc_picture_release;
void dynamic_libvlc_picture_release(libvlc_picture_t *pic)
{
    return _libvlc_picture_release(pic);
}
p_libvlc_media_player_get_chapter_count_for_title _libvlc_media_player_get_chapter_count_for_title;
int dynamic_libvlc_media_player_get_chapter_count_for_title(libvlc_media_player_t *p_mi, int i_title)
{
    return _libvlc_media_player_get_chapter_count_for_title(p_mi, i_title);
}
p_libvlc_audio_output_device_list_get _libvlc_audio_output_device_list_get;
libvlc_audio_output_device_t *dynamic_libvlc_audio_output_device_list_get(libvlc_instance_t *p_instance, char *aout)
{
    return _libvlc_audio_output_device_list_get(p_instance, aout);
}
p_libvlc_media_add_option_flag _libvlc_media_add_option_flag;
void dynamic_libvlc_media_add_option_flag(libvlc_media_t *p_md, char *psz_options, unsigned i_flags)
{
    return _libvlc_media_add_option_flag(p_md, psz_options, i_flags);
}
p_libvlc_media_new_as_node _libvlc_media_new_as_node;
libvlc_media_t *dynamic_libvlc_media_new_as_node(libvlc_instance_t *p_instance, char *psz_name)
{
    return _libvlc_media_new_as_node(p_instance, psz_name);
}
p_libvlc_dialog_set_context _libvlc_dialog_set_context;
void dynamic_libvlc_dialog_set_context(libvlc_dialog_id *p_id, void *p_context)
{
    return _libvlc_dialog_set_context(p_id, p_context);
}
p_libvlc_delay _libvlc_delay;
int64_t dynamic_libvlc_delay(int64_t pts)
{
    return _libvlc_delay(pts);
}
p_libvlc_media_player_select_track _libvlc_media_player_select_track;
void dynamic_libvlc_media_player_select_track(libvlc_media_player_t *p_mi, libvlc_media_track_t *track)
{
    return _libvlc_media_player_select_track(p_mi, track);
}
p_libvlc_media_player_add_slave _libvlc_media_player_add_slave;
int dynamic_libvlc_media_player_add_slave(libvlc_media_player_t *p_mi, libvlc_media_slave_type_t i_type, char *psz_uri, bool b_select)
{
    return _libvlc_media_player_add_slave(p_mi, i_type, psz_uri, b_select);
}
p_libvlc_track_description_list_release _libvlc_track_description_list_release;
void dynamic_libvlc_track_description_list_release(libvlc_track_description_t *p_track_description)
{
    return _libvlc_track_description_list_release(p_track_description);
}
p_libvlc_errmsg _libvlc_errmsg;
char *dynamic_libvlc_errmsg(void)
{
    return _libvlc_errmsg();
}
p_libvlc_media_get_tracklist _libvlc_media_get_tracklist;
libvlc_media_tracklist_t *dynamic_libvlc_media_get_tracklist(libvlc_media_t *p_md, libvlc_track_type_t type)
{
    return _libvlc_media_get_tracklist(p_md, type);
}
p_libvlc_media_player_set_android_context _libvlc_media_player_set_android_context;
void dynamic_libvlc_media_player_set_android_context(libvlc_media_player_t *p_mi, void *p_awindow_handler)
{
    return _libvlc_media_player_set_android_context(p_mi, p_awindow_handler);
}
p_libvlc_get_changeset _libvlc_get_changeset;
char *dynamic_libvlc_get_changeset(void)
{
    return _libvlc_get_changeset();
}
p_libvlc_renderer_item_flags _libvlc_renderer_item_flags;
int dynamic_libvlc_renderer_item_flags(libvlc_renderer_item_t *p_item)
{
    return _libvlc_renderer_item_flags(p_item);
}
p_libvlc_log_unset _libvlc_log_unset;
void dynamic_libvlc_log_unset(libvlc_instance_t *p_instance)
{
    return _libvlc_log_unset(p_instance);
}
p_libvlc_audio_set_volume _libvlc_audio_set_volume;
int dynamic_libvlc_audio_set_volume(libvlc_media_player_t *p_mi, int i_volume)
{
    return _libvlc_audio_set_volume(p_mi, i_volume);
}
p_libvlc_audio_get_track_count _libvlc_audio_get_track_count;
int dynamic_libvlc_audio_get_track_count(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_track_count(p_mi);
}
p_libvlc_media_set_user_data _libvlc_media_set_user_data;
void dynamic_libvlc_media_set_user_data(libvlc_media_t *p_md, void *p_new_user_data)
{
    return _libvlc_media_set_user_data(p_md, p_new_user_data);
}
p_libvlc_video_get_spu _libvlc_video_get_spu;
int dynamic_libvlc_video_get_spu(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_spu(p_mi);
}
p_libvlc_audio_set_volume_callback _libvlc_audio_set_volume_callback;
void dynamic_libvlc_audio_set_volume_callback(libvlc_media_player_t *mp, libvlc_audio_set_volume_cb set_volume)
{
    return _libvlc_audio_set_volume_callback(mp, set_volume);
}
p_libvlc_video_get_spu_description _libvlc_video_get_spu_description;
libvlc_track_description_t *dynamic_libvlc_video_get_spu_description(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_spu_description(p_mi);
}
p_libvlc_media_list_is_readonly _libvlc_media_list_is_readonly;
bool dynamic_libvlc_media_list_is_readonly(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_is_readonly(p_ml);
}
p_libvlc_media_list_player_get_media_player _libvlc_media_list_player_get_media_player;
libvlc_media_player_t *dynamic_libvlc_media_list_player_get_media_player(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_get_media_player(p_mlp);
}
p_libvlc_media_list_unlock _libvlc_media_list_unlock;
void dynamic_libvlc_media_list_unlock(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_unlock(p_ml);
}
p_libvlc_media_list_player_stop_async _libvlc_media_list_player_stop_async;
void dynamic_libvlc_media_list_player_stop_async(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_stop_async(p_mlp);
}
p_libvlc_release _libvlc_release;
void dynamic_libvlc_release(libvlc_instance_t *p_instance)
{
    return _libvlc_release(p_instance);
}
p_libvlc_media_track_release _libvlc_media_track_release;
void dynamic_libvlc_media_track_release(libvlc_media_track_t *track)
{
    return _libvlc_media_track_release(track);
}
p_libvlc_media_player_previous_chapter _libvlc_media_player_previous_chapter;
void dynamic_libvlc_media_player_previous_chapter(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_previous_chapter(p_mi);
}
p_libvlc_media_player_get_full_title_descriptions _libvlc_media_player_get_full_title_descriptions;
int dynamic_libvlc_media_player_get_full_title_descriptions(libvlc_media_player_t *p_mi, libvlc_title_description_t ***titles)
{
    return _libvlc_media_player_get_full_title_descriptions(p_mi, titles);
}
p_libvlc_video_get_logo_int _libvlc_video_get_logo_int;
int dynamic_libvlc_video_get_logo_int(libvlc_media_player_t *p_mi, unsigned option)
{
    return _libvlc_video_get_logo_int(p_mi, option);
}
p_libvlc_renderer_item_name _libvlc_renderer_item_name;
char *dynamic_libvlc_renderer_item_name(libvlc_renderer_item_t *p_item)
{
    return _libvlc_renderer_item_name(p_item);
}
p_libvlc_media_list_player_play _libvlc_media_list_player_play;
void dynamic_libvlc_media_list_player_play(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_play(p_mlp);
}
p_libvlc_audio_output_set _libvlc_audio_output_set;
int dynamic_libvlc_audio_output_set(libvlc_media_player_t *p_mi, char *psz_name)
{
    return _libvlc_audio_output_set(p_mi, psz_name);
}
p_libvlc_media_new_callbacks _libvlc_media_new_callbacks;
libvlc_media_t *dynamic_libvlc_media_new_callbacks(libvlc_instance_t *instance, libvlc_media_open_cb open_cb, libvlc_media_read_cb read_cb, libvlc_media_seek_cb seek_cb, libvlc_media_close_cb close_cb, void *opaque)
{
    return _libvlc_media_new_callbacks(instance, open_cb, read_cb, seek_cb, close_cb, opaque);
}
p_libvlc_media_discoverer_is_running _libvlc_media_discoverer_is_running;
bool dynamic_libvlc_media_discoverer_is_running(libvlc_media_discoverer_t *p_mdis)
{
    return _libvlc_media_discoverer_is_running(p_mdis);
}
p_libvlc_renderer_item_hold _libvlc_renderer_item_hold;
libvlc_renderer_item_t *dynamic_libvlc_renderer_item_hold(libvlc_renderer_item_t *p_item)
{
    return _libvlc_renderer_item_hold(p_item);
}
p_libvlc_audio_set_delay _libvlc_audio_set_delay;
int dynamic_libvlc_audio_set_delay(libvlc_media_player_t *p_mi, int64_t i_delay)
{
    return _libvlc_audio_set_delay(p_mi, i_delay);
}
p_libvlc_video_set_spu_delay _libvlc_video_set_spu_delay;
int dynamic_libvlc_video_set_spu_delay(libvlc_media_player_t *p_mi, int64_t i_delay)
{
    return _libvlc_video_set_spu_delay(p_mi, i_delay);
}
p_libvlc_renderer_discoverer_new _libvlc_renderer_discoverer_new;
libvlc_renderer_discoverer_t *dynamic_libvlc_renderer_discoverer_new(libvlc_instance_t *p_inst, char *psz_name)
{
    return _libvlc_renderer_discoverer_new(p_inst, psz_name);
}
p_libvlc_media_list_player_event_manager _libvlc_media_list_player_event_manager;
libvlc_event_manager_t *dynamic_libvlc_media_list_player_event_manager(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_event_manager(p_mlp);
}
p_libvlc_dialog_dismiss _libvlc_dialog_dismiss;
int dynamic_libvlc_dialog_dismiss(libvlc_dialog_id *p_id)
{
    return _libvlc_dialog_dismiss(p_id);
}
p_libvlc_audio_filter_list_get _libvlc_audio_filter_list_get;
libvlc_module_description_t *dynamic_libvlc_audio_filter_list_get(libvlc_instance_t *p_instance)
{
    return _libvlc_audio_filter_list_get(p_instance);
}
p_libvlc_media_player_get_chapter _libvlc_media_player_get_chapter;
int dynamic_libvlc_media_player_get_chapter(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_chapter(p_mi);
}
p_libvlc_picture_get_stride _libvlc_picture_get_stride;
unsigned dynamic_libvlc_picture_get_stride(libvlc_picture_t *pic)
{
    return _libvlc_picture_get_stride(pic);
}
p_libvlc_media_player_set_nsobject _libvlc_media_player_set_nsobject;
void dynamic_libvlc_media_player_set_nsobject(libvlc_media_player_t *p_mi, void *drawable)
{
    return _libvlc_media_player_set_nsobject(p_mi, drawable);
}
p_libvlc_set_app_id _libvlc_set_app_id;
void dynamic_libvlc_set_app_id(libvlc_instance_t *p_instance, char *id, char *version, char *icon)
{
    return _libvlc_set_app_id(p_instance, id, version, icon);
}
p_libvlc_media_player_get_selected_program _libvlc_media_player_get_selected_program;
libvlc_player_program_t *dynamic_libvlc_media_player_get_selected_program(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_selected_program(p_mi);
}
p_libvlc_audio_equalizer_get_band_frequency _libvlc_audio_equalizer_get_band_frequency;
float dynamic_libvlc_audio_equalizer_get_band_frequency(unsigned u_index)
{
    return _libvlc_audio_equalizer_get_band_frequency(u_index);
}
p_libvlc_audio_toggle_mute _libvlc_audio_toggle_mute;
void dynamic_libvlc_audio_toggle_mute(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_toggle_mute(p_mi);
}
p_libvlc_picture_type _libvlc_picture_type;
libvlc_picture_type_t dynamic_libvlc_picture_type(libvlc_picture_t *pic)
{
    return _libvlc_picture_type(pic);
}
p_libvlc_media_list_player_release _libvlc_media_list_player_release;
void dynamic_libvlc_media_list_player_release(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_release(p_mlp);
}
p_libvlc_media_list_player_retain _libvlc_media_list_player_retain;
void dynamic_libvlc_media_list_player_retain(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_retain(p_mlp);
}
p_libvlc_media_player_get_nsobject _libvlc_media_player_get_nsobject;
void *dynamic_libvlc_media_player_get_nsobject(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_nsobject(p_mi);
}
p_libvlc_audio_equalizer_release _libvlc_audio_equalizer_release;
void dynamic_libvlc_audio_equalizer_release(libvlc_equalizer_t *p_equalizer)
{
    return _libvlc_audio_equalizer_release(p_equalizer);
}
p_libvlc_picture_get_buffer _libvlc_picture_get_buffer;
unsigned char *dynamic_libvlc_picture_get_buffer(libvlc_picture_t *pic, size_t *size)
{
    return _libvlc_picture_get_buffer(pic, size);
}
p_libvlc_media_player_set_rate _libvlc_media_player_set_rate;
int dynamic_libvlc_media_player_set_rate(libvlc_media_player_t *p_mi, float rate)
{
    return _libvlc_media_player_set_rate(p_mi, rate);
}
p_libvlc_media_player_select_tracks _libvlc_media_player_select_tracks;
void dynamic_libvlc_media_player_select_tracks(libvlc_media_player_t *p_mi, libvlc_track_type_t type, libvlc_media_track_t **tracks, size_t track_count)
{
    return _libvlc_media_player_select_tracks(p_mi, type, tracks, track_count);
}
p_libvlc_audio_equalizer_set_preamp _libvlc_audio_equalizer_set_preamp;
int dynamic_libvlc_audio_equalizer_set_preamp(libvlc_equalizer_t *p_equalizer, float f_preamp)
{
    return _libvlc_audio_equalizer_set_preamp(p_equalizer, f_preamp);
}
p_libvlc_media_thumbnail_request_by_time _libvlc_media_thumbnail_request_by_time;
libvlc_media_thumbnail_request_t *dynamic_libvlc_media_thumbnail_request_by_time(libvlc_media_t *md, libvlc_time_t time, libvlc_thumbnailer_seek_speed_t speed, unsigned width, unsigned height, bool crop, libvlc_picture_type_t picture_type, libvlc_time_t timeout)
{
    return _libvlc_media_thumbnail_request_by_time(md, time, speed, width, height, crop, picture_type, timeout);
}
p_libvlc_media_list_lock _libvlc_media_list_lock;
void dynamic_libvlc_media_list_lock(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_lock(p_ml);
}
p_libvlc_media_list_item_at_index _libvlc_media_list_item_at_index;
libvlc_media_t *dynamic_libvlc_media_list_item_at_index(libvlc_media_list_t *p_ml, int i_pos)
{
    return _libvlc_media_list_item_at_index(p_ml, i_pos);
}
p_libvlc_set_user_agent _libvlc_set_user_agent;
void dynamic_libvlc_set_user_agent(libvlc_instance_t *p_instance, char *name, char *http)
{
    return _libvlc_set_user_agent(p_instance, name, http);
}
p_libvlc_media_player_get_length _libvlc_media_player_get_length;
libvlc_time_t dynamic_libvlc_media_player_get_length(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_length(p_mi);
}
p_libvlc_audio_output_list_get _libvlc_audio_output_list_get;
libvlc_audio_output_t *dynamic_libvlc_audio_output_list_get(libvlc_instance_t *p_instance)
{
    return _libvlc_audio_output_list_get(p_instance);
}
p_libvlc_picture_get_time _libvlc_picture_get_time;
libvlc_time_t dynamic_libvlc_picture_get_time(libvlc_picture_t *pic)
{
    return _libvlc_picture_get_time(pic);
}
p_libvlc_media_list_player_is_playing _libvlc_media_list_player_is_playing;
bool dynamic_libvlc_media_list_player_is_playing(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_is_playing(p_mlp);
}
p_libvlc_video_update_viewpoint _libvlc_video_update_viewpoint;
int dynamic_libvlc_video_update_viewpoint(libvlc_media_player_t *p_mi, libvlc_video_viewpoint_t *p_viewpoint, bool b_absolute)
{
    return _libvlc_video_update_viewpoint(p_mi, p_viewpoint, b_absolute);
}
p_libvlc_get_compiler _libvlc_get_compiler;
char *dynamic_libvlc_get_compiler(void)
{
    return _libvlc_get_compiler();
}
p_libvlc_media_new_location _libvlc_media_new_location;
libvlc_media_t *dynamic_libvlc_media_new_location(libvlc_instance_t *p_instance, char *psz_mrl)
{
    return _libvlc_media_new_location(p_instance, psz_mrl);
}
p_libvlc_new _libvlc_new;
libvlc_instance_t *dynamic_libvlc_new(int argc, char **argv)
{
    return _libvlc_new(argc, argv);
}
p_libvlc_media_discoverer_release _libvlc_media_discoverer_release;
void dynamic_libvlc_media_discoverer_release(libvlc_media_discoverer_t *p_mdis)
{
    return _libvlc_media_discoverer_release(p_mdis);
}
p_libvlc_video_set_crop_ratio _libvlc_video_set_crop_ratio;
void dynamic_libvlc_video_set_crop_ratio(libvlc_media_player_t *mp, unsigned num, unsigned den)
{
    return _libvlc_video_set_crop_ratio(mp, num, den);
}
p_libvlc_media_thumbnail_request_by_pos _libvlc_media_thumbnail_request_by_pos;
libvlc_media_thumbnail_request_t *dynamic_libvlc_media_thumbnail_request_by_pos(libvlc_media_t *md, float pos, libvlc_thumbnailer_seek_speed_t speed, unsigned width, unsigned height, bool crop, libvlc_picture_type_t picture_type, libvlc_time_t timeout)
{
    return _libvlc_media_thumbnail_request_by_pos(md, pos, speed, width, height, crop, picture_type, timeout);
}
p_libvlc_log_get_context _libvlc_log_get_context;
void dynamic_libvlc_log_get_context(libvlc_log_t *ctx, char **module, char **file, unsigned *line)
{
    return _libvlc_log_get_context(ctx, module, file, line);
}
p_libvlc_video_set_marquee_string _libvlc_video_set_marquee_string;
void dynamic_libvlc_video_set_marquee_string(libvlc_media_player_t *p_mi, unsigned option, char *psz_text)
{
    return _libvlc_video_set_marquee_string(p_mi, option, psz_text);
}
p_libvlc_media_player_set_title _libvlc_media_player_set_title;
void dynamic_libvlc_media_player_set_title(libvlc_media_player_t *p_mi, int i_title)
{
    return _libvlc_media_player_set_title(p_mi, i_title);
}
p_libvlc_audio_output_device_enum _libvlc_audio_output_device_enum;
libvlc_audio_output_device_t *dynamic_libvlc_audio_output_device_enum(libvlc_media_player_t *mp)
{
    return _libvlc_audio_output_device_enum(mp);
}
p_libvlc_video_get_track_description _libvlc_video_get_track_description;
libvlc_track_description_t *dynamic_libvlc_video_get_track_description(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_track_description(p_mi);
}
p_libvlc_video_set_track _libvlc_video_set_track;
int dynamic_libvlc_video_set_track(libvlc_media_player_t *p_mi, int i_track)
{
    return _libvlc_video_set_track(p_mi, i_track);
}
p_libvlc_free _libvlc_free;
void dynamic_libvlc_free(void *ptr)
{
    return _libvlc_free(ptr);
}
p_libvlc_picture_list_destroy _libvlc_picture_list_destroy;
void dynamic_libvlc_picture_list_destroy(libvlc_picture_list_t *list)
{
    return _libvlc_picture_list_destroy(list);
}
p_libvlc_media_player_set_position _libvlc_media_player_set_position;
int dynamic_libvlc_media_player_set_position(libvlc_media_player_t *p_mi, float f_pos, bool b_fast)
{
    return _libvlc_media_player_set_position(p_mi, f_pos, b_fast);
}
p_libvlc_picture_list_count _libvlc_picture_list_count;
size_t dynamic_libvlc_picture_list_count(libvlc_picture_list_t *list)
{
    return _libvlc_picture_list_count(list);
}
p_libvlc_video_set_format _libvlc_video_set_format;
void dynamic_libvlc_video_set_format(libvlc_media_player_t *mp, char *chroma, unsigned width, unsigned height, unsigned pitch)
{
    return _libvlc_video_set_format(mp, chroma, width, height, pitch);
}
p_libvlc_media_player_is_seekable _libvlc_media_player_is_seekable;
bool dynamic_libvlc_media_player_is_seekable(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_is_seekable(p_mi);
}
p_libvlc_media_list_player_previous _libvlc_media_list_player_previous;
int dynamic_libvlc_media_list_player_previous(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_previous(p_mlp);
}
p_libvlc_playlist_play _libvlc_playlist_play;
void dynamic_libvlc_playlist_play(libvlc_instance_t *p_instance)
{
    return _libvlc_playlist_play(p_instance);
}
p_libvlc_video_set_mouse_input _libvlc_video_set_mouse_input;
void dynamic_libvlc_video_set_mouse_input(libvlc_media_player_t *p_mi, unsigned on)
{
    return _libvlc_video_set_mouse_input(p_mi, on);
}
p_libvlc_event_attach _libvlc_event_attach;
int dynamic_libvlc_event_attach(libvlc_event_manager_t *p_event_manager, libvlc_event_type_t i_event_type, libvlc_callback_t f_callback, void *user_data)
{
    return _libvlc_event_attach(p_event_manager, i_event_type, f_callback, user_data);
}
p_libvlc_renderer_item_type _libvlc_renderer_item_type;
char *dynamic_libvlc_renderer_item_type(libvlc_renderer_item_t *p_item)
{
    return _libvlc_renderer_item_type(p_item);
}
p_libvlc_media_parse_async _libvlc_media_parse_async;
void dynamic_libvlc_media_parse_async(libvlc_media_t *p_md)
{
    return _libvlc_media_parse_async(p_md);
}
p_libvlc_picture_save _libvlc_picture_save;
int dynamic_libvlc_picture_save(libvlc_picture_t *pic, char *path)
{
    return _libvlc_picture_save(pic, path);
}
p_libvlc_media_thumbnail_request_destroy _libvlc_media_thumbnail_request_destroy;
void dynamic_libvlc_media_thumbnail_request_destroy(libvlc_media_thumbnail_request_t *p_req)
{
    return _libvlc_media_thumbnail_request_destroy(p_req);
}
p_libvlc_media_get_meta _libvlc_media_get_meta;
char *dynamic_libvlc_media_get_meta(libvlc_media_t *p_md, libvlc_meta_t e_meta)
{
    return _libvlc_media_get_meta(p_md, e_meta);
}
p_libvlc_media_discoverer_new _libvlc_media_discoverer_new;
libvlc_media_discoverer_t *dynamic_libvlc_media_discoverer_new(libvlc_instance_t *p_inst, char *psz_name)
{
    return _libvlc_media_discoverer_new(p_inst, psz_name);
}
p_libvlc_video_get_track_count _libvlc_video_get_track_count;
int dynamic_libvlc_video_get_track_count(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_track_count(p_mi);
}
p_libvlc_video_get_size _libvlc_video_get_size;
int dynamic_libvlc_video_get_size(libvlc_media_player_t *p_mi, unsigned num, unsigned *px, unsigned *py)
{
    return _libvlc_video_get_size(p_mi, num, px, py);
}
p_libvlc_picture_retain _libvlc_picture_retain;
void dynamic_libvlc_picture_retain(libvlc_picture_t *pic)
{
    return _libvlc_picture_retain(pic);
}
p_libvlc_clock _libvlc_clock;
int64_t dynamic_libvlc_clock(void)
{
    return _libvlc_clock();
}
p_libvlc_media_duplicate _libvlc_media_duplicate;
libvlc_media_t *dynamic_libvlc_media_duplicate(libvlc_media_t *p_md)
{
    return _libvlc_media_duplicate(p_md);
}
p_libvlc_media_get_parsed_status _libvlc_media_get_parsed_status;
libvlc_media_parsed_status_t dynamic_libvlc_media_get_parsed_status(libvlc_media_t *p_md)
{
    return _libvlc_media_get_parsed_status(p_md);
}
p_libvlc_media_get_stats _libvlc_media_get_stats;
bool dynamic_libvlc_media_get_stats(libvlc_media_t *p_md, libvlc_media_stats_t *p_stats)
{
    return _libvlc_media_get_stats(p_md, p_stats);
}
p_libvlc_media_parse_stop _libvlc_media_parse_stop;
void dynamic_libvlc_media_parse_stop(libvlc_media_t *p_md)
{
    return _libvlc_media_parse_stop(p_md);
}
p_libvlc_media_player_get_program_from_id _libvlc_media_player_get_program_from_id;
libvlc_player_program_t *dynamic_libvlc_media_player_get_program_from_id(libvlc_media_player_t *p_mi, int i_group_id)
{
    return _libvlc_media_player_get_program_from_id(p_mi, i_group_id);
}
p_libvlc_video_set_crop_window _libvlc_video_set_crop_window;
void dynamic_libvlc_video_set_crop_window(libvlc_media_player_t *mp, unsigned x, unsigned y, unsigned width, unsigned height)
{
    return _libvlc_video_set_crop_window(mp, x, y, width, height);
}
p_libvlc_media_list_count _libvlc_media_list_count;
int dynamic_libvlc_media_list_count(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_count(p_ml);
}
p_libvlc_media_slaves_clear _libvlc_media_slaves_clear;
void dynamic_libvlc_media_slaves_clear(libvlc_media_t *p_md)
{
    return _libvlc_media_slaves_clear(p_md);
}
p_libvlc_media_player_stop_async _libvlc_media_player_stop_async;
int dynamic_libvlc_media_player_stop_async(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_stop_async(p_mi);
}
p_libvlc_video_set_format_callbacks _libvlc_video_set_format_callbacks;
void dynamic_libvlc_video_set_format_callbacks(libvlc_media_player_t *mp, libvlc_video_format_cb setup, libvlc_video_cleanup_cb cleanup)
{
    return _libvlc_video_set_format_callbacks(mp, setup, cleanup);
}
p_libvlc_media_player_get_time _libvlc_media_player_get_time;
libvlc_time_t dynamic_libvlc_media_player_get_time(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_time(p_mi);
}
p_libvlc_media_list_player_new _libvlc_media_list_player_new;
libvlc_media_list_player_t *dynamic_libvlc_media_list_player_new(libvlc_instance_t *p_instance)
{
    return _libvlc_media_list_player_new(p_instance);
}
p_libvlc_media_list_player_pause _libvlc_media_list_player_pause;
void dynamic_libvlc_media_list_player_pause(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_pause(p_mlp);
}
p_libvlc_renderer_discoverer_release _libvlc_renderer_discoverer_release;
void dynamic_libvlc_renderer_discoverer_release(libvlc_renderer_discoverer_t *p_rd)
{
    return _libvlc_renderer_discoverer_release(p_rd);
}
p_libvlc_player_program_delete _libvlc_player_program_delete;
void dynamic_libvlc_player_program_delete(libvlc_player_program_t *program)
{
    return _libvlc_player_program_delete(program);
}
p_libvlc_dialog_post_action _libvlc_dialog_post_action;
int dynamic_libvlc_dialog_post_action(libvlc_dialog_id *p_id, int i_action)
{
    return _libvlc_dialog_post_action(p_id, i_action);
}
p_libvlc_video_get_teletext _libvlc_video_get_teletext;
int dynamic_libvlc_video_get_teletext(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_teletext(p_mi);
}
p_libvlc_dialog_post_login _libvlc_dialog_post_login;
int dynamic_libvlc_dialog_post_login(libvlc_dialog_id *p_id, char *psz_username, char *psz_password, bool b_store)
{
    return _libvlc_dialog_post_login(p_id, psz_username, psz_password, b_store);
}
p_libvlc_get_version _libvlc_get_version;
char *dynamic_libvlc_get_version(void)
{
    return _libvlc_get_version();
}
p_libvlc_media_discoverer_stop _libvlc_media_discoverer_stop;
void dynamic_libvlc_media_discoverer_stop(libvlc_media_discoverer_t *p_mdis)
{
    return _libvlc_media_discoverer_stop(p_mdis);
}
p_libvlc_media_tracks_get _libvlc_media_tracks_get;
unsigned dynamic_libvlc_media_tracks_get(libvlc_media_t *p_md, libvlc_media_track_t ***tracks)
{
    return _libvlc_media_tracks_get(p_md, tracks);
}
p_libvlc_media_new_fd _libvlc_media_new_fd;
libvlc_media_t *dynamic_libvlc_media_new_fd(libvlc_instance_t *p_instance, int fd)
{
    return _libvlc_media_new_fd(p_instance, fd);
}
p_libvlc_media_player_set_chapter _libvlc_media_player_set_chapter;
void dynamic_libvlc_media_player_set_chapter(libvlc_media_player_t *p_mi, int i_chapter)
{
    return _libvlc_media_player_set_chapter(p_mi, i_chapter);
}
p_libvlc_renderer_discoverer_list_release _libvlc_renderer_discoverer_list_release;
void dynamic_libvlc_renderer_discoverer_list_release(libvlc_rd_description_t **pp_services, size_t i_count)
{
    return _libvlc_renderer_discoverer_list_release(pp_services, i_count);
}
p_libvlc_audio_output_list_release _libvlc_audio_output_list_release;
void dynamic_libvlc_audio_output_list_release(libvlc_audio_output_t *p_list)
{
    return _libvlc_audio_output_list_release(p_list);
}
p_libvlc_media_discoverer_start _libvlc_media_discoverer_start;
int dynamic_libvlc_media_discoverer_start(libvlc_media_discoverer_t *p_mdis)
{
    return _libvlc_media_discoverer_start(p_mdis);
}
p_libvlc_media_get_user_data _libvlc_media_get_user_data;
void *dynamic_libvlc_media_get_user_data(libvlc_media_t *p_md)
{
    return _libvlc_media_get_user_data(p_md);
}
p_libvlc_media_set_meta _libvlc_media_set_meta;
void dynamic_libvlc_media_set_meta(libvlc_media_t *p_md, libvlc_meta_t e_meta, char *psz_value)
{
    return _libvlc_media_set_meta(p_md, e_meta, psz_value);
}
p_libvlc_audio_set_format _libvlc_audio_set_format;
void dynamic_libvlc_audio_set_format(libvlc_media_player_t *mp, char *format, unsigned rate, unsigned channels)
{
    return _libvlc_audio_set_format(mp, format, rate, channels);
}
p_libvlc_video_get_spu_count _libvlc_video_get_spu_count;
int dynamic_libvlc_video_get_spu_count(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_spu_count(p_mi);
}
p_libvlc_media_event_manager _libvlc_media_event_manager;
libvlc_event_manager_t *dynamic_libvlc_media_event_manager(libvlc_media_t *p_md)
{
    return _libvlc_media_event_manager(p_md);
}
p_libvlc_video_get_scale _libvlc_video_get_scale;
float dynamic_libvlc_video_get_scale(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_scale(p_mi);
}
p_libvlc_audio_equalizer_get_amp_at_index _libvlc_audio_equalizer_get_amp_at_index;
float dynamic_libvlc_audio_equalizer_get_amp_at_index(libvlc_equalizer_t *p_equalizer, unsigned u_band)
{
    return _libvlc_audio_equalizer_get_amp_at_index(p_equalizer, u_band);
}
p_libvlc_picture_get_width _libvlc_picture_get_width;
unsigned dynamic_libvlc_picture_get_width(libvlc_picture_t *pic)
{
    return _libvlc_picture_get_width(pic);
}
p_libvlc_media_release _libvlc_media_release;
void dynamic_libvlc_media_release(libvlc_media_t *p_md)
{
    return _libvlc_media_release(p_md);
}
p_libvlc_media_player_event_manager _libvlc_media_player_event_manager;
libvlc_event_manager_t *dynamic_libvlc_media_player_event_manager(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_event_manager(p_mi);
}
p_libvlc_audio_equalizer_new _libvlc_audio_equalizer_new;
libvlc_equalizer_t *dynamic_libvlc_audio_equalizer_new(void)
{
    return _libvlc_audio_equalizer_new();
}
p_libvlc_media_player_retain _libvlc_media_player_retain;
void dynamic_libvlc_media_player_retain(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_retain(p_mi);
}
p_libvlc_player_programlist_delete _libvlc_player_programlist_delete;
void dynamic_libvlc_player_programlist_delete(libvlc_player_programlist_t *list)
{
    return _libvlc_player_programlist_delete(list);
}
p_libvlc_media_player_can_pause _libvlc_media_player_can_pause;
bool dynamic_libvlc_media_player_can_pause(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_can_pause(p_mi);
}
p_libvlc_add_intf _libvlc_add_intf;
int dynamic_libvlc_add_intf(libvlc_instance_t *p_instance, char *name)
{
    return _libvlc_add_intf(p_instance, name);
}
p_libvlc_player_programlist_count _libvlc_player_programlist_count;
size_t dynamic_libvlc_player_programlist_count(libvlc_player_programlist_t *list)
{
    return _libvlc_player_programlist_count(list);
}
p_libvlc_media_player_get_tracklist _libvlc_media_player_get_tracklist;
libvlc_media_tracklist_t *dynamic_libvlc_media_player_get_tracklist(libvlc_media_player_t *p_mi, libvlc_track_type_t type)
{
    return _libvlc_media_player_get_tracklist(p_mi, type);
}
p_libvlc_audio_equalizer_get_preset_count _libvlc_audio_equalizer_get_preset_count;
unsigned dynamic_libvlc_audio_equalizer_get_preset_count(void)
{
    return _libvlc_audio_equalizer_get_preset_count();
}
p_libvlc_media_list_index_of_item _libvlc_media_list_index_of_item;
int dynamic_libvlc_media_list_index_of_item(libvlc_media_list_t *p_ml, libvlc_media_t *p_md)
{
    return _libvlc_media_list_index_of_item(p_ml, p_md);
}
p_libvlc_media_list_player_set_pause _libvlc_media_list_player_set_pause;
void dynamic_libvlc_media_list_player_set_pause(libvlc_media_list_player_t *p_mlp, int do_pause)
{
    return _libvlc_media_list_player_set_pause(p_mlp, do_pause);
}
p_libvlc_video_set_spu_text_scale _libvlc_video_set_spu_text_scale;
void dynamic_libvlc_video_set_spu_text_scale(libvlc_media_player_t *p_mi, float f_scale)
{
    return _libvlc_video_set_spu_text_scale(p_mi, f_scale);
}
p_libvlc_media_list_release _libvlc_media_list_release;
void dynamic_libvlc_media_list_release(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_release(p_ml);
}
p_libvlc_media_list_insert_media _libvlc_media_list_insert_media;
int dynamic_libvlc_media_list_insert_media(libvlc_media_list_t *p_ml, libvlc_media_t *p_md, int i_pos)
{
    return _libvlc_media_list_insert_media(p_ml, p_md, i_pos);
}
p_libvlc_set_exit_handler _libvlc_set_exit_handler;
void dynamic_libvlc_set_exit_handler(libvlc_instance_t *p_instance, void (*cb)(void *), void *opaque)
{
    return _libvlc_set_exit_handler(p_instance, cb, opaque);
}
p_libvlc_audio_get_volume _libvlc_audio_get_volume;
int dynamic_libvlc_audio_get_volume(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_volume(p_mi);
}
p_libvlc_media_list_new _libvlc_media_list_new;
libvlc_media_list_t *dynamic_libvlc_media_list_new(void)
{
    return _libvlc_media_list_new();
}
p_libvlc_video_get_spu_delay _libvlc_video_get_spu_delay;
int64_t dynamic_libvlc_video_get_spu_delay(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_spu_delay(p_mi);
}
p_libvlc_audio_equalizer_set_amp_at_index _libvlc_audio_equalizer_set_amp_at_index;
int dynamic_libvlc_audio_equalizer_set_amp_at_index(libvlc_equalizer_t *p_equalizer, float f_amp, unsigned u_band)
{
    return _libvlc_audio_equalizer_set_amp_at_index(p_equalizer, f_amp, u_band);
}
p_libvlc_media_player_is_playing _libvlc_media_player_is_playing;
bool dynamic_libvlc_media_player_is_playing(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_is_playing(p_mi);
}
p_libvlc_media_parse_with_options _libvlc_media_parse_with_options;
int dynamic_libvlc_media_parse_with_options(libvlc_media_t *p_md, libvlc_media_parse_flag_t parse_flag, int timeout)
{
    return _libvlc_media_parse_with_options(p_md, parse_flag, timeout);
}
p_libvlc_video_set_spu _libvlc_video_set_spu;
int dynamic_libvlc_video_set_spu(libvlc_media_player_t *p_mi, int i_spu)
{
    return _libvlc_video_set_spu(p_mi, i_spu);
}
p_libvlc_media_slaves_get _libvlc_media_slaves_get;
unsigned dynamic_libvlc_media_slaves_get(libvlc_media_t *p_md, libvlc_media_slave_t ***ppp_slaves)
{
    return _libvlc_media_slaves_get(p_md, ppp_slaves);
}
p_libvlc_video_set_callbacks _libvlc_video_set_callbacks;
void dynamic_libvlc_video_set_callbacks(libvlc_media_player_t *mp, libvlc_video_lock_cb lock, libvlc_video_unlock_cb unlock, libvlc_video_display_cb display, void *opaque)
{
    return _libvlc_video_set_callbacks(mp, lock, unlock, display, opaque);
}
p_libvlc_video_get_adjust_int _libvlc_video_get_adjust_int;
int dynamic_libvlc_video_get_adjust_int(libvlc_media_player_t *p_mi, unsigned option)
{
    return _libvlc_video_get_adjust_int(p_mi, option);
}
p_libvlc_picture_list_at _libvlc_picture_list_at;
libvlc_picture_t *dynamic_libvlc_picture_list_at(libvlc_picture_list_t *list, size_t index)
{
    return _libvlc_picture_list_at(list, index);
}
p_libvlc_media_get_type _libvlc_media_get_type;
libvlc_media_type_t dynamic_libvlc_media_get_type(libvlc_media_t *p_md)
{
    return _libvlc_media_get_type(p_md);
}
p_libvlc_title_descriptions_release _libvlc_title_descriptions_release;
void dynamic_libvlc_title_descriptions_release(libvlc_title_description_t **p_titles, unsigned i_count)
{
    return _libvlc_title_descriptions_release(p_titles, i_count);
}
p_libvlc_renderer_discoverer_list_get _libvlc_renderer_discoverer_list_get;
size_t dynamic_libvlc_renderer_discoverer_list_get(libvlc_instance_t *p_inst, libvlc_rd_description_t ***ppp_services)
{
    return _libvlc_renderer_discoverer_list_get(p_inst, ppp_services);
}
p_libvlc_media_player_set_equalizer _libvlc_media_player_set_equalizer;
int dynamic_libvlc_media_player_set_equalizer(libvlc_media_player_t *p_mi, libvlc_equalizer_t *p_equalizer)
{
    return _libvlc_media_player_set_equalizer(p_mi, p_equalizer);
}
p_libvlc_media_player_get_programlist _libvlc_media_player_get_programlist;
libvlc_player_programlist_t *dynamic_libvlc_media_player_get_programlist(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_programlist(p_mi);
}
p_libvlc_media_list_player_set_playback_mode _libvlc_media_list_player_set_playback_mode;
void dynamic_libvlc_media_list_player_set_playback_mode(libvlc_media_list_player_t *p_mlp, libvlc_playback_mode_t e_mode)
{
    return _libvlc_media_list_player_set_playback_mode(p_mlp, e_mode);
}
p_libvlc_media_list_remove_index _libvlc_media_list_remove_index;
int dynamic_libvlc_media_list_remove_index(libvlc_media_list_t *p_ml, int i_pos)
{
    return _libvlc_media_list_remove_index(p_ml, i_pos);
}
p_libvlc_media_slaves_release _libvlc_media_slaves_release;
void dynamic_libvlc_media_slaves_release(libvlc_media_slave_t **pp_slaves, unsigned i_count)
{
    return _libvlc_media_slaves_release(pp_slaves, i_count);
}
p_libvlc_media_player_pause _libvlc_media_player_pause;
void dynamic_libvlc_media_player_pause(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_pause(p_mi);
}
p_libvlc_renderer_discoverer_start _libvlc_renderer_discoverer_start;
int dynamic_libvlc_renderer_discoverer_start(libvlc_renderer_discoverer_t *p_rd)
{
    return _libvlc_renderer_discoverer_start(p_rd);
}
p_libvlc_media_player_get_position _libvlc_media_player_get_position;
float dynamic_libvlc_media_player_get_position(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_position(p_mi);
}
p_libvlc_media_player_get_xwindow _libvlc_media_player_get_xwindow;
long dynamic_libvlc_media_player_get_xwindow(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_xwindow(p_mi);
}
p_libvlc_video_get_cursor _libvlc_video_get_cursor;
int dynamic_libvlc_video_get_cursor(libvlc_media_player_t *p_mi, unsigned num, int *px, int *py)
{
    return _libvlc_video_get_cursor(p_mi, num, px, py);
}
p_libvlc_media_player_release _libvlc_media_player_release;
void dynamic_libvlc_media_player_release(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_release(p_mi);
}
p_libvlc_media_player_set_renderer _libvlc_media_player_set_renderer;
int dynamic_libvlc_media_player_set_renderer(libvlc_media_player_t *p_mi, libvlc_renderer_item_t *p_item)
{
    return _libvlc_media_player_set_renderer(p_mi, p_item);
}
p_libvlc_audio_output_device_get _libvlc_audio_output_device_get;
char *dynamic_libvlc_audio_output_device_get(libvlc_media_player_t *mp)
{
    return _libvlc_audio_output_device_get(mp);
}
p_libvlc_picture_get_height _libvlc_picture_get_height;
unsigned dynamic_libvlc_picture_get_height(libvlc_picture_t *pic)
{
    return _libvlc_picture_get_height(pic);
}
p_libvlc_media_save_meta _libvlc_media_save_meta;
int dynamic_libvlc_media_save_meta(libvlc_media_t *p_md)
{
    return _libvlc_media_save_meta(p_md);
}
p_libvlc_get_fullscreen _libvlc_get_fullscreen;
bool dynamic_libvlc_get_fullscreen(libvlc_media_player_t *p_mi)
{
    return _libvlc_get_fullscreen(p_mi);
}
p_libvlc_audio_get_track_description _libvlc_audio_get_track_description;
libvlc_track_description_t *dynamic_libvlc_audio_get_track_description(libvlc_media_player_t *p_mi)
{
    return _libvlc_audio_get_track_description(p_mi);
}
p_libvlc_media_player_set_hwnd _libvlc_media_player_set_hwnd;
void dynamic_libvlc_media_player_set_hwnd(libvlc_media_player_t *p_mi, void *drawable)
{
    return _libvlc_media_player_set_hwnd(p_mi, drawable);
}
p_libvlc_media_player_get_track_from_id _libvlc_media_player_get_track_from_id;
libvlc_media_track_t *dynamic_libvlc_media_player_get_track_from_id(libvlc_media_player_t *p_mi, char *psz_id)
{
    return _libvlc_media_player_get_track_from_id(p_mi, psz_id);
}
p_libvlc_media_track_hold _libvlc_media_track_hold;
libvlc_media_track_t *dynamic_libvlc_media_track_hold(libvlc_media_track_t *mt)
{
    return _libvlc_media_track_hold(mt);
}
p_libvlc_media_player_get_hwnd _libvlc_media_player_get_hwnd;
void *dynamic_libvlc_media_player_get_hwnd(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_hwnd(p_mi);
}
p_libvlc_media_player_get_selected_track _libvlc_media_player_get_selected_track;
libvlc_media_track_t *dynamic_libvlc_media_player_get_selected_track(libvlc_media_player_t *p_mi, libvlc_track_type_t type)
{
    return _libvlc_media_player_get_selected_track(p_mi, type);
}
p_libvlc_audio_set_format_callbacks _libvlc_audio_set_format_callbacks;
void dynamic_libvlc_audio_set_format_callbacks(libvlc_media_player_t *mp, libvlc_audio_setup_cb setup, libvlc_audio_cleanup_cb cleanup)
{
    return _libvlc_audio_set_format_callbacks(mp, setup, cleanup);
}
p_libvlc_media_player_set_time _libvlc_media_player_set_time;
int dynamic_libvlc_media_player_set_time(libvlc_media_player_t *p_mi, libvlc_time_t i_time, bool b_fast)
{
    return _libvlc_media_player_set_time(p_mi, i_time, b_fast);
}
p_libvlc_video_get_track _libvlc_video_get_track;
int dynamic_libvlc_video_get_track(libvlc_media_player_t *p_mi)
{
    return _libvlc_video_get_track(p_mi);
}
p_libvlc_audio_set_track _libvlc_audio_set_track;
int dynamic_libvlc_audio_set_track(libvlc_media_player_t *p_mi, int i_track)
{
    return _libvlc_audio_set_track(p_mi, i_track);
}
p_libvlc_audio_output_device_set _libvlc_audio_output_device_set;
void dynamic_libvlc_audio_output_device_set(libvlc_media_player_t *mp, char *module, char *device_id)
{
    return _libvlc_audio_output_device_set(mp, module, device_id);
}
p_libvlc_video_set_output_callbacks _libvlc_video_set_output_callbacks;
bool dynamic_libvlc_video_set_output_callbacks(libvlc_media_player_t *mp, libvlc_video_engine_t engine, libvlc_video_output_setup_cb setup_cb, libvlc_video_output_cleanup_cb cleanup_cb, libvlc_video_output_set_resize_cb resize_cb, libvlc_video_update_output_cb update_output_cb, libvlc_video_swap_cb swap_cb, libvlc_video_makeCurrent_cb makeCurrent_cb, libvlc_video_getProcAddress_cb getProcAddress_cb, libvlc_video_frameMetadata_cb metadata_cb, libvlc_video_output_select_plane_cb select_plane_cb, void *opaque)
{
    return _libvlc_video_set_output_callbacks(mp, engine, setup_cb, cleanup_cb, resize_cb, update_output_cb, swap_cb, makeCurrent_cb, getProcAddress_cb, metadata_cb, select_plane_cb, opaque);
}
p_libvlc_media_player_get_role _libvlc_media_player_get_role;
int dynamic_libvlc_media_player_get_role(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_get_role(p_mi);
}
p_libvlc_media_tracks_release _libvlc_media_tracks_release;
void dynamic_libvlc_media_tracks_release(libvlc_media_track_t **p_tracks, unsigned i_count)
{
    return _libvlc_media_tracks_release(p_tracks, i_count);
}
p_libvlc_video_new_viewpoint _libvlc_video_new_viewpoint;
libvlc_video_viewpoint_t *dynamic_libvlc_video_new_viewpoint(void)
{
    return _libvlc_video_new_viewpoint();
}
p_libvlc_media_subitems _libvlc_media_subitems;
struct libvlc_media_list_t *dynamic_libvlc_media_subitems(libvlc_media_t *p_md)
{
    return _libvlc_media_subitems(p_md);
}
p_libvlc_media_get_duration _libvlc_media_get_duration;
libvlc_time_t dynamic_libvlc_media_get_duration(libvlc_media_t *p_md)
{
    return _libvlc_media_get_duration(p_md);
}
p_libvlc_vprinterr _libvlc_vprinterr;
char *dynamic_libvlc_vprinterr(char *fmt, void *ap)
{
    return _libvlc_vprinterr(fmt, ap);
}
p_libvlc_media_list_media _libvlc_media_list_media;
libvlc_media_t *dynamic_libvlc_media_list_media(libvlc_media_list_t *p_ml)
{
    return _libvlc_media_list_media(p_ml);
}
p_libvlc_media_tracklist_at _libvlc_media_tracklist_at;
libvlc_media_track_t *dynamic_libvlc_media_tracklist_at(libvlc_media_tracklist_t *list, size_t index)
{
    return _libvlc_media_tracklist_at(list, index);
}
p_libvlc_audio_set_callbacks _libvlc_audio_set_callbacks;
void dynamic_libvlc_audio_set_callbacks(libvlc_media_player_t *mp, libvlc_audio_play_cb play, libvlc_audio_pause_cb pause, libvlc_audio_resume_cb resume, libvlc_audio_flush_cb flush, libvlc_audio_drain_cb drain, void *opaque)
{
    return _libvlc_audio_set_callbacks(mp, play, pause, resume, flush, drain, opaque);
}
p_libvlc_renderer_discoverer_stop _libvlc_renderer_discoverer_stop;
void dynamic_libvlc_renderer_discoverer_stop(libvlc_renderer_discoverer_t *p_rd)
{
    return _libvlc_renderer_discoverer_stop(p_rd);
}
p_libvlc_audio_output_device_list_release _libvlc_audio_output_device_list_release;
void dynamic_libvlc_audio_output_device_list_release(libvlc_audio_output_device_t *p_list)
{
    return _libvlc_audio_output_device_list_release(p_list);
}
p_libvlc_media_player_has_vout _libvlc_media_player_has_vout;
unsigned dynamic_libvlc_media_player_has_vout(libvlc_media_player_t *p_mi)
{
    return _libvlc_media_player_has_vout(p_mi);
}
p_libvlc_video_set_adjust_int _libvlc_video_set_adjust_int;
void dynamic_libvlc_video_set_adjust_int(libvlc_media_player_t *p_mi, unsigned option, int value)
{
    return _libvlc_video_set_adjust_int(p_mi, option, value);
}
p_libvlc_video_set_deinterlace _libvlc_video_set_deinterlace;
void dynamic_libvlc_video_set_deinterlace(libvlc_media_player_t *p_mi, int deinterlace, char *psz_mode)
{
    return _libvlc_video_set_deinterlace(p_mi, deinterlace, psz_mode);
}
p_libvlc_media_list_player_get_state _libvlc_media_list_player_get_state;
libvlc_state_t dynamic_libvlc_media_list_player_get_state(libvlc_media_list_player_t *p_mlp)
{
    return _libvlc_media_list_player_get_state(p_mlp);
}
p_libvlc_media_list_player_play_item_at_index _libvlc_media_list_player_play_item_at_index;
int dynamic_libvlc_media_list_player_play_item_at_index(libvlc_media_list_player_t *p_mlp, int i_index)
{
    return _libvlc_media_list_player_play_item_at_index(p_mlp, i_index);
}
p_libvlc_media_slaves_add _libvlc_media_slaves_add;
int dynamic_libvlc_media_slaves_add(libvlc_media_t *p_md, libvlc_media_slave_type_t i_type, unsigned i_priority, char *psz_uri)
{
    return _libvlc_media_slaves_add(p_md, i_type, i_priority, psz_uri);
}

const char * dynamic_load()
{
    char * error;
    _libvlc_video_set_crop_window = (p_libvlc_video_set_crop_window)dlsym(RTLD_DEFAULT, "libvlc_video_set_crop_window");
    _libvlc_media_list_retain = (p_libvlc_media_list_retain)dlsym(RTLD_DEFAULT, "libvlc_media_list_retain");
    _libvlc_audio_set_volume_callback = (p_libvlc_audio_set_volume_callback)dlsym(RTLD_DEFAULT, "libvlc_audio_set_volume_callback");
    _libvlc_audio_equalizer_get_preset_name = (p_libvlc_audio_equalizer_get_preset_name)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_get_preset_name");
    _libvlc_media_player_set_position = (p_libvlc_media_player_set_position)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_position");
    _libvlc_media_player_get_chapter = (p_libvlc_media_player_get_chapter)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_chapter");
    _libvlc_audio_toggle_mute = (p_libvlc_audio_toggle_mute)dlsym(RTLD_DEFAULT, "libvlc_audio_toggle_mute");
    _libvlc_media_track_hold = (p_libvlc_media_track_hold)dlsym(RTLD_DEFAULT, "libvlc_media_track_hold");
    _libvlc_picture_release = (p_libvlc_picture_release)dlsym(RTLD_DEFAULT, "libvlc_picture_release");
    _libvlc_video_set_crop_ratio = (p_libvlc_video_set_crop_ratio)dlsym(RTLD_DEFAULT, "libvlc_video_set_crop_ratio");
    _libvlc_media_player_select_tracks = (p_libvlc_media_player_select_tracks)dlsym(RTLD_DEFAULT, "libvlc_media_player_select_tracks");
    _libvlc_video_set_aspect_ratio = (p_libvlc_video_set_aspect_ratio)dlsym(RTLD_DEFAULT, "libvlc_video_set_aspect_ratio");
    _libvlc_media_list_release = (p_libvlc_media_list_release)dlsym(RTLD_DEFAULT, "libvlc_media_list_release");
    _libvlc_media_get_duration = (p_libvlc_media_get_duration)dlsym(RTLD_DEFAULT, "libvlc_media_get_duration");
    _libvlc_media_list_item_at_index = (p_libvlc_media_list_item_at_index)dlsym(RTLD_DEFAULT, "libvlc_media_list_item_at_index");
    _libvlc_set_exit_handler = (p_libvlc_set_exit_handler)dlsym(RTLD_DEFAULT, "libvlc_set_exit_handler");
    _libvlc_free = (p_libvlc_free)dlsym(RTLD_DEFAULT, "libvlc_free");
    _libvlc_media_player_set_hwnd = (p_libvlc_media_player_set_hwnd)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_hwnd");
    _libvlc_media_parse_stop = (p_libvlc_media_parse_stop)dlsym(RTLD_DEFAULT, "libvlc_media_parse_stop");
    _libvlc_media_player_set_renderer = (p_libvlc_media_player_set_renderer)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_renderer");
    _libvlc_media_list_player_play_item = (p_libvlc_media_list_player_play_item)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_play_item");
    _libvlc_dialog_post_action = (p_libvlc_dialog_post_action)dlsym(RTLD_DEFAULT, "libvlc_dialog_post_action");
    _libvlc_media_player_get_full_title_descriptions = (p_libvlc_media_player_get_full_title_descriptions)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_full_title_descriptions");
    
    dlerror();
    _libvlc_media_player_stop_async = (p_libvlc_media_player_stop_async)dlsym(RTLD_DEFAULT, "libvlc_media_player_stop_async");
    if((error = dlerror()) != NULL) _libvlc_media_player_stop_async = (p_libvlc_media_player_stop_async)dlsym(RTLD_DEFAULT, "libvlc_media_player_stop");

    _libvlc_player_programlist_delete = (p_libvlc_player_programlist_delete)dlsym(RTLD_DEFAULT, "libvlc_player_programlist_delete");
    _libvlc_audio_equalizer_get_band_count = (p_libvlc_audio_equalizer_get_band_count)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_get_band_count");
    _libvlc_video_set_adjust_int = (p_libvlc_video_set_adjust_int)dlsym(RTLD_DEFAULT, "libvlc_video_set_adjust_int");
    _libvlc_audio_get_track = (p_libvlc_audio_get_track)dlsym(RTLD_DEFAULT, "libvlc_audio_get_track");
    _libvlc_audio_equalizer_get_preset_count = (p_libvlc_audio_equalizer_get_preset_count)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_get_preset_count");
    _libvlc_media_get_stats = (p_libvlc_media_get_stats)dlsym(RTLD_DEFAULT, "libvlc_media_get_stats");
    _libvlc_media_set_user_data = (p_libvlc_media_set_user_data)dlsym(RTLD_DEFAULT, "libvlc_media_set_user_data");
    _libvlc_media_player_unselect_track_type = (p_libvlc_media_player_unselect_track_type)dlsym(RTLD_DEFAULT, "libvlc_media_player_unselect_track_type");
    _libvlc_media_list_player_set_playback_mode = (p_libvlc_media_list_player_set_playback_mode)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_set_playback_mode");
    _libvlc_audio_get_channel = (p_libvlc_audio_get_channel)dlsym(RTLD_DEFAULT, "libvlc_audio_get_channel");
    _libvlc_media_player_can_pause = (p_libvlc_media_player_can_pause)dlsym(RTLD_DEFAULT, "libvlc_media_player_can_pause");
    _libvlc_audio_filter_list_get = (p_libvlc_audio_filter_list_get)dlsym(RTLD_DEFAULT, "libvlc_audio_filter_list_get");
    _libvlc_renderer_item_name = (p_libvlc_renderer_item_name)dlsym(RTLD_DEFAULT, "libvlc_renderer_item_name");
    _libvlc_audio_set_volume = (p_libvlc_audio_set_volume)dlsym(RTLD_DEFAULT, "libvlc_audio_set_volume");
    _libvlc_media_player_get_length = (p_libvlc_media_player_get_length)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_length");
    _libvlc_media_list_player_set_media_list = (p_libvlc_media_list_player_set_media_list)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_set_media_list");
    _libvlc_media_player_get_xwindow = (p_libvlc_media_player_get_xwindow)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_xwindow");
    _libvlc_audio_equalizer_get_preamp = (p_libvlc_audio_equalizer_get_preamp)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_get_preamp");
    _libvlc_media_is_parsed = (p_libvlc_media_is_parsed)dlsym(RTLD_DEFAULT, "libvlc_media_is_parsed");
    _libvlc_video_get_adjust_float = (p_libvlc_video_get_adjust_float)dlsym(RTLD_DEFAULT, "libvlc_video_get_adjust_float");
    _libvlc_player_programlist_count = (p_libvlc_player_programlist_count)dlsym(RTLD_DEFAULT, "libvlc_player_programlist_count");
    _libvlc_media_thumbnail_request_destroy = (p_libvlc_media_thumbnail_request_destroy)dlsym(RTLD_DEFAULT, "libvlc_media_thumbnail_request_destroy");
    _libvlc_media_player_select_track = (p_libvlc_media_player_select_track)dlsym(RTLD_DEFAULT, "libvlc_media_player_select_track");
    _libvlc_video_set_spu_delay = (p_libvlc_video_set_spu_delay)dlsym(RTLD_DEFAULT, "libvlc_video_set_spu_delay");
    _libvlc_media_add_option = (p_libvlc_media_add_option)dlsym(RTLD_DEFAULT, "libvlc_media_add_option");
    _libvlc_get_compiler = (p_libvlc_get_compiler)dlsym(RTLD_DEFAULT, "libvlc_get_compiler");
    _libvlc_media_duplicate = (p_libvlc_media_duplicate)dlsym(RTLD_DEFAULT, "libvlc_media_duplicate");
    _libvlc_video_set_adjust_float = (p_libvlc_video_set_adjust_float)dlsym(RTLD_DEFAULT, "libvlc_video_set_adjust_float");
    _libvlc_media_player_get_title_count = (p_libvlc_media_player_get_title_count)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_title_count");
    _libvlc_media_new_fd = (p_libvlc_media_new_fd)dlsym(RTLD_DEFAULT, "libvlc_media_new_fd");
    _libvlc_renderer_item_type = (p_libvlc_renderer_item_type)dlsym(RTLD_DEFAULT, "libvlc_renderer_item_type");
    _libvlc_media_player_get_programlist = (p_libvlc_media_player_get_programlist)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_programlist");
    _libvlc_media_list_count = (p_libvlc_media_list_count)dlsym(RTLD_DEFAULT, "libvlc_media_list_count");
    _libvlc_media_discoverer_list_get = (p_libvlc_media_discoverer_list_get)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_list_get");
    _libvlc_media_player_set_role = (p_libvlc_media_player_set_role)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_role");
    _libvlc_media_discoverer_start = (p_libvlc_media_discoverer_start)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_start");
    _libvlc_video_get_spu_delay = (p_libvlc_video_get_spu_delay)dlsym(RTLD_DEFAULT, "libvlc_video_get_spu_delay");
    _libvlc_media_get_user_data = (p_libvlc_media_get_user_data)dlsym(RTLD_DEFAULT, "libvlc_media_get_user_data");
    _libvlc_audio_get_delay = (p_libvlc_audio_get_delay)dlsym(RTLD_DEFAULT, "libvlc_audio_get_delay");
    _libvlc_module_description_list_release = (p_libvlc_module_description_list_release)dlsym(RTLD_DEFAULT, "libvlc_module_description_list_release");
    _libvlc_video_update_viewpoint = (p_libvlc_video_update_viewpoint)dlsym(RTLD_DEFAULT, "libvlc_video_update_viewpoint");
    _libvlc_video_get_spu_description = (p_libvlc_video_get_spu_description)dlsym(RTLD_DEFAULT, "libvlc_video_get_spu_description");
    _libvlc_media_player_set_title = (p_libvlc_media_player_set_title)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_title");
    _libvlc_video_set_spu = (p_libvlc_video_set_spu)dlsym(RTLD_DEFAULT, "libvlc_video_set_spu");
    _libvlc_picture_type = (p_libvlc_picture_type)dlsym(RTLD_DEFAULT, "libvlc_picture_type");
    _libvlc_audio_output_set = (p_libvlc_audio_output_set)dlsym(RTLD_DEFAULT, "libvlc_audio_output_set");
    _libvlc_audio_equalizer_new_from_preset = (p_libvlc_audio_equalizer_new_from_preset)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_new_from_preset");
    _libvlc_audio_set_track = (p_libvlc_audio_set_track)dlsym(RTLD_DEFAULT, "libvlc_audio_set_track");
    _libvlc_media_player_has_vout = (p_libvlc_media_player_has_vout)dlsym(RTLD_DEFAULT, "libvlc_media_player_has_vout");
    _libvlc_media_release = (p_libvlc_media_release)dlsym(RTLD_DEFAULT, "libvlc_media_release");
    _libvlc_player_program_delete = (p_libvlc_player_program_delete)dlsym(RTLD_DEFAULT, "libvlc_player_program_delete");
    _libvlc_audio_set_callbacks = (p_libvlc_audio_set_callbacks)dlsym(RTLD_DEFAULT, "libvlc_audio_set_callbacks");
    _libvlc_audio_set_format = (p_libvlc_audio_set_format)dlsym(RTLD_DEFAULT, "libvlc_audio_set_format");
    _libvlc_media_player_select_program_id = (p_libvlc_media_player_select_program_id)dlsym(RTLD_DEFAULT, "libvlc_media_player_select_program_id");
    _libvlc_media_tracks_release = (p_libvlc_media_tracks_release)dlsym(RTLD_DEFAULT, "libvlc_media_tracks_release");
    _libvlc_audio_equalizer_get_amp_at_index = (p_libvlc_audio_equalizer_get_amp_at_index)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_get_amp_at_index");
    _libvlc_media_track_release = (p_libvlc_media_track_release)dlsym(RTLD_DEFAULT, "libvlc_media_track_release");
    _libvlc_media_player_is_playing = (p_libvlc_media_player_is_playing)dlsym(RTLD_DEFAULT, "libvlc_media_player_is_playing");
    _libvlc_title_descriptions_release = (p_libvlc_title_descriptions_release)dlsym(RTLD_DEFAULT, "libvlc_title_descriptions_release");
    _libvlc_media_list_is_readonly = (p_libvlc_media_list_is_readonly)dlsym(RTLD_DEFAULT, "libvlc_media_list_is_readonly");
    _libvlc_video_set_spu_text_scale = (p_libvlc_video_set_spu_text_scale)dlsym(RTLD_DEFAULT, "libvlc_video_set_spu_text_scale");
    _libvlc_media_player_add_slave = (p_libvlc_media_player_add_slave)dlsym(RTLD_DEFAULT, "libvlc_media_player_add_slave");
    _libvlc_log_get_context = (p_libvlc_log_get_context)dlsym(RTLD_DEFAULT, "libvlc_log_get_context");
    _libvlc_media_player_release = (p_libvlc_media_player_release)dlsym(RTLD_DEFAULT, "libvlc_media_player_release");
    _libvlc_video_set_logo_string = (p_libvlc_video_set_logo_string)dlsym(RTLD_DEFAULT, "libvlc_video_set_logo_string");
    _libvlc_video_get_spu_text_scale = (p_libvlc_video_get_spu_text_scale)dlsym(RTLD_DEFAULT, "libvlc_video_get_spu_text_scale");
    _libvlc_media_list_player_retain = (p_libvlc_media_list_player_retain)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_retain");
    _libvlc_playlist_play = (p_libvlc_playlist_play)dlsym(RTLD_DEFAULT, "libvlc_playlist_play");
    _libvlc_media_list_player_pause = (p_libvlc_media_list_player_pause)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_pause");
    _libvlc_media_player_set_equalizer = (p_libvlc_media_player_set_equalizer)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_equalizer");
    _libvlc_media_list_player_play_item_at_index = (p_libvlc_media_list_player_play_item_at_index)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_play_item_at_index");
    _libvlc_media_tracklist_count = (p_libvlc_media_tracklist_count)dlsym(RTLD_DEFAULT, "libvlc_media_tracklist_count");
    _libvlc_video_set_callbacks = (p_libvlc_video_set_callbacks)dlsym(RTLD_DEFAULT, "libvlc_video_set_callbacks");
    _libvlc_video_get_teletext = (p_libvlc_video_get_teletext)dlsym(RTLD_DEFAULT, "libvlc_video_get_teletext");
    _libvlc_event_attach = (p_libvlc_event_attach)dlsym(RTLD_DEFAULT, "libvlc_event_attach");
    _libvlc_renderer_discoverer_list_get = (p_libvlc_renderer_discoverer_list_get)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_list_get");
    _libvlc_media_player_set_pause = (p_libvlc_media_player_set_pause)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_pause");

    dlerror();
    _libvlc_media_list_player_stop_async = (p_libvlc_media_list_player_stop_async)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_stop_async");
    if((error = dlerror()) != NULL) _libvlc_media_list_player_stop_async = (p_libvlc_media_list_player_stop_async)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_stop");

    _libvlc_video_new_viewpoint = (p_libvlc_video_new_viewpoint)dlsym(RTLD_DEFAULT, "libvlc_video_new_viewpoint");
    _libvlc_video_set_output_callbacks = (p_libvlc_video_set_output_callbacks)dlsym(RTLD_DEFAULT, "libvlc_video_set_output_callbacks");
    _libvlc_media_new_path = (p_libvlc_media_new_path)dlsym(RTLD_DEFAULT, "libvlc_media_new_path");
    _libvlc_media_player_select_tracks_by_ids = (p_libvlc_media_player_select_tracks_by_ids)dlsym(RTLD_DEFAULT, "libvlc_media_player_select_tracks_by_ids");
    _libvlc_media_add_option_flag = (p_libvlc_media_add_option_flag)dlsym(RTLD_DEFAULT, "libvlc_media_add_option_flag");
    _libvlc_media_player_set_xwindow = (p_libvlc_media_player_set_xwindow)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_xwindow");
    _libvlc_audio_set_channel = (p_libvlc_audio_set_channel)dlsym(RTLD_DEFAULT, "libvlc_audio_set_channel");
    _libvlc_media_player_get_role = (p_libvlc_media_player_get_role)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_role");
    _libvlc_media_list_add_media = (p_libvlc_media_list_add_media)dlsym(RTLD_DEFAULT, "libvlc_media_list_add_media");
    _libvlc_media_list_lock = (p_libvlc_media_list_lock)dlsym(RTLD_DEFAULT, "libvlc_media_list_lock");
    _libvlc_media_slaves_clear = (p_libvlc_media_slaves_clear)dlsym(RTLD_DEFAULT, "libvlc_media_slaves_clear");
    _libvlc_media_player_get_chapter_count_for_title = (p_libvlc_media_player_get_chapter_count_for_title)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_chapter_count_for_title");
    _libvlc_log_unset = (p_libvlc_log_unset)dlsym(RTLD_DEFAULT, "libvlc_log_unset");
    _libvlc_video_get_track = (p_libvlc_video_get_track)dlsym(RTLD_DEFAULT, "libvlc_video_get_track");
    _libvlc_clock = (p_libvlc_clock)dlsym(RTLD_DEFAULT, "libvlc_clock");
    _libvlc_renderer_discoverer_start = (p_libvlc_renderer_discoverer_start)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_start");
    _libvlc_video_get_spu = (p_libvlc_video_get_spu)dlsym(RTLD_DEFAULT, "libvlc_video_get_spu");
    _libvlc_set_user_agent = (p_libvlc_set_user_agent)dlsym(RTLD_DEFAULT, "libvlc_set_user_agent");
    _libvlc_log_set_file = (p_libvlc_log_set_file)dlsym(RTLD_DEFAULT, "libvlc_log_set_file");
    _libvlc_media_tracklist_delete = (p_libvlc_media_tracklist_delete)dlsym(RTLD_DEFAULT, "libvlc_media_tracklist_delete");
    _libvlc_media_discoverer_stop = (p_libvlc_media_discoverer_stop)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_stop");
    _libvlc_video_set_mouse_input = (p_libvlc_video_set_mouse_input)dlsym(RTLD_DEFAULT, "libvlc_video_set_mouse_input");
    _libvlc_media_list_event_manager = (p_libvlc_media_list_event_manager)dlsym(RTLD_DEFAULT, "libvlc_media_list_event_manager");
    _libvlc_log_get_object = (p_libvlc_log_get_object)dlsym(RTLD_DEFAULT, "libvlc_log_get_object");
    _libvlc_media_event_manager = (p_libvlc_media_event_manager)dlsym(RTLD_DEFAULT, "libvlc_media_event_manager");
    _libvlc_media_get_parsed_status = (p_libvlc_media_get_parsed_status)dlsym(RTLD_DEFAULT, "libvlc_media_get_parsed_status");
    _libvlc_video_get_cursor = (p_libvlc_video_get_cursor)dlsym(RTLD_DEFAULT, "libvlc_video_get_cursor");
    _libvlc_video_get_aspect_ratio = (p_libvlc_video_get_aspect_ratio)dlsym(RTLD_DEFAULT, "libvlc_video_get_aspect_ratio");
    _libvlc_media_set_meta = (p_libvlc_media_set_meta)dlsym(RTLD_DEFAULT, "libvlc_media_set_meta");
    _libvlc_media_player_get_position = (p_libvlc_media_player_get_position)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_position");
    _libvlc_media_list_new = (p_libvlc_media_list_new)dlsym(RTLD_DEFAULT, "libvlc_media_list_new");
    _libvlc_toggle_fullscreen = (p_libvlc_toggle_fullscreen)dlsym(RTLD_DEFAULT, "libvlc_toggle_fullscreen");
    _libvlc_video_filter_list_get = (p_libvlc_video_filter_list_get)dlsym(RTLD_DEFAULT, "libvlc_video_filter_list_get");
    _libvlc_vprinterr = (p_libvlc_vprinterr)dlsym(RTLD_DEFAULT, "libvlc_vprinterr");
    _libvlc_media_player_navigate = (p_libvlc_media_player_navigate)dlsym(RTLD_DEFAULT, "libvlc_media_player_navigate");
    _libvlc_dialog_post_login = (p_libvlc_dialog_post_login)dlsym(RTLD_DEFAULT, "libvlc_dialog_post_login");
    _libvlc_audio_equalizer_release = (p_libvlc_audio_equalizer_release)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_release");
    _libvlc_video_set_key_input = (p_libvlc_video_set_key_input)dlsym(RTLD_DEFAULT, "libvlc_video_set_key_input");
    _libvlc_video_set_scale = (p_libvlc_video_set_scale)dlsym(RTLD_DEFAULT, "libvlc_video_set_scale");
    _libvlc_set_fullscreen = (p_libvlc_set_fullscreen)dlsym(RTLD_DEFAULT, "libvlc_set_fullscreen");
    _libvlc_video_get_scale = (p_libvlc_video_get_scale)dlsym(RTLD_DEFAULT, "libvlc_video_get_scale");
    _libvlc_media_list_player_event_manager = (p_libvlc_media_list_player_event_manager)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_event_manager");
    _libvlc_media_list_player_is_playing = (p_libvlc_media_list_player_is_playing)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_is_playing");
    _libvlc_media_player_program_scrambled = (p_libvlc_media_player_program_scrambled)dlsym(RTLD_DEFAULT, "libvlc_media_player_program_scrambled");
    _libvlc_audio_output_device_list_get = (p_libvlc_audio_output_device_list_get)dlsym(RTLD_DEFAULT, "libvlc_audio_output_device_list_get");
    _libvlc_media_player_get_rate = (p_libvlc_media_player_get_rate)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_rate");
    _libvlc_video_take_snapshot = (p_libvlc_video_take_snapshot)dlsym(RTLD_DEFAULT, "libvlc_video_take_snapshot");
    _libvlc_media_list_index_of_item = (p_libvlc_media_list_index_of_item)dlsym(RTLD_DEFAULT, "libvlc_media_list_index_of_item");
    _libvlc_video_set_track = (p_libvlc_video_set_track)dlsym(RTLD_DEFAULT, "libvlc_video_set_track");
    _libvlc_renderer_item_icon_uri = (p_libvlc_renderer_item_icon_uri)dlsym(RTLD_DEFAULT, "libvlc_renderer_item_icon_uri");
    _libvlc_picture_list_count = (p_libvlc_picture_list_count)dlsym(RTLD_DEFAULT, "libvlc_picture_list_count");
    _libvlc_media_player_set_time = (p_libvlc_media_player_set_time)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_time");
    _libvlc_audio_output_device_list_release = (p_libvlc_audio_output_device_list_release)dlsym(RTLD_DEFAULT, "libvlc_audio_output_device_list_release");
    _libvlc_media_player_get_hwnd = (p_libvlc_media_player_get_hwnd)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_hwnd");
    _libvlc_media_player_is_seekable = (p_libvlc_media_player_is_seekable)dlsym(RTLD_DEFAULT, "libvlc_media_player_is_seekable");
    _libvlc_video_set_teletext = (p_libvlc_video_set_teletext)dlsym(RTLD_DEFAULT, "libvlc_video_set_teletext");
    _libvlc_video_set_marquee_int = (p_libvlc_video_set_marquee_int)dlsym(RTLD_DEFAULT, "libvlc_video_set_marquee_int");
    _libvlc_audio_output_device_get = (p_libvlc_audio_output_device_get)dlsym(RTLD_DEFAULT, "libvlc_audio_output_device_get");
    _libvlc_media_list_player_get_media_player = (p_libvlc_media_list_player_get_media_player)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_get_media_player");
    _libvlc_video_get_adjust_int = (p_libvlc_video_get_adjust_int)dlsym(RTLD_DEFAULT, "libvlc_video_get_adjust_int");
    _libvlc_media_player_get_track_from_id = (p_libvlc_media_player_get_track_from_id)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_track_from_id");
    _libvlc_audio_equalizer_set_preamp = (p_libvlc_audio_equalizer_set_preamp)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_set_preamp");
    _libvlc_retain = (p_libvlc_retain)dlsym(RTLD_DEFAULT, "libvlc_retain");
    _libvlc_media_get_tracklist = (p_libvlc_media_get_tracklist)dlsym(RTLD_DEFAULT, "libvlc_media_get_tracklist");
    _libvlc_chapter_descriptions_release = (p_libvlc_chapter_descriptions_release)dlsym(RTLD_DEFAULT, "libvlc_chapter_descriptions_release");
    _libvlc_video_get_spu_count = (p_libvlc_video_get_spu_count)dlsym(RTLD_DEFAULT, "libvlc_video_get_spu_count");
    _libvlc_audio_equalizer_new = (p_libvlc_audio_equalizer_new)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_new");
    _libvlc_picture_list_destroy = (p_libvlc_picture_list_destroy)dlsym(RTLD_DEFAULT, "libvlc_picture_list_destroy");
    _libvlc_media_discoverer_media_list = (p_libvlc_media_discoverer_media_list)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_media_list");
    _libvlc_media_discoverer_list_release = (p_libvlc_media_discoverer_list_release)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_list_release");
    _libvlc_audio_set_mute = (p_libvlc_audio_set_mute)dlsym(RTLD_DEFAULT, "libvlc_audio_set_mute");
    _libvlc_audio_equalizer_set_amp_at_index = (p_libvlc_audio_equalizer_set_amp_at_index)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_set_amp_at_index");
    _libvlc_media_player_get_state = (p_libvlc_media_player_get_state)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_state");
    _libvlc_audio_get_track_count = (p_libvlc_audio_get_track_count)dlsym(RTLD_DEFAULT, "libvlc_audio_get_track_count");
    _libvlc_media_player_get_nsobject = (p_libvlc_media_player_get_nsobject)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_nsobject");
    _libvlc_media_player_get_selected_track = (p_libvlc_media_player_get_selected_track)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_selected_track");
    _libvlc_media_player_get_tracklist = (p_libvlc_media_player_get_tracklist)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_tracklist");
    _libvlc_video_set_logo_int = (p_libvlc_video_set_logo_int)dlsym(RTLD_DEFAULT, "libvlc_video_set_logo_int");
    _libvlc_renderer_discoverer_stop = (p_libvlc_renderer_discoverer_stop)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_stop");
    _libvlc_media_parse = (p_libvlc_media_parse)dlsym(RTLD_DEFAULT, "libvlc_media_parse");
    _libvlc_new = (p_libvlc_new)dlsym(RTLD_DEFAULT, "libvlc_new");
    _libvlc_media_list_player_get_state = (p_libvlc_media_list_player_get_state)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_get_state");
    _libvlc_media_player_event_manager = (p_libvlc_media_player_event_manager)dlsym(RTLD_DEFAULT, "libvlc_media_player_event_manager");
    _libvlc_audio_equalizer_get_band_frequency = (p_libvlc_audio_equalizer_get_band_frequency)dlsym(RTLD_DEFAULT, "libvlc_audio_equalizer_get_band_frequency");
    _libvlc_media_get_mrl = (p_libvlc_media_get_mrl)dlsym(RTLD_DEFAULT, "libvlc_media_get_mrl");
    _libvlc_video_get_marquee_int = (p_libvlc_video_get_marquee_int)dlsym(RTLD_DEFAULT, "libvlc_video_get_marquee_int");
    _libvlc_track_description_list_release = (p_libvlc_track_description_list_release)dlsym(RTLD_DEFAULT, "libvlc_track_description_list_release");
    _libvlc_media_tracklist_at = (p_libvlc_media_tracklist_at)dlsym(RTLD_DEFAULT, "libvlc_media_tracklist_at");
    _libvlc_clearerr = (p_libvlc_clearerr)dlsym(RTLD_DEFAULT, "libvlc_clearerr");
    _libvlc_audio_output_list_release = (p_libvlc_audio_output_list_release)dlsym(RTLD_DEFAULT, "libvlc_audio_output_list_release");
    _libvlc_picture_get_stride = (p_libvlc_picture_get_stride)dlsym(RTLD_DEFAULT, "libvlc_picture_get_stride");
    _libvlc_release = (p_libvlc_release)dlsym(RTLD_DEFAULT, "libvlc_release");
    _libvlc_media_thumbnail_request_by_time = (p_libvlc_media_thumbnail_request_by_time)dlsym(RTLD_DEFAULT, "libvlc_media_thumbnail_request_by_time");
    _libvlc_video_get_track_description = (p_libvlc_video_get_track_description)dlsym(RTLD_DEFAULT, "libvlc_video_get_track_description");
    _libvlc_media_list_insert_media = (p_libvlc_media_list_insert_media)dlsym(RTLD_DEFAULT, "libvlc_media_list_insert_media");
    _libvlc_dialog_set_context = (p_libvlc_dialog_set_context)dlsym(RTLD_DEFAULT, "libvlc_dialog_set_context");
    _libvlc_log_set = (p_libvlc_log_set)dlsym(RTLD_DEFAULT, "libvlc_log_set");
    _libvlc_video_set_format = (p_libvlc_video_set_format)dlsym(RTLD_DEFAULT, "libvlc_video_set_format");
    _libvlc_add_intf = (p_libvlc_add_intf)dlsym(RTLD_DEFAULT, "libvlc_add_intf");
    _libvlc_media_new_callbacks = (p_libvlc_media_new_callbacks)dlsym(RTLD_DEFAULT, "libvlc_media_new_callbacks");
    _libvlc_media_list_unlock = (p_libvlc_media_list_unlock)dlsym(RTLD_DEFAULT, "libvlc_media_list_unlock");
    _libvlc_media_player_get_full_chapter_descriptions = (p_libvlc_media_player_get_full_chapter_descriptions)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_full_chapter_descriptions");
    _libvlc_audio_get_mute = (p_libvlc_audio_get_mute)dlsym(RTLD_DEFAULT, "libvlc_audio_get_mute");
    _libvlc_printerr = (p_libvlc_printerr)dlsym(RTLD_DEFAULT, "libvlc_printerr");
    _libvlc_media_player_new = (p_libvlc_media_player_new)dlsym(RTLD_DEFAULT, "libvlc_media_player_new");
    _libvlc_media_player_set_video_title_display = (p_libvlc_media_player_set_video_title_display)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_video_title_display");
    _libvlc_media_get_codec_description = (p_libvlc_media_get_codec_description)dlsym(RTLD_DEFAULT, "libvlc_media_get_codec_description");
    _libvlc_media_player_set_rate = (p_libvlc_media_player_set_rate)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_rate");
    _libvlc_video_set_deinterlace = (p_libvlc_video_set_deinterlace)dlsym(RTLD_DEFAULT, "libvlc_video_set_deinterlace");
    _libvlc_media_player_pause = (p_libvlc_media_player_pause)dlsym(RTLD_DEFAULT, "libvlc_media_player_pause");
    _libvlc_audio_output_list_get = (p_libvlc_audio_output_list_get)dlsym(RTLD_DEFAULT, "libvlc_audio_output_list_get");
    _libvlc_media_get_state = (p_libvlc_media_get_state)dlsym(RTLD_DEFAULT, "libvlc_media_get_state");
    _libvlc_audio_set_format_callbacks = (p_libvlc_audio_set_format_callbacks)dlsym(RTLD_DEFAULT, "libvlc_audio_set_format_callbacks");
    _libvlc_media_discoverer_new = (p_libvlc_media_discoverer_new)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_new");
    _libvlc_renderer_discoverer_event_manager = (p_libvlc_renderer_discoverer_event_manager)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_event_manager");
    _libvlc_media_slaves_release = (p_libvlc_media_slaves_release)dlsym(RTLD_DEFAULT, "libvlc_media_slaves_release");
    _libvlc_media_new_location = (p_libvlc_media_new_location)dlsym(RTLD_DEFAULT, "libvlc_media_new_location");
    _libvlc_media_list_set_media = (p_libvlc_media_list_set_media)dlsym(RTLD_DEFAULT, "libvlc_media_list_set_media");
    _libvlc_media_list_media = (p_libvlc_media_list_media)dlsym(RTLD_DEFAULT, "libvlc_media_list_media");
    _libvlc_media_tracks_get = (p_libvlc_media_tracks_get)dlsym(RTLD_DEFAULT, "libvlc_media_tracks_get");
    
    dlerror();
    _libvlc_media_parse_async = (p_libvlc_media_parse_async)dlsym(RTLD_DEFAULT, "libvlc_media_parse_async");
    if((error = dlerror()) != NULL) _libvlc_media_parse_async = (p_libvlc_media_parse_async)dlsym(RTLD_DEFAULT, "libvlc_media_parse");

    _libvlc_event_detach = (p_libvlc_event_detach)dlsym(RTLD_DEFAULT, "libvlc_event_detach");
    _libvlc_video_get_size = (p_libvlc_video_get_size)dlsym(RTLD_DEFAULT, "libvlc_video_get_size");
    _libvlc_media_discoverer_is_running = (p_libvlc_media_discoverer_is_running)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_is_running");
    _libvlc_renderer_item_release = (p_libvlc_renderer_item_release)dlsym(RTLD_DEFAULT, "libvlc_renderer_item_release");
    _libvlc_player_programlist_at = (p_libvlc_player_programlist_at)dlsym(RTLD_DEFAULT, "libvlc_player_programlist_at");
    _libvlc_dialog_dismiss = (p_libvlc_dialog_dismiss)dlsym(RTLD_DEFAULT, "libvlc_dialog_dismiss");
    _libvlc_delay = (p_libvlc_delay)dlsym(RTLD_DEFAULT, "libvlc_delay");
    _libvlc_picture_list_at = (p_libvlc_picture_list_at)dlsym(RTLD_DEFAULT, "libvlc_picture_list_at");
    _libvlc_media_retain = (p_libvlc_media_retain)dlsym(RTLD_DEFAULT, "libvlc_media_retain");
    _libvlc_media_player_get_title = (p_libvlc_media_player_get_title)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_title");
    _libvlc_media_get_meta = (p_libvlc_media_get_meta)dlsym(RTLD_DEFAULT, "libvlc_media_get_meta");
    _libvlc_media_list_player_next = (p_libvlc_media_list_player_next)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_next");
    _libvlc_media_new_as_node = (p_libvlc_media_new_as_node)dlsym(RTLD_DEFAULT, "libvlc_media_new_as_node");
    _libvlc_media_list_player_release = (p_libvlc_media_list_player_release)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_release");
    _libvlc_media_list_player_play = (p_libvlc_media_list_player_play)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_play");
    _libvlc_media_player_next_frame = (p_libvlc_media_player_next_frame)dlsym(RTLD_DEFAULT, "libvlc_media_player_next_frame");
    _libvlc_picture_get_width = (p_libvlc_picture_get_width)dlsym(RTLD_DEFAULT, "libvlc_picture_get_width");
    _libvlc_media_thumbnail_request_by_pos = (p_libvlc_media_thumbnail_request_by_pos)dlsym(RTLD_DEFAULT, "libvlc_media_thumbnail_request_by_pos");
    _libvlc_media_player_get_selected_program = (p_libvlc_media_player_get_selected_program)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_selected_program");
    _libvlc_media_list_player_previous = (p_libvlc_media_list_player_previous)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_previous");
    _libvlc_media_player_set_nsobject = (p_libvlc_media_player_set_nsobject)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_nsobject");
    _libvlc_media_save_meta = (p_libvlc_media_save_meta)dlsym(RTLD_DEFAULT, "libvlc_media_save_meta");
    _libvlc_media_player_new_from_media = (p_libvlc_media_player_new_from_media)dlsym(RTLD_DEFAULT, "libvlc_media_player_new_from_media");
    _libvlc_media_player_get_chapter_count = (p_libvlc_media_player_get_chapter_count)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_chapter_count");
    _libvlc_media_player_next_chapter = (p_libvlc_media_player_next_chapter)dlsym(RTLD_DEFAULT, "libvlc_media_player_next_chapter");
    _libvlc_audio_get_track_description = (p_libvlc_audio_get_track_description)dlsym(RTLD_DEFAULT, "libvlc_audio_get_track_description");
    _libvlc_media_list_player_set_pause = (p_libvlc_media_list_player_set_pause)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_set_pause");
    _libvlc_dialog_set_callbacks = (p_libvlc_dialog_set_callbacks)dlsym(RTLD_DEFAULT, "libvlc_dialog_set_callbacks");
    _libvlc_media_player_set_media = (p_libvlc_media_player_set_media)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_media");
    _libvlc_dialog_get_context = (p_libvlc_dialog_get_context)dlsym(RTLD_DEFAULT, "libvlc_dialog_get_context");
    _libvlc_get_version = (p_libvlc_get_version)dlsym(RTLD_DEFAULT, "libvlc_get_version");
    _libvlc_media_slaves_add = (p_libvlc_media_slaves_add)dlsym(RTLD_DEFAULT, "libvlc_media_slaves_add");
    _libvlc_errmsg = (p_libvlc_errmsg)dlsym(RTLD_DEFAULT, "libvlc_errmsg");
    _libvlc_audio_get_volume = (p_libvlc_audio_get_volume)dlsym(RTLD_DEFAULT, "libvlc_audio_get_volume");
    _libvlc_renderer_discoverer_list_release = (p_libvlc_renderer_discoverer_list_release)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_list_release");
    _libvlc_media_player_get_media = (p_libvlc_media_player_get_media)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_media");
    _libvlc_media_player_set_android_context = (p_libvlc_media_player_set_android_context)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_android_context");
    _libvlc_media_player_set_chapter = (p_libvlc_media_player_set_chapter)dlsym(RTLD_DEFAULT, "libvlc_media_player_set_chapter");
    _libvlc_media_list_remove_index = (p_libvlc_media_list_remove_index)dlsym(RTLD_DEFAULT, "libvlc_media_list_remove_index");
    _libvlc_media_player_get_program_from_id = (p_libvlc_media_player_get_program_from_id)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_program_from_id");
    _libvlc_picture_get_height = (p_libvlc_picture_get_height)dlsym(RTLD_DEFAULT, "libvlc_picture_get_height");
    _libvlc_video_set_crop_border = (p_libvlc_video_set_crop_border)dlsym(RTLD_DEFAULT, "libvlc_video_set_crop_border");
    _libvlc_media_parse_with_options = (p_libvlc_media_parse_with_options)dlsym(RTLD_DEFAULT, "libvlc_media_parse_with_options");
    _libvlc_media_player_retain = (p_libvlc_media_player_retain)dlsym(RTLD_DEFAULT, "libvlc_media_player_retain");
    _libvlc_video_get_track_count = (p_libvlc_video_get_track_count)dlsym(RTLD_DEFAULT, "libvlc_video_get_track_count");
    _libvlc_media_get_type = (p_libvlc_media_get_type)dlsym(RTLD_DEFAULT, "libvlc_media_get_type");
    _libvlc_audio_output_device_enum = (p_libvlc_audio_output_device_enum)dlsym(RTLD_DEFAULT, "libvlc_audio_output_device_enum");
    _libvlc_video_set_marquee_string = (p_libvlc_video_set_marquee_string)dlsym(RTLD_DEFAULT, "libvlc_video_set_marquee_string");
    _libvlc_audio_output_device_set = (p_libvlc_audio_output_device_set)dlsym(RTLD_DEFAULT, "libvlc_audio_output_device_set");
    _libvlc_picture_save = (p_libvlc_picture_save)dlsym(RTLD_DEFAULT, "libvlc_picture_save");
    _libvlc_set_app_id = (p_libvlc_set_app_id)dlsym(RTLD_DEFAULT, "libvlc_set_app_id");
    _libvlc_renderer_item_flags = (p_libvlc_renderer_item_flags)dlsym(RTLD_DEFAULT, "libvlc_renderer_item_flags");
    _libvlc_renderer_discoverer_new = (p_libvlc_renderer_discoverer_new)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_new");
    _libvlc_picture_retain = (p_libvlc_picture_retain)dlsym(RTLD_DEFAULT, "libvlc_picture_retain");
    _libvlc_renderer_item_hold = (p_libvlc_renderer_item_hold)dlsym(RTLD_DEFAULT, "libvlc_renderer_item_hold");
    _libvlc_video_get_logo_int = (p_libvlc_video_get_logo_int)dlsym(RTLD_DEFAULT, "libvlc_video_get_logo_int");
    _libvlc_video_set_format_callbacks = (p_libvlc_video_set_format_callbacks)dlsym(RTLD_DEFAULT, "libvlc_video_set_format_callbacks");
    _libvlc_media_player_previous_chapter = (p_libvlc_media_player_previous_chapter)dlsym(RTLD_DEFAULT, "libvlc_media_player_previous_chapter");
    _libvlc_get_fullscreen = (p_libvlc_get_fullscreen)dlsym(RTLD_DEFAULT, "libvlc_get_fullscreen");
    _libvlc_picture_get_time = (p_libvlc_picture_get_time)dlsym(RTLD_DEFAULT, "libvlc_picture_get_time");
    _libvlc_media_player_play = (p_libvlc_media_player_play)dlsym(RTLD_DEFAULT, "libvlc_media_player_play");
    _libvlc_media_discoverer_release = (p_libvlc_media_discoverer_release)dlsym(RTLD_DEFAULT, "libvlc_media_discoverer_release");
    _libvlc_audio_set_delay = (p_libvlc_audio_set_delay)dlsym(RTLD_DEFAULT, "libvlc_audio_set_delay");
    _libvlc_media_thumbnail_request_cancel = (p_libvlc_media_thumbnail_request_cancel)dlsym(RTLD_DEFAULT, "libvlc_media_thumbnail_request_cancel");
    _libvlc_media_subitems = (p_libvlc_media_subitems)dlsym(RTLD_DEFAULT, "libvlc_media_subitems");
    _libvlc_media_player_get_time = (p_libvlc_media_player_get_time)dlsym(RTLD_DEFAULT, "libvlc_media_player_get_time");
    _libvlc_media_slaves_get = (p_libvlc_media_slaves_get)dlsym(RTLD_DEFAULT, "libvlc_media_slaves_get");
    _libvlc_media_list_player_new = (p_libvlc_media_list_player_new)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_new");
    _libvlc_media_list_player_set_media_player = (p_libvlc_media_list_player_set_media_player)dlsym(RTLD_DEFAULT, "libvlc_media_list_player_set_media_player");
    _libvlc_get_changeset = (p_libvlc_get_changeset)dlsym(RTLD_DEFAULT, "libvlc_get_changeset");
    _libvlc_picture_get_buffer = (p_libvlc_picture_get_buffer)dlsym(RTLD_DEFAULT, "libvlc_picture_get_buffer");
    _libvlc_renderer_discoverer_release = (p_libvlc_renderer_discoverer_release)dlsym(RTLD_DEFAULT, "libvlc_renderer_discoverer_release");
    return NULL;
}