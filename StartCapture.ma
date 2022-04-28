[top]
components : startcapture@StartCapture wirelesschannel@WirelessChannel
out : capture_started
out : channel_num
in : in
Link : in cmd_in@startcapture
Link : channel_go@startcapture    channel_go@wirelesschannel
Link : channel_done@wirelesschannel  channel_done@startcapture
Link : capture_started@startcapture capture_started
Link : channel_out@wirelesschannel channel_num

[startcapture]
distribution : normal
mean : 4
deviation : 2 

[wirelesschannel]
distribution : normal
mean : 4
deviation : 2 