wifi.setmode(wifi.STATION)
wifi.sta.config("yourSSID","yourPassword")

led1 = 4
gpio.mode(led1, gpio.OUTPUT)

srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
if wifi.sta.getip() == nil 
   then
       print("Connecting...")
   else
       print("Connected, IP is "..wifi.sta.getip())
       end
  conn:on("receive", function(client,request)
      local buf = "";
      local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
      if(method == nil)then
          _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
      end
      local _GET = {}
      if (vars ~= nil)then
          for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
              _GET[k] = v
          end
      end
      buf = buf.."<h1> ESP8266 Web Server</h1>";
      buf = buf.."<p>GPIO0 <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp;<a href=\"?pin=OFF1\"><button>OFF</button></a></p>";
      
      local _on,_off = "",""
      if(_GET.pin == "ON1")then
            gpio.write(led1, gpio.HIGH);
      elseif(_GET.pin == "OFF1")then
            gpio.write(led1, gpio.LOW);
      
      end
      client:send(buf);
      client:close();
      collectgarbage();
  end)
end)
