unit dmod1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, SdpoSerial;

type

  { TDataModule1 }

  TDataModule1 = class(TDataModule)
    SdpoSerial1: TSdpoSerial;
    procedure SdpoSerial1RxData(Sender: TObject);
  private

  public

  end;

var
  DataModule1: TDataModule1;

implementation

{$R *.lfm}

{ TDataModule1 }

procedure TDataModule1.SdpoSerial1RxData(Sender: TObject);
begin

end;

end.

