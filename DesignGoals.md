See [Future Goals](DesignGoals#Future_Goals.md) - "not done".

# Achieved Goals #
## goals for 0.1 (DONE) ##
  * the gtkaml XML tags correspond to existing GObject classes(DONE in 0.1), and their attributes correspond to GObject properties, signals or fields(DONE in 0.1)

  * the XML namespace URI includes the Vala namespace name(DONE in 0.1) followed by a colon (':') and the Vala pkg name (optional). The namespace you're creating can be specified in `gtkaml:namespace` attribute (DONE in 0.1):

```
<Gtkns:Window xmlns:Gtkns="Gtk:gtk+-2.0" xmlns:GLibns="GLib" xmlns:gtkaml="http://gtkaml.org/0.1" gtkaml:namespace="myNamespace" gtkaml:name="MyWindow">
...
</Gtkns:Window>
```
  * the gtkaml namespace name may be changed as long as its URI begins with `http://gtkaml.org/` (DONE in 0.1)

  * the root tag represents the class that you're extending(DONE in 0.1), and the `gtkaml:name` represents the name of the class you're creating(DONE in 0.1):

```
using Gtk;
using GLib;
namespace myNamespace {
   public class MyWindow : Gtk.Window { ... } 
}
```
  * the other tags are declared as locals in the `construct` method (DONE in 0.1) and code is generated so that their properties are set(DONE in 0.1) and they are added to the parent container(DONE in 0.1)

```
<Window xmlns="Gtk:gtk+-2.0" xmlns:GLibns="GLib" title="gtkaml window">
    <Label label="test" />
</Window>
```
generates:
```
   private Gtk.Label label1;
   construct {
       this.title = "gtkaml window";
       label1 = new Gtk.Label();
       label1.label = "test";
       this.add(label1);
   }
```
  * the `gtkaml:public` and `gtkaml:private` attributes can set a name and visibility of a tag and declare it as a class member(DONE in 0.1):

```
<Window xmlns="Gtk:gtk+-2.0" xmlns:GLibns="GLib" title="gtkaml window">
    <Label gtkaml:public="myLabel" label="test" />
</Window>
```
generates:
```
   public Gtk.Label myLabel;
   construct {
       this.title = "gtkaml window";
       myLabel = new Gtk.Label();
       myLabel.label = "test";
       this.add(myLabel);
   }
```
  * attributes can be specified as sub-tags too (e.g. for multiline values or complex literals like array ones) (DONE in 0.1)

```
    <Label gtkaml:public="myLabel" >
         <label>multiline 
label</label>
    </Label>
```

  * code can be written in CDATA sections of the root tag(DONE in 0.1)

```
<Window xmlns="Gtk:gtk+-2.0" xmlns:GLibns="GLib">
   <![CDATA[
   private function on_click() { 
      stdout.printf("clicked!\n"); 
   } ]]>
</Window>
```
  * signals are properties holding code as their value (e.g. a function call). The parameters are `target`(the emmiter) and the other parameters from the signal signature, with the same names(DONE in 0.1)

```
<Window xmlns="Gtk:gtk+-2.0" xmlns:GLibns="GLib">
   <Label gtkaml:public="myLabel" label="test" clicked="on_click()"/>   
   <![CDATA[
   private function on_click() { 
      stdout.printf("clicked!\n"); 
   } ]]>
</Window>
```
  * attributes that are not literals can be specified with {} surrounding an identifier or expression (DONE in 0.1)

```
   <string gtkaml:public="myString">There is no spoon</string>
   <Label gtkaml:public="myLabel" label="{myString}"/>
```
  * signals can be written in between {} too - this way you have to specify yourself the lambda function (DONE in 0.1):

```
<Window xmlns="Gtk:gtk+-2.0" xmlns:GLibns="GLib">
   <Label gtkaml:public="myLabel" label="test" clicked="{target=>{on_click()}}"/>   
   ...
```

  * creation methods are automatically determined based on the attributes present. If you want to use a specific creation method, specify his name as an attribute with the value "true" (DONE in 0.1):

```
   <Label with_mnemonic="true" label="_Shortcut"/>
```
  * the functions used to add child widgets to containers are automatically detected. If you want to use a specific container add function, specify his name as an attribute with the value "true" (DONE in 0.1):

```
   <VBox homogeneous="true" spacing="0">
       <Label pack_end="true" label="packed at end" />
   </VBox>
```

## Goals for 0.2 (DONE) ##

  * the `gtkaml:construct` and `gtkaml:preconstruct` are used to specify a method/code to be called before/after the construction of the ui, given that you cannot have another `construct` method (DONE in 0.2). The version with {} specifies a method (or lambda function), while the version without {} specifies verbatim executable code. Also, a default parameter `target` is be available (DONE in 0.2)

  * the `gtkaml:implements` root attribute is used to specify a comma-separated interface list (DONE in 0.2)

  * a class member can be 'added' multiple times in a container (thus skipping the creation) by specifying ~~`gtkaml:reference="identifier"`~~ ~~(DONE in 0.1.1.1)~~  `gtkaml:existing="identifier"` (DONE in 0.2). ~~Of course, no other attribute than the parameters to the add function shall be specified on a reference.~~ The values without {} will be cast to the tag class (DONE in 0.2)
```
   <TreeViewColumn title="col1">
       <CellRendererText gtkaml:private="renderer1" pack_start="true" expand="true" />
       <CellRendererText gtkaml:existing="renderer1" add_attribute="true" attribute="text" column="0" />
   </TreeViewColumn>
```

  * `gtkaml:standalone="true"` as attribute allows the beginning of a UI description that doesn't get added to a parent container. This way, using `<VBox gtkaml:standalone="true" gtkaml:existing="dialog.vbox" ...` enables you to customize an existing area of a dialog. (DONE in 0.2)

  * the creation method of the base class must be respected: all required creation methods' parameters must be specified for the root tag (DONE in 0.2). Otherwise the implicits definition file must have default values (see below).

  * The creation methods / container add methods can have default values for parameters in implicits configuration files. These are not taken into account when establishing maximum method match (DONE in 0.2)

  * the implicits.ini file is renamed to Gtk.implicits; when using a namespace, the implicits resolver looks up the namespacename.implicits in gtkaml's data folder and in --implicitsdir (DONE in 0.2)

  * xmlns:gtkaml URI versions are taken into account: give a warning if the source level is not specified or not <=0.2 (http://gtkaml.org/ is not specified, http://gtkaml.org/0.1 is 0.1 level). Also give warnings when the source level is > than the gtkaml version. (DONE in 0.2)

  * attributes can be hyphen-separated instead of underscores (e.g. `destroy-event`  instead of `destroy_event`) (DONE in 0.2)

  * delete generated files unless --save-temps present (DONE in 0.2.0.1)
  * align generated .vala source lines to the first code island lines (DONE in 0.2.0.1)
  * fix existing bugs + reformulate .implicits parsing code (partially DONE in 0.2.0.2)
  * cleanup source (TODO)
  * use more human-parsable version numbering scheme (x.y.z) (DONE in 0.2.3)
  * allow signals to be container add functions (e.g. Container.add () is a signal and it is not used right now) (DONE in 0.2.8)


# Future Goals #


## Goals for 0.4 ##
  * signal handlers syntax: use {} for arbitrary expressions and no (additional) curly braces for method names or lambdas. (DONE in 0.4.0)
  * enum literals (e.g. `<Window type="TOPLEVEL">` instead of `<Window type="{WindowType.TOPLEVEL}>"`)
  * non-class code after the XML end tag (e.g. int main() belongs there, not public static int main() )
  * text runs
  * pango and cairo examples
  * clutter/mx support
  * hildon examples


## Goals for 0.6 ##
To think about:
  * #### rewrite ####
    * method matcher should parse the .implicits files upfront
    * stop generating text (.vala) files. Directly create vala AST elements. The problem when I started gtkaml was that I didn't have a method to parse the 'code islands'. Now that Vala.Parser is a recursive descent parser, I could use other methods as entry points in the parser (e.g. `vala_parser_parse_declaration ()` ). This would also enrich gtkaml's knowledge about the current source.
  * #### data binding ####
    * By using the 'notify' event of GLib.Object we can re-evaluate a property value on each change of one of its tokens.
    * property values syntax: introduce data binding expression similar to lambda notation such as `<Label label='title => {"Title: " + title}' />` which binds on `this.title`. Maybe bind all MemberAccess by default, and disable binding with `<Label label='(){"Title: " + title}' />` ?

  * composition methods should support arrays/collections (as seen in Clutter Stage.add())
  * "together properties" which generate a call (such as `x="10" y="15"` generates `set_position (10, 10);`
  * ~~vala re-entrant parser (allows to generate AST directly instead of code, and to parse 'code islands')~~
  * `<gtkaml:Code source='path'>` instead of `<![[CDATA ... ]]>`. Suggest `filename.gtkaml.vala` as preferred path, (let `<![[CDATA>` live on, too).
  * introduce `gtkaml:show-all="true"` which basically sets `visible="true"` on all child widgets unless explicitly set invisible
  * array add methods (e.g. define an attribute then fill it with array elements)

## Not formulated ideas ##
  * Genie support through root gtkaml:language attribute (+ genie code generator). Bonus points: yaml markup for genie, detect it automatically
  * implement GtkBuildable by default? re-use GtkBuildable instead of 'implicits' ?

Side projects:
  * converter from glade/gtkbuilder (based on libglade?)
  * gtkamlpad for fast previewing (converter _to_ gtkbuilder?)
  * bindable collections libraries & widgets

## Goals for 1.0 ##
  * all of the above, tested and stable