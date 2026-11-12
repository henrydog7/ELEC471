% Vehicle 1 = 2019 Honda Civic Sport
veh_data(1).speeds = 1000:250:6000; %rpm
veh_data(1).torques = [87, 111, 129, 138, 151, 161, 166, 171, 175, 178, ...
                    180, 182, 185,186, 185, 183, 181, 180, 179, 178, 177];
veh_data(1).gears = [3.643,2.080,1.361,1.024,0.830,0.686];
veh_data(1).reverse = 3.673;
veh_data(1).final_drive = 4.105;
veh_data(1).gear_eff = 0.88; % includes gear + final drive eff
veh_data(1).width = 1.8; %m
veh_data(1).height = 1.41; %m
veh_data(1).length = 4.64; %m
veh_data(1).mass = 1287; %unloaded kg
veh_data(1).transmission = 1; % 1 = Manual, 0 = Auto
veh_data(1).shift_up_speeds = [
    15 25 35 45 55 0;% inf;   % Low throttle (0%)
    20 30 40 50 60 0;% inf;   % Medium throttle (50%)
    25 35 45 55 65 0;% inf    % Full throttle (100%)
];
veh_data(1).shift_down_speeds = [
    10 20 30 40 50 60;   % Low throttle (0%)
    15 25 35 45 55 65;   % Medium throttle (50%)
    20 30 40 50 60 70    % Full throttle (100%)
];

veh_data(1).wheel_radius = 0.3225; % m = 235/40/R18

% Vehicle 2 = 2024 Subaru Crosstrek Limited
veh_data(2).speeds = 1000:250:6000; %rpm
veh_data(2).torques = [92, 114, 137, 150, 160, 168, 175, 180, 185, 188, ...
                    190, 193, 195, 194, 193, 191, 190, 189, 187, 184, 180];
veh_data(2).gears = [4, 2.646, 1.965, 1.532, 1.199, 0.939, 0.73, 0.56];
veh_data(2).reverse = 4.379;
veh_data(2).final_drive = 3.7;
veh_data(2).gear_eff = 0.92;
veh_data(2).width = 1.8; %m
veh_data(2).height = 1.6; %m
veh_data(2).length = 4.48; %m
veh_data(2).mass = 1519; %unloaded kg
veh_data(2).transmission = 0;
veh_data(2).shift_up_speeds = [
    20 30 40 50 60 70 80 0;% inf;   % Low throttle (0%)
    25 35 45 55 65 75 85 0;% inf;   % Medium throttle (50%)
    30 40 50 60 70 80 90 0;% inf    % Full throttle (100%)
];
veh_data(2).shift_down_speeds = [
    0   15  25  35  45  55  65  75;  % Low throttle (0%)
    10  20  30  40  50  60  70  80;  % Medium throttle (50%)
    15  25  35  45  55  65  75  85;  % Full throttle (100%)
];
veh_data(2).wheel_radius = 0.35235; % m = P225/55/R18

% Vehicle 3 = 2022 Ford F-150 Regular Cab Truck
veh_data(3).speeds = 1000:250:6000; %rpm
veh_data(3).torques = [200, 300, 400, 475, 545, 600, 637, 662, 675, 675, ...
                    673, 662, 655, 642, 628, 600, 575, 542, 520, 498, 475];
veh_data(3).gears = [4.696, 2.985, 2.146, 1.8, 1.52, 1.275, 1.00, 0.854, 0.689, 0.636];
veh_data(3).reverse = 4.866;
veh_data(3).final_drive = 3.15;
veh_data(3).gear_eff = 0.92;
veh_data(3).width = 2.029; %m
veh_data(3).height = 1.961; %m
veh_data(3).length = 5.885; %m
veh_data(3).mass = 2114; %unloaded kg
veh_data(3).transmission = 0;
veh_data(3).shift_up_speeds = [
    10 20 30 40 50 60 70 80 90 0;% inf;   % Low throttle (0%)
    15 25 35 45 55 65 75 85 95 0;% inf;   % Medium throttle (50%)
    20 30 40 50 60 70 80 90 100 0;% inf   % Full throttle (100%)
];
veh_data(3).shift_down_speeds = [
    0   10  20  30  40  50  60  70  80  85;   % Low throttle (0%)
    5   15  25  35  45  55  65  75  85  95;   % Medium throttle (50%)
    10  20  30  40  50  60  70  80  90  100;  % Full throttle (100%)
];
veh_data(3).wheel_radius = 0.419; % m = 275/60/R20

veh_data(1).gears(7:10) = 0;
veh_data(1).shift_up_speeds(:, 7:10) = 0;
veh_data(1).shift_down_speeds(:, 7:10) = 0;

veh_data(2).gears(9:10) = 0;
veh_data(2).shift_up_speeds(:, 9:10) = 0;
veh_data(2).shift_down_speeds(:, 9:10) = 0;
veh_data(2).transmission = uint8(0);
veh_data(3).transmission = uint8(0);

bus_info = Simulink.Bus.createObject(veh_data(1));
VehicleBus = evalin('base', bus_info.busName);
evalin('base', ['clear ' bus_info.busName]);

for i = 1:3
    p = Simulink.Parameter;
    p.Value = veh_data(i);
    p.DataType = 'Bus: VehicleBus';
    assignin('base', sprintf('veh%d', i), p);
end