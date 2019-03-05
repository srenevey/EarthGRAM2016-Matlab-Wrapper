% Get the atmospheric density
h = 10;
lat = 25;
lon = 70;
epoch = '2019-01-25 14:30:00';
density = get_atm_density(h, lat, lon, epoch)
