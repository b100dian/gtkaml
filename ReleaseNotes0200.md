Based on vala 0.1.7, gtkaml 0.2 brings lots of new features that are described

gtkaml 0.2.0.0 requires glib-2.0, vala-1.0 >= 0.1.7, libxml-2.0, and gtk+-2.0

New features in gtkaml 0.2:

  * #### Write code your way ####
gtkaml 0.2 allows you to use either underscores in attribute names (like the Gtk+ functions do) or _hyphens_ (as signal names do) interchangeably

  * #### Write less ####
The new Gtk.implicits file allows default values for common arguments (for creation methods and add functions). For example, `HBox`/`VBox` creation method by default has `homogeneous=false` and `spacing=0`, while `pack_start` borrows the 3 defaults from `pack_start_defaults` so that you can specify only the changed ones

  * #### More control ####
gtkaml creates the `construct { }` method for your class, where it adds the generated code. If however you want to write yourself code at construction time, you can use `gtkaml:preconstruct` and `gtkaml:construct` code attributes on _any_ widget.

They work just like signals, and have a first `target` parameter with the current widget. Preconstruct is called exactly after creation, before setting other attributes. Construct is called exactly before adding the current widget to the parent container.

Also, `gtkaml:implements` on the root tag allows you to specify the interfaces you are implementing.

  * #### Reusing existing widgets ####
By specifying `gtkaml:existing="identifier"` you **skip the creation method** for the current tag, and use an existing widget. An use case would be adding a `CellRenderer` to a `TreeViewColumn` and then specifying the attribute it renders:
```
<TreeViewColumn resizable="true" clickable="false" append_column="true" title="size">
	<CellRendererText class:private="renderer1" expand="true" />
	<CellRendererText class:existing="renderer1" attribute="text" column="1" />
</TreeViewColumn>
```
The first child tag yields `renderer1 = new Gtk.CellRendererText ()` and `pack_start (renderer1, true)` and the second only `add_attribute ((renderer1 as Gtk.CellRendererText), "text", 1)`.

  * #### Creating standalone widgets ####
Specifying `gtkaml:standalone="true"` **skips the parent container add call** for that widget. This way you may create private fields that have their UI described in gtkaml but that you show later, in code, when appropiate. For example, a standalone about dialog:
```
<AboutDialog class:standalone="true" class:private="aboutdialog1" delete-event="{aboutdialog1.hide_on_delete}"
modal="true" window-position="{WindowPosition.CENTER_ON_PARENT}" />
```
You can later use this dialog with
```
aboutdialog1.run (); 
```

  * #### Existing-standalone widgets ####
By specifying both `gtkaml:standalone` and `gtkaml:existing` you can customize widgets _already created_ and _already added_ to their parent, like the **`Dialog.vbox`** container.

  * #### Windows support ####
Vala 0.1.7 comes with better windows support. Packages for gtkaml 0.2 on Windows will soon be available (There are already source installation instructions)

Known issues:

Known issues are filed as [issue #5](https://code.google.com/p/gtkaml/issues/detail?id=#5), [issue #6](https://code.google.com/p/gtkaml/issues/detail?id=#6) and [issue #7](https://code.google.com/p/gtkaml/issues/detail?id=#7) and they will be solved in future minor versions