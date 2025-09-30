# XRRGetOutputInfoSafe
a little library override to test incorrect usage of XRRGetOutputInfo, it will return a clean NULL pointer instead of crashing the whole application on an x error failed request.

currently happening in the warthunder launcher

## building
```
# build the XRRGetOutputInfoSafe.so
make
```
## usage
`LD_PRELOAD=./XRRGetOutputInfoSafe.so application`
