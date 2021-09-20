//go:build darwin && !ios

#include "_cgo_export.h"
#include <stdlib.h>
#include <locale.h>
#include <signal.h>
#include <string.h>

#import <CoreFoundation/CoreFoundation.h>
#import <Cocoa/Cocoa.h>

/**
 * Handler called when VLC asks to terminate the program.
 */
static void vlc_terminate(void *data)
{
    (void)data;
    dispatch_async(dispatch_get_main_queue(), ^{
        if (NSApp == nil) {
            CFRunLoopStop(CFRunLoopGetCurrent());
        } else {

            [NSApp stop:nil];
            NSEvent* event = [NSEvent otherEventWithType:NSApplicationDefined
                                                location:NSMakePoint(0,0)
                                           modifierFlags:0
                                               timestamp:0.0
                                            windowNumber:0
                                                 context:nil
                                                 subtype:0
                                                   data1:0
                                                   data2:0];
            [NSApp postEvent:event atStart:YES];
        }
    });
}

int AppRun(int i_argc, const char *ppsz_argv[])
{
    /* The so-called POSIX-compliant MacOS X reportedly processes SIGPIPE even
     * if it is blocked in all thread.
     * Note: this is NOT an excuse for not protecting against SIGPIPE. If
     * LibVLC runs outside of VLC, we cannot rely on this code snippet. */
    signal(SIGPIPE, SIG_IGN);
    /* Restore SIGCHLD in case our parent process ignores it. */
    signal(SIGCHLD, SIG_DFL);

#ifdef TOP_BUILDDIR
    setenv("VLC_PLUGIN_PATH", TOP_BUILDDIR"/modules", 1);
    setenv("VLC_DATA_PATH", TOP_SRCDIR"/share", 1);
#endif

#ifndef ALLOW_RUN_AS_ROOT
    if (geteuid() == 0)
    {
        fprintf(stderr, "VLC is not supposed to be run as root. Sorry.\n"
        "If you need to use real-time priorities and/or privileged TCP ports\n"
        "you can use %s-wrapper (make sure it is Set-UID root and\n"
        "cannot be run by non-trusted users first).\n", ppsz_argv[0]);
        return 1;
    }
#endif

    setlocale(LC_ALL, "");

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGPIPE);
    sigaddset(&set, SIGCHLD);
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    /* Handle signals with GCD */
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_source_t sigIntSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGINT, 0, queue);
    dispatch_source_t sigTermSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGTERM, 0, queue);
    dispatch_source_t sigChldSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, SIGCHLD, 0, queue);

    if (!sigIntSource || !sigTermSource || !sigChldSource)
        abort();

    dispatch_source_set_event_handler(sigIntSource, ^{
        vlc_terminate(nil);
    });
    dispatch_source_set_event_handler(sigTermSource, ^{
        vlc_terminate(nil);
    });

    dispatch_source_set_event_handler(sigChldSource, ^{
        int status;
        while(waitpid(-1, &status, WNOHANG) > 0);
    });

    dispatch_resume(sigIntSource);
    dispatch_resume(sigTermSource);
    dispatch_resume(sigChldSource);


    /* Handle parameters */
    const char *argv[i_argc + 2];
    int argc = 0;

    argv[argc++] = "--no-ignore-config";
    argv[argc++] = "--media-library";

    /* overwrite system language on Mac */
    char *lang = NULL;

    for (int i = 0; i < i_argc; i++) {
        if (!strncmp(ppsz_argv[i], "--language", 10)) {
            lang = strstr(ppsz_argv[i], "=");
            ppsz_argv++, i_argc--;
            continue;
        }
    }
    if (lang && strncmp( lang, "auto", 4 )) {
        char tmp[11];
        snprintf(tmp, 11, "LANG%s", lang);
        putenv(tmp);
    }

    if (!lang) {
        CFStringRef language;
        language = (CFStringRef)CFPreferencesCopyAppValue(CFSTR("language"), kCFPreferencesCurrentApplication);
        if (language) {
            CFIndex length = CFStringGetLength(language) + 1;
            if (length > 0) {
                CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
                lang = (char *)malloc(maxSize);
                if(lang) {
                    CFStringGetCString(language, lang, maxSize - 1, kCFStringEncodingUTF8);
                    if (strncmp( lang, "auto", 4 )) {
                        char tmp[11];
                        snprintf(tmp, 11, "LANG=%s", lang);
                        putenv(tmp);
                    }
                }
                free(lang);
            }
            CFRelease(language);
        }
    }

    ppsz_argv++; i_argc--; /* skip executable path */
    if (i_argc >= 1 && !strncmp(*ppsz_argv, "-psn" , 4))
        ppsz_argv++, i_argc--;
    memcpy (argv + argc, ppsz_argv, i_argc * sizeof(*argv));
    argc += i_argc;
    argv[argc] = NULL;

	int ret = 1;
	onRuning(argc, &argv);
	
    /* Initialize libvlc */
    // libvlc_instance_t *vlc = libvlc_new(argc, argv);
    // if (vlc == NULL)
    //     return 1;

    // int ret = 1;
    // libvlc_set_exit_handler(vlc, vlc_terminate, NULL);
    // libvlc_set_app_id(vlc, "org.VideoLAN.VLC", PACKAGE_VERSION, PACKAGE_NAME);
    // libvlc_set_user_agent(vlc, "VLC media player", "VLC/"PACKAGE_VERSION);

    // libvlc_add_intf(vlc, "hotkeys,none");

    // if (libvlc_add_intf(vlc, NULL))
    //     goto out;
    // libvlc_playlist_play(vlc, -1, 0, NULL);


    @autoreleasepool {
        if(NSApp == nil) {
            CFRunLoopRun();
        } else {
            [NSApp run];
        }
    }

    ret = 0;
    /* Cleanup */
out:
    dispatch_release(sigIntSource);
    dispatch_release(sigTermSource);
    dispatch_release(sigChldSource);
    // libvlc_release(vlc);
    return ret;
}
