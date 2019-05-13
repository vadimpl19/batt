object MainForm: TMainForm
  Left = 464
  Top = 147
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Battery Activator'
  ClientHeight = 426
  ClientWidth = 808
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000990000000000000000000000000999999900000
    0000000000000000999999999990000000000000000999999999999999000000
    0000000099999999999999999900000000999999999999999999999990000009
    9999999999999999999999999000999999999999999999999999999900000999
    9999999999999999999999900000009999999999999999999999999000000099
    99999999999999999000000000000009999999999999990000CCCC0000000000
    999999999990000CCCCCCC0000000000999999990000CCCCCCCCCC0000000000
    099990000CCCCCCCCCCCC00000000000000000CCCCCCCCCCCCCCC00000000000
    000CCCCCCCCCCCCCCCCC000000000000000CCCCCCCCCCCCCCCC0000000000000
    0000CCCCCCCCCCCCCC0000000000000000000CCCCCCCCCCCCC00000000000000
    00000CCCCCCCC0000000000000000000000000CCCC0000BBB000000000000000
    00000000000BBBBB000000000000000000000000BBBBBBB00000000000000000
    00000000BBBBBBB00000000000000000000000000BBBBB000000000000000000
    0000000000BBBB00000000000000000000000000000BB0000000000000000000
    00000000000BB0000000000000000000000000000000B000000000000000FFFF
    FFFFFFFFFFFFFFFFFFF9FFFFFF01FFFFF001FFFE0003FFF00003FC000007E000
    00070000000F8000001FC000001FC00007FFE0003C3FF001E03FF00F003FF878
    007FFFC0007FFE0000FFFE0001FFFF0003FFFF8003FFFF807FFFFFC3C7FFFFFE
    0FFFFFF01FFFFFF01FFFFFF83FFFFFFC3FFFFFFE7FFFFFFE7FFFFFFF7FFF}
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object RichEdit1: TRichEdit
    Left = 400
    Top = 0
    Width = 393
    Height = 393
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 400
    Width = 808
    Height = 26
    Panels = <
      item
        Width = 350
      end
      item
        Width = 538
      end>
    SimplePanel = False
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 616
    Width = 345
    Height = 25
    Min = 0
    Max = 100
    Step = 5
    TabOrder = 2
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 313
    Height = 57
    Caption = #1056#1077#1078#1080#1084
    Enabled = False
    TabOrder = 3
    object ActivB: TSpeedButton
      Left = 8
      Top = 16
      Width = 137
      Height = 33
      GroupIndex = 1
      Down = True
      Caption = #1040#1082#1090#1080#1074#1072#1094#1080#1103
      OnClick = ActivBClick
    end
    object byProfileB: TSpeedButton
      Left = 168
      Top = 16
      Width = 137
      Height = 33
      GroupIndex = 1
      Caption = #1056#1072#1079#1088#1103#1076' '#1087#1086' '#1087#1088#1086#1092#1080#1083#1102
      OnClick = byProfileBClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 80
    Width = 393
    Height = 313
    Caption = #1058#1077#1082#1091#1097#1080#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
    Enabled = False
    TabOrder = 4
    object batbox1: TGroupBox
      Left = 8
      Top = 24
      Width = 185
      Height = 137
      Caption = #1041#1072#1090#1072#1088#1077#1103' 1'
      TabOrder = 0
      object Label6: TLabel
        Left = 8
        Top = 16
        Width = 74
        Height = 13
        Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077','#1042
      end
      object Label7: TLabel
        Left = 8
        Top = 40
        Width = 37
        Height = 13
        Caption = #1058#1086#1082','#1084#1040
      end
      object Label8: TLabel
        Left = 8
        Top = 64
        Width = 78
        Height = 13
        Caption = #1042#1088#1077#1084#1103' '#1088#1072#1079#1088#1103#1076#1072
      end
      object Label9: TLabel
        Left = 8
        Top = 96
        Width = 73
        Height = 13
        Caption = #1045#1084#1082#1086#1089#1090#1100', '#1084#1040#1063
      end
      object Label1: TLabel
        Left = 48
        Top = 120
        Width = 34
        Height = 13
        Caption = #1057#1090#1072#1090#1091#1089
      end
      object batst1: TLabel
        Left = 96
        Top = 120
        Width = 20
        Height = 13
        Caption = 'N/A'
      end
      object batv1: TEdit
        Left = 96
        Top = 16
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 0
      end
      object batc1: TEdit
        Left = 96
        Top = 40
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 1
      end
      object batt1: TEdit
        Left = 96
        Top = 64
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 2
      end
      object batch1: TEdit
        Left = 96
        Top = 88
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 3
      end
    end
    object batbox3: TGroupBox
      Left = 8
      Top = 168
      Width = 185
      Height = 137
      Caption = #1041#1072#1090#1072#1088#1077#1103' 3'
      TabOrder = 1
      object Label18: TLabel
        Left = 8
        Top = 16
        Width = 74
        Height = 13
        Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077','#1042
      end
      object Label19: TLabel
        Left = 8
        Top = 40
        Width = 37
        Height = 13
        Caption = #1058#1086#1082','#1084#1040
      end
      object Label20: TLabel
        Left = 8
        Top = 64
        Width = 78
        Height = 13
        Caption = #1042#1088#1077#1084#1103' '#1088#1072#1079#1088#1103#1076#1072
      end
      object Label21: TLabel
        Left = 8
        Top = 96
        Width = 73
        Height = 13
        Caption = #1045#1084#1082#1086#1089#1090#1100', '#1084#1040#1063
      end
      object batst3: TLabel
        Left = 96
        Top = 120
        Width = 20
        Height = 13
        Caption = 'N/A'
      end
      object Label3: TLabel
        Left = 48
        Top = 120
        Width = 34
        Height = 13
        Caption = #1057#1090#1072#1090#1091#1089
      end
      object batv3: TEdit
        Left = 96
        Top = 16
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 0
      end
      object batc3: TEdit
        Left = 96
        Top = 40
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 1
      end
      object batt3: TEdit
        Left = 96
        Top = 64
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 2
      end
      object batch3: TEdit
        Left = 96
        Top = 88
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 3
      end
    end
    object batbox4: TGroupBox
      Left = 200
      Top = 168
      Width = 185
      Height = 137
      Caption = #1041#1072#1090#1072#1088#1077#1103' 4'
      Enabled = False
      TabOrder = 2
      Visible = False
      object Label22: TLabel
        Left = 8
        Top = 16
        Width = 74
        Height = 13
        Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077','#1042
      end
      object Label23: TLabel
        Left = 8
        Top = 40
        Width = 37
        Height = 13
        Caption = #1058#1086#1082','#1084#1040
      end
      object Label24: TLabel
        Left = 8
        Top = 64
        Width = 78
        Height = 13
        Caption = #1042#1088#1077#1084#1103' '#1088#1072#1079#1088#1103#1076#1072
      end
      object Label25: TLabel
        Left = 8
        Top = 96
        Width = 73
        Height = 13
        Caption = #1045#1084#1082#1086#1089#1090#1100', '#1084#1040#1063
      end
      object batst4: TLabel
        Left = 96
        Top = 120
        Width = 20
        Height = 13
        Caption = 'N/A'
      end
      object Label4: TLabel
        Left = 48
        Top = 120
        Width = 34
        Height = 13
        Caption = #1057#1090#1072#1090#1091#1089
      end
      object batv4: TEdit
        Left = 96
        Top = 16
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 0
      end
      object batc4: TEdit
        Left = 96
        Top = 40
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 1
      end
      object batt4: TEdit
        Left = 96
        Top = 64
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 2
      end
      object batch4: TEdit
        Left = 96
        Top = 88
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 3
      end
    end
    object batbox2: TGroupBox
      Left = 200
      Top = 24
      Width = 185
      Height = 137
      Caption = #1041#1072#1090#1072#1088#1077#1103' 2'
      TabOrder = 3
      object Label10: TLabel
        Left = 8
        Top = 16
        Width = 74
        Height = 13
        Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077','#1042
      end
      object Label11: TLabel
        Left = 8
        Top = 40
        Width = 37
        Height = 13
        Caption = #1058#1086#1082','#1084#1040
      end
      object Label12: TLabel
        Left = 8
        Top = 64
        Width = 78
        Height = 13
        Caption = #1042#1088#1077#1084#1103' '#1088#1072#1079#1088#1103#1076#1072
      end
      object Label13: TLabel
        Left = 8
        Top = 96
        Width = 73
        Height = 13
        Caption = #1045#1084#1082#1086#1089#1090#1100', '#1084#1040#1063
      end
      object batst2: TLabel
        Left = 96
        Top = 120
        Width = 20
        Height = 13
        Caption = 'N/A'
      end
      object Label2: TLabel
        Left = 48
        Top = 120
        Width = 34
        Height = 13
        Caption = #1057#1090#1072#1090#1091#1089
      end
      object batv2: TEdit
        Left = 96
        Top = 16
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 0
      end
      object batc2: TEdit
        Left = 96
        Top = 40
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 1
      end
      object batt2: TEdit
        Left = 96
        Top = 64
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 2
      end
      object batch2: TEdit
        Left = 96
        Top = 88
        Width = 73
        Height = 21
        Enabled = False
        TabOrder = 3
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.rtf'
    Filter = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1086#1090#1095#1077#1090'|*.rtf'
    Left = 800
    Top = 352
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.ROM'
    Filter = 'ROM|*.rom;*.ROM|All Types|*.*'
    Left = 704
    Top = 352
  end
  object PopupMenu1: TPopupMenu
    Left = 672
    Top = 352
    object N1: TMenuItem
      Caption = #1054#1095#1080'c'#1090#1080#1090#1100
      ShortCut = 16452
      OnClick = N1Click
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 568
    Top = 352
  end
  object touttimer: TTimer
    OnTimer = touttimerTimer
    Left = 736
    Top = 80
  end
  object MainMenu1: TMainMenu
    Left = 336
    Top = 192
    object N2: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    end
    object N4: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = N4Click
    end
  end
end
