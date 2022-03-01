set ns [new Simulator]

set nf [open ls.nam w]
set tf [open ls.tr w]
$ns trace-all $tf
$ns namtrace-all $nf

proc finish { } { 
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam ls.nam &
    exit 0
}

for { set i 0 } { $i < 12 } {incr i } {
    set n($i) [$ns node]
}

$ns duplex-link $n(0) $n(1) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(2) 1Mb 10ms DropTail
$ns duplex-link $n(2) $n(3) 1Mb 10ms DropTail
$ns duplex-link $n(3) $n(4) 1Mb 10ms DropTail
$ns duplex-link $n(4) $n(5) 1Mb 10ms DropTail
$ns duplex-link $n(5) $n(6) 1Mb 10ms DropTail
$ns duplex-link $n(6) $n(7) 1Mb 10ms DropTail
$ns duplex-link $n(7) $n(8) 1Mb 10ms DropTail
$ns duplex-link $n(8) $n(0) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(9) 1Mb 10ms DropTail
$ns duplex-link $n(9) $n(10) 1Mb 10ms DropTail
$ns duplex-link $n(10) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(11) $n(1) 1Mb 10ms DropTail
$ns duplex-link $n(10) $n(5) 1Mb 10ms DropTail

$ns duplex-link-op $n(0) $n(1) orient right
$ns duplex-link-op $n(1) $n(2) orient down
$ns duplex-link-op $n(2) $n(3) orient down
$ns duplex-link-op $n(4) $n(3) orient right
$ns duplex-link-op $n(5) $n(4) orient right
$ns duplex-link-op $n(6) $n(5) orient right
$ns duplex-link-op $n(7) $n(6) orient right
$ns duplex-link-op $n(7) $n(8) orient up
$ns duplex-link-op $n(8) $n(0) orient up
$ns duplex-link-op $n(0) $n(9) orient right-down
$ns duplex-link-op $n(9) $n(10) orient right
$ns duplex-link-op $n(10) $n(11) orient right
$ns duplex-link-op $n(11) $n(1) orient right-up
$ns duplex-link-op $n(5) $n(10) orient up

#0 to 5 udp
set udp0 [new Agent/UDP]
$ns attach-agent $n(0) $udp0
set null0 [new Agent/Null]
$ns attach-agent $n(5) $null0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$ns connect $udp0 $null0

$cbr0 set interval_ 0.05
$cbr0 set packetSize_ 500

$ns rtproto LS

$ns rtmodel-at 0.4 down $n(5) $n(10) 
$ns rtmodel-at 0.7 up $n(5) $n(10) 

$udp0 set fid_ 1
$ns color 1 Red

$ns at 0.1 "$cbr0 start"
$ns at 10 "finish"

$ns run