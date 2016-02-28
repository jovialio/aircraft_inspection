#include "component_test/occlusion_culling.h"


OcclusionCulling::OcclusionCulling(ros::NodeHandle &n, std::string modelName):
    nh(n),
    model(modelName)
{
//   original_pub = nh.advertise<sensor_msgs::PointCloud2>("original_point_cloud", 10);
//   visible_pub = nh.advertise<sensor_msgs::PointCloud2>("occlusion_free_cloud", 100);

   fov_pub = n.advertise<visualization_msgs::MarkerArray>("fov", 10);
   cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
   filtered_cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);

   occlusionFreeCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
   FrustumCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
   std::string path = ros::package::getPath("component_test");
   pcl::io::loadPCDFile<pcl::PointXYZ> (path+"/src/pcd/"+model, *cloud);
   voxelRes = 0.5;
   OriginalVoxelsSize=0.0;
   id=0.0;
   voxelFilterOriginal.setInputCloud (cloud);
   voxelFilterOriginal.setLeafSize (voxelRes, voxelRes, voxelRes);
   voxelFilterOriginal.initializeVoxelGrid();
   min_b1 = voxelFilterOriginal.getMinBoxCoordinates ();
   max_b1 = voxelFilterOriginal.getMaxBoxCoordinates ();
   for (int kk = min_b1.z (); kk <= max_b1.z (); ++kk)
   {
       for (int jj = min_b1.y (); jj <= max_b1.y (); ++jj)
       {
           for (int ii = min_b1.x (); ii <= max_b1.x (); ++ii)
           {
               Eigen::Vector3i ijk1 (ii, jj, kk);
               int index1 = voxelFilterOriginal.getCentroidIndexAt (ijk1);
               if(index1!=-1)
               {
                   OriginalVoxelsSize++;
               }

           }
       }
   }

   pcl::VoxelGrid<pcl::PointXYZ> voxelgrid;
   voxelgrid.setInputCloud (cloud);
   voxelgrid.setLeafSize (0.5f, 0.5f, 0.5f);
   voxelgrid.filter (*filtered_cloud);
}
OcclusionCulling::OcclusionCulling(std::string modelName):
    model(modelName)
{
    cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
    filtered_cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
    FrustumCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);

//    occlusionFreeCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
    std::string path = ros::package::getPath("component_test");
    pcl::io::loadPCDFile<pcl::PointXYZ> (path+"/src/pcd/"+model, *cloud);
    voxelRes = 0.5;
    OriginalVoxelsSize=0.0;
    id=0.0;
    voxelFilterOriginal.setInputCloud (cloud);
    voxelFilterOriginal.setLeafSize (voxelRes, voxelRes, voxelRes);
    voxelFilterOriginal.initializeVoxelGrid();
    min_b1 = voxelFilterOriginal.getMinBoxCoordinates ();
    max_b1 = voxelFilterOriginal.getMaxBoxCoordinates ();
    for (int kk = min_b1.z (); kk <= max_b1.z (); ++kk)
    {
        for (int jj = min_b1.y (); jj <= max_b1.y (); ++jj)
        {
            for (int ii = min_b1.x (); ii <= max_b1.x (); ++ii)
            {
                Eigen::Vector3i ijk1 (ii, jj, kk);
                int index1 = voxelFilterOriginal.getCentroidIndexAt (ijk1);
                if(index1!=-1)
                {
                    OriginalVoxelsSize++;
                }

            }
        }
    }
    pcl::VoxelGrid<pcl::PointXYZ> voxelgrid;
    voxelgrid.setInputCloud (cloud);
    voxelgrid.setLeafSize (0.5f, 0.5f, 0.5f);
    voxelgrid.filter (*filtered_cloud);
}
OcclusionCulling::OcclusionCulling():
    model(NULL)
{
    cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
    filtered_cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
    FrustumCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);

//    occlusionFreeCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud <pcl::PointXYZ>);
    std::string path = ros::package::getPath("component_test");
    pcl::io::loadPCDFile<pcl::PointXYZ> (path+"/src/pcd/scaled_desktop.pcd", *cloud);
    voxelRes = 0.5;
    OriginalVoxelsSize=0.0;
    id=0.0;
    voxelFilterOriginal.setInputCloud (cloud);
    voxelFilterOriginal.setLeafSize (voxelRes, voxelRes, voxelRes);
    voxelFilterOriginal.initializeVoxelGrid();
    min_b1 = voxelFilterOriginal.getMinBoxCoordinates ();
    max_b1 = voxelFilterOriginal.getMaxBoxCoordinates ();
    for (int kk = min_b1.z (); kk <= max_b1.z (); ++kk)
    {
        for (int jj = min_b1.y (); jj <= max_b1.y (); ++jj)
        {
            for (int ii = min_b1.x (); ii <= max_b1.x (); ++ii)
            {
                Eigen::Vector3i ijk1 (ii, jj, kk);
                int index1 = voxelFilterOriginal.getCentroidIndexAt (ijk1);
                if(index1!=-1)
                {
                    OriginalVoxelsSize++;
                }

            }
        }
    }
    pcl::VoxelGrid<pcl::PointXYZ> voxelgrid;
    voxelgrid.setInputCloud (cloud);
    voxelgrid.setLeafSize (0.5f, 0.5f, 0.5f);
    voxelgrid.filter (*filtered_cloud);
}
OcclusionCulling::~OcclusionCulling()
{
}
pcl::PointCloud<pcl::PointXYZ> OcclusionCulling::extractVisibleSurface(geometry_msgs::Pose location)
{
    // 1 *****Frustum Culling*******
    pcl::PointCloud <pcl::PointXYZ>::Ptr output (new pcl::PointCloud <pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr occlusionFreeCloud_local(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::FrustumCullingTT fc (true);
    fc.setInputCloud (cloud);
    fc.setVerticalFOV (45);
    fc.setHorizontalFOV (58);
    fc.setNearPlaneDistance (0.7);
    fc.setFarPlaneDistance (6.0);


    Eigen::Matrix4f camera_pose;
    Eigen::Matrix3d Rd;
    Eigen::Matrix3f Rf;

    camera_pose.setZero ();

    tf::Quaternion qt;
    qt.setX(location.orientation.x);
    qt.setY(location.orientation.y);
    qt.setZ(location.orientation.z);
    qt.setW(location.orientation.w);
    tf::Matrix3x3 R_tf(qt);
    tf::matrixTFToEigen(R_tf,Rd);
    Rf = Rd.cast<float>();
    camera_pose.block (0, 0, 3, 3) = Rf;
    Eigen::Vector3f T;
    T (0) = location.position.x; T (1) = location.position.y; T (2) = location.position.z;
    camera_pose.block (0, 3, 3, 1) = T;
    camera_pose (3, 3) = 1;
    fc.setCameraPose (camera_pose);
    fc.filter (*output);
    FrustumCloud->points= output->points;

    //2:****voxel grid occlusion estimation *****
    Eigen::Quaternionf quat(qt.w(),qt.x(),qt.y(),qt.z());
    output->sensor_origin_  = Eigen::Vector4f(T[0],T[1],T[2],0);
    output->sensor_orientation_= quat;
    pcl::VoxelGridOcclusionEstimationT voxelFilter;
    voxelFilter.setInputCloud (output);
    //voxelFilter.setLeafSize (0.03279f, 0.03279f, 0.03279f);
    voxelFilter.setLeafSize (voxelRes, voxelRes, voxelRes);
    voxelFilter.initializeVoxelGrid();

    int state,ret;

    pcl::PointXYZ pt,p1,p2;
    pcl::PointXYZRGB point;
    std::vector<Eigen::Vector3i, Eigen::aligned_allocator<Eigen::Vector3i> > out_ray;
    std::vector<geometry_msgs::Point> lineSegments;
    geometry_msgs::Point linePoint;

    // iterate over the entire frustum points
    for ( int i = 0; i < (int)output->points.size(); i ++ )
    {
        pcl::PointXYZ ptest = output->points[i];
        Eigen::Vector3i ijk = voxelFilter.getGridCoordinates( ptest.x, ptest.y, ptest.z);
        // process all free voxels
        int index = voxelFilter.getCentroidIndexAt (ijk);
        Eigen::Vector4f centroid = voxelFilter.getCentroidCoordinate (ijk);
        point = pcl::PointXYZRGB(0,244,0);
        point.x = centroid[0];
        point.y = centroid[1];
        point.z = centroid[2];

        if(index!=-1 )
        {
            out_ray.clear();
            ret = voxelFilter.occlusionEstimation( state,out_ray, ijk);
            //                        std::cout<<"State is:"<<state<<"\n";

            if(state != 1)
            {
                // estimate direction to target voxel
                Eigen::Vector4f direction = centroid - cloud->sensor_origin_;
                direction.normalize ();
                // estimate entry point into the voxel grid
                float tmin = voxelFilter.rayBoxIntersection (cloud->sensor_origin_, direction,p1,p2);
                if(tmin!=-1)
                {
                    // coordinate of the boundary of the voxel grid
                    Eigen::Vector4f start = cloud->sensor_origin_ + tmin * direction;
                    linePoint.x = cloud->sensor_origin_[0]; linePoint.y = cloud->sensor_origin_[1]; linePoint.z = cloud->sensor_origin_[2];
                    //std::cout<<"Box Min X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                    lineSegments.push_back(linePoint);

                    linePoint.x = start[0]; linePoint.y = start[1]; linePoint.z = start[2];
                    //std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                    lineSegments.push_back(linePoint);

                    linePoint.x = start[0]; linePoint.y = start[1]; linePoint.z = start[2];
                    //std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                    lineSegments.push_back(linePoint);

                    linePoint.x = centroid[0]; linePoint.y = centroid[1]; linePoint.z = centroid[2];
                    //std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                    lineSegments.push_back(linePoint);

                    occlusionFreeCloud_local->points.push_back(ptest);
                    occlusionFreeCloud->points.push_back(ptest);

                }
            }
        }


    }
    FreeCloud.points = occlusionFreeCloud_local->points;
    return FreeCloud;
}
float OcclusionCulling::calcCoveragePercent(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered)
{

    // *******************original cloud Grid***************************
    //used VoxelGridOcclusionEstimationT since the voxelGrid does not include getcentroid function
//        pcl::VoxelGridOcclusionEstimationT voxelFilterOriginal;
//        voxelFilterOriginal.setInputCloud (cloud);
//        voxelFilterOriginal.setLeafSize (voxelRes, voxelRes, voxelRes);
//        voxelFilterOriginal.initializeVoxelGrid();

     //*******************Occupied Cloud Grid***************************
    ros::Time covpercent_begin = ros::Time::now();
    pcl::VoxelGridOcclusionEstimationT voxelFilterOccupied;
//        voxelFilterOccupied.setInputCloud (occlusionFreeCloud);
    voxelFilterOccupied.setInputCloud (cloud_filtered);
    voxelFilterOccupied.setLeafSize (voxelRes, voxelRes, voxelRes);
    voxelFilterOccupied.initializeVoxelGrid();



     //*****************************************************************
    Eigen::Vector3i  min_b = voxelFilterOccupied.getMinBoxCoordinates ();
    Eigen::Vector3i  max_b = voxelFilterOccupied.getMaxBoxCoordinates ();
//        Eigen::Vector3i  min_b1 = voxelFilterOriginal.getMinBoxCoordinates ();
//        Eigen::Vector3i  max_b1 = voxelFilterOriginal.getMaxBoxCoordinates ();

    float MatchedVoxels=0 ;//OriginalVoxelsSize=0, ;

        // iterate over the entire original voxel grid to get the size of the grid
//        for (int kk = min_b1.z (); kk <= max_b1.z (); ++kk)
//        {
//            for (int jj = min_b1.y (); jj <= max_b1.y (); ++jj)
//            {
//                for (int ii = min_b1.x (); ii <= max_b1.x (); ++ii)
//                {
//                    Eigen::Vector3i ijk1 (ii, jj, kk);
//                    int index1 = voxelFilterOriginal.getCentroidIndexAt (ijk1);
//                    if(index1!=-1)
//                    {
//                        OriginalVoxelsSize++;
//                    }

//                }
//            }
//        }

        //iterate through the entire coverage grid to check the number of matched voxel between the original and the covered ones
    for (int kk = min_b.z (); kk <= max_b.z (); ++kk)
    {
        for (int jj = min_b.y (); jj <= max_b.y (); ++jj)
        {
            for (int ii = min_b.x (); ii <= max_b.x (); ++ii)
            {

                Eigen::Vector3i ijk (ii, jj, kk);
                int index1 = voxelFilterOccupied.getCentroidIndexAt (ijk);
                if(index1!=-1)
                {
                    Eigen::Vector4f centroid = voxelFilterOccupied.getCentroidCoordinate (ijk);
                    Eigen::Vector3i ijk_in_Original= voxelFilterOriginal.getGridCoordinates(centroid[0],centroid[1],centroid[2]) ;

                    int index = voxelFilterOriginal.getCentroidIndexAt (ijk_in_Original);

                    if(index!=-1)
                    {
                        MatchedVoxels++;
                    }
                }

            }
        }
    }

    //calculating the coverage percentage
    float coverage_ratio= MatchedVoxels/OriginalVoxelsSize;
    float coverage_percentage= coverage_ratio*100;

//    std::cout<<" the coverage ratio is = "<<coverage_ratio<<"\n";
//    std::cout<<" the number of covered voxels = "<<MatchedVoxels<<" voxel is covered"<<"\n";
//    std::cout<<" the number of original voxels = "<<OriginalVoxelsSize<<" voxel"<<"\n\n\n";
//    std::cout<<" the coverage percentage is = "<<coverage_percentage<<" %"<<"\n";

    ros::Time covpercent_end = ros::Time::now();
    double elapsed =  covpercent_end.toSec() - covpercent_begin.toSec();
//    std::cout<<"Coverage Percentage Calculation duration (s) = "<<elapsed<<"\n";

    return coverage_percentage;
}
//float OcclusionCulling::calcCoveragePercent(geometry_msgs::Pose location)
//{

//    pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud(new pcl::PointCloud<pcl::PointXYZ>);
//    pcl::PointCloud<pcl::PointXYZ> temp;
//    ros::Time occlusion_begin = ros::Time::now();
//    temp= extractVisibleSurface(location);
//    tempCloud->points = temp.points;
//    ros::Time occlusion_end = ros::Time::now();
//    double elapsed =  occlusion_end.toSec() - occlusion_begin.toSec();
//    std::cout<<"Extract visible surface duration (s) = "<<elapsed<<"\n";
//    // *******************original cloud Grid***************************
//    //used VoxelGridOcclusionEstimationT since the voxelGrid does not include getcentroid function
////        pcl::VoxelGridOcclusionEstimationT voxelFilterOriginal;
////        voxelFilterOriginal.setInputCloud (cloud);
////        voxelFilterOriginal.setLeafSize (voxelRes, voxelRes, voxelRes);
////        voxelFilterOriginal.initializeVoxelGrid();

//     //*******************Occupied Cloud Grid***************************
//    ros::Time covpercent_begin = ros::Time::now();
//    pcl::VoxelGridOcclusionEstimationT voxelFilterOccupied;
////        voxelFilterOccupied.setInputCloud (occlusionFreeCloud);
//    voxelFilterOccupied.setInputCloud (tempCloud);
//    voxelFilterOccupied.setLeafSize (voxelRes, voxelRes, voxelRes);
//    voxelFilterOccupied.initializeVoxelGrid();



//     //*****************************************************************
//    Eigen::Vector3i  min_b = voxelFilterOccupied.getMinBoxCoordinates ();
//    Eigen::Vector3i  max_b = voxelFilterOccupied.getMaxBoxCoordinates ();
////        Eigen::Vector3i  min_b1 = voxelFilterOriginal.getMinBoxCoordinates ();
////        Eigen::Vector3i  max_b1 = voxelFilterOriginal.getMaxBoxCoordinates ();

//    float MatchedVoxels=0 ;//OriginalVoxelsSize=0, ;

//        // iterate over the entire original voxel grid to get the size of the grid
////        for (int kk = min_b1.z (); kk <= max_b1.z (); ++kk)
////        {
////            for (int jj = min_b1.y (); jj <= max_b1.y (); ++jj)
////            {
////                for (int ii = min_b1.x (); ii <= max_b1.x (); ++ii)
////                {
////                    Eigen::Vector3i ijk1 (ii, jj, kk);
////                    int index1 = voxelFilterOriginal.getCentroidIndexAt (ijk1);
////                    if(index1!=-1)
////                    {
////                        OriginalVoxelsSize++;
////                    }

////                }
////            }
////        }

//        //iterate through the entire coverage grid to check the number of matched voxel between the original and the covered ones
//    for (int kk = min_b.z (); kk <= max_b.z (); ++kk)
//    {
//        for (int jj = min_b.y (); jj <= max_b.y (); ++jj)
//        {
//            for (int ii = min_b.x (); ii <= max_b.x (); ++ii)
//            {

//                Eigen::Vector3i ijk (ii, jj, kk);
//                int index1 = voxelFilterOccupied.getCentroidIndexAt (ijk);
//                if(index1!=-1)
//                {
//                    Eigen::Vector4f centroid = voxelFilterOccupied.getCentroidCoordinate (ijk);
//                    Eigen::Vector3i ijk_in_Original= voxelFilterOriginal.getGridCoordinates(centroid[0],centroid[1],centroid[2]) ;

//                    int index = voxelFilterOriginal.getCentroidIndexAt (ijk_in_Original);

//                    if(index!=-1)
//                    {
//                        MatchedVoxels++;
//                    }
//                }

//            }
//        }
//    }

//    //calculating the coverage percentage
//    float coverage_ratio= MatchedVoxels/OriginalVoxelsSize;
//    float coverage_percentage= coverage_ratio*100;

//    std::cout<<" the coverage ratio is = "<<coverage_ratio<<"\n";
//    std::cout<<" the number of covered voxels = "<<MatchedVoxels<<" voxel is covered"<<"\n";
//    std::cout<<" the number of original voxels = "<<OriginalVoxelsSize<<" voxel"<<"\n\n\n";
//    std::cout<<" the coverage percentage is = "<<coverage_percentage<<" %"<<"\n";

//    ros::Time covpercent_end = ros::Time::now();
//    elapsed =  covpercent_end.toSec() - covpercent_begin.toSec();
//    std::cout<<"Coverage Percentage Calculation duration (s) = "<<elapsed<<"\n";

//    return coverage_percentage;
//}

void OcclusionCulling::visualizeFOV(geometry_msgs::Pose location)
{

    pcl::PointCloud <pcl::PointXYZ>::Ptr output (new pcl::PointCloud <pcl::PointXYZ>);

    pcl::FrustumCullingTT fc (true);
    fc.setInputCloud (cloud);
    fc.setVerticalFOV (45);
    fc.setHorizontalFOV (58);
    fc.setNearPlaneDistance (0.7);
    fc.setFarPlaneDistance (6.0);

    Eigen::Matrix4f camera_pose;
    Eigen::Matrix3d Rd;
    Eigen::Matrix3f Rf;

    camera_pose.setZero ();

    tf::Quaternion qt;
    qt.setX(location.orientation.x);
    qt.setY(location.orientation.y);
    qt.setZ(location.orientation.z);
    qt.setW(location.orientation.w);
    tf::Matrix3x3 R_tf(qt);
    tf::matrixTFToEigen(R_tf,Rd);
    Rf = Rd.cast<float>();
    camera_pose.block (0, 0, 3, 3) = Rf;
    Eigen::Vector3f T;
    T (0) = location.position.x; T (1) = location.position.y; T (2) = location.position.z;
    camera_pose.block (0, 3, 3, 1) = T;
    camera_pose (3, 3) = 1;
    fc.setCameraPose (camera_pose);
    fc.filter (*output);

    //*** visualization the FOV *****
    std::vector<geometry_msgs::Point> fov_points;
    int c_color[3];
    geometry_msgs::Point point1;
    point1.x=fc.fp_bl[0];point1.y=fc.fp_bl[1];point1.z=fc.fp_bl[2]; fov_points.push_back(point1);//0
    point1.x=fc.fp_br[0];point1.y=fc.fp_br[1];point1.z=fc.fp_br[2]; fov_points.push_back(point1);//1
    point1.x=fc.fp_tr[0];point1.y=fc.fp_tr[1];point1.z=fc.fp_tr[2]; fov_points.push_back(point1);//2
    point1.x=fc.fp_tl[0];point1.y=fc.fp_tl[1];point1.z=fc.fp_tl[2]; fov_points.push_back(point1);//3
    point1.x=fc.np_bl[0];point1.y=fc.np_bl[1];point1.z=fc.np_bl[2]; fov_points.push_back(point1);//4
    point1.x=fc.np_br[0];point1.y=fc.np_br[1];point1.z=fc.np_br[2]; fov_points.push_back(point1);//5
    point1.x=fc.np_tr[0];point1.y=fc.np_tr[1];point1.z=fc.np_tr[2]; fov_points.push_back(point1);//6
    point1.x=fc.np_tl[0];point1.y=fc.np_tl[1];point1.z=fc.np_tl[2]; fov_points.push_back(point1);//7

    std::vector<geometry_msgs::Point> fov_linesNear;
    fov_linesNear.push_back(fov_points[4]);fov_linesNear.push_back(fov_points[5]);
    fov_linesNear.push_back(fov_points[5]);fov_linesNear.push_back(fov_points[6]);
    fov_linesNear.push_back(fov_points[6]);fov_linesNear.push_back(fov_points[7]);
    fov_linesNear.push_back(fov_points[7]);fov_linesNear.push_back(fov_points[4]);
    c_color[0]=1; c_color[1]=0; c_color[2]=1;
    linesList1 = drawLines(fov_linesNear,id++,c_color);//purple

    std::vector<geometry_msgs::Point> fov_linesFar;
    fov_linesFar.push_back(fov_points[0]);fov_linesFar.push_back(fov_points[1]);
    fov_linesFar.push_back(fov_points[1]);fov_linesFar.push_back(fov_points[2]);
    fov_linesFar.push_back(fov_points[2]);fov_linesFar.push_back(fov_points[3]);
    fov_linesFar.push_back(fov_points[3]);fov_linesFar.push_back(fov_points[0]);
    c_color[0]=1; c_color[1]=1; c_color[2]=0;
    linesList2 = drawLines(fov_linesFar,id++,c_color);//yellow


    std::vector<geometry_msgs::Point> fov_linestop;
    fov_linestop.push_back(fov_points[7]);fov_linestop.push_back(fov_points[3]);//top
    fov_linestop.push_back(fov_points[6]);fov_linestop.push_back(fov_points[2]);//top
    c_color[0]=0; c_color[1]=1; c_color[2]=0;
    linesList3 = drawLines(fov_linestop,id++,c_color);//green

    std::vector<geometry_msgs::Point> fov_linesbottom;
    fov_linesbottom.push_back(fov_points[5]);fov_linesbottom.push_back(fov_points[1]);//bottom
    fov_linesbottom.push_back(fov_points[4]);fov_linesbottom.push_back(fov_points[0]);//bottom
    c_color[0]=0; c_color[1]=0; c_color[2]=1;
    linesList4 = drawLines(fov_linesbottom,id++,c_color);//blue

    marker_array.markers.push_back(linesList1);
    marker_array.markers.push_back(linesList2);
    marker_array.markers.push_back(linesList3);
    marker_array.markers.push_back(linesList4);
    fov_pub.publish(marker_array);
}
visualization_msgs::Marker OcclusionCulling::drawLines(std::vector<geometry_msgs::Point> links, int id, int c_color[])
{
    visualization_msgs::Marker linksMarkerMsg;
    linksMarkerMsg.header.frame_id="map"; //change to "base_point_cloud" if it is used in component test package
    linksMarkerMsg.header.stamp=ros::Time::now();
    linksMarkerMsg.ns="link_marker";
    linksMarkerMsg.id = id;
    linksMarkerMsg.type = visualization_msgs::Marker::LINE_LIST;
    linksMarkerMsg.scale.x = 0.08;//0.03
    linksMarkerMsg.action  = visualization_msgs::Marker::ADD;
    linksMarkerMsg.lifetime  = ros::Duration(1000);
    std_msgs::ColorRGBA color;
    color.r = (float)c_color[0]; color.g=(float)c_color[1]; color.b=(float)c_color[2], color.a=1.0f;
//    if(c_color == 1)
//    {
//        color.r = 1.0;
//        color.g = 0.0;
//        color.b = 0.0;
//        color.a = 1.0;
//    }
//    else if(c_color == 2)
//    {
//        color.r = 0.0;
//        color.g = 1.0;
//        color.b = 0.0;
//        color.a = 1.0;
//    }
//    else
//    {
//        color.r = 0.0;
//        color.g = 0.0;
//        color.b = 1.0;
//        color.a = 1.0;
//    }
    std::vector<geometry_msgs::Point>::iterator linksIterator;
    for(linksIterator = links.begin();linksIterator != links.end();linksIterator++)
    {
        linksMarkerMsg.points.push_back(*linksIterator);
        linksMarkerMsg.colors.push_back(color);
    }
   return linksMarkerMsg;
}
