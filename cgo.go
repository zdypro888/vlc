package vlc

// #cgo LDFLAGS: -L${SRCDIR}/lib -lvlc -Wl,-rpath,$ORIGIN/lib
// #cgo CFLAGS: -Wdeprecated-declarations
// #include <vlc/vlc.h>
// #include <stdlib.h>
import "C"
