unit Uconnection;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils,SdpoSerial;

type

  { TconnectionHandler }

  TconnectionHandler = class
  constructor Create;
  destructor Destroy; override;
  function connect(serport:string;baud:TBaudRate):Boolean;
  function getMessage():string;
  procedure SerialConRxData(Sender: TObject);
  private
     SerialCon: TSdpoSerial;
  public

  end;
implementation

{ TconnectionHandler }

constructor TconnectionHandler.Create;
begin
  SerialCon:=TSdpoSerial.Create(nil);
  SerialCon.OnRxData:=@SerialConRxData;


end;

destructor TconnectionHandler.Destroy;
begin
  inherited Destroy;
end;

function TconnectionHandler.connect(serport: string; baud: TBaudRate): Boolean;
begin
  SerialCon.BaudRate:=baud;
  SerialCon.Device:=serport;

end;

function TconnectionHandler.getMessage(): string;
begin

end;

procedure TconnectionHandler.SerialConRxData(Sender: TObject);
begin

end;

end.

