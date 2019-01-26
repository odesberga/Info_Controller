unit FMain;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
   StdCtrls, SdpoSerial,FcomCon,Uconnection,contnrs,fgl;

type
  tchiptype = class
    chipindex:Integer;
    typename:string;
    createstring:string;
  end;
   tchiptypeslist = specialize TFPGObjectList<tchiptype>;
  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    ListBox1: TListBox;
    ListBox2: TListBox;
    shield_func_left: TPanel;
    shield_func_right: TPanel;
    Panel3: TPanel;
    Panel4: TPanel;
    Panel5: TPanel;
    Panel6: TPanel;
    Panel7: TPanel;
    Panel8: TPanel;
    Splitter1: TSplitter;
    Splitter2: TSplitter;
    Splitter3: TSplitter;
    procedure Button1Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure framefuncLeftClick(Sender: TObject);
    procedure setCaptions();
  private
    procedure readfile(filename: string);

  public
  var
      mf: TForm_common_controller;
      myform:TForm;
      Fchiptypeslist:tchiptypeslist;
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.framefuncLeftClick(Sender: TObject);
begin

end;

procedure TForm1.setCaptions();
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



procedure TForm1.Button1Click(Sender: TObject);



begin
  if not Assigned(mf)then
  Begin
  mf:=TForm_common_controller.Create(Application);
  mf.createControls(Fchiptypeslist[0].createstring,Fchiptypeslist[0].typename,Fchiptypeslist[0].chipindex);
  mf.Panel2.Parent:=shield_func_left;




  end;


end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  try
  if Assigned(mf) then
  begin
    mf.Close;
    freeandnil(mf);
  end;
  except
  end;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  mf.setfunction(StrToInt(edit1.Text),StrToInt(edit2.Text),StrToInt(edit3.Text));
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  setCaptions();
  readfile(ExtractFilePath(ParamStr(0))+'config/modules');
end;
  procedure TForm1.readfile(filename: string);
var
  r:tchiptype;
  sl1,sl2:TStringList;
  i,i2:integer;
  fileloc,additem:string;
begin
  sl1:=TStringList.create;

  sl1.LoadFromFile(filename );

  Fchiptypeslist:=Tchiptypeslist.Create(true);
  i2:=sl1.Count-1 ;
  if sl1.Count =1 then i2:=1;
  for i :=0 to i2-1 do
  begin
    r:=tchiptype.create;
    sl2:=TStringList.Create;
    sl2.Delimiter:=';';
    sl2.StrictDelimiter:=true;
    sl2.DelimitedText:=sl1[i];
    r.chipindex:=StrToInt(sl2[0]);
    r.typename:=sl2[1];
    r.createstring:=sl2[2];
    Fchiptypeslist.Add(r);
    FreeAndNil(sl2);
  end;
  FreeAndNil(sl1);
end;
end.

