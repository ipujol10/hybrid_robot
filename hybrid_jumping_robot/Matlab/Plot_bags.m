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
figure
odom_bag = rosbag("../bagfiles/odom_test/testOdom_new.bag");
odom_right = select(odom_bag, "Topic", "/HJC/Vel_robot/Right_wheel_pos");
odom_left = select(odom_bag, "Topic", "/HJC/Vel_robot/Left_wheel_pos");
odom_right_ts = timeseries(odom_right, "Data");
odom_right_ts.Time = odom_right_ts.Time - odom_bag.StartTime*ones(size(odom_right_ts.Time));
odom_left_ts = timeseries(odom_left, "Data");
odom_left_ts.Time = odom_left_ts.Time - odom_bag.StartTime*ones(size(odom_left_ts.Time));
plot(odom_left_ts)
hold on
plot(odom_right_ts)
hold off

%% LQR
% lqr_bag = rosbag("../bagfiles/LQR/2022-05-21-10-41-08.bag");