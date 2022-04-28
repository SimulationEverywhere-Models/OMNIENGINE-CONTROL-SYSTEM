[top]
components : create start stop@StopCapture 
out : capture_created
out : filter_code
out : capture_started
out : channel_num
out : capture_stopped
in :  create_capture
in :  start_capture
in :  stop_capture
Link : create_capture in@create 
Link : start_capture in@start 
Link : stop_capture cmd_in@stop
Link : capture_created@create capture_created
Link : filter_code@create filter_code
Link : capture_started@start capture_started
Link : channel_num@start channel_num
Link : capture_stopped@stop capture_stopped


[create]
components : createcapture@CreateCapture createfilter@CreateFilter
out : capture_created
out: filter_code
in : in
Link : in cmd_in@createcapture
Link : filter_go@createcapture    filter_go@createfilter
Link : filter_done@createfilter  filter_done@createcapture
Link : capture_created@createcapture capture_created
Link : filter_out@createfilter filter_code

[start]
components : startcapture@StartCapture wirelesschannel@WirelessChannel
out : capture_started
out : channel_num
in : in
Link : in cmd_in@startcapture
Link : channel_go@startcapture    channel_go@wirelesschannel
Link : channel_done@wirelesschannel  channel_done@startcapture
Link : capture_started@startcapture capture_started
Link : channel_out@wirelesschannel channel_num

[createcapture]
distribution : normal
mean : 4
deviation : 2 

[createfilter]
distribution : normal
mean : 4
deviation : 2

[startcapture]
distribution : normal
mean : 4
deviation : 2 

[wirelesschannel]
distribution : normal
mean : 4
deviation : 2 

[stop]
distribution : normal
mean : 4
deviation : 2