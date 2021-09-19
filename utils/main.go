package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strings"

	"modernc.org/cc/v3"
)

var parserTestBuiltin = `
#define __DI__
#define __FUNCTION__ __func__
#define __HI__
#define __PRETTY_FUNCTION__ __func__
#define __QI__
#define __SI__
#define __builtin_add_overflow(...) 0
#define __builtin_constant_p(x) (__builtin_constant_p_impl(0, x))
#define __builtin_expect(exp, c) (exp)
#define __builtin_mul_overflow(...) 0
#define __builtin_offsetof(type, member) ((__SIZE_TYPE__)&(((type*)0)->member))
#define __builtin_sub_overflow(...) 0
#define __builtin_va_arg(ap, type) ((type)__builtin_va_arg_impl(ap))
#define __builtin_va_end(ap)
#define __builtin_va_start(ap, v)
#define __declspec(...)
#define __extension__
#define __read_only__ 0
#define __signed signed
#define __sync_synchronize(...)
#define __word__
#define __write_only__ 0
#define asm __asm__

#ifndef __GNUC__
#define __attribute__(x)
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#endif

#ifdef __WCHAR_TYPE__
typedef __WCHAR_TYPE__ wchar_t;
#endif

typedef void * __builtin_va_list;

#if __SIZEOF_POINTER__ == 8
#else
typedef long double __float128;
#endif

#ifdef __UINT16_TYPE__
__UINT16_TYPE__ __builtin_bswap16 (__UINT16_TYPE__ x);
#endif

#ifdef __UINT32_TYPE__
__UINT32_TYPE__ __builtin_bswap32 (__UINT32_TYPE__ x);
#endif

#ifdef __UINT64_TYPE__
__UINT64_TYPE__ __builtin_bswap64 (__UINT64_TYPE__ x);
#endif

#ifdef __SIZEOF_INT128__
typedef __INT64_TYPE__ __int128_t[2];	//TODO
typedef __UINT64_TYPE__ __uint128_t[2];	//TODO
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
int gnu_printf(const char *format, ...);
int gnu_scanf(const char *format, ...);
int ms_scanf(const char *format, ...);
int ms_printf(const char *format, ...);
#endif

typedef struct { char real, imag; } __COMPLEX_CHAR_TYPE__;
typedef struct { double real, imag; } __COMPLEX_DOUBLE_TYPE__;
typedef struct { float real, imag; } __COMPLEX_FLOAT_TYPE__;
typedef struct { int real, imag; } __COMPLEX_INT_TYPE__;
typedef struct { long double real, imag; } __COMPLEX_LONG_DOUBLE_TYPE__;
typedef struct { long real, imag; } __COMPLEX_LONG_TYPE__;
typedef struct { long long real, imag; } __COMPLEX_LONG_LONG_TYPE__;
typedef struct { long long unsigned real, imag; } __COMPLEX_LONG_LONG_UNSIGNED_TYPE__;
typedef struct { long unsigned real, imag; } __COMPLEX_LONG_UNSIGNED_TYPE__;
typedef struct { short real, imag; } __COMPLEX_SHORT_TYPE__;
typedef struct { unsigned real, imag; } __COMPLEX_UNSIGNED_TYPE__;
typedef struct { unsigned short real, imag; } __COMPLEX_SHORT_UNSIGNED_TYPE__;

int __builtin_clzll (unsigned long long);
int __builtin_constant_p_impl(int, ...);
int __printf__ ( const char * format, ... );
int __scanf__ ( const char *format, ... );
void *__builtin_alloca (size_t);
void *__builtin_extract_return_addr (void *addr);
void *__builtin_frame_address (unsigned int level);
void *__builtin_malloc(size_t);
void *__builtin_stack_save(void);
void *__builtin_va_arg_impl(void* ap);

#define __INTMAX_TYPE__ long
#define __UINTMAX_TYPE__ unsigned long

#define TARGET_CPU_X86_64 1
#define TARGET_OS_UNIX 1

#define __x86_64__ 1

#define int_least8_t char
#define int_least16_t short
#define int_least32_t long
#define int_least64_t long long

#define uint_least8_t char
#define uint_least16_t short
#define uint_least32_t long
#define uint_least64_t long long

#define int_fast8_t char
#define int_fast16_t short
#define int_fast32_t long
#define int_fast64_t long long

#define uint_fast8_t char
#define uint_fast16_t short
#define uint_fast32_t long
#define uint_fast64_t long long

#define uint8_t char
#define uint16_t short
#define uint32_t long
#define uint64_t long long
`

func writeType(writer *bytes.Buffer, cct cc.Type) {
	if cct.Kind() == cc.Ptr {
		elem := cct.Elem()
		if elem.Kind() == cc.Function {
			writer.WriteString(cct.String())
			writer.WriteString(" ")
		} else {
			writeType(writer, elem)
			writer.WriteString("* ")
		}
	} else {
		writer.WriteString(cct.String())
		writer.WriteString(" ")
	}
}

func ccParser() {
	cfg := &cc.Config{PreprocessOnly: false}
	cfg.ABI, _ = cc.NewABIFromEnv()
	tran, err := cc.Translate(cfg,
		[]string{"/Users/zdypro/go/src/github.com/zdypro888/vlc/", "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.5/include/", "/Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/usr/include/"},
		[]string{"/Users/zdypro/go/src/github.com/zdypro888/vlc/", "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.5/include/", "/Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/usr/include/"},
		[]cc.Source{{Name: "pre.h", Value: parserTestBuiltin}, {Name: "/Users/zdypro/go/src/github.com/zdypro888/vlc/vlc/vlc.h", DoNotCache: true}})
	if err != nil {
		log.Println(err)
	} else {
		headerWriter := bytes.NewBuffer(nil)
		sourceWriter := bytes.NewBuffer(nil)
		sourceExecWriter := bytes.NewBuffer(nil)
		for key, nodes := range tran.Scope {
			if strings.HasPrefix(key.String(), "libvlc_") {
				for _, node := range nodes {
					switch value := node.(type) {
					case *cc.Enumerator:
						// log.Println(value)
					case *cc.EnumSpecifier:
					case *cc.StructOrUnionSpecifier:
					case *cc.Declarator:
						valueType := value.Type()
						if valueType.Kind() == cc.Function {
							sourceWriter.WriteString("typedef ")
							sourceExecWriter.WriteString("p_")
							sourceExecWriter.WriteString(key.String())
							sourceExecWriter.WriteString(" _")
							sourceExecWriter.WriteString(key.String())
							sourceExecWriter.WriteString(";\n")

							writeType(headerWriter, valueType.Result())
							writeType(sourceWriter, valueType.Result())
							writeType(sourceExecWriter, valueType.Result())

							headerWriter.WriteString("dynamic_")
							sourceWriter.WriteString(" (*p_")
							sourceExecWriter.WriteString("dynamic_")

							headerWriter.WriteString(key.String())
							sourceWriter.WriteString(key.String())
							sourceExecWriter.WriteString(key.String())

							headerWriter.WriteString("(")
							sourceWriter.WriteString(")(")
							sourceExecWriter.WriteString("(")

							pars := valueType.Parameters()
							for i, par := range pars {
								writeType(headerWriter, par.Type())
								writeType(sourceWriter, par.Type())
								writeType(sourceExecWriter, par.Type())
								headerWriter.WriteString(par.Name().String())
								sourceExecWriter.WriteString(par.Name().String())
								if i < len(pars)-1 {
									headerWriter.WriteString(", ")
									sourceWriter.WriteString(", ")
									sourceExecWriter.WriteString(", ")
								}
							}
							headerWriter.WriteString(");\n")
							sourceWriter.WriteString(");\n")
							sourceExecWriter.WriteString(") {\n")
							sourceExecWriter.WriteString("\t return ")
							sourceExecWriter.WriteString(" _")
							sourceExecWriter.WriteString(key.String())
							sourceExecWriter.WriteString("(")
							for i, par := range pars {
								sourceExecWriter.WriteString(par.Name().String())
								if i < len(pars)-1 {
									sourceExecWriter.WriteString(", ")
								}
							}
							sourceExecWriter.WriteString(");\n")
							sourceExecWriter.WriteString("}\n")
						}
					default:
						log.Printf("%v", node)
					}
				}
			}
		}
		log.Print(sourceExecWriter.String())
	}
}

func main() {
	names := []string{

		"libvlc_video_set_crop_window",
		"libvlc_media_list_retain",
		"libvlc_audio_set_volume_callback",
		"libvlc_audio_equalizer_get_preset_name",
		"libvlc_media_player_set_position",
		"libvlc_media_player_get_chapter",
		"libvlc_audio_toggle_mute",
		"libvlc_media_track_hold",
		"libvlc_picture_release",
		"libvlc_video_set_crop_ratio",
		"libvlc_media_player_select_tracks",
		"libvlc_video_set_aspect_ratio",
		"libvlc_media_list_release",
		"libvlc_media_get_duration",
		"libvlc_media_list_item_at_index",
		"libvlc_set_exit_handler",
		"libvlc_free",
		"libvlc_media_player_set_hwnd",
		"libvlc_media_parse_stop",
		"libvlc_media_player_set_renderer",
		"libvlc_media_list_player_play_item",
		"libvlc_dialog_post_action",
		"libvlc_media_player_get_full_title_descriptions",
		"libvlc_media_player_stop_async",
		"libvlc_player_programlist_delete",
		"libvlc_audio_equalizer_get_band_count",
		"libvlc_video_set_adjust_int",
		"libvlc_audio_get_track",
		"libvlc_audio_equalizer_get_preset_count",
		"libvlc_media_get_stats",
		"libvlc_media_set_user_data",
		"libvlc_media_player_unselect_track_type",
		"libvlc_media_list_player_set_playback_mode",
		"libvlc_audio_get_channel",
		"libvlc_media_player_can_pause",
		"libvlc_audio_filter_list_get",
		"libvlc_renderer_item_name",
		"libvlc_audio_set_volume",
		"libvlc_media_player_get_length",
		"libvlc_media_list_player_set_media_list",
		"libvlc_media_player_get_xwindow",
		"libvlc_audio_equalizer_get_preamp",
		"libvlc_media_is_parsed",
		"libvlc_video_get_adjust_float",
		"libvlc_player_programlist_count",
		"libvlc_media_thumbnail_request_destroy",
		"libvlc_media_player_select_track",
		"libvlc_video_set_spu_delay",
		"libvlc_media_add_option",
		"libvlc_get_compiler",
		"libvlc_media_duplicate",
		"libvlc_video_set_adjust_float",
		"libvlc_media_player_get_title_count",
		"libvlc_media_new_fd",
		"libvlc_renderer_item_type",
		"libvlc_media_player_get_programlist",
		"libvlc_media_list_count",
		"libvlc_media_discoverer_list_get",
		"libvlc_media_player_set_role",
		"libvlc_media_discoverer_start",
		"libvlc_video_get_spu_delay",
		"libvlc_media_get_user_data",
		"libvlc_audio_get_delay",
		"libvlc_module_description_list_release",
		"libvlc_video_update_viewpoint",
		"libvlc_video_get_spu_description",
		"libvlc_media_player_set_title",
		"libvlc_video_set_spu",
		"libvlc_picture_type",
		"libvlc_audio_output_set",
		"libvlc_audio_equalizer_new_from_preset",
		"libvlc_audio_set_track",
		"libvlc_media_player_has_vout",
		"libvlc_media_release",
		"libvlc_player_program_delete",
		"libvlc_audio_set_callbacks",
		"libvlc_audio_set_format",
		"libvlc_media_player_select_program_id",
		"libvlc_media_tracks_release",
		"libvlc_audio_equalizer_get_amp_at_index",
		"libvlc_media_track_release",
		"libvlc_media_player_is_playing",
		"libvlc_title_descriptions_release",
		"libvlc_media_list_is_readonly",
		"libvlc_video_set_spu_text_scale",
		"libvlc_media_player_add_slave",
		"libvlc_log_get_context",
		"libvlc_media_player_release",
		"libvlc_video_set_logo_string",
		"libvlc_video_get_spu_text_scale",
		"libvlc_media_list_player_retain",
		"libvlc_playlist_play",
		"libvlc_media_list_player_pause",
		"libvlc_media_player_set_equalizer",
		"libvlc_media_list_player_play_item_at_index",
		"libvlc_media_tracklist_count",
		"libvlc_video_set_callbacks",
		"libvlc_video_get_teletext",
		"libvlc_event_attach",
		"libvlc_renderer_discoverer_list_get",
		"libvlc_media_player_set_pause",
		"libvlc_media_list_player_stop_async",
		"libvlc_video_new_viewpoint",
		"libvlc_video_set_output_callbacks",
		"libvlc_media_new_path",
		"libvlc_media_player_select_tracks_by_ids",
		"libvlc_media_add_option_flag",
		"libvlc_media_player_set_xwindow",
		"libvlc_audio_set_channel",
		"libvlc_media_player_get_role",
		"libvlc_media_list_add_media",
		"libvlc_media_list_lock",
		"libvlc_media_slaves_clear",
		"libvlc_media_player_get_chapter_count_for_title",
		"libvlc_log_unset",
		"libvlc_video_get_track",
		"libvlc_clock",
		"libvlc_renderer_discoverer_start",
		"libvlc_video_get_spu",
		"libvlc_set_user_agent",
		"libvlc_log_set_file",
		"libvlc_media_tracklist_delete",
		"libvlc_media_discoverer_stop",
		"libvlc_video_set_mouse_input",
		"libvlc_media_list_event_manager",
		"libvlc_log_get_object",
		"libvlc_media_event_manager",
		"libvlc_media_get_parsed_status",
		"libvlc_video_get_cursor",
		"libvlc_video_get_aspect_ratio",
		"libvlc_media_set_meta",
		"libvlc_media_player_get_position",
		"libvlc_media_list_new",
		"libvlc_toggle_fullscreen",
		"libvlc_video_filter_list_get",
		"libvlc_vprinterr",
		"libvlc_media_player_navigate",
		"libvlc_dialog_post_login",
		"libvlc_audio_equalizer_release",
		"libvlc_video_set_key_input",
		"libvlc_video_set_scale",
		"libvlc_set_fullscreen",
		"libvlc_video_get_scale",
		"libvlc_media_list_player_event_manager",
		"libvlc_media_list_player_is_playing",
		"libvlc_media_player_program_scrambled",
		"libvlc_audio_output_device_list_get",
		"libvlc_media_player_get_rate",
		"libvlc_video_take_snapshot",
		"libvlc_media_list_index_of_item",
		"libvlc_video_set_track",
		"libvlc_renderer_item_icon_uri",
		"libvlc_picture_list_count",
		"libvlc_media_player_set_time",
		"libvlc_audio_output_device_list_release",
		"libvlc_media_player_get_hwnd",
		"libvlc_media_player_is_seekable",
		"libvlc_video_set_teletext",
		"libvlc_video_set_marquee_int",
		"libvlc_audio_output_device_get",
		"libvlc_media_list_player_get_media_player",
		"libvlc_video_get_adjust_int",
		"libvlc_media_player_get_track_from_id",
		"libvlc_audio_equalizer_set_preamp",
		"libvlc_retain",
		"libvlc_media_get_tracklist",
		"libvlc_chapter_descriptions_release",
		"libvlc_video_get_spu_count",
		"libvlc_audio_equalizer_new",
		"libvlc_picture_list_destroy",
		"libvlc_media_discoverer_media_list",
		"libvlc_media_discoverer_list_release",
		"libvlc_audio_set_mute",
		"libvlc_audio_equalizer_set_amp_at_index",
		"libvlc_media_player_get_state",
		"libvlc_audio_get_track_count",
		"libvlc_media_player_get_nsobject",
		"libvlc_media_player_get_selected_track",
		"libvlc_media_player_get_tracklist",
		"libvlc_video_set_logo_int",
		"libvlc_renderer_discoverer_stop",
		"libvlc_media_parse",
		"libvlc_new",
		"libvlc_media_list_player_get_state",
		"libvlc_media_player_event_manager",
		"libvlc_audio_equalizer_get_band_frequency",
		"libvlc_media_get_mrl",
		"libvlc_video_get_marquee_int",
		"libvlc_track_description_list_release",
		"libvlc_media_tracklist_at",
		"libvlc_clearerr",
		"libvlc_audio_output_list_release",
		"libvlc_picture_get_stride",
		"libvlc_release",
		"libvlc_media_thumbnail_request_by_time",
		"libvlc_video_get_track_description",
		"libvlc_media_list_insert_media",
		"libvlc_dialog_set_context",
		"libvlc_log_set",
		"libvlc_video_set_format",
		"libvlc_add_intf",
		"libvlc_media_new_callbacks",
		"libvlc_media_list_unlock",
		"libvlc_media_player_get_full_chapter_descriptions",
		"libvlc_audio_get_mute",
		"libvlc_printerr",
		"libvlc_media_player_new",
		"libvlc_media_player_set_video_title_display",
		"libvlc_media_get_codec_description",
		"libvlc_media_player_set_rate",
		"libvlc_video_set_deinterlace",
		"libvlc_media_player_pause",
		"libvlc_audio_output_list_get",
		"libvlc_media_get_state",
		"libvlc_audio_set_format_callbacks",
		"libvlc_media_discoverer_new",
		"libvlc_renderer_discoverer_event_manager",
		"libvlc_media_slaves_release",
		"libvlc_media_new_location",
		"libvlc_media_list_set_media",
		"libvlc_media_list_media",
		"libvlc_media_tracks_get",
		"libvlc_media_parse_async",
		"libvlc_event_detach",
		"libvlc_video_get_size",
		"libvlc_media_discoverer_is_running",
		"libvlc_renderer_item_release",
		"libvlc_player_programlist_at",
		"libvlc_dialog_dismiss",
		"libvlc_delay",
		"libvlc_picture_list_at",
		"libvlc_media_retain",
		"libvlc_media_player_get_title",
		"libvlc_media_get_meta",
		"libvlc_media_list_player_next",
		"libvlc_media_new_as_node",
		"libvlc_media_list_player_release",
		"libvlc_media_list_player_play",
		"libvlc_media_player_next_frame",
		"libvlc_picture_get_width",
		"libvlc_media_thumbnail_request_by_pos",
		"libvlc_media_player_get_selected_program",
		"libvlc_media_list_player_previous",
		"libvlc_media_player_set_nsobject",
		"libvlc_media_save_meta",
		"libvlc_media_player_new_from_media",
		"libvlc_media_player_get_chapter_count",
		"libvlc_media_player_next_chapter",
		"libvlc_audio_get_track_description",
		"libvlc_media_list_player_set_pause",
		"libvlc_dialog_set_callbacks",
		"libvlc_media_player_set_media",
		"libvlc_dialog_get_context",
		"libvlc_get_version",
		"libvlc_media_slaves_add",
		"libvlc_errmsg",
		"libvlc_audio_get_volume",
		"libvlc_renderer_discoverer_list_release",
		"libvlc_media_player_get_media",
		"libvlc_media_player_set_android_context",
		"libvlc_media_player_set_chapter",
		"libvlc_media_list_remove_index",
		"libvlc_media_player_get_program_from_id",
		"libvlc_picture_get_height",
		"libvlc_video_set_crop_border",
		"libvlc_media_parse_with_options",
		"libvlc_media_player_retain",
		"libvlc_video_get_track_count",
		"libvlc_media_get_type",
		"libvlc_audio_output_device_enum",
		"libvlc_video_set_marquee_string",
		"libvlc_audio_output_device_set",
		"libvlc_picture_save",
		"libvlc_set_app_id",
		"libvlc_renderer_item_flags",
		"libvlc_renderer_discoverer_new",
		"libvlc_picture_retain",
		"libvlc_renderer_item_hold",
		"libvlc_video_get_logo_int",
		"libvlc_video_set_format_callbacks",
		"libvlc_media_player_previous_chapter",
		"libvlc_get_fullscreen",
		"libvlc_picture_get_time",
		"libvlc_media_player_play",
		"libvlc_media_discoverer_release",
		"libvlc_audio_set_delay",
		"libvlc_media_thumbnail_request_cancel",
		"libvlc_media_subitems",
		"libvlc_media_player_get_time",
		"libvlc_media_slaves_get",
		"libvlc_media_list_player_new",
		"libvlc_media_list_player_set_media_player",
		"libvlc_get_changeset",
		"libvlc_picture_get_buffer",
		"libvlc_renderer_discoverer_release",
	}
	filepath.Walk("../", func(path string, info os.FileInfo, err error) error {
		if err == nil && !info.IsDir() && filepath.Ext(path) == ".go" {
			log.Printf("文件: %s", path)
			filedata, err := ioutil.ReadFile(path)
			if err != nil {
				return err
			}
			filesource := string(filedata)
			for _, name := range names {
				filesource = strings.ReplaceAll(filesource, fmt.Sprintf("C.%s(", name), fmt.Sprintf("C.dynamic_%s(", name))
			}
			ioutil.WriteFile(path, []byte(filesource), 0644)
		}
		return nil
	})
	log.Println(names)
}
