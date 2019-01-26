unit Fdebug;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls;

type

  { TForm_debug }

  TForm_debug = class(TForm)
    procedure FormClose(Sender: TObject; var CloseAction: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure Frame1Click(Sender: TObject);
    procedure Panel1Click(Sender: TObject);
  private

  public

  end;

var
  Form_debug: TForm_debug;

implementation

{$R *.lfm}

{ TForm_debug }

procedure TForm_debug.Frame1Click(Sender: TObject);
begin

end;

procedure TForm_debug.Panel1Click(Sender: TObject);
begin

end;

procedure TForm_debug.FormClose(Sender: TObject; var CloseAction: TCloseAction);
begin
  CloseAction:= caFree;
end;

procedure TForm_debug.FormCreate(Sender: TObject);
begin

end;

end.

