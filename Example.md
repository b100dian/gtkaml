# From Vala GTKSamples #

## [Basic Sample](http://live.gnome.org/Vala/GTKSample#line-7) ##
(Available in [Gtkon](Gtkon.md) syntax [here](http://code.google.com/p/gtkaml/source/browse/trunk/examples/vala2gtkon/gtk-hello.gtkon))
```
<Window xmlns:g="http://gtkaml.org/0.4" xmlns="Gtk" g:name="GtkHello"
  type="{WindowType.TOPLEVEL}" title="First GTK+ Program" 
  position="{WindowPosition.CENTER}" default-width="300" default-height="50"
  destroy="Gtk.main_quit">

  <Button label="Click me!" clicked='{target.label="Thank you";}' />

<![CDATA[
  static int main (string[] args) {
    Gtk.init (ref args);
    var window = new GtkHello ();
    window.show_all ();
    Gtk.main ();
    return 0;
  }
]]>
</Window>
```

Compile and run:
```
$ gtkamlc --pkg gtk+-2.0 gtk-hello.gtkaml
$ ./gtk-hello
```

## [Synchronizing Widgets](http://live.gnome.org/Vala/GTKSample#line-46) ##
(Available in [Gtkon](Gtkon.md) syntax [here](http://code.google.com/p/gtkaml/source/browse/trunk/examples/vala2gtkon/sync-sample.gtkon))
```
<Window xmlns:g="http://gtkaml.org/0.4" xmlns="Gtk"
  title="Enter your age" position="{WindowPosition.CENTER}"
  destroy="Gtk.main_quit" default-width="300" default-height="20"
  g:name="SyncSample">
  
  <HBox spacing="5">
    <SpinButton g:private="spin" with-range="true" min="0" max="130" step="1"
      value="35"
      value-changed="{slider.set_value (target.get_value ())}"/>
    <HScale g:private="slider"   with-range="true" min="0" max="130" step="1"
      value-changed="{spin.set_value (target.get_value ())}"/>
  </HBox>

<![CDATA[
    public static int main (string[] args) {
       Gtk.init (ref args);

       var window = new SyncSample ();
       window.show_all ();

       Gtk.main ();
       return 0;
    }
]]>
</Window>
```


Compile and run:
```
$ gtkamlc --pkg gtk+-2.0 sync-sample.gtkaml
$ ./gtk-hello
```

## [Creating a Dialog](http://live.gnome.org/Vala/GTKSample#line-211) ##
(Available in [Gtkon](Gtkon.md) syntax [here](http://code.google.com/p/gtkaml/source/browse/trunk/examples/vala2gtkon/search-dialog.gtkon))
```
<Dialog xmlns:g="http://gtkaml.org/0.4" xmlns="Gtk"
  g:name="SearchDialog" title="Find" has-separator="false"
  border-width="5" default-width="350" default-height="100"
  response="on_response" destroy="Gtk.main_quit">

  <VBox spacing="10" g:existing="vbox" g:standalone="true"> <!-- Dialog already has a vbox (existing) and is already added to the Dialog (standalone) -->
    <HBox homogeneous="false" spacing="20" expand="false">
      <Label with-mnemonic="true" label="_Search for:" mnemonic-widget="{search_entry}" expand="false"/>
      <Entry g:private="search_entry" />
    </HBox>
    <CheckButton g:private="match_case"     with-mnemonic="true" label="_Match case" expand="false"/>
    <CheckButton g:private="find_backwards" with-mnemonic="true" label="Find _backwards" expand="false"/>
  </VBox>
   
<![CDATA[

  public signal void find_next (string text, bool case_sensitivity);
  public signal void find_previous (string text, bool case_sensitivity);

  private Widget find_button;

  public SearchDialog () {
    add_button (STOCK_HELP, ResponseType.HELP);
    add_button (STOCK_CLOSE, ResponseType.CLOSE);
    this.find_button = add_button (STOCK_FIND, ResponseType.APPLY);
    this.find_button.sensitive = false;
  }

  private void on_response (Dialog source, int response_id) {
    switch (response_id) {
      case ResponseType.HELP:
        // show_help ();
        break;
      case ResponseType.APPLY:
        on_find_clicked ();
        break;
      case ResponseType.CLOSE:
        destroy ();
        break;
    }
  }

  private void on_find_clicked () {
    string text = this.search_entry.text;
    bool cs = this.match_case.active;
    if (this.find_backwards.active) {
      find_previous (text, cs);
    } else {
      find_next (text, cs);
    }
  }

  static int main (string[] args) {
    Gtk.init (ref args);
    var dialog = new SearchDialog ();
    dialog.show_all ();
    Gtk.main ();
    return 0;
  }
]]>
</Dialog>
```

Compile and run:
```
$ gtkamlc --pkg gtk+-2.0 search-dialog.gtkaml
$ ./gtk-hello
```


## [TreeView with ListStore](http://live.gnome.org/Vala/GTKSample#line-435) ##
(Available in [Gtkon](Gtkon.md) syntax [here](http://code.google.com/p/gtkaml/source/browse/trunk/examples/vala2gtkon/treeview-liststore-sample.gtkon))
```
<Window xmlns:g="http://gtkaml.org/0.4" xmlns="Gtk"
  g:name="TreeViewSample" title="Tree View Sample"
  default-width="250" default-height="100"
  destroy="Gtk.main_quit">

  <TreeView g:private="view" g:construct="setup_treeview()">
  	<TreeViewColumn title="Account Name">
		<CellRendererText g:private="column0" expand="false" />               <!-- gtk_cell_layout_pack_start call -->
		<CellRendererText g:existing="column0" attribute="text" column="0" /> <!-- gtk_cell_layout_add_attribute call -->
	</TreeViewColumn>
 	<TreeViewColumn title="Type">
		<CellRendererText g:private="column1" expand="false"/>
		<CellRendererText g:existing="column1" attribute="text" column="1" /> 
	</TreeViewColumn>

 	<TreeViewColumn title="Balance">
		<CellRendererText g:private="column2" expand="false" foreground-set="true"/> 
		<CellRendererText g:existing="column2" attribute="text" column="2" />
		<CellRendererText g:existing="column2" attribute="foreground" column="3" />
	</TreeViewColumn>
  </TreeView>

<![CDATA[
  private void setup_treeview () {
    TreeIter iter;
    var listmodel = new ListStore (4, typeof (string), typeof (string), typeof (string), typeof (string));
    listmodel.append (out iter);
    listmodel.set (iter, 0, "My Visacard", 1, "card", 2, "102,10", 3, "red", -1);

    listmodel.append (out iter);
    listmodel.set (iter, 0, "My Mastercard", 1, "card", 2, "10,20", 3, "red", -1);

    view.model = listmodel;
  }

  public static int main (string[] args) {     
    Gtk.init (ref args);

    var sample = new TreeViewSample ();
    sample.show_all ();
    Gtk.main ();

    return 0;
  }
]]>
</Window>
```

Compile and run:
```
$ gtkamlc --pkg gtk+-2.0 treeview-liststore-sample.gtkaml
$ ./gtk-hello
```



## Exhaustive Gtkaml Syntax sample ##

Which would produce this:

![http://blad.files.wordpress.com/2007/11/gtkaml1.png](http://blad.files.wordpress.com/2007/11/gtkaml1.png)

### MyVBox.gtkaml ###
Here is what you write:
```
<VBox xmlns="Gtk" xmlns:glib="GLib" xmlns:class="http://gtkaml.org/0.2" 
class:name="MyVBox">
	<Label use-markup="true" label="&lt;b&gt;Dialog Box Title Here&lt;/b&gt;" expand="false" fill="false" padding="0" />
	<Notebook can-focus="true" tab-vborder="1">
		<Label>
			<tab-label>
			    <Label label="Page 1"/>
			</tab-label>
			<label>label
multilne</label>
		</Label>
		<HBox homogeneous="false" spacing="0">
			<tab-label>
			    <CheckButton label="check button" active="true" />
			</tab-label>
			<Label label="Nothing to see here, please move along" />
		</HBox>
	</Notebook>
	<HButtonBox>
		<Button with-mnemonic="true" label="_abort" clicked="{on_click()}"/>
		<Button label="gtk-redo" use-stock="true"/>
		<Button label="fail"/>
	</HButtonBox>
<![CDATA[
	private void on_click() { message("you clicked me!"); }

	static int main (string[] args) 
	{
		Gtk.init (ref args);
		Window w = new Gtk.Window (WindowType.TOPLEVEL);
		w.delete_event += (x,y) => { Gtk.main_quit(); };
		MyVBox v = new MyVBox ();
		w.add (v);
		w.show_all ();
		Gtk.main ();
		return 0;
	}
		
]]>
</VBox>
```

Um.. what was that again? Here's what happens (same source, annotated):

```
<!-- MyVBox class extends VBox and imports the Gtk and GLib namespaces -->
<VBox class:name="MyVBox" xmlns="Gtk" xmlns:glib="GLib" xmlns:class="http://gtkaml.org/0.4">
	<!-- a label is added to the VBox, you can see the box_pack_start () parameters -->
	<Label use-markup="true" label="&lt;b&gt;Dialog Box Title Here&lt;/b&gt;" expand="false" fill="false" padding="0" />
	<!-- then a notebook (tab navigator) is added, with box_pack_start_defaults () -->
	<Notebook can-focus="true" tab-vborder="1">
		<!-- the first page in the notebook is only a label -->
		<Label>
			<!-- this is the widget used for notebook tab label -->
			<tab-label>
			    <!-- this label's text is set using the attribute label="" -->
			    <Label label="Page 1"/>
			</tab-label>
			<!-- the parent's text label is set using this sub-tag -->
			<label>label
multilne</label>
		</Label>
		<!-- the second page is an HBox -->
		<HBox homogeneous="false" spacing="0">
			<!-- actually this sub-tag is a parameter to gtk_notebook_append_page (notebook, child, tab_label) -->
			<tab-label>
			    <!-- this uses a check button as its notebook tab -->
			    <CheckButton label="check button" active="true" />
			</tab-label>
			<!-- this is what the HBox contains -->
			<Label label="Nothing to see here, please move along" />
		</HBox>
	</Notebook>
	<!-- next we add an HButtonBox to our VBox -->
	<HButtonBox>
		<!-- this button is created with gtk_button_new_with_mnemonic () 
		     'clicked' contains the body of the event handler lambda function -->
		<Button with-mnemonic="true" label="_abort" clicked="{on_click()}"/>
		<Button label="gtk-redo" use-stock="true"/>
		<Button label="fail"/>
	</HButtonBox>
<!-- cdata sections are used for Vala code -->
<![CDATA[
	private void on_click() { stdout.printf("you clicked me!"); }

	static int main (string[] args) 
	{
		Gtk.init (ref args);
		Window w = new Gtk.Window (WindowType.TOPLEVEL);
		w.delete_event += (x,y) => { Gtk.main_quit(); };
		MyVBox v = new MyVBox ();
		w.add (v);
		w.show_all ();
		Gtk.main ();
		return 0;
	}
		
]]>
</VBox>
```
and the output of

`$ gtkamlc --pkg gtk+2.0 MyVBox.gtkaml `

is the following MyVBox.vala file (along with MyVBox.c and MyVBox.h).

(to compile the executable you need to run
```
$ gcc `pkg-config --cflags gtk+-2.0` MyVBox.c -o myvbox `pkg-config --libs gtk+-2.0`
```
then `./myvbox` will execute it)

### MyVBox.vala ###
```
using Gtk;
using GLib;

public class MyVBox : Gtk.VBox
{
	private void on_click() { stdout.printf("you clicked me!"); }

	static int main (string[] args) 
	{
		Gtk.init (ref args);
		Window w = new Gtk.Window (WindowType.TOPLEVEL);
		MyVBox v = new MyVBox ();
		w.add (v);
		w.show_all ();
		Gtk.main ();
		return 0;
	}

	construct {
		Gtk.Label _label0;
		Gtk.Notebook _notebook0;
		Gtk.Label _label1;
		Gtk.Label _label2;
		Gtk.HBox _hbox0;
		Gtk.CheckButton _checkbutton0;
		Gtk.Label _label3;
		Gtk.HButtonBox _hbuttonbox0;
		Gtk.Button _button0;
		Gtk.Button _button1;
		Gtk.Button _button2;

		_label0 = new Gtk.Label ("<b>Dialog Box Title Here</b>");
		_notebook0 = new Gtk.Notebook ();
		_label2 = new Gtk.Label ("label for a tab");
		_label1 = new Gtk.Label ("label\nmultilne");
		_checkbutton0 = new Gtk.CheckButton.with_label ("check button");
		_hbox0 = new Gtk.HBox (false, 0);
		_label3 = new Gtk.Label ("Nothing to see here, please move along");
		_hbuttonbox0 = new Gtk.HButtonBox ();
		_button0 = new Gtk.Button.with_mnemonic ("_abort");
		_button1 = new Gtk.Button.with_label ("gtk-redo");
		_button2 = new Gtk.Button.with_label ("fail");

		this.name = "MyVBox";
		_label0.use_markup = true;
		this.pack_start (_label0, false, false, 0);

		_notebook0.can_focus = true;
		_notebook0.tab_vborder = 1;
		this.pack_start_defaults (_notebook0);

		_notebook0.append_page (_label1, _label2);

		_checkbutton0.active = true;
		_notebook0.append_page (_hbox0, _checkbutton0);

		_hbox0.pack_start_defaults (_label3);

		this.pack_start_defaults (_hbuttonbox0);

		_button0.has_default = true;
		_button0.clicked += target => { on_click(); };
		_hbuttonbox0.pack_start_defaults (_button0);

		_button1.use_stock = true;
		_hbuttonbox0.pack_start_defaults (_button1);

		_hbuttonbox0.pack_start_defaults (_button2);
	}
}
```

## Why? ##

Beacause vala further transforms the source into .c and .h and gcc compiles them (of course) to native code;)