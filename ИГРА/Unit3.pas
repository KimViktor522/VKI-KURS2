unit Unit3;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm3 = class(TForm)
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form3: TForm3;

implementation
uses unit2,unit1;
{$R *.dfm}

procedure TForm3.Button1Click(Sender: TObject);
begin 
  Form2.Show;
  Form3.Hide;
end;

procedure TForm3.FormClose(Sender: TObject; var Action: TCloseAction);
begin
	Form1.close;
end;

end.
