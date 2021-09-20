package vlc

/*
#cgo LDFLAGS: -ldl
#cgo CFLAGS: -Wno-deprecated-declarations
#include "dynamic.h"
#include <stdlib.h>
#include <dlfcn.h>
*/
import "C"
import (
	"fmt"
	"unsafe"
)

type instance struct {
	handle  *C.libvlc_instance_t
	events  *eventRegistry
	objects *objectRegistry
}

func (i *instance) assertInit() error {
	if i == nil || i.handle == nil {
		return ErrModuleNotInitialized
	}
	return nil
}

var inst *instance

// Init creates an instance of the libVLC module.
// Must be called only once and the module instance must be released using
// the Release function.
func Init(libs []string, args ...string) error {
	if inst != nil {
		return nil
	}
	for _, lib := range libs {
		clib := C.CString(lib)
		if dhandle := C.dlopen(clib, C.RTLD_LAZY); dhandle == nil {
			return fmt.Errorf("load: %s faild: %s", lib, C.GoString(C.dlerror()))
		}
		C.free(unsafe.Pointer(clib))
	}
	errchar := C.dynamic_load()
	if errchar != nil {
		return fmt.Errorf("can not load: %s", C.GoString(errchar))
	}
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

	handle := C.dynamic_libvlc_new(C.int(argc), *(***C.char)(unsafe.Pointer(&argv)))
	if handle == nil {
		return errOrDefault(getError(), ErrModuleInitialize)
	}

	inst = &instance{
		handle:  handle,
		events:  newEventRegistry(),
		objects: newObjectRegistry(),
	}

	return nil
}

// Release destroys the instance created by the Init function.
func Release() error {
	if inst == nil {
		return nil
	}

	C.dynamic_libvlc_release(inst.handle)
	inst = nil

	return getError()
}

// Version returns details regarding the version of the libVLC module.
func Version() VersionInfo {
	return moduleVersion
}

// SetAppName sets the human-readable application name and the HTTP user agent.
// The specified user agent is used when a protocol requires it.
func SetAppName(name, userAgent string) error {
	if err := inst.assertInit(); err != nil {
		return err
	}

	cName, cUserAgent := C.CString(name), C.CString(userAgent)
	C.dynamic_libvlc_set_user_agent(inst.handle, cName, cUserAgent)

	C.free(unsafe.Pointer(cName))
	C.free(unsafe.Pointer(cUserAgent))
	return nil
}

// SetAppID sets metadata for identifying the application.
func SetAppID(id, version, icon string) error {
	if err := inst.assertInit(); err != nil {
		return err
	}

	cID, cVersion, cIcon := C.CString(id), C.CString(version), C.CString(icon)
	C.dynamic_libvlc_set_app_id(inst.handle, cID, cVersion, cIcon)

	C.free(unsafe.Pointer(cID))
	C.free(unsafe.Pointer(cVersion))
	C.free(unsafe.Pointer(cIcon))
	return nil
}

// StartUserInterface attempts to start a user interface for the libVLC
// instance. Pass an empty string as the name parameter in order to start
// the default interface.
func StartUserInterface(name string) error {
	if err := inst.assertInit(); err != nil {
		return err
	}

	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	if C.dynamic_libvlc_add_intf(inst.handle, cName) < 0 {
		return errOrDefault(getError(), ErrUserInterfaceStart)
	}

	return nil
}
