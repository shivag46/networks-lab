set ns [new Simulator]
# Set color to the flow packets
$ns color 1 Blue
$ns color 2 Red
set nf [open out.nam w]
$ns namtrace-all $nf
# set nr [open out.tr w]
# $ns trace-all $nr
# End procedure
proc finish {} {
global ns nf nr
$ns flush-trace
close $nf
# close $nr
exec nam out.nam &
exit 0
}

set n0 [$ns node] 
set n1 [$ns node] 
set n2 [$ns node]
set n3 [$ns node] 
set n4 [$ns node] 
set n5 [$ns node]
# Create network connections
$ns duplex-link $n0 $n2 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns simplex-link $n3 $n2 10Mb 100ms DropTail
$ns simplex-link $n2 $n3 10Mb 100ms DropTail
$ns duplex-link $n3 $n4 10Mb 40ms DropTail
$ns duplex-link $n3 $n5 10Mb 40ms DropTail
# Orient the connections
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns simplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right-up
$ns duplex-link-op $n3 $n5 orient right-down

$ns queue-limit $n2 $n3 10
$ns duplex-link-op $n2 $n3 queuePos 0.5
# Create tcp connection 
set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp 
set sink [new Agent/TCPSink/DelAck]
$ns attach-agent $n4 $sink
$ns connect $tcp $sink
$tcp set fid_ 1
$tcp set window_ 8000
$tcp set packetSize_ 512
# Connect TCP to FTP application
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

# Create UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp 
set null [new Agent/Null] 
$ns attach-agent $n5 $null
$ns connect $udp $null
$udp set fid_ 2
# Connect UDP to CBR Application
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

#$cbr set type_ CBR
$cbr set packet_size_ 1024
$cbr set rate_ 1Mb
$cbr set random_ false
# Timestamp flow animation
$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 4.5 "$ftp stop"
$ns at 5.0 "$cbr stop"

$ns at 5.0 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n4 $sink"
$ns at 5.5 "finish"
# Run Simulation
$ns run