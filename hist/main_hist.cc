#include <algorithm>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/imgcodecs.hpp"

int main() {
    int bin = 8;
    std::vector<std::vector<int>> f;
    for (int i = 0; i < 40; ++i) {
        std::vector<int> hist(256);
        std::vector<int> gg;
        cv::Mat mat = cv::imread("/home/nick/images/archive/s" + std::to_string(i) + "/1.pgm", cv::IMREAD_GRAYSCALE);
        mat.convertTo(mat, CV_32F);
        std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);
        for(int j : img) {
            hist[j]++;
        }
        for (int iii = 1 ; iii <= bin; ++iii) {
            int ks = (iii-1)*256/bin;
            int kf = (iii)*256/bin - 1;
            int sum = 0;
            for (int aaa = ks; aaa <= kf; ++aaa) {
                sum += hist[aaa];
            }
            gg.push_back(sum);
        }
        f.push_back(gg);
    }

    int k = 0;
    for (int h = 0; h < 40; ++h) {
        std::cout << h << ") ";
        float l = 0;
        for (int u = 2; u < 11; ++u) {
            std::vector<int> x, gg(256);
            std::vector<int> test;
            cv::Mat mat = cv::imread(
                    "/home/nick/images/archive/s" + std::to_string(h) + "/" + std::to_string(u) + ".pgm",
                    cv::IMREAD_GRAYSCALE);
            mat.convertTo(mat, CV_32F);
            std::vector<int> img((float *) mat.data, (float *) mat.data + mat.rows * mat.cols);
            for(int i : img) {
                gg[i]++;
            }
            for (int iii = 1 ; iii <= bin; ++iii) {
                int ks = (iii-1)*256/bin;
                int kf = (iii)*256/bin - 1;
                int sum = 0;
                for (int aaa = ks; aaa <= kf; ++aaa) {
                    sum += gg[aaa];
                }
                test.push_back(sum);
            }

            for (int i = 0; i < 40; ++i) {
                int diff = 0;
                for (int j = 0; j < test.size(); ++j) {
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
        std::cout << l << "\n";
        k += l;
    }
    std::cout << k << "/360";
    return 0;
}
