set ns [new Simulator]

set tf [open out2.tr w]
set nf [open out2.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

proc finish { } {
    global ns nf tf
    $ns flush-trace
    close $nf
    close $tf
    exec nam out2.nam &
    exit 0 
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right 

$ns queue-limit $n0 $n1 10
$ns queue-limit $n1 $n2 10
$ns duplex-link-op $n1 $n2 queuePos 0.5 

#Set tcp
set tcp [new Agent/TCP/Reno]
$ns attach-agent $n0 $tcp 
set sink [new Agent/TCPSink/DelAck]
$ns attach-agent $n2 $sink
$tcp set fid_ 1
$tcp set window_ 8000
$tcp set packetSize_ 512
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns connect $tcp $sink

$ns at 0.2 "$ftp start"
$ns at 10 "finish"

$ns run