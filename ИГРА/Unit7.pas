unit Unit7;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm7 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Label1: TLabel;
    procedure FormShow(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form7: TForm7;
implementation
uses unit1,unit2,unit5;
{$R *.dfm}

procedure TForm7.Button1Click(Sender: TObject);
begin
  Form7.Hide;
  Form5.show;
end;

procedure TForm7.Button2Click(Sender: TObject);
begin
  Form7.Hide;
  Form2.Show;
end;

procedure TForm7.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  form1.Close;
end;

procedure TForm7.FormShow(Sender: TObject);
begin
  Label1.caption:='Проиграл';
end;

end.
