[top]
components : stopcapture@StopCapture
out : capture_stopped
in : in
Link : in cmd_in@stopcapture
Link : capture_stopped@stopcapture capture_stopped

[stopcapture]
distribution : normal
mean : 4
deviation : 2