#include <opencv2/opencv.hpp>
#include <iostream>

#include <string>
#include <vector>

int main() {
    std::vector<int> vec;
    std::vector<std::vector<int>> f;
    for (int i = 0; i < 100; ++i) {
        vec.push_back(std::rand() % 10304);
    }

    for (int i = 0; i < 40; ++i) {
        cv::Mat mat = cv::imread("/home/nick/images/archive/s" + std::to_string(i) + "/1.pgm", cv::IMREAD_GRAYSCALE);
        mat.convertTo(mat, CV_32F);
        std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);

        std::vector<int> v;
        for (int j = 0; j < 100; ++j) {
            v.push_back(img[vec[j]]);
        }

        f.push_back(v);
    }

    int k = 0;
    for (int h = 0; h < 40; ++h) {
        //std::cout << h << ") ";
        float l = 0;
        for (int u = 2; u < 11; ++u) {
            std::vector<int> x;
            cv::Mat mat = cv::imread(
                    "/home/nick/images/archive/s" + std::to_string(h) + "/" + std::to_string(u) + ".pgm",
                    cv::IMREAD_GRAYSCALE);
            mat.convertTo(mat, CV_32F);
            std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);

            std::vector<int> test;
            for (int i = 0; i < 100; ++i) {
                test.push_back(img[vec[i]]);
            }

            for (int i = 0; i < 40; ++i) {
                int diff = 0;
                for (int j = 0; j < 100; ++j) {
                    diff += abs(f[i][j] - test[j]);
                }
                x.push_back(diff);
            }

            auto min = *std::min_element(x.begin(), x.end());
            for (int i = 0; i < 40; ++i) {
                if (x[i] == min && h == i) {
                    l += 1;
                }
            }

        }
        //std::cout << l << "\n";
        k += l;
    }
    std::cout << k;
    return 0;
}

