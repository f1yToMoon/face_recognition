#include <algorithm>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/imgcodecs.hpp"

int main() {
    int down_width = 46;
    int down_height = 56;
    std::vector<std::vector<int>> f;
    for (int i = 0; i < 40; ++i) {
        cv::Mat resized_down;
        cv::Mat mat = cv::imread("/home/nick/images/archive/s" + std::to_string(i) + "/1.pgm", cv::IMREAD_GRAYSCALE);
        resize(mat, resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);
        resized_down.convertTo(mat, CV_32F);
        std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);
        f.push_back(img);
    }

    int k = 0;
    for (int h = 0; h < 40; ++h) {
        std::cout << h << ") ";
        float l = 0;
        for (int u = 2; u < 11; ++u) {
            std::vector<int> x, test(256);
            cv::Mat resized_down;
            cv::Mat mat = cv::imread(
                    "/home/nick/images/archive/s" + std::to_string(h) + "/" + std::to_string(u) + ".pgm",
                    cv::IMREAD_GRAYSCALE);
            resize(mat, resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);
            resized_down.convertTo(mat, CV_32F);
            std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);

            for (int i = 0; i < 40; ++i) {
                int diff = 0;
                for (int j = 0; j < img.size(); ++j) {
                    diff += abs(f[i][j] - img[j]);
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
        std::cout << l << "\n";
        k += l;
    }
    std::cout << k << "/360";
    return 0;
}
