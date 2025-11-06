// // camera_calib_picking.cpp
// // Build: g++ camera_calib_picking.cpp -o calib `pkg-config --cflags --libs opencv4` -std=c++17
// // hoặc tương ứng trong CMake / Qt project.

// #include <opencv2/opencv.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/imgproc.hpp>
// #include <filesystem>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <optional>

// namespace fs = std::filesystem;

// struct CalibResult {
//   cv::Mat cameraMatrix;      // K (3x3, CV_64F)
//   cv::Mat distCoeffs;        // (k1,k2,p1,p2[,k3,...]) CV_64F
//   std::vector<cv::Mat> rvecs;
//   std::vector<cv::Mat> tvecs;
//   cv::Mat newCameraMatrix;   // optimal K'
//   cv::Rect roi;              // valid ROI after undistort (x,y,w,h)
//   cv::Mat map1, map2;        // undistort maps (CV_16SC2 / CV_32FC1 etc.)
//   double reprojectionError = 0.0;
//   cv::Size imageSize;
// };

// // Calibrate camera from chessboard images
// CalibResult calibrateCameraFromChessboards(
//     const std::vector<std::string> &imagePaths,
//     const cv::Size &patternSize,   // inner corners (nx, ny)
//     double squareSize = 0.024,     // in meters (or any consistent unit)
//     int flags = 0,
//     const cv::TermCriteria &termCrit = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 1e-6),
//     bool saveResult = false,
//     const std::string &savePath = "calib_result.yml",
//     bool verbose = true
//     ) {
//   if (imagePaths.empty()) throw std::runtime_error("No calibration images provided.");

//   // prepare object points
//   int nx = patternSize.width;
//   int ny = patternSize.height;
//   std::vector<cv::Point3f> objp;
//   objp.reserve(nx * ny);
//   for (int j = 0; j < ny; ++j)
//     for (int i = 0; i < nx; ++i)
//       objp.emplace_back(i * squareSize, j * squareSize, 0.0);

//   std::vector<std::vector<cv::Point3f>> objectPoints;
//   std::vector<std::vector<cv::Point2f>> imagePoints;
//   cv::Size imageSize;
//   int successful = 0;

//   for (const auto &p : imagePaths) {
//     cv::Mat gray = cv::imread(p, cv::IMREAD_GRAYSCALE);
//     if (gray.empty()) {
//       if (verbose) std::cout << "Warning: cannot read " << p << std::endl;
//       continue;
//     }
//     if (imageSize == cv::Size()) imageSize = cv::Size(gray.cols, gray.rows);

//     std::vector<cv::Point2f> corners;
//     bool found = cv::findChessboardCorners(gray, patternSize, corners,
//                                            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);
//     if (!found) {
//       if (verbose) std::cout << "Chessboard NOT found in " << p << std::endl;
//       continue;
//     }
//     // refine to subpixel
//     cv::cornerSubPix(gray, corners, cv::Size(11,11), cv::Size(-1,-1), termCrit);
//     imagePoints.push_back(corners);
//     objectPoints.push_back(objp);
//     ++successful;
//     if (verbose) std::cout << "Found corners in " << p << std::endl;
//   }

//   if (successful < 5) {
//     throw std::runtime_error("Not enough valid calibration images (found " + std::to_string(successful) + "). Need >=5 good views.");
//   }

//   CalibResult res;
//   res.imageSize = imageSize;

//   cv::Mat K, dist;
//   std::vector<cv::Mat> rvecs, tvecs;
//   double rms = cv::calibrateCamera(objectPoints, imagePoints, imageSize, K, dist, rvecs, tvecs, flags);

//   // compute reprojection error
//   double totalErr = 0;
//   size_t totalPoints = 0;
//   for (size_t i = 0; i < objectPoints.size(); ++i) {
//     std::vector<cv::Point2f> proj;
//     cv::projectPoints(objectPoints[i], rvecs[i], tvecs[i], K, dist, proj);
//     double err = cv::norm(imagePoints[i], proj, cv::NORM_L2);
//     totalErr += err * err;
//     totalPoints += objectPoints[i].size();
//   }
//   double reprojError = std::sqrt(totalErr / totalPoints);

//   // optimal new camera matrix
//   cv::Mat newK = cv::getOptimalNewCameraMatrix(K, dist, imageSize, 0.0, imageSize, &res.roi);

//   // init undistort rectify maps
//   cv::Mat map1, map2;
//   cv::initUndistortRectifyMap(K, dist, cv::Mat(), newK, imageSize, CV_16SC2, map1, map2);

//   // fill result
//   res.cameraMatrix = K.clone();
//   res.distCoeffs = dist.clone();
//   res.rvecs = rvecs;
//   res.tvecs = tvecs;
//   res.newCameraMatrix = newK.clone();
//   res.map1 = map1.clone();
//   res.map2 = map2.clone();
//   res.reprojectionError = reprojError;

//   if (verbose) {
//     std::cout << "Calibrated camera:" << std::endl;
//     std::cout << " - image_size: " << imageSize << std::endl;
//     std::cout << " - camera_matrix:\n" << K << std::endl;
//     std::cout << " - dist_coeffs: " << dist.t() << std::endl;
//     std::cout << " - reprojection_error: " << reprojError << std::endl;
//     std::cout << " - roi: " << res.roi << std::endl;
//   }

//   if (saveResult) {
//     cv::FileStorage fs(savePath, cv::FileStorage::WRITE);
//     fs << "camera_matrix" << res.cameraMatrix;
//     fs << "dist_coeffs" << res.distCoeffs;
//     fs << "new_camera_matrix" << res.newCameraMatrix;
//     fs << "roi_x" << res.roi.x << "roi_y" << res.roi.y << "roi_w" << res.roi.width << "roi_h" << res.roi.height;
//     fs << "reproj_error" << res.reprojectionError;
//     fs << "image_width" << res.imageSize.width << "image_height" << res.imageSize.height;
//     // store maps as mats (they might be large)
//     fs << "map1" << res.map1;
//     fs << "map2" << res.map2;
//     fs.release();
//     if (verbose) std::cout << "Saved calibration to " << savePath << std::endl;
//   }

//   return res;
// }

// // Undistort an image using precomputed maps and crop to ROI
// cv::Mat undistortImage(const cv::Mat &img, const CalibResult &calib) {
//   cv::Mat und;
//   if (calib.map1.empty() || calib.map2.empty()) {
//     // fallback
//     cv::undistort(img, und, calib.cameraMatrix, calib.distCoeffs, calib.newCameraMatrix);
//   } else {
//     cv::remap(img, und, calib.map1, calib.map2, cv::INTER_LINEAR);
//   }
//   // crop to roi if valid
//   if (calib.roi.width > 0 && calib.roi.height > 0 && calib.roi.x >= 0 && calib.roi.y >= 0
//       && calib.roi.x + calib.roi.width <= und.cols && calib.roi.y + calib.roi.height <= und.rows) {
//     und = und(calib.roi).clone();
//   }
//   return und;
// }

// // Convert pixel (u,v) -> unit ray direction in camera coordinates
// // Returns normalized direction vec (x,y,1) in camera coords
// cv::Vec3d pixelToCameraRay(const cv::Point2d &pixel, const CalibResult &calib) {
//   // undistortPoints -> gives normalized coordinates if P == identity
//   std::vector<cv::Point2f> src{cv::Point2f((float)pixel.x, (float)pixel.y)};
//   std::vector<cv::Point2f> dst;
//   // Use P = identity so result is normalized image coordinates (x/z, y/z)
//   cv::Mat P = cv::Mat::eye(3,3, CV_64F);
//   cv::undistortPoints(src, dst, calib.cameraMatrix, calib.distCoeffs, cv::Mat(), P);
//   double x = dst[0].x;
//   double y = dst[0].y;
//   cv::Vec3d dir(x, y, 1.0);
//   double norm = cv::norm(dir);
//   if (norm > 1e-12) dir /= norm;
//   return dir;
// }

// // Intersect pixel ray with plane z = plane_z (in world coordinates).
// // If R_cam2world and t_cam2world are empty, assume camera coords == world coords.
// std::optional<cv::Point3d> pixelToWorldPlane(
//     const cv::Point2d &pixel,
//     double plane_z,
//     const CalibResult &calib,
//     const cv::Mat &R_cam2world = cv::Mat(), // 3x3
//     const cv::Mat &t_cam2world = cv::Mat()  // 3x1
//     ) {
//   cv::Vec3d dir_cam = pixelToCameraRay(pixel, calib); // unit vector in camera coords
//   cv::Vec3d cam_origin(0.0, 0.0, 0.0);

//   cv::Mat R;
//   cv::Mat t;
//   if (R_cam2world.empty()) {
//     R = cv::Mat::eye(3,3, CV_64F);
//   } else {
//     R = R_cam2world;
//   }
//   if (t_cam2world.empty()) {
//     t = cv::Mat::zeros(3,1, CV_64F);
//   } else {
//     t = t_cam2world;
//   }

//   // convert cam_origin and dir to world coords: X_w = R * X_cam + t
//   cv::Mat origin_cam = (cv::Mat_<double>(3,1) << cam_origin[0], cam_origin[1], cam_origin[2]);
//   cv::Mat origin_w = R * origin_cam + t;
//   cv::Mat dir_cam_mat = (cv::Mat_<double>(3,1) << dir_cam[0], dir_cam[1], dir_cam[2]);
//   cv::Mat dir_w = R * dir_cam_mat;

//   double dir_w_z = dir_w.at<double>(2,0);
//   if (std::abs(dir_w_z) < 1e-12) {
//     // ray parallel to plane
//     return std::nullopt;
//   }
//   double s = (plane_z - origin_w.at<double>(2,0)) / dir_w_z;
//   if (s < 0) {
//     // intersection behind camera
//     return std::nullopt;
//   }
//   cv::Mat pt_w = origin_w + s * dir_w;
//   return cv::Point3d(pt_w.at<double>(0,0), pt_w.at<double>(1,0), pt_w.at<double>(2,0));
// }

// // Project 3D world points to image pixels.
// // If caller has R_world2cam (3x3) and t_world2cam (3x1) provide them.
// // Otherwise assume identity.
// std::vector<cv::Point2f> projectPointsWorld(
//     const std::vector<cv::Point3f> &points3D,
//     const CalibResult &calib,
//     const cv::Mat &R_world2cam = cv::Mat(),
//     const cv::Mat &t_world2cam = cv::Mat()
//     ) {
//   cv::Mat R = R_world2cam.empty() ? cv::Mat::eye(3,3,CV_64F) : R_world2cam;
//   cv::Mat t = t_world2cam.empty() ? cv::Mat::zeros(3,1,CV_64F) : t_world2cam;

//   cv::Mat rvec;
//   cv::Rodrigues(R, rvec); // convert rotation matrix to rotation vector for projectPoints
//   std::vector<cv::Point2f> imgpts;
//   cv::projectPoints(points3D, rvec, t, calib.cameraMatrix, calib.distCoeffs, imgpts);
//   return imgpts;
// }

// // Utility: gather images in folder with extension filter
// std::vector<std::string> gatherImageFiles(const std::string &folder, const std::vector<std::string> &exts = {".jpg", ".png", ".jpeg", ".bmp"}) {
//   std::vector<std::string> files;
//   for (const auto &entry : fs::directory_iterator(folder)) {
//     if (!entry.is_regular_file()) continue;
//     std::string ext = entry.path().extension().string();
//     std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
//     if (std::find(exts.begin(), exts.end(), ext) != exts.end()) {
//       files.push_back(entry.path().string());
//     }
//   }
//   std::sort(files.begin(), files.end());
//   return files;
// }

// // Example usage in main
// int main(int argc, char** argv) {
//   // if (argc < 2) {
//   //   std::cout << "Usage: ./calib <images_folder>" << std::endl;
//   //   return 1;
//   // }

//   std::string folder = "D:/Personal project/Vision/Qt-Vision-Widget/calibration/calib_images/";

//   // std::string folder = argv[1];
//   auto images = gatherImageFiles(folder);
//   if (images.empty()) {
//     std::cerr << "No images found in folder: " << folder << std::endl;
//     return 1;
//   }

//   try {
//     // chessboard inner corners (nx, ny) e.g., 9x6
//     cv::Size patternSize(13, 9);
//     double squareSize = 0.020; // meters (adjust to your chessboard)
//     CalibResult calib = calibrateCameraFromChessboards(images, patternSize, squareSize, 0, cv::TermCriteria(), true, "calib_result.yml");

//     // Example: undistort an image and show
//     // cv::Mat img = cv::imread(images[0], cv::IMREAD_COLOR);
//     cv::Mat img = cv::imread("D:/Personal project/Vision/Qt-Vision-Widget/calibration/test_images/test_image_2.bmp", cv::IMREAD_COLOR);
//     cv::Mat und = undistortImage(img, calib);
//     cv::imshow("orig", img);
//     cv::imshow("undistorted", und);
//     cv::imwrite("undistorted.bmp", und);
//     cv::waitKey(0);

//     // Example: pixel -> ray
//     cv::Point2d px( und.cols/2.0, und.rows/2.0 );
//     cv::Vec3d ray = pixelToCameraRay(px, calib);
//     std::cout << "Ray (camera coords) for pixel " << px << " : " << ray << std::endl;

//     // Example: intersect with table plane z = 0 (world coords), assuming camera==world
//     auto pt3 = pixelToWorldPlane(px, 0.0, calib);
//     if (pt3) {
//       std::cout << "Intersection with z=0: " << *pt3 << std::endl;
//     } else {
//       std::cout << "Ray parallel or behind camera." << std::endl;
//     }

//     // Example projection of a 3D point
//     std::vector<cv::Point3f> pts3 = { cv::Point3f(0.1f, 0.05f, 0.2f) }; // in meters
//     auto imgpts = projectPointsWorld(pts3, calib);
//     std::cout << "Projected 2D: " << imgpts[0] << std::endl;

//   } catch (const std::exception &e) {
//     std::cerr << "Calibration failed: " << e.what() << std::endl;
//     return 1;
//   }

//   return 0;
// }
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <optional>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

// Convert cv::Mat (CV_32F or CV_64F, 1xN or Nx1 or RxC) -> QJsonArray (row-major)
inline QJsonArray matToJsonArray(const cv::Mat &m) {
  QJsonArray arr;
  CV_Assert(!m.empty());
  // We'll convert numbers to double for JSON
  if (m.isContinuous()) {
    int total = m.total() * m.channels();
    if (m.depth() == CV_64F) {
      const double* ptr = m.ptr<double>();
      for (int i = 0; i < total; ++i) arr.append(ptr[i]);
    } else if (m.depth() == CV_32F) {
      const float* ptr = m.ptr<float>();
      for (int i = 0; i < total; ++i) arr.append(static_cast<double>(ptr[i]));
    } else if (m.depth() == CV_8U) {
      const uchar* ptr = m.ptr<uchar>();
      for (int i = 0; i < total; ++i) arr.append(static_cast<int>(ptr[i]));
    } else {
      // convert other types to double temporarily
      cv::Mat tmp;
      m.convertTo(tmp, CV_64F);
      const double* ptr = tmp.ptr<double>();
      for (int i = 0; i < tmp.total() * tmp.channels(); ++i) arr.append(ptr[i]);
    }
  } else {
    // non-continuous: iterate rows
    cv::Mat tmp;
    m.convertTo(tmp, CV_64F);
    const double* ptr = tmp.ptr<double>();
    for (int i = 0; i < tmp.total() * tmp.channels(); ++i) arr.append(ptr[i]);
  }
  return arr;
}

// Convert QJsonArray -> cv::Mat with given rows, cols and type (CV_64F or CV_32F)
inline cv::Mat jsonArrayToMat(const QJsonArray &arr, int rows, int cols, int type = CV_64F) {
  CV_Assert((int)arr.size() == rows * cols);
  cv::Mat m(rows, cols, type);
  if (type == CV_64F) {
    double* ptr = m.ptr<double>();
    for (int i = 0; i < rows * cols; ++i) ptr[i] = arr[i].toDouble();
  } else if (type == CV_32F) {
    float* ptr = m.ptr<float>();
    for (int i = 0; i < rows * cols; ++i) ptr[i] = static_cast<float>(arr[i].toDouble());
  } else {
    // fallback: fill double and convert
    cv::Mat tmp(rows, cols, CV_64F);
    double* tptr = tmp.ptr<double>();
    for (int i = 0; i < rows * cols; ++i) tptr[i] = arr[i].toDouble();
    tmp.convertTo(m, type);
  }
  return m;
}

// Hàm calibrate camera và undistort ảnh
void calibrateAndUndistort(const vector<string>& imagePaths, Size boardSize, float squareSize, Mat& cameraMatrix, Mat& distCoeffs, Mat& newK, cv::Mat &map1, cv::Mat &map2) {
  vector<vector<Point3f>> objectPoints; // Tọa độ 3D trong không gian thực
  vector<vector<Point2f>> imagePoints;  // Tọa độ 2D trong ảnh
  vector<Point3f> obj;

  // Khởi tạo tọa độ điểm 3D (0,0,0), (1,0,0), ..., (boardSize.width-1, boardSize.height-1,0)
  for (int i = 0; i < boardSize.height; i++) {
    for (int j = 0; j < boardSize.width; j++) {
      obj.push_back(Point3f(j * squareSize, i * squareSize, 0));
    }
  }

  // Duyệt qua các ảnh calibration
  int cols;
  int rows;
  for (const auto& path : imagePaths) {
    Mat image = imread(path);
    if (image.empty()) {
      cerr << "Không đọc được ảnh: " << path << endl;
      continue;
    }

    cols = image.cols;
    rows = image.rows;

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    vector<Point2f> corners;
    bool found = findChessboardCorners(gray, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE);

    if (found) {
      cornerSubPix(gray, corners, Size(13, 9), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
      imagePoints.push_back(corners);
      objectPoints.push_back(obj);
    } else {
      cerr << "Không tìm thấy chessboard corners trong ảnh: " << path << endl;
    }
  }

  // Calibrate camera
  vector<Mat> rvecs, tvecs;
  double rms = calibrateCamera(objectPoints, imagePoints, Size(cols, rows), cameraMatrix, distCoeffs, rvecs, tvecs);

  double alpha = 0.0; // 0 -> crop, 1 -> keep all
  newK = cv::getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, Size(cols, rows), alpha, Size(cols, rows));

  // cv::Mat map1, map2;
  cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), newK, Size(cols, rows), CV_16SC2, map1, map2);

  cout << "Calibration hoàn tất với RMS error: " << rms << endl;
}

// Hàm undistort ảnh
Mat undistortImage(const Mat& distortedImage, const Mat& cameraMatrix, const Mat& distCoeffs) {
  Mat undistortedImage;
  undistort(distortedImage, undistortedImage, cameraMatrix, distCoeffs);
  return undistortedImage;
}

// Utility: gather images in folder with extension filter
std::vector<std::string> gatherImageFiles(const std::string &folder, const std::vector<std::string> &exts = {".jpg", ".png", ".jpeg", ".bmp"}) {
  std::vector<std::string> files;
  for (const auto &entry : fs::directory_iterator(folder)) {
    if (!entry.is_regular_file()) continue;
    std::string ext = entry.path().extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (std::find(exts.begin(), exts.end(), ext) != exts.end()) {
      files.push_back(entry.path().string());
    }
  }
  std::sort(files.begin(), files.end());
  return files;
}

// // Save to JSON + YAML maps
// inline bool saveCalibToJson(const CalibResult &calib, const QString &jsonPath, const QString &mapsPath /*yaml*/) {
//   // 1) JSON object
//   QJsonObject root;
//   // cameraMatrix 3x3
//   root["camera_rows"] = 3;
//   root["camera_cols"] = 3;
//   root["camera_matrix"] = matToJsonArray(calib.cameraMatrix);

//   // distCoeffs - store as rows x cols
//   root["dist_rows"] = calib.distCoeffs.rows;
//   root["dist_cols"] = calib.distCoeffs.cols;
//   root["dist_coeffs"] = matToJsonArray(calib.distCoeffs);

//   // new camera
//   root["new_camera_rows"] = calib.newCameraMatrix.rows;
//   root["new_camera_cols"] = calib.newCameraMatrix.cols;
//   root["new_camera_matrix"] = matToJsonArray(calib.newCameraMatrix);

//   // roi
//   QJsonObject roiObj;
//   roiObj["x"] = calib.roi.x;
//   roiObj["y"] = calib.roi.y;
//   roiObj["w"] = calib.roi.width;
//   roiObj["h"] = calib.roi.height;
//   root["roi"] = roiObj;

//   // image size
//   QJsonObject sizeObj;
//   sizeObj["width"] = calib.imageSize.width;
//   sizeObj["height"] = calib.imageSize.height;
//   root["image_size"] = sizeObj;

//   // reprojection error
//   root["reprojection_error"] = calib.reprojectionError;

//   // maps path (reference)
//   root["maps_file"] = mapsPath;

//   // write JSON to disk
//   QJsonDocument doc(root);
//   QFile file(jsonPath);
//   if (!file.open(QIODevice::WriteOnly)) return false;
//   file.write(doc.toJson(QJsonDocument::Indented));
//   file.close();

//   // 2) Save maps (if exist) to YAML using OpenCV FileStorage
//   if (!calib.map1.empty() && !calib.map2.empty()) {
//     try {
//       cv::FileStorage fs(mapsPath.toStdString(), cv::FileStorage::WRITE);
//       fs << "map1" << calib.map1;
//       fs << "map2" << calib.map2;
//       fs.release();
//     } catch (const std::exception &e) {
//       qWarning("Failed to write maps: %s", e.what());
//       // JSON already saved; still return false to indicate partial failure
//       return false;
//     }
//   }
//   return true;
// }

// // Load from JSON + YAML maps
// inline bool loadCalibFromJson(CalibResult &out, const QString &jsonPath) {
//   QFile file(jsonPath);
//   if (!file.open(QIODevice::ReadOnly)) return false;
//   QByteArray data = file.readAll();
//   file.close();

//   QJsonDocument doc = QJsonDocument::fromJson(data);
//   if (doc.isNull()) return false;
//   QJsonObject root = doc.object();

//   // cameraMatrix
//   int crow = root["camera_rows"].toInt();
//   int ccol = root["camera_cols"].toInt();
//   QJsonArray camArr = root["camera_matrix"].toArray();
//   out.cameraMatrix = jsonArrayToMat(camArr, crow, ccol, CV_64F);

//   // dist
//   int drows = root["dist_rows"].toInt();
//   int dcols = root["dist_cols"].toInt();
//   QJsonArray distArr = root["dist_coeffs"].toArray();
//   out.distCoeffs = jsonArrayToMat(distArr, drows, dcols, CV_64F);

//   // new camera
//   int ncr = root["new_camera_rows"].toInt();
//   int ncc = root["new_camera_cols"].toInt();
//   QJsonArray newKArr = root["new_camera_matrix"].toArray();
//   out.newCameraMatrix = jsonArrayToMat(newKArr, ncr, ncc, CV_64F);

//   // roi
//   QJsonObject roiObj = root["roi"].toObject();
//   out.roi = cv::Rect(roiObj["x"].toInt(), roiObj["y"].toInt(), roiObj["w"].toInt(), roiObj["h"].toInt());

//   // image size
//   QJsonObject sizeObj = root["image_size"].toObject();
//   out.imageSize = cv::Size(sizeObj["width"].toInt(), sizeObj["height"].toInt());

//   out.reprojectionError = root["reprojection_error"].toDouble();

//   // maps: load YAML if path present
//   QString mapsPath = root["maps_file"].toString();
//   if (!mapsPath.isEmpty()) {
//     try {
//       cv::FileStorage fs(mapsPath.toStdString(), cv::FileStorage::READ);
//       if (fs.isOpened()) {
//         fs["map1"] >> out.map1;
//         fs["map2"] >> out.map2;
//         fs.release();
//       } else {
//         qWarning("maps file not opened: %s", mapsPath.toStdString().c_str());
//       }
//     } catch (const std::exception &e) {
//       qWarning("Failed to read maps: %s", e.what());
//       // continue: maps optional
//     }
//   }

//   return true;
// }

// Ví dụ sử dụng
int main() {
  // Danh sách ảnh calibration (thay bằng đường dẫn thực tế)
  // vector<string> imagePaths = {
  //     "path/to/calib1.jpg",
  //     "path/to/calib2.jpg",
  //     // ... thêm ít nhất 10-15 ảnh
  // };


  // load file
  QFile file("temp.json");
  if (!file.open(QIODevice::ReadOnly)) return false;
  QByteArray data = file.readAll();
  file.close();

  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull()) return false;
  QJsonObject root = doc.object();

  // cameraMatrix
  int crow = root["camera_rows"].toInt();
  int ccol = root["camera_cols"].toInt();
  QJsonArray camArr = root["camera_matrix"].toArray();
  cv::Mat cameraMatrix = jsonArrayToMat(camArr, crow, ccol, CV_64F);

  // dist
  int drows = root["dist_rows"].toInt();
  int dcols = root["dist_cols"].toInt();
  QJsonArray distArr = root["dist_coeffs"].toArray();
  cv::Mat distCoeffs = jsonArrayToMat(distArr, drows, dcols, CV_64F);

  std::cout << cameraMatrix << std::endl;
  std::cout << distCoeffs << std::endl;

  return 0;


  // std::string folder = "D:/Personal project/Vision/Qt-Vision-Widget/calibration/calib_images/";
  // auto imagePaths = gatherImageFiles(folder);
  // if (imagePaths.empty()) {
  //   std::cerr << "No images found in folder: " << folder << std::endl;
  //   return 1;
  // }


  // // Kích thước bàn cờ (số ô theo chiều ngang và dọc)
  // Size boardSize(13, 9);
  // // Kích thước thực tế của mỗi ô (tính theo đơn vị bất kỳ, ví dụ mm)
  // float squareSize = 20.0f;

  // Mat cameraMatrix, distCoeffs;
  // cv::Mat map1, map2, newK, roi;

  // // Thực hiện calibration
  // calibrateAndUndistort(imagePaths, boardSize, squareSize, cameraMatrix, distCoeffs, newK, map1, map2);

  // // Undistort ảnh mẫu
  // Mat testImage = imread("D:/Personal project/Vision/Qt-Vision-Widget/calibration/test_images/test_image_2.bmp");
  // if (!testImage.empty()) {
  //   cv::Mat und;
  //   cv::remap(testImage, und, map1, map2, cv::INTER_LINEAR);
  //   cv::Mat und_cropped = und.clone(); // nếu alpha = 0.0 sẽ an toàn
  //   imwrite("undistorted_output.bmp", und_cropped);
  //   imshow("undistorted", und_cropped);

  //   // Mat result = undistortImage(testImage, cameraMatrix, distCoeffs);
  //   // imshow("Ảnh gốc", testImage);
  //   // imshow("Ảnh đã undistort", result);
  //   waitKey(0);
  // }

  // // Lưu thông số calibration (tuỳ chọn)
  // FileStorage fs("calibration_params.xml", FileStorage::WRITE);
  // fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
  // fs.release();

  // // 1) JSON object
  // QJsonObject root;
  // // cameraMatrix 3x3
  // root["camera_rows"] = 3;
  // root["camera_cols"] = 3;
  // root["camera_matrix"] = matToJsonArray(cameraMatrix);

  // // distCoeffs - store as rows x cols
  // root["dist_rows"] = distCoeffs.rows;
  // root["dist_cols"] = distCoeffs.cols;
  // root["dist_coeffs"] = matToJsonArray(distCoeffs);

  // QJsonDocument doc(root);
  // QFile jfile("temp.json");
  // if (!jfile.open(QIODevice::WriteOnly)) return false;
  // jfile.write(doc.toJson(QJsonDocument::Indented));
  // jfile.close();

  // return 0;
}
