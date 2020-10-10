unit Unit4;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm4 = class(TForm)
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form4: TForm4;

implementation
uses unit2,unit1;

{$R *.dfm}

procedure TForm4.Button1Click(Sender: TObject);
begin    
  Form2.Show;
  Form4.Hide;
end;

procedure TForm4.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  form1.Close;
end;

end.
