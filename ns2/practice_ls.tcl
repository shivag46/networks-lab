set ns [new Simulator]

set nr [open ls.tr w]
set nf [open ls.nam w]

$ns trace-all $nr
$ns namtrace-all $nf
proc finish { } {
    global nr nf ns
    $ns flush-trace
    close $nf
    close $nr
    exec nam ls.nam & 
    exit 0
}

for { set i 0 } { $i < 12 } { incr i } { set n($i) [$ns node] }

$ns duplex-link $n(0) $n(1) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 1Mb 10ms DropTail
$ns duplex-link $n(2) $n(3) 1Mb 10ms DropTail
$ns duplex-link $n(3) $n(4) 1Mb 10ms DropTail
$ns duplex-link $n(4) $n(5) 1Mb 10ms DropTail
$ns duplex-link $n(5) $n(6) 1Mb 10ms DropTail
$ns duplex-link $n(6) $n(7) 1Mb 10ms DropTail
$ns duplex-link $n(7) $n(8) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(8) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(9) 1Mb 10ms DropTail
$ns duplex-link $n(9) $n(10) 1Mb 10ms DropTail
$ns duplex-link $n(10) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(10) $n(5) 1Mb 10ms DropTail

$ns duplex-link-op $n(0) $n(1) orient right
$ns duplex-link-op $n(1) $n(2) orient down
$ns duplex-link-op $n(2) $n(3) orient down
$ns duplex-link-op $n(3) $n(4) orient left
$ns duplex-link-op $n(4) $n(5) orient left
$ns duplex-link-op $n(5) $n(6) orient left
$ns duplex-link-op $n(6) $n(7) orient left
$ns duplex-link-op $n(7) $n(8) orient up
$ns duplex-link-op $n(0) $n(9) orient right-down
$ns duplex-link-op $n(0) $n(8) orient down
$ns duplex-link-op $n(9) $n(10) orient right
$ns duplex-link-op $n(10) $n(11) orient right
$ns duplex-link-op $n(1) $n(11) orient left-down
$ns duplex-link-op $n(5) $n(10) orient up

set udp0 [new Agent/UDP]
$udp0 set fid_ 1
$ns attach-agent $n(0) $udp0
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.05
$cbr attach-agent $udp0
set null0 [new Agent/Null]
$ns attach-agent $n(5) $null0
$ns connect $udp0 $null0 

$ns color 1 Red
$ns rtproto LS
$ns rtmodel-at 5 down $n(5) $n(10)
$ns at 0.1 "$cbr start"
$ns at 45 "finish"

$ns run