[top]
components : createcapture@CreateCapture createfilter@CreateFilter
out : capture_created
out: filter_code
in : in
Link : in cmd_in@createcapture
Link : filter_go@createcapture    filter_go@createfilter
Link : filter_done@createfilter  filter_done@createcapture
Link : capture_created@createcapture capture_created
Link : filter_out@createfilter filter_code

[createcapture]
distribution : normal
mean : 4
deviation : 2 

[createfilter]
distribution : normal
mean : 4
deviation : 2