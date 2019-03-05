% Path to EarthGRAM2016
root = pwd;
EarthGRAM2016_model_path = [root, filesep, 'EarthGRAM2016', filesep];
    

% Check path to EarthGRAM2016 model
if (~(exist(EarthGRAM2016_model_path, 'dir') == 7))
    error('The path to the Earth GRAM model is invalid.');
end


% Check if NameRef.txt exists
if (~(exist([EarthGRAM2016_model_path, 'NameRef.txt'], 'file') == 2))
    error('The file NameRef.txt in EarthGRAM2016 could not be found.');
end


% Define the include directory
include_dir = ['-I', EarthGRAM2016_model_path, 'Source'];


% Unix
if (computer('arch') == "glnxa64" || computer('arch') == "maci64")
    lib_path = ['-L', EarthGRAM2016_model_path, 'Source/build'];
    EarthGRAM2016_macro = ['-DEARTHGRAM2016_PATH=\"', EarthGRAM2016_model_path, '\"'];

    
% Windows
elseif (computer('arch') == "win64")
    lib_path = ['-L', EarthGRAM2016_model_path, 'Source\build\Release'];
    EarthGRAM2016_macro = ['-DEARTHGRAM2016_PATH=\\"', strrep(EarthGRAM2016_model_path,'\','\\'), '\\"'];
end


mex('-output', 'get_atm_density', EarthGRAM2016_macro, include_dir, lib_path, '-lEarthGRAM2016', 'mex_wrapper.cpp')

clear