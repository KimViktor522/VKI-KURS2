unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation   
uses unit2;

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
  Timer1.Enabled:=true;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin   
  Timer1.Enabled:=false;
  Form2.Show;
  Form1.Hide;
end;

end.
