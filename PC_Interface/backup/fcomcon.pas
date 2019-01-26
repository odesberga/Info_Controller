unit FcomCon;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, db, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls,contnrs,fgl,UfuncDefHandler;

type



  { TForm_common_controller }
  TForm_common_controller = class(TForm)
    ComboBox1: TComboBox;
    ComboBox2: TComboBox;
    ComboBox3: TComboBox;
    ComboBox4: TComboBox;
    ComboBox5: TComboBox;
    ComboBox6: TComboBox;
    ComboBox7: TComboBox;
    ComboBox8: TComboBox;
    Edit1: TEdit;
    Panel1: TPanel;
    Panel2: TPanel;
    ScrollBox1: TScrollBox;
    procedure ComboBox1Change(Sender: TObject);
    procedure FormClose(Sender: TObject; var CloseAction: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure Panel1Click(Sender: TObject);
    procedure createControls(defineString,chipTypeName:string;chiptype:integer);
    procedure setCaptions();
    procedure setfunction(chipfuncnr,funcnr,subfuncnr:integer) overload;
    procedure setfunction(chipfuncnr,funcnr:integer;funcstring:string) overload;
  private
    funcdef:TfuncdefHandler;
    compnamelist:tstringlist;
    CBox: TComboBox;
    Edit: TEdit;
    Lbl:tlabel;

  public

  end;

var
  Form_common_controller: TForm_common_controller;

implementation

{$R *.lfm}

{ TForm_common_controller }

procedure TForm_common_controller.FormClose(Sender: TObject;
  var CloseAction: TCloseAction);
begin
  funcdef.Destroy;
  CloseAction:= caFree;
end;

procedure TForm_common_controller.ComboBox1Change(Sender: TObject);
begin
edit1.Text:=funcdef.Frules[ComboBox1.ItemIndex].name;
end;

procedure TForm_common_controller.FormCreate(Sender: TObject);
var
  i:integer;
  additem:string;
begin
   funcdef:=TfuncdefHandler.Create;
   compnamelist:=TStringList.Create;
end;

procedure TForm_common_controller.Panel1Click(Sender: TObject);
begin

end;

procedure TForm_common_controller.createControls(defineString,chipTypeName: string;chiptype:integer);
var
  controlslist,controlsdef:tstringlist;
  i,j,h,w:integer;
  additem,test:string;
begin

  controlslist:=TStringList.Create;
  controlslist.Delimiter:='$';
  controlslist.StrictDelimiter:=true;
  controlsdef:=TStringList.Create;
  controlsdef.Delimiter:=',';
  controlsdef.StrictDelimiter:=true;
  controlslist.DelimitedText:=defineString;
  h:=20;
     funcdef.readfile(ExtractFilePath(ParamStr(0))+'config/'+IntToStr(chiptype) );

       Lbl:=tlabel.Create(self);
       Lbl.Parent:=ScrollBox1;
       Lbl.Left:=10;
       Lbl.Top:= h;
       Lbl.Width:=170;
       Lbl.Name:='lblchipTypeName';
       h:=h+Lbl.Height;

       Lbl:=tlabel.Create(self);
       Lbl.Parent:=ScrollBox1;

       Lbl.Left:=10;
       Lbl.Top:= h;
       Lbl.Width:=170;
       Lbl.Name:='lblchipType';
       lbl.Caption:=chipTypeName;
       h:=h+Lbl.Height;
       h:=h+10;
       Lbl:=tlabel.Create(self);
       Lbl.Parent:=ScrollBox1;
       Lbl.Left:=10;
       Lbl.Top:= h;
       Lbl.Width:=170;
       Lbl.Name:='lblFuncName';
       h:=h+Lbl.Height+10;

       Edit:=TEdit.Create(self);
       Edit.Parent:=ScrollBox1;
       Edit.Left:=10;
       Edit.Top:= h;
       Edit.Width:=170;
       Edit.Name:='name';
       Edit.Text:='';
       compnamelist.Add(Edit.Name);
       h:=h+Edit.Height;





  for i :=0 to controlslist.count -1 do
  Begin
  controlsdef.DelimitedText:=controlslist[i];
    test:=controlslist[i];
    h:=h+StrToInt(controlsdef[2]);
    if lowercase(controlsdef[1])='c' then
    begin
       CBox:=TComboBox.Create(self);
       CBox.Parent:=ScrollBox1;
       cbox.Left:=10;
       CBox.Top:= h;
       cbox.Width:=StrToInt(controlsdef[3]);
       cbox.Name:=controlsdef[0];
       cbox.Text:='';
       for j :=0 to funcdef.Frules.Count -1 do
        begin
          additem:=funcdef.Frules[j].name;
          cbox.AddItem(additem,nil);
        end;
       compnamelist.Add(cbox.Name);
       h:=h+cbox.Height;
    end;
    if lowercase(controlsdef[1])='t' then
    begin
       Edit:=TEdit.Create(self);
       Edit.Parent:=ScrollBox1;
       Edit.Left:=10;
       Edit.Top:= h;
       Edit.Width:=StrToInt(controlsdef[3]);
       Edit.Name:=controlsdef[0];
       Edit.Text:='';
       compnamelist.Add(Edit.Name);
       h:=h+Edit.Height;
    end;

    if lowercase(controlsdef[1])='l' then
    begin
       Lbl:=tlabel.Create(self);
       Lbl.Parent:=ScrollBox1;
       Lbl.Left:=10;
       Lbl.Top:= h;
       Lbl.Width:=StrToInt(controlsdef[3]);
       Lbl.Name:=controlsdef[0];
       h:=h+Lbl.Height;
    end;

  end;
  setCaptions();
end;
  
procedure TForm_common_controller.setCaptions();
  var i,j: Integer;
    langdef,langdef2:TStringList;
begin
  langdef:=TStringList.Create;
  langdef2:=TStringList.Create;
  langdef2.Delimiter:=';';
  langdef2.StrictDelimiter:=true;
  langdef.LoadFromFile(ExtractFilePath(ParamStr(0))+'config/lang');

  for j:=0 to langdef.count-1 do
  begin
    langdef2.DelimitedText:=langdef[j];
    for i:=0 to ComponentCount-1 do
    begin
      if Components[i].Name=langdef2[0] then
      begin
       if (Components[i] is TEdit) then (Components[i] as TEdit).Text:=langdef2[1];
       if (Components[i] is TButton) then (Components[i] as TButton).Caption:=langdef2[1];
       if (Components[i] is Tlabel) then (Components[i] as Tlabel).Caption:=langdef2[1];
       if (Components[i] is Tpanel) then (Components[i] as Tpanel).Caption:='';
      end;
      if (Components[i] is Tpanel) then (Components[i] as Tpanel).Caption:='';
    end;

  end;
   FreeAndNil(langdef);
   FreeAndNil(langdef2);

end;

procedure TForm_common_controller.setfunction(chipfuncnr,funcnr, subfuncnr: integer);
var
  i:integer;
begin
   for i:=0 to ComponentCount-1 do
    begin
      if Components[i].Name=compnamelist[chipfuncnr] then
      begin
           if (Components[i] is TComboBox) then
           begin
             (Components[i] as TComboBox).Text:=funcdef.getName(funcnr,subfuncnr);
           end;

            //   if (Components[i] is TButton) then (Components[i] as TButton).Caption:=langdef2[1];
             //  if (Components[i] is Tlabel) then (Components[i] as Tlabel).Caption:=langdef2[1];
              //   if (Components[i] is Tpanel) then (Components[i] as Tpanel).Caption:='';
      end;
      if (Components[i] is Tpanel) then (Components[i] as Tpanel).Caption:='';
    end;
end;

procedure TForm_common_controller.setfunction(chipfuncnr,funcnr: integer;
  funcstring: string);
begin

end;

end.

