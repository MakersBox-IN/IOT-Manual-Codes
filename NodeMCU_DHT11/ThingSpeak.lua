


dht_pin=7




           
tmr.alarm(1, 1000, 1, function()
     if wifi.sta.getip() == nil 
     then
         print("Connecting...")
     else
         tmr.stop(1)
         print("Connected, IP is "..wifi.sta.getip())
     end
     end)

function postThingSpeak(level)
    connout = nil
    connout = net.createConnection(net.TCP, 0)
 
    connout:on("receive", function(connout, payloadout)
        if (string.find(payloadout, "Status: 200 OK") ~= nil) then
            print("Posted OK");
        end
    end)
 
    connout:on("connection", function(connout, payloadout)
 
        print ("Posting...");    
 
        connout:send("GET /update?api_key=<WriteAPIkey of channel at ThingSpeak>&field1=&field2="..temp.."."..temp_dec
        .. " HTTP/1.1\r\n"
        .. "Host: api.thingspeak.com\r\n"
        .. "Connection: close\r\n"
        .. "Accept: */*\r\n"
        .. "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n"
        .. "\r\n")
    end)
 
    connout:on("disconnection", function(connout, payloadout)
        connout:close();
        collectgarbage();
    end)
 
    connout:connect(80,'api.thingspeak.com')
end

        tmr.alarm(2, 10000, 1, function()
            status, temp, humi, temp_dec, humi_dec = dht.read(dht_pin)
            if status == dht.OK then
                print(string.format("DHT Temperature:%d.%03d;Humidity:%d.%03d\r\n",
                math.floor(temp),
                temp_dec,
                math.floor(humi),
                humi_dec
                ))
                print("DHT Temperature:"..temp..";".."Humidity:"..humi)
            elseif status == dht.ERROR_CHECKSUM then
                print( "DHT Checksum error." )
            elseif status == dht.ERROR_TIMEOUT then
                print( "DHT timed out." )
            end

 
            postThingSpeak(0)
        end)
