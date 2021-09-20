//go:build darwin || linux

package vlc

import (
	"fmt"
	"unsafe"
)

func LoadLibrary(libs []string) error {
	for _, lib := range libs {
		clib := C.CString(lib)
		if dhandle := C.dlopen(clib, C.RTLD_LAZY); dhandle == nil {
			return fmt.Errorf("load: %s faild: %s", lib, C.GoString(C.dlerror()))
		}
		C.free(unsafe.Pointer(clib))
	}
	return nil
}
