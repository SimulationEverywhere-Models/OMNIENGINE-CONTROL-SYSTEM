[top]
components : wirelesschannel@WirelessChannel
out : channel_done
in : in 
Link : in channel_go@wirelesschannel
Link : channel_done@wirelesschannel channel_done


[wirelesschannel]
distribution : normal
mean : 4
deviation : 2 