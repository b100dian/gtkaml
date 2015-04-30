## Introduction ##

Gtkon is a JSON-like alternative syntax to the standard XML that Gtkaml provides.

## Gtkon Syntax ##

Just like the XML syntax, each node corresponds to a widget which is added to the parent container.

Although colon-separated prefixes are still present as aliases to imported namespaces, the more lax syntax allows for the following shortcuts:

  * nodes just end on closing brace, no need to repeat the opening node name
  * values without whitespace may be left unquoted
  * attribute values can be quoted with ' or "
  * attributes may not have a value, in which case they are treated as ="true". A leading "!" means "false"
  * public members may be introduced directly with a leading `$` on the attribute (`$id` instead of `gtkaml:public="id"`). Private members start with `$.` (`$.priv_var`) Referencing an existing member is done with `&`
  * code islands are between  -{ and }-

The root node has to have the `gtkon:version=0.4` attribute and the regular gtkaml:[name](http://code.google.com/p/gtkaml/wiki/GtkamlKeywords#gtkaml:name) of the class.

The default prefix is introduced with `using=Gtk`, meaning that unprefixed nodes are from the Gtk namespace.

Aliases may be defined like this `using:p=Pango`, so from now on `p:` is for Pango nodes.

### Example ###
gtk-hello.gtkon
```
Dialog gtkon:version=0.4 using=Gtk name="SearchDialog" title="Find" !has-separator destroy=Gtk.main_quit {
	/*Dialog already has a VBox named vbox (existing) and is already added to the Dialog (standalone) */
	VBox spacing=10 &vbox gtkaml:standalone {
		HBox !homogeneous spacing=20 !expand {
			Label with-mnemonic label="_Search for:" mnemonic-widget={search_entry} !expand;
			Entry $search_entry;
		}
		CheckButton $match_case with-mnemonic label="_Match case" !expand;
		CheckButton $find_backwards with-mnemonic label="Find _backwards" !expand;
	}
	-{
		/* Vala code */
	}-
}
```