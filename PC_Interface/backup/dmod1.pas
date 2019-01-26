unit dmod1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, SdpoSerial;

type

  { TDataModule1 }

  TDataModule1 = class(TDataModule)
    SdpoSerial1: TSdpoSerial;
  private

  public

  end;

var
  DataModule1: TDataModule1;

implementation

{$R *.lfm}

end.

