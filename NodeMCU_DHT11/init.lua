print('init.lua ver 1.2')
wifi.setmode(wifi.STATION)
print('set mode=STATION (mode='..wifi.getmode()..')')
print('MAC: ',wifi.sta.getmac())
print('chip: ',node.chipid())
print('heap: ',node.heap())
-- wifi config start
wifi.sta.config("<name of your wi-fi connection>","<wi-fi password>")
-- wifi config end
wifi.sta.connect()
dofile("script.lua")
