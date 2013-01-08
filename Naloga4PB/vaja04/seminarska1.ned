package vaja04;

network seminarska1
{
    parameters:
        int up_datarate @unit(bps) = default(1 Mbps);
        int up_delay @unit(s) = default(100 us);
        double up_ber = default(1e-10);
        int down_datarate @unit(bps) = default(1 Mbps);
        int down_delay @unit(s) = default(100 us);
        double down_ber = default(1e-10);


    types:
        channel C_up extends ned.DatarateChannel
        {
            datarate = up_datarate;
            delay = up_delay;
            ber = up_ber;
        }

        channel C_down extends ned.DatarateChannel
        {
            datarate = down_datarate;
            delay = down_delay;
            ber = down_ber;
        }

    submodules:
        client: terminal {
            @display("p=20,200");
        }
        router: router {
            @display("p=220,200");
        }
        server1: server {
            @display("p=420,40");
        }
        server2: server {
            @display("p=420,200");
        }
        server3: server {
            @display("p=420,400");
        }


    connections:
        client.out --> C_up --> router.in++;
        server1.out --> C_down --> router.in++;
        server2.out --> C_down --> router.in++;
        server3.out --> C_down --> router.in++;

        router.out++ --> C_down --> client.in;
        router.out++ --> C_up --> server1.in;
        router.out++ --> C_up --> server2.in;
        router.out++ --> C_up --> server3.in;
}
