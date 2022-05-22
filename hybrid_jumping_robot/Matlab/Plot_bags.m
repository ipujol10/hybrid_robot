clear
close all
clc

%% IMU
imu_bags = rosbag("../bagfiles/IMU_test/0deg.bag");
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/45d.bag")];
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/90d.bag")];
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/135d.bag")];
imu_bags = [imu_bags rosbag("../bagfiles/IMU_test/180d.bag")];

titles = ["0 deg", "45 deg", "90 deg", "135 deg", "180 deg"];

for i = 1:size(imu_bags, 2)
    imu_angle = select(imu_bags(i), "Topic", "/HJC/IMU/Pitch");
    imu_ts = timeseries(imu_angle, "Data");
    imu_ts.Time = imu_ts.Time - imu_ts.Time(1,1)*ones(size(imu_ts));
    imu_ts.Data = imu_ts.Data*180/pi;
    subplot(3, 2, i)
    plot(imu_ts)
    title(titles(i))
    ylabel("Pitch [º]")
    imu_stat(i).name = titles(i);
    imu_stat(i).mean = mean(imu_ts);
    imu_stat(i).max = max(imu_ts);
    imu_stat(i).min = min(imu_ts);
end

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