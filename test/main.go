package main

import (
	"log"
	"os"
	"path"
	"path/filepath"

	"github.com/kardianos/osext"
	"github.com/zdypro888/vlc"
)

// #cgo LDFLAGS: -Wl,-rpath,./lib
import "C"

func main() {
	folder, _ := osext.ExecutableFolder()

	os.Setenv("VLC_PLUGIN_PATH", path.Join(folder, "plugins"))
	// os.Setenv("VLC_DATA_PATH", path.Join(folder, "share"))
	// os.Setenv("VLC_LIB_PATH", path.Join(folder, "lib"))

	// Initialize libVLC. Additional command line arguments can be passed in
	// to libVLC by specifying them in the Init function.
	if err := vlc.Init(filepath.Join(folder, "lib", "libvlc.dylib"), "--quiet"); err != nil {
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

	// Create new media instance from screen.
	screenOpts := &vlc.MediaScreenOptions{
		// Captured area left edge. Default: 0.
		X: 100,

		// Captured area top edge. Default: 0.
		Y: 100,

		// Captured area width. Default: 0 (full screen width).
		Width: 200,

		// Captured area height. Default: 0 (full screen height).
		Height: 200, // 0 for full screen height.

		// Frame rate. Default: 0.
		FPS: 30.0,

		// Captured area follows the mouse cursor. Default: false.
		FollowMouse: true,
	}

	media, err := vlc.NewMediaFromScreen(screenOpts)
	if err != nil {
		log.Fatal(err)
	}
	defer media.Release()

	// Set player media.
	if err := player.SetMedia(media); err != nil {
		log.Fatal(err)
	}

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
	if err = player.Play(); err != nil {
		log.Fatal(err)
	}

	<-quit
}
