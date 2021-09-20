package main

import (
	"log"
	"os"
	"path"
	"path/filepath"
	"runtime"
	"unsafe"

	"github.com/kardianos/osext"
	"github.com/zdypro888/vlc"
)

/*
#cgo CFLAGS: -x objective-c -DGL_SILENCE_DEPRECATION
#cgo LDFLAGS: -framework Cocoa -Wl,-rpath,./lib
#import <Cocoa/Cocoa.h>
#include <pthread.h>

void runApp(void);
void stopApp(void);
uint64 threadID();

void onRuning(void *);
*/
import "C"

var initThreadID uint64

func init() {
	runtime.LockOSThread()
	initThreadID = uint64(C.threadID())
}
func main() {
	if tid := uint64(C.threadID()); tid != initThreadID {
		log.Fatalf("app.Main called on thread %d, but app.init ran on %d", tid, initThreadID)
	}

	C.runApp()
}

//export onRuning
func onRuning(aDrawable unsafe.Pointer) {
	go vlcPlay(aDrawable)
}
func vlcPlay(aDrawable unsafe.Pointer) {
	folder, _ := osext.ExecutableFolder()
	os.Setenv("VLC_PLUGIN_PATH", path.Join(folder, "plugins"))
	// os.Setenv("VLC_DATA_PATH", path.Join(folder, "share"))
	// os.Setenv("VLC_LIB_PATH", path.Join(folder, "lib"))

	// Initialize libVLC. Additional command line arguments can be passed in
	// to libVLC by specifying them in the Init function.
	if err := vlc.Init(filepath.Join(folder, "lib", "libvlc.dylib"),
		"--play-and-pause",
		"--no-color",
		"--no-video-title-show",
		"--verbose=4",
		"--no-sout-keep",
		"--vout=macosx",
		"--text-renderer=freetype",
		"--extraintf=macosx_dialog_provider",
		"--audio-resampler=soxr"); err != nil {
		log.Fatal(err)
	}
	defer vlc.Release()

	// Create a new player.
	player, err := vlc.NewPlayer()
	if err != nil {
		log.Fatal(err)
	}
	defer func() {
		player.Stop()
		player.Release()
	}()
	player.SetNSObject(uintptr(aDrawable))

	// Add a media file from path or from URL.
	// Set player media from path:
	// media, err := player.LoadMediaFromPath("localpath/test.mp4")
	// Set player media from URL:
	media, err := player.LoadMediaFromURL("http://stream-uk1.radioparadise.com/mp3-32")
	if err != nil {
		log.Fatal(err)
	}
	defer media.Release()

	// Retrieve player event manager.
	manager, err := player.EventManager()
	if err != nil {
		log.Fatal(err)
	}

	// Register the media end reached event with the event manager.
	quit := make(chan struct{})
	eventCallback := func(event vlc.Event, userData interface{}) {
		close(quit)
	}

	eventID, err := manager.Attach(vlc.MediaPlayerEndReached, eventCallback, nil)
	if err != nil {
		log.Fatal(err)
	}
	defer manager.Detach(eventID)

	// Start playing the media.
	err = player.Play()
	if err != nil {
		log.Fatal(err)
	}

	<-quit
}
