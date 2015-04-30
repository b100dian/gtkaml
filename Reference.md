# Introduction #

Gtkaml has a couple of its own keywords (attributes), but relies heavily on existing Gtk widgets (or other libraries).


## gtkaml keywords ##

This is the complete list of gtkaml keywords as of 0.2.x:
[name](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:name)
[namespace](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:namespace)
[implements](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:implements)
[public](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:public)
[private](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:private)
[existing](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:existing)
[standalone](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:standalone)
[construct](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:construct)
[preconstruct](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#g:preconstruct)

## Gtk+ bindings ##

Gtk+ classes are further 'annotated' in [Gtk.implicits](http://code.google.com/p/gtkaml/source/browse/trunk/data/Gtk.implicits) with the following information:
  * **containers** : implicit methods to pick for 'add-to-container' meaning (e.g. subtags of a tag are added like this)
  * **constructor parameters** meaningful name (where needed) and/or default values

`Gtk.implicits` is automatically picked up by `gtkaml` when you're using the Vala namespace "Gtk" by assigning it an XML namespace/prefix (see `xmlns` in [the example](Example.md))

Here's a list of Gtk containers which are annotated:
[Container](http://code.google.com/p/gtkaml/wiki/GtkBindings#Container)
[ScrolledWindow](http://code.google.com/p/gtkaml/wiki/GtkBindings#ScrolledWindow)
[Box](http://code.google.com/p/gtkaml/wiki/GtkBindings#Box)
[VBox](http://code.google.com/p/gtkaml/wiki/GtkBindings#Box)
[HBox](http://code.google.com/p/gtkaml/wiki/GtkBindings#Box)
[Fixed](http://code.google.com/p/gtkaml/wiki/GtkBindings#Fixed)
[Paned](http://code.google.com/p/gtkaml/wiki/GtkBindings#Paned)
[HPaned](http://code.google.com/p/gtkaml/wiki/GtkBindings#Paned)
[VPaned](http://code.google.com/p/gtkaml/wiki/GtkBindings#Paned)
[Notebook](http://code.google.com/p/gtkaml/wiki/GtkBindings#Notebook)