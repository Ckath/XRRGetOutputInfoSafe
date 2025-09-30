#define _GNU_SOURCE /* for RTLD_NEXT */
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <dlfcn.h>

static XRROutputInfo *
(*XRRGetOutputInfo_orig)(Display *, XRRScreenResources *, RROutput) = NULL;


XRROutputInfo *
XRRGetOutputInfo(Display *dpy, XRRScreenResources *resources, RROutput output)
{
	/* get original function */
	if (!XRRGetOutputInfo_orig) {
		XRRGetOutputInfo_orig = dlsym(RTLD_NEXT, "XRRGetOutputInfo");
	}
	
	/* safeguard against invalid display */
	if (!dpy) {
		printf("XRRGetOutputInfo: display NULL, ignoring\n");
		return NULL;
	}
	/* safeguard against invalid resources */
	if (!resources) {
		printf("XRRGetOutputInfo: resources NULL, ignoring\n");
		return NULL;
	}
	/* safeguard against incorrect output */
	if (!output) {
		printf("XRRGetOutputInfo: output 0, ignoring\n");
		return NULL;
	}
	for (int i = 0; i <= resources->noutput; ++i) {
		/* out of valid outputs */
		if (i == resources->noutput) {
			printf("XRRGetOutputInfo: out of range output, ignoring\n");
			return NULL;
		} else if (output == resources->outputs[i]) {
			break;
		}
	}

	/* go on as usual when everything is checked */
	return XRRGetOutputInfo_orig(dpy, resources, output);
}
