_this tutorial is work in progress_
# Introduction #

gktaml enables you to quickly write user interfaces in GTK+ while _not_ losing any coding capabilities you would otherwise have.

This is a quick walk-trough on how to code in gtkaml and Vala.

## Hello World ##

```
<Window xmlns="Gtk" gtkaml:name="HelloWorldWindow" title="Hello World" 
delete-event="Gtk.main_quit" xmlns:gtkaml="http://gtkaml.org/0.6" >
<![CDATA[
   public static int main (string[] args)
   {
       Gtk.init (ref args);
       var window = new HelloWorldWindow ();
       window.show_all ();
       Gtk.main ();
       return 0;
   }
]]>
</Window>   
```

First, the root tag always defines a class. In this case, it's a class that extends `Gtk.Window` and it's named `HelloWorldWindow`.

The `xmlns="Gtk"` declaration does two things: 'imports' the Gtk vala namespace (`using Gtk;`) and second, assumes all you un-prefixed tags are classes from this namespace (e.g. `Window` is `Gtk.Window`)

If you have another namespace you would like included, use `xmlns:myns="Myns"` and prefix all your classes in that namespace with `myns` like this: `<myns:MyWidget ..`

The `gtkaml:name` is the name of the class you're defining. You can prefix it with a namespace (e.g `gtkaml:class='Myns.HelloWorldWindow'`) or use `gtkaml:namespace="Myns"` for that.

The `xmlns:gtkaml="http://gtkaml.org/0.2"` is the declaration of the gtkaml prefix for this kind of meta-informations. You can have it renamed (e.g. `xmlns:class="http://gtkaml.org/0.2"` if you think `class:name`, `class:namespace` is more readable.

`title` is a property of the Gtk.Window. The value of the `title` attribute is known to be string so you can just write the characters there. Same for numeric types (`spacing="0"`) and booleans (`visible="true"`).

`delete-event` is a signal of the Gtk.Window. It is triggered when the window is closed. The value specifies that the main Gtk quit function should be added as handler.

`<![CDATA[` is an XML construct that allows you to write otherwise invalid characters (like '`<`'). `gtkaml` uses this section to specify code that goes in the class definition: in this case, the entry point `main ()`.

### Compiling the example ###
Let's say you save the above in a file named `tutorial.gtkaml`
The fastest way to compile this would be

`gtkamlc --pkg gtk+-2.0 tutorial.gtkaml`

The `--pkg` parameter tells vala to include the bindings for Gtk. That means to also include the headers and the linking parameters specified by e.g. `pkg-config`

If the above command complains that `gtk+-2.0 not found in specified Vala API directories` then you should add the `--vapidir /path/to/share/vala/vapi` in the command-line, where `/path/to` is the prefix of your vala installation.

If you want the generated .vala and .c files, try this command

`gtkamlc -C --pkg gtk+-2.0 tutorial.gtkaml --dump-tree=tutorial.vala`

Now, the output is actually three files, tutorial.c and tutorial.h and tutorial.vala. The later can be inspected to understand what gtkaml did with your XML, before passing it to valac, but the first two files are the actual code you need: to compile them, use the following command:
```
gcc `pkg-config --cflags gtk+-2.0` tutorial.h tutorial.c -o tutorial `pkg-config --libs gtk+2.0`
```

(The backticks surrounding a command replace it with its output. pkg-config automatically fills in for us the (multiple) libraries gtk+-2.0 links to and the header directories needed.)

### A more complex user interface ###
We will leave the `main ()` function out for the moment. You can write it in another file which is your application's entry point. We will focus on our custom window.

TODO