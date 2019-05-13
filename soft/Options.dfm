object Parameters: TParameters
  Left = 689
  Top = 175
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
  ClientHeight = 356
  ClientWidth = 474
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 24
    Width = 70
    Height = 13
    Caption = #8470' COM '#1087#1086#1088#1090#1072
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 48
    Width = 233
    Height = 265
    Caption = #1055#1088#1086#1092#1080#1083#1100
    TabOrder = 0
    object D: TLabel
      Left = 16
      Top = 24
      Width = 209
      Height = 13
      Caption = #1042' '#1082#1072#1078#1076#1086#1081' '#1089#1090#1088#1086#1095#1082#1077' '#1095#1077#1088#1077#1079' '#1090#1086#1095#1082#1091' '#1089' '#1079#1072#1087#1103#1090#1086#1081' '
    end
    object Label2: TLabel
      Left = 16
      Top = 40
      Width = 145
      Height = 13
      Caption = #1090#1086#1082' '#1074' '#1084#1080#1083#1083#1080#1072#1084#1087#1077#1088#1072#1093', '#1074#1088#1077#1084#1103' '
    end
    object Label3: TLabel
      Left = 16
      Top = 56
      Width = 87
      Height = 13
      Caption = #1074' '#1084#1080#1083#1083#1080#1089#1077#1082#1091#1085#1076#1072#1093
    end
    object Label7: TLabel
      Left = 48
      Top = 240
      Width = 83
      Height = 13
      Caption = #1055#1077#1088#1080#1086#1076' '#1089#1098#1077#1084#1072','#1089
    end
    object RichEdit1: TRichEdit
      Left = 16
      Top = 72
      Width = 201
      Height = 145
      Lines.Strings = (
        '10;100')
      TabOrder = 0
    end
    object period: TEdit
      Left = 144
      Top = 232
      Width = 57
      Height = 21
      TabOrder = 1
      Text = 'act_time'
    end
  end
  object Button2: TButton
    Left = 152
    Top = 16
    Width = 75
    Height = 25
    Caption = #1047#1072#1076#1072#1090#1100
    TabOrder = 1
    OnClick = Button2Click
  end
  object CSpinEdit1: TCSpinEdit
    Left = 88
    Top = 16
    Width = 57
    Height = 22
    MaxValue = 20
    MinValue = 1
    TabOrder = 2
    Value = 1
  end
  object GroupBox2: TGroupBox
    Left = 248
    Top = 48
    Width = 209
    Height = 265
    Caption = #1040#1082#1090#1080#1074#1072#1094#1080#1103
    TabOrder = 3
    object Label4: TLabel
      Left = 8
      Top = 24
      Width = 40
      Height = 13
      Caption = #1058#1086#1082', '#1084#1040
    end
    object Label5: TLabel
      Left = 8
      Top = 56
      Width = 45
      Height = 13
      Caption = #1042#1088#1077#1084#1103', '#1089
    end
    object Label6: TLabel
      Left = 8
      Top = 88
      Width = 49
      Height = 13
      Caption = #1055#1086#1088#1086#1075','#1084#1040
    end
    object act_cur_e: TCSpinEdit
      Left = 72
      Top = 16
      Width = 57
      Height = 22
      MaxValue = 100
      MinValue = 1
      TabOrder = 0
      Value = 1
    end
    object act_time: TEdit
      Left = 72
      Top = 48
      Width = 57
      Height = 21
      TabOrder = 1
      Text = 'act_time'
    end
    object act_cur_level_e: TCSpinEdit
      Left = 72
      Top = 80
      Width = 57
      Height = 22
      MaxValue = 100
      MinValue = 1
      TabOrder = 2
      Value = 100
    end
  end
  object saveb: TButton
    Left = 272
    Top = 320
    Width = 75
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 4
    OnClick = savebClick
  end
  object loadb: TButton
    Left = 144
    Top = 320
    Width = 75
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 5
    Visible = False
  end
  object Button1: TButton
    Left = 344
    Top = 16
    Width = 105
    Height = 25
    Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1062#1040#1055
    TabOrder = 6
    OnClick = Button1Click
  end
end
