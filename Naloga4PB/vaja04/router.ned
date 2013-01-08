package vaja04;

module router
{
    parameters:
        @display("i=block/routing");

    gates:
        input in[];
        output out[];

    submodules:
        rx: receiver {
            @display("p=63,137");
        }
        tx0: transmitter {
            @display("p=337,42");
        }
        tx1: transmitter {
            @display("p=337,104");
        }
        tx2: transmitter {
            @display("p=337,170");
        }
        tx3: transmitter {
            @display("p=337,235");
        }
        switch: switchMM1 {
            @display("p=191,137");
        }
    connections:
        in[0] --> rx.in++;
        in[1] --> rx.in++;
        in[2] --> rx.in++;
        in[3] --> rx.in++;
        
        rx.out --> switch.in;
        switch.out++ --> tx0.in;
        switch.out++ --> tx1.in;
        switch.out++ --> tx2.in;
        switch.out++ --> tx3.in;
        
        tx0.out --> out++;
        tx1.out --> out++;
        tx2.out --> out++;
        tx3.out --> out++;
}
