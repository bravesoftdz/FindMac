object Form1: TForm1
  Left = 208
  Top = 195
  Width = 179
  Height = 130
  Caption = 'red911'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object edt1: TEdit
    Left = 0
    Top = 0
    Width = 161
    Height = 21
    ImeName = 'Russian'
    TabOrder = 0
    Text = '10.0.0.1'
  end
  object edt2: TEdit
    Left = 0
    Top = 24
    Width = 161
    Height = 21
    ImeName = 'Russian'
    TabOrder = 1
  end
  object btn1: TButton
    Left = 0
    Top = 48
    Width = 161
    Height = 25
    Caption = 'btn1'
    TabOrder = 2
    OnClick = btn1Click
  end
  object stat1: TStatusBar
    Left = 0
    Top = 73
    Width = 163
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
end
