## Container ##
add methods:
[add\_with\_properties](http://references.valadoc.org/gtk+-2.0/Gtk.Container.add_with_properties.html)

Due to a [limitation](http://code.google.com/p/gtkaml/issues/detail?id=7) in Gtkaml 0.2.x, the `Container` is using `add_with_properties` instead of `add`.

This is the only method for adding widgets to a `Container` so it's implicitly chosen.
All classes that extend `Container` have the ability to use its add method by default.

```
<Container>
  <Button />
</Button>
```

## ScrolledWindow ##
add methods:
[add\_with\_properties](http://references.valadoc.org/gtk+-2.0/Gtk.Container.add_with_properties.html),
[add\_with\_viewport](http://references.valadoc.org/gtk+-2.0/Gtk.ScrolledWindow.add_with_viewport.html).

The order above means that implicitly `add_with_properties` will be used. To use `add_with_viewport` write:
```
<ScrolledWindow>
   <Button add-with-viewport="true" />
</ScrolledWindow>
```

Also, `add_with_properites` is only mentioned for `ScrolledWindow` so that it takes precedence over the more-specific `add_with_viewport`.

## Box ##
add methods:
[pack\_start](http://references.valadoc.org/gtk+-2.0/Gtk.Box.pack_start.html),
[pack\_end](http://references.valadoc.org/gtk+-2.0/Gtk.Box.pack_end.html)


You can specify any of `expand`, `fill`, and `padding` on the child widget. The default values are: `expand="true"`, `fill="true"`, `padding="0"`.

Of course these add methods apply for `HBox` and `VBox` which implement from `Box`.

```
<HBox>
  <Button fill="false" /> <!-- pack_start () used by default -->
  <Button pack-end="true" expand="false" />
</HBox>
```

## Fixed ##
add methods: [put](http://references.valadoc.org/gtk+-2.0/Gtk.Fixed.put.html)

You need to specify `x` and `y` for this method.
```
<Fixed>
  <Button x="10" y="10" />
</Fixed>
```

## Paned ##
add methods:
[add1](http://references.valadoc.org/gtk+-2.0/Gtk.Paned.add1.html),
[add2](http://references.valadoc.org/gtk+-2.0/Gtk.Paned.add2.html),
[pack1](http://references.valadoc.org/gtk+-2.0/Gtk.Paned.pack1.html),
[pack2](http://references.valadoc.org/gtk+-2.0/Gtk.Paned.pack2.html),

For `pack1` and `pack2` you need to specify `resize` and `shrink` boolean parameters.
```
<HPaned>
  <Button />             <!-- by default uses add1() -->
  <Button add2="true" /> <!-- note: you need to specify add2() explicitly -->
</HPaned>
```

## Layout ##
add methods: [put](http://references.valadoc.org/gtk+-2.0/Gtk.Layout.put.html)

You need to specify `x` and `y` for `put`, which is the default method.
```
<Layout>
  <Button x="10" y="10" />
</Layout>
```

## Window ##
`Window` just inherits whatever `Bin` and `Container` have as add methods.

## MenuShell ##
add methods:
[append](http://references.valadoc.org/gtk+-2.0/Gtk.MenuShell.append.html)
[prepend](http://references.valadoc.org/gtk+-2.0/Gtk.MenuShell.prepend.html)
[insert](http://references.valadoc.org/gtk+-2.0/Gtk.MenuShell.insert.html)

Default is `append` which requires no parameters. `insert` requires `position` on child widget.

The same appliy for `MenuBar` and `Menu` which extend `MenuShell`.

```
<MenuBar>
  <MenuItem />
  <MenuItem prepend="true" />
  <MenuItem position="0" />    <!-- uses insert() -->
</MenuBar>
```

## Notebook ##
add methods:
[append\_page](http://references.valadoc.org/gtk+-2.0/Gtk.Notebook.append_page.html)
[append\_page\_menu](http://references.valadoc.org/gtk+-2.0/Gtk.Notebook.append_page_menu.html)
[prepend\_page](http://references.valadoc.org/gtk+-2.0/Gtk.Notebook.prepend_page.html)
[prepend\_page\_menu](http://references.valadoc.org/gtk+-2.0/Gtk.Notebook.prepend_page_menu.html)
[insert\_page](http://references.valadoc.org/gtk+-2.0/Gtk.Notebook.insert_page.html)
[insert\_page\_menu](http://references.valadoc.org/gtk+-2.0/Gtk.Notebook.insert_page_menu.html)

The default is `append_page`. All methods require an attribute `tab_label` of type **Widget** present on the child. The methods ending with `_menu` require a second one, `menu_label`.

To specify `tab-label` you either use `{code}` to write an expression (like the name of a private property or an _existing_ widget) or you use a **Complex attribute**, that is, a sub-tag that plays the role of an attribute.<Label g:private="label0" g:standalone="true" label="My Tab" />
<Notebook>
  <Button tab-label="{label0}" /> <!-- using a code expression  -->
  <Button>
     <tab-label>
        <Label label="My Other Tab" />  <!-- using a complex attribute -->
     <tab-label/>
  <Button/>
</Notebook>



TODO```