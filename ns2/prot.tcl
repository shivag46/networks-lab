set ns [new Simulator]

set nr [open dv.tr w]
set nf [open dv.nam w]
$ns trace-all $nr
$ns namtrace-all $nf

proc finish { } {
	global ns nf nr
	$ns flush-trace
	close $nf
	close $nr
	exec nam dv.nam &
	exit 0 
}

#for { set i 0 } { $i < 12} { incr i 1 } { set n($i) [$ns node]} 

for { set i 0 } { $i < 12 } { incr i } {
	set n($i) [$ns node]
}

for { set i 0 } { $i < 8 } { incr i 1 } {
	$ns duplex-link $n($i) $n([expr $i+1]) 1Mb 10ms DropTail
}

$ns duplex-link $n(0) $n(8) 1Mb 10ms DropTail
$ns duplex-link $n(1) $n(10) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(9) 1Mb 10ms DropTail
$ns duplex-link $n(9) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(10) $n(11) 1Mb 10ms DropTail
$ns duplex-link $n(11) $n(5) 1Mb 10ms DropTail

$ns duplex-link-op $n(0) $n(1) orient right
$ns duplex-link-op $n(1) $n(2) orient down
$ns duplex-link-op $n(2) $n(3) orient down
$ns duplex-link-op $n(3) $n(4) orient left
$ns duplex-link-op $n(4) $n(5) orient left
$ns duplex-link-op $n(5) $n(6) orient left
$ns duplex-link-op $n(6) $n(7) orient left
$ns duplex-link-op $n(7) $n(8) orient up
$ns duplex-link-op $n(8) $n(0) orient up
$ns duplex-link-op $n(5) $n(11) orient up 

$ns duplex-link-op $n(0) $n(9) orient right-down
$ns duplex-link-op $n(9) $n(11) orient right
$ns duplex-link-op $n(11) $n(10) orient right
$ns duplex-link-op $n(1) $n(10) orient left-down

#0 to 5 udp
set udp0 [new Agent/UDP]
$ns attach-agent $n(0) $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.05
$cbr0 attach-agent $udp0

set null0 [new Agent/Null]
$ns attach-agent $n(5) $null0

$ns connect $udp0 $null0

#1 to 5 udp
set udp1 [new Agent/UDP]
$ns attach-agent $n(1) $udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.05
$cbr1 attach-agent $udp1

set null1 [new Agent/Null]
$ns attach-agent $n(5) $null1

$ns connect $udp1 $null1

$ns rtproto LS 
 
#Make link 11-5 and 7-6 down for 1 second 
$ns rtmodel-at 2.0 down $n(11) $n(5) 
$ns rtmodel-at 3.0 down $n(7) $n(6) 
$ns rtmodel-at 6.0 up $n(11) $n(5) 
$ns rtmodel-at 7.0 up $n(7) $n(6) 

#Set color to packets
$udp0 set fid_ 1
$udp1 set fid_ 2
$ns color 1 Red
$ns color 2 Green

#Timings
$ns at 0.2 "$cbr0 start"
$ns at 0.3 "$cbr1 start"
$ns at 45.0 "finish"

$ns run



Socket prog - conversion functions
System calls
Bit/Byte stuffing
