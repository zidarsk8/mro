package vaja04;

module server
{
    parameters:
        @display("i=block/app");

    gates:
        input in;
        output out;
    submodules:
        servUnit: myQueue {
            @display("p=176,66");
            //resources = 5;
            //serviceTime = 100ms;            
        }

        response: responseGen {
            @display("p=176,188");
        }

        tx: transmitter {
            @display("p=176,299");
        }
        rx: receiver {
            @display("p=59,66");
        }
    connections:
        in --> rx.in++;
        rx.out --> servUnit.in++;
        servUnit.out --> response.in;
        response.out --> tx.in;
        tx.out --> out;
}
