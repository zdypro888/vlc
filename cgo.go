package vlc

// #cgo LDFLAGS: -Llib -lvlc -Wl,-rpath,$ORIGIN/lib
// #include <vlc/vlc.h>
// #include <stdlib.h>
import "C"
