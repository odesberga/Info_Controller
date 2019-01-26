unit UfuncDefHandler;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils,contnrs,fgl;
type
    trule = class
    func:Integer;
    subfunc:Integer;
    name:string;
  end;
   Truleslist = specialize TFPGObjectList<trule>;

    { TfuncdefHandler }

  TfuncdefHandler = class
      constructor Create;
      destructor Destroy; override;
      procedure readfile(filename:string);
      function getName(funct,subfunct:integer):string;

  private


  public

    Frules:Truleslist;

  end;

implementation

{ TfuncdefHandler }

constructor TfuncdefHandler.Create;
begin

end;

destructor TfuncdefHandler.Destroy;
begin
  inherited Destroy;
  freeandnil(Frules);

end;

procedure TfuncdefHandler.readfile(filename: string);
var
  r:trule;
  sl1,sl2:TStringList;
  i,i2:integer;
  fileloc,additem:string;
begin
  sl1:=TStringList.create;

  sl1.LoadFromFile(filename );

  Frules:=Truleslist.Create(true);
  i2:=sl1.Count-1 ;
  for i :=0 to i2-1 do
  begin
    r:=trule.create;
    sl2:=TStringList.Create;
    sl2.Delimiter:=';';
    sl2.StrictDelimiter:=true;
    sl2.DelimitedText:=sl1[i];
    r.func:=StrToInt(sl2[0]);
    r.subfunc:=StrToInt(sl2[1]);
    r.name:=sl2[2];
    Frules.Add(r);
    FreeAndNil(sl2);
  end;
  FreeAndNil(sl1);
end;

function TfuncdefHandler.getName(funct, subfunct: integer): string;
var
  i:integer;
begin
  result:='na';
  for i :=0 to  Frules.Count-1 do
  begin
    if Frules[i].func=funct then
    if Frules[i].subfunc=subfunct then
    begin
      result :=Frules[i].name;
      break;
    end;
  end;

end;

end.

