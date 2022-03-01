set ns [new Simulator]

set nr [open out.tr w]
$ns trace-all $nr

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish { } {
    global ns nf nr
    $ns flush-trace
    close $nf
    close $nr
    exec nam out.nam &
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
$ns duplex-link-op $n0 $n1 queuePos 0.5

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
$tcp set window_ 8000
$tcp set packetSize_ 512
set sink [new Agent/TCPSink/DelAck]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns at 0.1 "$ftp start"
$ns at 5 "finish"
$ns run