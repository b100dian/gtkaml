gtkaml is built using autotools and therefore the distribution comes with a './configure' script that only depends on unix utilities (so you don't have to have autotools installed - autoconf, automake etc.)

But you _do_ have to install a compatible compiler and shell.

The instructions here are based on [MinGW](http://www.mingw.org/) (minimal gcc for windows) and [MSYS](http://www.mingw.org/msys.shtml) (minimal system)

### Install MinGW ###
Use the [Automated MinGW installer](http://sourceforge.net/project/showfiles.php?group_id=2435) - as we speak this is [MinGW-5.1.4.exe](http://downloads.sourceforge.net/mingw/MinGW-5.1.4.exe?modtime=1168811236&big_mirror=1). The default installation path is **C:/MinGW** but you can change it.
Do **not** install the `make` utility that comes with MinGW.

### Install MSYS ###
At the moment, the base system has automatic installer only for the 1.0.10 version, found here: [MSYS-1.0.10.exe](http://downloads.sourceforge.net/mingw/MSYS-1.0.10.exe?modtime=1079444447&big_mirror=1) and as for the development toolkit, for the 1.0.1 version which is here: [msysDTK-1.0.1.exe](http://downloads.sourceforge.net/mingw/msysDTK-1.0.1.exe?modtime=1041430674&big_mirror=1)
Tell MSYS where MinGW resides (usually C:/MinGW).
The default installation path for MSYS is **C:/msys/1.0**

Now you should already have an msys shortcut on your desktop to start the rxvt terminal and play with shell commands like `ls -l` et co.;)

### gtkaml prerequisites ###
gtkaml requires gtk-2.0, which is available for download at [www.gtk.org](http://www.gtk.org/download-windows.html).

Just get the developer bundle.

Make a folder named **C:/usr** (or C:/libs or how you prefer) and unzip _all_ the files there. They usually come with sub-directories like `include`, `bin`, `share` and `lib` and they will nicely overlap just like on a UNIX `/usr` folder.

Now we will add C:/usr/bin in the **$PATH** and C:/usr/lib/pkgconfig in **$PKG\_CONFIG\_PATH**. To do this, enter msys and do a
```
$ mkdir /etc/profile.d
$ touch /etc/profile.d/gtkaml.sh
$ chmod a+x /etc/profile.d/gtkaml.sh
```
Now edit gtkaml.sh (you can have any other name here too) with your faVorite edItor so that its contents are:
```
#!/bin/sh
export PKG_CONFIG_PATH=/c/usr/lib/pkgconfig:/c/msys/lib/pkgconfig
export PATH=$PATH:/c/MinGW/libexec/gcc/mingw32/3.4.2/:/c/usr/bin
```
Adjust the paths if necessary - and restart msys.

(Note: to be able to run the Gtk+ programs outside msys consider adding that PATH to Windows's environment)

**Important**: from now on, make sure you configure every package with **`./configure --prefix=c:/usr`** so that it works outside of msys too (`c:/usr` is a valid windows path, but msys is able to emulate `/c/usr` which is not valid outside it). Another reason to do this is so that you _don't install executables in `c:/msys/1.0/bin`_, because msys might _fail to pass command-line arguments_ to those binaries.

Last but not least, gtkaml uses libxml2, which you can find here for windows: http://www.zlatkovic.com/libxml.en.html, but that distribution doesn't contain the libxml2.pc required for pkg-config.

So **if you want to _compile_ gtkaml, you have to _compile libxml2_ too**. Otherwise, use binary packages for both (see below).

### Compiling libxml2, vala and gtkaml ###

Download the latest version from [ftp://xmlsoft.org/libxml2/](ftp://xmlsoft.org/libxml2/), and do the following:
```
$ tar xvzf /path/to/libxml2-2.7.2.tar.gz
$ cd libxml2-2.7.2
$ ./configure --prefix=c:/usr
$ make
$ make install
```

Download vala 0.5.2 or later (for gtkaml 0.2.2.2). Start msys and change to a folder of your choice, and type there
```
$ tar -xvjf /path/to/vala-0.5.x.tar.bz2
$ cd vala-0.5.x
$ ./configure --prefix=c:/usr
$ make
$ make install
```

The same exact steps are for compiling gtkaml
```
$ tar -xvjf /path/to/gtkaml-0.2.x.x.tar.bz2
$ cd gtkaml-0.2.x.x
$ ./configure --prefix=c:/usr
$ make
$ make install
```

### Testing the environment ###
If gtkaml compiled, it already means that vala works, and Gtk+ and libxml2 are properly installed.

(This is because gtkaml uses libxml2, has .vala sources and some .gtkaml files in /tests or /examples which use Gtk+)

If you install from binary packages, try pasting the [example](Example.md) in a file and compile it.

### Binary packages for vala and gtkaml ###
Binary packages are available at the download section [here](http://code.google.com/p/gtkaml/downloads/list). Unzip them in c:/usr and you're done!

(**UPDATE**: the [Val(a)ide](http://code.google.com/p/valide/) project provides an installation kit for MinGW, Gtk+, and Vala. You would still need `msys` for binutils though)

Now you can start reading the [Vala Tutorial](http://live.gnome.org/Vala/Tutorial) or try out the sample code from [vala's homepage](http://live.gnome.org/Vala/), then you can jump to the gtkaml tutorial (when it's done).