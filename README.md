### Abandoned.
Using Qt and QML would require shipping extra 55 MB in DLLs (mainly Qt), and in total 130 files.  
No way I'd agree with this. So I moved to SFML and ImGui, instead.

## Crystal Keys (cKeys)
Windows program showing pressed keys and keyboard layouts.

Meant as a support program for my keyboards CK3 and CK4 (more on [my website](https://cryham.tuxfamily.org/archives/portfolio/crystal-keyboard-3-and-4)).

Uses Qt and QML for display and Windows Keyboard Hook to get key states.

Reads custom keyboard layouts, from json files (using jsmn parser library),  
outputed from this web based editor: www.keyboard-layout-editor.com  
Supports only basic rectangular layouts, no rotation or styling.  
The default.json layout is the ANSI 104 preset (top left combo).

Screenshot
----------

![](https://raw.githubusercontent.com/cryham/ckeys-qt/master/screenshot.png)
