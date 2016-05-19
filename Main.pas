unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Winsock2, ComCtrls;

type
  TForm1 = class(TForm)
    edt1: TEdit;
    edt2: TEdit;
    btn1: TButton;
    stat1: TStatusBar;
    procedure btn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

type TMacAddress = array [1..6] of byte;

var
  Form1: TForm1;

function SendARP(const DestIP, SrcIP: ULONG;
                   pMacAddr: PULONG;
                   var PhyAddrLen: ULONG): DWORD; stdcall; external 'IPHLPAPI.DLL';

implementation

{$R *.dfm}

function getmac(Value: TMacAddress; Length: DWORD): String;
var i: integer;
begin
 if Length = 0 then Result := 'MAC адрес не найден' else begin
  Result:= '';
  for i:= 1 to Length - 1 do
   Result:= Result + IntToHex(Value[i], 2) + ':';
  Result:= Result + IntToHex(Value[Length], 2)
 end
end;

procedure TForm1.btn1Click(Sender: TObject);
var DestIP, SrcIP: ULONG;
     pMacAddr: TMacAddress;
     PhyAddrLen: ULONG;
begin
 DestIP:= inet_addr(pchar(edt1.text));
 PhyAddrLen:= 6;
 SendArp(DestIP, 0, @pMacAddr, PhyAddrLen);
 edt2.text:= getmac(pMacAddr, PhyAddrLen)
 end;
 
end.

