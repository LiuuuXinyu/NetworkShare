~RButton::
Hotkey, MButton, Paste
Keywait, LButton, d, t0.2
        ; 参数 d （down）表示按键处于按下状态，t0.2 是等待 0.2 秒。
if errorlevel = 0
        ; 如果返回的错误码（errorlevel，很多的 AHK 命令都会返回错误码，这个变量是 AHK 自带的。）是 0 ，也就是说上面的 Keywait 命令执行成功。如果是 1 的话，说明 Keywait 执行失败。失败说明我们按下了右键之后，没有在 0.2 秒内按下左键。
{
KeyWait, LButton, U
        ; 来自 norchy 的修改 http://ahk.5d6d.com/viewthread.php?tid=211。如 word，LButton + RButton 后按 Ctrl + C 是没有效果的，此时这个功能会失败。加入一句 KeyWait, LButton, U 可解决此问题。
send ^c
Hotkey, MButton, on
}
return

Paste:
send ^v
Hotkey, MButton, off
return

^MButton::
send ^v
return

