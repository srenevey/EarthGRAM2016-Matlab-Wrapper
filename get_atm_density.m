% get_atm_density   Atmospheric density.
% 
%   density = get_atm_density(altitude, longitude, latitude, epoch) computes
%   the atmospheric density using EarthGRAM2016.	
% 
%   Inputs:
%     - altitude above sea level (km)
%     - longitude in degrees
%     - latitude in degrees
%     - epoch: char array containing the initial epoch. Must be in the format: 'YYYY-MM-DD hh:mm:ss'
%  
%   Output:
%     - density in kg/m^3
%
%
%   Example:
%     h = 10;
%     lat = 25;
%     lon = 70;
%     epoch = '2019-01-25 14:30:00';
%     density = get_atm_density(h, lat, lon, epoch)