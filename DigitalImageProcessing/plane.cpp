#include <pcl\visualization\pcl_visualizer.h>
#include <pcl\point_cloud.h>
#include <pcl\point_types.h>
#include"head.h"

void Plane() {
	//初始化点云
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_best(new pcl::PointCloud<pcl::PointXYZ>);

	//设置点云大小
	cloud->points.resize(350);
	cloud_plane->points.resize(350);
	cloud_best->points.resize(350);
	srand(time(0));
	//填充点云 -> 噪声
	for (int i = 0; i < 150; ++i) {
		cloud->points[i].x = rand() % 1000;
		cloud->points[i].y = rand() % 1000;
		cloud->points[i].z = rand() % 1000;
	}

	//填充点云 -> 平面
	for (int i = 150; i < cloud->points.size(); ++i) {
		cloud->points[i].x = rand() % 1000;
		cloud->points[i].y = rand() % 1000;
		cloud->points[i].z = 500 + rand() % 10;
	}

	//! ------------ 计算 -----------------------------------
	//! 平面方程 => Ax + By + Cz + D = 0
	//! 当前计算平面参数
	double A = 0, B = 0, C = 0, D = 0;
	//! 最优
	int best_A = 0, best_B = 0, best_C = 0, best_D = 0;
	double distance = 0;
	//! 容差
	float tolerance = 20;
	//! 票数
	int ticket = 0, best_ticket = 0;

	int temp_count = 0;

	for (int i = 0; i < cloud->points.size() - 3; i++) {
		for (int j = 1; j < cloud->points.size() - 2; j++) {
			//! init temo inliers
			for (int r = 0; r < cloud_plane->points.size() - 2; r++) {
				cloud_plane->points[r] = { 0,0,0 };
			}
			for (int k = 2; k < cloud->points.size() - 1; k++) {
				A = (cloud->points[k].y - cloud->points[i].y) * (cloud->points[k].z - cloud->points[i].z) - (cloud->points[j].z - cloud->points[i].z) * (cloud->points[k].y - cloud->points[i].y);
				B = (cloud->points[k].x - cloud->points[i].x) * (cloud->points[j].z - cloud->points[i].z) - (cloud->points[j].x - cloud->points[i].x) * (cloud->points[k].z - cloud->points[i].z);
				C = (cloud->points[j].x - cloud->points[i].x) * (cloud->points[k].y - cloud->points[i].y) - (cloud->points[k].x - cloud->points[i].x) * (cloud->points[j].y - cloud->points[i].y);
				D = -(cloud->points[i].x * A - cloud->points[i].y * B + cloud->points[i].z * C);

				for (int l = 0; l < cloud->points.size(); l++) {
					distance = abs(cloud->points[l].x * A - cloud->points[l].y * B + C * cloud->points[l].z + D) / (sqrt(A * A + B * B + C * C));
					if (distance < tolerance) {
						//! add temp inliers
						cloud_plane->points[ticket] = cloud->points[l];
						ticket++;
					}
				}

				if (ticket > best_ticket) {
					best_ticket = ticket;
					best_A = A;
					best_B = B;
					best_C = C;
					best_D = D;
					//! 存储 best inliers
					cloud_best = cloud_plane;
				}

				ticket = 0;
			}
		}
		cout << i << endl;

	}


	//cout << "A = " << best_A << endl;
	//cout << "B = " << best_B << endl;
	//cout << "C = " << best_C << endl;
	//cout << "D = " << best_D << endl;
	//cout << "best_ticket = " << best_ticket << endl;
	cout << "拟合平面方程：" << endl;
	cout << best_A << "x + " << best_B << "y + " << best_C << "z + " << D << " = 0" << endl;


	//! --------------------------------------------------------------
	//声明视窗
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	//设置视窗背景色
	viewer->setBackgroundColor(0, 0, 0);
	//预处理点云颜色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> magenta(cloud, 255, 0, 255);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> magenta_best(cloud_best, 0, 255, 0);
	//把点云加载到视窗
	viewer->addPointCloud(cloud, magenta, "cloud");
	viewer->addPointCloud(cloud_best, magenta_best, "cloud_best");
	//设置点云大小
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud_best");
	//显示
	viewer->spin();
}