wifi.setmode(wifi.STATION)
wifi.sta.config("<name of your wi-fi>","<wi-fi password>")
wifi.sta.connect()
tmr.alarm(1, 1000, 1, function()
     if wifi.sta.getip() == nil then
         print("Connecting...")
     else
         tmr.stop(1)
         print("Connected, IP is "..wifi.sta.getip())
     end
end)
pin = 6
status, temp, humi, temp_dec, humi_dec = dht.read(pin)
if status == dht.OK then
    -- Integer firmware using this example
    print(string.format("DHT Temperature:%d.%03d;Humidity:%d.%03d\r\n",
          math.floor(temp),
          temp_dec,
          math.floor(humi),
          humi_dec
    ))

    -- Float firmware using this example
    print("DHT Temperature:"..temp..";".."Humidity:"..humi)

elseif status == dht.ERROR_CHECKSUM then
    print( "DHT Checksum error." )
elseif status == dht.ERROR_TIMEOUT then
    print( "DHT timed out." )
end
        srv=net.createServer(net.TCP)
        srv:listen(80,function(conn)
        conn:on("receive", function(client,request)
        local buf = "";
        local buf1 = "";
        local buf2 = "";
        buf = buf.."<h1> Sensor Readings</h1>";
        buf1 = buf1.."<h2> Temperature </h2>"
        buf2 = buf2.."<h2> Humidity </h2>"
        client:send(buf);
        client:send(buf1);
        client:send(temp);
        client:send(buf2);
        client:send(humi);
        end)
        end)
