clear
close all
clc

%% IMU
imu_bags = rosbag("../bagfiles/IMU_test/0deg.bag");
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/45d.bag")];
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/90d.bag")];
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/135d.bag")];
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/180d.bag")];

shortest_time = imu_bags(1).EndTime - imu_bags(1).StartTime;

titles = ["0 deg", "45 deg", "90 deg", "135 deg", "180 deg"];

imu_ts = zeros(size(imu_bags));

for i = 2:size(imu_bags, 2)
    current_time = imu_bags(i).EndTime - imu_bags(i).StartTime;
    if current_time < shortest_time
        shortest_time = current_time;
    end
end

figure
hold on
for i = 1:size(imu_bags, 2)
    imu_angle = select(imu_bags(i), "Time", [imu_bags(i).StartTime, imu_bags(i).StartTime + shortest_time], "Topic", "/HJC/IMU/Pitch");
    imu_ts = timeseries(imu_angle, "Data");
    imu_ts.Time = imu_ts.Time - imu_ts.Time(1,1)*ones(size(imu_ts));
    imu_ts.Data = imu_ts.Data*180/pi;
    plot(imu_ts)
    imu_stat(i).name = titles(i);
    imu_stat(i).mean = mean(imu_ts);
    imu_stat(i).max = max(imu_ts);
    imu_stat(i).min = min(imu_ts);
end
legend(titles)
ylabel("Pitch [º]")
xlabel("Time [s]")
title("Pitch tests")
hold off

%% Odometry
odom_bag = rosbag("../bagfiles/odom_test/testOdom_new.bag");

odom_pos = select(odom_bag, "Topic", "/HJC/Vel_robot/Current_pos");
odom_ts = timeseries(odom_pos, "X", "Y");
odom_ts.Time = odom_ts.Time - odom_ts.Time(1,1)*ones(size(odom_ts.Time));
odom_ts.Data = -odom_ts.Data;

odom_ts2 = timeseries(odom_pos, "Z");
odom_ts2.Time = odom_ts2.Time - odom_ts2.Time(1,1)*ones(size(odom_ts2.Time));

figure
hold on
plot(odom_ts)
ylabel("Distance [m]")
yyaxis right
plot(odom_ts2)
ylabel("Angle turned [º]")
title("Odometry test")
xlabel("Time [s]")
legend("x position", "y position", "yaw")
hold off

odom_stat.max = max(odom_ts);
odom_stat.min = min(odom_ts);
odom_stat.distance = max(odom_ts) - min(odom_ts);

%% LQR
% lqr_bag = rosbag("../bagfiles/LQR/2022-05-21-10-41-08.bag");