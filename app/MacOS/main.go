package main

import (
	"log"
	"os"
	"path"
	"path/filepath"
	"unsafe"

	"github.com/kardianos/osext"
	"github.com/zdypro888/vlc"
)

/*
#cgo CFLAGS: -x objective-c
#cgo LDFLAGS: -framework CoreFoundation -framework Cocoa
#import <Cocoa/Cocoa.h>
#include <pthread.h>

int AppRun(int argc, const char *argv[]);

void onRuning(int argc, char *argv[]);
*/
import "C"

//LDFAGS  -Wl,-rpath,/executable_path/lib -Wl,-rpath,/executable_path/plugins  -F ../Frameworks -framework Breakpad

func main() {
	args := os.Args
	argc := len(args)
	argv := make([]*C.char, argc)

	for i, arg := range args {
		argv[i] = C.CString(arg)
	}
	defer func() {
		for i := range argv {
			C.free(unsafe.Pointer(argv[i]))
		}
	}()
	C.AppRun(C.int(argc), *(***C.char)(unsafe.Pointer(&argv)))
}

//export onRuning
func onRuning(argc C.int, argv **C.char) {
	length := int(argc)
	tmpslice := (*[1 << 30]*C.char)(unsafe.Pointer(argv))[:length:length]
	gostrings := make([]string, length)
	for i, s := range tmpslice {
		gostrings[i] = C.GoString(s)
	}
	log.Println(gostrings)
	folder, _ := osext.ExecutableFolder()
	os.Setenv("VLC_PLUGIN_PATH", path.Join(folder, "plugins"))
	os.Setenv("VLC_DATA_PATH", path.Join(folder, "share"))
	// os.Setenv("VLC_LIB_PATH", path.Join(folder, "lib"))
	os.Setenv("LANG", "zh_CN")

	vlcPlay(gostrings)
}

func vlcPlay(args []string) {
	folder, _ := osext.ExecutableFolder()
	// Initialize libVLC. Additional command line arguments can be passed in
	// to libVLC by specifying them in the Init function.
	args = append(args, "--verbose=4")
	if err := vlc.LoadLibrary([]string{filepath.Join(folder, "lib", "libvlccore.dylib"), filepath.Join(folder, "lib", "libvlc.dylib")}); err != nil {
		log.Fatal(err)
	}
	if err := vlc.Init(args...); err != nil {
		log.Fatal(err)
	}
	// defer vlc.Release()
	vlc.SetAppID("org.VideoLAN.VLC", "3.0.16", "GoVLC")
	vlc.SetAppName("GoVLC", "VLC/Go")
	vlc.StartUserInterface("hotkeys,none")
	vlc.StartUserInterface("")
	vlc.StartPlayPlaylist()

	// Create a new player.
	// player, err := vlc.NewPlayer()
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// defer func() {
	// 	player.Stop()
	// 	player.Release()
	// }()
	// err = player.SetNSObject(uintptr(aDrawable))
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// equalizer, err := vlc.NewEqualizer()
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// player.SetEqualizer(equalizer)
	// _, medias, err := vclouder.MediaQuery(1, 1, 0)
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// vmedia := (*vclouder.Media)(medias[0])
	// vstream, err := vmedia.Open(false, 10*time.Minute)
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// media, err := player.LoadMediaFromReadSeeker(vstream)
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// defer media.Release()
	// // Retrieve player event manager.
	// manager, err := player.EventManager()
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// // Register the media end reached event with the event manager.
	// quit := make(chan struct{})
	// eventCallback := func(event vlc.Event, userData interface{}) {
	// 	close(quit)
	// }
	// eventID, err := manager.Attach(vlc.MediaPlayerEndReached, eventCallback, nil)
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// defer manager.Detach(eventID)
	// // Start playing the media.
	// err = player.Play()
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// <-quit
}
