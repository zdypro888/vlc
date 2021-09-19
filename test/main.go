package main

import (
	"log"
	"os"
	"path"

	"github.com/kardianos/osext"
	"github.com/zdypro888/vlc"
)

// #cgo LDFLAGS: -Wl,-rpath,../lib
import "C"

func main() {
	folder, _ := osext.ExecutableFolder()

	os.Setenv("VLC_PLUGIN_PATH", path.Join(folder, "plugins"))
	// os.Setenv("VLC_DATA_PATH", path.Join(folder, "share"))
	// os.Setenv("VLC_LIB_PATH", path.Join(folder, "lib"))

	// Initialize libVLC. Additional command line arguments can be passed in
	// to libVLC by specifying them in the Init function.
	if err := vlc.Init(); err != nil {
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

}
