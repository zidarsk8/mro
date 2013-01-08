package vaja04;

network omrezje
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
            @display("p=30,39");
        }
        server1: server {
            @display("p=447,39");
        }
    connections:
        client.out --> C_up --> server1.in;
        server1.out --> C_down --> client.in;
}
