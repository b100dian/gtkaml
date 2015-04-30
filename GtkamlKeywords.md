# Introduction #

As seen in the [example](Example.md) or in the tests and sample that come with gtkaml, there is a **prefix** (usually referred to as `xmlns:g="http://gtkaml.org/0.2"` or `xmlns:gtkaml="http://gtkaml.org/0.2"`, or `xmlns:class`) that contains attributes that are _not_ part of the Gtk+ Vala bindings.

Here are their specifications, assuming the prefix is declared with **`xmlns:gtkaml`**.

### gtkaml:name ###
The name of the class you're creating. May contain fully qualified name.

Allowed only at the root tag level.

### gtkaml:namespace ###
The name of the namespace your class resides in.

Allowed only at the root tag level.

### gtkaml:implements ###
The comma-separated list of interfaces that the class implements.

Note that the inherited class is the root tag name.

### gtkaml:public ###
Specifies a name under which the current tag becomes a public class member.

Mutually exclusive with `gtkaml:private`.

### gtkaml:private ###
Specifies a name under which the current tag becomes a private class member.

Mutually exclusive with `class:public`.

### gtkaml:existing ###
Specifies that the current widget doesn't get constructed, but it configures a an existing widget. Also, it gets added to the parent container, unless it's `standalone` too.

The value is the identifier/expression under which the existing widget is reachable.

The expression is cast to the tag's name (e.g. `<VBox gtkaml:existing="dialog.vbox1" spacing="1" />` becomes `(dialog.vbox as VBox).spacing = 1`)

Allowed only on non-root tags.

### gtkaml:standalone ###
Specifies that the current widget doesn't get added to the parent container.

The only valid value is "true".

Allowed only on non-root tags.

### gtkaml:construct ###
Specifies code to be executed just before adding this widget to the parent container.

The code may use `target` as the name of the current widget, just like with a signal

### gtkaml:preconstruct ###
Specifies code to be executed just after the instance is created.

The code may use `target` as the name of the current widget, just like with a signal