unit Unit6;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm6 = class(TForm)
    Button1: TButton;
    Label1: TLabel;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    procedure Button1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
//    procedure FormCreate(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure RadioButton3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form6: TForm6;
  Sloj:integer;

implementation
uses unit2,unit1;
{$R *.dfm}

procedure TForm6.Button1Click(Sender: TObject);
begin
  Form2.Show;
  Form6.Hide;
end;

procedure TForm6.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  form1.Close;
end;

procedure TForm6.FormCreate(Sender: TObject);
begin   
  Sloj:=1;
end;

procedure TForm6.RadioButton1Click(Sender: TObject);
begin
  Sloj:=1;
end;

procedure TForm6.RadioButton2Click(Sender: TObject);
begin
  Sloj:=2;
end;

procedure TForm6.RadioButton3Click(Sender: TObject);
begin
  Sloj:=3;
end;

end.
